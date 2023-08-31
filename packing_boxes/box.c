#include <stdio.h>
#include <stdlib.h>
#define THICK (0.4)
void bubble_sort(int [], int);
int main()
{
    double a_a, a_b, a_c, b_a, b_b, b_c;
    printf("Enter box A dimensions:\n");
    if (scanf(" %lf %lf %lf", &a_c, &a_a, &a_b)!=3 || (a_a<=0) || (a_b<=0) || (a_c<=0))
    {
        printf("Invalid input.\n");
        return 1;
    }
    printf("Enter box B dimensions:\n");
    if (scanf(" %lf %lf %lf", &b_c, &b_a, &b_b)!=3 || (b_a<=0) || (b_b<=0) || (b_c<=0))
    {
        printf("Invalid input.\n");
        return 1;
    }

    double max_a, mid_a, min_a;
    max_a= (a_a>a_b ) ? (a_a>a_c ? a_a : a_c) : (a_b>a_c ? a_b : a_c);
    min_a= (a_c<a_a) ? (a_c<a_b ? a_c : a_b) : (a_a<a_b? a_a : a_b);
    mid_a= (a_a>a_b) ? (a_a<a_c ? a_a : (a_b>a_c ? a_b : a_c)) : (a_b<a_c ? a_b :(a_a>a_c ? a_a : a_c));

    double max_b, mid_b, min_b;
    max_b= (b_a>b_b ) ? (b_a>b_c ? b_a : b_c) : (b_b>b_c ? b_b : b_c);
    min_b= (b_c<b_a) ? (b_c<b_b ? b_c : b_b) : (b_a<b_b? b_a : b_b);
    mid_b= (b_a>b_b) ? (b_a<b_c ? b_a : (b_b>b_c ? b_b : b_c)) : (b_b<b_c ? b_b :(b_a>b_c ? b_a : b_c));

    if ( ((max_a-(THICK*2))>=max_b) && ((mid_a-(THICK*2))>=mid_b) && ((min_a-(THICK*2))>=min_b) )
    {
        int comp1 = ((int)((a_a-(THICK*2))/b_a)) * ((int)((a_b-(THICK*2))/b_b)) * ((int)((a_c-(THICK*2))/b_c));
        int comp2 = ((int)((a_a-(THICK*2))/b_a)) * ((int)((a_b-(THICK*2))/b_c)) * ((int)((a_c-(THICK*2))/b_b));
        int comp3 = ((int)((a_a-(THICK*2))/b_b)) * ((int)((a_b-(THICK*2))/b_a)) * ((int)((a_c-(THICK*2))/b_c));
        int comp4 = ((int)((a_a-(THICK*2))/b_b)) * ((int)((a_b-(THICK*2))/b_c)) * ((int)((a_c-(THICK*2))/b_a));
        int comp5 = ((int)((a_a-(THICK*2))/b_c)) * ((int)((a_b-(THICK*2))/b_b)) * ((int)((a_c-(THICK*2))/b_a));
        int comp6 = ((int)((a_a-(THICK*2))/b_c)) * ((int)((a_b-(THICK*2))/b_a)) * ((int)((a_c-(THICK*2))/b_b));
        int arr[6]={comp1,comp2,comp3,comp4,comp5,comp6};
        bubble_sort(arr, 6);
        int x = arr[5];
        printf("%d box(es) B could be packed into A.\n", x);
    }
    else if ( ((max_b-(THICK*2))>=max_a) && ((mid_b-(THICK*2))>=mid_a) && ((min_b-(THICK*2))>=min_a) )
    {
        int comp1 = ((int)((b_a-(THICK*2))/a_a)) * ((int)((b_b-(THICK*2))/a_b)) * ((int)((b_c-(THICK*2))/a_c));
        int comp2 = ((int)((b_a-(THICK*2))/a_a)) * ((int)((b_b-(THICK*2))/a_c)) * ((int)((b_c-(THICK*2))/a_b));
        int comp3 = ((int)((b_a-(THICK*2))/a_b)) * ((int)((b_b-(THICK*2))/a_a)) * ((int)((b_c-(THICK*2))/a_c));
        int comp4 = ((int)((b_a-(THICK*2))/a_b)) * ((int)((b_b-(THICK*2))/a_c)) * ((int)((b_c-(THICK*2))/a_a));
        int comp5 = ((int)((b_a-(THICK*2))/a_c)) * ((int)((b_b-(THICK*2))/a_b)) * ((int)((b_c-(THICK*2))/a_a));
        int comp6 = ((int)((b_a-(THICK*2))/a_c)) * ((int)((b_b-(THICK*2))/a_a)) * ((int)((b_c-(THICK*2))/a_b));
        int arr[6]={comp1,comp2,comp3,comp4,comp5,comp6};
        bubble_sort(arr, 6);
        int x = arr[5];
        printf("%d box(es) A could be packed into B.\n", x);
    }
    else
    {
        printf("Neither A nor B could be packed into the other.\n");
    }
    return 0;
}

void bubble_sort (int arr[], int n)
{
    int i, j, tmp;
    for (j=0; j<n-1; j++)
    {
        for (i=0; i<n-j-1; i++)
        {
            if (arr[i]>arr[i+1])
            {        
                tmp = arr[i];
                arr[i] = arr[i+1];
                arr[i+1] = tmp;
            }
        
        }
    }
}
    // length is greatest, width is mid, height is smallest
    // a_a = (a_a>a_b ) ? (a_a>a_c ? a_a : a_c) : (a_b>a_c ? a_b : a_c);
    // a_c = (a_c<a_a) ? (a_c<a_b ? a_c : a_b) : (a_a<a_b? a_a : a_b);
    // a_b = (a_a>a_b) ? (a_a<a_c ? a_a : (a_b>a_c ? a_b : a_c)) : (a_b<a_c ? a_b :(a_a>a_c ? a_a : a_c));

    // b_a = (b_a>b_b ) ? (b_a>b_c ? b_a : b_c) : (b_b>b_c ? b_b : b_c);
    // b_c = (b_c<b_a) ? (b_c<b_b ? b_c : b_b) : (b_a<b_b? b_a : b_b);
    // b_b = (b_a>b_b) ? (b_a<b_c ? b_a : (b_b>b_c ? b_b : b_c)) : (b_b<b_c ? b_b :(b_a>b_c ? b_a : b_c));

        // int length_fit= ((max_a-(THICK*2))/max_b);
        // int width_fit = ((mid_a-(THICK*2))/mid_b);
        // int height_fit= ((min_a-(THICK*2))/min_b);
        // int amount_of_box = length_fit * width_fit * height_fit;