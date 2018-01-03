/*
   Copyright (c) 2014, The Linux Foundation. All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are
   met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above
      copyright notice, this list of conditions and the following
      disclaimer in the documentation and/or other materials provided
      with the distribution.
    * Neither the name of The Linux Foundation nor the names of its
      contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
   WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
   ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
   BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
   BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
   WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
   OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
   IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdlib.h>
#define _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#include <sys/_system_properties.h>
#include <stdio.h>

#include <android-base/properties.h>
#include "property_service.h"
#include "vendor_init.h"

using android::base::GetProperty;
using android::init::property_set;

#define ISMATCH(a,b)    (!strncmp(a,b,PROP_VALUE_MAX))

#define CMDLINE_SIZE 1024

void property_override(char const prop[], char const value[])
{
    prop_info *pi;

    pi = (prop_info*) __system_property_find(prop);
    if (pi)
        __system_property_update(pi, value, strlen(value));
    else
        __system_property_add(prop, strlen(prop), value, strlen(value));
}

void gsm_properties(bool msim);
void set_model_config(bool plus);

void vendor_load_properties()
{
    std::string platform;
    std::string device;
    char cmdlinebuff[CMDLINE_SIZE];
    char board_id[32];
    char panel_id[32];
    FILE *fp;
    platform = GetProperty("ro.board.platform", "");

    if (platform != ANDROID_TARGET) {
        return;
    }

    if ((fp = fopen("/proc/cmdline", "r")) == NULL) {
        printf("Failed to open /proc/cmdline");
        return;
    }

    if (fgets(cmdlinebuff, CMDLINE_SIZE, fp) == NULL) {
        return;
    }
    char *boardindex = strstr(cmdlinebuff, "board_id=");
    if (boardindex != NULL) {
        strncpy(board_id, strtok(boardindex + 9, ":"), 32);
    }
    char *panelindex = strstr(cmdlinebuff, "panel=");
    if (panelindex != NULL) {
        strncpy(panel_id, strtok(panelindex + 28, ":"), 32);
    }
    fclose(fp);

    if (ISMATCH(board_id, "S82918B1")){
        if (ISMATCH(panel_id, "ili9881c_720p_video") || ISMATCH(panel_id, "hx8394f_boe_720p_video")) {
            property_override("ro.build.product", "A6020a40"); // HW39
            property_override("ro.product.device", "A6020a40");
            property_override("ro.product.model", "A6020a40");
            property_override("ro.build.fingerprint", "Lenovo/A6020a40/A6020a40:5.1.1/LMY47V/A6020a40_S007_161128_ROW:user/release-keys");
            set_model_config(false); // 720p
        } else { // panel_id = "otm1901a_tm_1080p_video" for A6020a46
            property_override("ro.build.product", "A6020a46");
            property_override("ro.product.device", "A6020a46");
            property_override("ro.product.model", "A6020a46");
            property_override("ro.build.fingerprint", "Lenovo/A6020a46/A6020a46:5.1.1/LMY47V/A6020a46_S042_160516_ROW:user/release-keys");
            set_model_config(true); // 1080p
        }
        gsm_properties(true);
    } else if (ISMATCH(board_id, "S82918E1")){
        property_override("ro.build.product", "A6020a41");
        property_override("ro.product.device", "A6020a41");
        property_override("ro.product.model", "A6020a41");
        property_override("ro.build.fingerprint", "Lenovo/A6020a41/A6020a41:5.1.1/LMY47V/A6020a41_S102_161123_ROW:user/release-keys");
        set_model_config(false);
        gsm_properties(false);
    } else if (ISMATCH(board_id, "S82918F1")){
        property_override("ro.build.product", "A6020l36");
        property_override("ro.product.device", "A6020l36");
        property_override("ro.product.model", "A6020l36");
        property_override("ro.build.fingerprint", "Lenovo/A6020l36/A6020l36:5.1.1/LMY47V/A6020l36_S032_160401_LAS:user/release-keys");
        set_model_config(true);
        gsm_properties(true);
    } else if (ISMATCH(board_id, "S82918G1")){
        property_override("ro.build.product", "A6020l37");
        property_override("ro.product.device", "A6020l37");
        property_override("ro.product.model", "A6020l37");
        property_override("ro.build.fingerprint", "Lenovo/A6020l37/A6020l37:5.1.1/LMY47V/A6020l37_S014_160402_LAS:user/release-keys");
        set_model_config(true);
        gsm_properties(false);
    } else if (ISMATCH(board_id, "S82918H1")){
        property_override("ro.build.product", "A6020a46");
        property_override("ro.product.device", "A6020a46");
        property_override("ro.product.model", "A6020a46");
        property_override("ro.build.fingerprint", "Lenovo/A6020a46/A6020a46:5.1.1/LMY47V/A6020a46_S105_161124_ROW:user/release-keys");
        set_model_config(true);
        gsm_properties(true);
    } else {
        // Use A6020a40 as default - board_id = "S82918D1"
        property_override("ro.build.product", "A6020a40");
        property_override("ro.product.device", "A6020a40");
        property_override("ro.product.model", "A6020a40");
        property_override("ro.build.fingerprint", "Lenovo/A6020a40/A6020a40:5.1.1/LMY47V/A6020a40_S102_161123_ROW:user/release-keys");
        set_model_config(false);
        gsm_properties(true);
    }
}

void gsm_properties(bool msim)
{
    if (msim) {
        property_set("persist.radio.multisim.config", "dsds");
        //property_set("ro.telephony.ril.config", "simactivation");
        property_set("ro.telephony.default_network", "9,9");
    } else {
        property_set("persist.radio.multisim.config", "");
        property_set("ro.telephony.default_network", "9");
    }
}

void set_model_config(bool plus){
    if (plus){
        property_set("ro.sf.lcd_density", "480");
        property_override("ro.product.name", "Vibe K5 Plus");

	/* Dalvik properties
         *
         * https://github.com/CyanogenMod/android_frameworks_native/blob/cm-14.1/build/phone-xxhdpi-2048-dalvik-heap.mk
         */
        property_set("dalvik.vm.heapstartsize", "16m");
        property_set("dalvik.vm.heapgrowthlimit", "192m");
        property_set("dalvik.vm.heapsize", "512m");
        property_set("dalvik.vm.heaptargetutilization", "0.75");
        property_set("dalvik.vm.heapminfree", "2m");
        property_set("dalvik.vm.heapmaxfree", "8m");
    } else {
        property_set("ro.sf.lcd_density", "320");
        property_override("ro.product.name", "Vibe K5");

        /* Dalvik properties
         *
         * https://github.com/CyanogenMod/android_frameworks_native/blob/cm-14.1/build/phone-xhdpi-2048-dalvik-heap.mk
         */
        property_set("dalvik.vm.heapstartsize", "8m");
        property_set("dalvik.vm.heapgrowthlimit", "192m");
        property_set("dalvik.vm.heapsize", "512m");
        property_set("dalvik.vm.heaptargetutilization", "0.75");
        property_set("dalvik.vm.heapminfree", "512k");
        property_set("dalvik.vm.heapmaxfree", "8m");
    }
}

