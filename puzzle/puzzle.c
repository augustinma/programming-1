#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void analysis(char**, ssize_t, int);
int remove_new_line(char**, ssize_t, int);
int create_arr_all_strings(char***, int*, char**, int, int);
void create_left_to_right_strings(char**, int, int, char***, int*, int*);
void create_l_to_r_for_row(char*, int, char***, int*, int*);
void create_i_tuple_l_to_r(char*, int, int, char***, int*, int*);
void reverse(char*, int);
// void create_right_to_left_strings(char**, int, int, char***, int*, int*);
// void create_r_to_l_for_row(char*, int, char***, int*, int*);
// void create_i_tuple_r_to_l(char*, int, int, char***, int*, int*);
void create_top_to_bottom_strings(char**, int, int, char***, int*, int*);
void create_t_to_b_for_col(char**, int, int, char***, int*, int*);
void create_i_tuple_t_to_b(char**, int, int, int, char***, int*, int*);
// void create_bottom_to_top_strings(char**, int, int, char***, int*, int*);
// void create_b_to_t_for_col(char**, int, int, char***, int*, int*);
// void create_i_tuple_b_to_t(char**, int, int, int, char***, int*, int*);
// void create_diag_tr_to_bl_strings(char**, int, int, char***, int*, int*);
// void create_diag_tr_to_bl_col(char**, int, int, char***, int*, int*);
// void create_diag_i_tuple_tr_bl(char**, int, int, int, char***, int*, int*);
// void create_diag_tr_to_bl_row(char**, int, int, char***, int*, int*);
// void create_diag_i_tuple_tr_bl_row(char**, int, int, int, char***, int*, int*);
// void create_diag_tl_to_br_strings(char**, int, int, char***, int*, int*);
// void create_diag_tl_to_br_col(char**, int, int, char***, int*, int*);
// void create_diag_i_tuple_tl_br(char**, int, int, int, char***, int*, int*);
// void create_diag_tl_to_br_row(char**, int, int, char***, int*, int*);
// void create_diag_i_tuple_tl_br_row(char**, int, int, int, char***, int*, int*);
void create_diagonal_1_strings(char**, int, int, char***, int*, int*);
// void parse_diagonal1(char**, int, int, char***, int*, int*);
void print_longest_rep_word(char**, int);

int cmpstringp(const void *p1, const void *p2)
{
    /* The actual arguments to this function are "pointers to
        pointers to char", but strcmp(3) arguments are "pointers
        to char", hence the following cast plus dereference */
    
    const char **str_p1 = (const char **)p1;
    const char **str_p2 = (const char **)p2;
    if (strlen(*str_p1)<strlen(*str_p2))
    {
        return -1;
    }
    else if (strlen(*str_p1)>strlen(*str_p2))
    {
        return 1;
    }
    else
    {
        return strcmp(*str_p1, *str_p2);
    }
}

int main(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
    int num_line=0;
    printf("Puzzle:\n");
    if ((nread = getline(&line, &len, stdin)) == -1)
    {
        printf("Invalid input.\n");
        free(line);
        line = NULL;
        return 1;
    }
    int size_arr_puzzle=nread-1;
    if (size_arr_puzzle==0)
    {
        printf("Invalid input.\n");
        free(line);
        line = NULL;
        return 2;
    }
    char** arr_puzzle=(char**)malloc(size_arr_puzzle*sizeof(*arr_puzzle));
    arr_puzzle[num_line]=line;
    num_line++;
    line=NULL;
    len=0;
    ssize_t cread;
    for (int i = 1; i < size_arr_puzzle; i++)
    {
        if ((cread = getline(&line, &len, stdin)) == nread)
        {
            arr_puzzle[num_line]=line;
            num_line++;
            line=NULL;
            len=0;
        }
        else
        {
            printf("Invalid input.\n");
            free(line);
            line = NULL;
            for (int j = 0; j < num_line; j++)
            {
                free(arr_puzzle[j]);
                arr_puzzle[j]=NULL;
            }
            free(arr_puzzle);
            arr_puzzle=NULL;
            return 3;
        }
    }

    if (getc(stdin)!=EOF)
    {
        printf("Invalid input.\n");
        for (int j = 0; j < num_line; j++)
        {
            free(arr_puzzle[j]);
            arr_puzzle[j]=NULL;
        }
        free(arr_puzzle);
        arr_puzzle=NULL;
        return 4;
    }

    if (num_line==1)
    {
        printf("All words are unique.\n");
        free(arr_puzzle[0]);
        arr_puzzle[0]=NULL;
        free(arr_puzzle);
        arr_puzzle=NULL;
        return 0;
    }

    analysis(arr_puzzle, nread, num_line);
    for (int j = 0; j < num_line; j++)
    {
        free(arr_puzzle[j]);
        arr_puzzle[j]=NULL;
    }
    free(arr_puzzle);
    arr_puzzle=NULL;
    return 0;

}

void analysis(char **arr_puzzle, ssize_t nread, int num_line)
{
    int string_len = remove_new_line(arr_puzzle, nread, num_line);
    int size_all_strings=(((10*string_len*string_len*string_len)-(9*string_len*string_len)+(2*string_len))/3)+1;   // (string_len*string_len)+(((8*(string_len-1))+(4*string_len)));
    char** arr_all_strings=(char**)malloc(size_all_strings*sizeof(*arr_all_strings));
    int rows_all_strings=create_arr_all_strings(&arr_all_strings, &size_all_strings, arr_puzzle, num_line, string_len);
    qsort(arr_all_strings, rows_all_strings, sizeof(*arr_all_strings), cmpstringp);
    print_longest_rep_word(arr_all_strings, rows_all_strings);
    for (int i=0; i< rows_all_strings; i++)
    {
        free(arr_all_strings[i]);
        arr_all_strings[i]=NULL;
    }
    free(arr_all_strings);
    arr_all_strings=NULL;
    // fflush(stdin);
}

void print_longest_rep_word(char** arr_all_strings, int rows_all_strings)
{
    unsigned int len_of_longest_rep_word=0;
    char*cmp_string;
    for (int i=rows_all_strings-1; i>0; i--)
    {
        if (strcmp(arr_all_strings[i-1], arr_all_strings[i])==0)
        {
            printf("Longest repeating words:\n");
            len_of_longest_rep_word=strlen(arr_all_strings[i]);
            while (strlen(arr_all_strings[i])==len_of_longest_rep_word)
            {
                if (i==0)
                {
                    break;
                }
                if (strcmp(arr_all_strings[i-1], arr_all_strings[i])==0)
                {
                    cmp_string=arr_all_strings[i];
                    printf("%s\n",cmp_string);
                }
                while ( i>0 && (strcmp(arr_all_strings[i-1], arr_all_strings[i])==0) )
                {
                    i--;
                }
                if (i>0)
                {
                    i--;
                }
                
            }
            return;
            
        } 
    }
    printf("All words are unique.\n");
}

int remove_new_line(char** arr_puzzle, ssize_t nread, int num_line)
{
    int last=nread-1;
    for (int i = 0; i < num_line; i++)
    {
        *(arr_puzzle[i]+(last))='\0';
    }
    return last;
    
}

int create_arr_all_strings(char*** arr_all_strings, int* size_all_strings, char** arr_puzzle, int rows_puzzle, int string_len)
{
    int rows_all_strings=0;
    char* tmp=NULL;
    for (int i = 0; i < rows_puzzle; i++)
    {
        for (int j = 0; j < string_len; j++)
        {
            if (rows_all_strings>=*size_all_strings)
            {
                *size_all_strings*=2;
                *arr_all_strings=(char**)realloc(*arr_all_strings, *size_all_strings*sizeof(**arr_all_strings));
            }
            tmp=(char*)realloc(tmp, 2*sizeof(*tmp));
            tmp[0]=*(arr_puzzle[i]+j);
            tmp[1]='\0';
            *((*arr_all_strings)+rows_all_strings)=tmp;
            rows_all_strings++;
            tmp=NULL;   
        }
    }
    create_diagonal_1_strings(arr_puzzle, rows_puzzle, string_len, arr_all_strings, size_all_strings, &rows_all_strings);
    create_left_to_right_strings(arr_puzzle, rows_puzzle, string_len, arr_all_strings, size_all_strings, &rows_all_strings);
    // create_right_to_left_strings(arr_puzzle, rows_puzzle, string_len, arr_all_strings, size_all_strings, &rows_all_strings);
    create_top_to_bottom_strings(arr_puzzle, rows_puzzle, string_len, arr_all_strings, size_all_strings, &rows_all_strings); 
    // create_bottom_to_top_strings(arr_puzzle, rows_puzzle, string_len, arr_all_strings, size_all_strings, &rows_all_strings);
    // create_diag_tr_to_bl_strings(arr_puzzle, rows_puzzle, string_len, arr_all_strings, size_all_strings, &rows_all_strings);
    // create_diag_tl_to_br_strings(arr_puzzle, rows_puzzle, string_len, arr_all_strings, size_all_strings, &rows_all_strings);
    return rows_all_strings; 
}


void create_left_to_right_strings(char** arr_puzzle, int rows_puzzle, int string_len, char*** arr_all_strings, int* size_all_strings, int* rows_all_strings)
{
    for (int i = 0; i < rows_puzzle; i++)
    {
        create_l_to_r_for_row(arr_puzzle[i], string_len, arr_all_strings, rows_all_strings, size_all_strings);
    }
    
}

void create_l_to_r_for_row(char* arr_puzzle_row, int string_len, char*** arr_all_strings, int* rows_all_strings, int* size_all_strings)
{
    if (string_len==0)
    {
        string_len=strlen(arr_puzzle_row);
    }
    for (int i = 2; i <= string_len; i++)
    {
        create_i_tuple_l_to_r(arr_puzzle_row, i, string_len, arr_all_strings, rows_all_strings, size_all_strings);
    }
    
}

void create_i_tuple_l_to_r(char* arr_puzzle_row, int i, int string_len, char*** arr_all_strings, int* rows_all_strings, int* size_all_strings)
{
    char* tmp=NULL;
    for (int j=0; j<=string_len-i; j++)
    {
        if (*rows_all_strings>=*size_all_strings)
        {
            *size_all_strings*=2;
            *arr_all_strings=(char**)realloc(*arr_all_strings, *size_all_strings*sizeof(**arr_all_strings));
        }
        tmp=(char*)realloc(tmp, (i+1)*sizeof(*tmp));
        strncpy(tmp, (arr_puzzle_row+j), i);
        tmp[i]='\0';
        *((*arr_all_strings)+(*rows_all_strings))=tmp;
        (*rows_all_strings)++;
        tmp=NULL;

        if (*rows_all_strings>=*size_all_strings)
        {
            *size_all_strings*=2;
            *arr_all_strings=(char**)realloc(*arr_all_strings, *size_all_strings*sizeof(**arr_all_strings));
        }
        tmp=(char*)realloc(tmp, (i+1)*sizeof(*tmp));
        strncpy(tmp, *((*arr_all_strings)+((*rows_all_strings)-1)), i+1);
        reverse(tmp, i);
        *((*arr_all_strings)+(*rows_all_strings))=tmp;
        (*rows_all_strings)++;
        tmp=NULL;
    }
}

void reverse(char* s, int length)
{
    char c;
    int i, j;

    for (i = 0, j = length - 1; i < j; i++, j--)
    {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

// void create_diagonal_1_strings(char** arr_puzzle, int rows_puzzle, int string_len, char*** arr_all_strings, int* size_all_strings, int* rows_all_strings)
// {
//     parse_diagonal1( arr_puzzle, rows_puzzle, string_len, arr_all_strings, size_all_strings, rows_all_strings);
// }

void create_diagonal_1_strings(char** arr_puzzle, int rows_puzzle, int string_len, char*** arr_all_strings, int* size_all_strings, int* rows_all_strings)
{
    char** arr_diagonal1=NULL;
    int size_diadonal1=1;
    int rows_arr_diagonal1=0;
    arr_diagonal1=(char**)realloc(arr_diagonal1, size_diadonal1*sizeof(*arr_diagonal1));
    char* tmp=NULL;
    int i=0;
    int k=0;
    int j;
    for (int l=1; l<string_len; l++)
    {
        tmp=(char*)realloc(tmp, (string_len+1)*sizeof(*tmp));
        j=l;
        while (j>=0)
        {
            tmp[k++]=*(arr_puzzle[i]+j);
            j--;
            i++;
        }
        tmp[k]='\0';
        if (rows_arr_diagonal1>=size_diadonal1)
        {
            size_diadonal1=size_diadonal1*2;
            arr_diagonal1=(char**)realloc(arr_diagonal1, size_diadonal1*sizeof(*arr_diagonal1));
        }
        arr_diagonal1[rows_arr_diagonal1++]=tmp;
        tmp=NULL;
        k=0;
        i=0;
    }

    int n=string_len-1;
    int p;
    for (int m=1; m<rows_puzzle-1; m++)
    {
        tmp=(char*)realloc(tmp, string_len*sizeof(*tmp));
        p=m;
        while (p<rows_puzzle)
        {
            tmp[k++]=*(arr_puzzle[p]+n);
            n--;
            p++;
        }
        tmp[k]='\0';
        if (rows_arr_diagonal1>=size_diadonal1)
        {
            size_diadonal1=size_diadonal1*2;
            arr_diagonal1=(char**)realloc(arr_diagonal1, size_diadonal1*sizeof(*arr_diagonal1));
        }
        arr_diagonal1[rows_arr_diagonal1++]=tmp;
        tmp=NULL;
        k=0;
        n=string_len-1;
    }

    int r=0;
    int s;
    for (int q=rows_puzzle-2; q>=0; q--)
    {
        tmp=(char*)realloc(tmp, (string_len+1)*sizeof(*tmp));
        s=q;
        while (s<rows_puzzle)
        {
            tmp[k++]=*(arr_puzzle[s]+r);
            s++;
            r++;
        }
        tmp[k]='\0';
        if (rows_arr_diagonal1>=size_diadonal1)
        {
            size_diadonal1=size_diadonal1*2;
            arr_diagonal1=(char**)realloc(arr_diagonal1, size_diadonal1*sizeof(*arr_diagonal1));
        }
        arr_diagonal1[rows_arr_diagonal1++]=tmp;
        tmp=NULL;
        k=0;
        r=0;
    }

    int t=0;
    int v;
    for (int u=1; u<string_len-1; u++)
    {
        tmp=(char*)realloc(tmp, string_len*sizeof(*tmp));
        v=u;
        while (v<string_len)
        {
            tmp[k++]=*(arr_puzzle[t]+v);
            t++;
            v++;
        }
        tmp[k]='\0';
        if (rows_arr_diagonal1>=size_diadonal1)
        {
            size_diadonal1=size_diadonal1*2;
            arr_diagonal1=(char**)realloc(arr_diagonal1, size_diadonal1*sizeof(*arr_diagonal1));
        }
        arr_diagonal1[rows_arr_diagonal1++]=tmp;
        tmp=NULL;
        k=0;
        t=0;
    }
    create_left_to_right_strings(arr_diagonal1, rows_arr_diagonal1, 0, arr_all_strings, size_all_strings, rows_all_strings);
    for (int a = 0; a < rows_arr_diagonal1; a++)
    {
        free(arr_diagonal1[a]);
        arr_diagonal1[a]=NULL;
    }
    free(arr_diagonal1);
    arr_diagonal1=NULL;
    
}

// void create_right_to_left_strings(char** arr_puzzle, int rows_puzzle, int string_len, char*** arr_all_strings, int* size_all_strings, int* rows_all_strings)
// {
//     for (int i = 0; i < rows_puzzle; i++)
//     {
//         create_r_to_l_for_row(arr_puzzle[i], string_len, arr_all_strings, rows_all_strings, size_all_strings);
//     }
// }

// void create_r_to_l_for_row(char* arr_puzzle_row, int string_len, char*** arr_all_strings, int* rows_all_strings, int* size_all_strings)
// {
//     for (int i = 2; i <= string_len; i++)
//     {
//         create_i_tuple_r_to_l(arr_puzzle_row, i, string_len, arr_all_strings, rows_all_strings, size_all_strings);
//     }
// }

// void create_i_tuple_r_to_l(char* arr_puzzle_row, int i, int string_len, char*** arr_all_strings, int* rows_all_strings, int* size_all_strings)
// {
//     char* tmp=NULL;
//     for (int j=string_len-1; j>=i-1; j--)
//     {
//         if (*rows_all_strings>=*size_all_strings)
//             {
//                 *size_all_strings*=2;
//                 *arr_all_strings=(char**)realloc(*arr_all_strings, *size_all_strings*sizeof(**arr_all_strings));
//             }
//         tmp=(char*)realloc(tmp, (i+1)*sizeof(*tmp));
//         int l=j;
//         for(int k=0; k<i; k++ )
//         {
//             tmp[k]=*(arr_puzzle_row+l);
//             l--;
//         }
//         tmp[i]='\0';
//         *((*arr_all_strings)+(*rows_all_strings))=tmp;
//         (*rows_all_strings)++;
//         tmp=NULL;
//     }
// }

void create_top_to_bottom_strings(char** arr_puzzle, int rows_puzzle, int string_len, char*** arr_all_strings, int* size_all_strings, int* rows_all_strings)
{
    for (int i = 0; i < string_len; i++)
    {
        create_t_to_b_for_col(arr_puzzle, i, rows_puzzle, arr_all_strings, rows_all_strings, size_all_strings);
    }
}

void create_t_to_b_for_col(char** arr_puzzle, int col, int rows_puzzle, char*** arr_all_strings, int* rows_all_strings, int* size_all_strings)
{
    for (int i = 2; i <= rows_puzzle; i++)
    {
        create_i_tuple_t_to_b(arr_puzzle, col, i, rows_puzzle, arr_all_strings, rows_all_strings, size_all_strings);
    }
}

void create_i_tuple_t_to_b(char** arr_puzzle, int col, int i, int rows_puzzle, char*** arr_all_strings, int* rows_all_strings, int* size_all_strings)
{
    char* tmp=NULL;
    for (int j=0; j<=rows_puzzle-i; j++)
    {
        if (*rows_all_strings>=*size_all_strings)
        {
            *size_all_strings*=2;
            *arr_all_strings=(char**)realloc(*arr_all_strings, *size_all_strings*sizeof(**arr_all_strings));
        }
        tmp=(char*)realloc(tmp, (i+1)*sizeof(*tmp));
        for(int k=0; k<i; k++ )
        {
            tmp[k]=*(arr_puzzle[j+k]+col);
        }
        tmp[i]='\0';
        *((*arr_all_strings)+(*rows_all_strings))=tmp;
        (*rows_all_strings)++;
        tmp=NULL;
        if (*rows_all_strings>=*size_all_strings)
        {
            *size_all_strings*=2;
            *arr_all_strings=(char**)realloc(*arr_all_strings, *size_all_strings*sizeof(**arr_all_strings));
        }
        tmp=(char*)realloc(tmp, (i+1)*sizeof(*tmp));
        strncpy(tmp, *((*arr_all_strings)+((*rows_all_strings)-1)), i+1);
        reverse(tmp, i);
        *((*arr_all_strings)+(*rows_all_strings))=tmp;
        (*rows_all_strings)++;
        tmp=NULL;
    }
}







// void create_bottom_to_top_strings(char** arr_puzzle, int rows_puzzle, int string_len, char*** arr_all_strings, int* size_all_strings, int* rows_all_strings)
// {
//     for (int i = 0; i < string_len; i++)
//     {
//         create_b_to_t_for_col(arr_puzzle, i, rows_puzzle, arr_all_strings, rows_all_strings, size_all_strings);
//     }
// }

// void create_b_to_t_for_col(char** arr_puzzle, int col, int rows_puzzle, char*** arr_all_strings, int* rows_all_strings, int* size_all_strings)
// {
//     for (int i = 2; i <= rows_puzzle; i++)
//     {
//         create_i_tuple_b_to_t(arr_puzzle, col, i, rows_puzzle, arr_all_strings, rows_all_strings, size_all_strings);
//     }
// }

// void create_i_tuple_b_to_t(char** arr_puzzle, int col, int i, int rows_puzzle, char*** arr_all_strings, int* rows_all_strings, int* size_all_strings)
// {
//     char* tmp=NULL;
//     for (int j=rows_puzzle-1; j>=i-1; j--)
//     {
//         if (*rows_all_strings>=*size_all_strings)
//         {
//             *size_all_strings*=2;
//             *arr_all_strings=(char**)realloc(*arr_all_strings, *size_all_strings*sizeof(**arr_all_strings));
//         }
//         tmp=(char*)realloc(tmp, (i+1)*sizeof(*tmp));
//         for(int k=0; k<i; k++ )
//         {
//             tmp[k]=*(arr_puzzle[j-k]+col);
//         }
//         tmp[i]='\0';
//         *((*arr_all_strings)+(*rows_all_strings))=tmp;
//         (*rows_all_strings)++;
//         tmp=NULL;
//     }
// }

// void create_diag_tr_to_bl_strings(char** arr_puzzle, int rows_puzzle, int string_len, char*** arr_all_strings, int* size_all_strings, int* rows_all_strings)
// {
//     for (int i=1; i<=string_len; i++)
//     {
//         create_diag_tr_to_bl_col(arr_puzzle, i, 0, arr_all_strings, size_all_strings, rows_all_strings);
//     }
//     for (int i=1; i<rows_puzzle; i++)
//     {
//         create_diag_tr_to_bl_row(arr_puzzle, i, rows_puzzle-1, arr_all_strings, size_all_strings, rows_all_strings);
//     }
// }

// void create_diag_tr_to_bl_col(char** arr_puzzle, int col, int row, char*** arr_all_strings, int* size_all_strings, int* rows_all_strings)
// {
//     for (int i = 2; i <= col; i++)
//     {
//         create_diag_i_tuple_tr_bl(arr_puzzle, i, col, row, arr_all_strings, size_all_strings, rows_all_strings);
//     }
    
// }

// void create_diag_i_tuple_tr_bl(char** arr_puzzle, int i, int col, int row, char*** arr_all_strings, int* size_all_strings, int* rows_all_strings)
// {
//     char* tmp=NULL;
//     for (int j=col-1, l=row; l<=col-i; j--, l++)
//     {
//         if (*rows_all_strings>=*size_all_strings)
//         {
//             *size_all_strings*=2;
//             *arr_all_strings=(char**)realloc(*arr_all_strings, *size_all_strings*sizeof(**arr_all_strings));
//         }

//         tmp=(char*)realloc(tmp, (i+1)*sizeof(*tmp));
//         int m=j;
//         int n=l;
//         for(int k=0; k<i; k++ )
//         {
//             tmp[k]=*(arr_puzzle[n]+m);
//             n++;
//             m--;
//         }
//         tmp[i]='\0';
//         *((*arr_all_strings)+(*rows_all_strings))=tmp;
//         (*rows_all_strings)++;
//         tmp=NULL;
//         if (*rows_all_strings>=*size_all_strings)
//         {
//             *size_all_strings*=2;
//             *arr_all_strings=(char**)realloc(*arr_all_strings, *size_all_strings*sizeof(**arr_all_strings));
//         }
//         tmp=(char*)realloc(tmp, (i+1)*sizeof(*tmp));
//         strncpy(tmp, *((*arr_all_strings)+((*rows_all_strings)-1)), i+1);
//         reverse(tmp, i);
//         *((*arr_all_strings)+(*rows_all_strings))=tmp;
//         (*rows_all_strings)++;
//         tmp=NULL;
//     }
// }

// void create_diag_tr_to_bl_row(char** arr_puzzle, int row, int col, char*** arr_all_strings, int* size_all_strings, int* rows_all_strings)
// {
//     for (int i = 2; i <= col; i++)
//     {
//         create_diag_i_tuple_tr_bl_row(arr_puzzle, row, col, i,  arr_all_strings, size_all_strings, rows_all_strings);
//     }
// }

// void create_diag_i_tuple_tr_bl_row(char** arr_puzzle, int row, int col, int i, char*** arr_all_strings, int* size_all_strings, int* rows_all_strings)
// {
//     char* tmp=NULL;
//     for (int j=col, l=row; l<=col-i+1; j--, l++)
//     {
//         if (*rows_all_strings>=*size_all_strings)
//         {
//             *size_all_strings*=2;
//             *arr_all_strings=(char**)realloc(*arr_all_strings, *size_all_strings*sizeof(**arr_all_strings));
//         }

//         tmp=(char*)realloc(tmp, (i+1)*sizeof(*tmp));
//         int m=j;
//         int n=l;
//         for(int k=0; k<i; k++ )
//         {
//             tmp[k]=*(arr_puzzle[n]+m);
//             n++;
//             m--;
//         }
//         tmp[i]='\0';
//         *((*arr_all_strings)+(*rows_all_strings))=tmp;
//         (*rows_all_strings)++;
//         tmp=NULL;
//         if (*rows_all_strings>=*size_all_strings)
//         {
//             *size_all_strings*=2;
//             *arr_all_strings=(char**)realloc(*arr_all_strings, *size_all_strings*sizeof(**arr_all_strings));
//         }
//         tmp=(char*)realloc(tmp, (i+1)*sizeof(*tmp));
//         strncpy(tmp, *((*arr_all_strings)+((*rows_all_strings)-1)), i+1);
//         reverse(tmp, i);
//         *((*arr_all_strings)+(*rows_all_strings))=tmp;
//         (*rows_all_strings)++;
//         tmp=NULL;
//     }
// }

// void create_diag_tl_to_br_strings(char** arr_puzzle, int rows_puzzle, int string_len, char*** arr_all_strings, int* size_all_strings, int* rows_all_strings)
// {
//      for (int i=1; i<=string_len; i++)
//     {
//         create_diag_tl_to_br_col(arr_puzzle, 0, i, arr_all_strings, size_all_strings, rows_all_strings);
//     }
//     // for (int i=1; i<rows_puzzle; i++)
//     // {
//     //     create_diag_tl_to_br_row(arr_puzzle, i, rows_puzzle-1, arr_all_strings, size_all_strings, rows_all_strings);
//     // }
// }

// void create_diag_tl_to_br_col(char** arr_puzzle, int col, int row, char*** arr_all_strings, int* size_all_strings, int* rows_all_strings)
// {
//     for (int i = 2; i <= col; i++)
//     {
//         create_diag_i_tuple_tl_br(arr_puzzle, i, col, row, arr_all_strings, size_all_strings, rows_all_strings);
//     }
    
// }

// void create_diag_i_tuple_tl_br(char** arr_puzzle, int i, int col, int row, char*** arr_all_strings, int* size_all_strings, int* rows_all_strings)
// {
//     char* tmp=NULL;
//     for (int j=col-1, l=row; l<=col-i; j--, l++)
//     {
//         if (*rows_all_strings>=*size_all_strings)
//         {
//             *size_all_strings*=2;
//             *arr_all_strings=(char**)realloc(*arr_all_strings, *size_all_strings*sizeof(**arr_all_strings));
//         }

//         tmp=(char*)realloc(tmp, (i+1)*sizeof(*tmp));
//         int m=j;
//         int n=l;
//         for(int k=0; k<i; k++ )
//         {
//             tmp[k]=*(arr_puzzle[n]+m);
//             n++;
//             m--;
//         }
//         tmp[i]='\0';
//         *((*arr_all_strings)+(*rows_all_strings))=tmp;
//         (*rows_all_strings)++;
//         tmp=NULL;
//         if (*rows_all_strings>=*size_all_strings)
//         {
//             *size_all_strings*=2;
//             *arr_all_strings=(char**)realloc(*arr_all_strings, *size_all_strings*sizeof(**arr_all_strings));
//         }
//         tmp=(char*)realloc(tmp, (i+1)*sizeof(*tmp));
//         strncpy(tmp, *((*arr_all_strings)+((*rows_all_strings)-1)), i+1);
//         reverse(tmp, i);
//         *((*arr_all_strings)+(*rows_all_strings))=tmp;
//         (*rows_all_strings)++;
//         tmp=NULL;
//     }
// }

















// {
//     char* tmp=NULL;
//     for (int l=row, j=col; l<=col-i; j--, l++)
//     {
//         if (*rows_all_strings>=*size_all_strings)
//         {
//             *size_all_strings*=2;
//             *arr_all_strings=(char**)realloc(*arr_all_strings, *size_all_strings*sizeof(**arr_all_strings));
//         }

//         tmp=(char*)realloc(tmp, ((i+1)*sizeof(*tmp)));
//         int m=j;
//         int n=l;
//         for(int k=0; k<i; k++ )
//         {
//             tmp[k]=*(arr_puzzle[n]+m);
//             n++;
//             m--;
//         }
//         tmp[i]='\0';
//         *((*arr_all_strings)+(*rows_all_strings))=tmp;
//         (*rows_all_strings)++;
//         tmp=NULL;
//     }
// }