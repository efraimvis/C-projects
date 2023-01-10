
#include "Cars.h"
#include "Clients.h"
#include "Suppliers.h"
#include "Common.h"
#include <stdio.h>

static Car CAR_LIST[N];
static Client CLIENT_LIST[M];
static Supplier SUP_LIST[K];

/*Test functions from Cars.c*/
void test_cars()
{
    int i,c,cap;
    createCarList(CAR_LIST);
    addNewCar(CAR_LIST,"0000800","11111","Renault","Megane","Black","2002","2002",80000,10000,1461);
    addNewCar(CAR_LIST,"0000500","11112","Renault","Megane","Black","2002","2002",80000,10000,1461);
    addNewCar(CAR_LIST,"0406001","11158","Renault","Megane","Black","2002","2002",80000,10000,1461);
    addNewCar(CAR_LIST,"0406004","11145","Renault","Megane","Black","2002","2002",80000,10000,1461);
    addNewCar(CAR_LIST,"0406001","11158","Renault","Megane","Black","2002","2002",80000,10000,1461);
    for(i=0;i<10;i++)
    {
        printCar(CAR_LIST[i]);
        printf("\n");
    }
    printf("-----------------------------------------------------------------------------\n");
    cap = 1461;
    c = carNumberWithGivenCapacity(CAR_LIST,cap);
    printf("There are %d cars with capacity %dcc\n", c, cap);
    printf("-----------------------------------------------------------------------------\n");
    deleteCar(CAR_LIST,"0000500");
    c = carNumberWithGivenCapacity(CAR_LIST,cap);
    printf("There are %d cars with capacity %dcc\n", c, cap);
    printf("-----------------------------------------------------------------------------\n");
}

/*Tests functions from Clients.c*/
void test_clients()
{
    int i;
    createClientList(CLIENT_LIST);
    addNewClient(CLIENT_LIST,"Gavril","Gavrilov","208697656","0000800",default_date(),default_time(),500);
    addNewClient(CLIENT_LIST,"Chuck","Eastwood","207697656","0406001",default_date(),default_time(),500);
    addNewClient(CLIENT_LIST,"Princess","Jackson","208699656","0406004",default_date(),default_time(),500);
    for(i=0;i<10;i++)
    {
        printClient(CLIENT_LIST[i]);
        printf("\n");
    }
    printf("-----------------------------------------------------------------------------\n");
    deleteClient(CLIENT_LIST,"207697656");
    for(i=0;i<10;i++)
    {
        printClient(CLIENT_LIST[i]);
        printf("\n");
    }
    printf("-----------------------------------------------------------------------------\n");
}

/*Test functions from Suppliers.c*/
void test_suppliers()
{
    int i;
    Greatest suppliers;
    char* sup[3];
    createSupplierList(SUP_LIST);
    addNewSupplier(SUP_LIST,"1234577890","UAZ","044752883",3,50);
    addNewSupplier(SUP_LIST,"1234577891","RAZ","044752884",3,575);
    addNewSupplier(SUP_LIST,"1234577892","TAZ","044752885",3,51);
    addNewSupplier(SUP_LIST,"1234577893","PAZ","044752886",3,5);
    addNewSupplier(SUP_LIST,"1234577894","QAZ","044752887",0,9999999999);
    addNewSupplier(SUP_LIST,"1234577895","WAZ","044752888",3,575);
    for(i=0;i<10;i++)
    {
        printSupplier(SUP_LIST[i]);
    }
    deleteSupplier(SUP_LIST,"WAZ");
    deleteSupplier(SUP_LIST,"TAZ");
    printf("-----------------------------------------------------------------------------\n");
    for(i=0;i<10;i++)
    {
        printSupplier(SUP_LIST[i]);
    }
    printf("-----------------------------------------------------------------------------\n");
    suppliers = threeGreatestSuppliers(SUP_LIST);
    sup[0] = suppliers.sup1;
    sup[1] = suppliers.sup2;
    sup[2] = suppliers.sup3;
    printf("Three geatest suppliers: \n");
    for(i=0;i<3;i++)
    {
        printf("%s\n", sup[i]);
    }
    printf("-----------------------------------------------------------------------------\n");
}

/*Tests functions from Common.c*/
void test_common()
{
    int n;
    char* year;
    year ="2002";
    n = clientNumberWithGivenCarYear(CLIENT_LIST,CAR_LIST,year);
    printf("Number of clients with car of year %s is %d \n",year,n);
    printf("-----------------------------------------------------------------------------\n");
}

/*Tests select functions from project with demo values*/
int main(void)
{
    test_cars();
    test_clients();
    test_suppliers();
    test_common();
    return 0;
}