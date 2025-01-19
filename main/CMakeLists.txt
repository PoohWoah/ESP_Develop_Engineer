set(SRC_FILES "main.c" "byte_rtc_request.c" "volc_rtc.c" "audio_processor.c")

if (CONFIG_ESP32_S3_KORVO2_V3_BOARD OR CONFIG_ESP32_S3_BOX_3_BOARD)
    list(APPEND  SRC_FILES "audio_stream_7210.c")
    message(STATUS "---> CONFIG_ESP32_S3_KORVO2_V3_BOARD")
elseif (CONFIG_ESP32_S3_KORVO2L_V1_BOARD)
    message(STATUS "---> CONFIG_ESP32_S3_KORVO2L_V1_BOARD")
    list(APPEND  SRC_FILES "audio_stream_8311.c")
endif()

set(COMPONENT_SRCS ${SRC_FILES})
set(COMPONENT_ADD_INCLUDEDIRS .)

register_component()

spiffs_create_partition_image(spiffs_data ../spiffs FLASH_IN_PROJECT)
