# Audio config
PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/audio/audio_effects.xml:system/vendor/etc/audio_effects.xml \
    $(LOCAL_PATH)/audio/audio_platform_info.xml:system/etc/audio_platform_info.xml \
    $(LOCAL_PATH)/audio/audio_policy.conf:system/etc/audio_policy.conf \
    $(LOCAL_PATH)/audio/mixer_paths.xml:system/etc/mixer_paths_qrd_skuh.xml \
    $(LOCAL_PATH)/audio/aanc_tuning_mixer.txt:system/etc/aanc_tuning_mixer.txt \

# Audio
PRODUCT_PACKAGES += \
    audio.primary.msm8916 \
    audio.r_submix.default \
    audio.usb.default \
    libaudio-resampler \
    libqcomvisualizer \
    libqcomvoiceprocessing \
    libqcomvoiceprocessingdescriptors \
    libqcompostprocbundle \
    tinymix \
    audio.a2dp.default \
