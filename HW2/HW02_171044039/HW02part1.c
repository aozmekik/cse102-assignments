#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* This is a program that takes the number of the students from keyboard between 3 and 50 and generates a random grade(1-100) for each student.
 * After the grades are generated, the program displays a menu which consist of 5 options.This options for user to select to get to know
 * some statistics about all students generated.
 */

void StudentScoreCalculator(int student_number); /* this is the main function for pretty much all calculations in this program */ 
void StudentGradePrint(int student_grade,int index);  /* function for printing each student's grade one by one */

/* functions for finding most successful and unsuccesful students and printing them */

int MaximumGrade(int student_grade,int max_temp);
int MinimumGrade(int student_grade,int min_temp);

void MostSuccesfulPrint(int student_grade,int index);
void MostUnsuccesfulPrint(int student_grade,int index);


char LetterGradeCalculator(int student_grade); /* letter grade for given grade */
void LetterGradePrint(int letterA,int letterB,int letterC,int letterD,int letterF); /* function for printing letter groups statics */

void AveragePrint(int total_grade,int student_number); /* average score */


void main(void){

	int student_number;


	printf("Enter Student Number(3-50)> ");
	scanf("%d",&student_number);

	while(!(3<=student_number && student_number<=50)){  /* making sure of the student number is in the interval of 3-50 */
		printf("\nNot in range!\n");
		printf("Enter Student Number(3-50)>");
	    scanf("%d",&student_number);
	}

	printf("\n");
	StudentScoreCalculator(student_number); /* calling the function which does all the work */

}


void StudentScoreCalculator(int student_number){ /*student_number is the given student number by the user*/
	
	int student_grade,total_grade=0,  /* for each student there is a student_grade and sum of them of course */ 
		max_temp=-1,min_temp=-1,  /* initialized maximum and minimum temporary variables for finding maximum grade and minimum grade as well */
		letterA=0,letterB=0,letterC=0,letterD=0,letterF=0, /* letter groups for letter grade statics of all students */
		scsfull_index,unscsfull_index, /* most succesfully student index and most unsuccesfully student index */
		selection, /* user selection for menu */
		index;  /* record of which student are we considering at that moment */

	
	/* THIS FUNCTION HAS TWO PARTS, (i.e TWO LOOPS)
	 * FIRST PART CREATES EACH STUDENT'S GRADE AND FINDS THE MOST SUCCESFULLY/UNSUCCESFULLY STUDENT BY COMPARING CURRENT STUDENT AND PREVIOUS STUDENT.
	 * PLUS , IT CALCULATES TOTAL GRADES BY SUMMING THEM ALL AND SPLITS EACH GRADE TO A LETTER GROUP.SECOND PART HAS INTERACTIVE MENU FOR USER
	 */

	/* PART ONE creating each student's grade and printing them one by one  */

	srand(40); /* creating different random number routine */
	index = 1; /* initializing for start at one */
	while(index<=student_number){
		 
		student_grade=rand()%101;  /*generating each student's grade one by one */

		/* maximum and minimum updates: checking whether the current grade is; 
		 * smaller than previous minimum grade or greater than previous maximum grade
		 * if it is , just update temp variables and if updated then update the indexes too
		 */

		max_temp=MaximumGrade(student_grade,max_temp); 
		if(max_temp==student_grade) /* if temp updated then update the index too */
			scsfull_index=index;

		min_temp=MinimumGrade(student_grade,min_temp);
		if(min_temp==student_grade)
			unscsfull_index=index;

		total_grade+=student_grade; /* adding current grade to total */

		/* spliting all grades into letter grades groups */

		switch(LetterGradeCalculator(student_grade)){
			case 'A': letterA++; break;
			case 'B': letterB++; break;
			case 'C': letterC++; break;
			case 'D': letterD++; break;
			case 'F': letterF++; break;
		}

		StudentGradePrint(student_grade,index); 

		++index; 

	}

	/* PART TWO interactive menu part for the user */

	selection = 0;
	while(selection!=-1){ /* it quits when the selection equals to -1 */

		printf("\n------------------------\n");
		printf("Student Score Calculator Menu for %d Student\n\n",student_number);
		printf("1.Most Succesful Student\n");
		printf("2.Most Unsuccesful Student\n");
		printf("3.Letter Grade Statics\n");
		printf("4.Calculate Average\n");
		printf("5.Show All Data\n");

		printf("\n\t\t\t Make Selection(1-5)> ");
		scanf("%d",&selection);

		switch(selection){
			case-1: break;
			case 1: MostSuccesfulPrint(max_temp,scsfull_index); break;
			case 2: MostUnsuccesfulPrint(min_temp,unscsfull_index); break;
			case 3: LetterGradePrint(letterA,letterB,letterC,letterD,letterF); break;
			case 4: AveragePrint(total_grade,student_number); break;
			case 5: MostSuccesfulPrint(max_temp,scsfull_index);
					MostUnsuccesfulPrint(min_temp,unscsfull_index);
					LetterGradePrint(letterA,letterB,letterC,letterD,letterF);
					AveragePrint(total_grade,student_number);
					break;
			default:
					printf("False Selection!\n");
		}
	}	
}


void StudentGradePrint(int student_grade,int index){

	printf("%d ",student_grade);

	/* printing protocol is print new line after every 10 grades */

		if(index%10==0)  
			printf("\n");
}


int MaximumGrade(int student_grade,int max_temp){
	
	if(max_temp==-1)
		max_temp = student_grade; /* first value of max_temp */
	else{
		if(max_temp<student_grade)
			max_temp = student_grade; /* changing maximum temporary variable with greater value */
	}

	return max_temp;
}

int MinimumGrade(int student_grade,int min_temp){
	
	if(min_temp==-1)
		min_temp=student_grade; 
	else{
		if(min_temp>student_grade)
			min_temp = student_grade; /* changing minimum temporary variable with smaller value */
	}

	return min_temp;
}


void MostSuccesfulPrint(int student_grade,int index){

	printf("\n\nMost Succesfully Student:\n");
	printf("Index: %d\n",index);
	printf("Score: %d\n",student_grade);
	printf("Letter Grade: %c\n",LetterGradeCalculator(student_grade));
}

void MostUnsuccesfulPrint(int student_grade,int index){

	printf("\n\nMost Unsuccesfully Student:\n");
	printf("Index: %d\n",index);
	printf("Score: %d\n",student_grade);
	printf("Letter Grade: %c\n",LetterGradeCalculator(student_grade));
}

char LetterGradeCalculator(int student_grade){
	char letter_grade;

	if(90<=student_grade && student_grade<=100)
		letter_grade = 'A';
	else if(80<=student_grade && student_grade<=89)
		letter_grade = 'B';
	else if(70<=student_grade && student_grade<=79)
		letter_grade = 'C';
	else if(60<=student_grade && student_grade<=69)
		letter_grade = 'D';
	else if(0<=student_grade && student_grade<=59)
		letter_grade = 'F';

	return letter_grade;
}

void LetterGradePrint(int letterA,int letterB,int letterC,int letterD,int letterF){
	printf("\n\n%d students got letter grade 'A'\n", letterA);
	printf("%d students got letter grade 'B'\n", letterB);
	printf("%d students got letter grade 'C'\n", letterC);
	printf("%d students got letter grade 'D'\n", letterD);
	printf("%d students got letter grade 'F'\n", letterF);

}

void AveragePrint(int total_grade,int student_number){
	double average;

	average = (double)total_grade/(double)student_number;

	printf("\n\nThe Average Score of %d Student is %.2lf\n",student_number,average);
}
