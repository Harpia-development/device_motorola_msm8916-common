/*
 * Copyright (C) 2016 The CyanogenMod Project
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

#include <hardware/power.h>

enum {
    PROFILE_BALANCED = 0,
    PROFILE_MAX
};

typedef struct governor_settings {
    int is_interactive;
    int boost;
    int boostpulse_duration;
    int go_hispeed_load;
    int go_hispeed_load_off;
    int hispeed_freq;
    int hispeed_freq_off;
    int min_sample_time;
    int timer_rate;
    int above_hispeed_delay;
    int target_loads;
    int target_loads_off;
    int scaling_max_freq;
    int scaling_min_freq;
    int scaling_min_freq_off;
    int max_freq_hysteresis;
    int timer_slack;
    int io_is_busy;
    int align_windows;
    int use_migration_notif;
    int use_sched_load;
} power_profile;

// Custom Lineage hints
const static power_hint_t POWER_HINT_SET_PROFILE = (power_hint_t)0x00000111;
