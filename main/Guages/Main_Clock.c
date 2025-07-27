#include "Main_Clock.h"
#include "lvgl.h"
#include "esp_now_lib.h"

lv_obj_t * units_indicator;
lv_obj_t * speedo;
lv_obj_t * rpm;
lv_obj_t * fuel;
lv_meter_indicator_t * indic;


static struct_cluster_message last_update = {0};
LV_FONT_DECLARE(michroma_60);
LV_FONT_DECLARE(michroma_32);


void set_gauage_values(struct_cluster_message values) {
    last_update = values;
}


void update_gauge_vals(lv_timer_t *timer) {

    lv_meter_set_indicator_value(rpm, indic, last_update.rpm);
    lv_label_set_text_fmt(speedo, "%d", (int)last_update.speed);
}

void create_outer_rpm_clock()
{
    lv_obj_set_style_bg_color(lv_scr_act(), lv_color_black(),0);
    // Meter start
    rpm = lv_meter_create(lv_scr_act());
    lv_obj_set_style_radius(rpm, LV_RADIUS_CIRCLE, 0);
    lv_obj_center(rpm);
    lv_obj_set_size(rpm, 480, 480);
    /*Add a scale first*/
    lv_meter_scale_t * scale = lv_meter_add_scale(rpm);
    lv_obj_set_style_bg_color(rpm, lv_color_hex(0x4d4f52), 0);
    lv_meter_set_scale_range(rpm, scale, 0, 8000, 270, 135);
    lv_meter_set_scale_ticks(rpm, scale, 41, 2, 10, lv_palette_main(LV_PALETTE_DEEP_ORANGE));
    lv_meter_set_scale_major_ticks(rpm, scale, 5, 4, 20, lv_palette_main(LV_PALETTE_DEEP_ORANGE), 0);
    lv_obj_set_style_text_color(rpm, lv_color_white(), LV_PART_TICKS);
    

    

    /*Add a needle line indicator*/
    indic = lv_meter_add_needle_line(rpm, scale, 8, lv_color_white(), 0);
}

void create_center_clock()
{
    lv_obj_t *inner_circle = lv_obj_create(rpm);
    lv_obj_set_size(inner_circle, 240, 240);  // Adjust size for your design
    lv_obj_center(inner_circle);
    lv_obj_set_style_bg_color(inner_circle, lv_color_black(), 0);
    lv_obj_set_style_radius(inner_circle, LV_RADIUS_CIRCLE, 0);
    lv_obj_set_style_border_width(inner_circle, 0, 0);

    speedo = lv_label_create(inner_circle);
    units_indicator = lv_label_create(inner_circle);
    
    lv_obj_set_style_text_font(speedo, &michroma_60, LV_PART_MAIN);
    lv_label_set_text_fmt(speedo, "0");
    lv_obj_center(speedo);
    lv_obj_set_style_text_align(speedo, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_style_text_color(speedo, lv_color_white(), LV_PART_MAIN);

    lv_label_set_text_fmt(units_indicator, "km/h");
    lv_obj_set_style_text_font(units_indicator, &michroma_32, LV_PART_MAIN);
    lv_obj_set_style_text_color(units_indicator, lv_color_white(), LV_PART_MAIN);
    // lv_obj_align(units_indicator, LV_ALIGN_OUT_BOTTOM_MID, 0, 0); 
    lv_obj_align_to(units_indicator, speedo, LV_ALIGN_OUT_BOTTOM_MID, 0, 5);


    lv_timer_create(update_gauge_vals, 16, NULL);
}



void create_main_clock() {
    create_outer_rpm_clock();
    create_center_clock();
}
