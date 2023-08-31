#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#endif /* __PROGTEST__ */

int valid_min(int, int);
int valid_hour(int, int);
int valid_day(long long int, int, int);
int valid_month(int, int);

int seg_g(int num)
{
  switch (num)
  {
  case 0:
  case 1:
  case 7:
  return 0;
  default:
  return 1;
  }
}

int seg_f(int num)
{
  switch (num)
  {
  case 1:
  case 2:
  case 3:
  case 7:
  return 0;
  default:
  return 1;
  }
}

int seg_e(int num)
{
  switch (num)
  {
  case 1:
  case 3:
  case 4:
  case 5:
  case 7:
  case 9:
  return 0;
  default:
  return 1;
  }
}

int seg_d(int num)
{
  switch (num)
  {
  case 1:
  case 4:
  case 7:
  return 0;
  default:
  return 1;
  }
}

int seg_c(int num)
{
  switch (num)
  {
  case 2:
  return 0;
  default:
  return 1;
  }
}

int seg_b(int num)
{
  switch (num)
  {
  case 5:
  case 6:
  return 0;
  default:
  return 1;
  }
}

int seg_a(int num)
{
  switch (num)
  {
  case 1:
  case 4:
  return 0;
  default:
  return 1;
  }
}

int change_digit(int curr, int next)
{
  int num_seg_changes=0;
  if(seg_a(curr)!=seg_a(next))
  {
    ++num_seg_changes;
  }
  if(seg_b(curr)!=seg_b(next))
  {
    ++num_seg_changes;
  }
  if(seg_c(curr)!=seg_c(next))
  {
    ++num_seg_changes;
  }
  if(seg_d(curr)!=seg_d(next))
  {
    ++num_seg_changes;
  }
  if(seg_e(curr)!=seg_e(next))
  {
    ++num_seg_changes;
  }
  if(seg_f(curr)!=seg_f(next))
  {
    ++num_seg_changes;
  }
  if(seg_g(curr)!=seg_g(next))
  {
    ++num_seg_changes;
  }
  return num_seg_changes;
}

int change_segment(int* p1, int next_number)
{
  int most_sig_dig1=*p1/10;
  int least_sig_dig1=*p1%10;
  int most_sig_dig_next=next_number/10;
  int least_sig_dig_next=next_number%10;
  int consumption_of_change=0;
  consumption_of_change+=change_digit(most_sig_dig1, most_sig_dig_next);
  consumption_of_change+=change_digit(least_sig_dig1, least_sig_dig_next);
  return consumption_of_change;
}

void carry_increment(long long int* py1, int* pm1, int* pd1, int* ph1, int* pi1)
{
  int min_i=0;
  int default_i= min_i;
  int min_h=0;
  int default_h= min_h;
  int min_d=1;
  int min_m=1;
  int default_m=min_m;

  if (!valid_min((*pi1), default_i))
  {
    *pi1=min_i;
    (*ph1)++;
  }
  if (!valid_hour((*ph1), default_h))
  {
    *ph1=min_h;
    (*pd1)++;
  }
  if (!valid_day(*py1, *pm1, (*pd1)))
  {
    *pd1=min_d;
    (*pm1)++;
  }
  if (!valid_month((*pm1), default_m))
  {
    *pm1=min_m;
    (*py1)++;
  }
}

void increment_min(long long int* py1, int* pm1, int* pd1, int* ph1, int* pi1, long long int* consumption)
{
  int min_i=0;
  int default_i=min_i;
  int min_h=0;
  int default_h=min_h;
  int consumption_per_minute_of_seconds_segment=200;
  *consumption+=consumption_per_minute_of_seconds_segment;
  if(!( (valid_min((*pi1+1), default_i))))
  {
    *consumption+=change_segment(pi1, min_i);
    if(!( (valid_hour((*ph1+1), default_h))))
    {
      *consumption+=change_segment(ph1, min_h);
    }
    else
    {
      *consumption+=change_segment(ph1, (*ph1+1));
    }
    (*pi1)++;
    carry_increment(py1, pm1, pd1, ph1, pi1);
  }
  else
  {
    *consumption+=change_segment(pi1, (*pi1+1));
    (*pi1)++;
  }
}

void equalise_i1_i2(long long int* py1, int* pm1, int* pd1, int* ph1, int* pi1, int i2, long long int* consumption)
{
  while ((*pi1)!=i2)
  {
    increment_min(py1, pm1, pd1, ph1, pi1, consumption);
  }
}

void increment_hour(long long int* py1, int* pm1, int* pd1, int* ph1, long long int* consumption, int*pi1)
{
  int min_h=0;
  int default_h=min_h;
  int consumption_per_hour_of_seconds_segment=200*60;
  int consumption_per_hour_of_min_segment=200;
  *consumption+=consumption_per_hour_of_seconds_segment+consumption_per_hour_of_min_segment;
  if(!( (valid_hour((*ph1+1), default_h))))
  {
    *consumption+=change_segment(ph1, min_h);
    (*ph1)++;
    carry_increment(py1, pm1, pd1, ph1, pi1);
  }
  else
  {
    *consumption+=change_segment(ph1, (*ph1+1));
    (*ph1)++;
  }
}

void equalise_h1_h2(long long int* py1, int* pm1, int* pd1, int* ph1, int h2, long long int*consumption, int*pi1)
{
  while ((*ph1)!=h2)
  {
    increment_hour(py1, pm1, pd1, ph1, consumption, pi1);
  }
}

int is_start_before_end(long long int y1, int m1, int d1, int h1, int i1, 
                     long long int y2, int m2, int d2, int h2, int i2)
{
  if (y1>y2)
  {
    return 0;
  }
  if (y1 == y2 && m1 > m2 )
  {
    return 0;
  }
  if (y1 == y2 && m1 == m2 && d1 > d2)
  {
    return 0;
  }
  if (y1 == y2 && m1 == m2 && d1 == d2 && h1 > h2)
  {
    return 0;
  }
  if (y1 == y2 && m1 == m2 && d1 == d2 && h1 == h2 && i1 > i2)
  {
    return 0;
  }
  return 1;
}

int valid_min(int i1, int i2)
{
  int minute_max = 59;
  int minute_min = 0;
  if (i1 > minute_max || i1 < minute_min || i2 > minute_max || i2 < minute_min)
  {
    return 0;
  }
  return 1;
}

int valid_hour(int h1, int h2)
{
  int max_hour = 23;
  int min_hour = 0;
  if (h1 > max_hour || h1 < min_hour || h2 > max_hour || h2 < min_hour)
  {
    return 0;
  }
  return 1;
}

int calc_february_limit(long long int y, int m)
{
  int not_leap_year=28;
  int leap_year=29;

  if (y%4000==0)
  {
    return not_leap_year;
  }
  else if (y%400==0)
  {
    return leap_year;
  }
  else if (y%100==0)
  {
    return not_leap_year;
  }
  else if (y%4==0)
  {
    return leap_year;
  }
  else
  {
    return not_leap_year;
  }
}

int calc_day_limit(long long int y, int m)
{
  int thirty_one_days = 31;
  int thirty_days = 30;
  if ( m==1 || m==3 || m==5 || m==7 || m==8 || m==10 || m==12 )
  {
    return thirty_one_days;
  }
  else if ( m==4 || m==6 || m==9 || m==11 )
  {
    return thirty_days;
  }
  else
  {
    return calc_february_limit(y, m);
  }
}

int valid_day(long long int y, int m, int d)
{
  int min_day=1;
  int day_limit_for_month = calc_day_limit(y, m);
  if (d > day_limit_for_month || d < min_day)
  {
    return 0;
  }
  return 1;
}

int valid_month(int m1, int m2)
{
  int max_month=12;
  int min_month=1;

  if (m1 < min_month || m1 > max_month || m2 < min_month || m2 > max_month)
  {
    return 0;
  }
  return 1;
}

int valid_year(long long int y1, long long int y2)
{
  long long int year_min=1600;
  if (y1 < year_min || y2 < year_min)
  {
    return 0;
  }
  return 1;
}

int valid_domain(long long int y1, int m1, int d1, int h1, int i1,
                long long int y2, int m2, int d2, int h2, int i2)
{
  int res_valid_year = valid_year(y1, y2);
  if (!(res_valid_year))
  {
    return 0;
  }
  int res_valid_month = valid_month(m1, m2);
  if (!(res_valid_month))
  {
    return 0;
  }
  int res_valid_day1 = valid_day(y1, m1, d1);
  if (!(res_valid_day1))
  {
    return 0;
  }
  int res_valid_day2 = valid_day(y2, m2, d2);
  if (!(res_valid_day2))
  {
    return 0;
  }
  int res_valid_hour = valid_hour(h1, h2);
  if (!(res_valid_hour))
  {
    return 0;
  }
  int res_valid_min = valid_min(i1, i2);
  if (!(res_valid_min))
  {
    return 0;
  }
  return 1;
}

int valid_input(long long int y1, int m1, int d1, int h1, int i1,
                long long int y2, int m2, int d2, int h2, int i2)
{
  int res_valid_domain=valid_domain(y1, m1, d1, h1, i1, y2, m2, d2, h2, i2);
  if (!(res_valid_domain))
  {
    return 0;
  }
  int res_start_before_end = is_start_before_end(y1, m1, d1, h1, i1, y2, m2, d2, h2, i2);
  if (!(res_start_before_end))
  {
    return 0;
  }
  return 1;
}

long long int convert_to_new_date(long long int y, int m, int d, int ny)
{
  long long int new_date=0;
  new_date=ny*365;
  new_date+=(y-1)/4;
  new_date-=(y-1)/100;
  new_date+=(y-1)/400;
  new_date-=(y-1)/4000;
  for (int i = 1; i <= m-1; i++)
  {
    new_date+=calc_day_limit(y, i);
  }
  new_date+=d;
  return new_date;
}

long long int calc_num_days(long long int y1, int m1, int d1, long long int y2, int m2, int d2)
{
  long long int year_diff = y2-y1;
  int new_year1 = 0;
  int new_year2 = year_diff;
  long long int new_date1=convert_to_new_date(y1, m1, d1, new_year1);
  long long int new_date2=convert_to_new_date(y2, m2, d2, new_year2);
  long long int num_days=new_date2-new_date1;
  return num_days;
}

// int calc_cons_per_24hrs_hours_seg()
// {
//   int cons=0;
//   int i;
//   for (i = 0; i < 23; i++)
//   {
//     cons+=change_segment(&i, i+1);
//   }
//   cons+=change_segment(&i, 0);
//   return cons;
// }

int energyConsumption (long long int y1, int m1, int d1, int h1, int i1,
                       long long int y2, int m2, int d2, int h2, int i2, long long int * consumption )
{
  int res_valid_input=valid_input(y1, m1, d1, h1, i1, y2, m2, d2, h2, i2);
  if (!(res_valid_input))
  {
    return 0;
  }
  *consumption=0;
  long long int* py1 = &y1;
  int* pm1 = &m1;
  int* pd1 = &d1;
  int* ph1 = &h1;
  int* pi1 = &i1;
  long long int num_days;
  equalise_i1_i2(py1, pm1, pd1, ph1, pi1, i2, consumption);
  equalise_h1_h2(py1, pm1, pd1, ph1, h2, consumption, pi1);
  if (y2-y1>4000)
  {
    long long int quotient=0;
    while (y2-y1>4000)
    {
      y2=y2-4000;
      quotient++;
    }
    
    *consumption+=quotient*427897366534LL;
  }
  num_days = calc_num_days(y1, m1, d1, y2, m2, d2);
  long long int consumption_per_24_hrs_seconds_segment=200*60*24;
  long long int consumption_per_24_hrs_minutes_segment=200*24;
  long long int consumption_per_24_hrs_hours_segment = 86; //calc_cons_per_24hrs_hours_seg();
  long long int cons_per_day=consumption_per_24_hrs_seconds_segment+consumption_per_24_hrs_minutes_segment+consumption_per_24_hrs_hours_segment;
  *consumption+=num_days*cons_per_day;
  return 1;
}

#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
{
  long long int consumption;

  assert ( energyConsumption ( 2126, 7, 3, 17, 39, 
                             206808879, 2, 6, 1, 24, &consumption ) == 1
           && consumption == 22123016204309425LL );

  assert ( energyConsumption ( 5600,  3,  1, 00, 00,
                               9600,  3,  1, 00, 00, &consumption ) == 1
           && consumption == 427897366534LL );
  assert ( energyConsumption ( 4600,  3,  1, 00, 00,
                               8600,  3,  1, 00, 00, &consumption ) == 1
           && consumption == 427897366534LL );
  assert ( energyConsumption ( 3600,  3,  1, 00, 00,
                               7600,  3,  1, 00, 00, &consumption ) == 1
           && consumption == 427897366534LL );
  assert ( energyConsumption ( 2600,  3,  1, 00, 00,
                               6600,  3,  1, 00, 00, &consumption ) == 1
           && consumption == 427897366534LL );
  assert ( energyConsumption ( 2600,  1,  1, 00, 00,
                               6600,  1,  1, 00, 00, &consumption ) == 1
           && consumption == 427897366534LL );
  assert ( energyConsumption ( 1600,  1,  1, 00, 00,
                               5600,  1,  1, 00, 00, &consumption ) == 1
           && consumption == 427897366534LL );
  assert ( energyConsumption ( 2021, 10,  1, 23, 59,
                               2021, 10,  2, 00, 00, &consumption ) == 1
           && consumption == 211LL );
  assert ( energyConsumption ( 2020, 2,  28, 23, 59,
                               2020, 2,  29, 00, 00, &consumption ) == 1
           && consumption == 211LL );
  assert ( energyConsumption ( 2045,  8, 15, 16, 42, 
                               2094,  8, 23,  8, 51, &consumption ) == 1
           && consumption == 5244028033LL );

  assert ( energyConsumption ( 2021, 10,  1, 13, 15,
                               2021, 10,  1, 18, 45, &consumption ) == 1
           && consumption == 67116LL );
  assert ( energyConsumption ( 2021, 10,  1, 13, 15,
                               2021, 10,  2, 11, 20, &consumption ) == 1
           && consumption == 269497LL );
  assert ( energyConsumption ( 2021,  1,  1, 13, 15,
                               2021, 10,  5, 11, 20, &consumption ) == 1
           && consumption == 81106033LL );
  assert ( energyConsumption ( 2024,  1,  1, 13, 15,
                               2024, 10,  5, 11, 20, &consumption ) == 1
           && consumption == 81398919LL );
  assert ( energyConsumption ( 1900,  1,  1, 13, 15,
                               1900, 10,  5, 11, 20, &consumption ) == 1
           && consumption == 81106033LL );
  assert ( energyConsumption ( 2021, 10,  1,  0,  0,
                               2021, 10,  1, 12,  0, &consumption ) == 1
           && consumption == 146443LL );
  assert ( energyConsumption ( 2021, 10,  1,  0, 15,
                               2021, 10,  1,  0, 25, &consumption ) == 1
           && consumption == 2035LL );
  assert ( energyConsumption ( 2021, 10,  1, 12,  0,
                               2021, 10,  1, 12,  0, &consumption ) == 1
           && consumption == 0LL );
  assert ( energyConsumption ( 2021, 10,  1, 12,  0,
                               2021, 10,  1, 12,  1, &consumption ) == 1
           && consumption == 204LL );
  assert ( energyConsumption ( 2021, 11,  1, 12,  0,
                               2021, 10,  1, 12,  0, &consumption ) == 0 );
  assert ( energyConsumption ( 2021, 10, 32, 12,  0,
                               2021, 11, 10, 12,  0, &consumption ) == 0 );
  assert ( energyConsumption ( 2100,  2, 29, 12,  0,
                               2100,  2, 29, 12,  0, &consumption ) == 0 );
  assert ( energyConsumption ( 2400,  2, 29, 12,  0,
                               2400,  2, 29, 12,  0, &consumption ) == 1
           && consumption == 0LL );
  return 0;
}
#endif /* __PROGTEST__ */
