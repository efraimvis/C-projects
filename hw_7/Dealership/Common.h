#ifndef COMMON_H
#define COMMON_H

#include "Cars.h"
#include "Clients.h"

/*Returns number of clients with cars of given year of manufacture
* 
* clientTree : Client Tree
* carTree : Car Tree
* year : given year of manufacture
*
* return : returns number of Clients with Cars of given year of manufacture, on error returns -1 and prints message*/
int clientNumberWithGivenCarYear(Tree clientTree,Tree carTree,char year[5]);

#endif