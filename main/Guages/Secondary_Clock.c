#include "Secondary_Clock.h"
#include "lvgl.h"
#include "esp_now_lib.h"


lv_obj_t * temp_gauge;
lv_obj_t * temp_label;

lv_obj_t * boost_gauge;
lv_obj_t * boost_label;



static struct_cluster_message last_update = {0};
LV_FONT_DECLARE(michroma_80);
LV_FONT_DECLARE(michroma_32);
LV_FONT_DECLARE(michroma_24);

LV_IMG_DECLARE(petrol_icon);


void set_gauage_values(struct_cluster_message values) {
    last_update = values;
}


void update_gauge_vals(lv_timer_t *timer) {

    // lv_arc_set_value(rpm_gauge, last_update.rpm);
    // if (last_update.rpm > 6000 && last_update.rpm < 6700)  {
    //     lv_obj_set_style_arc_color(rpm_gauge, lv_palette_main(LV_PALETTE_AMBER), LV_PART_INDICATOR);
    // } else if (last_update.rpm > 6500){
    //     lv_obj_set_style_arc_color(rpm_gauge, lv_palette_main(LV_PALETTE_RED), LV_PART_INDICATOR);
    // } else {
    //     lv_obj_set_style_arc_color(rpm_gauge, lv_palette_main(LV_PALETTE_BLUE_GREY), LV_PART_INDICATOR);
    // }
    // lv_label_set_text_fmt(rpm_value, "%d", (int)last_update.rpm);
    // lv_label_set_text_fmt(speedo, "%d", (int)last_update.speed);
    // lv_arc_set_value(fuel_gauge, last_update.fuel);
}


void create_center_clock()
{
    temp_label = lv_label_create(lv_scr_act());
    boost_label = lv_label_create(lv_scr_act());

    lv_label_set_text_fmt(temp_label, "40 °C");
    lv_obj_set_style_text_font(temp_label, &michroma_32, LV_PART_MAIN);
    lv_obj_set_style_text_color(temp_label, lv_palette_main(LV_PALETTE_GREY), LV_PART_MAIN);
    lv_obj_align(temp_label, LV_ALIGN_LEFT_MID, 50, 0);
    
    lv_label_set_text_fmt(boost_label, "0.0 bar");   
    lv_obj_set_style_text_font(boost_label, &michroma_32, LV_PART_MAIN);
    lv_obj_center(boost_label);
    lv_obj_set_style_text_color(boost_label, lv_color_white(), LV_PART_MAIN);
    lv_obj_align(boost_label, LV_ALIGN_RIGHT_MID, -50, 0);

}


void create_temp_gauge() {
    temp_gauge = lv_arc_create(lv_scr_act());
    lv_obj_center(temp_gauge);
    lv_arc_set_range(temp_gauge, 1, 130);
    lv_obj_set_size(temp_gauge, 475, 475);
    lv_arc_set_rotation(temp_gauge, 130);
    lv_arc_set_bg_angles(temp_gauge, 0, 120);
    

    lv_obj_set_style_arc_rounded(temp_gauge, false, LV_PART_MAIN);
    lv_obj_set_style_arc_rounded(temp_gauge, false, LV_PART_INDICATOR);
    lv_obj_remove_style(temp_gauge, NULL, LV_PART_KNOB);
    lv_obj_clear_flag(temp_gauge, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_set_style_arc_opa(temp_gauge, 90, 0);
    lv_obj_set_style_arc_width(temp_gauge, 20, LV_PART_INDICATOR);
    lv_obj_set_style_arc_width(temp_gauge, 20, LV_PART_MAIN);
}

void create_boost_gauge() {
    boost_gauge = lv_arc_create(lv_scr_act());
    lv_obj_center(boost_gauge);
    // It doesn't look like we can use floats here, so I'll have to scale the value up to an int.
    lv_arc_set_range(boost_gauge, 0, 100); 
    lv_obj_set_size(boost_gauge, 480, 480);
    lv_arc_set_rotation(boost_gauge, 290);
    lv_arc_set_bg_angles(boost_gauge, 0, 120);
    lv_arc_set_value(boost_gauge, 0);
    lv_obj_set_style_arc_color(boost_gauge, lv_palette_main(LV_PALETTE_GREY), LV_PART_INDICATOR);
    lv_arc_set_mode(boost_gauge, LV_ARC_MODE_REVERSE);

    lv_obj_set_style_arc_rounded(boost_gauge, false, LV_PART_MAIN);
    lv_obj_set_style_arc_rounded(boost_gauge, false, LV_PART_INDICATOR);
    lv_obj_remove_style(boost_gauge, NULL, LV_PART_KNOB);
    lv_obj_clear_flag(boost_gauge, LV_OBJ_FLAG_CLICKABLE); 
    lv_obj_set_style_arc_opa(boost_gauge, 50, 0);
    lv_obj_set_style_arc_width(boost_gauge, 20, LV_PART_INDICATOR);
    lv_obj_set_style_arc_width(boost_gauge, 20, LV_PART_MAIN);
}


void create_secondary_clock() {
    create_boost_gauge();
    create_center_clock();
    create_temp_gauge();
    lv_timer_create(update_gauge_vals, 16, NULL);
}