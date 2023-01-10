#ifndef CARS_H
#define CARS_H

#include "Tree.h"

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

/*Generates and initializes an empty Tree
*
* return : returns empty Tree, with root set to NULL
* if successful, NULL otherwise*/
Tree createCarTree();

/*Compares two given cars based on registration number
*
* car1, car2 - given cars
*
* return : returns negative value if car1 has a smaller registration number,
* positive value if car1 has larger registration number, 0 if cars have the same registration number*/
int carCompare(const void* car1, const void* car2);

/*Adds a new TreeNodw containing a Car to given Tree
*
* tree : given Tree
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
* returns 1 if car was added to Tree successfully,returns 0 and prints an error message otherwise*/
int addNewCar(Tree tree,char reg_num[8],char c_num[6],char* manufac,char* model,char* ,char y_m[5],char y_s[5],int op,int cp,int vol);

/*Prompts user for car information and adds a new car to a given Tree
*
* tree - given Tree
*
* returns 1 if successful, 0 otherwise and prints an error message*/
int inputCar(Tree tree);

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

/*Checks how many cars with given engine volume are in the Tree
*
* tree : given Tree
* vol : engine volume
*
* return : returns number of cars in the Tree with given engine volume if succeded, prints an error message and return 0 othewise*/
int carNumberWithGivenCapacity(Tree tree ,int vol);

/*Deletes a TreeNode containing Car with given registration number from the Tree
*
* tree - Tree
* reg : given registration number
*
* return : returns 1 if operation succeeded,0 otherwise*/
int deleteCar(Tree tree, char reg[8]);

/*Deletes all TreeNodes from the Tree
*
* tree : Tree
*
* return : returns 1 if operation succeeded,0 otherwise*/
int deleteAllCars(Tree tree);

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

/*Returns pointer to a Car with given registration number from Tree 
*
* tree - Tree
* reg - car registration number
*
* returns requested car if successful, NULL otherwise*/
Car* getCar(Tree tree, char* reg);

#endif