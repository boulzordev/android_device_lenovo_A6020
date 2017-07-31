# Screen density
PRODUCT_AAPT_CONFIG := normal
PRODUCT_AAPT_PREF_CONFIG := xxhdpi

# Display
PRODUCT_PACKAGES += \
    gralloc.msm8916 \
    copybit.msm8916 \
    hwcomposer.msm8916 \
    memtrack.msm8916 \
    libgenlock 


# RenderScript HAL
PRODUCT_PACKAGES += \
     android.hardware.renderscript@1.0-impl

PRODUCT_PROPERTY_OVERRIDES += \
    debug.hwui.use_buffer_age=false
