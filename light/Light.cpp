/*
 * Copyright (C) 2018-2019 The LineageOS Project
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

#define LOG_TAG "LightService"

#include "Light.h"

#include <android-base/logging.h>

namespace {
using android::hardware::light::V2_0::LightState;

static constexpr int DEFAULT_MAX_BRIGHTNESS = 255;

static uint32_t rgbToBrightness(const LightState& state) {
    uint32_t color = state.color & 0x00ffffff;
    return ((77 * ((color >> 16) & 0xff)) + (150 * ((color >> 8) & 0xff)) +
            (29 * (color & 0xff))) >> 8;
}

static bool isLit(const LightState& state) {
    return (state.color & 0x00ffffff);
}
}  // anonymous namespace

namespace android {
namespace hardware {
namespace light {
namespace V2_0 {
namespace implementation {

Light::Light(std::pair<std::ofstream, uint32_t>&& lcd_backlight,
             std::ofstream&& blinking_led, std::ofstream&& blinking_led_on_ms, std::ofstream&& blinking_led_off_ms)
    : mLcdBacklight(std::move(lcd_backlight)),
      mBlinkingLed(std::move(blinking_led)),
      mBlinkingLedOnMs(std::move(blinking_led_on_ms)),
      mBlinkingLedOffMs(std::move(blinking_led_off_ms)) {
    auto backlightFn(std::bind(&Light::setLcdBacklight, this, std::placeholders::_1));
    mLights.emplace(std::make_pair(Type::BACKLIGHT, backlightFn));

    if (mBlinkingLed) {
        auto attnFn(std::bind(&Light::setAttentionLight, this, std::placeholders::_1));
        auto notifFn(std::bind(&Light::setNotificationLight, this, std::placeholders::_1));
        mLights.emplace(std::make_pair(Type::ATTENTION, attnFn));
        mLights.emplace(std::make_pair(Type::NOTIFICATIONS, notifFn));
    }
}

// Methods from ::android::hardware::light::V2_0::ILight follow.
Return<Status> Light::setLight(Type type, const LightState& state) {
    auto it = mLights.find(type);

    if (it == mLights.end()) {
        return Status::LIGHT_NOT_SUPPORTED;
    }

    it->second(state);

    return Status::SUCCESS;
}

Return<void> Light::getSupportedTypes(getSupportedTypes_cb _hidl_cb) {
    std::vector<Type> types;

    for (auto const& light : mLights) {
        types.push_back(light.first);
    }

    _hidl_cb(types);

    return Void();
}

void Light::setLcdBacklight(const LightState& state) {
    std::lock_guard<std::mutex> lock(mLock);

    uint32_t brightness = rgbToBrightness(state);

    // If max panel brightness is not the default (255),
    // apply linear scaling across the accepted range.
    if (mLcdBacklight.second != DEFAULT_MAX_BRIGHTNESS) {
        int old_brightness = brightness;
        brightness = brightness * mLcdBacklight.second / DEFAULT_MAX_BRIGHTNESS;
        LOG(VERBOSE) << "scaling brightness " << old_brightness << " => " << brightness;
    }

    mLcdBacklight.first << brightness << std::endl;
}

void Light::setAttentionLight(const LightState& state) {
    std::lock_guard<std::mutex> lock(mLock);
    mAttentionState = state;
    setSpeakerLightLocked();
}

void Light::setNotificationLight(const LightState& state) {
    std::lock_guard<std::mutex> lock(mLock);
    mNotificationState = state;
    setSpeakerLightLocked();
}

void Light::setSpeakerLightLocked() {
    if (mBlinkingLed) {
        if (isLit(mNotificationState)) {
            int onMs, offMs;

            switch (mNotificationState.flashMode) {
                case Flash::TIMED:
                    onMs              =  mNotificationState.flashOnMs;
                    offMs             =  mNotificationState.flashOffMs;
                    mBlinkingLed      << "timer" << std::endl;
                    mBlinkingLedOnMs  << onMs    << std::endl;
                    mBlinkingLedOffMs << offMs   << std::endl;
                    break;
                case Flash::NONE:
                    mBlinkingLed      << "none" << std::endl;
                    break;
                default:
                    onMs              =  500;
                    offMs             =  750;
                    mBlinkingLed      << "timer" << std::endl;
                    mBlinkingLedOnMs  << onMs    << std::endl;
                    mBlinkingLedOffMs << offMs   << std::endl;
                    break;
            }

        } else {
                    mBlinkingLed          << "none"  << std::endl;
        }
    }
}

}  // namespace implementation
}  // namespace V2_0
}  // namespace light
}  // namespace hardware
}  // namespace android
