#ifndef INCLUDE_ELEV
#include"elev.h"
#define INCLUDE_ELEV
#endif

#ifndef INCLUDE_BOOL
#include <stdbool.h>
#define INCLUDE_BOOL
#endif



void orders_init();

void orders_set_orders(int floor, elev_button_type_t type);

void orders_clear_floor_orders(int floor);

bool orders_get(int floor, elev_button_type_t direction);

bool orders_exist();