#include<time.h>


typedef struct {
	time_t time_elapsed;
	time_t time_start;
} timer_struct;

static time_t timer_threshold_time = 3;

static timer_struct timer;


void timer_reset();

void timer_start();

void timer_update();

time_t timer_get_time();