# Copyright 2013 The Android Open Source Project
# Copyright 2015 The CyanogenMod Project

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_SRC_FILES := healthd_board_msm8916.cpp
LOCAL_MODULE := libhealthd.msm8916
LOCAL_C_INCLUDES := system/core/healthd/include
LOCAL_EXPORT_C_INCLUDE_DIRS := system/core/include
LOCAL_CFLAGS := -Werror
include $(BUILD_STATIC_LIBRARY)
