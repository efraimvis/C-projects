#ifndef SUPPLIERS_H
#define SUPPLIERS_H

#include "Tree.h"

typedef struct SSuplier 
{
    char business_num[11];
    char* supplier_name;
    char phone_num[11];
    int num_of_transactions;
    long total_sum_of_transactions;
} Supplier;

typedef struct GGreatest
{
    char sup1[11];
    long max1;
    char sup2[11];
    long max2;
    char sup3[11];
    long max3;
} Greatest;

/*Compares two given Suppliers based on business number
*
* supplier1, supplier2 - given Suppliers
*
* return : returns negative value if supplier1 has a smaller business number,
* positive value if supplier1 has larger business number, 0 if Suppliers have the same business number*/
int supplierCompare(const void* supplier1, const void* supplier2);

/*Generates and initializes an empty Tree
*
* return : returns empty Tree, with root set to NULL
* if successful, NULL otherwise*/
Tree createSupplierTree();

/*Adds a new TreeNode containing a Supplier to given Tree
*
* tree - given Tree
* bus_num : suppliers business number
* sup_name : supplier name
* phone_num : supplier phone number
* num_transactions : number of transactions with supplier
* total_transactions : total sum of transactions with supplier
* 
* return : returns 1 if operation succeeded, 0 otherwise and prints an error message*/
int addNewSupplier(Tree tree, char bus_num[11],char* sup_name,char phone_num[11],int num_transactions,long total_transactions);

/*Prompts user for Supplier information and adds a new Supplier to a given Tree
*
* tree - given Tree
*
* returns 1 if successful, 0 otherwise and prints an error message*/
int inputSupplier(Tree tree);

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
int isValidSupplier(char bus_num[11],char* sup_name,char phone_num[11],int num_transactions,long total_transactions);

/*Gets business numbers of the three greatest Suppliers in given Tree in the form of struct Greatest
*
* tree - given Tree
*
* return : returns struct Greatest containing business numbers of the three suppliers with whom there were
* the largest total sums of transactions*/
Greatest threeGreatestSuppliers(Tree tree);

/*Deletes a TreeNode containing Supplier with given business number from the Tree
*
* tree - Tree
* bus_num : given business number
*
* return : returns 1 if operation succeeded,0 otherwise*/
int deleteSupplier(Tree tree,char bus_num[11]);

/*Deletes all TreeNodes from the Tree
*
* tree : Tree
*
* return : returns 1 if operation succeeded,0 otherwise*/
int deleteAllSuppliers(Tree tree);

/*Prints information for given Supplier
*
* supplier - given supplier
*
* returns 1 always*/
int printSupplier(Supplier supplier);

/*Generate a supplier with given details
*
* bus_num : suppliers business number
* sup_name : supplier name
* phone_num : supplier phone number
* num_transactions : number of transactions with supplier
* total_transactions : total sum of transactions with supplier
*
* returns pointer to Supplier with given information if successful, NULL otherwise*/
Supplier* generateSupplier(char bus_num[11],char* sup_name,char phone_num[11],int num_transactions,long total_transactions);

/*Prints all suppliers in given Tree
*
* tree - given Tree
*
* returns 1 if successful, 0 otherwise*/
int printSuppliers(Tree tree);

/*Returns pointer to a Supplier with given business number from Tree
*
* tree - Tree
* bus_num - Supplier business number
*
* returns requested Supplier if successful, NULL otherwise*/
Supplier* getSupplier(Tree tree, char* bus_num);

/*Finds the average of supplier money (sum of total sums of transactions from all Suppliers, divided by number of Suppliers)
*
* root - Tree root
* numSuppliers - number of Suppliers in Tree
*
* return : returns average of supplier money (sum of total sums of transactions from all Suppliers, divided by number of Suppliers)*/
long averageOfSupplierMoney(TreeNode* root, int numSuppliers);



#endif