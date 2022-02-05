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

#include <libKitsunemimiCommon/buffer/data_buffer.h>

#include <libKitsunemimiHanamiCommon/structs.h>
#include <libKitsunemimiHanamiMessaging/hanami_messaging.h>

namespace Sagiri
{

/**
 * @brief getData
 * @param token
 * @param uuid
 * @param error
 * @return
 */
Kitsunemimi::DataBuffer*
getData(const std::string &token,
        const std::string &uuid,
        Kitsunemimi::ErrorContainer &error)
{
    Kitsunemimi::Hanami::ResponseMessage response;
    Kitsunemimi::Hanami::HanamiMessaging* msg = Kitsunemimi::Hanami::HanamiMessaging::getInstance();

    // build request to get train-data from sagiri
    Kitsunemimi::Hanami::RequestMessage request;
    request.id = "v1/data_set";
    request.httpType = Kitsunemimi::Hanami::GET_TYPE;
    request.inputValues = "{\"token\":\"" + token + "\""
                          ",\"uuid\":\"" + uuid + "\""
                          "}";

    // send request to sagiri
    if(msg->triggerSakuraFile("sagiri", response, request, error) == false) {
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

    const std::string location = jsonItem.get("location").getString();
    const std::string message = "{\"location\":\"" + location + "\"}";

    return  msg->sendGenericMessage("sagiri", message.c_str(), message.size(), error);
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
    Kitsunemimi::Hanami::HanamiMessaging* msg = Kitsunemimi::Hanami::HanamiMessaging::getInstance();
    Kitsunemimi::Hanami::ResponseMessage response;

    // create request for remote-calls
    Kitsunemimi::Hanami::RequestMessage request;
    request.id = "v1/data_set";
    request.httpType = Kitsunemimi::Hanami::GET_TYPE;
    request.inputValues = "{ \"uuid\" : \"" + dataSetUuid + "\","
                          "\"token\":\"" + token + "\"}";

    // send request to the target
    if(msg->triggerSakuraFile("sagiri", response, request, error) == false) {
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

}
