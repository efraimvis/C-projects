#ifndef COMMON_H
#define COMMON_H

#include "Clients.h"
#include "Cars.h"

/*Returns number of clients with cars of given year
* 
* client_list : client list
* car_list : car list
* year : year of manufacture
*
* return : returns number of clients with cars of given year, on error returns -1*/
int clientNumberWithGivenCarYear(Client* client_list,Car* car_list,char year[5]);

/*Returns year of manufacture for car by registration number
*
* list : car list
* reg : registration number
*
* return : returns year of manufacture for car with given registration, on error returns "0000"*/
char* getCarYear(Car* list,char reg[8]);

#endif