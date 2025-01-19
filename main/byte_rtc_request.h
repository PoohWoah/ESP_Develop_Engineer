/*
 * ESPRESSIF MIT License
 *
 * Copyright (c) 2025 <ESPRESSIF SYSTEMS (SHANGHAI) CO., LTD>
 *
 * Permission is hereby granted for use on all ESPRESSIF SYSTEMS products, in which case,
 * it is free of charge, to any person obtaining a copy of this software and associated
 * documentation files (the "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the Software is furnished
 * to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    BYTE_RTC_REQ_AUDIO_TYPE_G711A,
    BYTE_RTC_REQ_AUDIO_TYPE_OPUS,
} byte_rtc_req_audio_type_e;

typedef enum {
    BYTE_RTC_REQ_VIDEO_TYPE_MJPEG,
    BYTE_RTC_REQ_VIDEO_TYPE_H264,
} byte_rtc_req_video_type_e;

#define BYTE_RTC_DEFAULT_CONFIG() {                                                                  \
    .uri           = "",                                           \
    .authorization = "",  \
    .bot_id        = "",                                                          \
    .voice_id      = "",                                                          \
    .audio_type    = BYTE_RTC_REQ_AUDIO_TYPE_OPUS,                                                  \
    .video_type    = BYTE_RTC_REQ_VIDEO_TYPE_H264,                                                   \
}

typedef struct {
    char *room_id;
    char *app_id;
    char *token;
    char *uid;
} byte_rtc_req_result_t;

typedef struct {
    const char               *uri;
    const char               *authorization;
    const char               *bot_id;
    const char               *voice_id;
    byte_rtc_req_audio_type_e audio_type;
    byte_rtc_req_video_type_e video_type;
} byte_rtc_req_config_t;

byte_rtc_req_result_t *byte_rtc_request(byte_rtc_req_config_t *config);

void byte_rtc_request_free(byte_rtc_req_result_t *result);

#ifdef __cplusplus
}
#endif