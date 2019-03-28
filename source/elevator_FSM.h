#ifndef INCLUDE_IO
#include"io.h"
#define INCLUDE_IO
#endif

#ifndef INCLUDE_ORDERS
#include"orders.h"
#define INCLUDE_ORDERS
#endif

#ifndef INCLUDE_TIMER
#include"timer.h"
#define INCLUDE_TIMER
#endif

#ifndef INCLUDE_BOOL
#include <stdbool.h>
#define INCLUDE_BOOL
#endif

#ifndef INCLUDE_ELEV
#include"elev.h"
#define INCLUDE_ELEV
#endif

typedef enum{Idle = 0, Moving = 1, DoorOpen = 2} state;

typedef struct{
	int floor;
	state elevatorState;
	elev_motor_direction_t motor_direction;	

} elevatorStruct;

elevatorStruct elevator;

void elevator_FSM_init();

bool elevator_FSM_order_exists_in_same_dir();

bool elevator_FSM_should_stop();

elev_motor_direction_t elevator_FSM_direction_of_order();

void elevator_FSM_init_lights();

elev_button_type_t elevator_FSM_direction_to_button_type(elev_motor_direction_t input);