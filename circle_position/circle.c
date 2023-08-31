#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>


int main()
{
    double x1, y1, r1, x2, y2, r2;
    printf("Enter circle #1 parameters:\n");
    if (scanf (" %lf %lf %lf",&x1, &y1, &r1) !=3 || (r1<=0))
    {
        printf("Invalid input.\n");
        return 1;
    }
    printf("Enter circle #2 parameters:\n");
    if (scanf (" %lf %lf %lf",&x2, &y2, &r2) !=3 || (r2<=0))
    {
        printf("Invalid input.\n");
        return 1;
    }
    double d = sqrt(((x2-x1)*(x2-x1))+((y2-y1)*(y2-y1)));
    if ( (fabs(x1-x2)<=((r1*1000)*DBL_EPSILON)) && (fabs(y1-y2)<=((r1*1000)*DBL_EPSILON)) )
    {
        if( fabs(r1-r2)<=((r1*1000)*DBL_EPSILON) )
        {
            double area = (M_PI)*(r1)*(r1);
            printf("The circles are identical, overlap: %f\n", area);
        }
        else
        {
            if ((r1-r2)<(r1*1000)*DBL_EPSILON)
            {
                double area = (M_PI)*(r1)*(r1);
                printf("Circle #1 lies inside circle #2, overlap: %f\n", area);
            }
            else
            {
                double area = (M_PI)*(r2)*(r2);
                printf("Circle #2 lies inside circle #1, overlap: %f\n", area);
            }
            
        }
    }
    else if (fabs(d-(r1+r2))<=(d*1000*DBL_EPSILON))
    {
        printf("External touch, no overlap.\n");
    }
    else if (d>(r1+r2))
    {
        printf("The circles lie outside each other, no overlap.\n");
    }
    else if((fabs((d+r1)-r2))<=(d*1000)*DBL_EPSILON)
    {
        double area = (M_PI)*(r1)*(r1);
        printf("Internal touch, circle #1 lies inside circle #2, overlap: %f\n", area);
    }
    else if (fabs((d+r2)-r1)<=(d*1000)*DBL_EPSILON)
    {
        double area = (M_PI)*(r2)*(r2);
        printf("Internal touch, circle #2 lies inside circle #1, overlap: %f\n", area);
    }
    else if ((d+r1)<r2)
    {
        double area = (M_PI)*(r1)*(r1);
        printf("Circle #1 lies inside circle #2, overlap: %f\n", area); return 0;
    }
    else if ((d+r2)<r1)
    {
        double area = (M_PI)*(r2)*(r2);
        printf("Circle #2 lies inside circle #1, overlap: %f\n", area); return 0;
    }
    else
    {
        double r1_squared = (r1)*(r1);
        double r2_squared = (r2)*(r2);
        double d_squared = (d)*(d);
        double d1 = (r1_squared-r2_squared+d_squared)/(2*d);
        double d2 = (r2_squared-r1_squared+d_squared)/(2*d);
        double area = (r1_squared*(acos(d1/r1)))-(d1*(sqrt(r1_squared-(d1*d1))))+(r2_squared*(acos(d2/r2)))-(d2*(sqrt(r2_squared-(d2*d2))));
        printf("The circles intersect, overlap: %f\n", area);
    }


    return 0;
}