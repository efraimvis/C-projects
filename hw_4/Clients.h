#ifndef CLIENTS_H
#define CLIENTS_H
#include "TimeDate.h"
#define M 8000

typedef struct CClient 
{
    char first_name[21];
    char last_name[21];
    char id[10];
    char car_registration_num[8];
    Date s_rent_date;
    Time s_rent_hour;
    short rate_for_24hrs;
} Client;

/*Generates a default client and initialize default values
*
* return : returns client with default parameters*/
Client createDefaultClient();

/*Initializes an array of Clients
*
* list : pointer to a list of Clients 
*
* return : returns 1 if operation succeeded, 0 otherwise*/
int createClientList(Client* list);

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
int addNewClient(Client* list,char name[21],char last_name[21], char id[10], char reg[8],Date rent_date,Time rent_hour, short rate);

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
int isValidClient(char name[21],char last_name[21], char id[10], char reg[8],Date rent_date,Time rent_hour, short rate);


/*Removes a client with given id from the list
*
* client_list : client list
* id : client id
*
* return : returns 1 if operation succeed,prints an error mwssage and returns 0 otherwise*/
int deleteClient(Client* list,char id[10]);

/*Removes all clients from the list
*
* client_list : client list
*
* return : returns 1 if operation succeeded,prints an error message and returns 0 otherwise*/
int deleteAllClients(Client* list);

/*Prints to screen client information
*
* client : client
*
* return : returns 1 */
int printClient(Client client);

#endif