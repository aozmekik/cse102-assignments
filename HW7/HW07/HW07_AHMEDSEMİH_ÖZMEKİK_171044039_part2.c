#include <stdio.h>

#define INFILE "input_date.txt"
#define OUTFILE "new_date.txt" 

#define START 1 /* days start from 1 */
#define MPERY 12 /* month per year */
#define DPERW 7 /* day per week */

#define TRUE 1
#define FALSE 0

#define INCREASE  1
#define DECREASE -1


typedef struct
{
	int day,mon,year;

}date;

typedef enum
{
	jan,feb,marc,apr,may,june,july,aug,sep,oct,nov,dec
}month;

typedef enum
{
	sun,mon,tue,wed,thu,fri,sat
}day;


void input_date(void); /* for part1 */
void new_date(void); /* for part2*/
int is_leap(int year); /* is the leap or not */
int cmp_date(date d1,date d2); /* compares date's, if same returns 1*/


int main()
{
	input_date();
	new_date();

	return 0;
}

void input_date(void)
{
	date sd,ed; /* start date and end date */
	int	j, /* deciding increase or decrease the date day by day */
		days[]={31,28,31,30,31,30,31,31,30,31,30,31}; /* jan-to-dec, days in month */

	FILE *fp;

	fp=fopen(INFILE,"w");

	printf("\nEnter Start Date(dd/mm/yy)> "); scanf("%d/%d/%d",&sd.day,&sd.mon,&sd.year);
	printf("\nEnter End Date(dd/mm/yy)> ");   scanf("%d/%d/%d",&ed.day,&ed.mon,&ed.year);

	/* whether increase or decrease from start date to end date */
	if (sd.year>ed.year) 	j=DECREASE;
	else if(sd.mon>ed.mon)	j=DECREASE;
	else if(sd.day>ed.day)	j=DECREASE;
	else					j=INCREASE;

	if(fp){
		date d=sd; /* temp date starts from sd */

		for(d;!cmp_date(d,ed);d.day+=j){ 

			if(is_leap(d.year))	days[feb]=29;
			else 				days[feb]=28;

			/* check current day number is in boundaries of [1,current month's day] */
			if(d.day>days[d.mon-1] || d.day<START){ /* -1 for proper index number  */
				d.mon+=j;
				if(j==INCREASE)		d.day=START;
				else if(d.mon==0)	d.day=days[MPERY-1]; /* going back to 12 */ 
				else				d.day=days[d.mon-1];  
			}
			if(d.mon>MPERY || d.mon<START){ /* if out of [1,12], update */
				d.year+=j;
				if(j==INCREASE) d.mon=START;
				else			d.mon=MPERY;
			}

			fprintf(fp,"\n%d/%d/%d",d.day,d.mon,d.year);	
		}

		fprintf(fp,"\n%d/%d/%d",d.day,d.mon,d.year);	
	}
	else
		printf("Error occured when creating the file input_date.txt");

	fclose(fp);


}

/****** Doomsday Rule Implementation **********************************************************************************
 * In this algorithm, we first find doomsday of that year,															  
 * Doomsday responds a day that is given month's corresponding date (in mem_date[] array)  							 	 
 * For example, date is 27/04/2018, doomsday of 2018 is 3,month is april so memorable date is 4,					  	
 * 3 is corresponding to a wednesday(starts from 0), so 3/4/2018 is wednesday,
 * From now on this day is our reference point, so we can just find the distance between them and find the day as well 
 **********************************************************************************************************************/

void new_date(void)
{
	date d; /* dd/MM/yyyy date format */
	int day,anc,doomsday,diff, /* anchor day, and dooms day */
		mem_date[]={3,28,0,4,9,6,11,8,5,10,7,12}; /* memorable dates in doomsday rule,respectively jan-to-dec */ 


	FILE *fpr,*fpw;

	fpr = fopen(INFILE,"r");
	fpw = fopen(OUTFILE,"w"); 

	

	if(fpr && fpw){
		while(fscanf(fpr,"%d/%d/%d",&d.day,&d.mon,&d.year)==3){
			
			switch((d.year/100)%4){
				case 0: anc=tue; break;
				case 1:	anc=sun; break;
				case 2:	anc=fri; break;
				case 3:	anc=wed; break;
			}

			doomsday=(((d.year%100)/12)+((d.year%100)%12)+((d.year%100)%12)/4)%7+anc;

			for(month m=jan;m<=dec;m++){
				if(m==d.mon-1){
					/* rules of doomsday */
					if(is_leap(d.year)){
							mem_date[jan]=4;
							mem_date[feb]=29;
					}
					else{
						mem_date[jan]=3;
						mem_date[feb]=28;
					}	
					/* nth day of that month is doomsday of the year, which can be any day of week, f.e 4th in apr is always wednesday on 2018 */
					day=mem_date[m]; 
				}

			}

			diff=d.day-day;
			if(doomsday+(diff%7))
			day=(doomsday+(diff%7+7))%7;



			fprintf(fpw,"\n");
			switch(day){
				case mon:	fprintf(fpw,"Monday, ");	break;	
				case tue:	fprintf(fpw,"Tuesday, ");	break;
				case wed: 	fprintf(fpw,"Wednesday, ");	break;
				case thu:	fprintf(fpw,"Thursday, "); 	break;
				case fri:	fprintf(fpw,"Friday, ");	break;
				case sat:	fprintf(fpw,"Saturday, ");	break;
				case sun:	fprintf(fpw,"Sunday, ");	break;
			}


			switch(d.mon-1){
				case jan: 	fprintf(fpw,"January"); 	break;	
				case feb: 	fprintf(fpw,"February");	break;
				case marc:	fprintf(fpw,"March");		break;
				case apr:	fprintf(fpw,"April");		break;
				case may:	fprintf(fpw,"May");			break;
				case june:	fprintf(fpw,"June");		break;
				case july:	fprintf(fpw,"July");		break;
				case aug:	fprintf(fpw,"August");		break;
				case sep:	fprintf(fpw,"September");	break;
				case oct:	fprintf(fpw,"October");		break;
				case nov:	fprintf(fpw,"November"); 	break;
				case dec:	fprintf(fpw,"December");	break;
			}

			fprintf(fpw," %d, %d",d.day,d.year); 	
		}

	}

	else
		printf("Error occured when opening both files!");

	fclose(fpw);
	fclose(fpr);

}

int is_leap(int year)
{
	int leap;

	if(year%4!=0)			leap=FALSE;
	else if(year%100!=0)	leap=TRUE;
	else if(year%400!=0)	leap=FALSE;
	else 					leap=TRUE;

	return leap;
}

int cmp_date(date d1,date d2)
{
	int same=0;

	if(d1.day==d2.day && d1.mon==d2.mon && d1.year==d2.year)
		same=1;
	return same;
}

