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

/** \file
	\brief Module for data structures and functions pertaining to the FSM representation of the elevator*/

/** \defgroup Elevator_FSM
	\brief Module for data structures and functions pertaining to the FSM representation of the elevator*/

/** \ingroup Elevator_FSM
	\struct elevatorStruct
	\brief A struct which works as the internal FSM representation of the elevator*/
typedef struct{
	int floor;
	state elevatorState;
	elev_motor_direction_t motor_direction;

} elevatorStruct;

/** \ingroup Elevator_FSM
	\brief Getter-function for the floor variable in the FSM*/
int elevator_FSM_get_floor();

/** \ingroup Elevator_FSM
	\brief Getter-function for the state variable in the FSM*/
state elevator_FSM_get_state();

/** \ingroup Elevator_FSM
	\brief Getter-function for the direction variable in the FSM*/
elev_motor_direction_t elevator_FSM_get_direction();

/** \ingroup Elevator_FSM
	\brief Setter-function for the floor variable in the FSM*/
void elevator_FSM_set_floor(int floor_in);

/** \ingroup Elevator_FSM
	\brief Setter-function for the state variable in the FSM*/
void elevator_FSM_set_state(state state_in);

/** \ingroup Elevator_FSM
	\brief Setter-function for the direction variable in the FSM*/
void elevator_FSM_set_direction(elev_motor_direction_t direction_in);

/** \ingroup Elevator_FSM
	\brief Initializing method for the FSM*/
void elevator_FSM_init();

/** \ingroup Elevator_FSM
	\brief Returns a bool signifying whether an order exists in the current travelling direction of the elevator*/
bool elevator_FSM_order_exists_in_same_dir();

/** \ingroup Elevator_FSM
	\brief Returns a bool signifying whether the elevator should stop moving*/
bool elevator_FSM_should_stop();

/** \ingroup Elevator_FSM
	\brief Returns the direction of order. If several exist, the lowest floor one is prioritized*/
elev_motor_direction_t elevator_FSM_direction_of_order();

/** \ingroup Elevator_FSM
	\brief Clears the lights in all the panels*/
void elevator_FSM_clear_lights();
