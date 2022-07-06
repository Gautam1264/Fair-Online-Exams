#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct population {
                      int sol[6][5];
                      int fitness;
                  };

int friends[6][6] = {
                      {0,1,0,0,1,0},
                      {1,0,0,1,0,1},
                      {0,0,0,0,1,1},
                      {0,1,0,0,0,0},
                      {1,0,1,0,0,0},
                      {0,1,1,1,0,0}
                    };
int bsol[6][5];
int fbsol;
struct population p1[40],mp[40],cp[40],sp[40];

void fitness ()
{
    int i,j,k,l,m,c;

    for ( i=0 ; i<40 ; i++ )
    {
        p1[i].fitness = 0;
        for ( j=0 ; j<6 ; j++ )
        {
            for ( k=j ; k<6 ;k++ )
            {
                if ( friends[j][k] == 1 )
                {
                    c = 0;
                    for ( l=0 ; l<5 ; l++ )
                    {
                        for ( m=0 ; m<5 ; m++ )
                        {
                            if ( p1[i].sol[j][l] == p1[i].sol[k][m] )
                            {
                                c = c+1 ;
                                break;
                            }
                        }
                    }
                    p1[i].fitness = p1[i].fitness + c ;
                }
            }
        }
    }
}

void cpfitness ()
{
    int i,j,k,l,m,c;

    for ( i=0 ; i<40 ; i++ )
    {
        cp[i].fitness = 0;
        for ( j=0 ; j<6 ; j++ )
        {
            for ( k=j ; k<6 ;k++ )
            {
                if ( friends[j][k] == 1 )
                {
                    c = 0;
                    for ( l=0 ; l<5 ; l++ )
                    {
                        for ( m=0 ; m<5 ; m++ )
                        {
                            if ( cp[i].sol[j][l] == cp[i].sol[k][m] )
                            {
                                c = c+1 ;
                                break;
                            }
                        }
                    }
                    cp[i].fitness = cp[i].fitness + c ;
                }
            }
        }
    }
}

void mpfitness ()
{
    int i,j,k,l,m,c;

    for ( i=0 ; i<40 ; i++ )
    {
        mp[i].fitness = 0;
        for ( j=0 ; j<6 ; j++ )
        {
            for ( k=j ; k<6 ;k++ )
            {
                if ( friends[j][k] == 1 )
                {
                    c = 0;
                    for ( l=0 ; l<5 ; l++ )
                    {
                        for ( m=0 ; m<5 ; m++ )
                        {
                            if ( mp[i].sol[j][l] == mp[i].sol[k][m] )
                            {
                                c = c+1 ;
                                break;
                            }
                        }
                    }
                    mp[i].fitness = mp[i].fitness + c ;
                }
            }
        }
    }
}

void mutation ( int gen )
{
    int i,j,l,x,y,z,c;

    for ( i=0 ; i<40 ; i++ )
    {
       for ( j=0 ; j<6 ; j++ )
       {
           x = (rand()%10);
           if ( gen>50 )
           {
              if ( x<=1 )
              {
                 y = (rand()%5);
                 c = 1;
                 while ( c==1 )
                 {
                    z = 1+(rand()%10);
                    c = 0;
                    for ( l=0 ; l<5 ; l++ )
                    {
                        if ( l!=y && z == cp[i].sol[j][l] )
                        {
                            c = 1;
                        }
                    }
                 }
                 for ( l=0 ; l<5 ; l++ )
                 {
                    if ( l!=y )
                    {
                        mp[i].sol[j][l] = cp[i].sol[j][l];
                    }

                    if ( l==y )
                    {
                        mp[i].sol[j][l] = z;
                    }
                }
              }else {

                for ( l=0 ; l<5 ; l++ )
                {
                    mp[i].sol[j][l] = cp[i].sol[j][l];
                }
             }
          }else{
                if ( x<=3 )
                {
                    y = (rand()%5);
                    c = 1;
                    while ( c==1 )
                    {
                        z = 1+(rand()%10);
                        c = 0;
                        for ( l=0 ; l<5 ; l++ )
                        {
                            if ( l!=y && z == cp[i].sol[j][l] )
                            {
                                c = 1;
                            }
                        }
                    }
                    for ( l=0 ; l<5 ; l++ )
                    {
                        if ( l!=y )
                        {
                            mp[i].sol[j][l] = cp[i].sol[j][l];
                        }

                        if ( l==y )
                        {
                            mp[i].sol[j][l] = z;
                        }
                    }
                }else {

                   for ( l=0 ; l<5 ; l++ )
                   {
                        mp[i].sol[j][l] = cp[i].sol[j][l];
                   }
               }
          }
       }
    }
    mpfitness ();
}

void swap (int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void selection ()
{
     int i,j,k;
     int arr[40] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39};

     srand ( time( NULL ) );
     for ( i=39 ; i>0 ; i-- )
     {
         j = (rand()%(i+1));
         swap(&arr[i], &arr[j]);
     }

     for ( i=0 ; i<40 ; i=i+2 )
     {
         if ( p1[arr[i]].fitness >= p1[arr[i+1]].fitness )
         {
             for ( j=0 ; j<6 ; j++ )
             {
                 for ( k=0 ; k<5 ; k++ )
                 {
                     sp[i/2].sol[j][k] = p1[arr[i+1]].sol[j][k];
                 }
             }
             sp[i/2].fitness = p1[arr[i+1]].fitness;
         }else{
             for ( j=0 ; j<6 ; j++ )
             {
                 for ( k=0 ; k<5 ; k++ )
                 {
                     sp[i/2].sol[j][k] = p1[arr[i]].sol[j][k];
                 }
             }
             sp[i/2].fitness = p1[arr[i]].fitness;
         }
     }

     for ( i=39 ; i>0 ; i-- )
     {
         j = (rand()%(i+1));
         swap(&arr[i], &arr[j]);
     }

     for ( i=0 ; i<40 ; i=i+2 )
     {
         if ( p1[arr[i]].fitness >= p1[arr[i+1]].fitness )
         {
             for ( j=0 ; j<6 ; j++ )
             {
                 for ( k=0 ; k<5 ; k++ )
                 {
                     sp[(i/2)+20].sol[j][k] = p1[arr[i+1]].sol[j][k];
                 }
             }
             sp[(i/2)+20].fitness = p1[arr[i+1]].fitness;
         }else{
             for ( j=0 ; j<6 ; j++ )
             {
                 for ( k=0 ; k<5 ; k++ )
                 {
                     sp[(i/2)+20].sol[j][k] = p1[arr[i]].sol[j][k];
                 }
             }
             sp[(i/2)+20].fitness = p1[arr[i]].fitness;
         }
     }
}

void crossover ()
{
     int i,j,k,l,m,n,x;

     for ( i=0 ; i<40 ; i=i+2 )
     {
         j = (rand()%40);
         k = (rand()%40);
         while ( k==j )
         {
            k = (rand()%40);
         }
         x = (rand()%10);
         l = 6;
         if ( x<=5 )
         {
            l = (rand()%6);
         }

         for ( m=0 ; m<6 ; m++ )
         {
             for ( n=0 ; n<5 ; n++ )
             {
                 if ( m==l )
                 {
                    cp[i].sol[m][n] = sp[j].sol[m][n] ;
                 }else {
                    cp[i].sol[m][n] = sp[k].sol[m][n] ;
                 }
             }
         }
         for ( m=0 ; m<6 ; m++ )
         {
             for ( n=0 ; n<5 ; n++ )
             {
                 if ( m==l )
                 {
                    cp[i+1].sol[m][n] = sp[k].sol[m][n] ;
                 }else {
                    cp[i+1].sol[m][n] = sp[j].sol[m][n] ;
                 }
             }
         }
     }
     cpfitness ();
}

void initial()
{
    int i,j,k,l,m,x;

    for ( i=0 ; i<40 ; i++ )
    {
       for ( j=0 ; j<6 ; j++ )
       {
           for ( k=0 ; k<5 ; k++ )
           {
               if ( k==0 )
               {
                    x = 1+(rand()%10);
                    p1[i].sol[j][k] = x;
               }
               if ( k!=0 )
               {
                   m = 1;
                   while ( m == 1 )
                   {
                     x = 1+(rand()%10);
                     for ( l=0 ; l<k ; l++ )
                     {
                         if ( p1[i].sol[j][l] == x )
                         {
                             m = 1;
                             break;
                         }
                         m = 0;
                     }
                   }
                    p1[i].sol[j][k] = x;
               }

           }
       }
    }
}

int main()
{
    int i,j,k,l,min;
    initial ();
    fitness ();

    min = 1000;
    for ( j=0 ; j<40 ; j++ )
    {
        if ( p1[j].fitness <= min )
        {
            min = p1[j].fitness;
            for ( k=0 ; k<6 ; k++ )
            {
                for ( l=0 ; l<5 ; l++ )
                {
                    bsol[k][l] = p1[j].sol[k][l];
                }
            }
            fbsol = p1[j].fitness;
        }
    }

    for ( i=0 ; i<100000 ; i++ )
    {
         selection ();
         crossover ();
         mutation (i);

         for ( j=0 ; j<40 ; j++ )
         {
             for ( k=0 ; k<6 ; k++ )
             {
                 for ( l=0 ;l<5 ; l++ )
                 {
                     p1[j].sol[k][l] = mp[j].sol[k][l];
                 }
             }
             p1[j].fitness = mp[j].fitness;
         }

         for ( j=0 ; j<40 ; j++ )
         {
             if ( p1[j].fitness <= min )
             {
                 min = p1[j].fitness;
                 for ( k=0 ; k<6 ; k++ )
                 {
                    for ( l=0 ; l<5 ; l++ )
                    {
                        bsol[k][l] = p1[j].sol[k][l];
                    }
                 }
                 fbsol = p1[j].fitness;
             }
         }
    }


    for ( k=0 ; k<40 ; k++ )
    {
        printf ("Fitness = %d\n",p1[k].fitness);
        for ( i=0 ; i<6 ; i++ )
        {
            for ( j=0 ; j<5 ; j++ )
            {
                printf ("%d ",p1[k].sol[i][j]);
            }
            printf ("\n");
        }
        printf ("\n\n");
    }

    printf ("Best Solution Fitness = %d\n",fbsol);
    for ( i=0 ; i<6 ; i++ )
    {
        for ( j=0 ; j<5 ; j++ )
        {
            printf ("%d ",bsol[i][j]);
        }
        printf ("\n");
    }
    return 0;
}

