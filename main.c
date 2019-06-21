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


int main(){
	FILE *netflix;
	Filme filmes[MAX_LINHAS];
	char linha[255], *token, netflixStr[TOTAL_CHARS], c;
	int i = 0, primeiro = 1, atributo = 1, idFilme = 0, linhai = 1;
	int tamanhoNetflixStr;

	netflix = fopen("netflix_30.csv", "r");

	//lê o arquivo inteiro e armazena na string netflixStr

	tamanhoNetflixStr = fread(&netflixStr, sizeof(*netflixStr), TOTAL_CHARS, netflix);
	printf("%i.%i.%i- ", idFilme, atributo, linhai);
	linhai++;
	for(i=0; i < tamanhoNetflixStr; i++){
		c = netflixStr[i];

		if (c == ';') { //quando encontrar um separador
			printf("\n%i.%i.%i- ", idFilme, atributo, linhai);
			linhai++;
		}
		else
		if (c == '\n') { //quando pula linha
			printf("---- Fim de filme\n\n%i.%i.%i- ", idFilme, atributo, linhai);
			linhai++;
		}
		else { //quando encontrar qualquer outro caractere
			printf("%c", c);
		}

		atributo = linhai % 8;
				if (atributo == 0){
					idFilme++;
					atributo = 1;
				}
	}

	fclose(netflix);

	return 0;

}
