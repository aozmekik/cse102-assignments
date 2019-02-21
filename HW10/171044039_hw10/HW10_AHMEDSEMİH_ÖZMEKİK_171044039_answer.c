#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DATAFILE "data.txt"

#define LIST_T "output_prime_LinkedList.txt" /* linked-list, time shown output file */
#define LIST_F "primes_LinkedList.txt" /* linked-list, output of prime numbers */
#define ARRAY_T "output_prime_dynamic_array.txt" /* array, time shown output file */
#define ARRAY_F "primes_dynamic_array.txt" /* array, output of prime numbers */

#define TRUE 1
#define FALSE 0

typedef struct prime{
	int number;	
	struct prime *nextp; /* next prime's pointer */
}prime;

// PART 1 
int readLine(FILE **fp,int *n); /* reads each line from given file pointer */

// PART 2 AND PART 3
/* they find primes and record them into data structures of they own.			   *
 * and writes the time passed between calculations, finally print primes to screen */  
int findPrimeLinkedList(int max_num); 
int findPrimeArray(int max_num); 


// PART 4
/* they called in functions which mentioned above. 				*
 * write the primes in the files and calculates the time passed */ 
void writePrimeLinkedList(prime *head);
void writePrimeArray(int primes[],size_t pnumber);

void insert(int number,prime*head);
int isPrime(int n);

int main()
{
	FILE *fp;
	/* since we use append mode, files must be clean before we start */
	fp=fopen(ARRAY_T,"w"); fclose(fp);
	fp=fopen(LIST_T,"w"); fclose(fp);

	printf("\nFinding Prime Numbers...");
	printf("\nThis may take a while..");
	findPrimeLinkedList(500000);
	findPrimeLinkedList(750000);
	findPrimeLinkedList(1000000);

	findPrimeArray(500000);
	findPrimeArray(750000);
	findPrimeArray(1000000);
	printf("\nDone! You can check the files for information...\n");

	

	return 0;
}

int findPrimeLinkedList(int max_num)
{
	int n, /* tmp number which taken from .txt file */
		pnumber=0; /* total prime number */
	FILE *fp;
	clock_t start_t,end_t;

	fp=fopen(DATAFILE,"r");

	start_t = clock(); /* starts */
	printf("\nFinding Prime Numbers...");
	/* record prime numbers into linked-list */
	
	prime *head = NULL;
	head = (prime*)malloc(sizeof(prime));


	do readLine(&fp,&n);
	while(!isPrime(n));
	pnumber++;	

	(*head).number=n; /* found first prime number which belongs to head node */
	(*head).nextp=NULL;

	while(readLine(&fp,&n)!=EOF && n<=max_num){ 
		if(isPrime(n)){
			insert(n,head); /* insert all prime numbers to linked-list due to head node */
			pnumber++;
		}
	}
	end_t=clock();

	/* print the calculation time to a file */
	fp=fopen(LIST_T,"a"); /* append mode */
	fprintf(fp,"\nCalculation time for between 1 and %d : %lf ms",
		max_num,1000.0*(double)(end_t-start_t)/CLOCKS_PER_SEC);
	fclose(fp);

	/* print the numbers stored in linked-list */ 
	prime *current=head;
	while(current->nextp!=NULL){
		printf("\n%d",current->number);
		current=current->nextp;
	}printf("\n%d",current->number);

	if(max_num==1000000) /* write them only in this case, for part 4 */
		writePrimeLinkedList(head);

	return pnumber;
}

void writePrimeLinkedList(prime *head)
{
	clock_t start_t,end_t;
	FILE *fp;

	/* print the numbers to a file */

	fp=fopen(LIST_F,"w");

	start_t = clock(); 
	prime *current=head;
	while(current->nextp!=NULL){
		fprintf(fp,"\n%d",current->number);
		current=current->nextp;
	}fprintf(fp,"\n%d",current->number);
	end_t = clock();

	fclose(fp);

	/* print the file written time to a file */
	fp=fopen(LIST_T,"a");
	fprintf(fp,"\nFile written time: %lf ms",
		1000.0*(double)(end_t-start_t)/CLOCKS_PER_SEC); /* milisecond* */
	fclose(fp);
}

int findPrimeArray(int max_num)
{
	int n,
		pnumber=0, 
		*primes=NULL;  /* array */
	size_t arr_size=0;
	clock_t start_t,end_t;

	FILE *fp; 

	fp=fopen(DATAFILE,"r"); /* reopen the file to start finding primes again */

	/* record prime numbers into array */

	start_t = clock();
	while(readLine(&fp,&n)!=EOF && n<=max_num){
		if(isPrime(n)){
			++arr_size;
			primes=(int*)realloc(primes,arr_size*sizeof(int)); /* reallocating memory for new primes */
			primes[arr_size-1]=n; 
			printf("\n%d",primes[arr_size-1]); 
			pnumber++;
		}
	}
	end_t= clock();
	fclose(fp);

	/* print the calculation time, to a file */
	fp=fopen(ARRAY_T,"a"); /* append mode */
	fprintf(fp,"\nCalculation time for between 1 and %d : %lf ms",
		max_num,1000.0*(double)(end_t-start_t)/CLOCKS_PER_SEC);
	fclose(fp);


	if(max_num==1000000)
		writePrimeArray(primes,pnumber);

	return pnumber;
}

void writePrimeArray(int primes[],size_t pnumber)
{
	clock_t start_t,end_t;
	FILE *fp;

	fp = fopen(ARRAY_F,"a");

	/* print the numbers to a file */

	start_t = clock();
	for(int i=0;i<pnumber;i++)
		fprintf(fp,"\n%d",primes[i]);
	end_t = clock();

	fclose(fp);

	/* print the file written time to a file */

	fopen(ARRAY_T,"a");
	fprintf(fp,"\nFile written time: %lf",
		1000.0*(double)(end_t-start_t)/CLOCKS_PER_SEC); /* milisecond* */
	fclose(fp);

}

void insert(int number,prime *head)
{
	prime *lastp,*newp;

	lastp = head; 
	while((*lastp).nextp!=NULL) /* going to the last item */
		lastp=lastp->nextp; 
	
	

	/* insert */
	newp = (prime*)malloc(sizeof(prime));
	(*newp).number=number;
	(*newp).nextp=NULL; /* making newp, the last item */
	(*lastp).nextp=newp;

}


int readLine(FILE **fp,int *n) /* double pointer for to start from where it left off */
{	
	return fscanf(*fp,"%d,00",n);
}


int isPrime(int n) /* AKS primality test */
{
	int prime=FALSE,
		i=5,j=2; /* for purpose of AKS primality test */
	switch(n){
		case 1: return prime;
		case 2:
		case 3: prime=TRUE; return prime;
	}
	if(n%2==0)	return prime; 
	if(n%3==0)	return prime;
	else{
		while(i*i<=n){
			if(n%i==0)
				return prime;
			i+=j;
			j=6-j;;
		}
		prime=TRUE;
	}
	
	
	return prime;
}

