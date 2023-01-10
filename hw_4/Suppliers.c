#include "Suppliers.h"
#include "Checks.h"
#include <string.h>
#include <stdio.h>

#define D_BUS_NUM "defaultnum"
#define D_SUP_NAME "d_val"
#define D_PHONE "defaultnum"

/*Generates a default supplier
*
* returns a supplier with default parameters*/
Supplier createDefaultSupplier()
{
    Supplier supplier;
    strcpy(supplier.business_num,D_BUS_NUM);
    strcpy(supplier.supplier_name,D_SUP_NAME);
    strcpy(supplier.phone_num,D_PHONE);
    supplier.num_of_transactions = 0;
    supplier.total_sum_of_transactions = 0;
    return supplier;
}

/*Checks if supplier is default (by business number only)
*
* supplier : given supplier
*
* return 1 if supplier is default (has default business number), 0 otherwise*/
int isDefaultSupplier(Supplier supplier)
{
    if(strcmp(supplier.business_num,D_BUS_NUM) == 0) return 1;
    return 0;
}

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
int isValidSupplier(char bus_num[11],char sup_name[6],char phone_num[11],int num_transactions,long total_transactions)
{
    if(hasNumDigitsString(bus_num,10))
    {
        if(strlen(sup_name) <= 5)
        {
            if(isValidPhoneNumber(phone_num))
            {
                if(num_transactions >= 0 && getNumDigits(num_transactions) <= 5 && total_transactions >= 0 && getNumDigits(total_transactions) <= 10) return 1;
            }
        }
    }
    return 0;
}

/*Initializes an array of suppliers to default values
*
* list : pointer to list of suppliers
*
* return : returns 1 if operation succeeded, 0 if list pointer is null and prints an error message*/
int createSupplierList(Supplier* list)
{
    if(list != NULL)
    {
        int i;
        for(i=0;i<K;i++)
        {
            list[i] = createDefaultSupplier();
        }
        return 1;
    }
    else 
    {
        printf("\nError - null pointer to Supplier array\n");
        return 0;
    }
}

/*Adds a new supplier with given information to the list
*
* bus_num : suppliers business number
* sup_name : supplier name
* phone_num : supplier phone number
* num_transactions : number of transactions with supplier
* total_transactions : total sum of transactions with supplier
* 
* return : returns 1 if operation succeeded, 0 otherwise and prints an error message*/
int addNewSupplier(Supplier* list,char bus_num[11],char sup_name[6],char phone_num[11],int num_transactions,long total_transactions)
{
    if(list != NULL && isValidSupplier(bus_num,sup_name,phone_num,num_transactions,total_transactions))
    {
        int i;
        i=0;
        while(!isDefaultSupplier(list[i]) && i < K)
        {
            if((strcmp(list[i].supplier_name,sup_name) != 0) && (strcmp(list[i].business_num,bus_num) != 0)) i++;
            else return 0;
        }
        if(i < K) 
        {
            Supplier supplier;
            strcpy(supplier.business_num,bus_num);
            strcpy(supplier.supplier_name,sup_name);
            strcpy(supplier.phone_num,phone_num);
            supplier.num_of_transactions = num_transactions;
            supplier.total_sum_of_transactions = total_transactions;
            list[i] = supplier;
            return 1;
        }
    }
    else
    {
        printf("\nError - null pointer to Supplier list or invalid Supplier\n");
    }
    return 0;
}

/*Returns a struct Greatest, containing the business numbers of the 3 suppliers with which the largest transactions were carried out
*
* supplier_list : supplier list
*
* return : Returns a Greatest, containing the business numbers of the 3 suppliers with which the largest transactions were carried out if operation succeeded,
* Greatest with default values otherwise, and prints error message*/
Greatest threeGreatestSuppliers(Supplier* list)
{
    int i;
    Supplier max1, max2 ,max3;
    Greatest suppliers;
    max1 = createDefaultSupplier();
    max2 = createDefaultSupplier();
    max3 = createDefaultSupplier();
    strcpy(suppliers.sup1,D_BUS_NUM);
    strcpy(suppliers.sup2,D_BUS_NUM);
    strcpy(suppliers.sup3,D_BUS_NUM);
    if(list != NULL)
    {
        for(i=0;i<K;i++)
        {
            if(list[i].total_sum_of_transactions > max1.total_sum_of_transactions)
            {
                max3 = max2;
                max2 = max1;
                max1 = list[i];
            }
            else if(list[i].total_sum_of_transactions > max2.total_sum_of_transactions)
            {
                max3 = max2;
                max2 = list[i];
            }
            else if(list[i].total_sum_of_transactions > max3.total_sum_of_transactions)
            {
                max3 = list[i];
            }
        }
        strcpy(suppliers.sup1,max1.business_num);
        strcpy(suppliers.sup2,max2.business_num);
        strcpy(suppliers.sup3,max3.business_num);
    }
    else
    {
        printf("\nError - null pointer to Supplier list\n");
    }
    return suppliers;
}

/*Removes a supplier with given name from the list (sets supplier in index to default)
*
* supplier_list : supplier list
* sup_name : supplier name
*
* return : returns 1 if operation succeeded, 0 otherwise and prints error message*/
int deleteSupplier(Supplier* list,char sup_name[6])
{
    if(list != NULL)
    {
        int i;
        for(i=0;i<K;i++)
        {
            if(!strcmp(list[i].supplier_name,sup_name))
            {
                list[i] = createDefaultSupplier();
                return 1;
            }
        }
    }
    else
    {
        printf("\nError - null pointer to Supplier list or bad Supplier name\n");
    }
    return 0;
}

/*Removes all suppliers from the list (sets to default)
*
* supplier_list : supplier list
*
* return : returns 1 if operation succeeded, 0 otherwise and prints an error message*/
int deleteAllSuppliers(Supplier* list)
{
    if(list != NULL)
    {
        createSupplierList(list);
        return 1;
    }
    else
    {
        printf("\nError - null pointer to Supplier list\n");
    }
    return 0;
}

/*Prints information of given supplier
*
* returns 1*/
int printSupplier(Supplier supplier)
{
    printf("{business_num:%s supplier_name:%s phone_num:%s num_transactions:%d total_transactions:%ld}\n",supplier.business_num,supplier.supplier_name,supplier.phone_num,supplier.num_of_transactions,supplier.total_sum_of_transactions);
    return 1;
}