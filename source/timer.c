#include "timer.h"

void timer_reset(){
	timer.time_start = 0;
	timer.time_elapsed = 0;
	timer.is_timer_started = false;
}

void timer_start(){
	timer.time_start = time(NULL);
	timer.time_elapsed = 0;
	timer.is_timer_started = true;
}

void timer_update(){
	timer.time_elapsed = time(NULL) - timer.time_start;
}


time_t timer_get_time_start(){
	return timer.time_start;
}

time_t timer_get_time_elapsed(){
	return timer.time_elapsed;
}

bool timer_get_is_timer_started(){
	return timer.is_timer_started;
}

/*time_t timer_get_threshold_time(){
	return timer_threshold_time;
}
*/
