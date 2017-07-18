#include <string>
#include <map>

#define DPP_PARTITION  "/dev/block/mmcblk0p1"
#define DPP_MOUNTPOINT "/dpp"
#define DPP_FS         "vfat"
#define DPP_FLAGS      MS_RDONLY|MS_NOATIME|MS_NODEV|MS_NODIRATIME|MS_NOEXEC|MS_NOSUID
#define DPP_DATA       "shortname=lower,uid=1000,gid=1000,dmask=227,fmask=337,context=u:object_r:firmware_file:s0"
#define PRODUCT_DAT    "/dpp/Nokia/product.dat"

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
            "RM-820",
            {
                .device =      "phi_att",
                .family =      "phi",
                .description = "Lumia 920 (RM-820)",
            }
        },
        // Only released for China Unicom and in Viet Nam
        {
            "RM-821",
            {
                .device =      "phi",
                .family =      "phi",
                .description = "Lumia 920 (RM-821)",
            }
        },
        // Only released for China Unicom
        {
            "RM-822",
            {
                .device =      "phi_hspa",
                .family =      "phi",
                .description = "Lumia 920 (RM-822)",
            }
        },
        {
            "RM-824",
            {
                .device =      "arrow_att",
                .family =      "arrow",
                .description = "Lumia 820 (RM-824)",
            }
        },
        {
            "RM-825",
            {
                .device =      "arrow_row",
                .family =      "arrow",
                .description = "Lumia 820 (RM-825)",
            }
        },
        {
            "RM-826",
            {
                .device =      "arrow_hspa",
                .family =      "arrow",
                .description = "Lumia 820 (RM-826)",
            }
        },
        // Exclusively released for Verizon, an US provider
        {
            "RM-845",
            {
                .device =      "atlas",
                .family =      "arrow",
                .description = "Lumia 822 (RM-845)",
            }
        },
        {
            "RM-846",
            {
                .device =      "sand",
                .family =      "sand",
                .description = "Lumia 620 (RM-846)",
            }
        },
        // Exclusively released for Verizon, an US provider
        {
            "RM-860",
            {
                .device =      "laser",
                .family =      "phi",
                .description = "Lumia 928 (RM-860)",
            }
        },
        {
            "RM-867",
            {
                .device =      "phi_cmcc",
                .family =      "phi",
                .description = "Lumia 920T (RM-867)",
            }
        },
        {
            "RM-875",
            {
                .device =      "eos_row",
                .family =      "eos",
                .description = "Lumia 1020 (RM-875)",
            }
        },
        // Only released for China Unicom
        {
            "RM-876",
            {
                .device =      "eos_hspa",
                .family =      "eos",
                .description = "Lumia 1020 (RM-876)",
            }
        },
        {
            "RM-877",
            {
                .device =      "eos_nam",
                .family =      "eos",
                .description = "Lumia 1020 (RM-877)",
            }
        },
        // No idea about the "real" device codename! Exclusively released for T-Mobile US
        {
            "RM-878",
            {
                .device =      "arrow_tmobile",
                .family =      "arrow",
                .description = "Lumia 810 (RM-878)",
            }
        },
        {
            "RM-885",
            {
                .device =      "zeal_row",
                .family =      "zeal",
                .description = "Lumia 720 (RM-885)",
            }
        },
        // Only released for China Mobile
        {
            "RM-887",
            {
                .device =      "zeal_cmcc",
                .family =      "zeal",
                .description = "Lumia 720T (RM-887)",
            }
        },
        // My device!!! :)
        {
            "RM-892",
            {
                .device =      "catwalk",
                .family =      "catwalk",
                .description = "Lumia 925 (RM-892)",
            }
        },
        {
            "RM-893",
            {
                .device =      "catwalk_americas",
                .family =      "catwalk",
                .description = "Lumia 925 (RM-893)",
            }
        },
        {
            "RM-893",
            {
                .device =      "catwalk_hspa",
                .family =      "catwalk",
                .description = "Lumia 925 (RM-910)",
            }
        },
        // Only released for China Mobile
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
                .device =      "fame",
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
            "RM-941",
            {
                .device =      "max_row",
                .family =      "max",
                .description = "Lumia 625 (RM-941)",
            }
        },
        // Only released in Latin America
        {
            "RM-942",
            {
                .device =      "max_lta",
                .family =      "max",
                .description = "Lumia 625 (RM-942)",
            }
        },
        {
            "RM-943",
            {
                .device =      "max_lta",
                .family =      "max",
                .description = "Lumia 625 (RM-943)",
            }
        },
        // Only released in China
        {
            "RM-955",
            {
                .device =      "catwalk_cmcc",
                .family =      "catwalk",
                .description = "Lumia 925T (RM-955)",
            }
        },
        // The next three devices already have a device tree, but didn't got Android yet
        {
            "RM-994",
            {
                .device =      "batman_row",
                .family =      "batman",
                .description = "Lumia 1320 (RM-994)",
            }
        },
        // Only released in Latin America
        {
            "RM-995",
            {
                .device =      "batman_lta",
                .family =      "batman",
                .description = "Lumia 1320 (RM-995)",
            }
        },
        // Only released in China and Viet Nam
        {
            "RM-995",
            {
                .device =      "batman_hspa",
                .family =      "batman",
                .description = "Lumia 1320 (RM-996)",
            }
        },
        // Only released in China
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
                .device =      "glee",
                .family =      "glee",
                .description = "Lumia 525 (RM-998)",
            }
        },
    };

}
