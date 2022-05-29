/**
 * @file        hanami_messages_test.cpp
 *
 * @author      Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 * @copyright   Apache License Version 2.0
 *
 *      Copyright 2020 Tobias Anker
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

#include "sagiri_messages_test.h"

#include <libSagiriArchive/sagiri_messages.h>
#include <libKitsunemimiCommon/buffer/data_buffer.h>

namespace Sagiri
{

HanamiMessages_Test::HanamiMessages_Test()
    : Kitsunemimi::CompareTestHelper("HanamiMessages_Test")
{
    clusterSnapshot_test();
}

/**
 * @brief clusterSnapshot_test
 */
void
HanamiMessages_Test::clusterSnapshot_test()
{
    ClusterSnapshotPush_Message sourceMessage;

    sourceMessage.uuid = "asdf";
    sourceMessage.fileUuid = "poi";
    sourceMessage.payload = new uint8_t[10];
    sourceMessage.payloadSize = 5;
    strncpy(static_cast<char*>(sourceMessage.payload), "12345", 5);

    Kitsunemimi::DataBuffer result;
    sourceMessage.createBlob(result);

    ClusterSnapshotPush_Message targetMessage;
    TEST_EQUAL(targetMessage.read(result.data, result.usedBufferSize), true);

    TEST_EQUAL(targetMessage.uuid, sourceMessage.uuid);
    TEST_EQUAL(targetMessage.fileUuid, sourceMessage.fileUuid);

    const int compareRet = memcmp(targetMessage.payload,
                                  sourceMessage.payload,
                                  sourceMessage.payloadSize);
    TEST_EQUAL(compareRet, 0);
}

}  // namespace Sagiri
