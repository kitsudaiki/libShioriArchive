/**
 * @file        sagiri_messages.cpp
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

#include <libSagiriArchive/sagiri_messages.h>

namespace Sagiri
{

//==================================================================================================

/**
 * @brief constructor
 */
ClusterSnapshotPush_Message::ClusterSnapshotPush_Message()
    : HanamiMessage()
{
    m_type = CLUSTER_SNAPSHOT_PUSH_MESSAGE_TYPE;
}

/**
 * @brief destructor
 */
ClusterSnapshotPush_Message::~ClusterSnapshotPush_Message() {}

/**
 * @brief read message from bytes
 *
 * @param data data-pointer to read
 * @param dataSize number of bytes to read
 *
 * @return false, if message is broken, else true
 */
bool
ClusterSnapshotPush_Message::read(const void* data, const uint64_t dataSize)
{
    if(initRead(data, dataSize) == false) {
        return false;
    }

    if(readString(data, uuid) == false) {
        return false;
    }
    if(readString(data, fileUuid) == false) {
        return false;
    }
    if(readBinary(data, this->data) == false) {
        return false;
    }

    return true;
}

/**
 * @brief convert message content into binary to send
 *
 * @param result data-buffer for the resulting binary
 */
void
ClusterSnapshotPush_Message::createBlob(DataBuffer &result)
{
    const uint64_t totalMsgSize = sizeof(MessageHeader)
                                  + 3 * sizeof(Entry)
                                  + uuid.size()
                                  + fileUuid.size()
                                  + data.usedBufferSize;

    initBlob(result, totalMsgSize);
    appendString(result, uuid);
    appendString(result, fileUuid);
    appendData(result, data);
}

//==================================================================================================

/**
 * @brief constructor
 */
ClusterSnapshotPull_Message::ClusterSnapshotPull_Message()
{
    m_type = CLUSTER_SNAPSHOT_PULL_MESSAGE_TYPE;
}

/**
 * @brief destructor
 */
ClusterSnapshotPull_Message::~ClusterSnapshotPull_Message() {}

/**
 * @brief read message from bytes
 *
 * @param data data-pointer to read
 * @param dataSize number of bytes to read
 *
 * @return false, if message is broken, else true
 */
bool
ClusterSnapshotPull_Message::read(const void* data, const uint64_t dataSize)
{
    if(initRead(data, dataSize) == false) {
        return false;
    }

    if(readString(data, uuid) == false) {
        return false;
    }

    return true;
}

/**
 * @brief convert message content into binary to send
 *
 * @param result data-buffer for the resulting binary
 */
void
ClusterSnapshotPull_Message::createBlob(Kitsunemimi::DataBuffer &result)
{
    const uint64_t totalMsgSize = sizeof(MessageHeader)
                                  + 1 * sizeof(Entry)
                                  + uuid.size();

    initBlob(result, totalMsgSize);
    appendString(result, uuid);
}

//==================================================================================================

/**
 * @brief constructor
 */
DatasetRequest_Message::DatasetRequest_Message()
{
    m_type = DATASET_REQUEST_MESSAGE_TYPE;
}

/**
 * @brief destructor
 */
DatasetRequest_Message::~DatasetRequest_Message() {}

/**
 * @brief read message from bytes
 *
 * @param data data-pointer to read
 * @param dataSize number of bytes to read
 *
 * @return false, if message is broken, else true
 */
bool
DatasetRequest_Message::read(const void* data, const uint64_t dataSize)
{
    if(initRead(data, dataSize) == false) {
        return false;
    }

    if(readString(data, location) == false) {
        return false;
    }
    if(readString(data, columnName) == false) {
        return false;
    }

    return true;
}

/**
 * @brief convert message content into binary to send
 *
 * @param result data-buffer for the resulting binary
 */
void
DatasetRequest_Message::createBlob(DataBuffer &result)
{
    const uint64_t totalMsgSize = sizeof(MessageHeader)
                                  + 2 * sizeof(Entry)
                                  + location.size()
                                  + columnName.size();

    initBlob(result, totalMsgSize);
    appendString(result, location);
    appendString(result, columnName);
}

//==================================================================================================

/**
 * @brief constructor
 */
ResultPush_Message::ResultPush_Message()
{
    m_type = RESULT_PUSH_MESSAGE_TYPE;
}

/**
 * @brief destructor
 */
ResultPush_Message::~ResultPush_Message() {}

/**
 * @brief read message from bytes
 *
 * @param data data-pointer to read
 * @param dataSize number of bytes to read
 *
 * @return false, if message is broken, else true
 */
bool
ResultPush_Message::read(const void* data, const uint64_t dataSize)
{
    if(initRead(data, dataSize) == false) {
        return false;
    }

    if(readString(data, uuid) == false) {
        return false;
    }
    if(readString(data, results) == false) {
        return false;
    }

    return true;
}

/**
 * @brief convert message content into binary to send
 *
 * @param result data-buffer for the resulting binary
 */
void
ResultPush_Message::createBlob(DataBuffer &result)
{
    const uint64_t totalMsgSize = sizeof(MessageHeader)
                                  + 2 * sizeof(Entry)
                                  + uuid.size()
                                  + results.size();

    initBlob(result, totalMsgSize);
    appendString(result, uuid);
    appendString(result, results);
}

//==================================================================================================

/**
 * @brief constructor
 */
AuditLog_Message::AuditLog_Message()
{
    m_type = AUDIT_LOG_MESSAGE_TYPE;
}

/**
 * @brief destructor
 */
AuditLog_Message::~AuditLog_Message() {}

/**
 * @brief read message from bytes
 *
 * @param data data-pointer to read
 * @param dataSize number of bytes to read
 *
 * @return false, if message is broken, else true
 */
bool
AuditLog_Message::read(const void* data, const uint64_t dataSize)
{
    if(initRead(data, dataSize) == false) {
        return false;
    }

    if(readString(data, userUuid) == false) {
        return false;
    }
    if(readString(data, component) == false) {
        return false;
    }
    if(readString(data, endpoint) == false) {
        return false;
    }
    if(readString(data, type) == false) {
        return false;
    }

    return true;
}

/**
 * @brief convert message content into binary to send
 *
 * @param result data-buffer for the resulting binary
 */
void
AuditLog_Message::createBlob(DataBuffer &result)
{
    const uint64_t totalMsgSize = sizeof(MessageHeader)
                                  + 4 * sizeof(Entry)
                                  + userUuid.size()
                                  + component.size()
                                  + endpoint.size()
                                  + type.size();

    initBlob(result, totalMsgSize);
    appendString(result, userUuid);
    appendString(result, component);
    appendString(result, endpoint);
    appendString(result, type);
}

//==================================================================================================

}
