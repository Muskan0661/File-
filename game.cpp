#include<stdio.h>
int main ()
{
	int i,j,r,c;    //i=row j=col
    char grid[r][c] = {
        {'.', '#', '.', '.'},
        {'.', 'P', '.', '.'},
        {'.', '#', '#', '.'},
        {'.', '.', '.', 'E'}
    };

	//char '#','.', 'P', 'E';

	printf("enter row and column num(4-4)=");
	scanf("%d, %d", &i,&j);

     int startpoint=(1,1);
     int exit=(3,3);

     if(i==1 && j==1  )
  		{
  			printf("starting point ");
		  }
		  if (i==3 && j==3)
{
	printf("exit");
	  }	 if(i==0 && j==1 && i==2 && j==1 && j==2)
	  {
	  	printf("is not valid"); }
	   else
	   printf("can escape");
	   }
