#ifndef CLIENTS_H
#define CLIENTS_H
#include "TimeDate.h"
#include "Tree.h"

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


/*Generates and initializes an empty Tree
*
* return : returns empty Tree, with root set to NULL
* if successful, NULL otherwise*/
Tree createClientTree();

/*Prompts user for Client information and adds a new Client to a given Tree
*
* tree - given Tree
*
* returns 1 if successful, 0 otherwise and prints an error message*/
int inputClient(Tree tree);

int addNewClient_list(ClientList list,Client* client);

/*Compares two given Clients based on ID
*
* client1, client2 - given Clients
*
* return : returns negative value if client1 has a smaller ID number,
* positive value if client1 has larger ID number, 0 if Clients have the same ID number*/
int clientCompare(const void* client1, const void* client2);

/*Generates and initializes an empty linked list of ClientNodes
*
* return : returns empty list of ClientNodes, with pointers to first and last elements set to NULL
* if successful, NULL otherwise*/
ClientList createClientList();

/*Adds a new TreeNode containing a Client to given Tree
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
int addNewClient(Tree tree,char* name,char* last_name, char id[10], char reg[8],Date rent_date,Time rent_hour, short rate);

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


/*Deletes a TreeNode containing Client with given ID number from the Tree
*
* tree - Tree
* id : given ID number
*
* return : returns 1 if operation succeeded,0 otherwise*/
int deleteClient(Tree tree,char id[10]);

/*Deletes all TreeNodes from the Tree
*
* tree : Tree
*
* return : returns 1 if operation succeeded,0 otherwise*/
int deleteAllClients(Tree tree);

/*Prints information for given Client
*
* client - given client
*
* returns 1 always*/
int printClient(Client client);

/*Returns pointer to a Client with given ID number from Tree
*
* tree - Tree
* id - Client ID number
*
* returns requested Client if successful, NULL otherwise*/
Client* getClient(Tree tree,char id[10]);

/*Finds all Clients by specified ID number, or date of rental
*
* tree - given Tree
* key - string with which to search Tree; can be either a 9 digit ID number, or a date in format dd/mm/yyyy
*
* return : returns a ClientList of Clients found by searching Tree either by Client ID, or date of rental*/
ClientList findClient(Tree tree, char* key);

/*Prints all clients who rented a car on a specified date
*
* tree - given Tree
* date - date of rental
*
* returns 1 if successful, 0 otherwise*/
int printClientCarsForGivenRentDate(Tree tree,Date date);

#endif