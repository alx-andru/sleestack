#include <pebble.h>
#include "main.h"

#include <pebble.h>

static Window *s_main_window;
static TextLayer *s_time_layer, *s_date_layer, *s_time_layer, *s_text_utc_offset_layer, *s_time_utc_offset_layer, *s_battery_layer, *s_text_steps_layer, *s_steps_layer;
static void handle_accel_tap(AccelAxisType axis, int32_t direction);
static bool is_hidden;
int32_t utc_offset_int = 0, primary_font = 0, secondary_font = 5;
AppTimer * timer_hide;

const char *fonts[] ={ 
  // primary fonts
  FONT_KEY_BITHAM_42_BOLD, // 0
  FONT_KEY_BITHAM_42_LIGHT, // 1
  FONT_KEY_GOTHIC_28_BOLD, // 2
  FONT_KEY_ROBOTO_BOLD_SUBSET_49, // 3
  FONT_KEY_LECO_42_NUMBERS, // 4
  // secondary fonts
  FONT_KEY_GOTHIC_18, // 5
  FONT_KEY_GOTHIC_18_BOLD, // 6
  FONT_KEY_ROBOTO_CONDENSED_21, // 7
  FONT_KEY_LECO_20_BOLD_NUMBERS // 8
};

#define KEY_COLOR_BACKGROUND      0
#define KEY_COLOR_PRIMARY         1
#define KEY_COLOR_SECONDARY       2

#define KEY_TEXT_LABEL            4
#define KEY_STRING_UTC_OFFSET     5

#define KEY_STRING_PRIMARY_FONT   6
#define KEY_STRING_SECONDARY_FONT 7

static void update_steps(){
  HealthMetric metric = HealthMetricStepCount;
  time_t start = time_start_of_today();
  time_t end = time(NULL);  
  HealthServiceAccessibilityMask mask = health_service_metric_accessible(metric, start, end);
  
  if(mask & HealthServiceAccessibilityMaskAvailable) {
    static char s_buffer_steps[32];
    snprintf(s_buffer_steps, sizeof(s_buffer_steps), "%d", (int)health_service_sum_today(metric));
    text_layer_set_text(s_steps_layer, s_buffer_steps);
  }   
}

static void update_time() {
  time_t time_localtime = time(NULL); 
  struct tm *tm_local = localtime(&time_localtime);
  
  // Set time 21:44 (UTC-5)
  static char s_buff_local_time[8];
  strftime(s_buff_local_time, sizeof(s_buff_local_time), clock_is_24h_style() ? "%H:%M" : "%I:%M", tm_local);
  text_layer_set_text(s_time_layer, s_buff_local_time);
  // Set date Sat 21 May
  static char s_date_buffer[16];
  strftime(s_date_buffer, sizeof(s_date_buffer), "%a %d %b", tm_local);
  text_layer_set_text(s_date_layer, s_date_buffer);
  
  // Adjust UTC Offset - Experimental
  struct tm *tm_adjusted = gmtime(&time_localtime);
  if(tm_adjusted->tm_hour + utc_offset_int <= 0){
    if(tm_local->tm_isdst == 1){
      tm_adjusted->tm_hour += utc_offset_int + 24 + 1;    
    } else {
      tm_adjusted->tm_hour += utc_offset_int + 24;    
    }
  } else if(tm_adjusted->tm_hour + utc_offset_int >= 24) {
      tm_adjusted->tm_hour += utc_offset_int - 24;    
  } else {
   tm_adjusted->tm_hour += utc_offset_int;  
  }
  
  // Set utc offset time 03:44 (UTC+2 + DST)
  static char s_buff_adjusted_time[8];
  strftime(s_buff_adjusted_time, sizeof(s_buff_adjusted_time), clock_is_24h_style() ? "%H:%M" : "%I:%M", tm_adjusted);
  text_layer_set_text(s_time_utc_offset_layer, s_buff_adjusted_time);
  
  update_steps();  
}

// register tick handler to update time
static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  update_time();
}

// display battery charge
static void battery_handler(BatteryChargeState charge_state) {
  static char s_battery_buffer[16];

  if (charge_state.is_charging) {
    snprintf(s_battery_buffer, sizeof(s_battery_buffer), "CHRG");
  } else {
    snprintf(s_battery_buffer, sizeof(s_battery_buffer), "%d%%", charge_state.charge_percent);
  }
  text_layer_set_text(s_battery_layer, s_battery_buffer);
}


static void updateBackgroundColor(GColor background_color){
  window_set_background_color(s_main_window, background_color);  
}

static void updatePrimaryColor(GColor primary_color){
  text_layer_set_text_color(s_time_layer, primary_color);
  text_layer_set_text_color(s_text_utc_offset_layer, primary_color);
  text_layer_set_text_color(s_text_steps_layer, primary_color);
}

static void updateSecondaryColor(GColor secondary_color){
  text_layer_set_text_color(s_date_layer, secondary_color);
  text_layer_set_text_color(s_time_utc_offset_layer, secondary_color);
  text_layer_set_text_color(s_steps_layer, secondary_color);
  text_layer_set_text_color(s_battery_layer, secondary_color);
}

static void updateUtcOffsetLabel(char *s_buffer){
  text_layer_set_text(s_text_utc_offset_layer, s_buffer);
}

static void updatePrimaryFont(){
  text_layer_set_font(s_time_layer, fonts_get_system_font(fonts[primary_font]));
}
static void updateSecondaryFont(){
  text_layer_set_font(s_time_utc_offset_layer, fonts_get_system_font(fonts[secondary_font]));
  text_layer_set_font(s_steps_layer, fonts_get_system_font(fonts[secondary_font]));
  text_layer_set_font(s_date_layer, fonts_get_system_font(fonts[secondary_font]));
}

static void initializeConfig(){
  
  if (persist_exists(KEY_COLOR_PRIMARY)) {
    uint32_t primary_int = persist_read_int(KEY_COLOR_PRIMARY);
    GColor primary_color = GColorFromHEX(primary_int);
    updatePrimaryColor(primary_color);
  }
  
  if (persist_exists(KEY_COLOR_BACKGROUND)) {
    uint32_t background_int = persist_read_int(KEY_COLOR_BACKGROUND);
    GColor background_color = GColorFromHEX(background_int);
    updateBackgroundColor(background_color);
  }
  
  if (persist_exists(KEY_COLOR_SECONDARY)) {
    uint32_t sc_hex = persist_read_int(KEY_COLOR_SECONDARY);
    GColor secondary_color = GColorFromHEX(sc_hex);
    updateSecondaryColor(secondary_color);
  }
  
  if (persist_exists(KEY_TEXT_LABEL) && persist_exists(KEY_TEXT_LABEL)) {
    static char s_buffer[16];
    persist_read_string(KEY_TEXT_LABEL, s_buffer, 16);
    text_layer_set_text(s_text_utc_offset_layer, s_buffer);
  }
  
  if (persist_exists(KEY_STRING_UTC_OFFSET)) {    
    utc_offset_int = persist_read_int(KEY_STRING_UTC_OFFSET);
    update_time();
  }
  
  if (persist_exists(KEY_STRING_PRIMARY_FONT)) {
    primary_font = persist_read_int(KEY_STRING_PRIMARY_FONT);
    updatePrimaryFont();
  }
  
  if (persist_exists(KEY_STRING_SECONDARY_FONT)) {
    secondary_font = persist_read_int(KEY_STRING_SECONDARY_FONT);
    updateSecondaryFont();
  } 
}

static void main_window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);
  s_time_layer = text_layer_create(GRect(0, 58, bounds.size.w, 50));

  /// Time 00:00
  window_set_background_color(window, GColorMediumSpringGreen);
  text_layer_set_background_color(s_time_layer, GColorClear);
  text_layer_set_text_color(s_time_layer, GColorYellow);
  text_layer_set_text(s_time_layer, "00:00");
  text_layer_set_font(s_time_layer, fonts_get_system_font(fonts[primary_font]));
  text_layer_set_text_alignment(s_time_layer, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(s_time_layer));
  
  /// Date
  s_date_layer = text_layer_create(GRect(0, 100, 144, 30));
  text_layer_set_text_color(s_date_layer, GColorBlack);
  text_layer_set_background_color(s_date_layer, GColorClear);
  text_layer_set_text_alignment(s_date_layer, GTextAlignmentCenter);
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_date_layer));

  /// Battery
  s_battery_layer = text_layer_create(GRect(0, 0, 36, 20));
  layer_set_hidden((Layer *) s_battery_layer, true);
  text_layer_set_background_color(s_battery_layer, GColorClear);  
  text_layer_set_text_color(s_battery_layer, GColorYellow);
  text_layer_set_text_alignment(s_battery_layer, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(s_battery_layer));
  
  battery_handler(battery_state_service_peek());

  /// UTC Offset Label
  s_text_utc_offset_layer = text_layer_create(GRect(0, 130, 46, 14));
  layer_set_hidden((Layer *) s_text_utc_offset_layer, true);
  text_layer_set_text(s_text_utc_offset_layer, "UTC");
  text_layer_set_background_color(s_text_utc_offset_layer, GColorClear);
  text_layer_set_text_color(s_text_utc_offset_layer, GColorBlack);
  layer_add_child(window_layer, text_layer_get_layer(s_text_utc_offset_layer));
  text_layer_set_text_alignment(s_text_utc_offset_layer, GTextAlignmentCenter);
  
  /// UTC Offset Time
  s_time_utc_offset_layer = text_layer_create(GRect(0, 144, 46, 20));
  layer_set_hidden((Layer *) s_time_utc_offset_layer, true);
  text_layer_set_text(s_time_layer, "00:00");
  text_layer_set_background_color(s_time_utc_offset_layer, GColorClear);
  text_layer_set_text_color(s_time_utc_offset_layer, GColorWhite);
  layer_add_child(window_layer, text_layer_get_layer(s_time_utc_offset_layer));
  text_layer_set_font(s_time_utc_offset_layer, fonts_get_system_font(fonts[secondary_font]));
  text_layer_set_text_alignment(s_time_utc_offset_layer, GTextAlignmentCenter);
    
  /// Steps Label
  s_text_steps_layer = text_layer_create(GRect(95, 130, 46, 14));
  layer_set_hidden((Layer *) s_text_steps_layer, true);
  text_layer_set_text(s_text_steps_layer, "STEPS");
  text_layer_set_background_color(s_text_steps_layer, GColorClear);
  text_layer_set_text_color(s_text_steps_layer, GColorWhite);
  layer_add_child(window_layer, text_layer_get_layer(s_text_steps_layer));
  text_layer_set_text_alignment(s_text_steps_layer, GTextAlignmentCenter);
  
  /// Steps Value
  s_steps_layer = text_layer_create(GRect(95,144, 46 ,20));
  layer_set_hidden((Layer *) s_steps_layer, true);
  text_layer_set_text_color(s_steps_layer, GColorBlack);
  text_layer_set_background_color(s_steps_layer, GColorClear);
  text_layer_set_text_alignment(s_steps_layer, GTextAlignmentCenter);
  text_layer_set_font(s_steps_layer, fonts_get_system_font(fonts[secondary_font]));
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_steps_layer));
    
  initializeConfig();   
}

static void main_window_unload(Window *window) {
  text_layer_destroy(s_time_layer); 
  text_layer_destroy(s_date_layer);
  text_layer_destroy(s_text_utc_offset_layer);
  text_layer_destroy(s_time_utc_offset_layer);
  text_layer_destroy(s_battery_layer);
  text_layer_destroy(s_text_steps_layer);
  text_layer_destroy(s_steps_layer);
}

static void inbox_received_callback(DictionaryIterator *iter, void *context) {

  Tuple *message_tuple = dict_find(iter, KEY_COLOR_BACKGROUND);
  if(message_tuple) {
    uint32_t background_int = message_tuple->value->int32;
    GColor background_color = GColorFromHEX(background_int);
    persist_write_int(KEY_COLOR_BACKGROUND, background_int);
    
    updateBackgroundColor(background_color);  
  }
  
  message_tuple = dict_find(iter, KEY_COLOR_PRIMARY);  
  if(message_tuple) {
    uint32_t primary_int = message_tuple->value->int32;
    GColor primary_color = GColorFromHEX(primary_int);
    persist_write_int(KEY_COLOR_PRIMARY, primary_int);

    updatePrimaryColor(primary_color);
  }  
  
  
  message_tuple = dict_find(iter, KEY_COLOR_SECONDARY);  
  if(message_tuple) {
    uint32_t secondary_int = message_tuple->value->int32;
    GColor secondary_color = GColorFromHEX(secondary_int);
    persist_write_int(KEY_COLOR_SECONDARY, secondary_int);    

    updateSecondaryColor(secondary_color);
  }
  
  message_tuple = dict_find(iter, KEY_TEXT_LABEL);  
  if(message_tuple) {
    char *custom_label = message_tuple->value->cstring;
    static char s_buffer[16];
    snprintf(s_buffer, sizeof(s_buffer), "%s", custom_label);
    persist_write_string(KEY_TEXT_LABEL, custom_label);    

    updateUtcOffsetLabel(s_buffer);
  }
  
  message_tuple = dict_find(iter, KEY_STRING_UTC_OFFSET);  
  if(message_tuple) {
    char *offset = message_tuple->value->cstring;
    utc_offset_int = atoi(offset);
    
    persist_write_int(KEY_STRING_UTC_OFFSET, utc_offset_int);
  }
  
  message_tuple = dict_find(iter, KEY_STRING_PRIMARY_FONT);  
  if(message_tuple) {
    char *font = message_tuple->value->cstring;
    primary_font = atoi(font);
    persist_write_int(KEY_STRING_PRIMARY_FONT, primary_font);

    updatePrimaryFont();
  }
  
  message_tuple = dict_find(iter, KEY_STRING_SECONDARY_FONT);  
  if(message_tuple) {
    char *font = message_tuple->value->cstring;
    secondary_font = atoi(font);
    persist_write_int(KEY_STRING_SECONDARY_FONT, secondary_font);

    updateSecondaryFont();
  }
  
  update_time();
}




static void init() {
  s_main_window = window_create();

  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload
  });

  // Show the Window on the watch, with animated=true
  window_stack_push(s_main_window, true);

  // Make sure the time is displayed from the start
  update_time();

  // Register with TickTimerService
  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);

  battery_state_service_subscribe(battery_handler);
  accel_tap_service_subscribe(&handle_accel_tap);
  
  is_hidden = false;
  
  app_message_register_inbox_received(inbox_received_callback);
  app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());
  
}

static void hideCallback(void *data) {
 is_hidden = !is_hidden;
 layer_set_hidden((Layer *) s_battery_layer, !is_hidden);
 layer_set_hidden((Layer *) s_time_utc_offset_layer, !is_hidden);
 layer_set_hidden((Layer *) s_text_utc_offset_layer, !is_hidden);
 layer_set_hidden((Layer *) s_text_steps_layer, !is_hidden);
 layer_set_hidden((Layer *) s_steps_layer, !is_hidden);  
}

static void handle_accel_tap(AccelAxisType axis, int32_t direction)
{
  hideCallback(NULL); 
  timer_hide = app_timer_register(2000 , (AppTimerCallback) hideCallback, NULL);
}

static void deinit() {
  // Destroy Window
  window_destroy(s_main_window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}