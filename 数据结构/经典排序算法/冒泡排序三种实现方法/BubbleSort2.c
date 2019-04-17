#include<stdio.h>
#define N 10
int a[10]={5,6,7,4,12,6,9,10,2,3};

void bubbleSort1(int a[],int n)
{
    int i,j,temp,flag;
    for(i=0;i<n;i++)
    {
        flag=0;
        for(j=1;j<n-i;j++)
        {
           if(a[j]<a[j-1])
           {
               flag=1;
               temp=a[j];
               a[j]=a[j-1];
               a[j-1]=temp;
           }
        }
        if(flag==0)
            break;
    }
}

void print(int a[],int n)
{
    int i;
    for(i=0;i<n;i++)
        printf("%d\t",a[i]);
    printf("\n\n");
}

int main()
{
    print(a,N);
    bubbleSort1(a,N);
    print(a,N);

}
