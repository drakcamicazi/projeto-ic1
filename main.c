#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_LINHAS 1000
#define TOTAL_CHARS 100000

struct filme{
	char title[100];
	char rating[6];
	char ratingLevel[100];
	int ratingDescription;
	int releaseYear;
	int urScore;
	int urSize;
};

struct structAtributo{
	int aFilme, aTipo;
	char aDesc[100];
};

typedef struct filme Filme;
typedef struct structAtributo Atributo;

//TODO PELO MENOS MAIS UMA FUNÇÃO

//útil para apagar o \n do arquivo pré-processado
void apagarUltimoChar(char *c){
	int tamanho = strlen(c); //armazena tamanho da string
	c[tamanho - 1] = '\0'; //Seta o penúltimo caractere como fim
	return;
}

//função para verificar se abriu os arquivos
void verificarAbertura(FILE *f1, FILE *f2){
	if(f1 == NULL || f2 == NULL){
		printf("Erro na abertura de algum arquivo.");
		exit(0);
	}
}

int main(){
	FILE *netflix, *processado;
	Filme filmes[MAX_LINHAS];
	Atributo a[7 * MAX_LINHAS];
	char linha[255], *token, netflixStr[TOTAL_CHARS], c;
	int i = 0, j, primeiro = 1, atributo = 1, idFilme = 0, linhai = 2, tamanhoNetflixStr;
	int l=0, lFilme=0, lTipo=0, pontovirgula = -1, itoken, cont = 0;
	char lDesc[100]="";

	//------------TAREFA 0: PRÉ-PROCESSAMENTO DO ARQUIVO NETFLIX_ALL.CSV---------------
	processado = fopen("netflix_preproc.txt", "w");
	netflix = fopen("netflix_all.csv", "r");

	verificarAbertura(netflix, processado);

	//lê o arquivo inteiro e armazena na string netflixStr
	tamanhoNetflixStr = fread(&netflixStr, sizeof(*netflixStr), TOTAL_CHARS, netflix);

	for (i=0; i<TOTAL_CHARS; i++){ //FOR PARA TRATAR CAMPOS VAZIOS DENOTADOS POR ;;
		if(netflixStr[i] == ';' && netflixStr[i+1] == ';'){
			/* empurra string para o final do vetor de caracteres */
			for(j=TOTAL_CHARS-1; j>i+1; j--){
				netflixStr[j] = netflixStr[j-2];
			}
			cont=cont+2;
			netflixStr[i+1] = 'N';/* insere o caractere N no vetor de caracteres */
			netflixStr[i+2] = 'A';/* insere o caractere A no vetor de caracteres */
		}
	}
	tamanhoNetflixStr += cont; //atualiza a variável do tamanho da netflixStr

	for(i=0; i < tamanhoNetflixStr; i++){ //FOR PARA PRÉ-PROCESSAMENTO DO ARQUIVO
		c = netflixStr[i];
		if (c == ';') { //quando encontrar um separador
			//escreve a linha SE for um atributo válido
			if (idFilme != 0 && atributo != 0) fprintf(processado, "\n%i;%i;%i;", idFilme-1, atributo, linhai-8);
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

	//--------------TAREFA 1: ARMAZENAR EM REGISTROS DO TIPO FILME---------------

	processado = fopen("netflix_preproc.txt", "r");
	verificarAbertura(processado, processado);
	i=0;
	while (fgets(linha, 255, processado) != NULL){
		token = strtok(linha, ";");
		itoken = 0;
		/* walk through other tokens */
		while(token != NULL) {
			if (itoken == 0) a[i].aFilme = atoi(token);
			else
			if (itoken == 1) a[i].aTipo = atoi(token);
			else
			if (itoken == 3) {
				apagarUltimoChar(token);
				strcpy(a[i].aDesc, token);
			}
			token = strtok(NULL, ";");
			itoken++;
		}
		i++;
	}
	fclose(processado);

	for (i = 0; i < (MAX_LINHAS*7); i++){ //loop para armazenar do registro de atributo no registro de filme
		if (a[i].aTipo == 1) //char title (1)
		strcpy(filmes[a[i].aFilme].title, a[i].aDesc);
		else
		if (a[i].aTipo == 2) //char rating (2)
		strcpy(filmes[a[i].aFilme].rating, a[i].aDesc);
		else
		if (a[i].aTipo == 3) //char ratingLevel (3)
		strcpy(filmes[a[i].aFilme].ratingLevel, a[i].aDesc);
		else
		if (a[i].aTipo == 4) // int ratingDescription (4)
		filmes[a[i].aFilme].ratingDescription = atoi(a[i].aDesc);
		else
		if (a[i].aTipo == 5) //int releaseYear (5)
		filmes[a[i].aFilme].releaseYear = atoi(a[i].aDesc);
		else
		if (a[i].aTipo == 6) //int urScore (6)
		filmes[a[i].aFilme].urScore = atoi(a[i].aDesc);
		else
		if (a[i].aTipo == 7) //int urSize (7)
		filmes[a[i].aFilme].urSize = atoi(a[i].aDesc);
		else
		printf("Erro nos indices de tipo: %i\n", a[i].aTipo);
	}

	//-------printf para testar o que foi armazenado no struct filme
	// printf("title;rating;ratingLevel;ratingDescription;release year;user rating score;user rating size;\n");
	// for (i=0; i<MAX_LINHAS; i++){
	// 	printf("%s;%s;%s;%i;%i;%i;%i\n", filmes[i].title, filmes[i].rating, filmes[i].ratingLevel, filmes[i].ratingDescription, filmes[i].releaseYear, filmes[i].urScore, filmes[i].urSize);
	// }

	return 0;
}
