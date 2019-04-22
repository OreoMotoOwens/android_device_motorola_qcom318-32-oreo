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

#include <fstream>
#include <unistd.h>
#include <stdlib.h>

#include <android-base/properties.h>
#define _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#include <sys/_system_properties.h>

#include "property_service.h"
#include "log.h"
#include "util.h"
#include "vendor_init.h"

using android::init::property_set;
using android::base::GetProperty;

void property_override(char const prop[], char const value[])
{
    prop_info *pi;
     pi = (prop_info*) __system_property_find(prop);
    if (pi)
        __system_property_update(pi, value, strlen(value));
    else
        __system_property_add(prop, strlen(prop), value, strlen(value));
}
 void property_override_dual(char const system_prop[],
        char const vendor_prop[], char const value[])
{
    property_override(system_prop, value);
    property_override(vendor_prop, value);
}

void vendor_load_properties()
{

    std::string device = GetProperty("ro.boot.device", "");
    std::string radio = GetProperty("ro.boot.radio", "");
    std::string platform = GetProperty("ro.board.platform", "");
    std::string sku = GetProperty("ro.boot.hardware.sku", "");
    std::string carrier = GetProperty("ro.boot.carrier");

    if (platform != ANDROID_TARGET)
        return;

    property_override("ro.product.model", sku.c_str());
    property_set("ro.hw.device", device.c_str();
    property_set("ro.hw.radio", radio.c_str();

    if (device == "owens") {
        if (radio == "US") {
            if (carrier == "sprint") {
                property_set("ro.build.description","owens_sprint-user 7.1.1 NCR26.58-44 28 release-keys");
                property_set("ro.build.fingerprint","motorola/owens_sprint/owens:7.1.1/NCR26.58-44/28:user/release-keys");
                property_set("ro.mot.build.oem.product","owens_sprint");
                property_set("ro.mot.build.customerid ","sprint");
                property_set("persist.rcs.supported","1");
                property_set("persist.vt.supported","1");
                property_set("persist.eab.supported","1");
                property_set("persist.radio.videopause.mode","1");
                property_set("net.tethering.noprovisioning", "true");
                property_set("tether_dun_required", "0");
            } else {
                property_set("ro.carrier", "retus");
                property_set("ro.mot.build.oem.product","owens");
                property_set("ro.mot.build.customerid","retail");
                property_set("persist.ims.volte","true");
                property_set("persist.ims.vt","false");
                property_set("persist.ims.vt.epdg","false");
                property_set("persist.ims.rcs","false");
                property_set("persist.radio.videopause.mode","0");
                property_set("persist.vt.supported","0");
                property_set("persist.eab.supported","0");
                property_set("persist.rcs.supported","0");
            }
            property_set("ro.radio.imei.sv", "2");
		}
	}
}
