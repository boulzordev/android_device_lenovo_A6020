# Camera
PRODUCT_PACKAGES += \
    camera.msm8916 \
    libbson \
    libshim_gui \
    libshim_atomic \
    libshim_mutexdestroy \
    Snap\

PRODUCT_COPY_FILES += \
     $(LOCAL_PATH)/configs/external_camera_config.xml:system/etc/external_camera_config.xml
