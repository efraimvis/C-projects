#ifndef CARS_H
#define CARS_H
#define N 10000

typedef struct CCar 
{
    char registration_num[8];
    char chassis_num[6];
    char manufacturer[11];
    char model[11];
    char color[8];
    char y_of_manufacture[5];
    char y_start_of_use[5];
    int original_price;
    int current_price;
    int engine_volume;
} Car;

/*Checks if given car is default car.
*Car: car
* return : returns 1 if default car return 0 otherwise*/
int isDefaultCar(Car car);

/*Generates and initializes an N sized array of Cars
*
* return : returns 1 if operation succeeded, prints an error message and returns 0 otherwise*/
int createCarList(Car* list);

/*Adds a car to list of cars
*
* list : pointer to a Car array
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
int addNewCar(Car* list,char reg_num[8],char c_num[6],char manufac[11],char model[11],char color[8],char y_m[5],char y_s[5],int op,int cp,int vol);

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
int isValidCar(char reg_num[8],char c_num[6],char manufac[11],char model[11],char color[8],char y_m[5],char y_s[5],int op,int cp,int vol);

/*Checks how many cars with given engine volume are in the list
*
* list : list of cars
* vol : engine volume
*
* return : returns number of cars in the list with given engine volume if succeded, prints an error message and return 0*/
unsigned int carNumberWithGivenCapacity(Car* list ,int vol);

/*Removes a car with given registration number from the list
*
* car_list : car list
* reg : given registration number
*
* return : returns 1 if operation succeeded,return 0 and prints an error message otherwise*/
int deleteCar(Car* list, char reg[8]);

/*Removes all cars from the list
*
* car_list : car list
*
* return : returns 1 if operation succeeded, returns 0 and prints an error message otherwise*/
int deleteAllCars(Car* list);

/*Prints to screen car information
*
* car : car 
*
* return : returns 1 */
int printCar(Car car);

#endif