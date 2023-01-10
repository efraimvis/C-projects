#include <stdio.h>
#include <stdlib.h>

/*Representation of an undirected graph of ints*/
struct undirected
{
    int* matrix;
    int numVertices;
};

typedef struct undirected* UGraph;

/*Determines whether a number is in a given array
*
* arr - given array
* size - size of given array
* element - number to find
*
* return : returns 1 if element is in array, 0 otherwise;
* on error prints message*/
int isInArray(int arr[],int size, int element)
{
    if(arr != NULL)
    {
        int i;
        for(i=0;i<size;i++)
        {
            if(arr[i] == element) return 1;
        }
    }
    else printf("\nError - null pointer to array\n");
    return 0;
}

/*Finds the complement of a given set in the universal set of n integers 0 through n-1
*
* n - number representing exclusive upper bound of universal set
* set - set of integers
* setSize - size of given set
*
* return : returns int array of size (n-setSize) representing complement of given set in universal set
* on error returns null*/
int* getComplement(int n,int set[],int setSize)
{
    if(n> 0 && setSize > 0 && setSize <= n)
    {
        int i,compMember;
        int* complement;
        int compSize;
        compSize = n-setSize;
        complement = (int*)calloc(compSize,sizeof(int));
        if(!complement) return 0;
        i=0;
        for(compMember=0;compMember<n;compMember++)
        {
            if(!isInArray(set,setSize,compMember))
            {
                complement[i] = compMember;
                i++;
            }
        }
        return complement;
    }
    return NULL;
}

/*Determines whether a group of vertices of a given graph is a main group, and prints appropriate message
*
* Graph - given adjacency matrix representation of an undirected graph
* graph_N - size of a single side of given adjacency matrix (number of vertices in graph)
* Group - given group of vertices
* group_M - size of given group of vertices
*
* return : returns 1 if group is a main group, 0 otherwise; On error prints message
*
*------ NOTICE : Commented out line can be enabled to see internal logic----------*/
int isMainGroup(int* Graph, int graph_N,int Group[], int group_M)
{
    if(Graph != NULL && Group != NULL && graph_N > 0 && group_M >0 && group_M<graph_N)
    {
        int compSize, compI,groupI;
        int* complement;
        compSize = graph_N-group_M;
        complement = getComplement(graph_N,Group,group_M);
        if(!complement) return 0;
        for(compI=0;compI<compSize;compI++)
        {
            int flag;
            flag = 0;
            for(groupI=0;groupI<group_M;groupI++)
            {
                /**
                printf("complement[compI] : %d | Group[groupI] : %d || val: %d \n",complement[compI],Group[groupI],Graph[complement[compI]*graph_N+Group[groupI]]);
                **/
                if(Graph[complement[compI]*graph_N+Group[groupI]] == 1) flag++;
            }
            if(flag == 0)
            {
                printf("\nGroup {");
                for(groupI=0;groupI<group_M;groupI++)
                {
                    if(groupI < group_M-1)  printf("%d, ",Group[groupI]);
                    else printf("%d",Group[groupI]);
                }
                printf("} is not a main group\n");
                free(complement);
                complement = NULL;
                return 0;
            }
        }
        printf("\nGroup {");
        for(groupI=0;groupI<group_M;groupI++)
        {
            if(groupI < group_M-1)  printf("%d, ",Group[groupI]);
            else printf("%d",Group[groupI]);
        }
        printf("} is a main group\n");
        free(complement);
        complement = NULL;
        return 1;
    }
    else printf("\nError - bad parameters\n");
    return 0;
}

/*Generates an undirected graph of ints from user input
*
* return : returns the UGraph generated*/
UGraph createGraph()
{
    UGraph Graph;
    int* matrix;
    int numVertices;
    Graph = (UGraph)malloc(sizeof(struct undirected));
    if(!Graph) return NULL;
    while(1)
    {
        printf("\nPlease enter number of vertices (positive integer between 2 and 20): ");
        scanf("%d",&numVertices);
        if(!(numVertices > 1 && numVertices <=20)) printf("\nNumber of vertices must be between 2 and 20\n");
        else break;
    }
    matrix = (int*)calloc((numVertices*numVertices),sizeof(int));
    if(!matrix) return NULL;
    Graph->matrix = matrix;
    Graph->numVertices = numVertices;
    return Graph;
}

/*Adds an edge to a graph
*
* Graph - given undirected graph
*
* return : returns 1 if edge was added successfully, 0 otherwise*/
int addEdge(UGraph Graph)
{
    if(Graph != NULL && Graph->matrix != NULL && Graph->numVertices > 0)
    {
        int from;
        int to;
        while(1)
        { 
            printf("\nPlease enter edge to to add (eg. 0 5): ");  
            scanf("%d %d",&from,&to);
            if(!(from >= 0 && from < Graph->numVertices && to >= 0 && to < Graph->numVertices && from != to)) printf("\nEdge must be between valid vertices in graph (loops not allowed)\n");
            else break;
        }
        Graph->matrix[from*Graph->numVertices + to] = 1;
        Graph->matrix[to*Graph->numVertices + from] = 1;
        if(Graph->matrix[from*Graph->numVertices + to] == 1 && Graph->matrix[to*Graph->numVertices + from] == 1)
        {
            printf("\nEdge (%d,%d) added successfully!\n",from,to);
            return 1;
        }
    }
    else printf("\nError - bad graph\n");
    return 0;
}

/*Creates a graph from user input, and tests various groups entered by user*/
void runInterface()
{
    UGraph Graph;
    int* Group;
    int groupSize;
    char selection;
    Graph = createGraph();
    if(!Graph) return;
    selection = 0;
    while(1)
    {
        char dummy[2];
        if(!addEdge(Graph)) return;
        gets(dummy);
        printf("\nEnter q to stop entering edges, any other key to continue : ");
        scanf("%c",&selection);
        if(selection == 'q') break;
    }
    selection = 0;
    while(selection != 'q')
    {
        int i;
        char dummy[2];
        while(1)
        {
            printf("\nEnter group size : ");
            scanf("%d",&groupSize);
            if(!(groupSize > 0 && groupSize < Graph->numVertices)) printf("\nInvalid group size\n");
            else break;
        }
        Group = (int*)calloc(groupSize,sizeof(int));
        if(!Group) return;
        printf("\nEnter group elements (one by one) : ");
        for(i=0;i<groupSize;i++)
        {
            while(1)
            {
                int temp;
                scanf("%d",&temp);
                if(!(temp >= 0 && temp < Graph->numVertices)) printf("\nInvalid vertex\n");
                else
                {
                    Group[i] = temp;
                    break;
                }
            }
        }
        isMainGroup(Graph->matrix,Graph->numVertices,Group,groupSize);
        free(Group);
        gets(dummy);
        printf("\nEnter 'q' to quit, any other key to check another group : ");
        scanf("%c",&selection);
    }
    free(Graph->matrix);
    free(Graph);
}

/*Tests function of isMainGroup with some demonstration values*/
void DEMO()
{
    int Graph[][7] ={
                    {0,1,0,0,0,0,1},
                    {1,0,1,1,0,1,0},
                    {0,1,0,1,0,0,1},
                    {0,1,1,0,1,0,0},
                    {0,0,0,1,0,1,1},
                    {0,1,0,0,1,0,1},
                    {1,0,1,0,1,1,0}
                    };
    int Group1[] = {0};
    int Group2[] = {2,6};
    int Group3[] = {0,5,4};
    int Group4[] = {0,3,5};
    int Group5[] = {0,5,3};
    int Group6[] = {5,0,3};
    int Group7[] = {0,1,2};
    int Group8[] = {4,5,6};
    int Group9[] = {2,4};
    isMainGroup(Graph[0],7,Group1,1);
    isMainGroup(Graph[0],7,Group2,2);
    isMainGroup(Graph[0],7,Group3,3);
    isMainGroup(Graph[0],7,Group4,3);
    isMainGroup(Graph[0],7,Group5,3);
    isMainGroup(Graph[0],7,Group6,3);
    isMainGroup(Graph[0],7,Group7,3);
    isMainGroup(Graph[0],7,Group8,3);
    isMainGroup(Graph[0],7,Group9,2);
}

void runProgram()
{
    char selection;
    char dummy[2];
    selection = 0;
    while(selection != '3')
    {
        printf("Please enter your choice :\n1)See demo over graph from assignment\t2)Enter your own parameters\t3)Quit\nYour choice: ");
        scanf("%c",&selection);
        switch(selection)
        {
            case '1' : 
            {
                DEMO();
                printf("\n");
                gets(dummy);
                break;
            }
            case '2' :
            {
                runInterface();
                gets(dummy);
                printf("\n");
                break;
            }
            case '3' : break;

            default : printf("\nInvalid selection\n");
        }
    }
    printf("\nGoodbye!");
}

int main(void)
{
    runProgram();
    return 0;
}
