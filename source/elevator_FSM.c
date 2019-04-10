#include"elevator_FSM.h"
#include<stdio.h>
#include<assert.h>

elevatorStruct elevator;

bool order_exists_above();

bool order_exists_below();

int elevator_FSM_get_floor(){
	return elevator.floor;
}

state elevator_FSM_get_state(){
	return elevator.elevatorState;
}

elev_motor_direction_t elevator_FSM_get_direction(){
	return elevator.motor_direction;
}

void elevator_FSM_set_floor(int floor_in){
	if (floor_in < 0 || floor_in > 3){
		printf("HER SKJER FEILEN!!!!!!!!!!\n");
		return;
	}
	elevator.floor = floor_in;
}

void elevator_FSM_set_state(state state_in){
	elevator.elevatorState = state_in;
}

void elevator_FSM_set_direction(elev_motor_direction_t direction_in){
	elevator.motor_direction = direction_in;
	printf("retning er %d inni elev_set_direction\n", elevator.motor_direction);
	elev_set_motor_direction(elevator.motor_direction);
}

void elevator_FSM_init(){
	while(elev_get_floor_sensor_signal() == -1);
	elevator.motor_direction = DIRN_STOP;
	elev_set_motor_direction(elevator.motor_direction);
	elevator.elevatorState = Idle;
	elevator.floor = elev_get_floor_sensor_signal();
}

bool elevator_FSM_order_exists_in_same_dir(){
	for(int i = 0; i < 4; ++i){
		if(elevator.floor < i && elevator.motor_direction == DIRN_UP && orders_get(i, BUTTON_CALL_UP)){
			return true;
		}
		if(elevator.floor > i && elevator.motor_direction == DIRN_DOWN && orders_get(i, BUTTON_CALL_DOWN)){
			return true;
		}
	}
	return false;
}

bool elevator_FSM_should_stop(){
	if(elev_get_floor_sensor_signal() != -1){
		if(orders_get(elev_get_floor_sensor_signal(),elevator_FSM_direction_to_button_type(elevator_FSM_get_direction()))){
			printf("elevator_should_stop gikk av på naivt tilfelle\n");
			return true;
		}else{
			switch(elevator_FSM_get_direction()){
				case DIRN_UP:
				if(!order_exists_above()){
					printf("elevator_should_stop gikk av på dirn_up\n");
					return true;
				}
				break;
				case DIRN_DOWN:
				if(!order_exists_below()){
					printf("elevator_should_stop gikk av på dirn_down\n");
					return true;
				}
				break;
				default:
				return false;
			}
		}
	}else{
		return false;
	}
	return false;
}

elev_motor_direction_t elevator_FSM_direction_of_order(){
	for(int i = 0; i < 4; ++i){
		if(orders_get(i, BUTTON_CALL_UP) || orders_get(i, BUTTON_CALL_DOWN)){
			if(i < elevator.floor){
				return DIRN_DOWN;
			} else if(i > elevator.floor){
				return DIRN_UP;
			}
		}
	}
	return DIRN_STOP;
}

void elevator_FSM_clear_lights(){
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 3; j++){
			if(!(i == 0 && j == BUTTON_CALL_DOWN) && !(i == 3 && j == BUTTON_CALL_UP)){
				elev_set_button_lamp(j,i,0);
			}
		}
	}
	elev_set_door_open_lamp(0);
}

elev_button_type_t elevator_FSM_direction_to_button_type(elev_motor_direction_t input){
	switch(input){
		case DIRN_DOWN:
			return BUTTON_CALL_DOWN;
		case DIRN_UP:
			return BUTTON_CALL_UP;
		default:
			return BUTTON_CALL_DOWN;
	}
}

bool order_exists_above(){
	if(elev_get_floor_sensor_signal() == 3){
		return false;
	}
	for(int i = elev_get_floor_sensor_signal() + 1; i < 4; i++){
		if(orders_get(i, BUTTON_CALL_DOWN) || orders_get(i, BUTTON_CALL_UP)){
			return true;
		}
	}
	return false;
}

bool order_exists_below(){
	if(elev_get_floor_sensor_signal() == 0){
		return false;
	}
	for(int i = elev_get_floor_sensor_signal() - 1; i > -1; i--){
		if(orders_get(i, BUTTON_CALL_DOWN) || orders_get(i, BUTTON_CALL_UP)){
			return true;
		}
	}
	return false;
}
