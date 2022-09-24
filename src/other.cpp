/**
 * @file        other.h
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

#include <libShioriArchive/other.h>
#include <libShioriArchive/shiori_messages.h>

#include <libKitsunemimiCommon/buffer/data_buffer.h>
#include <libKitsunemimiCrypto/common.h>

#include <libKitsunemimiHanamiCommon/component_support.h>
#include <libKitsunemimiHanamiCommon/structs.h>
#include <libKitsunemimiHanamiNetwork/hanami_messaging.h>
#include <libKitsunemimiHanamiNetwork/hanami_messaging_client.h>

using Kitsunemimi::Hanami::HanamiMessaging;
using Kitsunemimi::Hanami::HanamiMessagingClient;
using Kitsunemimi::Hanami::SupportedComponents;

namespace Shiori
{

/**
 * @brief send list with request-results to shiori
 *
 * @param uuid uuid of the request-task
 * @param name name of the request-task
 * @param results data-array with results
 * @param error reference for error-output
 *
 * @return true, if successful, else false
 */
bool
sendResults(const std::string &uuid,
            const std::string &name,
            const std::string &userId,
            const std::string &projectId,
            const Kitsunemimi::DataArray &results,
            Kitsunemimi::ErrorContainer &error)
{
    HanamiMessagingClient* client = HanamiMessaging::getInstance()->shioriClient;
    if(client == nullptr) {
        return false;
    }

    // fill message
    ResultPush_Message msg;
    msg.uuid = uuid;
    msg.name = name;
    msg.userId = userId;
    msg.projectId = projectId;
    msg.results = results.toString();

    // TODO: variable size
    uint8_t buffer[1024*1024];
    const uint64_t size = msg.createBlob(buffer, 1024*1024);

    Kitsunemimi::DataBuffer* ret = client->sendGenericRequest(buffer, size, error);
    delete ret;

    return true;
}

/**
 * @brief send error-message to shiori
 *
 * @param userId id of the user where the error belongs to
 * @param errorMessage error-message to send to shiori
 */
void
sendErrorMessage(const std::string &userId,
                 const std::string &errorMessage)
{
    // create message
    Kitsunemimi::ErrorContainer error;
    HanamiMessagingClient* client = HanamiMessaging::getInstance()->shioriClient;
    if(client == nullptr) {
        return;
    }

    Kitsunemimi::Hanami::ErrorLog_Message msg;
    msg.userId = userId;
    msg.errorMsg = errorMessage;
    uint8_t buffer[96*1024];
    const uint64_t size = msg.createBlob(buffer, 96*1024);

    // send
    client->sendGenericMessage(buffer, size, error);
}

/**
 * @brief send audit-log-entry to shiori
 *
 * @param targetComponent accessed component
 * @param targetEndpoint accessed endpoint
 * @param userId user-id who made the request to the endpoint
 * @param requestType http-type of the request
 */
void
sendAuditMessage(const std::string &targetComponent,
                 const std::string &targetEndpoint,
                 const std::string &userId,
                 const Kitsunemimi::Hanami::HttpRequestType requestType)
{
    // check if shiori is supported
    if(SupportedComponents::getInstance()->support[Kitsunemimi::Hanami::SHIORI] == false) {
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
    HanamiMessagingClient* client = HanamiMessaging::getInstance()->shioriClient;
    if(client == nullptr) {
        return;
    }

    AuditLog_Message msg;
    msg.userId = userId;
    msg.type = httpType;
    msg.component = targetComponent;
    msg.endpoint = targetEndpoint;
    uint8_t buffer[96*1024];
    const uint64_t size = msg.createBlob(buffer, 96*1024);

    if(client->sendGenericMessage(buffer, size, error) == false) {
        LOG_ERROR(error);
    }
}

}
