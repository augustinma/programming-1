#ifndef __PROGTEST__
#include <stdio.h>
#include <assert.h>
#endif /* __PROGTEST__ */
int input_sanitisation(int, int, int, int, int, int, int, int, int, int);
int y_sanitisation (int);
int m_sanitisation (int);
int d_sanitisation (int, int, int);
int h_sanitisation (int);
int i_sanitisation (int);
int start_precede_end (int, int, int, int, int, int, int, int, int, int);
int is_leap_year (int);
void number_of_cuckoo (int, int, int, int, int, int, int, int, int, int, long long int*);
void start_equals_end (int, int, long long int*);
void end_cuckoo (int, int, long long int*);

int cuckooClock ( int y1, int m1, int d1, int h1, int i1,
                  int y2, int m2, int d2, int h2, int i2, long long int * cuckoo )
{
  if (!(input_sanitisation(y1, m1, d1, h1, i1, y2, m2, d2, h2, i2)))  //input sanitation
  {
    return 0;
  }
  number_of_cuckoo(y1, m1, d1, h1, i1, y2, m2, d2, h2, i2, cuckoo);
  return 1;
}

#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
{
  long long int cuckoo;

  assert ( cuckooClock ( 2020, 10,  1, 13, 15,
                         2020, 10,  1, 18, 45, &cuckoo ) == 1 && cuckoo == 26 );
  assert ( cuckooClock ( 2020, 10,  1, 13, 15,
                         2020, 10,  2, 11, 20, &cuckoo ) == 1 && cuckoo == 165 );
  assert ( cuckooClock ( 2020,  1,  1, 13, 15,
                         2020, 10,  5, 11, 20, &cuckoo ) == 1 && cuckoo == 50025 );
  assert ( cuckooClock ( 2019,  1,  1, 13, 15,
                         2019, 10,  5, 11, 20, &cuckoo ) == 1 && cuckoo == 49845 );
  assert ( cuckooClock ( 1900,  1,  1, 13, 15,
                         1900, 10,  5, 11, 20, &cuckoo ) == 1 && cuckoo == 49845 );
  assert ( cuckooClock ( 2020, 10,  1,  0,  0,
                         2020, 10,  1, 12,  0, &cuckoo ) == 1 && cuckoo == 102 );
  assert ( cuckooClock ( 2020, 10,  1,  0, 15,
                         2020, 10,  1,  0, 25, &cuckoo ) == 1 && cuckoo == 0 );
  assert ( cuckooClock ( 2020, 10,  1, 12,  0,
                         2020, 10,  1, 12,  0, &cuckoo ) == 1 && cuckoo == 12 );
  assert ( cuckooClock ( 2020, 11,  1, 12,  0,
                         2020, 10,  1, 12,  0, &cuckoo ) == 0 );
  assert ( cuckooClock ( 2020, 10, 32, 12,  0,
                         2020, 11, 10, 12,  0, &cuckoo ) == 0 );
  assert ( cuckooClock ( 2100,  2, 29, 12,  0,
                         2100,  2, 29, 12,  0, &cuckoo ) == 0 );
  assert ( cuckooClock ( 2400,  2, 29, 12,  0,
                         2400,  2, 29, 12,  0, &cuckoo ) == 1 && cuckoo == 12 );
  assert ( cuckooClock ( 2020,  2, 29, 12,  0,
                         2020,  2, 29, 12,  0, &cuckoo ) == 1 && cuckoo == 12 );
  assert ( cuckooClock ( 2021,  2, 28, 0,  0,                                  //my_test
                         2022,  2, 27, 23,  59, &cuckoo ) == 1 && cuckoo == 65700);
  assert ( cuckooClock ( 2020,  2, 28, 0,  0,                                  //my_test
                         2021,  2, 27, 23,  59, &cuckoo ) == 1 && cuckoo == 65880);
  assert ( cuckooClock ( 2020,  2, 29, 0,  0,                                  //my_test
                         2021,  2, 27, 23,  59, &cuckoo ) == 1 && cuckoo == 65700);
  assert ( cuckooClock ( 2020,  2, 28, 0,  0,                                  //my_test
                         2024,  2, 27, 23,  59, &cuckoo ) == 1 && cuckoo == 262980);
  return 0;
}
#endif /* __PROGTEST__ */

int input_sanitisation (int y1, int m1, int d1, int h1, int i1, int y2, int m2, int d2, int h2, int i2)
{
  if (!(y_sanitisation(y1)))
  {
    return 0;
  }
  else if (!(y_sanitisation(y2)))
  {
    return 0;
  }
  else if (!(m_sanitisation(m1)))
  {
    return 0;
  }
  else if (!(m_sanitisation(m2)))
  {
    return 0;
  }
  else if (!(d_sanitisation(d1, m1, y1)))
  {
    return 0;
  }
  else if(!(d_sanitisation(d2, m2, y2)))
  {
    return 0;
  }
  else if (!(h_sanitisation(h1)))
  {
    return 0;
  }
  else if (!(h_sanitisation(h2)))
  {
    return 0;
  }
  else if (!(i_sanitisation(i1)))
  {
    return 0;
  }
  else if (!(i_sanitisation(i2)))
  {
    return 0;
  }
  else if (!(start_precede_end(y1, m1, d1, h1, i1, y2, m2, d2, h2, i2)))
  {
    return 0;
  }
  else 
  {
    return 1;
  }
}

int y_sanitisation (int y)
{
  if (y>=1600)
  {
    return 1;
  }
  else 
  {
    return 0;
  }
}

int m_sanitisation (int m)
{
  if (m<=12 && m>=1)
  {
    return 1;
  }
  else 
  {
    return 0;
  }
}

int d_sanitisation (int d, int m, int y)
{
  if (d<1)
  {
    return 0;
  }
  int j;
  if (m==1 || m==3 || m==5 || m==7 || m==8 || m==10 || m==12)
  {
    j=1;
  }
  else if (m==2)
  {
    j=2;
  }
  else j=3;
  
  switch (j)
  {
  case 1: if(d>31)
          {
            return 0;
          }return 1;
  case 2: if (is_leap_year(y))
          {
            if (d>29)
            {
              return 0;
            }
          }
          else
          {
            if (d>28)
            {
              return 0;
            }
          }return 1;
  case 3: if (d>30)
          {
            return 0;
          }return 1;
  default: return 0;
  }
}

int is_leap_year(int y)
{
  if ((y%4000)==0)
  {
    return 0;
  }
  else if((y%400)==0)
  {
    return 1;
  }
  else if((y%100)==0)
  {
    return 0;
  }
  else if ((y%4)==0)
  {
    return 1;
  }
  else 
  {
    return 0;
  }
}

int h_sanitisation (int h)
{
  if (h<=23 && h>=0)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

int i_sanitisation (int i)
{
  if (i<=59 && i>=0)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

int start_precede_end(int y1, int m1, int d1, int h1, int i1, int y2, int m2, int d2, int h2, int i2)
{
  if (y1<y2)
  {
    return 1;
  }
  else if(y1==y2)
  {
    int start=m1*1000000+d1*10000+h1*100+i1;
    int end=m2*1000000+d2*10000+h2*100+i2;
    if (start<=end)
    {
      return 1;
    }
    else 
    {
      return 0;
    }
  }
  else
  {
    return 0;
  }
}

void number_of_cuckoo(int y1, int m1, int d1, int h1, int i1, int y2, int m2, int d2, int h2, int i2, long long int* cuckoo)
{
  *cuckoo=0;

  if (y1==y2 && m1==m2 && d1==d2 && h1==h2 && i1==i2)
  {
    start_equals_end(i1, h1, cuckoo);
    return;
  }

  while ((h1!=h2) || (i1!=i2))
  {
    if (i1==30)
    {
      *cuckoo+=1;
    }
    else if (i1==0)
    {
      *cuckoo+=(h1%12);
      if ((h1%12)==0)
      {
        *cuckoo+=12;
      }
    }
    else
    {
      *cuckoo+=0;
    }
    ++i1;
    if(!(i_sanitisation(i1)))
    {
      i1=0;
      ++h1;
      if(!(h_sanitisation(h1)))
      {
        h1=0;
        ++d1;
        if(!(d_sanitisation(d1, m1, y1)))
        {
          d1=1;
          ++m1;
          if(!(m_sanitisation(m1)))
          {
            m1=1;
            ++y1;
          }
        }
      }
    }
  }

  if ((y1!=y2) || (m1!=m2) || (d1!=d2))
  {
    int days_y2_minus_y1=0;
    int years=0;
    int leap_day=0;
    int days=0;
    while ((m1!=m2) || (d1!=d2))
    {
      ++d1;
      ++days;
      if(!(d_sanitisation(d1, m1, y1)))
      {
        d1=1;
        ++m1;
        if(!(m_sanitisation(m1)))
        {
          m1=1;
          ++y1;
        }
      }
    }
    *cuckoo=(*cuckoo)+(180*days);
    if (y1!=y2)
    {
      if( (m1>=3) || ((m1==2) && (d1==29)) ) 
      {
        if (is_leap_year(y1))
        {
          --leap_day;
        }
      }
      while(y1!=y2)
      {
        if (is_leap_year(y1))
        {
          ++leap_day;
        }
        ++y1;
        ++years;
      }
      if( (m2>=3) || ((m2==2) && (d2==29)) )                       //((m2<2) || ((m2==2)&&(d2<29)) )
      {
        if (is_leap_year(y2))
        {
          ++leap_day;
        }
      }
      days_y2_minus_y1=((365*years)+leap_day);
      *cuckoo=(*cuckoo)+(days_y2_minus_y1*180);
    }
  }
  end_cuckoo(i2, h2, cuckoo);
}

void start_equals_end (int i1, int h1, long long int*cuckoo)
{
  if (i1==30)
  {
    *cuckoo=1;
  }
  else if (i1==0)
  {
    *cuckoo=(h1%12);
    if (*cuckoo==0)
    {
      *cuckoo+=12;
    }
  }
  else
  {
    *cuckoo=0;
  }
}

void end_cuckoo(int i1, int h1, long long int*cuckoo)
{
  if (i1==30)
  {
    *cuckoo+=1;
  }
  else if (i1==0)
  {
    *cuckoo+=(h1%12);
    if (h1%12==0)
    {
      *cuckoo+=12;
    }
  }
  else
  {
    *cuckoo+=0;
  }
}
