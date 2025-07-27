#ifndef ESP_NOW_LIB_H
#define ESP_NOW_LIB_H

typedef struct struct_cluster_message {
    short rpm;
    short speed;
    short fuel;
    short boost;

    short coolant_temp;
    short oil_temp;
    short oil_pressure;
    float voltage;
} struct_cluster_message;

void init_esp_now();

#endif