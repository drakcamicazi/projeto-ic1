//Alunos:
//Milan Rufini de Andrade,   nº USP 11273868
//Thalles Raphael Guimarães, nº USP 11320297
#include <stdio.h>
#include <string.h>
#define MAX_LINHAS 30
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

//void armazena(Filme f, int id, char texto){
//	if (id == 1) f.title = texto;
//	else
//		if (id == 2) f.rating = texto;
//}

int main(){
	FILE *netflix;
	Filme filmes[MAX_LINHAS];
	char linha[255], *token, netflixStr[TOTAL_CHARS], c;
	int i = 0, primeiro = 1, atributo = 0, idFilme = 0;
	int tamanhoNetflixStr;

	netflix = fopen("netflix_30.csv", "r");

	 //lê o arquivo inteiro e armazena na string netflixStr

    tamanhoNetflixStr = fread(&netflixStr, sizeof(*netflixStr), TOTAL_CHARS, netflix);

	for(i=0; i < tamanhoNetflixStr; i++){
        c = netflixStr[i];
				if ( c == ';') printf("\n");
				else
					if (c == '\n') printf("Fim de filme\n");
						else printf("%c", c);
	}

	fclose(netflix);

	return 0;

}
