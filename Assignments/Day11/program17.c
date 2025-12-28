//program to check products of digits at odd and even position are equal
#include <stdio.h>

#define MAX 20

int main()
{
    int n;
    printf("Enter the number: ");
    scanf("%d",&n);
    int arr[MAX];
    int t=0;
    while(n!=0)
    {
        arr[t++]=n%10;
        n/=10;
    }
    int even_pos_prod=1;
    int odd_pos_prod=1;
    for(int i=0;i<t;i++)
    {
        if(i%2==0)
        {
            odd_pos_prod*=arr[i];
        }
        else
        {
            even_pos_prod*=arr[i];
        }
    }
    printf("%s",((odd_pos_prod==even_pos_prod)?("Yes"):("No")));
    return 0;
}