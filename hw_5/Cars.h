#ifndef CARS_H
#define CARS_H

typedef struct CCar 
{
    char registration_num[8];
    char chassis_num[6];
    char* manufacturer;
    char* model;
    char* color;
    char y_of_manufacture[5];
    char y_start_of_use[5];
    int original_price;
    int current_price;
    int engine_volume;
} Car;

typedef struct CarNode
{
    Car* car;
    struct CarNode* next;
} CarNode;

typedef struct carList 
{
    CarNode* first;
    CarNode* last;
} carList;

typedef struct carList* CarList;

/*Generates and initializes an empty linked list of CarNodes
*
* return : returns empty list of CarNodes, with pointers to first and last elements set to NULL*/
CarList createCarList();

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
int addNewCar(CarList list,char reg_num[8],char c_num[6],char* manufac,char* model,char* ,char y_m[5],char y_s[5],int op,int cp,int vol);

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
int isValidCar(char reg_num[8],char c_num[6],char* manufac,char* model,char* color,char y_m[5],char y_s[5],int op,int cp,int vol);

/*Checks how many cars with given engine volume are in the list
*
* list : list of cars
* vol : engine volume
*
* return : returns number of cars in the list with given engine volume if succeded, prints an error message and return 0 otherwise*/
int carNumberWithGivenCapacity(CarList list ,int vol);

/*Recursively checks how many cars with given engine volume are in the list
*
* list : list of cars
* vol : engine volume
*
* return : returns number of cars in the list with given engine volume if succeded, prints an error message and return 0 otherwise*/
int carNumberWithGivenCapacity_REC(CarNode* node ,int vol);

/*Deletes a CarNode containing Car with given registration number from the list
*
* list - car list
* reg : given registration number
*
* return : returns 1 if operation succeeded,0 otherwise*/
int deleteCar(CarList list, char reg[8]);

/*Deletes all CarNodes from the list
*
* list : car list
*
* return : returns 1 if operation succeeded,0 otherwise*/
int deleteAllCars(CarList list);

/*Prints information for given Car
*
* car - given car
*
* returns 1 always*/
int printCar(Car car);

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
Car* generateCar(char reg_num[8],char c_num[6],char* manufac,char* model,char* color,char y_m[5],char y_s[5],int op,int cp,int vol);

/*Returns pointer to a Car from list with given registration number
*
* list - CarList
* reg - car registration number
*
* returns requested car if successful, NULL otherwise*/
Car* getCar(CarList list, char* reg);

/*Reverses order of CarList sorted by year of manufacture
*
* list - car list
*
* returns 1 if list was inverted successfully, 0 otherwise*/
int inverseCarList(CarList list);

/*Prints all cars in given list
*
* list - CarList
*
* returns 1 if successful, 0 otherwise*/
int printAllCars(CarList list);

#endif