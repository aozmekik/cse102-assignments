#include <stdio.h>

#define OPEN_MSG "open_msg.txt"
#define SECRET_MSG "secret_msg.txt"
#define MAX_CHAR 1024


void menu(void);
void encrypt_open_msg(void);
void decrypt_secret_msg(void);
int find_size_of_line(char line[]);
void reverse_line(char line[], int line_lenght);

int main()
{
	menu();

	return 0;
}

void menu(void)
{	
	int choice;

	do
	{
		printf("\n1. Encrypt\n2. Decrypt\n0. Exit\nChoice> ");
		scanf("%d",&choice);

		if(choice>0 || choice<3)
			switch(choice){
			case 0: break;
			case 1: encrypt_open_msg(); 	break;
			case 2: decrypt_secret_msg();	break;
			}

	}while(choice!=0);

}

void encrypt_open_msg(void)
{
	char msg[MAX_CHAR];
	FILE *fp_r,*fp_w; /* read and write pointers */

	int line_lenght=0,key=0;

	fp_r = fopen(OPEN_MSG,"r"); /* open_msg file with 'read' mode */
	fp_w = fopen(SECRET_MSG,"w"); fclose(fp_w); /* deleting contents of secret_msg file */
	fp_w = fopen(SECRET_MSG,"a"); /*  'append mode' for adding encrypted text to secret_msg file*/

	printf("Key> "); scanf("%d",&key);

	if(fp_r){
		while(fgets(msg,MAX_CHAR,fp_r)!=NULL){
					/* encryption */
			line_lenght=find_size_of_line(msg);

			if(msg[line_lenght-1]==10){ /* if there is the new line at the end, we delete it and update line length */
				 msg[line_lenght-1]=0;
				 line_lenght--;
			}

			reverse_line(msg,line_lenght);

			for(int i=0;i<line_lenght;i++){
				if(msg[i]=='.')			msg[i]='*';
				else if(msg[i]==' ')	msg[i]='_';
				else if(msg[i]-key<'a')	msg[i]='z'-(key-(msg[i]-'a'))+1;
				else 					msg[i]=msg[i]-key;
			}

			printf("\n%s",msg);

			if(fp_w){
				fputs(msg,fp_w); fputs("\n",fp_w);
			}
			else
				printf("\nError occured when opening the 'secret message' file!...");

		}	
	}
	else 
		printf("\nError occured when opening the 'open message' file!...");

	fclose(fp_r);
	fclose(fp_w);
	
}


void decrypt_secret_msg(void)
{
	char msg[MAX_CHAR];
	FILE *fp_r,*fp_w;

	int line_lenght=0,key=0;

	fp_r=fopen(SECRET_MSG,"r");
	fp_w = fopen(OPEN_MSG,"w"); fclose(fp_w);
	fp_w = fopen(OPEN_MSG,"a"); 

	printf("Key> "); scanf("%d",&key);

	if(fp_r){
		while(fgets(msg,MAX_CHAR,fp_r)!=NULL){
					/* decryption */
			line_lenght=find_size_of_line(msg);

			if(msg[line_lenght-1]==10){ 
				msg[line_lenght-1]=0;
				line_lenght--;
			}

			for(int i=0;i<line_lenght;i++){
				if(msg[i]=='*')			msg[i]='.';
				else if(msg[i]=='_')	msg[i]=' ';
				else if(msg[i]+key>'z')	msg[i]='a'+(key-('z'-msg[i]))-1;
				else 					msg[i]=msg[i]+key;
			}

			reverse_line(msg,line_lenght);

			printf("\n%s",msg);

			if(fp_w){
				fputs(msg,fp_w); fputs("\n",fp_w);
			}
			else
				printf("\nError occured when opening the 'open message' file!...");
		}
					
	}
	else 
		printf("\nError occured when opening the 'secret message' file!...");

	fclose(fp_r);
	fclose(fp_w);
}


void reverse_line(char line[MAX_CHAR],int line_lenght)
{
	char temp_line[MAX_CHAR];

	for(int i=0;i<line_lenght;i++) /* reversing */
		temp_line[line_lenght-1-i]=line[i];

	for(int i=0;i<line_lenght;i++) /* copying */
		line[i]=temp_line[i];


}

int find_size_of_line(char line[MAX_CHAR])
{
	int size=0;

	int i=0;
	while(line[i]!='\0'){ /* before it reaches end of string, counts char number */
		size++; 
		i++;
	}

	return size;
}