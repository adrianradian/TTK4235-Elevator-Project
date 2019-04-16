#ifndef INCLUDE_ELEV
#include"elev.h"
#define INCLUDE_ELEV
#endif

#ifndef INCLUDE_BOOL
#include <stdbool.h>
#define INCLUDE_BOOL
#endif

/*! \file
    \brief Module for functions and data structures pertaining to placing and reading orders*/

/** \brief Clears all existing entries in orders-matrix. Also works as the initializing method for the orders-matrix*/
void orders_clear_all();

/** \brief Setter-function for orders*/
void orders_set_order(int floor, elev_button_type_t button_type);

/** \brief Clears all orders on a given floor*/
void orders_clear_floor_orders(int floor);

/** \brief Getter-function for orders*/
bool orders_get_order(int floor, elev_button_type_t direction);

/** \brief Returns a bool signifying whether any unhandled orders currently exist*/
bool orders_exist();
