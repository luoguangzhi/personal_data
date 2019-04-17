#include<stdio.h>
#define N 10
int a[10]={5,6,7,4,12,6,9,10,2,3};

void insertsort3(int a[],int n)
{
    int i,j,temp;
    for(i=1;i<n;i++)
    {
        for(j=i-1;j>=0&&a[j]>a[j+1];j--)
        {
            temp=a[j+1];
            a[j+1]=a[j];
            a[j]=temp;
        }
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
    insertsort3(a,N);
    print(a,N);

}
