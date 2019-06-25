#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_LINHAS 1000 //1000
#define TOTAL_CHARS 100000

struct filme{
	char title[100];
	char rating[9];
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
	FILE *netflix, *processado, *ex2;
	Filme filmes[MAX_LINHAS];
	Atributo a[7 * MAX_LINHAS];
	char linha[255], *token, netflixStr[TOTAL_CHARS], c;
	int i = 0, j, primeiro = 1, atributo = 1, idFilme = 0, linhai = 2, tamanhoNetflixStr;
	int l=0, lFilme=0, lTipo=0, pontovirgula = -1, itoken, cont = 0;
	char lDesc[100]="";
	int mRatings[80][14] = {{ 0 }}, maiorAno, menorAno, qtdAnos, filmesPorAno[80] = {0};

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
	// printf("%i\n", filmes[MAX_LINHAS-1].urSize);
	//TODO: RESOLVER O BUG DO urSize


	//-------------------TAREFA 2: ELABORE ANO A ANO A TOTALIZAÇÃO DE VÍDEOS P/ CADA UM DOS RATING-----------------------------

	//passo 1, encontrar maior e menor ano de lançamento
	maiorAno = filmes[0].releaseYear;
	menorAno = filmes[0].releaseYear;
	for (i = 0; i < MAX_LINHAS; i++){
		if (filmes[i].releaseYear > maiorAno) maiorAno = filmes[i].releaseYear;
		if (filmes[i].releaseYear < menorAno) menorAno = filmes[i].releaseYear;
	}
	qtdAnos = maiorAno - menorAno;

	//passo 2, popula a primeira coluna da matriz com os anos
	for(i=0; i <= qtdAnos; i++){
		mRatings[i][0] = maiorAno - i;
	}

	for (i = 0; i < MAX_LINHAS; i++){ // passo 3, FOR PARA ATRIBUIR AS QUANTIDADES DE RATINGS NA MATRIZ
		if (strcmp(filmes[i].rating, "G") == 0) mRatings[maiorAno - filmes[i].releaseYear][1]++; // ta imprimindo 9 na coluna G sendo q deveria talvez ser 8????
		else
		if (strcmp(filmes[i].rating, "PG") == 0) mRatings[maiorAno - filmes[i].releaseYear][2]++;
		else
		if (strcmp(filmes[i].rating, "PG-13") == 0) mRatings[maiorAno - filmes[i].releaseYear][3]++;
		else
		if (strcmp(filmes[i].rating, "R") == 0) mRatings[maiorAno - filmes[i].releaseYear][4]++;
		else
		if (strcmp(filmes[i].rating, "NR") == 0) mRatings[maiorAno - filmes[i].releaseYear][5]++;
		else
		if (strcmp(filmes[i].rating, "UR") == 0) mRatings[maiorAno - filmes[i].releaseYear][6]++;
		else
		if (strcmp(filmes[i].rating, "TV-G") == 0) mRatings[maiorAno - filmes[i].releaseYear][7]++;
		else
		if (strcmp(filmes[i].rating, "TV-PG") == 0) mRatings[maiorAno - filmes[i].releaseYear][8]++;
		else
		if (strcmp(filmes[i].rating, "TV-14") == 0) mRatings[maiorAno - filmes[i].releaseYear][9]++;
		else
		if (strcmp(filmes[i].rating, "TV-MA") == 0) mRatings[maiorAno - filmes[i].releaseYear][10]++;
		else
		if (strcmp(filmes[i].rating, "TV-Y") == 0) mRatings[maiorAno - filmes[i].releaseYear][11]++;
		else
		if (strcmp(filmes[i].rating, "TV-Y7") == 0) mRatings[maiorAno - filmes[i].releaseYear][12]++;
		else
		if (strcmp(filmes[i].rating, "TV-Y7-FV") == 0) mRatings[maiorAno - filmes[i].releaseYear][13]++;
		else
		printf("Rating %i: %s fora do padrão.\n", i, filmes[i].rating);
	}

	//passo 4, escreve no arquivo a matriz de ratings por ano
	ex2 = fopen("totalizacao_ratings.csv", "w");
	fprintf(ex2, "Ano; G; PG; PG-13; R; NR; UR; TV-G; TV-PG; TV-14; TV-MA; TV-Y; TV-Y7; TV-Y7-FV;\n");
	for(i=0; i<=qtdAnos; i++){
		for(j=0; j<14; j++){
			fprintf(ex2, "%4i; ", mRatings[i][j]);
		}
		fprintf(ex2, "\n");
	}
	fclose(ex2);

	//-------------------TAREFA 3: MOSTRAR QUANTOS VÍDEOS FORAM LANÇADOS PELA NETFLIX A CADA ANO-----------------------------

	printf("ano |qtd de filmes lançados\n");
	for (i = 0; i <= qtdAnos; i++){
		cont = 0;
		for (j = 1; j <= 13 ; j++){
			cont = cont+ mRatings[i][j];
		}
		if (cont != 0) printf("%4i| %3i \n", maiorAno-i, cont);
	}



	return 0;
}
