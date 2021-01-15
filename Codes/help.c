/*
 *TRABALHO 2 - DISCIPLINA ESTRUTURA DE DADOS 3

 *Authors:
 *Felipe de Oliveira 10284970
 *Bruner Eduardo Augusto Albrecht 9435846

 *Novembro, 2020
 */

#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "arq.h"
/***************************************_ASSINATURAS_*************************************************/
void binarioNaTela1(char *nomeArquivoBinario, char *nomeArquivoIndice); /* Correção do arquivo binário. */
void binarioNaTela2(char *nomeArquivoBinario);
void trim(char *str); /* Pode ser útil pra você (extra). */
void scan_quote_string(char *str); /* Use para ler strings entre aspas. */
char *spliter(char * buffer, int position, int special);
void tratamentoString(char *campo, int size);

/*************************************_FUNCIONALIDADES_**********************************************/
void binarioNaTela1(char *nomeArquivoBinario, char *nomeArquivoIndice) {

    /* Use essa função para comparação no run.codes. Lembre-se de ter fechado (fclose) o arquivo anteriormente.
     *  Ela vai abrir de novo para leitura e depois fechar (você não vai perder pontos por isso se usar ela). */

    unsigned long i, cs;
    unsigned char *mb;
    FILE *fs, *fi;
    size_t fl;
    if (nomeArquivoBinario == NULL || !(fs = fopen(nomeArquivoBinario, "rb"))) {
        fprintf(stderr, "ERRO NA FUNÇÃO BINARIO NA TELA. Não se esqueça do fclose e verifique se passou o argumento corretamente!\n");
        return;
    }
    if (nomeArquivoIndice == NULL || !(fi = fopen(nomeArquivoIndice, "rb"))) {
        fprintf(stderr, "ERRO NA FUNÇÃO BINARIO NA TELA. Não se esqueça do fclose e verifique se passou o argumento corretamente!\n");
        return;
    }
    fseek(fs, 0, SEEK_END);
    fl = ftell(fs);
    fseek(fs, 0, SEEK_SET);
    mb = (unsigned char *) malloc(fl);
    fread(mb, 1, fl, fs);
    fclose(fs);
    cs = fl;
    for (i = 0; i < fl; i++) {
        cs += (unsigned long) mb[i];
    }
    fseek(fi, 0, SEEK_END);
    fl = ftell(fi);
    fseek(fi, 0, SEEK_SET);
    mb = (unsigned char *) realloc(mb, fl);
    fread(mb, 1, fl, fi);
    fclose(fi);
    cs += fl;
    for (i = 0; i < fl; i++) {
        cs += (unsigned long) mb[i];
    }
    printf("%lf\n", (cs / (double) 100));
    free(mb);
}

void binarioNaTela2(char *nomeArquivoBinario) {

	/* Use essa função para comparação no run.codes. Lembre-se de ter fechado (fclose) o arquivo anteriormente.
	*  Ela vai abrir de novo para leitura e depois fechar (você não vai perder pontos por isso se usar ela). */

	unsigned long i, cs;
	unsigned char *mb;
	FILE *fs;
	size_t fl;
	if(nomeArquivoBinario == NULL || !(fs = fopen(nomeArquivoBinario, "rb"))) {
		fprintf(stderr, "ERRO NA FUNÇÃO BINARIO NA TELA. Não se esqueça do fclose e verifique se passou o argumento corretamente!\n");
		return;
	}
	fseek(fs, 0, SEEK_END);
	fl = ftell(fs);
	fseek(fs, 0, SEEK_SET);
	mb = (unsigned char *) malloc(fl);
	fread(mb, 1, fl, fs);
	fclose(fs);
	cs = fl;
	for(i = 0; i < fl; i++) {
		cs += (unsigned long) mb[i];
	}
	printf("%lf\n", (cs / (double) 100));
	free(mb);
}

void trim(char *str) {

    /*
     *	Essa função arruma uma string de entrada "str".
     *	Manda pra ela uma string que tem '\r' e ela retorna sem.
     *	Ela remove do início e do fim da string todo tipo de espaçamento (\r, \n, \t, espaço, ...).
     *	Por exemplo:
     *
     *	char minhaString[] = "    \t TESTE  DE STRING COM BARRA R     \t  \r\n ";
     *	trim(minhaString);
     *	printf("[%s]", minhaString); // vai imprimir "[TESTE  DE STRING COM BARRA R]"
     *
     */

    size_t len;
    char *p;

    // remove espaçamentos do fim
    for (len = strlen(str); len > 0 && isspace(str[len - 1]); len--);
    str[len] = '\0';

    // remove espaçamentos do começo
    for (p = str; *p != '\0' && isspace(*p); p++);
    len = strlen(p);

    memmove(str, p, sizeof (char) * (len + 1));
}

void scan_quote_string(char *str) {

    /*
     *	Use essa função para ler um campo string delimitado entre aspas (").
     *	Chame ela na hora que for ler tal campo. Por exemplo:
     *
     *	A entrada está da seguinte forma:
     *		nomeDoCampo "MARIA DA SILVA"
     *
     *	Para ler isso para as strings já alocadas str1 e str2 do seu programa, você faz:
     *		scanf("%s", str1); // Vai salvar nomeDoCampo em str1
     *		scan_quote_string(str2); // Vai salvar MARIA DA SILVA em str2 (sem as aspas)
     *
     */

    char R;

    while ((R = getchar()) != EOF && isspace(R)); // ignorar espaços, \r, \n...

    if (R == 'N' || R == 'n') { // campo NULO
        getchar();
        getchar();
        getchar(); // ignorar o "ULO" de NULO.
        strcpy(str, ""); // copia string vazia
    } else if (R == '\"') {
        if (scanf("%[^\"]", str) != 1) { // ler até o fechamento das aspas
            strcpy(str, "");
        }
        getchar(); // ignorar aspas fechando
    } else if (R != EOF) { // vc tá tentando ler uma string que não tá entre aspas! Fazer leitura normal %s então...
        *str = R;
        str++;
        while ((R = getchar()) != EOF && !isspace(R)) {
            *str = R;
            str++;
        }
        *str = '\0';
    } else { // EOF
        strcpy(str, "");
    }
}

char *spliter(char * buffer, int position, int special) {
    // passar o buffer, tamanho e qual vc posição vc quer
    char *str = NULL;
    // alocar o  tamanho certo 
    str = (char *) malloc(strlen(buffer) * sizeof (char));
    // necessário copiar para não perder a referência do BUFFER
    strcpy(str, buffer);
    //char* token = strtok(str, ""); 

    if (special == 1) {// separação por aspas
        char* token = strtok(str, "\"");
        //printf("str = %s, sizeof(str)= %ld and strlen(str) = %ld\n", str, sizeof(str), strlen(str));
        int aux = 0;
        while (token != NULL) {
            //printf("%s\n", token); 
            if (aux == (position - 1)) {
                break;
            }
            aux++;
            //token = strtok(NULL, " "" "); // ele retornará null caso entre com um número maior que os campos separados da string, ou igual a zero.
            token = strtok(NULL, "\"");
            //printf("Teminando o laço do while!\n");
        }

        //printf("Saindo do spliter\n");
        //free(str);
        return token;
    }
    if (special == 0) {// separação por espaços
        //printf("Entrando no special == 0!\n");
        //printf("AQUI #!\n");
        char* token = strtok(str, " ");
        int aux = 0;
        while (token != NULL) {
            //printf("%s\n", token); 
            if (aux == (position - 1)) {
                break;
            }
            aux++;
            token = strtok(NULL, " "); // ele retornará null caso entre com um número maior que os campos separados da string, ou igual a zero.
            //printf("Teminando o laço do while! aux = %d\n", aux);
        }

        //free(str);
        return token;
    }
    //return token;
}

void tratamentoString(char *campo, int size) {
    //recebe um campo (string), verfica o seu tamanho e completa com $ se o campo estiver com os espaços vazios
    int i, aux = 0;
    //condição especial para os cabeçalhos, que serão preenchidos com $ para completar os espaços vazios
    if (!(strcmp(campo, "0"))) {
        for (i = 0; i < size; i++) {
            campo[i] = '$'; // preenche todos os espaços
        }
    } else {
        //strings que precisam completar seus espaços entram neste else
        if (size == (strlen(campo) + 1)) {
            // caso a string já tenha o tamanho exato permitido pelo campo 
            //printf("Tamanho exato\n");
        }

        if (size > strlen(campo)) {
            // caso a string não tamanho exato permitido pelo campo, completaremos com o $
            aux = strlen(campo) + 1; // vamos para o primeiro espaço depois do \0
            for (i = aux; i < size; i++) {
                campo[i] = '$';
            }
            //printf("Tratamento feito\n");
        }
    }
}