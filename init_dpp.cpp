/*
   Copyright (c) 2017, The Linux Foundation. All rights reserved.
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
#include <sstream>
#include <map>
#include <vector>

#include <sys/stat.h>
#include <sys/mount.h>

#include "vendor_init.h"
#include "property_service.h"
#include "log.h"
#include "util.h"

#include "dpp.h"

using namespace std;

vector<string> split(string string_to_split, char split_char) /* I change this for taking all elements in product.dat @dung11112003*/
{
	vector<string> elements;
	elements.push_back("");
	int i = 0;
	int k = 0;
	int string_length = string_to_split.length() - 1;
	while (i <= string_length)
	{
		if (string_to_split.at(i) != split_char) 
		{
			elements[k] = elements[k] + string_to_split.at(i);
		}
		else
		{
			elements.push_back("");
			k++;
		}
		i++;
	}
	return elements;
}


void ds_properties();

int dpp::mount() {
    int ret = 0;

    if (access(DPP_MOUNTPOINT, F_OK) == -1) {
        ret = make_dir(DPP_MOUNTPOINT, 0400);
        if (ret) {
            if (::mount("", "/", "", MS_REMOUNT, NULL) == 0) {
                ret = make_dir(DPP_MOUNTPOINT, 0400);
                ::mount("", "/", "", MS_REMOUNT|MS_RDONLY, NULL);
            }
        }
    }

    if (!ret) {
        if (::mount(DPP_PARTITION, DPP_MOUNTPOINT, DPP_FS, DPP_FLAGS, DPP_DATA) == 0) {
            return 0;
        }
        else {
            ERROR("Mounting DPP failed\n");
            return -1;
        }
    }
    else {
        ERROR("Cannot create mountpoint for DPP\n");
        return -1;
    }
}

string get_productCode() {		/* This function is changed for taking product codes instead of RM-codes */
    ifstream prod_dat;
    vector<string> parts;
    string productCode;
    if (dpp::mount() == 0) {
        if (access(PRODUCT_DAT, R_OK) == 0) {
            prod_dat.open(PRODUCT_DAT);
            prod_dat >> productCode;
            productCode.erase(productCode.find_last_not_of("\n\r")+1);
            parts = split(productCode, ':');
            if (parts.size() == 6) {
                if (parts.at(0) == "TYPE") {
			return parts[6];
                }
                else {
                    ERROR("This product.dat is strange, TYPE should be the first line\n");
                }
            }
            else {
                ERROR("Invalid product.dat?\n");
            }
            prod_dat.close();
        }
        else {
            ERROR("Cannot access device info\n");
        }
    }
    return "xxxxxx";
}

dpp::device dpp::get_device(string productCode) /* Those product codes were checked many times. If any of those product codes were wrong, pull request or contact @sjrmac or @feherneoh or me to fix */
{	/*Those product codes are used to identity devices instead of RM-codes */
    const string RM_998[] = {"059V2V1", "059V2V2", "059V4T6", "059V4T8", "059V5J7", "059V6D8", "059V6G1", "059V7P2", "059V466", "059V486", "059V535", "059V536", "059V568", "059V570", "059V579"};
    const string RM_997[] = {"059V2V5", "059V444"};
    const string RM_913[] = {"059S0P9", "059S320"};
    const string RM_914[] = {"059R9Z8", "059S083", "059S0G7", "059S0P4", "059S0P5", "059S0P6", "059S0P7", "059S102", "059S107", "059S152", "059S184", "059S1L1", "059S1L2", "059S1L3", "059S1L4", "059S1N6", "059S1T1", "059S1T3", "059S1V5", "059S222", "059S223", "059S224", "059S2F0", "059S2J1", "059S2J2", "059S2J3", "059S2P9", "059S2Q5", "059S2W9", "059S2X0", "059S328", "059S337", "059S341", "059S342", "059S356", "059S357", "059S359", "059S371", "059S372", "059S373", "059S391", "059S393", "059S394", "059S3J0", "059S3J1", "059S3J3", "059S3J4", "059S3J5", "059S3J6", "059S3J7", "059S3J8", "059S3J9", "059S3L1", "059S3L8", "059S3L9", "059S3M0", "059S3M5", "059S3P5", "059S3P6", "059S3P7", "059S3Q0", "059S3R3", "059S3T5", "059S3W7", "059S4B3", "059S4G9", "059S4H0", "059S4S4", "059S4T6", "059S580", "059S583", "059S590", "059S591", "059S5C2", "059S5C6", "059S5C7", "059S5D4", "059S5F7", "059S5F8", "059S5F9", "059S5G0", "059S5J1", "059S5J3", "059S5J9", "059S5K0", "059S5K1", "059S5P0", "059S5V8", "059S5X0", "059S655", 
"059S656", "059S6G9", "059S6H0", "059S6R7", "059S6W9", "059S6X9", "059S722", "059S735", "059S7B9", "059S7D0", "059S7D1", "059S7D2", "059S7G2", "059S7H0", "059S8R3", "059S969", "059S971", "059S9V3", "059S9Z7", "059T107", "059T138", "059T344", "059T345", "059T346", "059T3K1", "059T4C0", "059T610", "059T6F1", "059T766", "059T873", "059V251", "059V393", "059V3R5", "059V420", "059V431", "059V4N0", "059V6S1", "059V7J0", "059V7M8", "059V878"};
    const string RM_915[] = {"059S218", "059S2D1", "059S2D2", "059S2X1", "059S2X9", "059S312", "059S340", "059S343", "059S346", "059S355", "059S3M1", "059S559", "059S560", "059S5B1", "059S5H1", "059S5H3", "059S5H4", "059S5P6", "059S5T2", "059S5T6", "059S5V0", "059S5V2", "059S8H9", "059S8S2", "059S925", "059S9N7", "059T007", "059T037", "059T038", "059T060", "059T0F3", "059T0F6", "059T0F7", "059T0F8", "059T103", "059T104", "059T105", "059T109", "059T110", "059T149", "059T1H1", "059T203", "059T205", "059T277", "059T279", "059T332", "059T333", "059T5C8", "059T5W6", "059T768", "059T7N4", "059V3M8", "059V3S6", "059V448", "059V6X6", "059V7P7"};
    const string RM_917[] = {"059S000", "059S0B4", "059T039"};
    const string RM_885[] = {"059R0Q1", "059S088", "059S0Q0", "059S0S8", "059S0T3", "059S0T4", "059S0T5", "059S0T6", "059S0T9", "059S0V0", "059S0V1", "059S0V2", "059S0V4", "059S0V6", "059S0W0", "059S0W1", "059S0W2", "059S0W4", "059S0W5", "059S1P8", "059S1Q8", "059S1Q9", "059S1R3", "059S1R4", "059S1R7", "059S1S1", "059S1S7", "059S1S8", "059S1S9", "059S1T4", "059S1T6", "059S1T7", "059S1T9", "059S1V0", "059S1V4", "059S1V9", "059S1W1", "059S1W3", "059S1W4", "059S1W5", "059S207", "059S215", "059S216", "059S220", "059S221", "059S2F5", "059S2F6", "059S2F7", "059S2F8", "059S2F9", "059S2T0", "059S2T1", "059S2T2", "059S2T7", "059S2T8", "059S2T9", "059S2V0", "059S2V7", "059S2V9", "059S2W0", "059S2X2", "059S2X5", "059S2X6", "059S2Z5", "059S2Z7", "059S303", "059S304", "059S305", "059S306", "059S307", "059S308", "059S309", "059S310", "059S329", "059S330", "059S331", "059S351", "059S360", "059S361", "059S362", "059S363", "059S366", "059S368", "059S369", "059S370", "059S375", "059S376", "059S377", "059S378", "059S379", 
"059S380", "059S381", "059S382", "059S383", "059S384", "059S385", "059S386", "059S387", "059S388", "059S389", "059S390", "059S3J2", "059S3M6", "059S3M8", "059S3M9", "059S3N2", "059S3N4", "059S3N5", "059S3N7", "059S3N9", "059S3P8", "059S3Q1", "059S3R7", "059S3S8", "059S3T7", "059S3V4", "059S3V5", "059S3V6", "059S3W0", "059S3W8", "059S410", "059S435", "059S458", "059S460", "059S461", "059S462", "059S463", "059S464", "059S465", "059S466", "059S467", "059S468", "059S469", "059S470", "059S471", "059S482", "059S485", "059S488", "059S492", "059S498", "059S499", "059S4B0", "059S4B1", "059S4G8", "059S4H4", "059S4H5", "059S4H6", "059S4L1", "059S4M8", "059S4M9", "059S4N0", "059S4N2", "059S4P4", "059S4Q1", "059S4Q3", "059S4Q4", "059S4Q5", "059S4Q7", "059S4Q8", "059S4Q9", "059S4R1", "059S4R5", "059S4R7", "059S4T2", "059S4T3", "059S4T4", "059S4T5", "059S4T9", "059S4V0", "059S4W3", "059S4W4", "059S4W5", "059S4X4", "059S4X6", "059S4X7", "059S4X8", "059S4Z0", "059S4Z1", "059S4Z3", "059S503", "059S504", "059S505", "059S506", 
"059S507", "059S508", "059S510", "059S534", "059S535", "059S536", "059S593", "059S595", "059S5C3", "059S5C5", "059S5D3", "059S5F0", "059S5F2", "059S5J4", "059S5K4", "059S5N7", "059S5N8", "059S5N9", "059S5P1", "059S5Q8", "059S5T0", "059S5T1", "059S5T4", "059S5T5", "059S5V1", "059S5X1", "059S5Z0", "059S5Z3", "059S5Z7", "059S5Z9", "059S606", "059S610", "059S615", "059S616", "059S625", "059S626", "059S627", "059S628", "059S629", "059S630", "059S631", "059S632", "059S683", "059S684", "059S685", "059S6D6", "059S6D7", "059S6D8", "059S6D9", "059S6F4", "059S6G4", "059S6G5", "059S6G6", "059S6H1", "059S6H5", "059S6J2", "059S6J3", "059S6J4", "059S6J5", "059S6J6", "059S6J7", "059S6J8", "059S6J9", "059S6K0", "059S6K2", "059S6K4", "059S6K6", "059S6K8", "059S6K9", "059S6L0", "059S6L1", "059S6L8", "059S6M6", "059S6P9", "059S6Q1", "059S6Q2", "059S6X1", "059S6X3", "059S704", "059S705", "059S706", "059S707", "059S714", "059S716", "059S739", "059S741", "059S746", "059S7C4", "059S7C8", "059S7C9", "059S7F2", "059S7F3", "059S7G1", 
"059S7G3", "059S7G5", "059S7H1", "059S880", "059S8G4", "059S8G5", "059S8G6", "059S8G7", "059S8G8", "059S8J1", "059S8J7", "059S8J9", "059S8K0", "059S8K1", "059S8K2", "059S8K3", "059S8K4", "059S8S1", "059S915", "059S921", "059S922", "059S930", "059S950", "059S979", "059S980", "059S982", "059S983", "059S9H7", "059T004", "059T022", "059T042", "059T061", "059T062", "059T071", "059T078", "059T0F4", "059T0F5", "059T0P1", "059T100", "059T108", "059T146", "059T1C3", "059T1C4", "059T1D0", "059T1N8", "059T258", "059T2M9", "059T2T1", "059T2W8", "059T2W9", "059T390", "059T392", "059T393", "059T3H9", "059T3J0", "059T3J1", "059T3J2", "059T3J3", "059T3J4", "059T3J5", "059T3J6", "059T3J7", "059T3J8", "059T3J9", "059T3K0", "059T8T1", "059T940", "059V017", "059V020", "059V340", "059V3M1", "059V7J8"};
    const string RM_887[] = {"059S313", "059S315", "059S316", "059S317", "059S318"};
    int i = 0;
    while (i <= 14)
    {
        if (productCode == RM_998[i]) 
        {
            return dpp::device.at("RM-998");
        }
    }
    i = 0;
    while (i <= 1)
    {
        if (productCode == RM_997[i]) 
        {
            return dpp::device.at("RM-997");
        }
    }
    i = 0;
    while (i <= 1)
    {
        if (productCode == RM_913[i]) 
        {
            return dpp::device.at("RM-913");
        }
    }
    i = 0;
    while (i <= 129)
    {
        if (productCode == RM_914[i]) 
        {
            return dpp::device.at("RM-914");
        }
    }
    i = 0;
    while (i <= 55)
    {
        if (productCode == RM_915[i]) 
        {
            return dpp::device.at("RM-915");
        }
    }
    i = 0;
    while (i <= 2)
    {
        if (productCode == RM_917[i]) 
        {
            return dpp::device.at("RM-917");
        }
    }
    i = 0;
    while (i <= 347)
    {
        if (productCode == RM_885[i]) 
        {
            return dpp::device.at("RM-885");
        }
    }
    i = 0;
    while (i <= 4)
    {
        if (productCode == RM_887[i]) 
        {
            return dpp::device.at("RM-887");
        }
    }
    return dpp::unknown;  
}

void ds_properties()
{
    property_set("persist.radio.multisim.config", "dsds");
    property_set("persist.radio.dont_use_dsd", "true");
}

void vendor_load_properties()
{
    string productCode;
    dpp::device dev;
    productCode = get_productCode();
    dev = dpp::get_device(productCode);
    property_set("ro.product.device", dev.device.c_str());
    property_set("ro.product.name",   ("lineage_" + dev.family).c_str());
    property_set("ro.product.model",  dev.description.c_str());
}
