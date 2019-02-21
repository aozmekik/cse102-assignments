/*
** hw4_lib.c:
**
** The source file implementing library functions.
**
** Author: Ahmed Semih Özmekik
**
** No: 171044039
** 
*/

#include "hw4_lib.h"
#include <math.h>



/* Numeric approximation of the integral of the function f within the range [xs,xe],as the n increases, delta decreases and the error is reduced*/
	/**************** TRAPEZOIDAL RULE ***************

		(1)	 	delta= (xe-xs)/n  	 // since we are directly taking delta as argument no need this steps for this piece of code
		(2)	 	x(i)= x(0)+i*delta (x(0)=xs)
		(3)	 	actual result ~= (delta/2)*[f(xs)+2f(xi)+...+2f(xe-1)+f(xe)]

	/*************************************************/

double integral(double f(double x), double xs, double xe, double delta){
	

	double  xi,
			result=0.0;

	result = f(xs)+f(xe); /* getting rid of exceptions for to create general form */

	xi=xs; /* starts from zeroth term which is xs*/
	int i=1;
	while(xi<xe){
		xi=xs+i*delta; /* (2) */
		result+=2*f(xi); /* part of (3) */
		++i;
	}

	result *= delta/2;

	return result;

}





/* Numeric approximation of the integral of the function f within the range [xs,xe],as the n increases, delta decreases and the error is reduced*/
	/**************** TRAPEZOIDAL RULE FOR DOUBLE INTEGRATION ***************
	
			(1) 	delta_x=(xe-xs)/n; // since we are directly taking delta as argument no need this steps for this piece of code 
					delta_y=(ye-ys)/n;

			(2)		x(i)= x(0)+i*delta (x(0)=xs) (2.1)
					y(i)= y(0)+i*delta (y(0)=ys) (2.2)

							
							y0   y1  y2  y3...

						x0	 A - K - L - D -
							----------------
						x1	 M - P - R - N -
							----------------
						x2	 N - S - T - O -
							----------------
						x3	 B - E - F - C -
							----------------
						.
						.
						.


			for.ex: A=f(x0,y0)
													   (  3.1	)		(  3.2	)	     ( 3.3 )
			(3)		actual result ~=(delta/2)*(delta/2)[(A+B+C+D)+2*(K+L+M+N+E+F+O+N)+4*(P+R+S+T]
	
	/***********************************************************************/


double integral2(double f(double x, double y), double xs, double xe, double ys, double ye, double delta){


	double 	xi=0,yi=0,
			result=0.0;

	int i,j;

	result = f(xs,ys)+f(xs,ye)+f(xe,ys)+f(xe,ye); /* 3.1 */


	/* 3.2 (K+L+E+F) */

	for(xi=xs;;xi=xe){	
		for(i=1,yi=ys+1*delta;
							  yi<ye;
							    ++i, yi=ys+i*delta){ /* (2.1) and it goes f(xs,y1)+..+f(xs,ye-1)+f(xe,y1)+..+f(xe,ye-1) and multiply by 2 */
			result+=2*f(xi,yi);
		}

		if(xi==xe) break; 
	}

	/* 3.2 (M+N+O+N) */

	for(yi=ys;;yi=ye){
		for(i=1,xi=xs+1*delta;
						xi<xe;
						  ++i, xi=xs+i*delta){	/* (2.2) and it goes like f(x1,ys)+..+f(xe-1,ys)+f(x1,ye)+..+f(xe-1,ye) and multiply by 2 */
			result+=2*f(xi,yi);
		} 	
		
		if(yi==ye) break;
	}


	/* 3.3 (P+R+S+T)  */

	for(i=1,xi=xs+1*delta;
						  xi<xe;
						  	++i, xi=xs+i*delta){

		for(j=1,yi=ys+1*delta;						/* sum of remaining(inner) functions and multiply by 4 */
						yi<ye;
						   ++j, yi=ys+j*delta){
			result+=4*f(xi,yi);

		}
	}

	result *= (delta/2)*(delta/2);

	return result;

}


/* I used general central difference formula to approximate the derivatives */
int derivatives(double f(double a), double x, double eps, double * d1, double * d2){

	int error=0; /* equals ; 0 if no problem ,-1 in case of dividing by zero */

	if(eps==0)
		error = -1;

	*d1 = (f(x+eps)-f(x-eps))/(2*eps);

	*d2 = (f(x+eps)-2*f(x)+f(x-eps))/(eps*eps);

	return error;
}


/* finds error between numeric and actual derivatives */
int compare_derivatives(double f(double a), double d1(double b), double d2(double b), double x, double eps, double * e1, double *e2){

	double approximate_d1=0.0,approximate_d2=0.0; /* numeric derivatives */

	int error =0; /* consists of error withing the derivates func */

	error=derivatives(f,x,eps,&approximate_d1,&approximate_d2);

	*e1 = fabs(approximate_d1-d1(x));
	*e2 = fabs(approximate_d2-d2(x));

	return error;
}

/* ***WARNING***
 * this func is not working properly , yet I keep it here.
 ********************************************************* 
 * the idea was to use bisection method on the both right and left side of peak and pit points(extremum)
 * if I want to know extremum points then I needed to know roots of first derivative and roots of its derivative , and so on
 * for this nesting goes til 4th derivate,I had a bit difficult time to find peak points of peak points
 * the existences of many exceptions made this pieces of code became problematic and buggy for me 
 * again , it is not working but I wanted to show that I have tried.
 ************************************************************************************************************************/
int find_roots(double f(double x), double * x1, double * x2, double * x3, double * x4)
{

		void search_root(double f(double *a0,double *a1,double *a2,double *a3,double *a4),double *a0,double *a1,double *a2,double *a3,double *a4)
	{
		double ex0=0.0,ex1=0.0,ex2=0.0,ex3=0.0; 
		//find_extreme(f,&a0,&a1,&a2,&a3,&a4,&ex0,&ex1,&ex2,&ex3); /* finding extremum points in small to big order*/

		double function(double x) /* creating a new func with given coefficients */
		{
			double result;
			//result = poly_func(x,&a0,&a1,&a2,&a3,&a4);
			return result;
		}

		/* seeking root with extremum points which we have already found */ 
		//seek_root(f,)

	}

		int find(double f(double x), double * x1, double * x2, double * x3, double * x4)
	{
		double 	a0,a1,a2,a3,a4, /* coefficients */
				d1,d2,d3,d4; /* all derivate results */

		double  f1_root1=0.0,f1_root2=0.0,f1_root3=0.0, /* f'(x) has at most 3 roots */
				f2_root1=0.0,f2_root2=0.0, /* f''(x)=ax^2+bx+c func has two roots  */
			   	f3_root=0.0; /* f'''()=ax+b func has one root  */

		/* f(0)=a0 , f'(0)=a1 , f''(0)=2a2, f'''(0)=6a3 , f''''(0)=24a4 */

		//derivatives(f,0,eps,&d1,&d2);
		//derivate3(f,0,eps,&d3); 
		//derivate4(f,0,eps,&d4);

		a0=f(0);
		a1=d1;
		a2=d2/2; 
		a3=d3/6;
		a4=d4/24;


		f3_root=(-6*a3)/(24*a4); /* f'''(x)= 24a4x + 6a3 */

		//find_parabol(12.0*a4,6.0*a3,2.0*a2,&f2_root1,&f2_root2); /* f''(x) = 12a4x^2 + 6a3x + 2a2 */

		//f2_root1=search_root()


	}

		void find_parabol(double a,double b,double c,double *x1,double *x2)
	{
		/* ax^2+bx+c; delta=b^2-4ac; */
		double delta=0.0;
		delta = (b*b)-(4*a*c);

		*x1=(-b+sqrt(delta))/(2*a);
		*x2=(-b-sqrt(delta))/(2*a);

	}	

		void derivate3(double f(double a),double x,double eps,double *d3)
	{
		*d3 = (f(x+2)-(2*f(x+1))+(2*f(x-1)-f(x-2)))/(2*eps*eps*eps);
	}


	void derivate4(double f(double a),double x,double eps,double *d4)
	{
		*d4 = (f(x+2)-(4*f(x+1))+(6*f(x))-(4*f(x-1))+f(x-2))/(eps*eps*eps*eps);
	}


	/*** if there is a peak or pit it means there must be at most 2 roots around it ***
	 *** this general func is for finding that root by brute forcing  				***/
	void seek_root(double f(double a),double extremum,double eps,int pos)
	{
		double result=0.0;
		double LEFT=0;
		double x=0.0;

		 /* if we want it to go left along the x axis for to find root in the left,we would decrease x */   

		result = f(x);
		if(pos==LEFT){
			while(result!=0){
				x-=eps;
				result=f(x);
			}
		}else{
			while(result!=0){
				x+=eps;
				result=f(x);
			}
		}
	}  


	return 0;
}