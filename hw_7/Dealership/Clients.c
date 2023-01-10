#include "Clients.h"
#include "Checks.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*Compares two Clients by rent date
*
* client1, client2 - Clients, passed as void* 
*
* return : returns negative value if date for client1 is earlier, 0 if date is the same, positive value otherwise*/
int compareByDate(const void* client1, const void* client2)
{
    if(client1 && client2)
    {
        return dateCompare(((Client*)client1)->s_rent_date,((Client*)client2)->s_rent_date);
    }
    return 0;
}

/*Generates and initializes an empty Tree
*
* return : returns empty Tree, with root set to NULL
* if successful, NULL otherwise*/
Tree createClientTree()
{
    return createTree();
}

/*Compares two given Clients based on ID
*
* client1, client2 - given Clients
*
* return : returns negative value if client1 has a smaller ID number,
* positive value if client1 has larger ID number, 0 if Clients have the same ID number*/
int clientCompare(const void* client1, const void* client2)
{
    return strcmp(((Client*)client1)->id,((Client*)client2)->id);
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

/*Returns pointer to a Client with given ID number from Tree
*
* tree - Tree
* id - Client ID number
*
* returns requested Client if successful, NULL otherwise*/
Client* getClient(Tree tree,char id[10])
{
    if(tree != NULL && isValidIdString(id))
    {
        if(tree->root != NULL)
        {
            Tree node;
            Client* dummy;
            Client* returnClient;
            dummy = (Client*)malloc(sizeof(Client));
            if(!dummy) return NULL;
            strcpy(dummy->id,id);
            node = findNode(tree,dummy,sizeof(Client),clientCompare);
            if(node == NULL || node->root == NULL)
            {
                free(dummy);
                free(node);
                dummy = NULL;
                node = NULL;
                return NULL;
            }
            returnClient = (Client*)node->root->value;
            free(dummy);
            free(node);
            dummy = NULL;
            node = NULL;
            return returnClient;
        }
    }
    return NULL;
}

/*Finds all Clients by specified ID number, or date of rental - and returns a linked list of TreeNodes containing those clients
*
* tree - given Tree
* key - string with which to search Tree; can be either a 9 digit ID number, or a date in format dd/mm/yyyy
*
* return : returns a linked list (degenerated Tree) of Clients found by searching Tree either by Client ID, or date of rental*/
Tree findClient(Tree tree,char* key)
{
    if(tree != NULL && tree->root != NULL)
    {
        Tree list;
        Client* dummy;
        dummy = (Client*)malloc(sizeof(Client));
        list = createTree();
        if(!list || !dummy) return NULL;
        if(isValidIdString(key))
        {
            strcpy(dummy->id,key);
            list = findNode(tree,dummy,sizeof(Client),clientCompare);
            if(!list) return NULL;
            free(dummy);
            dummy = NULL;
            return list;
        }
        else if(is_valid_date(dateFromString(key)))
        {
            Date date;
            date = dateFromString(key);
            dummy->s_rent_date = date;
            list = findNode(tree,dummy,sizeof(Client),compareByDate);
            if(!list) return NULL;
            free(dummy);
            dummy = NULL;
            return list;
        }
    }
    return NULL;
}

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
int addNewClient(Tree tree,char* name,char* last_name, char id[10], char reg[8],Date rent_date,Time rent_hour, short rate)
{
    if(tree != NULL)
    {
        if(isValidClient(name,last_name,id,reg,rent_date,rent_hour,rate))
        {   
            Client* client;
            client = generateClient(name,last_name,id,reg,rent_date,rent_hour,rate);
            return addNewNode(tree,client,sizeof(Client),clientCompare);         
        }
        else printf("\nError - invalid Client\n");
    }
    else printf("\nError - null pointer to Client list\n");
    return 0;
}

/*Prompts user for Client information and adds a new Client to a given Tree
*
* tree - given Tree
*
* returns 1 if successful, 0 otherwise and prints an error message*/
int inputClient(Tree tree)
{
    if(tree != NULL)
    {
        char name[20];
        char last_name[20];
        char id[10];
        char reg[8];
        Date rent_date;
        Time rent_hour;
        short rate;
        char dummy[2];
        gets(dummy);
        while(1)
        {
            printf("\nPlease enter client first name : ");
            gets(name);
            if(strlen(name) == 0) printf("\nClient first name must contain at least one character\n");
            else break;
        }
        while(1)
        {
            printf("\nPlease enter client last name : ");
            gets(last_name);
            if(strlen(last_name) == 0) printf("\nClient last name must contain at least one character\n");
            else break;
        }
        while(1)
        {
            printf("\nPlease enter client ID number : ");
            gets(id);
            if(!isValidIdString(id)) printf("\nInvalid ID\n");
            else if(getClient(tree,id) != NULL) printf("\nThere is already a client with this ID\n");
            else break;
        }
        while(1)
        {
            printf("\nPlease enter client car registration number : ");
            gets(reg);
            if(!hasNumDigitsString(reg,7)) printf("\nInvalid registration number\n");
            else break;
        }
        while(1)
        {
            char datestring[11];
            printf("\nPlease enter date of start of rental (format dd/mm/yyyy, including slashes) : ");
            gets(datestring);
            rent_date = dateFromString(datestring);
            if(dateCompare(rent_date,default_date()) == 0) printf("\nInvalid date\n");
            else break;
        }
        while(1)
        {
            char timestring[6];
            printf("\nPlease enter time of start of rental (format hh:mm, including colon) : ");
            gets(timestring);
            rent_hour = timeFromString(timestring);
            if(timeCompare(rent_hour,default_time()) == 0) printf("\nInvalid time\n");
            else break;
        }
        while(1)
        {
            printf("\nPlease enter rental rate : ");
            scanf("%hd",&rate);
            if(!(rate >=0 && rate <= 999)) printf("\nRate must be between 0 and 999\n");
            else break;
        }
        if(addNewClient(tree,name,last_name,id,reg,rent_date,rent_hour,rate))
        {
            printf("\nClient added successfully!\n");
            return 1;
        }
        else
        {
            printf("\nCould not add client\n");
        }
    }
    else
    {
        printf("\nError - list is null\n");
    }
    return 0;
}


/*Deletes a TreeNode containing Client with given ID number from the Tree
*
* tree - Tree
* id : given ID number
*
* return : returns 1 if operation succeeded,0 otherwise*/
int deleteClient(Tree tree,char id[10])
{
    if(tree != NULL && tree->root != NULL && isValidIdString(id))
    {
        Client* dummy;
        int retval;
        dummy = (Client*)malloc(sizeof(Client));
        strcpy(dummy->id,id);
        retval = removeNode(tree,dummy,sizeof(Client),clientCompare);
        free(dummy);
        return retval;
    }
    return 0;
}

/*Deletes all TreeNodes from the Tree
*
* tree : Tree
*
* return : returns 1 if operation succeeded,0 otherwise*/
int deleteAllClients(Tree tree)
{
    if(tree != NULL)
    {
        if(tree->root == NULL) return 1;
        else
        {
            return freeTree(tree);
        }
    }
    else printf("\nError - null pointer to Client list\n");
    return 0;
}

/*Recursive helper function to function printClientCarsForGivenRentDate
*
* root - Tree root
* date - given Date
*
* returns 1 if all Clients for given rent date printed successfully, 0 otherwise*/
int printClientCarsForGivenRentDate_helper(TreeNode* root,Date date)
{
    if(!root) return 0;
    printClientCarsForGivenRentDate_helper(root->left,date);
    if(dateCompare(date,((Client*)root->value)->s_rent_date) == 0)
    {
        printClient(*((Client*)root->value));
    }
    printClientCarsForGivenRentDate_helper(root->right,date);
    return 1;
}

/*Prints all clients who rented a car on a specified date
*
* tree - given Tree
* date - date of rental
*
* returns 1 if successful, 0 otherwise*/
int printClientCarsForGivenRentDate(Tree tree,Date date)
{
    if(tree != NULL && tree->root != NULL && is_valid_date(date))
    {
        return printClientCarsForGivenRentDate_helper(tree->root,date);
    }
    return 0;
}


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

