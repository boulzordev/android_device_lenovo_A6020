LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_SRC_FILES := loader.c
LOCAL_MODULE := benloader

LOCAL_32_BIT_ONLY := true

include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES := init.c
LOCAL_MODULE := bencmdline

LOCAL_32_BIT_ONLY := true

include $(BUILD_EXECUTABLE)
