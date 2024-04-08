// Settings.cc

// Store settings in NV flash using the `settings` Zephyr module
#include "Settings.h"
#include "Z9Lock_status.h"          // update "paired" mode
#include "Z9Crypto_gcm.h"

#include <zephyr/device.h>
#include <zephyr/drivers/flash.h>
#include <zephyr/storage/flash_map.h>
#include <zephyr/fs/nvs.h>

#define NVS_PARTITION		storage_partition
#define NVS_PARTITION_DEVICE	FIXED_PARTITION_DEVICE(NVS_PARTITION)
#define NVS_PARTITION_OFFSET	FIXED_PARTITION_OFFSET(NVS_PARTITION)
#define NVS_PARTITION_ID        FIXED_PARTITION_ID(NVS_PARTITION)


//#ifdef CONFIG_Z9_CONTROLLER
// flash memory keys & backing store
static struct nvs_fs fs;

uint8_t lock_public_key[65];
uint8_t noc_public_key[65];
uint8_t noc_derived_key[16];

// key handles for PSA
gcm_key_id_t noc_key_handle;
#ifdef CONFIG_Z9_CONTROLLER
void nvm_settings_reset()
{
    nvs_clear(&fs);

    // not really needed -- processor reset occurs next
    void nvm_settings_set_mode();
}

/* define the nvs file system by settings with:
 *	sector_size equal to the pagesize,
 *	3 sectors
 *	starting at NVS_PARTITION_OFFSET
 */
    
void nvm_settings_init()
{
    int rc;
    flash_pages_info info;

    printk("%s: mounting circular data fs\n", __func__);
	fs.flash_device = NVS_PARTITION_DEVICE;
	if (!device_is_ready(fs.flash_device)) {
		printk("Flash device %s is not ready\n", fs.flash_device->name);
		goto construction;
	}
	fs.offset = NVS_PARTITION_OFFSET;
	rc = flash_get_page_info_by_offs(fs.flash_device, fs.offset, &info);
	if (rc) {
		printk("Unable to get page info\n");
		goto construction;
	}
	fs.sector_size = info.size;
	fs.sector_count = 3U;

	rc = nvs_mount(&fs);
	if (rc)
    {
		printk("%s: Flash Init failed\n", __func__);
  
        const flash_area *fa_p;
        rc = flash_area_open(NVS_PARTITION_ID, &fa_p);
        flash_area_erase(fa_p, 0, fa_p->fa_size);   // erase everything...
        printk("%s: flash_area erased: %d bytes\n", __func__, fa_p->fa_size);
        rc = nvs_mount(&fs);        // retry
  
		goto construction;
	}

    // read keys from flash
    rc = nvs_read(&fs, KEY_noc_public, noc_public_key, sizeof(noc_public_key));
    printk("%s: public_key result: %d\n", __func__, rc);
    if (rc <= 0)
        noc_public_key[0] = 0;      // not initialized
    rc = nvs_read(&fs, KEY_lock_public, lock_public_key, sizeof(lock_public_key));
    if (rc <= 0)
        noc_public_key[0] = 0;
    rc = nvs_read(&fs, KEY_noc_derived_key, noc_derived_key, sizeof(noc_derived_key));
    if (rc <= 0)
        noc_public_key[0] = 0;
    
    if (noc_public_key[0])
    {
        printk("%s: retrieved derived key: ", __func__);
        auto p = noc_derived_key;
        auto n = sizeof(noc_derived_key);
        while (n--)
            printk("%02x", *p++);
        printk("\n");

    }
    else
    {
construction:
        printk("%s: shared secret is uninitialized\n", __func__);
        std::memset(noc_public_key, 0, sizeof(noc_public_key));
    }
    nvm_settings_set_mode();
}

void nvm_settings_set_mode()
{
    if (noc_public_key[0] && noc_derived_key[0])
    {
        z9lock_status.set_mode(LockStatusMode::NORMAL);
        Z9Crypto_gcmSetKey(noc_key_handle, noc_derived_key, sizeof(noc_derived_key));
    }
    else
        z9lock_status.set_mode(LockStatusMode::CONSTRUCTION);
}
// keys are stored in globals: write to flash
void nvm_settings_save_keys()
{

    // write keys to flash
    printk("%s: saving keys to flash\n", __func__);
	nvs_write(&fs, KEY_lock_public, lock_public_key, sizeof(lock_public_key));
	nvs_write(&fs, KEY_noc_public, noc_public_key, sizeof(noc_public_key));
	nvs_write(&fs, KEY_noc_derived_key, noc_derived_key, sizeof(noc_derived_key));
#ifdef CONFIG_Z9_CONTROLLER 
    // notify lock in paired mode
    nvm_settings_set_mode();
#endif
}

#endif
