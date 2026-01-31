//program to print sum and product of a number

#include<stdio.h>
#include<stdlib.h>


void print_sum_and_product(int n)
{
  int temp=n;
  int sum=0;
  int product=1;
  while(n!=0)
  {
    sum+=(n%10);
    n/=10;
  }
  while(temp!=0)
  {
    product*=(((temp%10)!=0)?(temp%10):(1));
    temp/=10;
  }
  printf("Sum = %d\n",sum);
  printf("Product = %d",product);
}

int main()
{
    int n;
    printf("Enter your number: ");
    scanf("%d",&n);
    print_sum_and_product(n);
    return 0;
}