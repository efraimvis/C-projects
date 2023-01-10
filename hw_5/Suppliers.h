#ifndef SUPPLIERS_H
#define SUPPLIERS_H

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
    char sup2[11];
    char sup3[11];
} Greatest;

typedef struct SupplierNode
{
    Supplier* supplier;
    struct SupplierNode* next;
} SupplierNode;

typedef struct supplierList 
{
    SupplierNode* first;
    SupplierNode* last;
} supplierList;

typedef struct supplierList* SupplierList;

/*Generates and initializes an empty linked list of SupplierNodes
*
* return : returns empty list of SupplierNodes, with pointers to first and last elements set to NULL
* if successful, NULL otherwise*/
SupplierList createSupplierList();

/*Adds a new SupplierNode containing a Supplier to list of suppliers
*
* bus_num : suppliers business number
* sup_name : supplier name
* phone_num : supplier phone number
* num_transactions : number of transactions with supplier
* total_transactions : total sum of transactions with supplier
* 
* return : returns 1 if operation succeeded, 0 otherwise and prints an error message*/
int addNewSupplier(SupplierList list, char bus_num[11],char* sup_name,char phone_num[11],int num_transactions,long total_transactions);

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

/*Generates a struct Greatest containing business numbers of the three greatest suppliers
*
* list - list of suppliers
*
* returns struct Greatest containing business numbers of the three greatest suppliers,
* on error returns a Greatest containing default values, and prints an error message*/
Greatest threeGreatestSuppliers(SupplierList list);

/*Recursively generates a struct Greatest containing business numbers of the three greatest suppliers
*
* list - list of suppliers
*
* returns struct Greatest containing business numbers of the three greatest suppliers,
* on error returns a Greatest containing default values, and prints an error message*/
Greatest threeGreatestSuppliers_REC(SupplierList list);

/*Deletes a SupplierNode containing Supplier with given business number from the list
*
* list - supplier list
* bus_num : given supplier business number
*
* return : returns 1 if operation succeeded,0 otherwise and prints an error message*/
int deleteSupplier(SupplierList list,char bus_num[11]);

/*Deletes all SupplierNodes from the list
*
* list : supplier list
*
* return : returns 1 if operation succeeded,0 otherwise and prints an error message*/
int deleteAllSuppliers(SupplierList list);

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

/*Prints all suppliers in given list; AVAILABLE TO DAVIS ONLY
*
* list - SupplierList
*
* returns 1 if successful, 0 otherwise and prints an error message*/
int printSuppliers(SupplierList list);

/*Returns pointer to a Supplier with given business number from list
*
* list - SupplierList
* reg - supplier business number
*
* returns requested Supplier if successful, NULL otherwise*/
Supplier* getSupplier(SupplierList list, char* bus_num);



#endif