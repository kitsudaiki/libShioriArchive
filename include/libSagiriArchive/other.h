/**
 * @file        other.cpp
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

#ifndef KITSUNEMIMI_HANAMI_SAGIRI_OTHER_H
#define KITSUNEMIMI_HANAMI_SAGIRI_OTHER_H

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

bool sendResults(const std::string &uuid,
                 const std::string &name,
                 const std::string &userId,
                 const std::string &projectId,
                 const Kitsunemimi::DataArray &results,
                 Kitsunemimi::ErrorContainer &error);

void sendErrorMessage(const std::string &userUuid,
                      const std::string &errorMessage);

void sendAuditMessage(const std::string &targetComponent,
                      const std::string &targetEndpoint,
                      const std::string &userUuid,
                      const Kitsunemimi::Hanami::HttpRequestType requestType);

}

#endif // KITSUNEMIMI_HANAMI_SAGIRI_OTHER_H
