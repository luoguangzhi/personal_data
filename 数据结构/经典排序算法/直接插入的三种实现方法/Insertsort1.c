#include<stdio.h>
#define N 10
int a[10]={5,6,7,4,12,6,9,10,2,3};

void insertsort1(int a[],int n)
{
    int i,j,k;
    for(i=1;i<n;i++)
    {
        for(j=i-1;j>=0;j--)
        {
            if(a[j]<a[i])
                break;
        }

        if(j!=i-1)
        {
            int temp = a[i];
            for(k=i-1;k>j;k--)
                a[k+1]=a[k];
            a[k+1]=temp;
        }
    }
}

void print(int a[],int n)
{
    int i;
    for(i=0;i<n;i++)
        printf("%d\t",a[i]);
    printf("\n");
}

int main()
{
    print(a,N);
    insertsort1(a,N);
    print(a,N);

}
