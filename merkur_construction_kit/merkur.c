#include <stdio.h>
#include <stdlib.h>

void bubble_sort(long long int*, int);
void swap (long long int*, long long int*b);

int main()
{
    int num_beams=0;
    long long int *beams;
    beams=(long long int*)malloc(10001*sizeof(long long int));
    printf("Beam lengths:\n");
    while ( (scanf ("%lld", &beams[num_beams])==1) && (num_beams<=10000) )
    {
        if ( (beams[num_beams]<=0) || (num_beams==10000) )
        {
            printf("Invalid input.\n");
            free (beams);
            return 0;
        }
        num_beams++;
    }
    if (feof(stdin))
    {
        if (num_beams<3)
        {
            printf("Invalid input.\n");
            free (beams);
            return 0;
        }
    }
    else
    {
        printf("Invalid input.\n");
        free (beams);
        return 0;
    }
    bubble_sort(beams, num_beams);
    int num_tri=0;
    int i_high=num_beams-1;
    while(i_high>=2)
    {
        int k=1;
        int l=2;
        while ((i_high-l>=0) && (i_high-k>=1)  && ((beams[i_high-k]+beams[i_high-l])>beams[i_high]) )
        {
            ++num_tri;
            do
            {
                ++l;
            } while ( (i_high-l>=0) && (beams[i_high-l]==beams[i_high-l+1]) );
            if (i_high-l<0 || (!((beams[i_high-k]+beams[i_high-l])>beams[i_high])) )
            {
                do
                {
                    ++k;
                    l=k+1;
                } while ( (i_high-k>=0) && (beams[i_high-k]==beams[i_high-k+1]));
                
            }
               
        }
        do
        {
            --i_high;
        } while ((i_high>=0) && beams[i_high]==beams[i_high+1]);
        
    }
    printf("Triangles: %d\n", num_tri);
    free (beams);
    return 0;
}

void bubble_sort (long long int *arr, int max)
{
    for (int i=0; i<max-1; i++)
    {
        for (int j=0; j<max-i-1; j++)
        {
            if(arr[j]>arr[j+1])
            {
                swap(&arr[j], &arr[j+1]);
            }
        }
    }
}

void swap(long long int* a, long long int* b)
{
    long long int tmp = *a;
    *a = *b;
    *b = tmp;
}

//  2 9 18 4 1 5 19 6 3 1 2 8