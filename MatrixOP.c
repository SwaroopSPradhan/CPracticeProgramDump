// ====================================================================================================================	
// 	-The folowing code is to print a charecter in form of half a pyramid.
//	-Revision exercise for refereshing the knowledge of C
// 	-For c++ change the #include<stdio> to #include<iostream> and changing the printf to cout<< and scanf to cin>>
// 	-The following code is written by Swaroop Sampad Pradhan
// 	-The following program can be extended for n dimension swquare matrix by using dynamic allocation for array size
//=====================================================================================================================
#include<stdio.h>
#include<stdlib.h>

//  addition 
	void add(int m[3][3], int n[3][3], int sum[3][3])
	{
	  for(int i=0;i<3;i++)
	    for(int j=0;j<3;j++)
 	     sum[i][j] = m[i][j] + n[i][j];
	}

//  subtraction 
	void subtract(int m[3][3], int n[3][3], int result[3][3])
	{	
 	 for(int i=0;i<3;i++)
 	   for(int j=0;j<3;j++)
	      result[i][j] = m[i][j] - n[i][j];
	}

//  multiplication 
	void multiply(int m[3][3], int n[3][3], int result[3][3])
	{
  	for(int i=0; i < 3; i++)
           {
   		 for(int j=0; j < 3; j++)
   	 	   {
     		        result[i][j] = 0; // assign 0
      
          // find product
   		       for (int k = 0; k < 3; k++)
     		 	result[i][j] += m[i][k] * n[k][j];
    	           }
  	    }
	}

//  for finding transpose 
	void transpose(int matrix[3][3], int trans[3][3])
	{
         for (int i = 0; i < 3; i++)
  	      for (int j = 0; j < 3; j++)
 	 	 trans[i][j] = matrix[j][i];
	}

//  printing
	void display(int matrix[3][3])
	{	
  	for(int i=0; i<3; i++)
  		{
    		for(int j=0; j<3; j++)
      	       	printf("%d\t",matrix[i][j]);

   		   printf("\n");
  		}
	}

//====================main starts from here
int main()
{
  int a[3][3] ;  //first matrix
  int b[3][3] ;  //second matrix
  int c[3][3];
  int choice;   // variable to take choice
printf("Enter the first square matrix of order 3 : ") ;
  for(int i = 0; i < 3; i++)
	{
	 for(int j = 0; j < 3; j++)
  	 scanf("%2d",&a[i][j]);
	}
printf("Enter the second matrix of order 3 : ") ;
for(int i = 0; i < 3; i++)
	{
	 for(int j = 0; j < 3; j++)	
	 scanf("%2d",&b[i][j]);
	}



  // printing for conformation
  printf("First Matrix:\n");
  display(a);
  printf("Second Matrix:\n");
  display(b);

 

 // menu to choose the operation
  do
  {
   
    printf("\nChoose the matrix operation,\n");
    printf("----------------------------\n");
    printf("1. Addition\n");
    printf("2. Subtraction\n");
    printf("3. Multiplication\n");
    printf("4. Transpose\n");
    printf("5. Exit\n");
    printf("----------------------------\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
      case 1:
        add(a, b, c);
        printf("Sum of matrix: \n");
        display(c);
        break;
      case 2:
        subtract(a, b, c);
        printf("Subtraction of matrix: \n");
        display(c);
        break;
      case 3:
        multiply(a, b, c);
        printf("Multiplication of matrix: \n");
        display(c);
        break;
      case 4:
        printf("Transpose of the first matrix: \n");
        transpose(a, c);
        display(c);
        printf("Transpose of the second matrix: \n");
        transpose(b, c);
        display(c);
        break;
      case 5:
        printf("Thank You.\n");
        exit(0);
      default:
        printf("Invalid input.\n");
        printf("Please enter the correct input.\n");
    }
  }while(1);

  return 0;
}
