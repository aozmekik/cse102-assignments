#include <stdio.h>

#define OPNUM 3

/* Author : Ahmed Semih Özmekik															  *
 * This is the implementation of a recursive function which finds the operations,         *
 * between the numbers of given array in order. Operations can only be +,-,*			  *
 * The algorithm is simple, which is brute force. Brute forcing starts from last element. * 
 * And from that element to first element, program finds a solution of every operations.  *
 * Since it goes backwards, reverse of the operations added to solution.   				  *
 * If no solution found for given expected value, space characters returned   		  	  *
 ******************************************************************************************/


typedef enum
{
	plus,minus,multiply 
}operator;

char* find_operations(int arr[], int expected_val, char operations[],
size_t arr_len, int cursor, int current); /* cursor and current must be given zero*/ 
int operation(int n1,int n2,operator op); /* finds the reverse result of the operations */


int main()
{

	char operations[6]; /* n-1 elements and one null element */
	int arr[6]={25,12,6,10,32,8};

	find_operations(arr,44,operations,6,0,0);
	
	printf("%s\n",operations);



	return 0;
}


char* find_operations(int arr[], int expected_val, char operations[],
size_t arr_len,int cursor, int current)
{
	char ops[OPNUM]="+-*";

	if(cursor==0)	current=expected_val; /* at first case, current starts from expected value*/

	cursor=arr_len-1; /* proper index; from last element to first element */
	
	/* at the element second, check whether the result equals to first element */
	if(arr_len==2){
		for(int op=plus;op<OPNUM;op++){ /* trying all operations */
			if(operation(current,arr[cursor],op)==arr[cursor-1]){ 
				operations[0]=ops[op]; /* starting to return all the succesful operators */
				return operations;
			}
			else
				operations[0]=' ';
		}
	}

	/* at bigger elements from second, again the same brute forcing method goes */
	else{
		for(int op=plus;op<=OPNUM;op++){
			operations=find_operations(arr,expected_val,operations,arr_len-1,cursor,
				 		operation(current,arr[cursor],op));

			if(operations[0]==' ') continue;
			else{
				operations[cursor-1]=ops[op];
				return operations;
			}
		}
	}

	operations[cursor-1]=' '; /* not found case, returns space */ 

	return operations;
}


/* in this case, n1 must be current value, and since we are starting from last,
   all operation goes from backward */
int operation(int n1,int n2,operator op)
{
	int result;
	switch(op){
		case minus:	 	result=n1+n2;		break;
		case plus:   	result=n1-n2; 		break;
		case multiply: 	result=n1/n2;		break;
	}

	return result;
}
