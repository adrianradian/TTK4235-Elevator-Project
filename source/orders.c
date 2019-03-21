#include "orders.h"

void orders_init(){
	for(int i = 0; i < 4; ++i){
		for(int j = 0; j < 3; ++j){
			orders[i][j] = false;
		}
	}
}

void orders_set_orders(int floor, elev_button_type_t type){ orders[floor][(int)type] = true; }

void orders_clear_floor_orders(int floor){
	for(int i = 0; i < 3; i++){
		orders[floor][i] = false;
	}
}

bool orders_get(int floor, elev_button_type_t direction){ return (orders[floor][(int)BUTTON_COMMAND] || orders[floor][(int)direction]); }

bool orders_exist(){
	bool temp = false;
	for(int i = 0; i < 4; ++i){
		for(int j = 0; j < 3; ++j){
			temp = temp && orders[i][j];
		}
	}
	return temp;
}