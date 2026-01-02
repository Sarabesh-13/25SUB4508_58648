#include<stdio.h>
#include<stdlib.h>

enum WeekDays
{
    SUNDAY=0,
    MONDAY,
    TUESDAY,
    WEDNESDAY,
    THURSDAY,
    FRIDAY,
    SATURDAY
};


int main()
{
    enum WeekDays day;
    printf("enter a day between (0-6): \n");
    int n;
    scanf("%d",&n);
    day=n;
    switch(day)
    {
        case 0:
        {
            printf("Sunday");
            break;
        }
        case 1:
        {
            printf("Monday");
            break;
        }
        case 2:
        {
            printf("Tuesday");
            break;
        }
        case 3:
        {
            printf("Wednesday");
            break;
        }
        case 4:
        {
            printf("Thursday");
            break;
        }
        case 5:
        {
            printf("Friday");
            break;
        }
        case 6:
        {
            printf("Saturday");
            break;
        }
        default:
        {
            break;
        }
    }
    return 0;
}