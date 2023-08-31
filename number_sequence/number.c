#include <stdio.h>
#include <math.h>
#include <stdlib.h>


void num_at_pos(long long int, int);
long long int base_exponent(int, int);
void print_num_and_arrow(long long int, int, int);
void print_letter(int);

int main(void)
{
    long long int pos;
    int base;
    printf("Position and radix:\n");
    while(scanf(" %lld",&pos)==1 && !(feof(stdin)) && scanf(" %d", &base) )   //(scanf(" %lld %d", &pos, &base)==2)
    {
        if (pos<0 || base <2 || base >36)
        {
            printf("Invalid input.\n");
        }
        else
        {
            num_at_pos(pos, base);
        }
    }
    if (feof(stdin))
    {
        return 0;
    }
    else
    {
        printf("Invalid input.\n");
    }
    
}

void num_at_pos(long long int pos, int base)
{
    long long int number=-1;
    int arrow_pos=-1;
    int total_digits=1;
    int base_power=0;
    long long int prev_pos=-1;
    if (pos<base)
    {
        number=pos;
        arrow_pos=0;
    }
    else
    {
        while (pos>0)
        {
            prev_pos=pos;
            pos=pos-((base-1)*(base_exponent(base, base_power))*total_digits);
            if (pos>0)
            {
                ++total_digits;
                ++base_power;
            }
        }
        number=ceil((double)prev_pos/total_digits);
        --base_power;
        for (int i=base_power; i>=0; --i)
        {
            number=number+((base-1)*base_exponent(base, base_power));
            --base_power;
        }
        arrow_pos=pos%total_digits+total_digits-1;

    }
    print_num_and_arrow(number, arrow_pos, base);
    //printf("%d\n", number);
    //printf("%d\n", arrow_pos);
}

long long int base_exponent(int base, int exponent)
{
    long long int result=1;
    for (int i=exponent; i>0; --i)
    {
        result= result*base;
    }
    return result;
}

void print_num_and_arrow(long long int number, int arrow_pos, int base)
{
    int size=8;
    int curr=-1;
    int* arr_digits = (int*)malloc(size*sizeof(int));
    if (number==0)
    {
        printf("0\n");
        printf("^\n");
        free(arr_digits);
        arr_digits=NULL;
        return;
    }
    while (number > 0)
    {
        ++curr;
        if (curr>=size)
        {
            size=size*2;
            arr_digits=(int*)realloc(arr_digits, size*sizeof(int));
        }
        arr_digits[curr]=(number%base);
        number=number/base;
    }
    for(int i=curr; i>=0; i--)
    {
        if (arr_digits[i]>=10)
        {
            print_letter(arr_digits[i]);
        }
        else
        {
            printf("%d", arr_digits[i]);
        }
        
    }
    printf("\n");
    for (int i=0; i<arrow_pos; ++i)
    {
        printf(" ");
    }
    printf("^\n");
    free(arr_digits);
    arr_digits=NULL;
}

void print_letter(int num)
{
    int ascii=97;
    for (int i=10; i<=36; i++, ascii++)
    {
        if(num==i)
        {
            printf("%c", ascii);
            break;
        }
    }
}