/*
 * Copyright (C) 2018 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#define LOG_TAG "android.hardware.health@2.0-service.msm8953"
#include <android-base/logging.h>

#include <healthd/healthd.h>
#include <health2/Health.h>
#include <health2/service.h>
#include <hidl/HidlTransportSupport.h>

#include <android-base/file.h>
#include <android-base/strings.h>

#include <vector>
#include <string>

using android::hardware::health::V2_0::DiskStats;
using android::hardware::health::V2_0::StorageInfo;

void healthd_board_init(struct healthd_config*) {
}

int healthd_board_battery_update(struct android::BatteryProperties*) {
    // return 0 to log periodic polled battery status to kernel log
    return 1;
}

const char kDiskStatsFile[] = "/sys/block/mmcblk0/stat";
const char kMMCName[] = "MMC0";

void get_storage_info(std::vector<struct StorageInfo>&) {
    // Use defaults.
}

void get_disk_stats(std::vector<DiskStats>& vec_stats) {
    const size_t kDiskStatsSize = 11;
    struct DiskStats stats = {};

    stats.attr.isInternal = true;
    stats.attr.isBootDevice = true;
    stats.attr.name = std::string(kMMCName);


    std::string buffer;
    if (!android::base::ReadFileToString(std::string(kDiskStatsFile), &buffer)) {
        LOG(ERROR) << kDiskStatsFile << ": ReadFileToString failed.";
        return;
    }

    // Regular diskstats entries
    std::stringstream ss(buffer);
    for (uint i = 0; i < kDiskStatsSize; ++i) {
        ss >> *(reinterpret_cast<uint64_t*>(&stats) + i);
    }
    vec_stats.resize(1);
    vec_stats[0] = stats;

    return;
}

int main() { 
	return health_service_main(); 
}
