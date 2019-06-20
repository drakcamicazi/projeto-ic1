//Alunos:
//Milan Rufini de Andrade,   nº USP 11273868
//Thalles Raphael Guimarães, nº USP 11320297
#include <stdio.h>
#include <string.h>
#define MAX_LINHAS 9
#define TOTAL_CHARS 90900

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

int main(){
	FILE *netflix;
	Filme filmes[MAX_LINHAS];
	char linha[255], *token, netflixStr[TOTAL_CHARS];
	int i = 1, primeiro = 1, atributo = 0, idFilme = 0;

	netflix = fopen("netflix_10.csv", "r");

	while (fgets(linha, 255, netflix) != NULL){

		//printf("%s\n", linha); /* printa cada linha */

		if (primeiro == 0){ //para não ler a primeira linha!
			/* get the first token */
			token = strtok(linha, ";");

			/* walk through other tokens */
			while( token != NULL ) {
				atributo = i%8;

				printf( "%i.%i- %s\n", idFilme, atributo, token); //printa cada bloquinho de info com o id do filme e qual é o atributo

				token = strtok(NULL, ";");

				i++;
				if (atributo == 0) idFilme++; //se chegar ao atributo 0 (fim do registro do filme), mudar o id do filme pro próximo
			}
		}
		primeiro = 0;

	}

	fclose(netflix);

	return 0;

}

