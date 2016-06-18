#
# Copyright (C) 2015 The CyanogenMod Project
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

$(call inherit-product, $(SRC_TARGET_DIR)/product/languages_full.mk)

# The gps config appropriate for this device
$(call inherit-product, device/common/gps/gps_us_supl.mk)


DEVICE_PACKAGE_OVERLAYS += device/lenovo/A6020/overlay


ifeq ($(TARGET_PREBUILT_KERNEL),)
else
	LOCAL_KERNEL := $(TARGET_PREBUILT_KERNEL)
	PRODUCT_COPY_FILES += \
		device/lenovo/A6020/dt.img:dt.img
	PRODUCT_COPY_FILES += \
    	$(LOCAL_KERNEL):kernel
endif

# Overlay
DEVICE_PACKAGE_OVERLAYS += $(LOCAL_PATH)/overlay

# Screen density
PRODUCT_AAPT_CONFIG := normal

$(call inherit-product, frameworks/native/build/phone-xhdpi-1024-dalvik-heap.mk)

# Audio config
PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/audio/audio_platform_info.xml:system/etc/audio_platform_info.xml \
    $(LOCAL_PATH)/audio/mixer_paths.xml:system/etc/mixer_paths.xml

# Audio
PRODUCT_PACKAGES += \
    audiod \
    audio.a2dp.default \
    audio.primary.msm8916 \
    audio.r_submix.default \
    audio.usb.default \
    libaudio-resampler \
    libqcomvisualizer \
    libqcomvoiceprocessing \
    libqcompostprocbundle \
    tinymix

# Media
PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/configs/media_codecs.xml:system/etc/media_codecs.xml \
    $(LOCAL_PATH)/configs/media_codecs_performance.xml:system/etc/media_codecs_performance.xml \
    $(LOCAL_PATH)/configs/media_profiles.xml:system/etc/media_profiles.xml

# Display
PRODUCT_PACKAGES += \
    gralloc.msm8916 \
    copybit.msm8916 \
    hwcomposer.msm8916 \
    memtrack.msm8916


# CM

PRODUCT_PACKAGES += \
	org.cyanogenmod.platform \
	org.cyanogenmod.platform-res

# Ramdisk

PRODUCT_PACKAGES += \
    fstab.qcom \
    ueventd.qcom.rc

# RIL

PRODUCT_PACKAGES += \
    libcnefeatureconfig \
	librmnetctl

# Shim

PRODUCT_PACKAGES += \
	libshim_ril

PRODUCT_BUILD_PROP_OVERRIDES += BUILD_UTC_DATE=0
PRODUCT_NAME := full_A6020
PRODUCT_DEVICE := A6020

$(call inherit-product-if-exists, vendor/lenovo/A6020/A6020-vendor.mk)

$(call inherit-product, $(SRC_TARGET_DIR)/product/full_base_telephony.mk)
$(call inherit-product-if-exists, vendor/cm/config/common_full_phone.mk)
