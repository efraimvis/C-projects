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
        return insert(tree,supplier,sizeof(Supplier),supplierCompare);
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
            TreeNode* node;
            dummy = (Supplier*)malloc(sizeof(Supplier));
            if(!dummy) return NULL;
            strcpy(dummy->business_num,bus_num);
            node = search(tree,dummy,supplierCompare);
            if(node == NULL)
            {
                free(dummy);
                dummy = NULL;
                return NULL;
            }
            returnSupplier = (Supplier*)node->value;
            free(dummy);
            dummy = NULL;
            return returnSupplier;
        }
    }
    return NULL;
}

/*Recursive helper function to function threeGreatestSuppliers
* 
* root - Tree root
* suppliers - struct Greatest representing business numbers of greatest suppliers
*
* return : returns 1 if successful, 0 otherwise*/
int threeGreatestSuppliers_helper(TreeNode* root,Greatest* suppliers)
{
    if(!root) return 0;
    if(((Supplier*)root->value)->total_sum_of_transactions >= suppliers->max1)
    {
        suppliers->max3 = suppliers->max2;
        strcpy(suppliers->sup3,suppliers->sup2);
        suppliers->max2 = suppliers->max1;
        strcpy(suppliers->sup2,suppliers->sup1);
        suppliers->max1 = ((Supplier*)root->value)->total_sum_of_transactions;
        strcpy(suppliers->sup1,((Supplier*)root->value)->business_num);
    }
    else if(((Supplier*)root->value)->total_sum_of_transactions >= suppliers->max2)
    {
        suppliers->max3 = suppliers->max2;
        strcpy(suppliers->sup3,suppliers->sup2);
        suppliers->max2 = ((Supplier*)root->value)->total_sum_of_transactions;
        strcpy(suppliers->sup2,((Supplier*)root->value)->business_num);
    }
    else if(((Supplier*)root->value)->total_sum_of_transactions >= suppliers->max3)
    {
        suppliers->max3 = ((Supplier*)root->value)->total_sum_of_transactions;
        strcpy(suppliers->sup3,((Supplier*)root->value)->business_num);
    }
    threeGreatestSuppliers_helper(root->left,suppliers);
    threeGreatestSuppliers_helper(root->right,suppliers);
    return 1;
}

/*Gets business numbers of the three greatest Suppliers in given Tree in the form of struct Greatest
*
* tree - given Tree
*
* return : returns struct Greatest containing business numbers of the three suppliers with whom there were
* the largest total sums of transactions*/
Greatest threeGreatestSuppliers(Tree tree)
{
    Greatest suppliers;
    strcpy(suppliers.sup1,D_BUS_NUM);
    strcpy(suppliers.sup2,D_BUS_NUM);
    strcpy(suppliers.sup3,D_BUS_NUM);
    suppliers.max1 = suppliers.max2 = suppliers.max3 = 0;
    if(tree != NULL)
    {
        if(tree->elementCount >= 3)
        {
            threeGreatestSuppliers_helper(tree->root,&suppliers);
            return suppliers;
        }
        else
        {
            printf("\nLess than 3 suppliers\n");
        }
    }
    return suppliers;
}

/*Finds the average of supplier money (sum of total sums of transactions from all Suppliers, divided by number of Suppliers)
*
* root - Tree root
* numSuppliers - number of Suppliers in Tree
*
* return : returns average of supplier money (sum of total sums of transactions from all Suppliers, divided by number of Suppliers)*/
long averageOfSupplierMoney(TreeNode* root,int numSuppliers)
{
    if(!root) return 0;
    return ((((Supplier*)root->value)->total_sum_of_transactions)/(numSuppliers))+averageOfSupplierMoney(root->right,numSuppliers)+averageOfSupplierMoney(root->left,numSuppliers);
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
        retval = deleteNode(tree,dummy,sizeof(Supplier),supplierCompare);
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
            return deleteTree(tree);
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

/*Recursive helper function to function printSuppliers
*
* root - Tree root
*
* returns 1 if successful, 0 otherwise*/
int printSuppliers_helper(TreeNode* root)
{
    if(!root) return 0;
    printSuppliers_helper(root->left);
    printf("\n");
    printSupplier(*((Supplier*)root->value));
    printSuppliers_helper(root->right);
    return 1;
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
        printSuppliers_helper(tree->root);
    }
    return 0;
}

