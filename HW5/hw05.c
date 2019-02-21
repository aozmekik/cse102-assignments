#include <stdio.h>


/********************************************************************************************
 * This program is the implementation of "Turkish Draughts" game.							*
 * There is a 8x8 board and all sizing done due to that size accordingly 					*
 * Program does not fit very well with this rule "Maximum capture compulsory", 				*
 * Yet it carries out a capture automatically if it is possible to capture,					*
 * after each move you gain the right to capture.											*
 *   																						*
 *  Author : Ahmed Semih Özmekik															*
 *																							*
 ********************************************************************************************
 */

 
typedef enum {white_man, black_man, white_king, black_king, empty} piece; /* representing game objects in the game table*/ 
typedef enum {white = 10, black = 20} player; /* representing player1 and player2 */
 

void init_board(piece board[][8]); 
void display_board(piece board[][8]);

void sample_game_1(void); 
void sample_game_2(void);



int move(piece board[][8], int from_x, int from_y, int to_x, int to_y, player p); /* general function for move, prints captured enemy number */
int move_piece(piece board[][8],int from_x,int from_y,int to_x,int to_y,piece p);/* makes the move for given piece, if it's valid */
int move_men(piece board[][8],int *from_x,int *from_y,int to_x,int to_y,piece p); /* move mechanics for only men*/
int move_king(piece board[][8],int *from_x,int *from_y,int to_x,int to_y,piece p); /* move mechanics for only king */
int check_move(const piece board[][8], int from_x, int from_y, int to_x, int to_y, piece p); /* checks the move's result, 1 , 0 or -2 */
int auto_move(piece board[][8], int from_x, int from_y, int *to_x, int *to_y, piece p); /* captures automatically any piece which can be captured */
int check_end_of_game(piece board[][8]); /* checks if any player run out of pieces */



int main()
{
	sample_game_1();
	printf("\n\n");


	return 0;
}

void init_board(piece board[][8])
{
	for(int i=0;i<8;i++){

		if(i==1 || i==2){
			for(int j=0;j<8;j++)
				board[i][j] = black_man; /* placed on second and third rows */ 
		}

		else if(i==5 || i==6){
			for(int j=0;j<8;j++)
				board[i][j] = white_man;
		}

		else{
			for(int j=0;j<8;j++)
				board[i][j] = empty; /* empty representation for the rest */
		}


	}
	
}

void display_board(piece board[][8])
{ 
	printf("\n");
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			switch(board[i][j]){
				case empty: 	 printf("-"); break;
				case white_man:  printf("w"); break;
				case black_man:  printf("b"); break;
				case white_king: printf("W"); break;
				case black_king: printf("B"); break; 
			}	
		}
		printf("\n"); 
	}
}

int move(piece board[][8], int from_x, int from_y, int to_x, int to_y, player p)
{	
	int result=-2;

	piece pi = board[from_x][from_y];

	/* firstly checking if the player p is trying to move a piece that does not belong to him.*/
	if(p==white){
		if(pi!=white_king && pi!=white_man){
			result = -1; 
			return result;
		}
	}
	else if(p==black){
		if(pi!=black_king && pi!=black_man){
			result = -1;
			return result;
		}
	}

	result = move_piece(board,from_x,from_y,to_x,to_y,pi);

	printf("\nThe move is executed with %d of opponents pieces captured\n",result);

	return result;

}


int move_piece(piece board[][8],int from_x,int from_y,int to_x,int to_y,piece p)
{
	int result=-2,
		total_result=0;

	if(from_x<0 && from_x>7)
		return result;
	if(from_y<0 && from_y>7)
		return result;
	if(to_x<0 && to_x>7)
		return result;
	if(to_x<0 && to_x>7)
		return result;

	
	/* white_man's and black_man's moves */
	if(p==white_man || p==black_man){
		result = move_men(board,&from_x,&from_y,to_x,to_y,p);
		while(result==1){ /* in case of capture, move claim earned */
			total_result+=result;
			auto_move(board,from_x,from_y,&to_x,&to_y,p); /* got the target location from auto_move (x,y) */
			result=move_men(board,&from_x,&from_y,to_x,to_y,p);
		}
	}
	/* white_king's and black_king's moves */
	else if(p==white_king || p==black_king){
		result = move_king(board,&from_x,&from_y,to_x,to_y,p);
		while(result==1){
			total_result+=result;
			auto_move(board,from_x,from_y,&to_x,&to_y,p);
			result=move_king(board,&from_x,&from_y,to_x,to_y,p);
		}
	}

	if(total_result!=0)
		result=total_result;

	return result;		
}

int move_men(piece board[][8],int *from_x,int *from_y,int to_x,int to_y,piece p)
{
	int result=-2,
		  x=0,y=0; /* difference between from's and to's */

	piece enemy1,enemy2; /* defining enemy objects which can't more than two for one object */

	x=to_x-*from_x;
	y=to_y-*from_y;


	if(p==white_man){
		enemy1=black_man; 
		enemy2=black_king;
		if(x>0) /* no move allowed for white_man to go down */
			return result;
	}
	else if(p==black_man){
		enemy1=white_man; 
		enemy2=white_king;
		if(x<0)	/* no move allowed for black_man to go up */
			return result;
	}

	if(x!=0 && y!=0)/* check whether it is trying to move both vertically and horizontally*/
		return result;

	if((x==1 || x==-1) || (y==1 || y==-1)){
		if(board[to_x][to_y]==empty){ /* moveable only it's empty */
				board[to_x][to_y]=p;
				board[*from_x][*from_y]=empty; 
				result=0; /* actual move and succes flag */
		}
	}
	else if((x==2 || x==-2) || (y==2 || y==-2)){ /* jump move for men's, which is max 2 */

		/* checking if there is an enemy between target place and current place, if not then no jumping allowed*/
		if(board[*from_x+(x/2)][*from_y+(y/2)]==enemy1 || board[*from_x+(x/2)][*from_y+(y/2)]==enemy2){ 
			if(board[to_x][to_y]==empty){
					board[to_x][to_y]=p;
					board[*from_x][*from_y]=empty;
					board[*from_x+(x/2)][*from_y+(y/2)]=empty; /* enemy removed from table */ 
					result=1; /* succes flag for capturing one enemy*/
				} 
		}
	}

	/* updating the from's for the next move for autoplay mode */
	if(result!=-2){
		*from_x=to_x;
		*from_y=to_y;

		if(to_x==7 || to_x==0){ /* after every move, turning the men into a king if the men is convenient for to become king*/
			if(p==white_man)
				board[to_x][to_y]=white_king;
		
			else if(p==black_man)
				board[to_x][to_y]=black_king;
		}
	}

	return result;

}		


int move_king(piece board[][8],int *from_x,int *from_y,int to_x,int to_y,piece p)
{
	int result=-2,
		 x,y,updt_x,updt_y, /* enhancers and enhancers of that enhancers */	
		capture=0,captured_x=0,captured_y=0; /* keeping datas of captured */
	int i=0,j=0,piece_counter=0; /* counter */

	piece enemy1,enemy2;

	if(to_x>*from_x){
		x=to_x-*from_x;
		updt_x=1;
	}else {
		x=*from_x-to_x;
		if(*from_x==to_x)updt_x=0;
		else updt_x=-1;
	}

	if(to_y>*from_y){
		y=to_y-*from_y;
		updt_y=1;
	}else{
		y=*from_y-to_y;
		if(*from_y==to_y) updt_y=0;
		else updt_y=-1;
	}

	if(p==white_king){
		enemy1=black_man; 
		enemy2=black_king;
	}
	else if(p==black_king){
		enemy1=white_man; 
		enemy2=white_king;
	}

	if(x!=0 && y!=0) /* if both differences are not zero then this means user is trying to move crosswise*/ 
		return result;

	/* deciding on counter due to axis that choosed to move on */  
	if(x==0) j=y; 
	else j=x;

	/* initializing our enhancers */
	x=0; 
	y=0;

	/* check the target place is empty */
	if(board[to_x][to_y]==empty){
		/* check every place between the target place and current place */
		for(i=0;i<j;i++){
			x+=updt_x;
			y+=updt_y;
			if(board[*from_x+x][*from_y+y]==empty){
				result = 0; /*checking every square, if all of them are empty then this move is allowed*/
			}		
			else if(piece_counter==0){
				piece_counter++; 
				if(board[*from_x+x][*from_y+y]==enemy1 || board[*from_x+x][*from_y+y]==enemy2){
					capture = 1; /* enemy captured situation */
					captured_x=*from_x+x;
					captured_y=*from_y+y;
					piece_counter++;
				}
				else{ /* if an ally appears in that square then no jumping allowed */ 
					result =-2;
					return result;
				}
			}
			else{
				result = -2;
				return result;
			}
			
		}

		/* no problem for each square */ 
		if(result!=-2){
			board[to_x][to_y]=p;
			board[*from_x][*from_y]=empty;
			*from_x=to_x;
			*from_y=to_y;
			if(capture==1){
				result = capture;
				board[captured_x][captured_y]=empty;
			}

		}
		else if(result==1){

			board[*from_x+x][*from_y+y]=empty; /* enemy removed from table */
			
			*from_y=to_y;
		}

	}

	return result;
}


int auto_move(piece board[][8], int from_x, int from_y, int *to_x, int *to_y, piece p)
{
	int result = -2;
	int x=*to_x,y=*to_y; /* protecting first values */

	int men_mov[4][2]={{0,2},{2,0},{0,-2},{-2,0}}; /* (x,y) possible men moves to capture */
	int king_mov[4][2]={{1,0},{-1,0},{0,-1},{0,1}}; /* (x,y) starting points king moves to capture */


	/* mens auto move */
	if(p==white_man || p==black_man){
		/* checking around for whether an enemy to be captured exists, if there exists then capture any of them */ 
		for(int i=0;i<4;i++){
			*to_x+=men_mov[i][0];
			*to_y+=men_mov[i][1];

			if((*to_x<0 || *to_x>7 ) || (*to_y<0 || *to_y>7)){
				*to_x=x;
				*to_y=y;
				continue;
			}

			result=check_move(board,from_x,from_y,*to_x,*to_y,p);
			if(result==1){
				return result;
			}
			*to_x=x;
			*to_y=y;
		}
	}

	/* kings auto move */
	else if(p==white_king || p==black_king){

		/* again the same, capture if you can */
		for(int i=0;i<4;i++){
			
			for(int j=1;;j++){
				*to_x+=king_mov[i][0]*j;
				*to_y+=king_mov[i][1]*j;

				if((*to_x<0 || *to_x>7 ) || (*to_y<0 || *to_y>7))
					break; /* terminating the loop if x or y is out of boundaries */

				result = check_move(board,from_x,from_y,*to_x,*to_y,p);
				if(result==1)
					return result;
				*to_x=x;
				*to_y=y;		

			}

			*to_x=x;
			*to_y=y;			
		}


	}



	return result;
}

int check_move(const piece board[][8], int from_x, int from_y, int to_x, int to_y, piece p)
{
	int result = -2;

	piece temp_board[8][8];



	/* creating temporary board to see the result of that move without changing real array itself*/
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++)
			temp_board[i][j]=board[i][j];
	}


	/* men */
	if(p==white_man || p==black_man)
		result=move_men(temp_board,&from_x,&from_y,to_x,to_y,p);
	
	/* king */
	else if(p==white_king || p==black_king)
		result=move_king(temp_board,&from_x,&from_y,to_x,to_y,p);


	return result;
}


int check_end_of_game(piece board[][8])
{
	int result = -1;
	int white_piece=0,black_piece=0;

	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			if(board[i][j]==white_king || board[i][j]==white_man)
				white_piece++;
			else if(board[i][j]==black_king || board[i][j]==black_man)
				black_piece++;
		}
	}

	if(white_piece==0){
		printf("\nPlayer 2 has won the game!");
		result = black;
	}
	else if(black_piece==0){
		printf("\nPlayer 1 has won the game");
		result = white;
	}

	return result;
}

void sample_game_1(void)
{
	piece game_board[8][8];
	player player1=white;
	player player2=black;
	player p;

	/* x and y coordinats of positions of this senario */
	int blacks[16][2]={
		{1,1},{1,2},{1,4},{1,6},{2,0},{2,2},{2,3},{2,4},{2,5},{2,7},{3,0},{3,1},{3,2},{3,5},{3,6},{3,7}
	};

	int whites[16][2]={
		{4,0},{4,2},{4,3},{4,4},{4,5},{4,7},{5,0},{5,1},{5,2},{5,3},{5,5},{5,6},{5,7},{6,2},{6,3},{6,6}
	};

	/* fromx,fromy,tox,toy; moves of players; for ex. player1,player2,player1..  */
	int moves[21][4]={
		{5,1,4,1},{3,1,5,1},{5,3,5,4},{5,1,5,3},{4,7,4,6},{3,2,5,2},{4,6,2,6},{7,3,3,3},{5,7,4,7},{3,7,5,7},
		{5,0,5,1},{3,0,5,0},{5,4,5,3},{3,3,6,3},{5,5,5,4},{3,5,5,5},{0,6,0,1},{5,7,5,5},{0,1,7,1},{6,7,6,4}
	};


	/* initializing the board for this senario */
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
				game_board[i][j]=empty;
		}
	}
	for(int i=0;i<16;i++){
		game_board[blacks[i][0]][blacks[i][1]]=black_man;
		game_board[whites[i][0]][whites[i][1]]=white_man;
	}

	display_board(game_board);
	printf("\nGame is Starting...");

	/* player1 versus player2 game loop */


	/* for the purpose of this game's senario, only 19 moves will be taken into consideration */
	p=player1;
	for(int i=0;i<20;i++){
		printf("\nPlayer %d plays his move...",p/10);
		move(game_board,moves[i][0],moves[i][1],moves[i][2],moves[i][3],p);
		display_board(game_board);
		check_end_of_game(game_board);

		if(p==player1) /* changing players */
			p=player2;
		else
			p=player1;

	}




}

void sample_game_2(void)
{
	piece game_board[8][8];
	player player1=white;
	player player2=black;
	player p;

	int blacks[16][2]={
		{1,2},{1,3},{1,4},{1,5},{2,1},{2,2},{2,3},{2,4},{2,6},{2,7},{3,0},{3,1},{3,2},{3,5},{3,7},{4,5}
	};

	int whites[16][2]={
		{4,2},{4,3},{4,4},{4,6},{4,7},{5,0},{5,1},{5,2},{5,3},{5,4},{5,6},{5,7},{6,2},{6,3},{6,4},{6,5}
	};

	int moves[13][4]={
		{5,1,4,1},{3,1,5,1},{4,3,3,3},{4,5,4,3},{3,3,3,1},{1,2,1,0},{5,3,4,3},{5,1,5,3},{4,3,3,3},
		{2,3,4,3},{5,6,5,5},{7,5,4,5},{4,6,4,4}
	};


	/* initializing the board for this senario */
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
				game_board[i][j]=empty;
		}
	}


	for(int i=0;i<16;i++){
		game_board[blacks[i][0]][blacks[i][1]]=black_man;
		game_board[whites[i][0]][whites[i][1]]=white_man;
	}

	game_board[5][7]=white_man;

	display_board(game_board);
	printf("\nGame is Starting...");

	/* player1 versus player2 game loop */


	/* for the purpose of this game's senario, only 13 moves will be taken into consideration */
	p=player1;
	for(int i=0;i<13;i++){
		printf("\nPlayer %d plays his move...",p/10);
		move(game_board,moves[i][0],moves[i][1],moves[i][2],moves[i][3],p);
		display_board(game_board);

		if(p==player1) /* changing players */
			p=player2;
		else
			p=player1;

	}
	
	

}