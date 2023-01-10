#include <stdio.h>
#include <string.h>
#include "Checks.h"
#include "Common.h"


/*Recursive helper function to function clientNumberWithGivenCarYear
*
* clientRoot - root of Client Tree
* carTree - Tree of Cars
* year - given year of manufacture
*
* return : returns the number of Clients with a Car of given year of manufacture*/
int clientNumberWithGivenCarYear_helper(TreeNode* clientRoot,Tree carTree,char year[5])
{
    Car* car;
    int counter;
    if(!clientRoot) return 0;
    counter = 0;
    car = getCar(carTree,((Client*)clientRoot->value)->car_registration_num);
    if(car != NULL)
    {
        if(strcmp(car->y_of_manufacture,year) == 0) counter++;
    }
    counter += (clientNumberWithGivenCarYear_helper(clientRoot->left,carTree,year)+clientNumberWithGivenCarYear_helper(clientRoot->right,carTree,year));
    return counter;
}

/*Returns number of clients with cars of given year of manufacture
* 
* clientTree : Client Tree
* carTree : Car Tree
* year : given year of manufacture
*
* return : returns number of Clients with Cars of given year of manufacture, on error returns -1 and prints message*/
int clientNumberWithGivenCarYear(Tree clientTree,Tree carTree,char year[5])
{
    if(clientTree != NULL && clientTree->root != NULL && carTree != NULL && carTree->root != NULL &&isValidYear(year))
    {
        return clientNumberWithGivenCarYear_helper(clientTree->root,carTree,year);
    }
    else printf("\nError - null pointer to list or invalid year\n");
    return -1;
}