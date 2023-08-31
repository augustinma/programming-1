#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int next_sq_free(int);
int is_sq_free (int);
int is_prime(int);
int is_non_rep_div(int);

int large_find_k(int, int*, int);
int large_next_sq_free(int, int*, int);
int large_is_sq_free(int, int*, int);
int large_is_prime(int, int*, int);
int large_is_non_rep_div(int, int*, int);
int binary_search (int, int*, int, int);

int main()
{
    printf("Index:\n");
    int input;
    int prev_input=1;
    int *arr=NULL;
    int result =0;
    int *num=NULL;
    num=(int*)malloc(31622*sizeof(int));
    for (int i=0; i<31622; ++i)
    {
        num[i]=1;
    }
    for(int i=2; i<=(int)sqrt(31622);)
    {
        for (int j=i*i; j<31622; ++j)
        {
            if ((j%i)==0)
            num[j]=0;
        }
        do
        {
            i=i+1;
        } while (num[i]!=1 && i<=(int)sqrt(31622));
    }
    int *prime;
    prime= (int*)malloc(10000*sizeof(int));
    for (int i=0; i<10000; ++i)
    {
        prime[i]=0;
    }
    int k=0;
    for (int j=2; j<31622; ++j)
    {
        if(num[j]==1)
        {
            prime[k]=j;
            ++k;
        }
    }
    int h=0;
    for (int i=0; i<10000; i++)
    {
        if (prime[i]==0)
        {
            h=(i-1); break;
        }
    }
    free(num);
    while ( (scanf("%d", &input)==1) && (input>0) )
    {
        int cond=0;
        if (input>1000000){cond=1;}
        switch (cond)
        {
        case 1:
            {
                result = large_find_k(input, prime, h);
                printf("= %d\n", result);
            }
            break;
        
        default:
            {
                if (prev_input==1)
                {
                    arr=(int *)realloc(arr, sizeof(int));
                    arr[0]=1;
                }
                if (input>prev_input)
                {
                    arr=(int *)realloc(arr, input*sizeof(int));
                    for (int i=prev_input; i<input; ++i)
                    {
                        arr[i]=next_sq_free(arr[i-1]+1);
                    }
                    printf("= %d\n", arr[input-1]); 
                }
                else
                {
                    printf("= %d\n", arr[input-1]);
                }
                if (input>prev_input)
                {
                    prev_input=input;
                }

            }
            break;
        }
    }
    if ( feof (stdin) )
    {
        free(prime); return 0;
    }
    else
    {
        printf ("Invalid input.\n"); free(prime); return 0;
    }
    return 0;
}

int next_sq_free (int num)
{
    while (!(is_sq_free(num)))
    {
        num=num+1;
    }
    return num;
}

int is_sq_free(int num)
{
    if (is_prime(num) || is_non_rep_div(num))
    {
        return 1;
    }
    return 0; 
}

int is_prime(int num)
{
    if (num==2 || num==3)
    {
        return 1;
    }
    else if ((num%2==0) || (num%3==0))
    {
        return 0;
    }
    for (int i=5; i<=(int)sqrt(num); i=i+2)
    {
        if (num%i==0)
        {
            return 0;
        }
    }
    return 1;
}

int is_non_rep_div(int num)
{
    for (int i=2; i<=(int)sqrt(num); i++)
    {
        if ( (num%i==0) )
        {
            if ((num/i)%i==0)
            {
                return 0;
            }
            
        }
    }
    return 1;
}

int large_find_k (int input, int*prime, int h)
{


    int m=1;
    int count=1;
    for(int i=0; i<input-1; ++i)
    {
        m = large_next_sq_free(m+1, prime, h);
        count=count+1;
    }
    return m;
    
}

int large_next_sq_free(int num, int*prime, int h)
{
    while (!(large_is_sq_free(num, prime, h)))
    {
        num=num+1;
    }
    return num;
}

int large_is_sq_free(int num, int*prime, int h)
{
    if (large_is_prime(num, prime, h) || large_is_non_rep_div(num, prime, h))
    {
        return 1;
    }
    return 0; 
}

int large_is_prime (int num, int*prime, int h)
{
    return binary_search(num, prime, 0, h);
}

int large_is_non_rep_div (int i, int *prime, int h)
{
    for (int j=0; prime[j]<=(int)sqrt(i); j++)
    {
        if ( (i%prime[j]==0) )
        {
            if ((i/prime[j])%prime[j]==0)
            {
                return 0;
            }
            
        }
    }
    return 1;
}

int binary_search(int key, int *arr, int l, int h)
{
    while (h>=l)
    {
        int mid = (l+h)/2;
        if (arr[mid]==key) return 1;
        if (key < arr[mid]) h= mid-1; else l= mid+1;
    }
    return 0;
}