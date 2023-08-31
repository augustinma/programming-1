#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void analyse(char, char*, int, int, char*, int);
void recur(int*, char, char*, int, int, int, char*, int, int, int);

int main(void){

    char char_abb;
    int size_abb=1;
    int num_abb=0;
    char* abb=(char*)malloc(size_abb*sizeof(*abb));
    printf("Abbreviation:\n");
    while((char_abb=(char)getc(stdin))>0)
    {
        if (num_abb>=size_abb)
        {
            size_abb*=2;
            abb=(char*)realloc(abb, size_abb*sizeof(*abb));
        }
        if ((char_abb=='\n') && num_abb>0)
        {
            abb[num_abb]='\0';
            break;
        }
        else if (isupper(char_abb))
        {
            abb[num_abb++]=char_abb;
        }
        else
        {
            printf("Invalid input.\n");
            free(abb);
            abb=NULL;
            return 1;
        }
    }
    if (num_abb==0)
    {
        printf("Invalid input.\n");
        free(abb);
        abb=NULL;
        return 5;
    }

    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
    int limit_per_word;
    char prob_type;
    char* text=NULL;
    int n1=0;
    int n2=0;
    int s;
    char s_q=0;
    char e_q=0;
    printf("Problems:\n");
    while ((nread = getline(&line, &len, stdin)) != -1) 
    {
        if (nread<5)
        {
            printf("Invalid input.\n");
            break;
        }
        line[nread-1]='\0';
        text = (char*)realloc(text, nread*sizeof(*text));
        // text[0]='\"';
        if ((s=sscanf(line, " %c %d %1c%n%[^\"]%n%1c", &prob_type, &limit_per_word, &s_q, &n1, &text[1], &n2, &e_q)==5) || (s=sscanf(line, " %c %d %1c%n%n%1c", &prob_type, &limit_per_word, &s_q, &n1, &n2, &e_q))==4)
        {
            int len_text=0;
            if (s_q=='\"' && e_q=='\"')
            {
                text[0]=s_q;
                text[n2-n1+1]=e_q;
                text[n2-n1+2]='\0';
                len_text=n2-n1+2;
            }
            else
            {
                printf("Invalid input.\n");
                free(abb);
                abb=NULL;
                free(line);
                line=NULL;
                free(text);
                text=NULL;
                return 2;
            }
            if ((prob_type=='#' || prob_type=='?') && (limit_per_word>0) )
            {
                analyse(prob_type, abb, num_abb, limit_per_word, text, len_text);
            }
            else
            {
                printf("Invalid input.\n");
                free(abb);
                abb=NULL;
                free(line);
                line=NULL;
                free(text);
                text=NULL;
                return 4;
            }
        }
        else
        {
            printf("Invalid input.\n");
            free(abb);
            abb=NULL;
            free(line);
            line=NULL;
            free(text);
            text=NULL;
            return 3;
        }
        free(line);
        line=NULL;
        free(text);
        text=NULL;
    }
    free(abb);
    abb=NULL;
    free(line);
    line=NULL;
}

void analyse(char prob_type, char* abb, int num_abb, int limit_per_word, char* text, int len_text)
{
    char* buffer=(char*)malloc((len_text+1)*sizeof(*buffer));
    strcpy(buffer, text);
    // int buffer_i=0;
    // while (buffer[buffer_i]!='\0')
    // {
    //     buffer[buffer_i]=tolower(buffer[buffer_i]);
    //     buffer_i++;
    // }
    int abb_i;
    int buff_i;
    int lim_i;
    int res;
    if (prob_type=='?')
    {
        abb_i=0;
        buff_i=0;
        lim_i=0;
        res=0;
        recur(&res, prob_type, abb, abb_i, lim_i, limit_per_word, buffer, buff_i, num_abb, len_text);
        printf("> %d\n",res);
    }
    else
    {
        for (int i=1; i<=limit_per_word; i++)
        {
            abb_i=0;
            buff_i=0;
            lim_i=0;
            res=0;
            recur(&res, prob_type, abb, abb_i, lim_i, i, buffer, buff_i, num_abb, len_text);
            printf("> limit %d: %d\n", i, res);
        }
        
    }
    free(buffer);
    buffer=NULL;
}

void recur(int* res, char prob_type, char* abb, int abb_i, int lim_i, int limit_per_word, char* buffer, int buff_i, int num_abb, int len_text)
{
    if (abb[abb_i]=='\0')
    {
        if (prob_type=='?')
        {
            for (int i=buff_i; buffer[i]!='\0'; i++)
            {
                buffer[i]=tolower(buffer[i]);
            }
            printf("%s\n", buffer);
        }
        *res=((*res)+1);
        return;
    }
    else if (buffer[buff_i]=='\0' || (num_abb-abb_i)>(len_text-buff_i))
    {
        return;
    }
    if (isspace(buffer[buff_i]))
    {
        lim_i=0;
    }
    else if (isupper(buffer[buff_i]))
    {
        buffer[buff_i]=tolower(buffer[buff_i]);
    }
    if (abb[abb_i]==toupper(buffer[buff_i]))
    {
        if (lim_i<limit_per_word)
        {
            recur(res, prob_type, abb, abb_i, lim_i, limit_per_word, buffer, (buff_i+1), num_abb, len_text);
            buffer[buff_i]=abb[abb_i];
            abb_i++;
            lim_i++;
        }
    }
    recur(res, prob_type, abb, abb_i, lim_i, limit_per_word, buffer, (buff_i+1), num_abb, len_text);
}