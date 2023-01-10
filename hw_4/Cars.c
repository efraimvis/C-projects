#include "Cars.h"
#include "Checks.h"
#include <stdio.h>
#include <string.h>
#define D_REG_NUM "DEFAULT"
#define D_C_NUM "00000"
#define D_MAN "DEFAULT000"
#define D_MOD "DEFAULT000"
#define D_COLOR "DEFAULT"
#define D_YEAR "1886"
/*Checks if given car is default car.
*Car: car
* return : returns 1 if default car return 0 otherwise*/
int isDefaultCar(Car car)
{
    if(strcmp(car.registration_num,D_REG_NUM) == 0) return 1;
    return 0;
}
/*Generates a default car and initialize default values
*
* return : returns car with default parameters*/
Car generateDefaultCar()
{
    Car car;
    strcpy(car.registration_num,D_REG_NUM);
    strcpy(car.chassis_num , D_C_NUM);
    strcpy(car.manufacturer ,D_MAN);
    strcpy(car.model ,D_MOD);
    strcpy(car.color ,D_COLOR);
    strcpy(car.y_of_manufacture , D_YEAR);
    strcpy(car.y_start_of_use , D_YEAR);
    car.original_price = 0;
    car.current_price = 0;
    car.engine_volume = 0;
    return car;
}

/*Generates and initializes an N sized array of Cars
*
* return : returns 1 if operation succeeded, prints an error message and returns 0 otherwise*/
int createCarList(Car* list)
{
    if(list != NULL)
    {
        int i;
        for(i=0;i<N;i++)
        {
            list[i] = generateDefaultCar();
        }
        return 1;
    }
    else printf("\nError - null pointer to Car list\n");
    return 0;
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
int isValidCar(char reg_num[8],char c_num[6],char manufac[11],char model[11],char color[8],char y_m[5],char y_s[5],int op,int cp,int vol)
{
    if(hasNumDigitsString(reg_num,7) && hasNumDigitsString(c_num,5))
    {
        if(strlen(manufac) <= 10 && strlen(model) <= 10 && strlen(color) <= 7)
        {
            if(isValidYear(y_m) && isValidYear(y_s))
            {
                if((op >= 0 && cp >= 0 && vol >= 0) && (getNumDigits(op) <= 7 && getNumDigits(cp) <= 7 && getNumDigits(vol) <= 4)) return 1;
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
* returns car with given details if succeded, return default car otherwise*/
Car generateCar(char reg_num[8],char c_num[6],char manufac[11],char model[11],char color[8],char y_m[5],char y_s[5],int op,int cp,int vol)
{
    if(isValidCar(reg_num,c_num,manufac,model,color,y_m,y_s,op,cp,vol))
    {
        Car car;
        strcpy(car.registration_num,reg_num);
        strcpy(car.chassis_num , c_num);
        strcpy(car.manufacturer ,manufac);
        strcpy(car.model , model);
        strcpy(car.color , color);
        strcpy(car.y_of_manufacture , y_m);
        strcpy(car.y_start_of_use , y_s);
        car.original_price = op;
        car.current_price = cp;
        car.engine_volume = vol;
        return car;
    }
    return generateDefaultCar();
}

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
int addNewCar(Car* list, char reg_num[8],char c_num[6],char manufac[11],char model[11],char color[8],char y_m[5],char y_s[5],int op,int cp,int vol)
{
    if(list != NULL)
    {
        if(isValidCar(reg_num,c_num,manufac,model,color,y_m,y_s,op,cp,vol))
        {
            Car car;
            int i;
            car = generateCar(reg_num,c_num,manufac,model,color,y_m,y_s,op,cp,vol);
            i=0;
            while(!isDefaultCar(list[i]) && i<N)
            {
                if((strcmp(list[i].registration_num, car.registration_num) == 0) || (strcmp(list[i].chassis_num, car.chassis_num) == 0)) return 0;
                i++;
            }
            if(i < N)
            {
                if(isDefaultCar(list[i]))
                {
                    list[i] = car;
                    return 1;
                }
                return 0;
            }
            else return 0;
        }
        else printf("\nError - invalid Car\n");
    }
    else printf("\nError - null pointer to Car list\n");
    return 0;
}

/*Checks how many cars with given engine volume are in the list
*
* list : list of cars
* vol : engine volume
*
* return : returns number of cars in the list with given engine volume if succeded, prints an error message and return 0*/
unsigned int carNumberWithGivenCapacity(Car* list,int vol)
{
    if(list != NULL)
    {
        if(vol >= 0 && getNumDigits(vol) <= 4)
        {
            int i,counter;
            counter = 0;
            for(i=0;i<N;i++)
            {
                if(list[i].engine_volume == vol) counter++;
            }
            return counter;
        }
        else printf("\nError - bad engine volume\n");
    }
    else printf("\nError - null pointer to Car list\n");
    return 0;
}

/*Removes a car with given registration number from the list
*
* car_list : car list
* reg : given registration number
*
* return : returns 1 if operation succeeded,return 0 and prints an error message otherwise*/
int deleteCar(Car* list, char reg[8])
{
    if(list != NULL)
    {
        if(hasNumDigitsString(reg,7))
        {
            int i;
            i=0;
            while((strcmp(list[i].registration_num,reg) != 0) && i<N) i++;
            if((strcmp(list[i].registration_num,reg) == 0))
            {
                list[i] =generateDefaultCar();
                return 1;
            }
        }
        else printf("\nError - bad registration number\n");
    }
    else printf("\nError - null pointer to Car list\n");
    return 0;
}

/*Removes all cars from the list
*
* car_list : car list
*
* return : returns 1 if operation succeeded, returns 0 and prints an error message otherwise*/
int deleteAllCars(Car* list)
{
    if(list != NULL)
    {
        createCarList(list);
        return 1;
    }
    else printf("\nError - null pointer to Car list\n");
    return 0;
}
/*Prints to screen car information
*
* car : car
*
* return : returns 1 */
int printCar(Car car)
{
    printf("{registration:%s chassis:%s manufacturer:%s model:%s color:%s y_of_manufacture:%s current_price:%d engine_volume:%dcc}\n",car.registration_num,car.chassis_num,car.manufacturer,car.model,car.color,car.y_of_manufacture,car.current_price,car.engine_volume);
    return 1;
}