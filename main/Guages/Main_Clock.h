#ifndef MAIN_CLOCK_H
#define MAIN_CLOCK_H
#include "esp_now_lib.h"

void create_main_clock();

void set_gauage_values(struct_cluster_message values);

#endif