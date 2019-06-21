//Alunos:
//Milan Rufini de Andrade,   nº USP 11273868
//Thalles Raphael Guimarães, nº USP 11320297
#include <stdio.h>
#include <string.h>
#define MAX_LINHAS 29
#define TOTAL_CHARS 100000

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
	char aFilme[5], aTipo[2]; //MUDAR PARA INT
	char aDesc[100];
};

typedef struct filme Filme;
typedef struct structAtributo Atributo;

int main(){
	FILE *netflix, *processado;
	Filme filmes[MAX_LINHAS];
	Atributo a[7 * MAX_LINHAS];
	char linha[255], *token, netflixStr[TOTAL_CHARS], c;
	int i = 0, primeiro = 1, atributo = 1, idFilme = 0, linhai = 2, tamanhoNetflixStr;
	int l=0, lFilme=0, lTipo=0, pontovirgula = -1, itoken;
	char lDesc[100]="";
	//------------PARTE 0: PRÉ-PROCESSAMENTO DO ARQUIVO NETFLIX_ALL.CSV---------------
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

	//--------------PARTE 1: ARMAZENAR EM REGISTROS DO TIPO FILME---------------

	processado = fopen("netflix_preproc.txt", "r");

	// while ((fscanf(processado, "%[^\n]", &linha )) != EOF) {
	// 	puts(linha); //POR QUE VC CAI EM UM LOOP INFINITO???----------------------------
	//
	// }
	// while ((c = fgetc(processado)) != EOF) {
	// 	printf("%c", c);
	// 	if (c == ';')	pontovirgula++;
	// 	else pontovirgula = -1;
	// }
	//
	i=0;
	while (fgets(linha, 255, processado) != NULL){
		token = strtok(linha, ";");
		itoken = 0;
		strcpy(a[i].aFilme, "0");
		strcpy(a[i].aTipo, "0");
		strcpy(a[i].aDesc, "NA");
		/* walk through other tokens */
		while( itoken <= 3 ) {

			if (itoken == 0 && token != NULL) strcpy(a[i].aFilme, token);
			else
			if (itoken == 1 && token != NULL) strcpy(a[i].aTipo, token);
			else
			if (itoken == 3 && token != NULL) strcpy(a[i].aDesc, token);
			else
			printf("Linha %s lida.\n", token);
			token = strtok(NULL, ";");
			itoken++;
		}
		i++;
	}
	fclose(processado);

	printf("---------------------\n");

	for (i = 0; i < (MAX_LINHAS*8); i++){
		printf("Filme %s, tipo %s, desc: %s\n", a[i].aFilme, a[i].aTipo, a[i].aDesc);
	}

	return 0;
}
