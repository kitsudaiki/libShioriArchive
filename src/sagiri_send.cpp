/**
 * @file        sagiri_send.cpp
 *
 * @author      Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 * @copyright   Apache License Version 2.0
 *
 *      Copyright 2022 Tobias Anker
 *
 *      Licensed under the Apache License, Version 2.0 (the "License");
 *      you may not use this file except in compliance with the License.
 *      You may obtain a copy of the License at
 *
 *          http://www.apache.org/licenses/LICENSE-2.0
 *
 *      Unless required by applicable law or agreed to in writing, software
 *      distributed under the License is distributed on an "AS IS" BASIS,
 *      WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *      See the License for the specific language governing permissions and
 *      limitations under the License.
 */

#include <libSagiriArchive/sagiri_send.h>
#include <libSagiriArchive/sagiri_messages.h>

#include <libKitsunemimiCommon/buffer/data_buffer.h>
#include <libKitsunemimiCrypto/common.h>

#include <libKitsunemimiHanamiCommon/component_support.h>
#include <libKitsunemimiHanamiCommon/structs.h>
#include <libKitsunemimiHanamiMessaging/hanami_messaging.h>
#include <libKitsunemimiHanamiMessaging/hanami_messaging_client.h>

using Kitsunemimi::Hanami::HanamiMessaging;
using Kitsunemimi::Hanami::HanamiMessagingClient;
using Kitsunemimi::Hanami::SupportedComponents;

namespace Sagiri
{

/**
 * @brief get data-set payload from sagiri
 *
 * @param token token for request
 * @param uuid uuid of the data-set to download
 * @param error reference for error-output
 *
 * @return data-buffer with data if successful, else nullptr
 */
Kitsunemimi::DataBuffer*
getData(const std::string &token,
        const std::string &uuid,
        const std::string &columnName,
        Kitsunemimi::ErrorContainer &error)
{
    Kitsunemimi::Hanami::ResponseMessage response;
    HanamiMessagingClient* client = HanamiMessaging::getInstance()->sagiriClient;

    // build request to get train-data from sagiri
    Kitsunemimi::Hanami::RequestMessage request;
    request.id = "v1/data_set";
    request.httpType = Kitsunemimi::Hanami::GET_TYPE;
    request.inputValues = "{\"token\":\"" + token + "\""
                          ",\"uuid\":\"" + uuid + "\""
                          "}";

    if(client == nullptr) {
        return nullptr;
    }

    // send request to sagiri
    if(client->triggerSakuraFile(response, request, error) == false) {
        return nullptr;
    }

    // check response
    if(response.success == false)
    {
        error.addMeesage(response.responseContent);
        return nullptr;
    }

    // parse result
    Kitsunemimi::Json::JsonItem jsonItem;
    if(jsonItem.parse(response.responseContent, error) == false) {
        return nullptr;
    }

    // create real request
    DatasetRequest_Message msg;
    msg.location = jsonItem.get("location").getString();
    msg.columnName = columnName;
    DataBuffer msgBlob;
    msg.createBlob(msgBlob);

    return client->sendGenericRequest(msgBlob.data, msgBlob.usedBufferSize, error);
}

/**
 * @brief send list with request-results to sagiri
 *
 * @param uuid uuid of the request-task
 * @param results data-array with results
 * @param error reference for error-output
 *
 * @return true, if successful, else false
 */
bool
sendResults(const std::string &uuid,
            const Kitsunemimi::DataArray &results,
            Kitsunemimi::ErrorContainer &error)
{
    HanamiMessagingClient* client = HanamiMessaging::getInstance()->sagiriClient;
    if(client == nullptr) {
        return false;
    }

    ResultPush_Message msg;
    msg.uuid = uuid;
    msg.results = results.toString();
    DataBuffer msgBlob;
    msg.createBlob(msgBlob);

    Kitsunemimi::DataBuffer* ret = client->sendGenericRequest(msgBlob.data,
                                                              msgBlob.usedBufferSize,
                                                              error);
    delete ret;
    return true;
}

/**
 * @brief get information of a specific data-set from sagiri
 *
 * @param result reference for result-output
 * @param dataSetUuid uuid of the requested data-set
 * @param token for authetification against sagiri
 * @param error reference for error-output
 *
 * @return true, if successful, else false
 */
bool
getDataSetInformation(Kitsunemimi::Json::JsonItem &result,
                      const std::string &dataSetUuid,
                      const std::string &token,
                      Kitsunemimi::ErrorContainer &error)
{
    HanamiMessagingClient* client = HanamiMessaging::getInstance()->sagiriClient;
    if(client == nullptr) {
        return false;
    }

    Kitsunemimi::Hanami::ResponseMessage response;

    // create request for remote-calls
    Kitsunemimi::Hanami::RequestMessage request;
    request.id = "v1/data_set";
    request.httpType = Kitsunemimi::Hanami::GET_TYPE;
    request.inputValues = "{\"uuid\" : \"" + dataSetUuid + "\","
                          "\"token\":\"" + token + "\"}";

    // send request to the target
    if(client->triggerSakuraFile(response, request, error) == false) {
        return false;
    }

    // check response
    if(response.success == false)
    {
        error.addMeesage(response.responseContent);
        return false;
    }

    // parse result
    if(result.parse(response.responseContent, error) == false) {
        return false;
    }

    return true;
}

/**
 * @brief send error-message to sagiri
 *
 * @param userUuid uuid of the user where the error belongs to
 * @param errorMessage error-message to send to sagiri
 */
void
sendErrorMessage(const std::string &userUuid,
                 const std::string &errorMessage)
{
    // create message
    Kitsunemimi::ErrorContainer error;
    HanamiMessagingClient* client = HanamiMessaging::getInstance()->sagiriClient;
    if(client == nullptr) {
        return;
    }

    Kitsunemimi::Hanami::ErrorLog_Message msg;
    msg.userUuid = userUuid;
    msg.errorMsg = errorMessage;
    DataBuffer msgBlob;
    msg.createBlob(msgBlob);

    // send
    client->sendGenericMessage(msgBlob.data, msgBlob.usedBufferSize, error);
}

/**
 * @brief send error-message to sagiri
 *
 * @param context context context-object to log
 * @param inputValues inputValues input-values of the request to log
 */
void
sendAuditMessage(const std::string &targetComponent,
                 const std::string &targetEndpoint,
                 const std::string &userUuid,
                 const Kitsunemimi::Hanami::HttpRequestType requestType)
{
    // check if sagiri is supported
    if(SupportedComponents::getInstance()->support[Kitsunemimi::Hanami::SAGIRI] == false) {
        return;
    }

    // convert http-type into string
    std::string httpType = "GET";
    if(requestType == Kitsunemimi::Hanami::DELETE_TYPE) {
        httpType = "DELETE";
    }
    if(requestType == Kitsunemimi::Hanami::GET_TYPE) {
        httpType = "GET";
    }
    if(requestType == Kitsunemimi::Hanami::HEAD_TYPE) {
        httpType = "HEAD";
    }
    if(requestType == Kitsunemimi::Hanami::POST_TYPE) {
        httpType = "POST";
    }
    if(requestType == Kitsunemimi::Hanami::PUT_TYPE) {
        httpType = "PUT";
    }

    // create message
    LOG_DEBUG("process uri: \'" + targetEndpoint + "\' with type '" + httpType + "'");

    // send
    Kitsunemimi::ErrorContainer error;
    HanamiMessagingClient* client = HanamiMessaging::getInstance()->sagiriClient;
    if(client == nullptr) {
        return;
    }

    AuditLog_Message msg;
    msg.userUuid = userUuid;
    msg.type = httpType;
    msg.component = targetComponent;
    msg.endpoint = targetEndpoint;
    DataBuffer msgBlob;
    msg.createBlob(msgBlob);

    if(client->sendGenericMessage(msgBlob.data, msgBlob.usedBufferSize, error) == false) {
        LOG_ERROR(error);
    }
}

}
