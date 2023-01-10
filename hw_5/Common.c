#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Checks.h"
#include "Common.h"

/*Returns number of clients with cars of given year
* 
* client_list : client list
* car_list : car list
* year : year of manufacture
*
* return : returns number of clients with cars of given year, on error returns -1*/
int clientNumberWithGivenCarYear(ClientList client_list,CarList car_list,char year[5])
{
    if(client_list != NULL && client_list->first != NULL && car_list != NULL && car_list->first != NULL &&isValidYear(year))
    {
        int counter;
        counter = 0;
        {
            ClientNode* scan;
            scan = client_list->first;
            while(scan != NULL)
            {
                Car* car;
                car = getCar(car_list,scan->client->car_registration_num);
                if(car != NULL)
                {
                    if(strcmp(car->y_of_manufacture,year) == 0) counter++;
                }
                scan = scan->next;
            }
        }
        return counter;
    }
    else printf("\nError - null pointer to list or invalid year\n");
    return -1;
}