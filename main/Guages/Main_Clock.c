#include "Main_Clock.h"
#include "lvgl.h"


lv_obj_t * speedo;
lv_obj_t * rpm;
lv_meter_indicator_t * indic;

static void set_value(void * indic, int32_t v)
{
    lv_meter_set_indicator_value(rpm, indic, v);
}

static short last_rpm_value = 0;

void set_rpm(short rpm_value) {
    last_rpm_value = rpm_value;
}


static void set_speed(void * label, int32_t speed) {
    lv_label_set_text_fmt(label, "%" PRId32 "\nkm/h", speed);
}


void rpm_anim_cb(lv_timer_t *timer) {

    lv_meter_set_indicator_value(rpm, indic, last_rpm_value);
}

void add_main_clock() {
// Meter start
    rpm = lv_meter_create(lv_scr_act());
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
    indic = lv_meter_add_needle_line(rpm, scale, 8, lv_palette_main(LV_PALETTE_RED), 0);

    lv_obj_t *inner_circle = lv_obj_create(rpm);
lv_obj_set_size(inner_circle, 230, 230);  // Adjust size for your design
lv_obj_center(inner_circle);
lv_obj_set_style_bg_color(inner_circle, lv_color_black(), 0);
lv_obj_set_style_radius(inner_circle, LV_RADIUS_CIRCLE, 0);
lv_obj_set_style_border_width(inner_circle, 0, 0);
speedo = lv_label_create(inner_circle);
lv_label_set_text_fmt(speedo, "0\nkm/h");
lv_obj_set_style_text_align(speedo, LV_TEXT_ALIGN_CENTER, 0);
lv_obj_set_style_text_color(speedo, lv_color_white(), LV_PART_MAIN);
lv_obj_center(speedo);
lv_timer_create(rpm_anim_cb, 16, NULL);

    /*Create an animation to set the value*/
    // lv_anim_t a;
    // lv_anim_init(&a);
    // lv_anim_set_exec_cb(&a, set_value);
    // lv_anim_set_var(&a, indic);
    // lv_anim_set_values(&a, 0, 8000);
    // lv_anim_set_time(&a, 2000);
    // lv_anim_set_repeat_delay(&a, 100);
    // lv_anim_set_playback_time(&a, 500);
    // lv_anim_set_playback_delay(&a, 100);
    // lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE);
    // lv_anim_start(&a);

    //     lv_anim_t b;
    // lv_anim_init(&b);
    // lv_anim_set_exec_cb(&b, set_speed);
    // lv_anim_set_var(&b, speedo);
    // lv_anim_set_values(&b, 0, 280);
    // lv_anim_set_time(&b, 2000);
    // lv_anim_set_repeat_delay(&b, 100);
    // lv_anim_set_playback_time(&b, 500);
    // lv_anim_set_playback_delay(&b, 100);
    // lv_anim_set_repeat_count(&b, LV_ANIM_REPEAT_INFINITE);
    // lv_anim_start(&b);
}
