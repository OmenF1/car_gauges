#include "Main_Clock.h"
#include "lvgl.h"
#include "esp_now_lib.h"

lv_obj_t * units_indicator;
lv_obj_t * speedo;
lv_obj_t * fuel_gauge;
lv_obj_t * rpm_gauge;
lv_obj_t * rpm_value;



static struct_cluster_message last_update = {0};
LV_FONT_DECLARE(michroma_80);
LV_FONT_DECLARE(michroma_32);
LV_FONT_DECLARE(michroma_24);

LV_IMG_DECLARE(petrol_icon);


void set_gauage_values(struct_cluster_message values) {
    last_update = values;
}


void update_gauge_vals(lv_timer_t *timer) {

    lv_arc_set_value(rpm_gauge, last_update.rpm);
    if (last_update.rpm > 6000 && last_update.rpm < 6700)  {
        lv_obj_set_style_arc_color(rpm_gauge, lv_palette_main(LV_PALETTE_AMBER), LV_PART_INDICATOR);
    } else if (last_update.rpm > 6500){
        lv_obj_set_style_arc_color(rpm_gauge, lv_palette_main(LV_PALETTE_RED), LV_PART_INDICATOR);
    } else {
        lv_obj_set_style_arc_color(rpm_gauge, lv_palette_main(LV_PALETTE_BLUE_GREY), LV_PART_INDICATOR);
    }
    lv_label_set_text_fmt(rpm_value, "%d", (int)last_update.rpm);
    lv_label_set_text_fmt(speedo, "%d", (int)last_update.speed);
}


void create_center_clock()
{
    speedo = lv_label_create(lv_scr_act());
    units_indicator = lv_label_create(lv_scr_act());
    rpm_value = lv_label_create(lv_scr_act());

    lv_label_set_text_fmt(units_indicator, "km/h");
    lv_obj_set_style_text_font(units_indicator, &michroma_32, LV_PART_MAIN);
    lv_obj_set_style_text_color(units_indicator, lv_palette_main(LV_PALETTE_GREY), LV_PART_MAIN);
    // lv_obj_align(units_indicator, LV_ALIGN_LEFT_MID, 40, -50); keeping as an alternative layout
    lv_obj_align(units_indicator, LV_ALIGN_TOP_MID, 0, 120);
    
    lv_label_set_text_fmt(speedo, "0");   
    lv_obj_set_style_text_font(speedo, &michroma_80, LV_PART_MAIN);
    lv_obj_center(speedo);
    lv_obj_set_style_text_color(speedo, lv_color_white(), LV_PART_MAIN);
    // lv_obj_align(speedo, LV_ALIGN_LEFT_MID, 30, 0); keeping as an alternative layout
    // lv_obj_align(speedo, LV_ALIGN_TOP_MID, 0, 120);

    lv_label_set_text_fmt(rpm_value, "0");   
    lv_obj_set_style_text_font(rpm_value, &michroma_24, LV_PART_MAIN);
    lv_obj_set_style_text_color(rpm_value, lv_palette_main(LV_PALETTE_GREY), LV_PART_MAIN);
    lv_obj_align(rpm_value, LV_ALIGN_RIGHT_MID, -10, 0);
}


void create_rpm_gauge() {
    rpm_gauge = lv_arc_create(lv_scr_act());
    lv_obj_center(rpm_gauge);
    lv_arc_set_range(rpm_gauge, 0, 8000);
    lv_obj_set_size(rpm_gauge, 480, 480);
    lv_arc_set_rotation(rpm_gauge, 135);
    lv_arc_set_bg_angles(rpm_gauge, 0, 220);
    lv_arc_set_value(rpm_gauge, 0);

    lv_obj_set_style_arc_rounded(rpm_gauge, false, LV_PART_MAIN);
    lv_obj_set_style_arc_rounded(rpm_gauge, false, LV_PART_INDICATOR);
    lv_obj_remove_style(rpm_gauge, NULL, LV_PART_KNOB);
    lv_obj_clear_flag(rpm_gauge, LV_OBJ_FLAG_CLICKABLE); 
    lv_obj_set_style_arc_opa(rpm_gauge, 50, 0);
    lv_obj_set_style_arc_width(rpm_gauge, 80, LV_PART_INDICATOR);
    lv_obj_set_style_arc_width(rpm_gauge, 80, LV_PART_MAIN);
}

void create_fuel_gauge() {
    fuel_gauge = lv_arc_create(lv_scr_act());
    lv_obj_center(fuel_gauge);
    lv_arc_set_range(fuel_gauge, 1, 100);
    lv_obj_set_size(fuel_gauge, 475, 475);
    lv_arc_set_rotation(fuel_gauge, 30);
    lv_arc_set_bg_angles(fuel_gauge, 0, 75);
    lv_arc_set_value(fuel_gauge, 50);
    lv_obj_set_style_arc_color(fuel_gauge, lv_palette_main(LV_PALETTE_GREY), LV_PART_INDICATOR);

    lv_obj_set_style_arc_rounded(fuel_gauge, false, LV_PART_MAIN);
    lv_obj_set_style_arc_rounded(fuel_gauge, false, LV_PART_INDICATOR);
    lv_obj_remove_style(fuel_gauge, NULL, LV_PART_KNOB);
    lv_obj_clear_flag(fuel_gauge, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_set_style_arc_opa(fuel_gauge, 90, 0);
    lv_obj_set_style_arc_width(fuel_gauge, 25, LV_PART_INDICATOR);
    lv_obj_set_style_arc_width(fuel_gauge, 25, LV_PART_MAIN);
    lv_arc_set_mode(fuel_gauge, LV_ARC_MODE_REVERSE);

    lv_obj_t * full_label = lv_label_create(lv_scr_act());
    lv_obj_t * empty_label = lv_label_create(lv_scr_act());

    lv_label_set_text_fmt(full_label, "F");   
    lv_obj_set_style_text_font(full_label, &michroma_32, LV_PART_MAIN);
    lv_obj_set_style_text_color(full_label, lv_color_white(), LV_PART_MAIN);
    lv_obj_align(full_label, LV_ALIGN_BOTTOM_RIGHT, -60, -130);

    lv_label_set_text_fmt(empty_label, "E");   
    lv_obj_set_style_text_font(empty_label, &michroma_32, LV_PART_MAIN);
    lv_obj_set_style_text_color(empty_label, lv_color_white(), LV_PART_MAIN);
    lv_obj_align(empty_label, LV_ALIGN_BOTTOM_MID, -50, -40);

    lv_obj_t * fuel_icon = lv_img_create(lv_scr_act());
    lv_img_set_src(fuel_icon, &petrol_icon);
    lv_obj_set_width(fuel_icon, 50);
    lv_obj_set_height(fuel_icon, 50);
    lv_obj_align(fuel_icon, LV_ALIGN_BOTTOM_MID, 60, -80);
}

void create_main_clock() {
    create_rpm_gauge();
    create_center_clock();
    create_fuel_gauge();
    lv_timer_create(update_gauge_vals, 16, NULL);
}