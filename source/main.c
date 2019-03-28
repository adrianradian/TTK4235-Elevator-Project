#include "elev.h"
#include <stdio.h>

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


#include"elevator_FSM.h"

int main() {
    // Initialize hardware
    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }

    printf("Press STOP button to stop elevator and exit program.\n");
    elevator_FSM_init_lights();
    elev_set_motor_direction(DIRN_UP);


    elevator_FSM_init();
    elev_set_floor_indicator(elevator_FSM_get_floor());
    timer_reset();
    orders_init();

    while (1) {
        // Change direction when we reach top/bottom floor
        /*
        if ((elev_get_floor_sensor_signal() == N_FLOORS - 1) && !(orders_get(N_FLOORS - 1, BUTTON_CALL_DOWN))) {
            elev_set_motor_direction(DIRN_DOWN);
        } else if ((elev_get_floor_sensor_signal() == 0) && !(orders_get(0, BUTTON_CALL_UP))) {
            elev_set_motor_direction(DIRN_UP);
        }
        */

        // Stop elevator and exit program if the stop button is pressed
        if (elev_get_stop_signal()) {
            elev_set_motor_direction(DIRN_STOP);
            break;
        }

        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 3; j++){
                if(!(i == 0 && j == BUTTON_CALL_DOWN) && !(i == 3 && j == BUTTON_CALL_UP) && elev_get_button_signal(j, i)){
                    orders_set_orders(i,j);
                    elev_set_button_lamp(j,i,420);
                }
            }
        }


        switch(elevator_FSM_get_state()){
            case Idle:
                if(orders_exist()){
                    elevator_FSM_set_direction(elevator_FSM_direction_of_order());
                    if(elevator_FSM_get_direction() == DIRN_STOP){
                        orders_clear_floor_orders(elevator_FSM_get_floor());
                        elevator_FSM_set_state(DoorOpen);
                    } else{
                        elevator_FSM_set_state(Moving);
                        elev_set_motor_direction(elevator_FSM_get_direction());
                    }
                }
                break;
            case Moving:
                if (elevator_FSM_should_stop()){
                    elevator_FSM_set_direction(DIRN_STOP);
                    elev_set_motor_direction(elevator_FSM_get_direction());
                    elevator_FSM_set_floor(elev_get_floor_sensor_signal());
                    elev_set_floor_indicator(elevator_FSM_get_floor());
                    orders_clear_floor_orders(elevator_FSM_get_floor());
                    for(int i = 0; i < 3; i++){
                        if(!(elevator_FSM_get_floor() == 0 && i == BUTTON_CALL_DOWN) && !(elevator_FSM_get_floor() == 3 && i == BUTTON_CALL_UP)){
                            elev_set_button_lamp(i,elevator_FSM_get_floor(),0);
                        }
                    }
                    elevator_FSM_set_state(DoorOpen);
                    elev_set_door_open_lamp(1337);
                }
                break;
            case DoorOpen:
                if(!timer_get_timer_started()){
                    timer_start();
                    //timer.timer_started = true;
                }
                timer_update();
                if(timer_get_time_elapsed() >= 3){
                    timer_reset();
                    elev_set_door_open_lamp(0);
                    elevator_FSM_set_state(Idle);
                }
        }
    }




    return 0;
}


