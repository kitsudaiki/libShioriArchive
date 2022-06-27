/**
 * @file        snapshots.h
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

#ifndef KITSUNEMIMI_HANAMI_SAGIRI_SNAPSHOTS_H
#define KITSUNEMIMI_HANAMI_SAGIRI_SNAPSHOTS_H

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

Kitsunemimi::DataBuffer* getSnapshotData(const std::string &location,
                                         Kitsunemimi::ErrorContainer &error);

bool getSnapshotInformation(Kitsunemimi::Json::JsonItem &result,
                            const std::string &snapshotUuid,
                            const std::string &token,
                            Kitsunemimi::ErrorContainer &error);

bool runInitProcess(std::string &fileUuid,
                    const std::string &snapshotUuid,
                    const std::string &snapshotName,
                    const std::string &userUuid,
                    const std::string &projectUuid,
                    const uint64_t totalSize,
                    const std::string &headerMessage,
                    const std::string &token,
                    Kitsunemimi::ErrorContainer &error);

bool sendData(const Kitsunemimi::DataBuffer* data,
              uint64_t &targetPos,
              const std::string &uuid,
              const std::string &fileUuid,
              Kitsunemimi::ErrorContainer &error);

bool runFinalizeProcess(const std::string &snapshotUuid,
                        const std::string &fileUuid,
                        const std::string &token,
                        const std::string &userUuid,
                        const std::string &projectUuid,
                        Kitsunemimi::ErrorContainer &error);
}

#endif // KITSUNEMIMI_HANAMI_SAGIRI_SNAPSHOTS_H
