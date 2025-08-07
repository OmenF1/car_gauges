#ifndef SECONDARY_CLOCK_H
#define SECONDARY_CLOCK_H
#include "esp_now_lib.h"

void create_secondary_clock();

void set_gauage_values(struct_cluster_message values);

#endif