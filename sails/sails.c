#include <stdio.h>
#include <math.h>

int is_sheet_bigger(double, double, double, double);
void print_num_sheets(int);
int find_min_sheets(double, double, double, double, double);
int calc_rows_or_columns(double, double, double);

int main(void)
{
    printf("Sheet dimensions:\n");
    double sheet_w;
    double sheet_h;
    if (scanf("%lf %lf", &sheet_w, &sheet_h)!=2)
    {
        printf("Invalid input.\n");
        return 1;
    }
    if (sheet_w<=0 || sheet_h<=0)
    {
        printf("Invalid input.\n");
        return 1;
    }

    printf("Sail dimensions:\n");
    double sail_w;
    double sail_h;
    if (scanf("%lf %lf", &sail_w, &sail_h)!=2)
    {
        printf("Invalid input.\n");
        return 1;
    }
    if (sail_w<=0 || sail_h<=0)
    {
        printf("Invalid input.\n");
        return 1;
    }

    int no_overlap = is_sheet_bigger(sheet_w, sheet_h, sail_w, sail_h);
    int sheets_for_sail;
    if (no_overlap)
    {
        sheets_for_sail=1;
        print_num_sheets(sheets_for_sail);
    }
    else
    {
        double overlap;
        printf("Overlap:\n");
        if (scanf("%lf", &overlap)!=1)
        {
            printf("Invalid input.\n");
            return 1;
        }
        if (overlap<0)
        {
            printf("Invalid input.\n");
            return 1;
        }

        sheets_for_sail= find_min_sheets(sheet_w, sheet_h, sail_w, sail_h, overlap);
        print_num_sheets(sheets_for_sail);
    }


    return 0;
}

int is_sheet_bigger(double sheet_w, double sheet_h, double sail_w, double sail_h)
{
    if ( (sheet_w>=sail_w && sheet_h>=sail_h) || (sheet_w>=sail_h && sheet_h>=sail_w) )
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void print_num_sheets(int sheets)
{
    if (sheets<=0)
    {
        printf("No solution.\n");
    }
    else
    {
        printf("Sheets: %d\n", sheets);
    }
}

int find_min_sheets(double sheet_w, double sheet_h, double sail_w, double sail_h, double overlap)
{
    int num_columns1=calc_rows_or_columns(sail_w, sheet_w, overlap);

    int num_rows1=calc_rows_or_columns(sail_h, sheet_h, overlap);

    int num_sheets1=num_columns1*num_rows1;

    int num_columns2=calc_rows_or_columns(sail_h, sheet_w, overlap);

    int num_rows2=calc_rows_or_columns(sail_w, sheet_h, overlap);

    int num_sheets2=num_columns2*num_rows2;

    if (num_sheets1<=0 && num_sheets2<=0)
    {
        return -1;
    }
    if (num_sheets1<=0)
    {
        return num_sheets2;
    }
    else if (num_sheets2<=0)
    {
        return num_sheets1;
    }
    else
    {
        return (num_sheets1<=num_sheets2?num_sheets1:num_sheets2);
    }
}

int calc_rows_or_columns(double sail_dim, double sheet_dim, double overlap)
{
    double epsilon =1.0e-12;
    if (sail_dim-sheet_dim>0)
    {
        if (sheet_dim<overlap)
        {
            return -1;
        }
        return(ceil((sail_dim-sheet_dim)/(sheet_dim-overlap)-(((sail_dim-sheet_dim)/(sheet_dim-overlap))*epsilon))+1);
    }
    else
    {
        return 1;
    }
}