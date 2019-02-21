#include <stdio.h>


/* This is a program that finds each digit of given number */

int Power(int base,int power); /* pow function that I implemented */
int DigitNumber(int number); /* function that finds digit of given number */



void main(void){

	int number,remainder,
		first_digit=0,second_digit=0,third_digit=0,fourth_digit=0,fifth_digit=0; /* all initialized zero for in case of non existance */

	printf("Enter the number(23-98760)> ");
	scanf("%d",&number);
	while(!(23<=number && number<=98760)){ /* keeps asking the number in the cases of out of boundaries */
		printf("Wrong number!!\n");
		printf("Enter the number(23-98760)> ");
		scanf("%d",&number);

	}

	/* 
	 * in each loop we find each digit.
	 * we find each remainder by dividing the number to 10^i+1, which gives us digit or digits 
	 * for example , for 234 ; in the first turn remainder is 4.Then we update our number to get rid of this 
	 * digit to have clean 230.In the second remainder for 10^2 is 30 and that extra zeros taken care of 
	 * in the assigment statements for each case which is the same way for one of them.
	 *
	 */

	for(int i = 0;i<DigitNumber(number);i++){  /* loop as many as digit number */
		remainder = number%Power(10,i+1);
		number-=remainder;

		switch(DigitNumber(remainder)){
			case 1: first_digit=remainder; break;
			case 2: second_digit=remainder/(Power(10,i)); break;
			case 3: third_digit=remainder/(Power(10,i)); break;
			case 4: fourth_digit=remainder/(Power(10,i)); break;
			case 5: fifth_digit=remainder/(Power(10,i)); break;
		}
	}

	if(fifth_digit!=0)  printf("\nThe fifth digit is %d\n",fifth_digit);
	if(fourth_digit!=0) printf("The fourth digit is %d\n",fourth_digit);
	if(third_digit!=0)  printf("The third digit is %d\n",third_digit);
	if(second_digit!=0) printf("The second digit is %d\n",second_digit);
	if(first_digit!=0)  printf("The first digit is %d\n",first_digit);

}	

/* basic taking power function */
int Power(int base,int power){

	int result=1;
	
	for(int i = 0;i<power;i++){
		result *= base;
	}

	return result;
}

int DigitNumber(int number){

	int temp = number; /* assign number to a temporary variable */

	/*
	 * we are geting rid of each digits in every loop and counting them as well
	 * when temp is no longer greater or equal to 1 then it means there is no digit left to count
	 */

	int digit_number=0; /*initialized for the loop */
	for(digit_number;temp>=1;++digit_number){
		temp/=10;
	}

	return digit_number;
}

