#include<stdio.h>
#define N 10
int a[10]={5,6,7,4,12,6,9,10,2,3};

void insertsort2(int a[],int n)
{
    int i,j;
    for(i=1;i<n;i++)
    {
       if(a[i]<a[i-1])
       {
           int temp=a[i];  //a[i]会被改变，需要暂时保存
           for(j=i-1;j>=0 && temp<a[j];j--)
                a[j+1]=a[j];
           a[j+1]=temp;
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
    insertsort2(a,N);
    print(a,N);

}
