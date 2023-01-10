#include <stdio.h>
#define N 5

/*Function Resize
*----------------
* Takes an N by N int array 'in' and a 2N by 2N int array out (assuming N is defined as a positive number),
* and assigns the values of 'in' to 'out', such that every four directly adjacent places in 'out',
* starting from the top left corner - will contain the appropriate value of 'in'; e.g if in[0][0] is 1,
* then out[0][0], out[0][1], out[1][0] and out[1][1] will also become 1 (similar to naive bitmap resizing).
* if N is defined as non-positive, function will print error message.
*
* in : N by N input int array  
* out : 2N by 2N output int array
**/
void Resize(int in[N][N],int out[2*N][2*N])
{
    if(N > 0)
    {
        for(int i=0;i<N;i++)
        {
            for(int j = 0;j<N;j++)
            {
                int ii =2*i, jj = 2*j;
                out[ii][jj] = in[i][j];
                out[ii+1][jj+1] = in[i][j];
                out[ii][jj+1] = in[i][j];
                out[ii+1][jj] = in[i][j];
            }
        }
    }
    else printf("\nError - global int 'N' must be defined as positive\n");
}

/*Function print_diagonals
*-------------------------
* Prints the anti-diagonals (bottom left to top right) of a given N by N int array A (assuming N is defined as positive), 
* starting from the top left corner, such that each diagonal is printed in a new line e.g first A[0][0], then the next line
* will have A[1][0] and A[0][1], the third will have A[2][0] A[1][1] and A[0][2] etc. , and the last line will be A[N-1][N-1].
*
* A : N by N int array of which the anti-diagonals will be printed*/
void print_diagonals(int A[N][N])
{
    if(N > 0)
    {
        for(int i =0;i<N;i++)
        {
            int j = i, k = 0;
            while(j>= 0)
            {
                printf("%6d",A[j][k]);
                j--;
                k++;
            }
            printf("\n");
        }
        for(int i = 1;i<N;i++)
        {
            int j = N-1, k = i;
            while(j>=i)
            {
                printf("%6d",A[j][k]);
                j--;
                k++;
            }
            printf("\n");
        }
    }
    else printf("\nError - 'N' must be defined as positive\n");
}

/*Function main
*--------------
* demonstrates Resize and print_diagonals with demonstration arrays*/
int main(void)
{
    int A[N][N] = {{45,13,19,69,86},{89,22,42,25,75},{4,55,57,42,36},{95,35,94,10,99},{51,37,34,5,61}};
    int in[N][N] = {{3,2,12,8,7},{9,34,6,1,3},{7,90,30,50,78},{1,2,3,4,65},{4,5,6,2,7}}; 
    int out[2*N][2*N];
    Resize(in,out);
    for(int i = 0;i<2*N;i++)
    {
        for(int j = 0;j<2*N;j++)
        {
            printf("%6d",out[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    print_diagonals(A);
    return 0;
}