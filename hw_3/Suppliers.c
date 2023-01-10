#include "Suppliers.h"
#include <stdio.h>
#define K  50

/*Generates and initializes a K sized array of suppliers
*
* return : returns an array of suppliers*/
Supplier createSupplierList[K](){}

/*Adds a new supplier with given information to the list
*
* bus_num : suppliers business number
* sup_name : supplier name
* phone_num : supplier phone number
* num_transactions : number of transactions with supplier
* total_transactions : total sum of transactions with supplier
* 
* return : returns 1 if operation succeeded, 0 otherwise*/
int addNewSupplier(long long bus_num,char sup_name[5],char phone_num[10],unsigned int num_transactions,unsigned int total_transactions){}

/*Checks if given supplier information is valid
*
* bus_num : suppliers business number
* sup_name : supplier name
* phone_num : supplier phone number
* num_transactions : number of transactions with supplier
* total_transactions : total sum of transactions with supplier
*
* return : returns 1 if supplier information is valid, 0 otherwise
*/
int isValidSupplier(long long bus_num,char sup_name[5],char phone_num[10],unsigned int num_transactions,unsigned int total_transactions){}

/*Returns a long int array of size 3, containing the business numbers of the 3 suppliers with which the largest transactions were carried out
*
* supplier_list : supplier list
*
* return : Returns a long int array of size 3, containing the business numbers of the 3 suppliers with which the largest transactions were carried out if operation succeeded, array of zeros otherwise*/
long long threeGreatestSuppliers[3](Supplier supplier_list[]){}

/*Removes a supplier with given name from the list
*
* supplier_list : supplier list
* sup_name : supplier name
*
* return : returns 1 if operation succeeded, 0 otherwise*/
int deleteSupplier(Supplier supplier_list[],char sup_name[5]){}

/*Removes all suppliers from the list
*
* supplier_list : supplier list
*
* return : returns 1 if operation succeeded, 0 otherwise*/
int deleteAllSuppliers(Supplier supplier_list[]){}