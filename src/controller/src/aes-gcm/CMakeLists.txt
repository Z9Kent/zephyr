if(CONFIG_Z9_GCM_C)

# software GCM (derived from mbedTLS)
include_directories(.)
target_sources(app PRIVATE z9-gcm-aes.c z9-gcm-c.c cipher.c cipher_wrap.c)

endif()
