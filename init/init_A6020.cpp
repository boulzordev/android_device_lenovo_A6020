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

void vendor_load_properties()
{
    char platform[PROP_VALUE_MAX];
    char device[PROP_VALUE_MAX];
    char cmdlinebuff[CMDLINE_SIZE];
    char board_id[32];
    FILE *fp;
    int rc;
    rc = property_get("ro.board.platform", platform);

    if (!rc || !ISMATCH(platform, ANDROID_TARGET)) {
        property_set("ro.board_id", "target");
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
        property_set("ro.product.device", "A6020a40");
        property_set("ro.product.model", "Lenovo K5");
        property_set("ro.board_id", board_id);
    } else if (ISMATCH(board_id, "")) {
        property_set("ro.board_id", "empty");
    } else {
        // Default fallback
        property_set("ro.sf.lcd_density", "480");
        property_set("ro.product.device", "A6020");
        property_set("ro.product.model", "Lenovo K5 Fallback");
        property_set("ro.board_id", board_id);
    }

    property_get("ro.product.device", device);
    INFO("Found board id: %s. Setting device to %s\n", board_id, device);
}
