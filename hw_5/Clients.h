#ifndef CLIENTS_H
#define CLIENTS_H
#include "TimeDate.h"

int printClientCarsForGivenRentDate();

typedef struct CClient 
{
    char* first_name;
    char* last_name;
    char id[10];
    char car_registration_num[8];
    Date s_rent_date;
    Time s_rent_hour;
    short rate_for_24hrs;
} Client;

typedef struct ClientNode
{
    Client* client;
    struct ClientNode* next;
} ClientNode;

typedef struct clientList
{
    ClientNode* first;
    ClientNode* last;
} clientList;

typedef struct clientList* ClientList;


/*Generates and initializes an empty linked list of ClientNodes
*
* return : returns empty list of ClientNodes, with pointers to first and last elements set to NULL
* if successful, NULL otherwise*/
ClientList createClientList();

/*Adds a new ClientNode containing a Client to list of clients
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
int addNewClient(ClientList list,char* name,char* last_name, char id[10], char reg[8],Date rent_date,Time rent_hour, short rate);

/*Creates a Client from given information
*
* name : client name
* last_name : client last name
* id : client id
* reg : registration number of rental car
* rent_date : date of start of rental
* rent_hour : hour of start of rental
* rate : rental rate for 24 hours
*
* returns pointer to Client with given information if successful, NULL otherwise*/
Client* generateClient(char* name,char* last_name, char id[10], char reg[8],Date rent_date,Time rent_hour, short rate);

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
int isValidClient(char* name,char* last_name, char id[10], char reg[8],Date rent_date,Time rent_hour, short rate);


/*Deletes a ClientNode containing Client with given ID number from the list
*
* list - client list
* id : given client ID number
*
* return : returns 1 if operation succeeded,0 otherwise*/
int deleteClient(ClientList list,char id[10]);

/*Deletes all ClientNodes from the list
*
* list : client list
*
* return : returns 1 if operation succeeded,0 otherwise*/
int deleteAllClients(ClientList list);

/*Prints information for given Client
*
* client - given client
*
* returns 1 always*/
int printClient(Client client);

/*Returns pointer to a Client from list with given ID number
*
* list - ClientList
* id - Client ID
*
* returns requested Client if successful, NULL otherwise*/
Client* getClient(ClientList list,char id[10]);

#endif