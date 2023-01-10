#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Cars.h"
#include "Clients.h"
#include "Checks.h"
#include "TimeDate.h"
#include "Suppliers.h"
#include "Common.h"

/*Prompts user for car information and adds a new car to a list
*
* list - CarList
*
* returns 1 if successful, 0 otherwise and prints an error message*/
int inputCar(CarList list)
{
    if(list != NULL)
    {
        char reg_num[8];
        char c_num[6];
        char manufac[20];
        char model[20];
        char color[20];
        char y_m[5];
        char y_s[5];
        int op, cp, vol;
        char dummy[2];
        gets(dummy);
        while(1)
        {
            printf("\nPlease enter car registration number : ");
            gets(reg_num);
            if(!hasNumDigitsString(reg_num,7)) printf("\nInvalid registration number\n");
            else if(getCar(list,reg_num)) printf("\nThere is already a car with this registration number\n");
            else break;
        }
        while(1)
        {
            printf("\nPlease enter chassis number : ");
            gets(c_num);
            if(!hasNumDigitsString(c_num,5)) printf("\nInvalid chassis number\n");
            else break;
        }
        while(1)
        {
            printf("\nPlease enter manufacturer name : ");
            gets(manufac);
            if(strlen(manufac) == 0) printf("\nManufacturer name must contain at least one character\n");
            else if(!isSingleWord(manufac)) printf("\nInvalid manufacturer name\n");
            else break;
        }
        while(1)
        {
            printf("\nPlease enter model name : ");
            gets(model);
            if(strlen(model) == 0) printf("\nModel name must contain at least one character\n");
            else break;
        }
        while(1)
        {
            printf("\nPlease enter color : ");
            gets(color);
            if(strlen(color) == 0) printf("\nColor must contain at least one character\n");
            else break;
        }
        while(1)
        {
            printf("\nPlease enter year of manufacture : ");
            gets(y_m);
            if(!isValidYear(y_m)) printf("\nInvalid year\n");
            else break;
        }
        while(1)
        {
            printf("\nPlease enter year of start of use : ");
            gets(y_s);
            if(!isValidYear(y_s)) printf("\nInvalid year\n");
            else if(strcmp(y_s,y_m) < 0) printf("\nYear of start of use cannot be earlier than year of manufacture\n");
            else break;
        }
        while(1)
        {
            printf("\nPlease enter original price : ");
            scanf("%d",&op);
            if(!(op >= 0 && op <= 9999999)) printf("\nInvalid amount\n");
            else break;
        }
        while(1)
        {
            printf("\nPlease enter current price : ");
            scanf("%d",&cp);
            if(!(cp >= 0 && cp <= 9999999)) printf("\nInvalid amount\n");
            else break;
        }
        while(1)
        {
            printf("\nPlease enter engine volume : ");
            scanf("%d",&vol);
            if(!(vol >= 1000 && vol <= 9999)) printf("\nInvalid engine volume\n");
            else break;
        }
        if(addNewCar(list,reg_num,c_num,manufac,model,color,y_m,y_s,op,cp,vol))
        {
            printf("\nCar added successfully\n");
            return 1;
        }
        else
        {
            printf("\nCould not add car\n");
            return 0;
        }
    }
    else
    {
        printf("\nError - null pointer to list\n");
    }
    return 0;
}

/*Prompts user for client information and adds a new client to a list
*
* list - ClientList
*
* returns 1 if successful, 0 otherwise and prints an error message*/
int inputClient(ClientList list)
{
    if(list != NULL)
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
            else if(getClient(list,id) != NULL) printf("\nThere is already a client with this ID\n");
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
            if(dateCompare(rent_date,default_date())) printf("\nInvalid date\n");
            else break;
        }
        while(1)
        {
            char timestring[6];
            printf("\nPlease enter time of start of rental (format hh:mm, including colon) : ");
            gets(timestring);
            rent_hour = timeFromString(timestring);
            if(timeCompare(rent_hour,default_time())) printf("\nInvalid time\n");
            else break;
        }
        while(1)
        {
            printf("\nPlease enter rental rate : ");
            scanf("%hd",&rate);
            if(!(rate >=0 && rate <= 999)) printf("\nRate must be between 0 and 999\n");
            else break;
        }
        if(addNewClient(list,name,last_name,id,reg,rent_date,rent_hour,rate))
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

/*Prompts user for supplier information and adds a new supplier to a list
*
* list - SupplierList
*
* returns 1 if successful, 0 otherwise and prints an error message*/
int inputSupplier(SupplierList list)
{
    if(list != NULL)
    {
        char bus_num[11];
        char sup_name[20];
        char phone_num[11];
        int num_transactions;
        long total_transactions;
        char dummy[2];
        gets(dummy);
        while(1)
        {
            printf("\nPlease enter supplier business number : ");
            gets(bus_num);
            if(!hasNumDigitsString(bus_num,10)) printf("\nInvalid business number\n");
            else if(getSupplier(list,bus_num) != NULL) printf("\nThere is already a supplier with this business number\n");
            else break;
        }
        while(1)
        {
            printf("\nPlease enter supplier name : ");
            gets(sup_name);
            if(strlen(sup_name) == 0) printf("\nSupplier name must have at least one digit\n");
            else break;
        }
        while(1)
        {
            printf("\nPlease enter supplier phone number : ");
            gets(phone_num);
            if(!isValidPhoneNumber(phone_num)) printf("\nInvalid phone number\n");
            else break;
        }
        while(1)
        {
            printf("\nPlesae enter number of transactions : ");
            scanf("%d",&num_transactions);
            if(!(num_transactions >= 0 && num_transactions <= 99999)) printf("\nInvalid number of transactions\n");
            else break;
        }
        while(1)
        {
            printf("\nPlease enter total sum of transactions : ");
            scanf("%ld",&total_transactions);
            if(!(total_transactions >= 0 && total_transactions <= 9999999999)) printf("\nInvalid sum of transactions\n");
            else break;
        }
        if(addNewSupplier(list,bus_num,sup_name,phone_num,num_transactions,total_transactions))
        {
            printf("\nSupplier added successfully!\n");
            return 1;
        }
        else
        {
            printf("\nCould not add supplier\n");
        }
    }
    else
    {
        printf("\nError - null pointer to list\n");
    }
    return 0;
}

/*Displays a menu and allows user to perform various operations on given car list
*
* list - CarList
*
* returns 1 if successful, 0 otherwise*/
int runCarInterface(CarList list)
{
    if(list!= NULL)
    {
        int choice;
        while(choice != 8)
        {
            printf("\nCars:\n\n1)Add new car\t2)Delete Car\t3)Car number with given capacity\n4)Car number with given capacity REC\t5)Invert car list   6)Delete all cars\n7)Print all cars\t8)Exit\nYour choice : ");
            scanf("%d",&choice);
            switch(choice)
            {
                case 1 :
                {
                    inputCar(list);
                    break;
                }
                case 2 :
                {
                    if(list->first != NULL)
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
                        if(!deleteCar(list,reg)) printf("\nCould not find car\n");
                        else printf("\nCar deleted successfully!\n");
                        break;
                    }
                    else printf("\nList is empty\n");
                    break;
                }
                case 3 : 
                {
                    if(list->first != NULL)
                    {
                        int vol;
                        while(1)
                        {
                            printf("\nPlease enter engine volume : ");
                            scanf("%d",&vol);
                            if(!(vol >= 1000 && vol <= 9999)) printf("\nInvalid engine volume\n");
                            else break;
                        }
                        printf("\n%d cars with engine volume %dcc\n",carNumberWithGivenCapacity(list,vol),vol);
                        break;
                    }
                    else printf("\nList is empty\n");
                    break;
                }
                case 4 :
                {
                    if(list->first != NULL)
                    {
                        int vol;
                        printf("\nPlease enter engine volume : ");
                        scanf("%d",&vol);
                        if(!(vol >= 1000 && vol <= 9999)) printf("\nInvalid engine volume\n");
                        else printf("\n%d cars with engine volume %dcc\n",carNumberWithGivenCapacity_REC(list->first,vol),vol);
                        break;
                    }
                    else printf("\nList is empty\n");
                    break;
                }
                case 5 :
                {
                    if(list->first != NULL)
                    {
                        if(inverseCarList(list)) printf("\nList inverted\n");
                        else printf("\nCould not invert list\n");
                        break;
                    }
                    else printf("\nList is empty\n");
                    break;
                }
                case 6 :
                {
                    if(list->first != NULL)
                    {
                        if(deleteAllCars(list)) printf("\nAll cars deleted successfully!\n");
                        else printf("\nCould not delete all cars\n");
                        break;
                    }
                    else printf("\nList is empty\n");
                    break;
                }
                case 7 :
                {
                    if(list->first != NULL)
                    {
                        printAllCars(list);
                    }
                    else printf("\nList is empty\n");
                    break;
                }
                case 8 : break;
                default : printf("\nInvalid selection\n");
            }
        }
        return 1;
    }
    else
    {
        printf("\nNull pointer to list\n");
    }
    return 0;
}

/*Displays a menu and allows user to perform various operations on given client list
*
* list - ClientList
*
* returns 1 if successful, 0 otherwise*/
int runClientInterface(ClientList clientList,CarList carList)
{
    if(clientList != NULL && carList != NULL)
    {
        int choice;
        while(choice != 6)
        {
            printf("\nClients:\n\n1)Add new client  2)Delete client\t3)Client number with given car year\n4)Print client cars for given rent date(DAVIS only)\t5)Delete all clients\n6)Exit\nYour choice : ");
            scanf("%d",&choice);
            switch(choice)
            {
                case 1 :
                {
                    inputClient(clientList);
                    break;
                }
                case 2 :
                {
                    if(clientList->first != NULL)
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
                        if(!deleteClient(clientList,id)) printf("\nCould not find client\n");
                        else printf("\nClient deleted successfully!\n");
                    }
                    else printf("\nList is empty\n");
                    break;
                }
                case 3 :
                {
                    if(clientList->first != NULL && carList->first != NULL)
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
                        printf("\nThere are %d clients with cars of year %s",clientNumberWithGivenCarYear(clientList,carList,year),year);
                        break;
                    }
                    else printf("\nList is empty\n");
                    break;
                }
                case 4 : 
                {
                    #ifdef DAVIS
                    if(clientList->first != NULL)
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
                            if(dateCompare(date,default_date())) printf("\nInvalid date\n");
                            else break;
                        }
                        printClientCarsForGivenRentDate(clientList,date);
                        break;
                    }
                    else printf("\nList is empty\n");
                    break;
                    #else 
                    printf("\nFeature is unavailable\n");
                    #endif
                    break;
                }
                case 5 :
                {
                    if(clientList->first != NULL)
                    {
                        if(deleteAllClients(clientList)) printf("\nAll clients deleted successfully!\n");
                        else printf("\nCould not delete all clients\n");
                        break;
                    }
                    else printf("\nList is empty\n");
                    break;
                }
                case 6 : break;
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

/*Displays a menu and allows user to perform various operations on given supplier list
*
* list - SupplierList
*
* returns 1 if successful, 0 otherwise*/
int runSupplierInterface(SupplierList list)
{
    if(list != NULL)
    {
        int choice;
        while(choice != 7)
        {
            printf("\nSuppliers:\n\n1)Add new supplier\t2)Delete supplier\t3)Three greatest suppliers\n4)Three greatest suppliers REC\t5)Print suppliers(DAVIS only)\t6)Delete all suppliers\n7)Exit\nYour choice : ");
            scanf("%d",&choice);
            switch(choice)
            {
                case 1 :
                {
                    inputSupplier(list);
                    break;
                }
                case 2 :
                {
                    if(list->first != NULL)
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
                        if(deleteSupplier(list,bus)) printf("\nSupplier deleted successfully!\n");
                        else printf("\nCould not delete supplier\n");
                        break;
                    }
                    else printf("\nList is empty\n");
                    break;
                }
                case 3 :
                {
                    if(list->first != NULL && list->first->next != NULL && list->first->next->next != NULL)
                    {
                        Greatest suppliers;
                        suppliers = threeGreatestSuppliers(list);
                        printf("\n3 greatest suppliers are : %s, %s, %s\n",suppliers.sup1,suppliers.sup2,suppliers.sup3);
                        break;
                    }
                    else printf("\nLess than 3 suppliers\n");
                    break;
                }
                case 4 :
                {
                    if(list->first != NULL && list->first->next != NULL && list->first->next->next != NULL)
                    {
                        Greatest suppliers;
                        suppliers = threeGreatestSuppliers_REC(list);
                        printf("\n3 greatest suppliers are : %s, %s, %s\n",suppliers.sup1,suppliers.sup2,suppliers.sup3);
                        break;
                    }
                    else printf("\nLess than 3 suppliers\n");
                    break;
                }
                case 5 :
                {
                    #ifdef DAVIS
                    if(list->first != NULL)
                    {
                        printf("\n");
                        printSuppliers(list);
                    }
                    else printf("\nList is empty\n");
                    break;
                    #else
                    printf("\nFeature is unavailable\n");
                    #endif
                    break;
                }
                case 6 :
                {
                    if(list->first != NULL)
                    {
                        if(deleteAllSuppliers(list)) printf("\nAll suppliers deleted successfully!\n");
                        else printf("\nCould not delete all suppliers\n");
                        break;
                    }
                    else printf("\nList is empty\n");
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

/*Displays a menu system and allows user to manage given lists of cars, clients and suppliers
*
* carList - CarList
* clientList - ClientList
* supplierList - SupplierList
*
* returns 1 if successful, 0 otherwise*/
int runInterface(CarList carList,ClientList clientList ,SupplierList supplierList)
{
    if(carList != NULL && clientList != NULL && supplierList != NULL)
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
                    runCarInterface(carList);
                    break;
                }
                case 2 :
                {
                    runClientInterface(clientList,carList);
                    break;
                }
                case 3 :
                {
                    runSupplierInterface(supplierList);
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
    CarList cars;
    ClientList clients;
    SupplierList suppliers;
    cars = createCarList();
    clients = createClientList();
    suppliers = createSupplierList();
    addNewCar(cars,"6922258","11111","Toyota","Corolla","Silver","2018","2019",132900,90000,1500);
    addNewCar(cars,"8970159","14513","Hyundai","Ioniq","Black","2017","2017",143900,100000,1600);
    addNewCar(cars,"1209865","84651","Kia","Picanto","Red","2015","2015",84500,100000,1197);
    addNewClient(clients,"Nimrod","Ashkenazi","319034385","8970159",generate_date(2021,5,5),generate_time(0,0),250);
    addNewClient(clients,"Gilad","Shmueli","314673187","6922258",generate_date(2021,5,4),generate_time(8,0),235);
    addNewClient(clients,"Lital","Mazuz","207482183","1209865",generate_date(2021,5,24),generate_time(23,59),180);
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