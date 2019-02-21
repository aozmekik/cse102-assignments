/**************************************************************************
 * Author: Ahmed Semih Özmekik                                            *
 * This piece of code is the implementation of hotel database management. *
 * Simply, due to function's capabilities, as a receptionist,		      *
 * You can check somenone in, or see avalaible rooms, so on and so forth. *
 * In addition to functions, you can quickly record your database,        *
 * Due to the given .txt files with the given format in the example.      *
 **************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CUSTOMER_FILE "customers.txt"
#define ROOM_FILE "rooms.txt"

#define MAXCHAR 15 


typedef struct Customer{
	char name[MAXCHAR],
		 surname[MAXCHAR],
		 gender[7]; /* female or male */
	int age;
	struct Customer *nextc; /* pointer to next customer */
}Customer;

typedef struct Room{
	int number,
		capacity,
		floor;
	Customer *c;
	struct Room *nextr; /* pointer to next room */   

}Room;

void add_room_to_end(Room *headr,Room *r);
void add_room_after_room_number(Room *headr,Room **r,int room_number);
void add_customer_to_end(Customer *headc,Customer *newc); 
void link_customers_to_room(Room *r,Customer **c);
void remove_room(Room *headr,int room_number);
void show_vacancy(Room *headr);
void get_by_floor(Room *headr,int floor);
void print_list(Room *headr);

/* additional useful functions */
Room* get_room(Room *headr,int room_number); /* return room due to given room number */ 
void print_room(Room *r); /* print given room */
Room* read_room_list(); /* reads room datas from text file */
void copy_room(Room *r1,Room *r2); /* copy component's of r2 to r1 */
void copy_customer(Customer *c1,Customer *c2); /* copy component's of c2 to c1 */


int main()
{
	Room *headr = read_room_list();
	print_list(headr);	

	return 0;
}

void add_room_to_end(Room *headr,Room *r)
{
	Room *tmpr, /* temp room, for to use it as cursor */
		 *newr=(Room*)malloc(sizeof(Room));

	copy_room(newr,r); /* copied the component for new room */

	tmpr=headr;
	while(tmpr->nextr!=NULL){
		tmpr=tmpr->nextr; 
	}
	
	/* put new room to the end of the list */
	newr->nextr=NULL;
	tmpr->nextr=newr;

	r=newr;
	
}

void add_room_after_room_number(Room *headr,Room **r,int room_number)
{
	Room *tmpr,
		 *newr=(Room*)malloc(sizeof(Room));

	Customer *c = (Customer*)malloc(sizeof(Customer));
	newr->c=c;

	/* copy the room's component */
	copy_room(newr,*r);

	/* insert the new room due to given room number */
	tmpr=get_room(headr,room_number);
	if(tmpr!=NULL)
	{
		newr->nextr=tmpr->nextr;
		tmpr->nextr=newr;
	}
	else
		add_room_to_end(headr,*r);

	free(*r);
	*r=newr;
}

void add_customer_to_end(Customer *headc,Customer *c)
{
	Customer *tmpc, /* cursor */
			 *newc; /* new customer */

	newc=(Customer*)malloc(sizeof(Customer));
	copy_customer(newc,c);

	tmpc=headc;
	while(tmpc->nextc=NULL)
		tmpc=tmpc->nextc; /* go to end */
		
	tmpc->nextc=newc;
	newc->nextc=NULL;
}


void link_customers_to_room(Room *r,Customer **c)
{
	Customer *tmpc,
		     *newc; /* customer(s) */

	
	if(r==NULL) return; /* terminate */

	/* create the customer */
	newc=(Customer*)malloc(sizeof(Customer));
	copy_customer(newc,*c);
	newc->nextc=(*c)->nextc; /* linked the tail */	


	tmpc=r->c;
	if(tmpc==NULL) /* assign */
	{
		r->c=newc;
	}
	else		/* append */
	{

		while(tmpc->nextc!=NULL)
			tmpc=tmpc->nextc;

		/* add partial customer list to the room */
		tmpc->nextc=newc;  
	}
	
	*c=newc;
}

void remove_room(Room *headr,int room_number)
{
	Room *pre_room,*next_room,
		 *tmpr = headr; /* cursor */ 

	/* previous room of room that will be deleted */
	while(tmpr->nextr->number!=room_number)	
		tmpr=tmpr->nextr;
	pre_room=tmpr;

	/* next room */
	while(tmpr->number!=room_number)
		tmpr=tmpr->nextr;
	next_room=tmpr->nextr;

	pre_room->nextr=next_room;

	/* free the allocated memory */
	free(tmpr);  
}

void show_vacancy(Room *headr)
{
	Room *tmpr = headr; /* cursor */

	printf("\nAll available rooms:");
	while(tmpr!=NULL)
	{
		if(tmpr->c==NULL)	print_room(tmpr);
		tmpr=tmpr->nextr;
	}
	printf("\n");

}

void get_by_floor(Room *headr,int floor)
{
	Room *tmpr = headr; /* cursor */
	printf("\nAll rooms in the floor %d:",floor);
	while(tmpr!=NULL)
	{
		if(tmpr->floor==floor) print_room(tmpr);
		tmpr=tmpr->nextr;
	}
	printf("\n");
}

void print_list(Room *headr)
{
	Room *tmpr = headr; /* cursor */
	printf("\nAll rooms:");
	while(tmpr!=NULL)
	{
		print_room(tmpr);
		tmpr=tmpr->nextr;
	}
	printf("\n");
}

Room* get_room(Room *headr,int room_number)
{
	Room *tmpr = headr;
	while(tmpr!=NULL)
	{
		if(tmpr->number==room_number)
			return tmpr;
		tmpr=tmpr->nextr;
	}

	return NULL; /* no room exist with the given room number */ 
}

void print_room(Room *r)
{
	Customer *tmpc; /* customer cursor */
	if(r!=NULL)
	{
		printf("\nRoom %d(Floor %d - Capacity %dx)",r->number,r->floor,r->capacity);
		if(r->c==NULL)
			printf("\n->Empty");
		else
		{
			tmpc=r->c;
			while(tmpc!=NULL)
			{
				printf("\n->%s %s(%d - %s)",tmpc->name,tmpc->surname,tmpc->age,tmpc->gender);
				tmpc=tmpc->nextc;
			}
		}
		
	}
}

Room* read_room_list(void)
{
	/* temp, customer variables */
	Customer *headc, /* head variable of partly lists */
			 *tmpc;  /* hold each records of customers whichk taken from file */
	int room_number; /* for to classify customers */ 

	/* temp, room variables */
	Room *headr, /* room list */
		 *tmpr; /* hold each records of rooms which taken from file*/

	/* allocations */
	headr=(Room*)malloc(sizeof(Room));
	tmpr=(Room*)malloc(sizeof(Room));

	headc=(Customer*)malloc(sizeof(Customer));
	tmpc=(Customer*)malloc(sizeof(Customer));

	FILE *fp;


	/* STORING ROOM RECORDS */

	fp=fopen(ROOM_FILE,"r");

	tmpr->c=NULL;
	/* push first element to head */
	if(fscanf(fp,"%d,%d,%d",&(headr->number),&(headr->floor),&(headr->capacity))==EOF)
	{
		printf("\nNo room list to be stored! Terminating... ");
	}
	headr->nextr=NULL;

	/* no need for customer for temporary time */
	tmpr->c=NULL;
	while(fscanf(fp,"%d,%d,%d",&(tmpr->number),&(tmpr->floor),&(tmpr->capacity))!=EOF)
	{	
		add_room_to_end(headr,tmpr);
	}
	
	free(tmpr); /* free the temporary space */
	fclose(fp);

	/* STORING CUSTOMER RECORDS TO ROOMS */

	fp=fopen(CUSTOMER_FILE,"r");

	tmpc->nextc=NULL;
	while(fscanf(fp,"%d,%[^ ] %[^,],%d,%s",
		&room_number,tmpc->name,tmpc->surname,&(tmpc->age),tmpc->gender)!=EOF)
	{
		link_customers_to_room(get_room(headr,room_number),&tmpc);
	}

	free(tmpc);
	fclose(fp);

	return headr;
}

/* copy r2's component to r1 */
void copy_room(Room *r1,Room *r2)
{
	r1->number=r2->number;
	r1->floor=r2->floor;
	r1->capacity=r2->capacity;
	r1->nextr=r2->nextr;

	if(r2->c!=NULL) /* if there exists a customer list for to be copied, then execute */
	{
		copy_customer(r1->c,r2->c);
	}
	else
		r1->c=NULL;

}
/* copy c2's component to c1 */
void copy_customer(Customer *c1,Customer *c2)
{
	strcpy(c1->name,c2->name);
	strcpy(c1->surname,c2->surname);
	strcpy(c1->gender,c2->gender);
	c1->age=c2->age;
	c1->nextc=c2->nextc;
}