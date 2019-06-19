//Alunos:
//Milan Rufini de Andrade,   nº USP 11273868
//Thalles Raphael Guimarães, nº USP 11320297
#include <stdio.h>
#include <string.h>
#define MAX_LINHAS 9

struct filme{
	char title[100];
	char rating[6];
	char ratingLevel[100];
	int ratingDescription;
	char releaseYear[5];
	int urScore;
	int urSize;
};

typedef struct filme Filme;

void armazena(Filme f, int id, char[100] texto){
	if (id == 1) f.title = texto;
	else
		if (id == 2) f.rating = texto;
}

int main(){
	FILE *netflix;
	Filme filmes[MAX_LINHAS];
	char linha[255], *token;
	int i, j = 0, primeiro = 1;

	netflix = fopen("netflix_10.csv", "r");
	
	i=1;
	while (fgets(linha, 255, netflix) != NULL){
		
		//printf("%s\n", linha); /* printa cada linha */

		if (primeiro == 0){ //para não ler a primeira linha!
			/* get the first token */
		   	token = strtok(linha, ";");
		   
			   /* walk through other tokens */
			   while( token != NULL ) {
				
			      printf( "%i.%i- %s\n", j, i%8, token ); //printa cada bloquinho de info
			    
				
			      token = strtok(NULL, ";");
				i++;
				if (i%8 == 0) j++;
			   }
		}
		primeiro = 0;
		
	
	 }

      fclose(netflix);

      return 0;

}

