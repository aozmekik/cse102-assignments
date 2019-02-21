#include <stdio.h>
#include <math.h>

#define PI 3.14

/* This is a program that calculates areas of : 
 * the largest circle that fits inside a rectangle,
 * the largest square that fits inside the rectangle,
 * the smallest circle that surrounds the same rectangle,
 * the smallest square that surrounds the same rectangle.
 */



double circle_area(double radius);
double calc_hypotenuse(int side1,int side2);
double calc_radius_of_smallest_circle(int side1, int side2);
double calc_radius_of_largest_circle(int side1, int side2);
double calc_area_of_smallest_circle(int side1, int side2);
double calc_area_of_largest_circle(int side1, int side2);
double calc_area_of_smallest_square(int side1, int side2);
double calc_area_of_largest_square(int side1, int side2);
double calc_area_of_square (int side);
void display_results(double largest_circle,double largest_square,double smallest_circle,double smallest_square);


void main(void){

	// defining edges , areas and getting edges from user 
	int side1,side2;
	double largest_circle,largest_square,smallest_circle,smallest_square;

	printf("First side of rectangle> ");
	scanf("%d",&side1);
	printf("\nSecond side of rectangle> ");
	scanf("%d",&side2);

	//using functions that we have already implemented for calculating areas
	smallest_circle = calc_area_of_smallest_circle(side1,side2);
	largest_circle = calc_area_of_largest_circle(side1,side2);

	smallest_square = calc_area_of_smallest_square(side1,side2);
	largest_square = calc_area_of_largest_square(side1,side2);



	// calling the function which prints the results to the user
	display_results(largest_circle,largest_square,smallest_circle,smallest_square);

}


// calculation of area of circle
double circle_area(double radius){

	double area;
	area = PI * pow(radius,2);

	return area;

}

// pisagor theorem for calculating the hypotenuse
double calc_hypotenuse(int side1,int side2){

	double hypotenuse;

// using pow() and sqrt() functions for pisagor theorem
	hypotenuse = sqrt(pow((double)side1,2)+pow((double)side2,2));

	return hypotenuse;

}

// diameter of smallest circle equals to the hyptenuse of surrounded rectangle
double calc_radius_of_smallest_circle(int side1,int side2){

	double radius;

	//we divided by two because we are looking for radius not diameter
	radius = calc_hypotenuse(side1,side2)/2;

	return radius;
}

// diameter of largest circle equals to the small side of rectangle 
double calc_radius_of_largest_circle(int side1,int side2){

	double radius;

	//  picked the small side , divided by two and assigned to the radius 

	if(side1>side2)
		radius = (double)side2/2;
	else
		radius = (double)side1/2;

	return radius;
}


double calc_area_of_smallest_circle(int side1,int side2){

	double radius,area;

	//using functions to calculate radius and area

	radius = calc_radius_of_smallest_circle(side1,side2);

	area = circle_area(radius);

	return area;
}

double calc_area_of_largest_circle(int side1,int side2){

	double radius,area;

	radius = calc_radius_of_largest_circle(side1,side2);

	area = circle_area(radius);

	return area;

}

//calculation area of square 
double calc_area_of_square(int side){

	double area;

	// area formula of square
	area = pow((double)side,2);

	return area;
}

// each edges of largest square must be equal to the small side of rectangle
double calc_area_of_largest_square(int side1,int side2){

	double square_side , area;

	// picked the small side of rectangle and assigned to square_side which is any side of square 

	if(side1>side2)
		square_side = (double)side2;
	else
		square_side = (double)side1;

	area =  calc_area_of_square(square_side);

	return area;
}

//each edges of smallest square must be equal to the long side of rectangle
double calc_area_of_smallest_square(int side1,int side2){

	double square_side,area;

	// picked the long side of rectangle and assigned to square_side which is any side of square
	if(side1>side2)
		square_side = side1;
	else
		square_side = side2;

	area = calc_area_of_square(square_side);

	return area;
}

void display_results(double largest_circle,double largest_square,double smallest_circle,double smallest_square){


	// printing the values
	printf("\nArea of the largest circle that fits inside this rectangle: %0.2lf",largest_circle);
	printf("\nArea of the smallest circle that surrounds this rectangle: %0.2lf",smallest_circle);
	printf("\nArea of the largest square that fits inside this rectangle: %0.2lf",largest_square);
	printf("\nArea of the smallest square that surrounds the same rectangle: %0.2lf\n",smallest_square);

}