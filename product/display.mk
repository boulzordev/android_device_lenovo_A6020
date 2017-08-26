# Screen density
PRODUCT_AAPT_CONFIG := normal
PRODUCT_AAPT_PREF_CONFIG := xxhdpi

# Display
PRODUCT_PACKAGES += \
    android.hardware.graphics.allocator@2.0-impl \
    android.hardware.graphics.allocator@2.0-service \
    android.hardware.graphics.composer@2.1-impl \
    android.hardware.graphics.mapper@2.0-impl \
    android.hardware.memtrack@1.0-impl \
    gralloc.msm8916 \
    copybit.msm8916 \
    hwcomposer.msm8916 \
    memtrack.msm8916 \
    libgenlock 


# RenderScript HAL
PRODUCT_PACKAGES += \
     android.hardware.renderscript@1.0-impl
