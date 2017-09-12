# Wifi
PRODUCT_PACKAGES += \
    dhcpcd.conf \
    hostapd_default.conf \
    hostapd \
    wpa_supplicant \
    wpa_supplicant.conf

PRODUCT_PACKAGES += \
    p2p_supplicant_overlay.conf \
    wpa_supplicant_overlay.conf

PRODUCT_PACKAGES += \
    WCNSS_qcom_cfg.ini

PRODUCT_PACKAGES += \
    libqsap_sdk \
    libQWiFiSoftApCfg \
    wificond \
    wcnss_service \
    libwpa_client

# WiFi HAL
PRODUCT_PACKAGES += \
    android.hardware.wifi@1.0-service
