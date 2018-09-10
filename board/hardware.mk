# Qualcomm support
BOARD_USES_QCOM_HARDWARE := true

JAVA_SOURCE_OVERLAYS := org.lineageos.hardware|device/lenovo/A6020/lineagehw|**/*.java

#DoubleTapToWake support
TARGET_TAP_TO_WAKE_NODE := "/sys/android_touch/doubletap2wake"

