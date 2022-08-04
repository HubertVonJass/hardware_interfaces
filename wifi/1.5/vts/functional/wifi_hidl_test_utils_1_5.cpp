/*
 * Copyright (C) 2021 The Android Open Source Project
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

#include <VtsHalHidlTargetCallbackBase.h>
#include <android-base/logging.h>

#undef NAN  // NAN is defined in bionic/libc/include/math.h:38

#include <android/hardware/wifi/1.5/IWifi.h>
#include <android/hardware/wifi/1.5/IWifiApIface.h>
#include <android/hardware/wifi/1.5/IWifiChip.h>
#include <gtest/gtest.h>
#include <hidl/GtestPrinter.h>
#include <hidl/ServiceManagement.h>

#include "wifi_hidl_call_util.h"
#include "wifi_hidl_test_utils.h"

using ::android::sp;
using ::android::hardware::hidl_string;
using ::android::hardware::hidl_vec;
using ::android::hardware::Return;
using ::android::hardware::Void;
using ::android::hardware::wifi::V1_0::ChipModeId;
using ::android::hardware::wifi::V1_0::IfaceType;
using ::android::hardware::wifi::V1_5::IWifiApIface;
using ::android::hardware::wifi::V1_5::IWifiChip;

sp<IWifiChip> getWifiChip_1_5(const std::string& instance_name) {
    return IWifiChip::castFrom(getWifiChip(instance_name));
}

sp<IWifiApIface> getWifiApIface_1_5(const std::string& instance_name) {
    ChipModeId mode_id;
    sp<IWifiChip> wifi_chip_ = getWifiChip_1_5(instance_name);
    configureChipToSupportIfaceType(wifi_chip_, IfaceType::AP, &mode_id);
    const auto& status_and_iface = HIDL_INVOKE(wifi_chip_, createApIface);
    return IWifiApIface::castFrom(status_and_iface.second);
}

sp<IWifiApIface> getBridgedWifiApIface_1_5(const std::string& instance_name) {
    ChipModeId mode_id;
    sp<IWifiChip> wifi_chip_ = getWifiChip_1_5(instance_name);
    configureChipToSupportIfaceType(wifi_chip_, IfaceType::AP, &mode_id);
    const auto& status_and_iface =
        HIDL_INVOKE(wifi_chip_, createBridgedApIface);
    return IWifiApIface::castFrom(status_and_iface.second);
}
