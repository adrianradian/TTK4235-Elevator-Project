#include "timer.h"

void timer_reset(){
	timer.time_start = NULL;
	timer.time_elapsed = NULL;
}

void timer_start(){
	timer.time_start = time(NULL);
	timer.time_elapsed = 0;
}

void timer_update(){
	timer.time_elapsed = time(NULL) - time_start;
}

time_t timer_get_time(){
	return timer.time_elapsed;
}