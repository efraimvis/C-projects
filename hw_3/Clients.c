#include "Clients.h"
#include "TimeDate.h"
#include "Checks.h"
#include <stdio.h>
#define M 8000

/*Generates and initializes an M sized array of Clients
*
* return : returns an array of Clients*/
Client createClientList[M](){}

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
* return : returns 1 if operation succeeded, 0 otherwise*/
int addNewClient(char name[20],char last_name[20], char id[9], char reg[7],Date rent_date,Time rent_hour, unsigned short rate){}

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
int isValidClient(char name[20],char last_name[20], char id[9], char reg[7],Date rent_date,Time rent_hour, unsigned short rate){}

/*Returns number of clients with cars of given year
* 
* client_list : client list
* year : given year
*
* return : returns number of clients with cars of given year, -1 otherwise*/
int clientNumberWithGivenCarYear(Client client_list[],char year[4]){}

/*Removes a client with given id from the list
*
* client_list : client list
* id : client id
*
* return : returns 1 if operation succeed, 0 otherwise*/
int deleteClient(Client client_list[],char id[9]){}

/*Removes all clients from the list
*
* client_list : client list
*
* return : returns 1 if operation succeeded, 0 otherwise*/
int deleteAllClients(Client client_list[]){}
