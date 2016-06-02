# Release name
PRODUCT_RELEASE_NAME := A6020a40

# Inherit some common CM stuff.
$(call inherit-product, vendor/cm/config/common_full_phone.mk)

# Inherit device configuration
$(call inherit-product, device/lenovo/A6020a40/device_A6020a40.mk)

## Device identifier. This must come after all inclusions
PRODUCT_DEVICE := A6020a40
PRODUCT_NAME := cm_A6020a40
PRODUCT_BRAND := lenovo
PRODUCT_MODEL := A6020a40
PRODUCT_MANUFACTURER := lenovo
