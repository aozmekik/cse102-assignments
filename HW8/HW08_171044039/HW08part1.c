#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define BRDSIZE 10

/* Author : Ahmed Semih Özmekik															    *
 * This is the implementation of a board game.         									    *
 * Every block on that board have types which shown below. Every type has it's own feature. * 
 * There are single player game mode and multi player game mode as well.  					* 
 * Like any table game, the dice is thrown and and it is played according to this dice.     *
 ******************************************************************************************/

typedef enum{
	player1=1,player2
}player;

typedef enum{
	start,normal,penalty,snake,stair,boost,trap,finish
}blcktype;

typedef struct{
	char text;
	int data,pos_x,pos_y,jump_x,jump_y,jmpdata;
	blcktype type;

}block;



block find_block(block board[BRDSIZE][BRDSIZE],int data); /* finding the block properties such as pos_x or pos_y from given data component */
void init_board(block board[BRDSIZE][BRDSIZE]); /* initalizing board for specific design */
void print_board(block board[BRDSIZE][BRDSIZE]); /* prints board */

int play(block board[BRDSIZE][BRDSIZE],block *b,int move); /* general play function, updates current block, returns whether the games is over or not */
int single_player(block board[BRDSIZE][BRDSIZE],block b); /* single player function which is recursive */
int multi_player(block board[BRDSIZE][BRDSIZE]); /* multi_player function */




int main()
{
	block board[BRDSIZE][BRDSIZE];	
	srand(time(NULL));

	init_board(board);
	print_board(board);

	block b=board[9][9]; /* starting point */

	printf("\nTotal Move:%d",single_player(board,b));
	multi_player(board);


	return 0;

}

int play(block board[BRDSIZE][BRDSIZE],block *b,int move)
{
	int win=0;

	block nextb, 	/* the block player wants to forward */
		  firstb=*b; /* keeping first block */


	if((*b).data+move>100) /* if out of boundaries, then no move */
		return win;

	nextb=find_block(board,(*b).data+move);	
	
	switch(nextb.type){	
		case finish: 	*b=nextb; win=1; 					break;
		case normal: 	*b=nextb; 							break;
		case boost:
		case trap:
		case stair:
		case snake:	    if(nextb.jmpdata>100)	/* again, checking boundaries */			
							return win;
						else if(nextb.jmpdata<1){
							*b=firstb;
							return win;
						}	
						*b=find_block(board,nextb.jmpdata); break;

		case penalty:										break;

	}
	

	return win;

}

int single_player(block board[BRDSIZE][BRDSIZE],block b)
{
	int dice,moves=0;
	char opt;
	block firstb=b;

	dice=(rand()%6)+1;
	if(!play(board,&b,dice)){
		moves++;
		moves+=single_player(board,b);
	}

	printf("\nThe move was made in the following way: (Throwen Dice:%d)\nNew Block:%d <- Previous Block:%d\n",dice,b.data,firstb.data);

	if(moves==0)	moves=1; /* for the last move */

	return moves;
		
}

int multi_player(block board[BRDSIZE][BRDSIZE])
{
	int m1=0,m2=0,m, /* moves of players and winner*/
		dice,
		winner=0; /* winner to return */
	block b; 
	char opt;

	
	/* player 1*/
	b=board[9][9]; /* starting block */
	do{
		m1++; dice=(rand()%6)+1;
	}while(!play(board,&b,dice));

	/*player 2*/
	
	b=board[9][9]; 
	do{
		m2++; dice=(rand()%6)+1;
	}while(!play(board,&b,dice));

	
	if(m1<m2){
		winner=player1;	m=m1;
	}
	else{
		winner=player2; m=m2;
	}	  

	printf("\nGame Over! Winner is Player %d with %d moves",winner,m);
		
	return winner;
}


void print_board(block board[BRDSIZE][BRDSIZE])
{
	block b;

	printf("\t\t\t\t\t\t\t\t\t\b\b(Finish)\n");
	for(int i=0;i<BRDSIZE;i++){
		for(int j=0;j<BRDSIZE;j++){
			b=board[i][j];
			if(b.type==normal || b.type==start || b.type==finish){
				printf("%3d     ",b.data);
				if(b.type==start)
					printf("\n\t\t\t\t\t\t\t\t\t\b(Start)");	
			}
			else{
				if(b.type==snake || b.type==stair)
					printf("%2c{%2d}  ",b.text,b.jmpdata);
				else
					printf("%3c     ",b.text);
			}
				
		}
		printf("\n\n");
	}
	
}

void init_board(block board[BRDSIZE][BRDSIZE])
{
	/* coordinat data's of block types */ 
	int pe[3][2]={{8,2},{5,2},{1,5}},
		bo[5][2]={{7,1},{6,5},{5,0},{3,4},{1,8}},
		tr[4][2]={{6,9},{4,3},{2,8},{0,2}},
		st[7][3]={{9,3,11},{8,6,28},{6,1,52},{4,6,77},{3,1,77},{2,5,83},{1,1,94}},  /* in addition, jump to that data values*/
		sn[8][3]={{9,4,1},{7,5,12},{5,5,22},{4,9,44},{3,7,52},{2,2,68},{0,8,56},{0,7,52}};

	int d,updt; /* data */
	block b; /* block temp variable */


	/* initializing the board with normal block values, in first */ 
	for(int i=0;i<BRDSIZE;i++){
		if(i%2==0){
			d=(((BRDSIZE-1)-i)*10)+1;
			updt=1;
		}
		else{
			d-=11;
			updt=-1;
		}

		for(int j=0;j<BRDSIZE;j++){
			b.data=d;
			d+=updt;
			b.pos_x=i;
			b.pos_y=j;
			b.jump_x=0;
			b.jump_y=0;
			b.jmpdata=0;
			b.type=normal;
			b.text=0;
			board[i][j]=b;
		}
	}

	/* start */
	board[9][9].type=start;

	/* penalties */
	for(int i=0;i<3;i++){
		block b=board[pe[i][0]][pe[i][1]];
		b.type=penalty;
		b.text='P';
		board[pe[i][0]][pe[i][1]]=b;
	}

	/* boosts */
	for(int i=0;i<5;i++){
		block b=board[bo[i][0]][bo[i][1]];
		b.type=boost;
		b.text='B';
		b.jmpdata=b.data+5;
		board[bo[i][0]][bo[i][1]]=b;
	}

	/* traps */
	for(int i=0;i<4;i++){
		block b=board[tr[i][0]][tr[i][1]];
		b.type=trap;
		b.text='T';
		b.jmpdata=b.data-5;
		board[tr[i][0]][tr[i][1]]=b;
	}

	/* stairs */
	for(int i=0;i<7;i++){
		block b=board[st[i][0]][st[i][1]];
		b.type=stair;
		b.text='M';
		b.jmpdata=st[i][2];
		b.jump_x=find_block(board,b.jmpdata).pos_x; /* find where to jump as coordinats with jmpdata*/
		b.jump_y=find_block(board,b.jmpdata).pos_y;
		board[st[i][0]][st[i][1]]=b;
	}

	/* snakes */
	for(int i=0;i<8;i++){
		block b=board[sn[i][0]][sn[i][1]];
		b.type=snake;
		b.text='S';
		b.jmpdata=sn[i][2];
		b.jump_x=find_block(board,b.jmpdata).pos_x;
		b.jump_y=find_block(board,b.jmpdata).pos_y;
		board[sn[i][0]][sn[i][1]]=b;
	}

	/* finish */
	board[0][9].type=finish;
	

}


block find_block(block board[BRDSIZE][BRDSIZE],int data)
{
	block b;

	for(int i=0;i<BRDSIZE;i++){
		for(int j=0;j<BRDSIZE;j++){
			b=board[i][j];
			if(b.data==data)
				return b;
		}
	}

	return board[9][9]; /* if data is out of boundaries, starts from zero*/ 
}
