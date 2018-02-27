# Shims
TARGET_LD_SHIM_LIBS := \
    /system/lib64/libril.so|libshim_ril.so \
    /system/vendor/lib/libmmcamera2_stats_modules.so|libshim_gui.so \
    /system/vendor/lib/libmmcamera2_stats_modules.so|libshim_atomic.so \
    /system/lib/hw/camera.vendor.msm8916.so|libshim_atomic.so \
    /system/lib/libmmjpeg_interface.so|libshim_atomic.so \
    /system/vendor/lib64/libril-qc-qmi-1.so|rild_socket.so \
    /system/vendor/lib/libmmcamera2_imglib_modules.so|libshim_atomic.so

