#include<stdio.h>
#define N 10
int a[10]={5,6,7,4,12,6,9,10,2,3};

void bubbleSort3(int a[],int n)
{
    int i,j,temp,flag;
    flag=n;
    while(flag > 0)
    {
        j=flag;
        flag=0;
        for(i=1;i<j;i++)
        {
            if(a[i] < a[i-1])
            {
                temp=a[i];
                a[i]=a[i-1];
                a[i-1]=temp;

                flag=i;
            }
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
    bubbleSort3(a,N);
    print(a,N);

}
