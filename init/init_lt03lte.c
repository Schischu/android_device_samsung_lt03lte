/*
   Copyright (c) 2013, The Linux Foundation. All rights reserved.

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

#include "vendor_init.h"
#include "property_service.h"
#include "log.h"
#include "util.h"

#include "init_msm.h"

void init_msm_properties(unsigned long msm_id, unsigned long msm_ver, char *board_type)
{
    char platform[PROP_VALUE_MAX];
    char bootloader[PROP_VALUE_MAX];
    char device[PROP_VALUE_MAX];
    char devicename[PROP_VALUE_MAX];
    int rc;

    UNUSED(msm_id);
    UNUSED(msm_ver);
    UNUSED(board_type);

    rc = property_get("ro.board.platform", platform);
    if (!rc || !ISMATCH(platform, ANDROID_TARGET))
        return;

    property_get("ro.bootloader", bootloader);

    if (strstr(bootloader, "P605V")) {
        /* lt03ltevzw */
        cdma_properties("0");
        property_set("ro.build.fingerprint", "samsung/lt03ltevzw/lt03lte:4.4.2/KOT49H/P605VVRUCNC2:user/release-keys");
        property_set("ro.build.description", "hltevzw-user 4.4.2 KOT49H P605VVRUCNC2 release-keys");
        property_set("ro.product.model", "SM-P605V");
        property_set("ro.product.device", "lt03ltevzw");
        property_set("ro.cdma.home.operator.alpha", "Verizon");
        property_set("ro.cdma.home.operator.numeric", "311480");
    } else if (strstr(bootloader, "P605S")) {
        /* lt03ltesks */
        gsm_properties();
        property_set("ro.build.fingerprint", "samsung/lt03ltesks/lt03lte:4.4.2/KOT49H/P605SKSUCND6:user/release-keys");
        property_set("ro.build.description", "hlteusc-user 4.4.2 KOT49H P605SKSUCND6 release-keys");
        property_set("ro.product.model", "SM-P605M");
        property_set("ro.product.device", "lt03ltesks");
    } else if (strstr(bootloader, "P605M")) {
        /* lt03ltecmo */
        gsm_properties();
        property_set("ro.build.fingerprint", "samsung/lt03ltecmo/hlteusc:4.4.2/KOT49H/P605UBUUCND6:user/release-keys");
        property_set("ro.build.description", "hlteusc-user 4.4.2 KOT49H P605UBUUCND6 release-keys");
        property_set("ro.product.model", "SM-P605M");
        property_set("ro.product.device", "lt03ltecmo");
    } else {
        /* lt03ltexx */
        gsm_properties();
        property_set("ro.build.fingerprint", "samsung/lt03ltexx/lt03lte:4.3/KOT49H/P605XXUCNE2:user/release-keys");
        property_set("ro.build.description", "lt03ltexx-user 4.4.2 KOT49H P605XXUCNE2 release-keys");
        property_set("ro.product.model", "SM-P605");
        property_set("ro.product.device", "lt03ltexx");
    }
    property_get("ro.product.device", device);
    strlcpy(devicename, device, sizeof(devicename));
    ERROR("Found bootloader id %s setting build properties for %s device\n", bootloader, devicename);
}

void gsm_properties()
{
    property_set("ro.telephony.default_network", "9");
    property_set("ro.telephony.ril.v3", "newDialCode");
    property_set("telephony.lteOnGsmDevice", "1");
}

void cdma_properties(char cdma_sub[])
{
    property_set("ro.telephony.default_cdma_sub", cdma_sub); // 0: RUIM/SIM  1: NV
    property_set("ro.telephony.default_network", "10");
    property_set("ro.telephony.ril.v3", "newDriverCallU,newDialCode");
    property_set("telephony.lteOnCdmaDevice", "1");
}
