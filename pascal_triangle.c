// ====================================================================================================================	
// 	-The folowing code is to print a charecter in form of half a pyramid.
//	-Revision exercise for refereshing the knowledge of C
// 	-For c++ change the #include<stdio> to #include<iostream> and changing the printf to cout<< and scanf to cin>>
// 	-The following code is written by Swaroop Sampad Pradhan
//=====================================================================================================================

#include <stdio.h>
int main() 
{
   int rows, term = 1, space, i, j;
   printf("Enter the number of rows: ");
   scanf("%d", &rows);
   for (i = 0; i < rows; i++)   //controls the no of rows
   {
      for (sp= 1; sp<= rows - i; sp++)   //controls the no of spaces before printing the first charecter
         printf("  ");
      for (j = 0; j <= i; j++)   //controls the digits in a row
     	 {
        	 if (j == 0)
          	  coef = 1;
        	 else
        	    term = term * (i - j + 1) / j;  //prints the digitsin a row
          printf("%4d", term);
     	 }
      printf("\n");
   }
   return 0;
}

