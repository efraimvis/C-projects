#ifndef SUPPLIERS_H
#define SUPPLIERS_H

#define K 50

typedef struct SSuplier 
{
    char business_num[11];
    char supplier_name[6];
    char phone_num[11];
    int num_of_transactions;
    long total_sum_of_transactions;
} Supplier;

typedef struct GGreatest
{
    char sup1[11];
    char sup2[11];
    char sup3[11];
} Greatest;

/*Generates a default supplier
*
* returns a supplier with default parameters*/
Supplier createDefaultSupplier();

/*Checks if supplier is default (by business number only)
*
* supplier : given supplier
*
* return 1 if supplier is default (has default business number), 0 otherwise*/
int isDefaultSupplier(Supplier supplier);

/*Initializes an array of suppliers to default values
*
* list : pointer to list of suppliers
*
* return : returns 1 if operation succeeded, 0 if list pointer is null and prints an error message*/
int createSupplierList(Supplier* list);

/*Adds a new supplier with given information to the list
*
* bus_num : suppliers business number
* sup_name : supplier name
* phone_num : supplier phone number
* num_transactions : number of transactions with supplier
* total_transactions : total sum of transactions with supplier
* 
* return : returns 1 if operation succeeded, 0 otherwise and prints an error message*/
int addNewSupplier(Supplier* list, char bus_num[11],char sup_name[6],char phone_num[11],int num_transactions,long total_transactions);

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
int isValidSupplier(char bus_num[11],char sup_name[6],char phone_num[11],int num_transactions,long total_transactions);

/*Returns a struct Greatest, containing the business numbers of the 3 suppliers with which the largest transactions were carried out
*
* supplier_list : supplier list
*
* return : Returns a Greatest, containing the business numbers of the 3 suppliers with which the largest transactions were carried out if operation succeeded,
* Greatest with default values otherwise, and prints error message*/
Greatest threeGreatestSuppliers(Supplier* list);

/*Removes a supplier with given name from the list (sets supplier in index to default)
*
* supplier_list : supplier list
* sup_name : supplier name
*
* return : returns 1 if operation succeeded, 0 otherwise and prints error message*/
int deleteSupplier(Supplier* list,char sup_name[6]);

/*Removes all suppliers from the list (sets to default)
*
* supplier_list : supplier list
*
* return : returns 1 if operation succeeded, 0 otherwise and prints an error message*/
int deleteAllSuppliers(Supplier* list);

/*Prints information of given supplier
*
* returns 1*/
int printSupplier(Supplier supplier);

#endif