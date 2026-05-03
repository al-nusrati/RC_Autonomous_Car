#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_log.h>
#include <esp_camera.h>

static const char *TAG = "HAWK_GOOUUU";

// ===== GOOUUU camera pins (from your camera_pins.h) =====
#define CAM_PIN_PWDN     -1
#define CAM_PIN_RESET    -1
#define CAM_PIN_XCLK     15
#define CAM_PIN_SIOD     4     // SDA
#define CAM_PIN_SIOC     5     // SCL
#define CAM_PIN_D0       10    // Y2
#define CAM_PIN_D1       12    // Y3
#define CAM_PIN_D2       8     // Y4
#define CAM_PIN_D3       11    // Y5
#define CAM_PIN_D4       9     // Y6
#define CAM_PIN_D5       18    // Y7
#define CAM_PIN_D6       17
#define CAM_PIN_D7       16
#define CAM_PIN_VSYNC    6
#define CAM_PIN_HREF     7
#define CAM_PIN_PCLK     13

static esp_err_t hawk_camera_init() {
    camera_config_t config;
    memset(&config, 0, sizeof(config));

    // Assign in struct declaration order to prevent C++ warnings
    config.pin_pwdn      = CAM_PIN_PWDN;
    config.pin_reset     = CAM_PIN_RESET;
    config.pin_xclk      = CAM_PIN_XCLK;
    config.pin_sccb_sda  = CAM_PIN_SIOD;
    config.pin_sccb_scl  = CAM_PIN_SIOC;
    config.pin_d7        = CAM_PIN_D7;
    config.pin_d6        = CAM_PIN_D6;
    config.pin_d5        = CAM_PIN_D5;
    config.pin_d4        = CAM_PIN_D4;
    config.pin_d3        = CAM_PIN_D3;
    config.pin_d2        = CAM_PIN_D2;
    config.pin_d1        = CAM_PIN_D1;
    config.pin_d0        = CAM_PIN_D0;
    config.pin_vsync     = CAM_PIN_VSYNC;
    config.pin_href      = CAM_PIN_HREF;
    config.pin_pclk      = CAM_PIN_PCLK;
    config.xclk_freq_hz  = 20000000;
    config.ledc_timer    = LEDC_TIMER_1;
    config.ledc_channel  = LEDC_CHANNEL_3;
    config.pixel_format  = PIXFORMAT_JPEG;
    config.frame_size    = FRAMESIZE_128X128;
    config.jpeg_quality  = 12;
    config.fb_count      = 2;
    config.fb_location   = CAMERA_FB_IN_PSRAM;
    config.grab_mode     = CAMERA_GRAB_WHEN_EMPTY;
    config.sccb_i2c_port = 1;   // GOOUUU uses I2C port 1 for camera SCCB

    esp_err_t err = esp_camera_init(&config);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Camera init failed: 0x%x", err);
        return err;
    }

    sensor_t *s = esp_camera_sensor_get();
    if (s) {
        ESP_LOGI(TAG, "Camera PID=0x%02X VER=0x%02X", s->id.PID, s->id.VER);
    }
    return ESP_OK;
}

extern "C" void app_main() {
    ESP_LOGI(TAG, "GOOUUU camera test starting...");
    if (hawk_camera_init() == ESP_OK) {
        ESP_LOGI(TAG, "Camera ready – stream or drive code goes here");
    }
    while (1) vTaskDelay(1000);
}