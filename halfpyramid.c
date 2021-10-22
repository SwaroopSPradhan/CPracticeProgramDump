// ====================================================================================================================	
// 	-The folowing code is to print a charecter in form of half a pyramid.
//	-Revision exercise for refereshing the knowledge of C
// 	-For c++ change the #include<stdio> to #include<iostream> and changing the printf to cout<< and scanf to cin>>
// 	-The following code is written by Swaroop Sampad Pradhan
//=====================================================================================================================


#include <stdio.h>
int main() 
{
   int i, j, rows;
   printf("Enter the number of rows: ") ;
   scanf("%d", &rows) ;
   printf("\n") ;
   for (i = 1; i <= rows; ++i)  //decides the number of rows in which the pattern is to be printed
   {
      for (j = 1; j <= i; ++j)  //decides the no of times * is to be printed in a row
         {
         printf("* ") ;
         }
      printf("\n") ;
   }
   return 0;
}

