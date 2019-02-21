
/***************************************************************************
 * Author: Ahmed Semih Özmekik                                             *
 * This is the implementation of a maze simulation.                        *
 * There is a maze which we call forest, and there is a botanist who, 	   *
 * tries to find hidden flower in that forest, before he ran out of water. * 
 * All the moves done by botanist are randomly and smartly generated 	   *
 * by computer and informations about this simulation taken from .csv file,*
 * which you can see it's format from example init.csv file.       		   *
 ***************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define INIT_FILE "init.csv"  

#define B 'B'
#define F 'F'
#define WALL '#'
#define ROAD ' '

#define TRUE 1
#define EMPTY 0


typedef struct{
	char **map;
	int	width,height,
		flower_x,flower_y;
}Forest;

typedef struct{
	int coord_x,coord_y,
		water_bottle_size;
}Botanist;

void init_game (Forest *forest, Botanist *botanist);
void print_map (Forest forest);
void search(Forest *f,Botanist *b,int *found,int *old_dir);
int is_valid(Forest f,Botanist b,int moves[][2],int new_dir,int old_dir); /* checks whether the move is valid */
int is_sided(Forest f,Botanist b,int moves[][2]); /* checks if the botanist has only one place to go */ 

int main()
{
	Forest forest;
	Botanist botanist;
	int found=0,dir=0; /* initialized vars for recursive search func */

	init_game(&forest,&botanist);

	srand(time(NULL));

	search(&forest,&botanist,&found,&dir);




	return 0;

}

void init_game (Forest *forest, Botanist *botanist)
{
	FILE *fp;
	char **map,c; 

	fp=fopen(INIT_FILE,"r"); 


	fscanf(fp,"%d",&(*botanist).water_bottle_size);
	fscanf(fp,"%d,%d",&(*forest).height,&(*forest).width);

	/* memory allocation for map */ 
	map = calloc((*forest).height, sizeof(char*));
	for(int i=0;i<(*forest).height;i++)
		map[i] = (char *)calloc((*forest).width, sizeof(char));

	for(int i=0;i<(*forest).height;i++){
		for(int j=0;j<(*forest).width;j++){
			if((c=(char)fgetc(fp))!= EOF){
				switch(c){
					case B:		(*botanist).coord_x=i; (*botanist).coord_y=j;
									break; 
					case F:		(*forest).flower_x=i;	(*forest).flower_y=j;
									break;
					case WALL:  	
					case ROAD:		break;
					default: j--;   continue; /* any other chars unwanted */	 
				}
				map[i][j]=c;
			}
		}
	}	

	(*forest).map=map; /* making the real map pointer, point the prepared memory */

	fclose(fp);


}

void print_map(Forest forest)
{
	for(int i=0;i<forest.height;i++){
		for(int j=0;j<forest.width-1;j++)	printf("%c,",forest.map[i][j]);
		printf("%c\n",forest.map[i][forest.width-1]); /* prevent print comma at end of the line */ 
	}

}

void search(Forest *f,Botanist *b,int *found,int *old_dir)
{
	int moves[4][2]={{1,0},{0,1},{-1,0},{0,-1}}, /* available moves(x,y) */
		dir=0; /* direction, could be 0,1,2,3 */

	if(*found==TRUE){
		print_map(*f);
		printf("\nI have found it on (%d,%d)",(*b).coord_x,(*b).coord_y);
	}
	
	else if((*b).water_bottle_size==EMPTY){
		(*f).map[(*b).coord_x][(*b).coord_y]=B;
		print_map(*f);
		printf("\nHelp! I am on (%d,%d)",(*b).coord_x,(*b).coord_y);
	}

	else{
		do dir=rand()%4; /* randomly deciding where to go */
		while(!is_valid(*f,*b,moves,dir,*old_dir)); /* if move is valid, then move */

		(*f).map[(*b).coord_x][(*b).coord_y]=ROAD; /* cleans old place */
		(*b).coord_x+=moves[dir][0];
		(*b).coord_y+=moves[dir][1];
		(*b).water_bottle_size--; /* 1 ml/step */
		if(((*b).coord_x==(*f).flower_x) && ((*b).coord_y==(*f).flower_y))  
			*found=TRUE;
	
		search(f,b,found,&dir);
	}


}

/* checks if the move is 1: out of boundaries 			    *
 *						 2: meaningless    					*
 *						 3: doable due to the rules of game */

int is_valid(Forest f,Botanist b,int moves[][2],int new_dir,int old_dir)
{
	int x=b.coord_x+moves[new_dir][0],
		y=b.coord_y+moves[new_dir][1],
		valid=!TRUE;

	if(x>=f.height || y>=f.width || x<0 || y<0) /* 1 */
		return valid;

	/* prevent that the botanist to go where he just came from.               	 	 *
	 * so that unnecessary moves are not made. And of course if the botanist, 		 *
	 * can not go to another place from there, then the moves have to be played 	 *
	 * +2 or -2 means, distance between indices of moves which neutralize each other */ 
	if(new_dir+2==old_dir || new_dir-2==old_dir){ /* 2 */
		if(!is_sided(f,b,moves)) /* if the botanist not surrounded by walls */
			return valid;
	} 

	switch(f.map[x][y]){ /* 3 */
		case WALL: break; /* not valid if there is wall */
		default  : valid=TRUE; 
	}

	return valid;
}

int is_sided(Forest f,Botanist b,int moves[][2])
{
	int x,y,
		sides=0,
		only=!TRUE;

	for(int i=0;i<4;i++){ /* checking if the botanist surrounded by walls */
		x=b.coord_x+moves[i][0];
		y=b.coord_y+moves[i][1];
		if(x>=f.height || y>=f.width || x<0 || y<0){
			sides++; /* out of boundaries */
			continue;
		}
		if(f.map[x][y]==WALL) sides++;
	}

	if(sides==3) /* there are 3 place he can't go which means he is surrounded */
		only=TRUE;

	return only;
}
