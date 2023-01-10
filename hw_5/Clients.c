#include "Clients.h"
#include "TimeDate.h"
#include "Checks.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*Generates and initializes an empty linked list of ClientNodes
*
* return : returns empty list of ClientNodes, with pointers to first and last elements set to NULL
* if successful, NULL otherwise*/
ClientList createClientList()
{
    ClientList list;
    list = (ClientList)malloc(sizeof(clientList));
    if(list == NULL) return NULL;
    list->first = NULL;
    list->last = NULL;
    return list;
}

/*Adds a new ClientNode containing given Client to the start of a list
*
* list - ClientList
* client - pointer to a Client
*
* returns 1 if ClientNode was added successfully, 0 otherwise*/
int client_addToStart(ClientList list, Client* client)
{
    if(list != NULL)
    {
        ClientNode* newNode;
        newNode = (ClientNode*)malloc(sizeof(ClientNode));
        if(newNode == NULL) return 0;
        newNode->client = client;
        newNode->next = list->first;
        list->first = newNode;
        if(newNode->next == NULL) list->last = newNode;
        return 1;
    }
    return 0;
}

/*Adds a new ClientNode containing given Client to the end of a list
*
* list - ClientList
* client - pointer to a Client
*
* returns 1 if ClientNode was added successfully, 0 otherwise*/
int client_addToEnd(ClientList list, Client* client)
{
    if(list != NULL)
    {
        ClientNode* newNode;
        newNode = (ClientNode*)malloc(sizeof(ClientNode));
        if(newNode == NULL) return 0;
        newNode->client = client;
        if(list->last != NULL )list->last->next = newNode;
        else list->first = newNode;
        list->last = newNode;
        newNode->next = NULL;
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
int isValidClient(char* name,char* last_name, char id[10], char reg[8],Date rent_date,Time rent_hour,short rate)
{
    if(isValidIdString(id))
    {
        if(hasNumDigitsString(reg,7))
        {
            if(is_valid_date(rent_date) && is_valid_time(rent_hour))
            {
                if(rate >= 0 && rate <=999) return 1;
            }
        }
    }
    return 0;
}

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
Client* generateClient(char* name,char* last_name, char id[10], char reg[8],Date rent_date,Time rent_hour,short rate)
{
    if(isValidClient(name,last_name,id,reg,rent_date,rent_hour,rate))
    {
        Client* client;
        client = (Client*)malloc(sizeof(Client));
        client->first_name = (char*)malloc(sizeof(strlen(name)+1));
        client->last_name = (char*)malloc(sizeof(strlen(last_name)+1));
        if(client == NULL || client->first_name == NULL || client->last_name == NULL) return NULL;
        strcpy(client->first_name,name);
        strcpy(client->last_name,last_name);
        strcpy(client->id ,id);
        strcpy(client->car_registration_num ,reg);
        client->s_rent_date = rent_date;
        client->s_rent_hour = rent_hour;
        client->rate_for_24hrs = rate;
        return client;
    }
    else
    {
        printf("\nError - invalid client information\n");
    }
    return NULL;
}

/*Returns pointer to a Client from list with given ID number
*
* list - ClientList
* id - Client ID
*
* returns requested Client if successful, NULL otherwise*/
Client* getClient(ClientList list,char id[10])
{
    if(list != NULL && list->first != NULL)
    {
        if(isValidIdString(id))
        {
            ClientNode* scan;
            scan = list->first;
            while(scan != NULL)
            {
                if(strcmp(id,scan->client->id) == 0) return scan->client;
                scan = scan->next;
            }
            scan = NULL;
        }
    }
    return NULL;
}

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
int addNewClient(ClientList list,char* name,char* last_name, char id[10], char reg[8],Date rent_date,Time rent_hour, short rate)
{
    if(list != NULL)
    {
        if(isValidClient(name,last_name,id,reg,rent_date,rent_hour,rate))
        {   
            Client* client = generateClient(name,last_name,id,reg,rent_date,rent_hour,rate);
            if(list->first == NULL)
            { 
                client_addToStart(list,client);
                return 1;
            }
            if(strcmp(client->id,list->first->client->id) <=0)
            {
                client_addToStart(list,client);
                return 1;
            }
            else if(strcmp(client->id,list->last->client->id) >=0)
            {
                client_addToEnd(list,client);
                return 1;
            }
            else
            {
                ClientNode* scan;
                ClientNode* newNode;
                newNode = (ClientNode*)malloc(sizeof(ClientNode));
                if(newNode == NULL) return 0;
                newNode->client = client;
                scan = list->first;
                while(strcmp(client->id,scan->client->id) < 0) scan = scan->next;
                newNode->next = scan->next;
                scan->next = newNode;
                return 1;
            }            
        }
        else printf("\nError - invalid Client\n");
    }
    else printf("\nError - null pointer to Client list\n");
    return 0;
}


/*Deletes a ClientNode containing Client with given ID number from the list
*
* list - client list
* id : given client ID number
*
* return : returns 1 if operation succeeded,0 otherwise*/
int deleteClient(ClientList list,char id[10])
{
    if(list != NULL && list->first != NULL && isValidIdString(id) && strcmp(id,list->first->client->id) >= 0 && strcmp(id,list->last->client->id) <= 0)
    {
        ClientNode* scan;
        scan = list->first;
        if(strcmp(list->first->client->id,id) == 0)
        {
            list->first = scan->next;
            free(scan->client);
            free(scan);
            return 1;
        }
        else if(strcmp(list->last->client->id,id) == 0)
        {
            while(scan->next != list->last) scan = scan->next;
            list->last = scan;
            free(scan->next->client);
            free(scan->next);
            list->last->next = NULL;
            return 1;
        }
        else if(list->first->next == NULL && strcmp(list->first->client->id,id) != 0) return 0;
        else
        {
            ClientNode* temp;
            while((strcmp(scan->next->client->id,id) != 0) && scan->next->next != NULL) scan = scan->next;
            if(scan->next == list->last) return 0;
            temp = scan->next;
            scan->next = temp->next;
            free(temp->client);
            free(temp);
            return 1;
        }
    }
    return 0;
}

/*Deletes all ClientNodes from the list
*
* list : client list
*
* return : returns 1 if operation succeeded,0 otherwise*/
int deleteAllClients(ClientList list)
{
    if(list != NULL)
    {
        if(list->first == NULL) return 1;
        else
        {
            ClientNode* scan;
            scan = list->first;
            while(scan != NULL)
            {
                ClientNode* temp = scan;
                list->first = scan->next;
                scan = scan->next;
                free(temp->client);
                free(temp);
            }
            list->first = NULL;
            list->last = NULL;
            return 1;
        }
    }
    else printf("\nError - null pointer to Client list\n");
    return 0;
}

#ifdef DAVIS
/*Prints all clients who rented a car on a specified date; AVAILABLE TO DAVIS ONLY
*
* list - client list
* date - date of rental
*
* returns 1 if successful, 0 otherwise*/
int printClientCarsForGivenRentDate(ClientList list,Date date)
{
    if(list != NULL && list->first != NULL && is_valid_date(date))
    {
        ClientNode* scan;
        int numclients;
        numclients = 0;
        scan = list->first;
        while(scan != NULL)
        {
            if(dateCompare(scan->client->s_rent_date,date)) 
            {
                printClient(*scan->client);
                numclients++;
            }
            scan = scan->next;
        }
        scan = NULL;
        return numclients;
    }
    return 0;
}
#endif


/*Prints information for given Client
*
* client - given client
*
* returns 1 always*/
int printClient(Client client)
{
    printf("{name:%s last name:%s id:%s car_reg:%s s_rent_date:%s s_rent_hour:%s rate:%d}\n",client.first_name,client.last_name,client.id,client.car_registration_num,date_string(client.s_rent_date),time_string(client.s_rent_hour),client.rate_for_24hrs);
    return 1;
}
