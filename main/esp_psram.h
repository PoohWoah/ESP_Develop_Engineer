#ifndef ESP_PSRAM_H
#define ESP_PSRAM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "esp_heap_caps.h"
#include "esp_timer.h"

void * esp_psram_malloc(size_t size);
void * esp_psram_calloc(size_t n, size_t size);
void * esp_psram_realloc(void *ptr, size_t size);

unsigned long esp_millis(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
