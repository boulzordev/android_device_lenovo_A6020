#
# Copyright (C) 2015-2016 The CyanogenMod Project
# Copyright (C) 2017 The LineageOS Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#


# inherit from the proprietary version
-include vendor/lenovo/A6020/BoardConfigVendor.mk

LOCAL_PATH := device/lenovo/A6020

TARGET_SPECIFIC_HEADER_PATH := $(LOCAL_PATH)/include

# Asserts
TARGET_OTA_ASSERT_DEVICE := A6020,A6020a40,A6020a41,A6020a46,A6020l36,A6020l37,K32c36,k5,k5_plus,vibe_k5

include $(LOCAL_PATH)/board/*.mk
