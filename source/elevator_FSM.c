#include"elevator_FSM.h"

void elevator_FSM_init(){
	while(elev_get_floor_sensor_signal() == -1);
	elevator.floor = elev_get_floor_sensor_signal();
	elevator.elevatorState = Idle;
	elevator.motor_direction = DIRN_STOP;
	elev_set_motor_direction(elevator.motor_direction);
}

bool elevator_FSM_order_exists_in_same_dir(){
	for(int i = 0; i < 4; ++i){
		if(elevator.floor < i && elevator.motor_direction == DIRN_UP && orders_get(i, DIRN_UP)){
			return true;
		}
		if(elevator.floor > i && elevator.motor_direction == DIRN_DOWN && orders_get(i, DIRN_DOWN)){
			return true;
		}
	}
	return false;
}

bool elevator_FSM_should_stop(){
	return ((elev_get_floor_sensor_signal() != -1) && orders_get(elev_get_floor_sensor_signal(),elevator.motor_direction));
}

elev_motor_direction_t elevator_FSM_direction_of_order(){
	for(int i = 0; i < 4; ++i){
		if(orders_get(i, DIRN_UP) || orders_get(i,DIRN_DOWN)){
			if(i < elevator.floor){
				return DIRN_DOWN;
			} else if(i > elevator.floor){
				return DIRN_UP;
			} else{
				return DIRN_STOP;
			}
		}
	}
}