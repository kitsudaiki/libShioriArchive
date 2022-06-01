/**
 * @file        sagiri_send.h
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

#ifndef KITSUNEMIMI_HANAMI_SAGIRI_SEND_H
#define KITSUNEMIMI_HANAMI_SAGIRI_SEND_H

#include <string>

#include <libKitsunemimiCommon/logger.h>

#include <libKitsunemimiHanamiCommon/enums.h>

namespace Kitsunemimi {
struct DataBuffer;
namespace Json {
class JsonItem;
}
}

namespace Sagiri
{

Kitsunemimi::DataBuffer* getDatasetData(const std::string &token,
                                        const std::string &uuid,
                                        const std::string &columnName,
                                        Kitsunemimi::ErrorContainer &error);
Kitsunemimi::DataBuffer* getSnapshotData(const std::string &location,
                                         Kitsunemimi::ErrorContainer &error);

bool sendResults(const std::string &uuid,
                 const Kitsunemimi::DataArray &results,
                 Kitsunemimi::ErrorContainer &error);

bool getDataSetInformation(Kitsunemimi::Json::JsonItem &result,
                           const std::string &dataSetUuid,
                           const std::string &token,
                           Kitsunemimi::ErrorContainer &error);

bool getSnapshotInformation(Kitsunemimi::Json::JsonItem &result,
                            const std::string &snapshotUuid,
                            const std::string &token,
                            Kitsunemimi::ErrorContainer &error);

void sendAuditMessage(const std::string &targetComponent,
                      const std::string &targetEndpoint,
                      const std::string &userUuid,
                      const Kitsunemimi::Hanami::HttpRequestType requestType);

bool sendClusterSnapshotPushFinish(const std::string &uuid,
                                   const std::string &fileUuid,
                                   Kitsunemimi::ErrorContainer &error);

bool getClusterSnapshot(const std::string &uuid,
                        Kitsunemimi::ErrorContainer &error);
}

#endif // KITSUNEMIMI_HANAMI_SAGIRI_SEND_H
