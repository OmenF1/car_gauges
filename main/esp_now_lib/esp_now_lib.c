#include <stdint.h>
#include "esp_now_lib.h"
#include "esp_now.h"
#include "esp_log.h"
#include "Guages/Main_Clock.h"

static const char *TAG = "esp-now-lib";



typedef struct struct_message {
    short a;
} struct_message;

struct_message message;

void on_data_receive(const esp_now_recv_info_t *mac, const uint8_t *data, int len) {
  memcpy(&message, data, sizeof(message));
  set_rpm(message.a);
}


void init_esp_now() {
    esp_now_init();
    esp_now_register_recv_cb(on_data_receive);

}

