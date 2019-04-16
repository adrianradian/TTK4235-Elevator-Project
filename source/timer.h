#include<time.h>

#ifndef INCLUDE_BOOL
#include <stdbool.h>
#define INCLUDE_BOOL
#endif

/** \file
	\brief Module for functions and data structures pertaining to timer functionality*/

/** \defgroup Timer
	\brief Module for functions and data structures pertaining to timer functionality*/

/** \ingroup Timer
	\struct timer_struct
	\brief Struct representing the timer*/
typedef struct {
	time_t time_elapsed;
	time_t time_start;
	bool is_timer_started;
} timer_struct;

/** \ingroup Timer
	\brief Method for stopping and resetting the timer. Also works as initializing function*/
void timer_reset();

/** \ingroup Timer
	\brief Method for starting the timer*/
void timer_start();

/** \ingroup Timer
	\brief Method for updating the timer*/
void timer_update();

/** \ingroup Timer
	\brief Getter-function for time elapsed since timer was started*/
time_t timer_get_time_elapsed();

/** \ingroup Timer
	\brief Method returning a bool signifying whether the timer is currently running*/
bool timer_get_is_timer_started();
