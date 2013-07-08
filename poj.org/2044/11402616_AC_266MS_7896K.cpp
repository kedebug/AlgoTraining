#include <iostream>
using namespace std ;
const int DAY = 366 ;
struct NODE
{
 int a ;  // ( 1 , 1 )
 int b ;  // ( 1 , 4 )
 int c ;  // ( 4 , 1 )
 int d ;  // ( 4 , 4 )
};
int d[DAY] , day ;
bool flag[7][7][7][7][9][DAY] ;
int dir[9][2] = { { 0 , 0 } ,       //same
     { -1 , 0 } , { -2 , 0 } ,   //up
     { 0 , -1 } , { 0 , -2 } ,   //left
     { 1 , 0 } , { 2 , 0 } ,     //down
     { 0 , 1 } , { 0 , 2 } } ;  //right
bool Check( int x , int y , int num , NODE e )
{
 int a ;
 if ( e.a == 7 || e.b == 7 || e.c == 7 || e.d == 7 )
  return false ;
  a = ( 1<<(15-4*x-y) ) | ( 1<<(15-4*x-y-1) ) | 
  ( 1<<(15-4*(x+1)-y) ) | ( 1<<(15-4*(x+1)-y-1) ) ;
 if ( ( d[num]&a ) != 0 )
  return false ;
 if ( flag[e.a][e.b][e.c][e.d][3*x+y][num] == true )
  return false ;
 flag[e.a][e.b][e.c][e.d][3*x+y][num] = true ;
 return true ;
}
bool dfs( int x , int y , int num , NODE e )
{
 if ( num == day )
  return true ;
 if ( Check( x , y , num , e ) == false )
  return false ;
 int i ;
 for ( i = 0 ; i < 9 ; i++ )
 {
  int xx = x+dir[i][0] ;
  int yy = y+dir[i][1] ;
  if ( xx < 0 || xx >= 3 || yy < 0 || yy >= 3 )
   continue ;
  NODE node = e ;
  node.a++ ;
  node.b++ ;
  node.c++ ;
  node.d++ ;
  if ( xx == 0 && yy == 0 )
   node.a = 0 ;
  if ( xx == 2 && yy ==0 )
   node.c = 0 ;
  if ( xx == 0 && yy == 2 )
   node.b = 0 ;
  if ( xx == 2 && yy == 2 )
   node.d = 0 ;
  if ( dfs( xx , yy , num+1 , node ) )
   return true ;
 }
 return false ;
}
int main()
{
// freopen( "e:\\in.txt" , "r" , stdin ) ;
 while ( scanf( "%d" , &day ) != EOF && day != 0 )
 {
  int i , j ;
  memset( d , 0 , sizeof( d ) ) ;
  memset( flag , 0 , sizeof( flag ) ) ;
  for ( i = 0 ; i < day ; i++ )
  {
   for ( j = 0 ; j < 16 ; j++ )
   {
    int temp ;
    scanf( "%d" , &temp ) ;
    d[i] = ( d[i]<<1 ) | temp ;
   }
  }
  NODE node ;
  node.a = node.b = node.c = node.d = 1 ;
  if ( dfs( 1 , 1 , 0 , node ) == true )
   printf( "1\n" ) ;
  else
   printf( "0\n" ) ;
 }
 return 0 ;
}