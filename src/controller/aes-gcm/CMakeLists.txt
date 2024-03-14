if(CONFIG_Z9_GCM_C)

# software GCM (derived from mbedTLS)
include_directories(.)
target_sources(app PRIVATE aes-gcm/aes.cc aes-gcm/gcm.cc aes-gcm/cipher.cc aes-gcm/cipher_wrap.cc)

endif()
