#include "Cars.h"
#include "Checks.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/*Generates and initializes an empty Tree
*
* return : returns empty Tree, with root set to NULL
* if successful, NULL otherwise*/
Tree createCarTree()
{
    return createTree();
}

/*Compares two given cars based on registration number
*
* car1, car2 - given cars
*
* return : returns negative value if car1 has a smaller registration number,
* positive value if car1 has larger registration number, 0 if cars have the same registration number*/
int carCompare(const void* car1, const void* car2)
{
    return strcmp(((Car*)car1)->registration_num,((Car*)car2)->registration_num);
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

/*Returns pointer to a Car with given registration number from Tree
*
* tree - Tree
* reg - car registration number
*
* returns requested car if successful, NULL otherwise*/
Car* getCar(Tree tree, char* reg)
{
    if(tree != NULL && hasNumDigitsString(reg,7))
    {
        if(tree->root != NULL)
        {
            Car* dummy;
            Car* returnCar;
            Tree node;
            dummy = (Car*)malloc(sizeof(Car));
            if(!dummy) return NULL;
            strcpy(dummy->registration_num,reg);
            node = findNode(tree,dummy,sizeof(Car),carCompare);
            if(node == NULL || node->root == NULL)
            {
                free(dummy);
                free(node);
                node = NULL;
                dummy = NULL;
                return NULL;
            }
            returnCar = (Car*)node->root->value;
            free(dummy);
            free(node);
            node = NULL;
            dummy = NULL;
            return returnCar;
        }
    }
    else
    {
        printf("\nError - Tree is null or invalid registration number\n");
    }
    return NULL;
}

/*Adds a new TreeNode containing a Car to given Tree
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
int addNewCar(Tree tree, char reg_num[8],char c_num[6],char* manufac,char* model,char* color,char y_m[5],char y_s[5],int op,int cp,int vol)
{
    if(isValidCar(reg_num,c_num,manufac,model,color,y_m,y_s,op,cp,vol) && tree != NULL)
    {
        Car* car = generateCar(reg_num,c_num,manufac,model,color,y_m,y_s,op,cp,vol);
        return addNewNode(tree,car,sizeof(Car),carCompare);
    }
    else
    {
        printf("\nError - Invalid car information or null Tree\n");
    }
    return 0;
}

/*Prompts user for car information and adds a new car to a given Tree
*
* tree - given Tree
*
* returns 1 if successful, 0 otherwise and prints an error message*/
int inputCar(Tree tree)
{
    if(tree != NULL)
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
            else if(getCar(tree,reg_num)) printf("\nThere is already a car with this registration number\n");
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
        if(addNewCar(tree,reg_num,c_num,manufac,model,color,y_m,y_s,op,cp,vol))
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
        printf("\nError - null pointer to Tree\n");
    }
    return 0;
}

/*Recursive helper function to function carNumberWithGivenCapacity
*
* root - root of Tree
* vol - engine volume
*
* return : returns the number of cars in the tree which have given engine volume*/
int carNumberWithGivenCapacity_helper(TreeNode* root,int vol)
{
    int counter;
    if(root == NULL) return 0;
    counter = 0;
    if(((Car*)root->value)->engine_volume == vol)
    {
        counter++;
    }
    counter += (carNumberWithGivenCapacity_helper(root->left,vol)+carNumberWithGivenCapacity_helper(root->right,vol));
    return counter;
}

/*Checks how many cars with given engine volume are in the Tree
*
* tree : given Tree
* vol : engine volume
*
* return : returns number of cars in the Tree with given engine volume if succeded, prints an error message and return 0 othewise*/
int carNumberWithGivenCapacity(Tree tree,int vol)
{
    if(tree != NULL && tree->root != NULL)
    {
        if(vol >= 0 && vol <= 9999)
        {
            return carNumberWithGivenCapacity_helper(tree->root,vol);
        }
        else printf("\nError - bad engine volume\n");
    }
    else printf("\nError - null pointer to Tree\n");
    return 0;
}


/*Deletes a TreeNode containing Car with given registration number from the Tree
*
* tree - Tree
* reg : given registration number
*
* return : returns 1 if operation succeeded,0 otherwise*/
int deleteCar(Tree tree, char reg[8])
{
    if(tree != NULL && tree->root != NULL &&hasNumDigitsString(reg,7))
    {
        Car* dummy;
        int retval;
        dummy = (Car*)malloc(sizeof(Car));
        strcpy(dummy->registration_num,reg);
        retval = removeNode(tree,dummy,sizeof(Car),carCompare);
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
int deleteAllCars(Tree tree)
{
    if(tree != NULL)
    {
        if(tree->root == NULL) return 1;
        else
        {
            return freeTree(tree);
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
