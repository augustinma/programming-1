#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING 100

typedef struct item
{
    char name[MAX_STRING];
    int q_sold;
    int pos;
}Item;

void insert(Item** parr_items, char* it_name, int index, int* pnum_items, int* psize, Item*** prank)
{
    Item** rank=*prank;
    Item* arr_items=*parr_items; 
    if (*pnum_items==0)
    {
        strncpy (arr_items[index].name, it_name, MAX_STRING-1);
        arr_items[index].q_sold=0;
        arr_items[index].pos=0;
        rank[arr_items[index].pos]=&arr_items[index];
        *pnum_items=*pnum_items+1;
        return;
    }
    if (*pnum_items>=*psize)
    {
        *psize=*psize*2;
        arr_items=(Item*)realloc(arr_items, (*psize)*sizeof(Item));
        rank=(Item**)realloc(rank, (*psize)*sizeof(Item*));
        for (int i = 0; i < *pnum_items; i++)
        {
            rank[arr_items[i].pos]=&arr_items[i];
        }
        
    }
    for (int i=*pnum_items; i>index; i--)
    {
        strncpy(arr_items[i].name, arr_items[i-1].name, MAX_STRING);
        arr_items[i].q_sold=arr_items[i-1].q_sold;
        arr_items[i].pos=arr_items[i-1].pos;
        rank[arr_items[i].pos]=&arr_items[i];     // ??
    }
    strncpy (arr_items[index].name, it_name, MAX_STRING-1);
    arr_items[index].q_sold=0;
    arr_items[index].pos=*pnum_items;
    rank[arr_items[index].pos]=&arr_items[index];
    *pnum_items=*pnum_items+1;
    *parr_items=arr_items;
    *prank=rank;
}

int search(Item* list, char* x, int num_items, int* pret_index)
{
    if (num_items==0)
    {
        *pret_index=0;
        return 0;
    }
    int size=num_items;
    int lo = 0, hi = size, mid;
    int cmp_res;
    while ( lo < hi )
    {
        mid = (lo + hi) >> 1;
        cmp_res=strncmp(list[mid].name, x, MAX_STRING);
        if (  cmp_res==0 )
        {
            *pret_index=mid; 
            return 1;
        }
        if ( cmp_res<0 )
        lo = mid + 1; /* attention: +1 */
        else
        hi = mid;
    }
    *pret_index=hi;
    return 0;
}

void search_and_add(Item** parr_items, char* it_name, int* pnum_items, int* psize, Item*** prank)
{
    Item** rank=*prank;
    Item* arr_items=*parr_items;
    int index=-1;
    int found=search(arr_items, it_name, *pnum_items, &index);
    Item* tmp;
    if (found)
    {
        arr_items[index].q_sold++;
        int j=arr_items[index].pos;
        while ( j-1>=0 && rank[j]->q_sold>rank[j-1]->q_sold)
        {
            tmp=rank[j-1];
            rank[j-1]->pos++;
            rank[j]->pos--;
            rank[j-1]=rank[j];
            rank[j]=tmp;
            j--;
        }
        
    }
    else
    {
        insert(&arr_items, it_name, index, pnum_items, psize, &rank);
        *prank=rank;
        arr_items[index].q_sold++;
    }
    *parr_items=arr_items;
}

int main(void)
{
    int size=1024;
    int num_items=0;
    Item* arr_items = (Item*)malloc(size*sizeof(Item));
    int top_n;
    Item** rank=(Item**)malloc(size*sizeof(Item*));
    printf("Top N:\n");
    int top_sellers=0;
    if (scanf("%d", &top_n)!=1 || top_n<=0)
    {
        printf("Invalid input.\n");
        free(arr_items);
        free(rank);
        return 1;
    }
    printf("Requests:\n");
    char command;
    char it_name[(MAX_STRING+1)];
    for (int i = 0; i < (MAX_STRING+1); i++)
    {
        it_name[i]='\0';
    }
    
    while (scanf(" %c", &command)==1)
    {
        if (command=='+')
        {
            // add the item if not found and increment quantity sold;
            if ( !(scanf(" %100s",it_name)==1) || it_name[MAX_STRING-1]!='\0')
            {
                printf("Invalid input.\n");
                free(arr_items);
                free(rank);
                return 3;
            }
            search_and_add(&arr_items, it_name, &num_items, &size, &rank);
        }
        else if (command=='#')
        {
            int top=top_n;
            if (top>num_items)
            {
                top=num_items;
            }
            
            // print rank, Top N sold items and quantity sold, summary.
            int j=0;
            int l=0;
            int k=0;
            while (l<top && j<top)
            {
                k=0;
                while( (j+k+1<num_items) && (rank[j]->q_sold==rank[(j+k)+1]->q_sold) )
                {
                    k++;
                }
                for (int i = 0; i <= k; i++)
                {
                    printf("%d.",j+1);
                    if(k!=0)
                    {
                        printf("-%d.",j+k+1);
                        printf(" %s, %dx\n",rank[j+i]->name, rank[j+i]->q_sold);
                        top_sellers+=rank[j+i]->q_sold;
                        if(l!=top-1)
                        {
                            l++;
                        }
                    }
                    else
                    {
                        printf(" %s, %dx\n",rank[j+i]->name, rank[j+i]->q_sold);
                        top_sellers+=rank[j+i]->q_sold;
                        // if(l!=top_n-1)
                        // {
                        //     l++;
                        // }
                    }
                }
                j=j+k+1;
                if(k==0)
                {
                    l++;
                }
            }
            printf("Top sellers: sold %d items\n", top_sellers);
            top_sellers=0;
        }
        else if (command=='?')
        {
            // print summary;
            int top=top_n;
            if (top>num_items)
            {
                top=num_items;
            }
            for (int i = 0; i < top; i++)
            {
                top_sellers+=rank[i]->q_sold;
                if (i==top-1)
                {
                    int k=1;
                    while ((i+k)<num_items && rank[i]->q_sold==rank[i+k]->q_sold)
                    {
                        top_sellers+=rank[i+k]->q_sold;
                        k++;
                    }
                    
                }
                
            }
            printf("Top sellers: sold %d items\n", top_sellers);
            top_sellers=0;
        }
        else
        {
            printf("Invalid input.\n");
            free(arr_items);
            free(rank);
            return 2;
        }
    }
    if (feof(stdin))
    {
        free(arr_items);
        free(rank);
        return 0;
    }
    else
    {
        printf("Invalid input.\n");
        free(arr_items);
        free(rank);
        return 2;
    }
}