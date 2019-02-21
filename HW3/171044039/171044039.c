#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

/* In this program there are multiple subprograms which are :
 * randomly generated horses withing the horse racing game for user to guess , simply guessing game.
 * tool for finding a number inside a big number.
 * pattern which in the order of kind of multiplication's    
 *
 * Author 	: Ahmed Semih Özmekik
 * 
 * use -lm argument for success compile of math library 
 **********************************************************************/


/* menu */
void menu(void);	

int getInt(int mini, int maxi);
int numberGeneratorBetweenRange(int min, int max);

/* horse racing game*/
void horseRacingGame(void);

/* occurence counter */
void countOccurence(void);
int DigitNumber(int number); /* function that finds digit of given number */

/* triangle of sequences */
void triangleOfSequences(void); 


void main(void){

	menu();

}

void menu(void){
	int selection;


	do{


		do{
			printf("\n1. Horse Racing Game\n2. Occurrence Counter\n3. Triangle of Sequences\n0. Exit\n");
			printf("Your Selection> ");
			selection=getInt(0,3);

		 }while(!(0<=selection && selection<=3));

		switch (selection){
		case 1: horseRacingGame(); 		break;
		case 2: countOccurence(); 		break;
		case 3: triangleOfSequences(); 	
		case 0: break;
		}	

	}while(selection!=0);
	
}


int getInt(int mini,int maxi){
	int number;

	do{
		scanf("%d",&number);
		if(!(mini<=number && number<=maxi))
			printf("Error!\nPlease enter your selection between %d to %d> ",mini,maxi);
	}while(!(mini<=number && number<=maxi));

	return number;

}

int numberGeneratorBetweenRange(int min,int max){
	int number;

	srand(time(NULL)); /* random routine */
	number = rand()%(max-min+1)+min; /* for example 3-5 : max-min+1 = 3 , 3<=number%3+min<=5 */ 

	return number;
}


void horseRacingGame(void){
	int horse_number, 	/* number of horse to be generated randomly */
		user_horse,		/* user's horse which will be taken from the user */
		horse_finish_time, 	/* each horse's speed which will be generated randomly in the race */
		winner_finish_time=21, /* initialized winner finish time as 21(bigger than max which is 20) at first so that every horse can be faster than this*/
		winner; 		/* winner horse */

	horse_number=numberGeneratorBetweenRange(3,5);

	printf("There are %d horses in the race!\n",horse_number);
	printf("Enter Your Horse> ");
	user_horse=getInt(1,horse_number);
	printf("Racing Starts...\n");

	for(int horse=1;horse<=horse_number;horse++){
		/* I did not use numberGeneratorBetweenRange() function here because every time it loops through srand(time(NULL)) restarts the time and values becoming same 
		 * due to the process time which is always the same. */
		horse_finish_time=rand()%11+10; /* 10 to 20 units */ 	

		if(horse_finish_time<=winner_finish_time){
			if(horse_finish_time==winner_finish_time){ 

				/* we have more than one tie situtations */


				/* USER TIE WITH COMPUTER */

				/* conditions for user tie with computer :
				 * 1.if current horse equals to the user's horse that means user ties with previous winner at this moment or
				 * 2.if previous winner equals to the user's horse that means computer ties with previous winner which is user's horse
				 * between this two condition there is just one different which is described down below:
	 			 *
				 *	Horse 1    : --     				Horse 1    : --
				 *	User Horse : ---       		or 		Horse 2    : ---
				 *	Horse 3    : ---					User Horse : ---
	  			 * (second condition approved)			(first condition approved)
				 *	
				 *
				 */ 

				if(horse==user_horse || winner == user_horse) 
					winner = 0; /* user tie with computer*/


				/* COMPUTER TIE WITH COMPUTER*/

				/* all other cases in this situtations */

				else
					winner = -1; /*computer tie with computer */

			}else{ /* then if no equality just update the winner vars */
				winner_finish_time = horse_finish_time; /* change the winner_finish_time with the new finish time that is smaller and which means faster*/
				winner=horse; /* change the winner */
			}
			
		}

		printf("Horse %d:",horse);

		/* printing distance units due to the speed */
		for(horse_finish_time;horse_finish_time>0;horse_finish_time--)
			printf("-");

		printf("\n");
	}

	if(winner==0)
		printf("No winner!\n");
	else if(winner==-1)
		printf("You lose, yet no winner!\n");
	else{
		if(user_horse==winner)
			printf("You win!\n");
		else
			printf("You lose! Winner is Horse %d\n",winner);
	}

}

void countOccurence(void){
	int big_number,	search_number, occurence=0, /*variables in which program computes number of occurrences of search number in big number */
		temp_piece, /* temporary var for pieces in big_number */
		big_digits,search_digits; /* digit numbers */

	printf("Give Big Number> ");
	scanf("%d",&big_number);
	printf("\nGive Search Number> ");
	scanf("%d",&search_number);

	big_digits=DigitNumber(big_number);
	search_digits=DigitNumber(search_number);

	int i = search_digits-1;  /* for example: if big digit is 8 and search digit is 2 then we need to loop for 7 times which is as long as i<big_digits*/
	int j = 0;
	while(i<big_digits){
		temp_piece=big_number%(int)pow(10,i+1); /* take the number from right to left due to the search_digits ex:for 123123 and 12 every loop> 23,123,3123,23123*/
		temp_piece/=pow(10,j++); /* then getting rid of extra digits on right, ex: 123123 and 12 > 23,12(123/10),31(3123/100)*/

		if(temp_piece==search_number) /* occurence between search_number and pieces which seperated above */
			++occurence; 

		++i;
	}
	printf("Big Number: %d\nSearch Number: %d\nOccurence: %d\n",big_number,search_number,occurence);

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

	if(number==0)
		digit_number=1; /* our algorithm here does not care about zero so we need to say that zero's digit number is one */

	return digit_number;
}


void triangleOfSequences(void){

	int number;	

	number = numberGeneratorBetweenRange(2,10);

	/* I have consider this as a multiplication table:
	 * what I mean:
	 *
	 *		   j=1		j=2 	j=3 	j=4
     * 		
	 *   i=1    1*1    
     *
	 *   i=2	2*1 	2*2 
     *
	 *	 i=3  	3*1 	3*2 	3*3 	
	 * 
     * 	 i=4 	4*1 	4*2 	4*3 	4*4
     * 
     * i is from 1 to number and j is from 1 to i and result is always j*i in this case which very similar to multiplication table 
	 */

	for(int i=1;i<=number;i++){ 

		for(int j=1;j<=i;j++){
			printf("%d ",i*j);
			
		}

		printf("\n");
	}

}
