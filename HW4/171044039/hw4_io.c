/*
** hw4_io.c:
**
** The source file implementing input and output functions.
**
** Author: Ahmed Semih Özmekik
**
** NO: 171044039
** 
*/

#include <stdio.h>
#include "hw4_io.h"



int read_polynomial3(double * a0, double * a1, double * a2, double * a3){

	printf("Polynomial format shown below , enter your coefficients due to the format...\n");
	printf("-> p(x)=a3x^3+a2x^2+a1x^1+a0\n");

	/* gets and sets of coefficients */ 

	printf("a3> ");
	scanf("%lf",a3);

	printf("\na2> ");
	scanf("%lf",a2);

	printf("\na1> ");
	scanf("%lf",a1);

	printf("\na0> ");
	scanf("%lf",a0);

	return 1;
}

int read_polynomial4(double * a0, double * a1, double * a2, double * a3,double * a4){

	printf("Polynomial format shown below , enter your coefficients due to the format...\n");
	printf("-> p(x)=a4x^4+a3x^3+a2x^2+a1x^1+a0\n");

	/* gets and sets of coefficients */ 

	printf("a4> ");
	scanf("%lf",a4);

	printf("a3> ");
	scanf("%lf",a3);

	printf("\na2> ");
	scanf("%lf",a2);

	printf("\na1> ");
	scanf("%lf",a1);

	printf("\na0> ");
	scanf("%lf",a0);

	return 1;
}




void write_polynomial3(double a0, double a1, double a2, double a3){

	if(a3!=0){
		if(a3==-1)		printf("-"); /* for every case instead of -1x^3 , it is -x^3 */
		else if(a3!=1)	printf("%+.2f",a3);	/* print value only when its not 1, 1x^3 instead x^3 */ 
		printf("x^3");
	}

	if(a2!=0){
		if(a2==-1)		printf("-");
		else if(a2!=1)	printf("%+.2f",a2);
		else if(a3!=0)	printf("+");	/* if its starting term do not add '+'' value in front of its */ 
		printf("x^2");
	}

	if(a1!=0){
		if(a1==-1)		printf("-");
		else if(a1!=1)	printf("%+.2f",a1);
		else if(a2!=0)	printf("+");
		printf("x");
	}

	if(a1==0 && a2==0 && a3==0) printf("%.2f",a0);
	else printf("%+.2f",a0);


}



void write_polynomial4(double a0, double a1, double a2, double a3,double a4){

	if(a4!=0){
		if(a4==-1)		printf("-"); 
		else if(a4!=1)	printf("%.2f",a4); 
		printf("x^4");
	}

	if(a3!=0){
		if(a3==-1)		printf("-");
		else if(a3!=1)	printf("%+.2f",a3);
		else if(a4!=0)	printf("+"); 
		printf("x^3");
	}

	if(a2!=0){
		if(a2==-1)		printf("-");
		else if(a2!=1)	printf("%+.2f",a2);
		else if(a3!=0)	printf("+");
		printf("x^2");
	}

	if(a1!=0){
		if(a1==-1)		printf("-");
		else if(a1!=1)	printf("%+.2f",a1);
		else if(a2!=0)	printf("+");
		printf("x");
	}

	if(a1==0 && a2==0 && a3==0 && a4==0) printf("%.2f",a0);
	else printf("%+.2f",a0);
	
}


