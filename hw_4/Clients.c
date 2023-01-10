#include "Clients.h"
#include "TimeDate.h"
#include "Checks.h"
#include <stdio.h>
#include <string.h>

#define D_F_NAME "default_first_name__"
#define D_L_NAME "default_last_name___"
#define D_ID "default00"
#define D_REG_NUM "default"

/*Generates a default client and initialize default values
*
* return : returns client with default parameters*/
Client createDefaultClient()
{
    Client client;
    strcpy(client.first_name,D_F_NAME);
    strcpy(client.last_name, D_L_NAME);
    strcpy(client.id,D_ID);
    strcpy(client.car_registration_num,D_REG_NUM);
    client.s_rent_date = default_date();
    client.s_rent_hour = default_time();
    client.rate_for_24hrs = 0;
    return client;
}

/*Initializes an array of Clients with default values
*
* list : pointer to a list of Clients 
*
* return : returns 1 if operation succeeded, 0 otherwise*/
int createClientList(Client* list)
{
    if(list != NULL)
    {
        int i;
        for(i=0;i<M;i++)
        {
            list[i] = createDefaultClient();
        }
        return 1;
    }
    return 0;
}

/*Checks if all client information is valid
*
* name : client name
* last_name : client last name
* id : client id
* reg : registration number of rental car
* rent_date : date of start of rental
* rent_hour : hour of start of rental
* rate : rental rate for 24 hours
*
* return : returns 1 if client information is correct, 0 otherwise*/
int isValidClient(char name[21],char last_name[21], char id[10], char reg[8],Date rent_date,Time rent_hour,short rate)
{
    if(isValidIdString(id))
    {
        if((strlen(name)<= 20 && strcmp(name,D_F_NAME) != 0) && (strlen(last_name)<= 20 && strcmp(last_name,D_L_NAME) != 0))
        {
            if(hasNumDigitsString(reg,7))
            {
                if(is_valid_date(rent_date) && is_valid_time(rent_hour))
                {
                    if(rate >= 0 && getNumDigits(rate) <= 3) return 1;
                }
            }
        }
    }
    return 0;
}

/*Adds new client with given information to list
*
* name : client name
* last_name : client last name
* id : client id
* reg : registration number of rental car
* rent_date : date of start of rental
* rent_hour : hour of start of rental
* rate : rental rate for 24 hours
*
* return : returns 1 if operation succeeded, prints an error message and return 0 otherwise*/
int addNewClient(Client* list,char name[21],char last_name[21], char id[10], char reg[8],Date rent_date,Time rent_hour, short rate)
{
    if(list != NULL)
    {
        if(isValidClient(name,last_name,id,reg,rent_date,rent_hour,rate))
        {
            int i;
            i=0;
            while((strcmp(list[i].id,D_ID) != 0) && i<M)
            {
                if(!strcmp(list[i].id,id)) return 0;
                i++;
            }
            if(i<M)
            {
                strcpy(list[i].first_name,name);
                strcpy(list[i].last_name ,last_name);
                strcpy(list[i].id ,id);
                strcpy(list[i].car_registration_num ,reg);
                list[i].s_rent_date = rent_date;
                list[i].s_rent_hour = rent_hour;
                list[i].rate_for_24hrs = rate;
                return 1;
            }
        }
        else printf("\nError - invalid Client\n");
    }
    else printf("\nError - null pointer to Client list\n");
    return 0;
}


/*Removes a client with given id from the list
*
* client_list : client list
* id : client id
*
* return : returns 1 if operation succeed,prints an error mwssage and returns 0 otherwise*/
int deleteClient(Client* list,char id[10])
{
    if(list != NULL && isValidIdString(id))
    {
        int i;
        i=0;
        while((strcmp(list[i].id,id) != 0) && i<M) i++;
        if(i<M)
        {
            list[i] = createDefaultClient();
            return 1;
        }
        else printf("\nError - Client not found\n");
    }
    else printf("\nError - null pointer to Client list\n");
    return 0;
}

/*Removes all clients from the list
*
* client_list : client list
*
* return : returns 1 if operation succeeded,prints an error message and returns 0 otherwise*/
int deleteAllClients(Client* list)
{
    if(list != NULL)
    {
        createClientList(list);
        return 1;
    }
    else printf("\nError - null pointer to Client list\n");
    return 0;
}

/*Prints to screen client information
*
* client : client
*
* return : returns 1 */
int printClient(Client client)
{
    printf("{name:%s last name:%s id:%s car_reg:%s s_rent_date:%02d:%02d:%04d s_rent_hour:%02d:%02d rate:%d}\n",client.first_name,client.last_name,client.id,client.car_registration_num,client.s_rent_date.day,client.s_rent_date.month,client.s_rent_date.year,client.s_rent_hour.hours,client.s_rent_hour.minutes,client.rate_for_24hrs);
    return 1;
}
