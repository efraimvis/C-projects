#include "Suppliers.h"
#include "Checks.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define D_BUS_NUM "defaultnum"

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
int isValidSupplier(char bus_num[11],char* sup_name,char phone_num[11],int num_transactions,long total_transactions)
{
    if(hasNumDigitsString(bus_num,10))
    {
        if(isValidPhoneNumber(phone_num))
        {
            if(num_transactions >= 0 && num_transactions <= 99999 && total_transactions >= 0 && total_transactions <= 9999999999) return 1;
        }
    }
    return 0;
}

/*Compares two given Suppliers based on business number
*
* supplier1, supplier2 - given Suppliers
*
* return : returns negative value if supplier1 has a smaller business number,
* positive value if supplier1 has larger business number, 0 if Suppliers have the same business number*/
int supplierCompare(const void* supplier1, const void* supplier2)
{
    return strcmp(((Supplier*)supplier1)->business_num,((Supplier*)supplier2)->business_num);
}

/*Gets the total sum of transactions of a given Supplier
*
* supplier - Supplier (passed as void *)
*
* return : returns total sum of transactions for given Supplier*/
long double supplierTransactions(const void* supplier)
{
    return ((Supplier*)supplier)->total_sum_of_transactions;
}

/*Generate a supplier with given details
*
* bus_num : suppliers business number
* sup_name : supplier name
* phone_num : supplier phone number
* num_transactions : number of transactions with supplier
* total_transactions : total sum of transactions with supplier
*
* returns pointer to Supplier with given information if successful, NULL otherwise*/
Supplier* generateSupplier(char bus_num[11],char* sup_name,char phone_num[11],int num_transactions,long total_transactions)
{
    if(isValidSupplier(bus_num,sup_name,phone_num,num_transactions,total_transactions))
    {
        Supplier* supplier;
        supplier = (Supplier*)malloc(sizeof(Supplier));
        supplier->supplier_name = (char*)malloc(sizeof(strlen(sup_name)+1));
        if(supplier == NULL || supplier->supplier_name == NULL) return NULL;
        strcpy(supplier->business_num,bus_num);
        strcpy(supplier->supplier_name,sup_name);
        strcpy(supplier->phone_num,phone_num);
        supplier->num_of_transactions = num_transactions;
        supplier->total_sum_of_transactions = total_transactions;
        return supplier;
    }
    return NULL;
} 

/*Generates and initializes an empty Tree
*
* return : returns empty Tree, with root set to NULL
* if successful, NULL otherwise*/
Tree createSupplierTree()
{
    return createTree();
}

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
int addNewSupplier(Tree tree,char bus_num[11],char* sup_name,char phone_num[11],int num_transactions,long total_transactions)
{
    if(tree != NULL && isValidSupplier(bus_num,sup_name,phone_num,num_transactions,total_transactions))
    {
        Supplier* supplier = generateSupplier(bus_num,sup_name,phone_num,num_transactions,total_transactions);
        return addNewNode(tree,supplier,sizeof(Supplier),supplierCompare);
    }
    else
    {
        printf("\nError - null pointer to Supplier list or invalid Supplier\n");
    }
    return 0;
}

/*Prompts user for Supplier information and adds a new Supplier to a given Tree
*
* tree - given Tree
*
* returns 1 if successful, 0 otherwise and prints an error message*/
int inputSupplier(Tree tree)
{
    if(tree != NULL)
    {
        char bus_num[11];
        char sup_name[20];
        char phone_num[11];
        int num_transactions;
        long total_transactions;
        char dummy[2];
        gets(dummy);
        while(1)
        {
            printf("\nPlease enter supplier business number : ");
            gets(bus_num);
            if(!hasNumDigitsString(bus_num,10)) printf("\nInvalid business number\n");
            else if(getSupplier(tree,bus_num) != NULL) printf("\nThere is already a supplier with this business number\n");
            else break;
        }
        while(1)
        {
            printf("\nPlease enter supplier name : ");
            gets(sup_name);
            if(strlen(sup_name) == 0) printf("\nSupplier name must have at least one digit\n");
            else break;
        }
        while(1)
        {
            printf("\nPlease enter supplier phone number : ");
            gets(phone_num);
            if(!isValidPhoneNumber(phone_num)) printf("\nInvalid phone number\n");
            else break;
        }
        while(1)
        {
            printf("\nPlesae enter number of transactions : ");
            scanf("%d",&num_transactions);
            if(!(num_transactions >= 0 && num_transactions <= 99999)) printf("\nInvalid number of transactions\n");
            else break;
        }
        while(1)
        {
            printf("\nPlease enter total sum of transactions : ");
            scanf("%ld",&total_transactions);
            if(!(total_transactions >= 0 && total_transactions <= 9999999999)) printf("\nInvalid sum of transactions\n");
            else break;
        }
        if(addNewSupplier(tree,bus_num,sup_name,phone_num,num_transactions,total_transactions))
        {
            printf("\nSupplier added successfully!\n");
            return 1;
        }
        else
        {
            printf("\nCould not add supplier\n");
        }
    }
    else
    {
        printf("\nError - null pointer to list\n");
    }
    return 0;
}

/*Returns pointer to a Supplier with given business number from Tree
*
* tree - Tree
* bus_num - Supplier business number
*
* returns requested Supplier if successful, NULL otherwise*/
Supplier* getSupplier(Tree tree, char* bus_num)
{
    if(tree != NULL && hasNumDigitsString(bus_num,10))
    {
        if(tree->root != NULL)
        {
            Supplier* dummy;
            Supplier* returnSupplier;
            Tree node;
            dummy = (Supplier*)malloc(sizeof(Supplier));
            if(!dummy) return NULL;
            strcpy(dummy->business_num,bus_num);
            node = findNode(tree,dummy,sizeof(Supplier),supplierCompare);
            if(node == NULL || node->root == NULL)
            {
                free(dummy);
                free(node);
                node = NULL;
                dummy = NULL;
                return NULL;
            }
            returnSupplier = (Supplier*)node->root->value;
            free(dummy);
            free(node);
            node = NULL;
            dummy = NULL;
            return returnSupplier;
        }
    }
    return NULL;
}

/*Finds the average of supplier money (sum of total sums of transactions from all Suppliers, divided by number of Suppliers)
*
* root - Tree root
* numSuppliers - number of Suppliers in Tree
*
* return : returns average of supplier money (sum of total sums of transactions from all Suppliers, divided by number of Suppliers)*/
long double averageOfSupplierMoney(TreeNode* root, int numSuppliers)
{
    return averageKey(root,numSuppliers,supplierTransactions);
}

/*Deletes a TreeNode containing Supplier with given business number from the Tree
*
* tree - Tree
* bus_num : given business number
*
* return : returns 1 if operation succeeded,0 otherwise*/
int deleteSupplier(Tree tree,char bus_num[11])
{
    if(tree != NULL && tree->root != NULL && hasNumDigitsString(bus_num,10))
    {
        Supplier* dummy;
        int retval;
        dummy = (Supplier*)malloc(sizeof(Supplier));
        strcpy(dummy->business_num,bus_num);
        retval = removeNode(tree,dummy,sizeof(Supplier),supplierCompare);
        free(dummy);
        return retval;
    }
    else
    {
        printf("\nError - null pointer to Supplier list or bad Supplier name\n");
    }
    return 0;
}

/*Deletes all TreeNodes from the Tree
*
* tree : Tree
*
* return : returns 1 if operation succeeded,0 otherwise*/
int deleteAllSuppliers(Tree tree)
{
    if(tree != NULL)
    {
        if(tree->root == NULL) return 1;
        else
        {
            return freeTree(tree);
        }
    }
    else
    {
        printf("\nError - null pointer to Supplier list\n");
    }
    return 0;
}

/*Prints information for given Supplier
*
* supplier - given supplier
*
* returns 1 always*/
int printSupplier(Supplier supplier)
{
    printf("{business_num:%s supplier_name:%s phone_num:%s num_transactions:%d total_transactions:%ld}\n",supplier.business_num,supplier.supplier_name,supplier.phone_num,supplier.num_of_transactions,supplier.total_sum_of_transactions);
    return 1;
}

int print_supplier(const void* supplier)
{
    return printSupplier(*((Supplier*)supplier));
}

/*Prints all suppliers in given Tree
*
* tree - given Tree
*
* returns 1 if successful, 0 otherwise*/
int printSuppliers(Tree tree)
{
    if(tree != NULL && tree->root != NULL)
    {
        printTree(tree,print_supplier);
    }
    return 0;
}

/*Gets business numbers of the three greatest Suppliers in given Tree in the form of an array of 3 strings
* modifies passed char array
*
* tree - given Tree
* arr - array of 3 business numbers
*
* return : 1 if successful, 0 otherwise; On error prints message*/
int threeGreatestSuppliers(Tree tree,char arr[3][11])
{
    if(tree != NULL && tree->elementCount >= 3)
    {
        int i;
        Greatest greatest;
        Supplier** suppliers;
        greatest.max1 = greatest.max2 = greatest.max3 = 0;
        strcpy(greatest.sup1,D_BUS_NUM);
        strcpy(greatest.sup2,D_BUS_NUM);
        strcpy(greatest.sup3,D_BUS_NUM);
        suppliers = (Supplier**)treeToArray(tree,sizeof(Supplier*));
        for(i=0;i<tree->elementCount;i++)
        {
            if(suppliers[i]->total_sum_of_transactions > greatest.max1)
            {
                greatest.max3 = greatest.max2;
                strcpy(greatest.sup3,greatest.sup2);
                greatest.max2 = greatest.max1;
                strcpy(greatest.sup2,greatest.sup1);
                greatest.max1 = suppliers[i]->total_sum_of_transactions;
                strcpy(greatest.sup1,suppliers[i]->business_num);
            }
            else if(suppliers[i]->total_sum_of_transactions > greatest.max2)
            {
                greatest.max3 = greatest.max2;
                strcpy(greatest.sup3,greatest.sup2);
                greatest.max2 = suppliers[i]->total_sum_of_transactions;
                strcpy(greatest.sup2,suppliers[i]->business_num);
            }
            else if(suppliers[i]->total_sum_of_transactions > greatest.max3)
            {
                greatest.max3 = suppliers[i]->total_sum_of_transactions;
                strcpy(greatest.sup3,suppliers[i]->business_num);
            }
        }
        free(suppliers);
        suppliers = NULL;
        strcpy(arr[2],greatest.sup3);
        strcpy(arr[1],greatest.sup2);
        strcpy(arr[0],greatest.sup1);
        return 1;
    }
    else printf("\nError -tree is null or has less than 3 elements\n");
    return 0;
}

