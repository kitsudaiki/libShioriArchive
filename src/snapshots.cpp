/**
 * @file        snapshots.cpp
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

#include <libSagiriArchive/snapshots.h>
#include <libSagiriArchive/sagiri_messages.h>

#include <libKitsunemimiHanamiCommon/component_support.h>
#include <libKitsunemimiHanamiMessaging/hanami_messaging.h>
#include <libKitsunemimiHanamiMessaging/hanami_messaging_client.h>

using Kitsunemimi::Hanami::HanamiMessaging;
using Kitsunemimi::Hanami::HanamiMessagingClient;
using Kitsunemimi::Hanami::SupportedComponents;

namespace Sagiri
{

/**
 * @brief getSnapshotData
 * @param token
 * @param uuid
 * @param error
 * @return
 */
Kitsunemimi::DataBuffer*
getSnapshotData(const std::string &location,
                Kitsunemimi::ErrorContainer &error)
{
    HanamiMessagingClient* client = HanamiMessaging::getInstance()->sagiriClient;

    // create real request
    ClusterSnapshotPull_Message msg;
    msg.location = location;
    DataBuffer msgBlob;
    msg.createBlob(msgBlob);

    return client->sendGenericRequest(msgBlob.data, msgBlob.usedBufferSize, error);
}

/**
 * @brief getSnapshotInformation
 * @param result
 * @param dataSetUuid
 * @param token
 * @param error
 * @return
 */
bool
getSnapshotInformation(Kitsunemimi::Json::JsonItem &result,
                       const std::string &snapshotUuid,
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
    request.id = "v1/cluster_snapshot";
    request.httpType = Kitsunemimi::Hanami::GET_TYPE;
    request.inputValues = "{\"uuid\" : \"" + snapshotUuid + "\","
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

}
