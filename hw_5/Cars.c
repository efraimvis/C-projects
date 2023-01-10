#include "Cars.h"
#include "Checks.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*Generates and initializes an empty linked list of CarNodes
*
* return : returns empty list of CarNodes, with pointers to first and last elements set to NULL
* if successful, NULL otherwise*/
CarList createCarList()
{
    CarList list;
    list = (CarList)malloc(sizeof(struct carList));
    if(list == NULL) return NULL;
    list->first = NULL;
    list->last = NULL;
    return list;
}

/*Checks if all given car details are valid
*
* reg_num : car registration number
* c_num : car chassis number
* manufac : manufacturer name
* model : car model
* color : car color
* y_m : year of manufacture
* y_s : year of start of use
* op : original price of car
* cp : current price of car
* vol : engine volume
*
* returns 1 if details are valid, 0 otherwise*/
int isValidCar(char reg_num[8],char c_num[6],char* manufac,char* model,char* color,char y_m[5],char y_s[5],int op,int cp,int vol)
{
    if(hasNumDigitsString(reg_num,7) && hasNumDigitsString(c_num,5))
    {
        if(isSingleWord(manufac))
        {
            if(isValidYear(y_m) && isValidYear(y_s) && strcmp(y_m,y_s) <=0)
            {
                if(op >= 0 && op <= 9999999 && cp >= 0 && cp <=9999999 && vol >= 1000 && vol <= 9999) return 1;
            }
        }
    }
    return 0;
}

/*Generate a car with given details
*
* reg_num : car registration number
* c_num : car chassis number
* manufac : manufacturer name
* model : car model
* color : car color
* y_m : year of manufacture
* y_s : year of start of use
* op : original price of car
* cp : current price of car
* vol : engine volume
*
* returns pointer to car with given information if successful, NULL otherwise*/
Car* generateCar(char reg_num[8],char c_num[6],char* manufac,char* model,char* color,char y_m[5],char y_s[5],int op,int cp,int vol)
{
    if(isValidCar(reg_num,c_num,manufac,model,color,y_m,y_s,op,cp,vol))
    {
        Car* car;
        car = (Car*)malloc(sizeof(Car));
        car->manufacturer = (char*)malloc(sizeof(strlen(manufac)+1));
        car->model = (char*)malloc(sizeof(strlen(model)+1));
        car->color = (char*)malloc(sizeof(strlen(color)+1));
        if(car == NULL || car->manufacturer == NULL || car->model == NULL || car->color == NULL) return NULL;
        strcpy(car->registration_num,reg_num);
        strcpy(car->chassis_num , c_num);
        strcpy(car->manufacturer ,manufac);
        strcpy(car->model , model);
        strcpy(car->color , color);
        strcpy(car->y_of_manufacture , y_m);
        strcpy(car->y_start_of_use , y_s);
        car->original_price = op;
        car->current_price = cp;
        car->engine_volume = vol;
        return car;
    }
    return NULL;
}

/*Adds a new CarNode containing given Car to the start of a list
*
* list - CarList
* car - pointer to a Car
*
* returns 1 if CarNode was added successfully, 0 otherwise*/
int car_addToStart(CarList list, Car* car)
{
    if(list != NULL)
    {
        CarNode* newNode;
        newNode = (CarNode*)malloc(sizeof(CarNode));
        if(newNode == NULL) return 0;
        newNode->car = car;
        newNode->next = list->first;
        list->first = newNode;
        if(newNode->next == NULL) list->last = newNode;
        return 1;
    }
    return 0;
}

/*Adds a new CarNode containing given Car to the end of a list
*
* list - CarList
* car - pointer to a Car
* 
* returns 1 if CarNode was added successfully, 0 otherwise*/
int car_addToEnd(CarList list, Car* car)
{
    if(list != NULL)
    {
        CarNode* newNode;
        newNode = (CarNode*)malloc(sizeof(CarNode));
        if(newNode == NULL) return 0;
        newNode->car = car;
        if(list->last != NULL )list->last->next = newNode;
        else list->first = newNode;
        list->last = newNode;
        newNode->next = NULL;
        return 1;
    }
    return 0;
}

/*Returns pointer to a Car from list with given registration number
*
* list - CarList
* reg - car registration number
*
* returns requested car if successful, NULL otherwise*/
Car* getCar(CarList list, char* reg)
{
    if(list!= NULL && hasNumDigitsString(reg,7))
    {
        if(list->first != NULL)
        {
            CarNode* scan;
            scan = list->first;
            while(scan != NULL)
            {
                if(strcmp(scan->car->registration_num,reg) == 0) return scan->car;
                scan = scan->next;
            }
            scan = NULL;
        }
    }
    else
    {
        printf("\nError - list is null or invalid registration number\n");
    }
    return NULL;
}

/*Adds a new CarNode containing a Car to list of cars
*
* list : CarList
* reg_num : car registration number
* c_num : car chassis number
* manufac : manufacturer name
* model : car model
* color : car color
* y_m : year of manufacture
* y_s : year of start of use
* op : original price of car
* cp : current price of car
* vol : engine volume
*
* returns 1 if car was added to list successfully,returns 0 and prints an error message otherwise*/
int addNewCar(CarList list, char reg_num[8],char c_num[6],char* manufac,char* model,char* color,char y_m[5],char y_s[5],int op,int cp,int vol)
{
    if(isValidCar(reg_num,c_num,manufac,model,color,y_m,y_s,op,cp,vol) && list != NULL)
    {
        Car* car = generateCar(reg_num,c_num,manufac,model,color,y_m,y_s,op,cp,vol);
        if(list->first == NULL)
        {
            car_addToStart(list,car);
            return 1;
        }
        if(getCar(list,reg_num) == NULL)
        {
            if(strcmp(car->y_of_manufacture,list->first->car->y_of_manufacture) <= 0)
            {
                car_addToStart(list,car);
                return 1;
            }
            else if(strcmp(car->y_of_manufacture,list->last->car->y_of_manufacture) >= 0)
            {
                car_addToEnd(list,car);
                return 1;
            }
            else
            {
                CarNode* scan;
                CarNode* newNode;
                newNode = (CarNode*)malloc(sizeof(CarNode));
                if(newNode == NULL) return 0;
                newNode->car = car;
                scan = list->first;
                while(strcmp(car->y_of_manufacture,scan->car->y_of_manufacture) < 0) scan = scan->next;
                newNode->next = scan->next;
                scan->next = newNode;
                return 1;
            }
        }
    }
    else
    {
        printf("\nError - Invalid car information or null list\n");
    }
    return 0;
}

/*Checks how many cars with given engine volume are in the list
*
* list : list of cars
* vol : engine volume
*
* return : returns number of cars in the list with given engine volume if succeded, prints an error message and return 0 othewise*/
int carNumberWithGivenCapacity(CarList list,int vol)
{
    if(list != NULL && list->first != NULL)
    {
        if(vol >= 0 && vol <= 9999)
        {
            CarNode* scan;
            int counter;
            counter = 0;
            scan = list->first;
            while(scan != NULL)
            {
                if(scan->car->engine_volume == vol) counter++;
                scan = scan->next;
            }
            return counter;
        }
        else printf("\nError - bad engine volume\n");
    }
    else printf("\nError - null pointer to Car list\n");
    return 0;
}

/*Recursively checks how many cars with given engine volume are in the list
*
* node : CarNode in list
* vol : engine volume
*
* return : returns number of cars in the list with given engine volume if succeded, prints an error message and return 0 othewise*/
int carNumberWithGivenCapacity_REC(CarNode* node,int vol)
{
    if(node != NULL && vol >=0 && vol <= 9999)
    {
        if(node->car->engine_volume == vol)
        {
            return 1+carNumberWithGivenCapacity_REC(node->next,vol);
        }
        else
        {
            return carNumberWithGivenCapacity_REC(node->next,vol);
        }
    }
    else return 0;
}

/*Reverses order of CarList sorted by year of manufacture
*
* list - car list
*
* returns 1 if list was inverted successfully, 0 otherwise*/
int inverseCarList(CarList list)
{
    if(list != NULL)
    {
        CarNode* previous;
        CarNode* current;
        if(list->first != NULL)
        {
            previous = list->first;
            list->first = list->first->next;
            current = list->first;
            previous->next = NULL;
            while(list->first != NULL)
            {
                list->first = list->first->next;
                current->next = previous;
                previous = current;
                current = list->first;
            }
            list->first = previous;
            return 1;
        }
    }
    return 0;
}

/*Deletes a CarNode containing Car with given registration number from the list
*
* list - car list
* reg : given registration number
*
* return : returns 1 if operation succeeded,0 otherwise*/
int deleteCar(CarList list, char reg[8])
{
    if(list != NULL && list->first != NULL &&hasNumDigitsString(reg,7))
    {
        CarNode* scan;
        scan = list->first;
        if(strcmp(list->first->car->registration_num,reg) == 0)
        {
            if(list->first->next != NULL)
            {
                list->first = scan->next;
            }
            else
            {
                list->first = NULL;
                list->last = NULL;
            }
            free(scan->car);
            free(scan);
            return 1;
        }
        else if(strcmp(list->last->car->registration_num,reg) == 0)
        {
            while(scan->next != list->last) scan = scan->next;
            list->last = scan;
            free(scan->next->car);
            free(scan->next);
            list->last->next = NULL;
            return 1;
        }
        else if(list->first->next == NULL && strcmp(reg,list->first->car->registration_num) != 0) return 0;
        else
        {
            CarNode* temp;
            while((strcmp(scan->next->car->registration_num,reg) != 0) && scan->next->next != NULL) scan = scan->next;
            if(scan->next == list->last) return 0;
            temp = scan->next;
            scan->next = temp->next;
            free(temp->car);
            free(temp);
            return 1;
        }
    }
    return 0;
}

/*Deletes all CarNodes from the list
*
* list : car list
*
* return : returns 1 if operation succeeded,0 otherwise*/
int deleteAllCars(CarList list)
{
    if(list != NULL)
    {
        if(list->first == NULL) return 1;
        else
        {
            CarNode* scan;
            scan = list->first;
            while(scan != NULL)
            {
                CarNode* temp = scan;
                list->first = scan->next;
                scan = scan->next;
                free(temp->car);
                free(temp);
            }
            list->first = NULL;
            list->last = NULL;
            return 1;
        }
    }
    return 0;
}

/*Prints information for given Car
*
* car - given car
*
* returns 1 always*/
int printCar(Car car)
{
    printf("{registration:%s chassis:%s manufacturer:%s model:%s color:%s y_of_manufacture:%s current_price:%d engine_volume:%dcc}\n",car.registration_num,car.chassis_num,car.manufacturer,car.model,car.color,car.y_of_manufacture,car.current_price,car.engine_volume);
    return 1;
}

/*Prints all cars in given list
*
* list - CarList
*
* returns 1 if successful, 0 otherwise*/
int printAllCars(CarList list)
{
    if(list != NULL && list->first != NULL)
    {
        CarNode* scan;
        scan = list->first;
        printf("\n");
        while(scan != NULL)
        {
            printCar(*scan->car);
            printf("\n");
            scan = scan->next;
        }
    }
    return 0;
}