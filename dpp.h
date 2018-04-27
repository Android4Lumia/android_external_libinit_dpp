#include <string>
#include <map>

#define _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#include <sys/_system_properties.h>

#define DPP_PARTITION  "/dev/block/mmcblk0p1"
#define DPP_MOUNTPOINT "/dpp"
#define DPP_FS         "vfat"
#define DPP_FLAGS      MS_RDONLY|MS_NOATIME|MS_NODEV|MS_NODIRATIME|MS_NOEXEC|MS_NOSUID
#define DPP_DATA       "shortname=lower,uid=1000,gid=1000,dmask=227,fmask=337,context=u:object_r:firmware_file:s0"
#define PRODUCT_DAT    "/dpp/Nokia/product.dat"

void property_override(char const prop[], char const value[])
{
    prop_info *pi;

    pi = (prop_info*) __system_property_find(prop);
    if (pi)
        __system_property_update(pi, value, strlen(value));
    else
        __system_property_add(prop, strlen(prop), value, strlen(value));
}

namespace dpp {

    typedef struct device {
        std::string device;
        std::string family;
        std::string description;
    } device;

    int         mount(void);
    dpp::device get_device(void);

    dpp::device unknown = {
        .device = "unknown",
        .family = "unknown",
        .description = "Unknown or not supported device",
    };

    std::map<std::string, dpp::device> devices = {
        {
            "RM-885",
            {
                .device =      "zeal_row",
                .family =      "zeal",
                .description = "Lumia 720 (RM-885)",
            }
        },
        {
            "RM-887",
            {
                .device =      "zeal_cmcc",
                .family =      "zeal",
                .description = "Lumia 720T (RM-887)",
            }
        },
        {
            "RM-913",
            {
                .device =      "fame_cmcc",
                .family =      "fame",
                .description = "Lumia 520 (RM-913)",
            }
        },
        {
            "RM-914",
            {
                .device =      "fame_row",
                .family =      "fame",
                .description = "Lumia 520 (RM-914)",
            }
        },
        {
            "RM-915",
            {
                .device =      "fame_lta",
                .family =      "fame",
                .description = "Lumia 520 (RM-915)",
            }
        },
        {
            "RM-917",
            {
                .device =      "fame_tmo",
                .family =      "fame",
                .description = "Lumia 521 (RM-917)",
            }
        },
        {
            "RM-997",
            {
                .device =      "glee_cmcc",
                .family =      "glee",
                .description = "Lumia 526 (RM-997)",
            }
        },
        {
            "RM-998",
            {
                .device =      "glee_row",
                .family =      "glee",
                .description = "Lumia 525 (RM-998)",
            }
        },
    };

}
