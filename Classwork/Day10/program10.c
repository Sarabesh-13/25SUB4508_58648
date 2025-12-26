//program to have enums for weekdays and convert them to integers and print them

#include <stdio.h>

enum Weekday {
    SUNDAY,
    MONDAY,
    TUESDAY,
    WEDNESDAY,
    THURSDAY,
    FRIDAY,
    SATURDAY
};

int main()
{
    for(int i = SUNDAY; i <= SATURDAY; i++) {
        printf("Day %d\n", i);
    }
}