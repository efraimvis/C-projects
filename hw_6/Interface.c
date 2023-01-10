#include <stdio.h>
#include <string.h>
#include "Checks.h"
#include "Suppliers.h"
#include "Common.h"

/*Displays a menu and allows user to perform various operations on given Tree of Cars
*
* tree - Tree
*
* returns 1 if successful, 0 otherwise*/
int runCarInterface(Tree tree)
{
    if(tree != NULL)
    {
        int choice;
        while(choice != 5)
        {
            printf("\nCars:\n\n1)Add new car\t2)Delete Car\t3)Car number with given capacity\n4)Delete all cars\t5)Exit\nYour choice : ");
            scanf("%d",&choice);
            switch(choice)
            {
                case 1 :
                {
                    inputCar(tree);
                    break;
                }
                case 2 :
                {
                    if(tree->root != NULL)
                    {
                        char dummy[2];
                        char reg[8];
                        gets(dummy);
                        while(1)
                        {
                            printf("\nPlease enter car registration number : ");
                            gets(reg);
                            if(!hasNumDigitsString(reg,7)) printf("\nInvalid registration number\n");
                            else break;
                        }
                        if(!deleteCar(tree,reg)) printf("\nCould not find car\n");
                        else printf("\nCar deleted successfully!\n");
                        break;
                    }
                    else printf("\nTree is empty\n");
                    break;
                }
                case 3 : 
                {
                    if(tree->root != NULL)
                    {
                        int vol;
                        while(1)
                        {
                            printf("\nPlease enter engine volume : ");
                            scanf("%d",&vol);
                            if(!(vol >= 1000 && vol <= 9999)) printf("\nInvalid engine volume\n");
                            else break;
                        }
                        printf("\n%d cars with engine volume %dcc\n",carNumberWithGivenCapacity(tree,vol),vol);
                        break;
                    }
                    else printf("\nTree is empty\n");
                    break;
                }
                case 4 :
                {
                    if(tree->root != NULL)
                    {
                        if(deleteAllCars(tree)) printf("\nAll cars deleted successfully!\n");
                        else printf("\nCould not delete all cars\n");
                        break;
                    }
                    else printf("\nTree is empty\n");
                    break;
                }
                case 5 : break;
                default : printf("\nInvalid selection\n");
            }
        }
        return 1;
    }
    else
    {
        printf("\nNull pointer to Tree\n");
    }
    return 0;
}

/*Displays a menu and allows user to perform various operations on given Tree of Clients
*
* clientTree - Tree of Clients
* carTree - Tree of Cars (used for clientNumberWithGivenCarYear)
*
* returns 1 if successful, 0 otherwise*/
int runClientInterface(Tree clientTree,Tree carTree)
{
    if(clientTree != NULL && carTree != NULL)
    {
        int choice;
        while(choice != 7)
        {
            printf("\nClients:\n\n1)Add new client  2)Delete client\t3)Client number with given car year\n4)Print client cars for given rent date\t5)find client\t6)Delete all clients\n7)Exit\nYour choice : ");
            scanf("%d",&choice);
            switch(choice)
            {
                case 1 :
                {
                    inputClient(clientTree);
                    break;
                }
                case 2 :
                {
                    if(clientTree->root != NULL)
                    {
                        char dummy[2];
                        char id[10];
                        gets(dummy);
                        while(1)
                        {
                            printf("\nPlease enter client ID : ");
                            gets(id);
                            if(!isValidIdString(id)) printf("\nInvalid ID\n");
                            else break;
                        }
                        if(!deleteClient(clientTree,id)) printf("\nCould not find client\n");
                        else printf("\nClient deleted successfully!\n");
                    }
                    else printf("\nTree is empty\n");
                    break;
                }
                case 3 :
                {
                    if(clientTree->root != NULL && carTree->root != NULL)
                    {
                        char dummy[2];
                        char year[5];
                        gets(dummy);
                        while(1)
                        {
                            printf("\nPlease enter year : ");
                            gets(year);
                            if(!isValidYear(year)) printf("\nInvalid year\n");
                            else break;
                        }
                        printf("\nThere are %d clients with cars of year %s",clientNumberWithGivenCarYear(clientTree,carTree,year),year);
                        break;
                    }
                    else printf("\nCar tree or client tree empty\n");
                    break;
                }
                case 4 : 
                {
                    if(clientTree->root != NULL)
                    {
                        Date date;
                        char dummy[2];
                        char datestring[10];
                        gets(dummy);
                        while(1)
                        {
                            printf("\nPlease enter date (in format dd/mm/yyyy, including slashes): ");
                            gets(datestring);
                            date = dateFromString(datestring);
                            if(dateCompare(date,default_date()) == 0) printf("\nInvalid date\n");
                            else break;
                        }
                        printClientCarsForGivenRentDate(clientTree,date);
                        break;
                    }
                    else printf("\nTree is empty\n");
                    break;
                }
                case 5 :
                {
                    if(clientTree->root != NULL)
                    {
                        char dummy[2];
                        char key[11];
                        ClientList clientList;
                        gets(dummy);
                        while(1)
                        {
                            printf("\nPlease enter client information (id or rent date in format dd/mm/yyyy): ");
                            gets(key);
                            if(!(isValidIdString(key) || is_valid_date(dateFromString(key)))) printf("\nInvalid information\n");
                            else break;
                        }
                        clientList = findClient(clientTree,key);
                        if(clientList == NULL || clientList->first == NULL) printf("\nNo clients to show\n");
                        else
                        {
                            ClientNode* scan;
                            scan = clientList->first;
                            printf("\n");
                            while(scan != NULL)
                            {
                                printClient(*scan->client);
                                scan = scan->next;
                            }
                            scan = NULL;
                        }
                        break;
                    }
                    else printf("\nTree is empty\n");
                    break;
                }
                case 6 :
                {
                    if(clientTree->root != NULL)
                    {
                        if(deleteAllClients(clientTree)) printf("\nAll clients deleted successfully!\n");
                        else printf("\nCould not delete all clients\n");
                        break;
                    }
                    else printf("\nTree is empty\n");
                    break;
                }
                case 7 : break;
                default : printf("\nInvalid selection\n");
            }
        }
    }
    else
    {
        printf("\nNull pointer to list\n");
    }
    return 0;
}

/*Displays a menu and allows user to perform various operations on given Tree of Suppliers
*
* tree - Tree
*
* returns 1 if successful, 0 otherwise*/
int runSupplierInterface(Tree tree)
{
    if(tree != NULL)
    {
        int choice;
        while(choice != 7)
        {
            printf("\nSuppliers:\n\n1)Add new supplier\t2)Delete supplier\t3)Three greatest suppliers\n4)Average of supplier money\t5)Print suppliers\t6)Delete all suppliers\n7)Exit\nYour choice : ");
            scanf("%d",&choice);
            switch(choice)
            {
                case 1 :
                {
                    inputSupplier(tree);
                    break;
                }
                case 2 :
                {
                    if(tree->root != NULL)
                    {
                        char dummy[2];
                        char bus[11];
                        gets(dummy);
                        while(1)
                        {
                            printf("\nPlease enter supplier business number : ");
                            gets(bus);
                            if(!hasNumDigitsString(bus,10)) printf("\nInvalid business number\n");
                            else break;
                        }
                        if(deleteSupplier(tree,bus)) printf("\nSupplier deleted successfully!\n");
                        else printf("\nCould not delete supplier\n");
                        break;
                    }
                    else printf("\nTree is empty\n");
                    break;
                }
                case 3 :
                {
                    if(tree->elementCount >= 3)
                    {
                        Greatest suppliers;
                        suppliers = threeGreatestSuppliers(tree);
                        printf("\n3 greatest suppliers are : %s, %s, %s\n",suppliers.sup1,suppliers.sup2,suppliers.sup3);
                        break;
                    }
                    else printf("\nLess than 3 suppliers\n");
                    break;
                }
                case 4 :
                {
                    if(tree->root != NULL)
                    {
                        long average;
                        average = averageOfSupplierMoney(tree->root,tree->elementCount);
                        printf("\nAverage of supplier money is : %ld\n",average);
                    }
                    else printf("\nTree empty\n");
                    break;
                }
                case 5 :
                {
                    if(tree->root != NULL)
                    {
                        printf("\n");
                        printSuppliers(tree);
                    }
                    else printf("\nTree is empty\n");
                    break;
                }
                case 6 :
                {
                    if(tree->root != NULL)
                    {
                        if(deleteAllSuppliers(tree)) printf("\nAll suppliers deleted successfully!\n");
                        else printf("\nCould not delete all suppliers\n");
                        break;
                    }
                    else printf("\nTree is empty\n");
                    break;
                }
                case 7 : break;
                default : printf("\nInvalid selection\n");
            }
        }
    }
    else
    {
        printf("\nNull pointer to list\n");
    }
    return 0;
}

/*Displays a menu system and allows user to manage given Trees of Cars, Clients and Suppliers
*
* carTree - Tree of Cars
* clientTree - Tree of Clients
* supplierTree - Tree of Suppliers
*
* returns 1 if successful, 0 otherwise*/
int runInterface(Tree carTree,Tree clientTree ,Tree supplierTree)
{
    if(carTree != NULL && clientTree != NULL && supplierTree != NULL)
    {
        int choice;
        while(choice != 4)
        {
            printf("\nMain Menu\n\n1)Manage cars\t2)Manage clients\t3)Manage suppliers\n4)Exit\nYour choice : ");
            scanf("%d",&choice);
            switch(choice)
            {
                case 1 :
                {
                    runCarInterface(carTree);
                    break;
                }
                case 2 :
                {
                    runClientInterface(clientTree,carTree);
                    break;
                }
                case 3 :
                {
                    runSupplierInterface(supplierTree);
                    break;
                }
                case 4 : break;
                default : printf("\nInvalid selection\n");
            }
        }
        printf("\nGoodbye!\n");
    }
    else printf("\nNull pointer to list\n");
    return 0;
}

/*Runs a demo of assignment with some preset values*/
int DEMO()
{
    Tree cars;
    Tree clients;
    Tree suppliers;
    cars = createCarTree();
    clients = createClientTree();
    suppliers = createSupplierTree();
    addNewCar(cars,"6922258","11111","Toyota","Corolla","Silver","2018","2019",132900,90000,1500);
    addNewCar(cars,"8970159","14513","Hyundai","Ioniq","Black","2017","2017",143900,100000,1600);
    addNewCar(cars,"1209865","84651","Kia","Picanto","Red","2015","2015",84500,100000,1197);
    addNewClient(clients,"Nimrod","Ashkenazi","319034385","8970159",generate_date(2021,5,5),generate_time(0,0),250);
    addNewClient(clients,"Gilad","Shmueli","314673187","6922258",generate_date(2021,5,5),generate_time(8,0),235);
    addNewClient(clients,"Lital","Mazuz","207482183","1209865",generate_date(2021,5,5),generate_time(23,59),180);
    addNewSupplier(suppliers,"4687321035","Toyota","0534575432",3,200000);
    addNewSupplier(suppliers,"5387121430","NEC","0521572821",5,3000);
    addNewSupplier(suppliers,"5104543330","Eldan","0546903186",8,150000);
    runInterface(cars,clients,suppliers);
    return 0;
}

int main(void)
{
    DEMO();
    return 0;
}