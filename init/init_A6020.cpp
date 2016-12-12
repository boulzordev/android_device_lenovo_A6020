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
#include <stdio.h>

#include "vendor_init.h"
#include "property_service.h"
#include "log.h"
#include "util.h"

#define ISMATCH(a,b)    (!strncmp(a,b,PROP_VALUE_MAX))

#define CMDLINE_SIZE 1024 

void gsm_properties(bool msim);
void set_heap_hwui_config(bool plus);

void vendor_load_properties()
{
    std::string platform;
    std::string device;
    char cmdlinebuff[CMDLINE_SIZE];
    char board_id[32];
    FILE *fp;
    platform = property_get("ro.board.platform");

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
    fclose(fp);

    if (ISMATCH(board_id, "S82918D1")) {
        property_set("ro.sf.lcd_density", "320");
        property_set("ro.product.variant", "A6020a40");
        property_set("ro.product.model", "Lenovo K5");
        property_set("ro.board_id", board_id);
        set_heap_hwui_config(false);
        gsm_properties(true);
    } else if (ISMATCH(board_id, "S82918G1")){
        property_set("ro.sf.lcd_density", "480");
        property_set("ro.product.variant", "A6020l37");
        property_set("ro.product.model", "Lenovo K5 Plus");
        property_set("ro.board_id", board_id);
        set_heap_hwui_config(true);
        gsm_properties(false);
    } else if (ISMATCH(board_id, "S82918B1")){
        property_set("ro.sf.lcd_density", "480");
        property_set("ro.product.variant", "A6020a46");
        property_set("ro.product.model", "Lenovo K5 Plus");
        property_set("ro.board_id", board_id);
        set_heap_hwui_config(true);
        gsm_properties(true);
    } else if (ISMATCH(board_id, "S82918H1")){
        property_set("ro.sf.lcd_density", "480");
        property_set("ro.product.variant", "A6020a46");
        property_set("ro.product.model", "Lenovo K5 Plus");
        property_set("ro.board_id", board_id);
        set_heap_hwui_config(true);
        gsm_properties(true);
    } else if (ISMATCH(board_id, "S82918F1")){
        property_set("ro.sf.lcd_density", "480");
        property_set("ro.product.variant", "A6020l36");
        property_set("ro.product.model", "Lenovo K5 Plus");
        property_set("ro.board_id", board_id);
        set_heap_hwui_config(true);
        gsm_properties(true);
    } else if (ISMATCH(board_id, "S82918E1")){
        property_set("ro.sf.lcd_density", "320");
        property_set("ro.product.variant", "A6020a41");
        property_set("ro.product.model", "Lenovo K5");
        property_set("ro.board_id", board_id);
        set_heap_hwui_config(false);
        gsm_properties(false);
    } else if (ISMATCH(board_id, "")) {
        property_set("ro.board_id", "default");
        property_set("ro.product.device", "default");
        set_heap_hwui_config(true);
    } else {
        // Default fallback
        property_set("ro.sf.lcd_density", "480");
        property_set("ro.product.variant", "A6020");
        property_set("ro.product.model", "Lenovo K5 Fallback");
        property_set("ro.board_id", "default");
        set_heap_hwui_config(true);
        gsm_properties(true);
    }
    property_set("ro.product.ota.model", property_get("ro.product.model").c_str());

    device = property_get("ro.product.variant");
    //Force device to variant if not set
    property_set("ro.product.device", device.c_str());

    INFO("Found board id: %s. Setting device to %s\n", board_id, device.c_str());
}

void gsm_properties(bool msim)
{
    /* System prop to turn on CdmaLTEPhone always */
    property_set("telephony.lteOnCdmaDevice", "0");
    property_set("ro.telephony.default_network", "9");
    if (msim) {
        property_set("persist.radio.multisim.config", "dsds");
        property_set("ro.telephony.ril.config", "simactivation");
    } else {
        property_set("persist.radio.multisim.config", "");
    }
}

void set_heap_hwui_config(bool plus){
    if (plus){
        /*
         * https://github.com/CyanogenMod/android_frameworks_native/blob/cm-14.1/build/phone-xxhdpi-2048-dalvik-heap.mk
         * https://github.com/CyanogenMod/android_frameworks_native/blob/cm-14.1/build/phone-xxhdpi-2048-hwui-memory.mk
         */
        property_set("ro.hwui.texture_cache_size", "72");
        property_set("ro.hwui.layer_cache_size", "48");
        property_set("ro.hwui.r_buffer_cache_size", "8");
        property_set("ro.hwui.path_cache_size", "32");
        property_set("ro.hwui.gradient_cache_size", "1");
        property_set("ro.hwui.drop_shadow_cache_size", "6");
        property_set("ro.hwui.texture_cache_flushrate", "0.4");
        property_set("ro.hwui.text_small_cache_width", "1024");
        property_set("ro.hwui.text_small_cache_height", "1024");
        property_set("ro.hwui.text_large_cache_width", "2048");
        property_set("ro.hwui.text_large_cache_height", "1024");
        property_set("dalvik.vm.heapstartsize", "16m");
        property_set("dalvik.vm.heapgrowthlimit", "192m");
        property_set("dalvik.vm.heapsize", "512m");
        property_set("dalvik.vm.heaptargetutilization", "0.75");
        property_set("dalvik.vm.heapminfree", "2m");
        property_set("dalvik.vm.heapmaxfree", "8m");
    } else {
        property_set("ro.hwui.text_large_cache_height", "2048");
        property_set("ro.hwui.texture_cache_size", "40");
        property_set("dalvik.vm.heapstartsize", "8m");
        property_set("dalvik.vm.heapgrowthlimit", "96m");
        property_set("dalvik.vm.heapsize", "256m");
        property_set("dalvik.vm.heaptargetutilization", "0.75");
        property_set("dalvik.vm.heapminfree", "2m");
        property_set("dalvik.vm.heapmaxfree", "8m");
    }
}
