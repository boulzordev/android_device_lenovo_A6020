# Qualcomm support
BOARD_USES_QCOM_HARDWARE := true

JAVA_SOURCE_OVERLAYS := org.lineageos.hardware|device/lenovo/A6020/lineagehw|**/*.java

# Lineage hardware
BOARD_HARDWARE_CLASS += \
    device/lenovo/A6020/lineagehw
