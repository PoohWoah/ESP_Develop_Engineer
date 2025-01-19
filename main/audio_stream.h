#pragma once

#include "audio_element.h"
#include "recorder_sr.h"

/**
 * @brief Create an encoder stream for recording audio
 *
 * This function initializes and configures an encoder stream to process recorded audio data. 
 * The encoder stream can be used to encode audio into specific formats such as MP3 or AAC.
 *
 * @return Handle to the audio element representing the encoder stream
 */
audio_element_handle_t create_record_encoder_stream(void);

/**
 * @brief Create a raw audio stream for recording
 *
 * This function initializes a raw audio stream for recording. It allows the recorded audio
 * data to be passed through without any processing or encoding.
 *
 * @return Handle to the audio element representing the raw stream
 */
audio_element_handle_t create_record_raw_stream(void);

/**
 * @brief Create an I2S stream for recording audio
 *
 * This function initializes an I2S audio stream for recording purposes. It is typically used
 * to interface with audio hardware such as microphones or ADCs via the I2S protocol.
 *
 * @return Handle to the audio element representing the I2S stream
 */
audio_element_handle_t create_record_i2s_stream(void);

/**
 * @brief Create a decoder stream for audio playback
 *
 * This function initializes and configures a decoder stream to process audio data for playback.
 * The decoder supports decoding audio formats such as MP3, AAC, or WAV.
 *
 * @return Handle to the audio element representing the decoder stream
 */
audio_element_handle_t create_player_decoder_stream(void);

/**
 * @brief Create a WAV decoder stream for audio playback
 *
 * This function initializes a dedicated WAV decoder stream for playback. It decodes WAV format
 * audio files and prepares the data for further processing or output.
 *
 * @return Handle to the audio element representing the WAV decoder stream
 */
audio_element_handle_t create_player_wav_decoder_stream(void);

/**
 * @brief Create a raw audio stream for playback
 *
 * This function initializes a raw audio stream for playback. It allows unprocessed audio data
 * to be sent directly to the output without decoding.
 *
 * @return Handle to the audio element representing the raw stream
 */
audio_element_handle_t create_player_raw_stream(void);

/**
 * @brief Create an I2S stream for audio playback
 *
 * This function initializes an I2S stream for audio playback. It interfaces with audio hardware
 * such as speakers or DACs via the I2S protocol for audio output.
 *
 * @return Handle to the audio element representing the I2S stream
 */
audio_element_handle_t create_player_i2s_stream(bool enable_task);

/**
 * @brief Create a stream element to convert mono-channel (1 channel) audio data to stereo-channel (2 channels).
 *
 * @return 
 *     - A handle to the audio element on success.
 *     - NULL if the creation fails.
 */
audio_element_handle_t create_ch1_to_ch2_rsp_stream(void);

/**
 * @brief Create a stream element to convert mono-channel 8 kHz audio to stereo-channel 16 kHz audio.
 *
 * @return 
 *     - A handle to the audio element on success.
 *     - NULL if the creation fails.
 */
audio_element_handle_t create_8k_ch1_to_16k_ch2_rsp_stream(void);

/**
 * @brief Create a SPIFFS stream for audio player file input
 *
 * This function initializes a stream that reads audio data from the SPIFFS (SPI Flash File System).
 * It is used for playing audio files stored in the flash memory.
 *
 * @return Handle to the audio element representing the SPIFFS stream
 */
audio_element_handle_t create_audio_player_spiffs_stream(void);

/**
 * @brief Get the default audio recording configuration.
 *
 * @return Default audio recording configuration
 */
recorder_sr_cfg_t get_default_audio_record_config(void);

