#include <stdio.h>
#include <string.h>
#include "Checks.h"
#include "Cars.h"
#include "Common.h"
#include "Clients.h"


/*Returns year of manufacture for car by registration number
*
* list : car list
* reg : registration number
*
* return : returns year of manufacture for car with given registration, on error returns "0000"*/
char* getCarYear(Car* list,char reg[8])
{
    if(list != NULL && hasNumDigitsString(reg,7))
    {
        int i;
        for(i=0;i<N;i++)
        {
            if(!strcmp(reg,list[i].registration_num)) return list[i].y_of_manufacture;
        }
    }
    return "0000";
}

/*Returns number of clients with cars of given year
* 
* client_list : client list
* car_list : car list
* year : year of manufacture
*
* return : returns number of clients with cars of given year, on error returns -1*/
int clientNumberWithGivenCarYear(Client* client_list,Car* car_list,char year[5])
{
    if(client_list != NULL && car_list != NULL && isValidYear(year))
    {
        int i;
        int counter;
        char* car_year;
        char reg_num[8];
        counter = 0;
        for(i=0;i<M;i++)
        {
            strcpy(reg_num,client_list[i].car_registration_num);
            car_year = getCarYear(car_list,reg_num);
            if(strcmp(year,car_year) == 0) counter++;
        }
        return counter;
    }
    else printf("\nError - null pointer to list or invalid year\n");
    return -1;
}