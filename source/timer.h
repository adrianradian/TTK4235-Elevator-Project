#include<time.h>

#ifndef INCLUDE_BOOL
#include <stdbool.h>
#define INCLUDE_BOOL
#endif

typedef struct {
	time_t time_elapsed;
	time_t time_start;
	bool is_timer_started;
} timer_struct;

//time_t timer_threshold_time = 3;

timer_struct timer;

void timer_reset();

void timer_start();

void timer_update();

time_t timer_get_time_start();

time_t timer_get_time_elapsed();

//time_t timer_get_threshold_time();

bool timer_get_is_timer_started();
