#include<stdio.h>
int main ()
{
	int marks=10,day;
	int deduct=2,final=0;
	printf("enter late days of submission=");
	scanf("%d",&day);
	if(day>=2 && day<=4)
	{
        final=marks-deduct;

	 }
	 else if(day>=5 &&  day<=7)
	 {
	 	final=marks-2*deduct;


	 }
	 else if(day>7)
	 {
           final=marks-3*deduct;
          
	 }
	 else
	 {
	 	final=marks-marks;
	 }
	 printf("after deduction marks are %d",final);

}