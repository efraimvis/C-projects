#include "Suppliers.h"
#include "Checks.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define D_BUS_NUM "defaultnum"
#define D_SUP_NAME "d_val"
#define D_PHONE "defaultnum"


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

/*Generates and initializes an empty linked list of SupplierNodes
*
* return : returns empty list of SupplierNodes, with pointers to first and last elements set to NULL
* if successful, NULL otherwise*/
SupplierList createSupplierList()
{
    SupplierList list;
    list = (SupplierList)malloc(sizeof(struct supplierList));
    if(list == NULL) return NULL;
    list->first = NULL;
    list->last = NULL;
    return list;
}

/*Adds a new SupplierNode containing given Supplier to the start of a list
*
* list - SupplierList
* car - pointer to a Supplier
*
* returns 1 if SupplierNode was added successfully, 0 otherwise*/
int addToStart(SupplierList list, Supplier* supplier)
{
    if(list != NULL)
    {
        SupplierNode* newNode;
        newNode = (SupplierNode*)malloc(sizeof(SupplierNode));
        if(newNode == NULL) return 0;
        newNode->supplier = supplier;
        newNode->next = list->first;
        list->first = newNode;
        if(newNode->next == NULL) list->last = newNode;
        return 1;
    }
    return 0;
}

/*Adds a new SupplierNode containing given Supplier to the end of a list
*
* list - SupplierList
* car - pointer to a Supplier
*
* returns 1 if SupplierNode was added successfully, 0 otherwise*/
int addToEnd(SupplierList list, Supplier* supplier)
{
    if(list != NULL)
    {
        SupplierNode* newNode;
        newNode = (SupplierNode*)malloc(sizeof(SupplierNode));
        if(newNode == NULL) return 0;
        newNode->supplier = supplier;
        if(list->last != NULL )list->last->next = newNode;
        else list->first = newNode;
        list->last = newNode;
        newNode->next = NULL;
        return 1;
    }
    return 0;
}

/*Adds a new SupplierNode containing a Supplier to list of suppliers
*
* bus_num : suppliers business number
* sup_name : supplier name
* phone_num : supplier phone number
* num_transactions : number of transactions with supplier
* total_transactions : total sum of transactions with supplier
* 
* return : returns 1 if operation succeeded, 0 otherwise and prints an error message*/
int addNewSupplier(SupplierList list,char bus_num[11],char* sup_name,char phone_num[11],int num_transactions,long total_transactions)
{
    if(list != NULL && isValidSupplier(bus_num,sup_name,phone_num,num_transactions,total_transactions))
    {
        Supplier* supplier = generateSupplier(bus_num,sup_name,phone_num,num_transactions,total_transactions);
        if(list->first == NULL)
        {
            addToStart(list,supplier);
            return 1;
        }
        if(strcmp(supplier->business_num,list->first->supplier->business_num) <= 0)
        {
            addToStart(list,supplier);
            return 1;
        }
        else if(strcmp(supplier->business_num,list->last->supplier->business_num) >= 0)
        {
            addToEnd(list,supplier);
            return 1;
        }
        else
        {
            SupplierNode* scan;
            SupplierNode* newNode;
            newNode = (SupplierNode*)malloc(sizeof(SupplierNode));
            if(newNode == NULL) return 0;
            newNode->supplier = supplier;
            scan = list->first;
            while(strcmp(supplier->business_num,scan->supplier->business_num) < 0) scan = scan->next;
            newNode->next = scan->next;
            scan->next = newNode;
            return 1;
        }
    }
    else
    {
        printf("\nError - null pointer to Supplier list or invalid Supplier\n");
    }
    return 0;
}

/*Returns pointer to a Supplier with given business number from list
*
* list - SupplierList
* reg - supplier business number
*
* returns requested Supplier if successful, NULL otherwise*/
Supplier* getSupplier(SupplierList list, char* bus_num)
{
    if(list != NULL && list->first != NULL)
    {
        SupplierNode* scan;
        scan = list->first;
        while(scan != NULL)
        {
            if(strcmp(scan->supplier->business_num,bus_num) == 0) return scan->supplier;
            scan = scan->next;
        }
        scan = NULL;
    }
    return NULL;
}

/*Generates a struct Greatest containing business numbers of the three greatest suppliers
*
* list - list of suppliers
*
* returns struct Greatest containing business numbers of the three greatest suppliers,
* on error returns a Greatest containing default values, and prints an error message*/
Greatest threeGreatestSuppliers(SupplierList list)
{
    Greatest suppliers;
    strcpy(suppliers.sup1,D_BUS_NUM);
    strcpy(suppliers.sup2,D_BUS_NUM);
    strcpy(suppliers.sup3,D_BUS_NUM);
    if(list!= NULL && list->first != NULL && list->first->next != NULL && list->first->next->next != NULL)
    {
        long max1,max2,max3;
        SupplierNode* scan;
        max1 = 0;
        max2 = 0;
        max3 = 0;
        scan = list->first;
        while(scan != NULL)
        {
            if(scan->supplier->total_sum_of_transactions >= max1)
            {
                max3 = max2;
                strcpy(suppliers.sup3,suppliers.sup2);
                max2 = max1;
                strcpy(suppliers.sup2,suppliers.sup1);
                max1 = scan->supplier->total_sum_of_transactions;
                strcpy(suppliers.sup1,scan->supplier->business_num);
            }
            else if(scan->supplier->total_sum_of_transactions >= max2)
            {
                max3 = max2;
                strcpy(suppliers.sup3,suppliers.sup2);
                max2 = scan->supplier->total_sum_of_transactions;
                strcpy(suppliers.sup2,scan->supplier->business_num);
            }
            else if(scan->supplier->total_sum_of_transactions >= max3)
            {
                max3 = scan->supplier->total_sum_of_transactions;
                strcpy(suppliers.sup3,scan->supplier->business_num);
            }
            scan = scan->next;
        }
    }
    else
    {
        printf("\nError - null list or less than 3 suppliers\n");
    }
    return suppliers;
}

/*Helper function for threeGreatestSuppliers_REC
*
* scan - pointer to SupplierNode
* suppliers - struct containing business numbers
* max1, max2, max3 - values of 3 largest total sums of transactions
*
* returns struct Greatest containing business numbers of the three greatest suppliers,
* on error returns a Greatest containing default values*/
Greatest threeGreatestSuppliers_REC_helper(SupplierNode* scan,Greatest suppliers,int max1, int max2, int max3)
{
    if(scan == NULL) return suppliers;
    else
    {
        if(scan->supplier->total_sum_of_transactions >= max1)
        {
            max3 = max2;
            strcpy(suppliers.sup3,suppliers.sup2);
            max2 = max1;
            strcpy(suppliers.sup2,suppliers.sup1);
            max1 = scan->supplier->total_sum_of_transactions;
            strcpy(suppliers.sup1,scan->supplier->business_num);
        }
        else if(scan->supplier->total_sum_of_transactions >= max2)
        {
            max3 = max2;
            strcpy(suppliers.sup3,suppliers.sup2);
            max2 = scan->supplier->total_sum_of_transactions;
            strcpy(suppliers.sup2,scan->supplier->business_num);
        }
        else if(scan->supplier->total_sum_of_transactions >= max3)
        {
            max3 = scan->supplier->total_sum_of_transactions;
            strcpy(suppliers.sup3,scan->supplier->business_num);
        }
        return threeGreatestSuppliers_REC_helper(scan->next,suppliers,max1,max2,max3);
    }
}

/*Recursively generates a struct Greatest containing business numbers of the three greatest suppliers
*
* list - list of suppliers
*
* returns struct Greatest containing business numbers of the three greatest suppliers,
* on error returns a Greatest containing default values, and prints an error message*/
Greatest threeGreatestSuppliers_REC(SupplierList list)
{
    Greatest suppliers;
    strcpy(suppliers.sup1,D_BUS_NUM);
    strcpy(suppliers.sup2,D_BUS_NUM);
    strcpy(suppliers.sup3,D_BUS_NUM);
    if(list != NULL && list->first != NULL && list->first->next != NULL && list->first->next->next != NULL)
    {
        int max1;
        int max2;
        int max3;
        max1 = max2 = max3 = 0;
        suppliers = threeGreatestSuppliers_REC_helper(list->first,suppliers,max1,max2,max3);
    }
    else
    {
        printf("\nError - null list or less than 3 suppliers\n");
    }
    return suppliers;
}

/*Deletes a SupplierNode containing Supplier with given business number from the list
*
* list - supplier list
* bus_num : given supplier business number
*
* return : returns 1 if operation succeeded,0 otherwise and prints an error message*/
int deleteSupplier(SupplierList list,char bus_num[11])
{
    if(list != NULL && list->first != NULL && hasNumDigitsString(bus_num,10))
    {
        if(strcmp(bus_num,list->first->supplier->business_num) >= 0 && strcmp(bus_num,list->last->supplier->business_num) <= 0)
        {
            SupplierNode* scan;
            scan = list->first;
            if(strcmp(list->first->supplier->business_num,bus_num) == 0)
            {
                list->first = scan->next;
                free(scan->supplier);
                free(scan);
                return 1;
            }
            else if(strcmp(list->last->supplier->business_num,bus_num) == 0)
            {
                while(scan->next != list->last) scan = scan->next;
                list->last = scan;
                free(scan->next->supplier);
                free(scan->next);
                list->last->next = NULL;
                return 1;
            }
            else if(list->first->next == NULL && strcmp(list->first->supplier->business_num,bus_num) != 0) return 0;
            else
            {
                SupplierNode* temp;
                while((strcmp(scan->next->supplier->business_num,bus_num) != 0) && scan->next->next != NULL) scan = scan->next;
                if(scan->next == list->last)
                {
                    printf("\nError - supplier not in list\n");
                    return 0;
                }
                temp = scan->next;
                scan->next = temp->next;
                free(temp->supplier);
                free(temp);
                return 1;
            }
        }
        else
        {
            printf("\nError - supplier not in list\n");
            return 0;
        }
    }
    else
    {
        printf("\nError - null pointer to Supplier list or bad Supplier name\n");
    }
    return 0;
}

/*Deletes all SupplierNodes from the list
*
* list : supplier list
*
* return : returns 1 if operation succeeded,0 otherwise and prints an error message*/
int deleteAllSuppliers(SupplierList list)
{
    if(list != NULL)
    {
        if(list->first == NULL) return 1;
        else
        {
            SupplierNode* scan;
            scan = list->first;
            while(scan != NULL)
            {
                SupplierNode* temp = scan;
                list->first = scan->next;
                scan = scan->next;
                free(temp->supplier);
                free(temp);
            }
            list->first = NULL;
            list->last = NULL;
            return 1;
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

#ifdef DAVIS
/*Prints all suppliers in given list; AVAILABLE TO DAVIS ONLY
*
* list - SupplierList
*
* returns 1 if successful, 0 otherwise and prints an error message*/
int printSuppliers(SupplierList list)
{
    if(list != NULL && list->first != NULL)
    {
        SupplierNode* scan;
        scan = list->first;
        while(scan != NULL)
        {
            printSupplier(*scan->supplier);
            scan = scan->next;
        }
        scan = NULL;
        return 1;
    }
    else
    {
        printf("\nError - list empty or null\n");
    }
    return 0;
}
#endif