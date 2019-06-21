//Alunos:
//Milan Rufini de Andrade,   nº USP 11273868
//Thalles Raphael Guimarães, nº USP 11320297
#include <stdio.h>
#include <string.h>
#define MAX_LINHAS 29
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

struct structAtributo{
	int aFilme, aTipo;
	char aDesc[100];
};

typedef struct filme Filme;
typedef struct structAtributo Atributo;

//void armazenaAtributo(int aFilme, int aTipo, char[100] aDesc){}

int main(){
	FILE *netflix, *processado;
	Filme filmes[MAX_LINHAS];
	Atributo a[203]; //203 é 29 * 7  (num de filmes * num de atributos por filme)
	char linha[255], desc[100][203], *token, netflixStr[TOTAL_CHARS], c;
	int i = 0, primeiro = 1, atributo = 1, idFilme = 0, linhai = 2;
	int tamanhoNetflixStr;

	processado = fopen("netflix_preproc.txt", "w");
	netflix = fopen("netflix_30.csv", "r");

	//lê o arquivo inteiro e armazena na string netflixStr

	tamanhoNetflixStr = fread(&netflixStr, sizeof(*netflixStr), TOTAL_CHARS, netflix);

	for(i=0; i < tamanhoNetflixStr; i++){ //FOR PARA PRÉ-PROCESSAMENTO DO ARQUIVO
		c = netflixStr[i];

		if (c == ';') { //quando encontrar um separador
			if (idFilme != 0) fprintf(processado, "\n%i;%i;%i;", idFilme-1, atributo, linhai-8);
			if (atributo == 0){
				atributo = 1;
				idFilme = idFilme + 1;
				if (idFilme > MAX_LINHAS) {
					break; //break o for quando atinge o máximo de filmes
				}
			}
			linhai++;
		}
		else
		if (c == '\n') { //quando pula linha e o idFilme tá dentro do limite
			if (idFilme != 0)
				if (linhai != 9) fprintf(processado, "\n%i;%i;%i;", idFilme-1, atributo, linhai-8);
				else fprintf(processado, "%i;%i;%i;", idFilme-1, atributo, linhai-8);

			linhai++;
		}
		else { //quando encontrar qualquer outro caractere
			if (idFilme != 0) fprintf(processado, "%c", c);
		}

		atributo = linhai % 8;

	}

	fclose(netflix);

	fclose(processado);

	return 0;

}
