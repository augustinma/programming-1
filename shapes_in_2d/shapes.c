#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef struct perimeter_and_area
{
    char sh;
    double perimeter;
    double area;
}Perimeter_and_AREA;

int input(Perimeter_and_AREA*);
int triangle(Perimeter_and_AREA*);
double triangle_area(double, double, double);
int rectangle(Perimeter_and_AREA*);
int square (Perimeter_and_AREA*);
void compare(Perimeter_and_AREA*, Perimeter_and_AREA*);

int main (void)
{
    printf("Shape #1\n");
    Perimeter_and_AREA * shape1=(Perimeter_and_AREA*)malloc(sizeof(Perimeter_and_AREA));
    if (input(shape1))
    {
        free (shape1);
        return 1;
    }
    printf("Shape #2\n");
    Perimeter_and_AREA * shape2=(Perimeter_and_AREA*)malloc(sizeof(Perimeter_and_AREA));
    if (input(shape2))
    {
        free (shape1);
        free (shape2);
        return 1;
    }
    compare(shape1, shape2);
    free(shape1);
    free(shape2);
    return 0;
}

int input (Perimeter_and_AREA* shape)
{
    if (scanf(" %[R-T]c", &shape->sh)!=1)
    {
        printf("Invalid input.\n");
        return 1;
    }
    if (shape->sh=='T')
    {
        return triangle(shape);
    }
    else if (shape->sh=='R')
    {
        return rectangle(shape);
    }
    else if (shape->sh=='S')
    {
        return square(shape);
    }
    else 
    {
        return 1;
    }
}
int triangle (Perimeter_and_AREA* perimeter_area_triangle)
{
    double side_a;
    double side_b;
    double side_c;
    // check if three decimals are in the input
    if (scanf(" %lf %lf %lf", &side_a, &side_b, &side_c) !=3)
    {
        printf("Invalid input.\n");
        return 1;
    }
    // check if each side is greater than 0
    if (side_a <=0 || side_b <=0 || side_c<=0)
    {
        printf("Invalid input.\n");
        return 1;
    }
    // check if triangle inequality is fulfilled
    if (!(side_a+side_b>side_c+(__DBL_EPSILON__*100*side_c) && side_a+side_c>side_b+(__DBL_EPSILON__*100*side_b) && side_b+side_c>side_a+(__DBL_EPSILON__*100*side_a)))
    {
        printf("Invalid input.\n");
        return 1;
    }
    perimeter_area_triangle->perimeter =side_a+side_b+side_c;
    perimeter_area_triangle->area = triangle_area(side_a, side_b, side_c); 
    return 0;
}

double triangle_area(double side_a, double side_b, double side_c)
{
    double s = ((side_a+side_b+side_c)/2.0);
    //Area = sqr(s(s-a)(s-b)(s-c)
    double area = sqrt(s*(s-side_a)*(s-side_b)*(s-side_c));
    return area;
}

int rectangle(Perimeter_and_AREA* perimeter_area_rectangle)
{
    double side_a;
    double side_b;
    if (scanf(" %lf %lf", &side_a, &side_b)!=2)
    {
        printf("Invalid input.\n");
        return 1;
    }
    if (side_a<=0 || side_b <=0)
    {
        printf("Invalid input.\n");
        return 1;
    }
    if (fabs(side_a-side_b)<__DBL_EPSILON__*100*(side_a))
    {
        printf("Invalid input.\n");
        return 1;
    }
    perimeter_area_rectangle->perimeter = (side_a*2)+(side_b*2);
    perimeter_area_rectangle->area=side_a*side_b;
    return 0;
}

int square(Perimeter_and_AREA*perimeter_area_square)
{
    double side_a;
    if (scanf(" %lf", &side_a)!=1)
    {
        printf("Invalid input.\n");
        return 1;
    }
    if (side_a<=0)
    {
        printf("Invalid input.\n");
        return 1;
    }
    perimeter_area_square->area =side_a*side_a;
    perimeter_area_square->perimeter=side_a*4;
    return 0;
}

void compare(Perimeter_and_AREA*shape1, Perimeter_and_AREA*shape2)
{
    printf("Perimeter: ");
    if (shape1->sh=='T')
    {
        printf("triangle #1 ");
    }
    if (shape1->sh=='R')
    {
        printf("rectangle #1 ");
    }
    if (shape1->sh=='S')
    {
        printf("square #1 ");
    }
    if (shape1->perimeter<((shape2->perimeter)-(shape2->perimeter*100*__DBL_EPSILON__)))
    {
        printf("< ");
    }
    else if(shape1->perimeter>((shape2->perimeter)+(shape2->perimeter*100*__DBL_EPSILON__)))
    {
        printf("> ");
    }
    else
    {
        printf("= ");
    }
    if (shape2->sh=='T')
    {
        printf("triangle #2\n");
    }
    if (shape2->sh=='R')
    {
        printf("rectangle #2\n");
    }
    if (shape2->sh=='S')
    {
        printf("square #2\n");
    }

    // area comp
    printf("Area: ");
    if (shape1->sh=='T')
    {
        printf("triangle #1 ");
    }
    if (shape1->sh=='R')
    {
        printf("rectangle #1 ");
    }
    if (shape1->sh=='S')
    {
        printf("square #1 ");
    }
    if (shape1->area<((shape2->area)-(shape2->area*100*__DBL_EPSILON__)))
    {
        printf("< ");
    }
    else if(shape1->area>((shape2->area)+(shape2->area*100*__DBL_EPSILON__)))
    {
        printf("> ");
    }
    else
    {
        printf("= ");
    }
    if (shape2->sh=='T')
    {
        printf("triangle #2\n");
    }
    if (shape2->sh=='R')
    {
        printf("rectangle #2\n");
    }
    if (shape2->sh=='S')
    {
        printf("square #2\n");
    }
}