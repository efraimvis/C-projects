#include "Cars.h"
#include "Checks.h"
#include <stdio.h>
#define N 10000

/*Generates and initializes an N sized array of Cars
*
* return : returns an array of Cars*/
Car createCarList[N](){}

/*Adds a car to list of cars
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
* returns 1 if car was added to list successfully, 0 otherwise*/
int addNewCar(char reg_num[7],char c_num[5],char manufac[10],char model[10],char color[7],char y_m[4],char y_s[4],unsigned int op,unsigned int cp,unsigned int vol){}

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
int isValidCar(char reg_num[7],char c_num[5],char manufac[10],char model[10],char color[7],char y_m[4],char y_s[4],unsigned int op,unsigned int cp,unsigned int vol){}

/*Checks how many cars with given engine volume are in the list
*
* car_list : list of cars
* vol : engine volume
*
* return : returns number of cars in the list with given engine volume*/
unsigned int carNumberWithGivenCapacity(Car car_list[],unsigned int vol){}

/*Removes a car with given registration number from the list
*
* car_list : car list
* reg : given registration number
*
* return : returns 1 if operation succeeded, 0 otherwise*/
int deleteCar(Car car_list[], char[7] reg){}

/*Removes all cars from the list
*
* car_list : car list
*
* return : returns 1 if operation succeeded, 0 otherwise*/
int deleteAllCars(Car car_list[]){}