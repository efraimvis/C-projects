#ifndef COMMON_H
#define COMMON_H

#include "Cars.h"
#include "Clients.h"

/*Returns number of clients with cars of given year
* 
* client_list : client list
* car_list : car list
* year : year of manufacture
*
* return : returns number of clients with cars of given year, on error returns -1*/
int clientNumberWithGivenCarYear(ClientList client_list,CarList car_list,char year[5]);

#endif