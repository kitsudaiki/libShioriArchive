/**
 * @file        sagiri_messages.h
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

#ifndef SAGIRIMESSAGES_H
#define SAGIRIMESSAGES_H

#include <libKitsunemimiHanamiMessaging/hanami_messages.h>

using Kitsunemimi::Hanami::HanamiMessage;
using Kitsunemimi::DataBuffer;

namespace Sagiri
{

enum SagiriMessageTypes
{
    UNDEFINED_MESSAGE_TYPE = 0,
    DATASET_REQUEST_MESSAGE_TYPE = 1,
    RESULT_PUSH_MESSAGE_TYPE = 2,
    AUDIT_LOG_MESSAGE_TYPE = 3,
    CLUSTER_SNAPSHOT_PUSH_MESSAGE_TYPE = 4,
    CLUSTER_SNAPSHOT_PULL_MESSAGE_TYPE = 5,
};

//==================================================================================================

class ClusterSnapshotPush_Message
        : public HanamiMessage
{
public:
    ClusterSnapshotPush_Message();
    ~ClusterSnapshotPush_Message();

    std::string uuid = "";
    std::string fileUuid = "";
    void* payload = nullptr;
    uint64_t payloadSize = 0;

    bool read(void* data, const uint64_t dataSize);
    void createBlob(DataBuffer &result);
};

//==================================================================================================

class ClusterSnapshotPull_Message
        : public HanamiMessage
{
public:
    ClusterSnapshotPull_Message();
    ~ClusterSnapshotPull_Message();

    std::string location = "";

    bool read(void* data, const uint64_t dataSize);
    void createBlob(DataBuffer &result);
};

//==================================================================================================

class DatasetRequest_Message
        : public HanamiMessage
{
public:
    DatasetRequest_Message();
    ~DatasetRequest_Message();

    std::string location = "";
    std::string columnName = "";

    bool read(void* data, const uint64_t dataSize);
    void createBlob(DataBuffer &result);
};

//==================================================================================================

class ResultPush_Message
        : public HanamiMessage
{
public:
    ResultPush_Message();
    ~ResultPush_Message();

    std::string uuid = "";
    std::string results;

    bool read(void* data, const uint64_t dataSize);
    void createBlob(DataBuffer &result);
};

//==================================================================================================

class AuditLog_Message
        : public HanamiMessage
{
public:
    AuditLog_Message();
    ~AuditLog_Message();

    std::string userUuid = "";
    std::string component = "";
    std::string endpoint = "";
    std::string type = "";

    bool read(void* data, const uint64_t dataSize);
    void createBlob(DataBuffer &result);
};

//==================================================================================================

}

#endif // SAGIRIMESSAGES_H
