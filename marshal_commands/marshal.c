#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct TSoldier
{
  struct TSoldier   * m_Next;
  int                 m_PersonalID;
  char                m_SecretRecord[64];
} TSOLDIER;

#endif /* __PROGTEST__ */

TSOLDIER         * mergePlatoons     ( TSOLDIER        * p1,
                                       TSOLDIER        * p2 )
{
  TSOLDIER * n=NULL;
  TSOLDIER * tmp1=NULL;
  TSOLDIER * tmp2=NULL;
  TSOLDIER * dst=NULL;
  TSOLDIER * src=NULL;
  if (p2 == NULL)
  {
    return p1;
  }
  if (p1==NULL)
  {
    return p2;
  }
  else
  {
    n=p1;
  }
  src=n;
  while (p1||p2)
  {
    if (p2!=NULL)
    {
      dst=p2;
      if (p1==NULL)
      {
        break;
      }
      tmp1=p1->m_Next;
      src->m_Next=dst;
      src=src->m_Next;
      p1=tmp1;
    }
    if (p1!=NULL)
    {
      dst=p1;
      if (p2==NULL)
      {
        break;
      }
      tmp2=p2->m_Next;
      src->m_Next=dst;
      src=src->m_Next;
      p2=tmp2;
    }
  }
  return n;
}

void               splitPlatoon      ( TSOLDIER        * src, 
                                       TSOLDIER       ** p1,
                                       TSOLDIER       ** p2 )
{
  if (src==NULL)
  {
    *p1=src;
    *p2=src;
    return;
  }
  int i=1;
  TSOLDIER *count=NULL;
  count = src;
  TSOLDIER * penultimate=NULL;
  while (count->m_Next!=NULL)
  {
    ++i;
    penultimate=count;
    count = count->m_Next;
  }
  TSOLDIER * up_to_mid=src;
  TSOLDIER * prev =up_to_mid;
  if (i%2==0)
  {
    for (int j=0; j<i/2; j++)
    {
      prev=up_to_mid;
      up_to_mid = up_to_mid->m_Next;
    }
    prev->m_Next=NULL;
  }
  else
  {
    for (int j=0; j<i/2; j++)
    {
      prev=up_to_mid;
      up_to_mid = up_to_mid->m_Next;
    }
    prev->m_Next=NULL;
    free(count);
    if (penultimate!=NULL)
    {
      penultimate->m_Next=NULL;
    }
  }
  if (i<=1)
  {
    *p1=NULL;
    *p2=NULL;
    return;
  }
  *p1= src;
  *p2= up_to_mid;
}

void               destroyPlatoon    ( TSOLDIER        * src )
{
  TSOLDIER * p=NULL;
  while (src)
  {
    p=src->m_Next;
    free(src);
    src=p;
  }
  src=NULL;
}
#ifndef __PROGTEST__
TSOLDIER         * createSoldier     ( int               id,
                                       TSOLDIER        * next )
{
  TSOLDIER * r = (TSOLDIER *) malloc ( sizeof ( *r ) );
  r -> m_PersonalID = id;
  r -> m_Next = next;
  /* r -> m_SecretRecord will be filled by someone with a higher security clearance */
  return r;  
}
int main ( void )
{
  TSOLDIER * a, *b, *c;
  a = createSoldier ( 0,
        createSoldier ( 1,
          createSoldier ( 2,
            createSoldier ( 3,
              createSoldier ( 4, NULL )))));
  b = createSoldier ( 10,
        createSoldier ( 11,
          createSoldier ( 12,
            createSoldier ( 13,
              createSoldier ( 14, NULL )))));
  c = mergePlatoons ( a, b );
  assert ( c != NULL
           && c -> m_PersonalID == 0
           && c -> m_Next != NULL
           && c -> m_Next -> m_PersonalID == 10
           && c -> m_Next -> m_Next != NULL
           && c -> m_Next -> m_Next -> m_PersonalID == 1
           && c -> m_Next -> m_Next -> m_Next != NULL
           && c -> m_Next -> m_Next -> m_Next -> m_PersonalID == 11
           && c -> m_Next -> m_Next -> m_Next -> m_Next != NULL
           && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_PersonalID == 2
           && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next != NULL
           && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_PersonalID == 12
           && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next != NULL
           && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_PersonalID == 3
           && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next != NULL
           && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_PersonalID == 13
           && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next != NULL
           && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_PersonalID == 4
           && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next != NULL
           && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_PersonalID == 14
           && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
  splitPlatoon ( c, &a, &b );
  assert ( a != NULL
           && a -> m_PersonalID == 0
           && a -> m_Next != NULL
           && a -> m_Next -> m_PersonalID == 10
           && a -> m_Next -> m_Next != NULL
           && a -> m_Next -> m_Next -> m_PersonalID == 1
           && a -> m_Next -> m_Next -> m_Next != NULL
           && a -> m_Next -> m_Next -> m_Next -> m_PersonalID == 11
           && a -> m_Next -> m_Next -> m_Next -> m_Next != NULL
           && a -> m_Next -> m_Next -> m_Next -> m_Next -> m_PersonalID == 2
           && a -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
  assert ( b != NULL
           && b -> m_PersonalID == 12
           && b -> m_Next != NULL
           && b -> m_Next -> m_PersonalID == 3
           && b -> m_Next -> m_Next != NULL
           && b -> m_Next -> m_Next -> m_PersonalID == 13
           && b -> m_Next -> m_Next -> m_Next != NULL
           && b -> m_Next -> m_Next -> m_Next -> m_PersonalID == 4
           && b -> m_Next -> m_Next -> m_Next -> m_Next != NULL
           && b -> m_Next -> m_Next -> m_Next -> m_Next -> m_PersonalID == 14
           && b -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
  destroyPlatoon ( a );
  destroyPlatoon ( b );

  a = createSoldier ( 0,
        createSoldier ( 1,
          createSoldier ( 2, NULL )));
  b = createSoldier ( 10,
        createSoldier ( 11,
          createSoldier ( 12,
            createSoldier ( 13,
              createSoldier ( 14, NULL )))));
  c = mergePlatoons ( a, b );
  assert ( c != NULL
           && c -> m_PersonalID == 0
           && c -> m_Next != NULL
           && c -> m_Next -> m_PersonalID == 10
           && c -> m_Next -> m_Next != NULL
           && c -> m_Next -> m_Next -> m_PersonalID == 1
           && c -> m_Next -> m_Next -> m_Next != NULL
           && c -> m_Next -> m_Next -> m_Next -> m_PersonalID == 11
           && c -> m_Next -> m_Next -> m_Next -> m_Next != NULL
           && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_PersonalID == 2
           && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next != NULL
           && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_PersonalID == 12
           && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next != NULL
           && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_PersonalID == 13
           && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next != NULL
           && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_PersonalID == 14
           && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
  splitPlatoon ( c, &a, &b );
  assert ( a != NULL
           && a -> m_PersonalID == 0
           && a -> m_Next != NULL
           && a -> m_Next -> m_PersonalID == 10
           && a -> m_Next -> m_Next != NULL
           && a -> m_Next -> m_Next -> m_PersonalID == 1
           && a -> m_Next -> m_Next -> m_Next != NULL
           && a -> m_Next -> m_Next -> m_Next -> m_PersonalID == 11
           && a -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
  assert ( b != NULL
           && b -> m_PersonalID == 2
           && b -> m_Next != NULL
           && b -> m_Next -> m_PersonalID == 12
           && b -> m_Next -> m_Next != NULL
           && b -> m_Next -> m_Next -> m_PersonalID == 13
           && b -> m_Next -> m_Next -> m_Next != NULL
           && b -> m_Next -> m_Next -> m_Next -> m_PersonalID == 14
           && b -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
  destroyPlatoon ( a );
  destroyPlatoon ( b );

  a = createSoldier ( 0,
        createSoldier ( 1,
          createSoldier ( 2, NULL )));
  b = createSoldier ( 10,
        createSoldier ( 11,
          createSoldier ( 12,
            createSoldier ( 13, NULL ))));
  c = mergePlatoons ( a, b );
  assert ( c != NULL
           && c -> m_PersonalID == 0
           && c -> m_Next != NULL
           && c -> m_Next -> m_PersonalID == 10
           && c -> m_Next -> m_Next != NULL
           && c -> m_Next -> m_Next -> m_PersonalID == 1
           && c -> m_Next -> m_Next -> m_Next != NULL
           && c -> m_Next -> m_Next -> m_Next -> m_PersonalID == 11
           && c -> m_Next -> m_Next -> m_Next -> m_Next != NULL
           && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_PersonalID == 2
           && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next != NULL
           && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_PersonalID == 12
           && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next != NULL
           && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_PersonalID == 13
           && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
  splitPlatoon ( c, &a, &b );
  assert ( a != NULL
           && a -> m_PersonalID == 0
           && a -> m_Next != NULL
           && a -> m_Next -> m_PersonalID == 10
           && a -> m_Next -> m_Next != NULL
           && a -> m_Next -> m_Next -> m_PersonalID == 1
           && a -> m_Next -> m_Next -> m_Next == NULL );
  assert ( b != NULL
           && b -> m_PersonalID == 11
           && b -> m_Next != NULL
           && b -> m_Next -> m_PersonalID == 2
           && b -> m_Next -> m_Next != NULL
           && b -> m_Next -> m_Next -> m_PersonalID == 12
           && b -> m_Next -> m_Next -> m_Next == NULL );
  destroyPlatoon ( a );
  destroyPlatoon ( b );

//my test
  a = createSoldier ( 0,
        createSoldier ( 1,
          createSoldier ( 2,
            createSoldier (3,
              createSoldier (4, NULL )))));
  b = createSoldier ( 10,
        createSoldier ( 11,
          createSoldier ( 12,
            createSoldier ( 13, NULL ))));
  c = mergePlatoons ( a, b );
  assert ( c != NULL);
           assert( c -> m_PersonalID == 0);
           assert( c -> m_Next != NULL);
           assert( c -> m_Next -> m_PersonalID == 10);
           assert( c -> m_Next -> m_Next != NULL);
           assert( c -> m_Next -> m_Next -> m_PersonalID == 1);
           assert( c -> m_Next -> m_Next -> m_Next != NULL);
           assert( c -> m_Next -> m_Next -> m_Next -> m_PersonalID == 11);
           assert( c -> m_Next -> m_Next -> m_Next -> m_Next != NULL);
           assert( c -> m_Next -> m_Next -> m_Next -> m_Next -> m_PersonalID == 2);
           assert( c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next != NULL);
           assert( c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_PersonalID == 12);
           assert( c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next != NULL);
           assert( c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_PersonalID == 3);
           assert( c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next != NULL);
           assert( c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_PersonalID == 13);
           assert( c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next != NULL);
           assert( c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_PersonalID == 4);
           assert( c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
  splitPlatoon ( c, &a, &b );
  assert ( a != NULL
           && a -> m_PersonalID == 0
           && a -> m_Next != NULL
           && a -> m_Next -> m_PersonalID == 10
           && a -> m_Next -> m_Next != NULL
           && a -> m_Next -> m_Next -> m_PersonalID == 1
           && a -> m_Next -> m_Next -> m_Next != NULL
           && a -> m_Next -> m_Next -> m_Next -> m_PersonalID == 11
           && a -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
  assert ( b != NULL
           && b -> m_PersonalID == 2
           && b -> m_Next != NULL
           && b -> m_Next -> m_PersonalID == 12
           && b -> m_Next -> m_Next != NULL
           && b -> m_Next -> m_Next -> m_PersonalID == 3
           && b -> m_Next -> m_Next -> m_Next != NULL
           && b -> m_Next -> m_Next -> m_Next -> m_PersonalID == 13
           && b -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
  destroyPlatoon ( a );
  destroyPlatoon ( b );

  a = createSoldier ( 0, NULL);
  b = NULL;
  c = mergePlatoons ( a, b );
  assert ( c != NULL);
  assert( c -> m_PersonalID == 0);
  assert( c -> m_Next == NULL);
  splitPlatoon ( c, &a, &b );
  assert ( a == NULL);
  assert ( b == NULL);
  destroyPlatoon (a);
  destroyPlatoon (b);
  return 0;
}
#endif /* __PROGTEST__ */
