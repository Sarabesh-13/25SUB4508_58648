//calculate distance between two points in 2D space
#include <stdio.h>
#include <math.h>

int main() {
    double x1, y1, x2, y2, distance;

    printf("Enter coordinates of the first point (x1 y1): ");
    scanf("%lf %lf", &x1, &y1);

    printf("Enter coordinates of the second point (x2 y2): ");
    scanf("%lf %lf", &x2, &y2);

    // Calculate the distance using the distance formula
    distance = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));

    printf("The distance between the points (%.2lf, %.2lf) and (%.2lf, %.2lf) is: %.2lf\n", x1, y1, x2, y2, distance);

    return 0;
}