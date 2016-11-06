# Copyright 2013 The Android Open Source Project

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_SRC_FILES := healthd_board_A6020.cpp
LOCAL_MODULE := libhealthd.A602O
LOCAL_CFLAGS := -Werror
include $(BUILD_STATIC_LIBRARY)

include $(CLEAR_VARS)

LOCAL_SRC_FILES := \
	healthd.cpp \
	healthd_mode_android.cpp \
	healthd_mode_charger.cpp \
	BatteryMonitor.cpp \
	BatteryPropertiesRegistrar.cpp

LOCAL_MODULE := A6020_charger
LOCAL_FORCE_STATIC_EXECUTABLE := true
LOCAL_MODULE_PATH := $(TARGET_ROOT_OUT_SBIN)
LOCAL_UNSTRIPPED_PATH := $(TARGET_ROOT_OUT_SBIN_UNSTRIPPED)

LOCAL_CFLAGS := -D__STDC_LIMIT_MACROS -Werror

HEALTHD_CHARGER_DEFINES := RED_LED_PATH \
    GREEN_LED_PATH \
    BLUE_LED_PATH \
    BACKLIGHT_PATH \
    CHARGING_ENABLED_PATH

$(foreach healthd_charger_define,$(HEALTHD_CHARGER_DEFINES), \
  $(if $($(healthd_charger_define)), \
    $(eval LOCAL_CFLAGS += -D$(healthd_charger_define)=\"$($(healthd_charger_define))\") \
  ) \
)

ifeq ($(strip $(BOARD_CHARGER_DISABLE_INIT_BLANK)),true)
LOCAL_CFLAGS += -DCHARGER_DISABLE_INIT_BLANK
endif

ifeq ($(strip $(BOARD_CHARGER_ENABLE_SUSPEND)),true)
LOCAL_CFLAGS += -DCHARGER_ENABLE_SUSPEND
endif

ifeq ($(strip $(BOARD_NO_CHARGER_LED)),true)
LOCAL_CFLAGS += -DNO_CHARGER_LED
endif

LOCAL_C_INCLUDES := bootable/recovery

LOCAL_STATIC_LIBRARIES := libbatteryservice libbinder libminui libpng libz libutils libstdc++ libcutils liblog libm libc

ifeq ($(strip $(BOARD_CHARGER_ENABLE_SUSPEND)),true)
LOCAL_STATIC_LIBRARIES += libsuspend
endif

LOCAL_HAL_STATIC_LIBRARIES := libhealthd

ifeq ($(BOARD_USES_QCOM_HARDWARE),true)
BOARD_HAL_STATIC_LIBRARIES ?= libhealthd.A602O
endif

include $(BUILD_EXECUTABLE)


define _add-charger-image
include $$(CLEAR_VARS)
LOCAL_MODULE := device_lenovo_A6020_charger_$(notdir $(1))
LOCAL_MODULE_STEM := $(notdir $(1))
_img_modules += $$(LOCAL_MODULE)
LOCAL_SRC_FILES := $1
LOCAL_MODULE_CLASS := ETC
LOCAL_MODULE_PATH := $$(TARGET_ROOT_OUT)/res/images/charger
include $$(BUILD_PREBUILT)
endef

_img_modules :=
IMAGES_DIR := images
_images :=
$(foreach _img, $(call find-subdir-subdir-files, "$(IMAGES_DIR)", "*.png"), \
  $(eval $(call _add-charger-image,$(_img))))

include $(CLEAR_VARS)
LOCAL_MODULE := A6020_charger_res_images
LOCAL_REQUIRED_MODULES := $(_img_modules)
include $(BUILD_PHONY_PACKAGE)

_add-charger-image :=
_img_modules :=
