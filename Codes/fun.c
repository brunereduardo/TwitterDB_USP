/*
 *TRABALHO 2 - DISCIPLINA ESTRUTURA DE DADOS 3

 *Authors:
 *Felipe de Oliveira 10284970
 *Bruner Eduardo Augusto Albrecht 9435846

 *Novembro, 2020
 */
#include "fun.h"
#include "ed.h"
#include "arq.h"
#include "help.h"
#include <ctype.h>
/**************************************************************ASSINATURAS****************************************/
void funcUM(char *buffer, listaPessoa *ram);
void funcDois(char *buffer);
void funcTres(char *buffer);
void funcQuatro(char *buffer, listaPessoa *ram);
//void funcCinco(char *buffer);
void funcSeis(char *buffer);
void funcSete(char *buffer, Lista_Segue_RAM *ram_segue);
//void funcOito(char *buffer);
void init();

/**************************************************************_FUNCIONALIDADES_*************************************************/

void funcUM(char *buffer, listaPessoa *ram) {
    //printf("Entrei na funcionalidade 1!\n");
    char *strUm = NULL;
    char *strDois = NULL;
    char *strTres = NULL;
    char *strQuat = NULL;

    //printf("buffer = %s, sizeof(buffer)= %ld and strlen(buffer) = %ld\n", buffer, sizeof(buffer), strlen(buffer));
    strDois = spliter(buffer, 2, 0); // arquivo.csv
    //printf("%s\n", strDois);
    strTres = spliter(buffer, 3, 0); // arquivo.bin
    //printf("%s\n", strTres);
    strQuat = spliter(buffer, 4, 0); // arquivo.index 
    //printf("%s\n", strQuat);
    //chamada da função  leituraArq
    leituraArq(strDois, strTres, strQuat, ram); //chama a função leituraArq do arq.c
    binarioNaTela1(strTres, strQuat); //chama a função binarioNaTela1 do aux.c
}

void funcDois(char *buffer) {
    //printf("Entrei na funcionalidade 2!\n");
    char *strUm = NULL;
    char *strDois = NULL;
    strUm = spliter(buffer, 1, 0); // número da funcionalidade
    //printf("%s\n", strUm);
    strDois = spliter(buffer, 2, 0); // arquivoPessoa.bin
    //printf("%s\n", strDois);
    printFile(strDois); //chama a função printFile do arq.c
}

void funcTres(char *buffer) {
    //printf("Entrei na funcionalidade 3!\n");
    char *strUm = NULL;
    char *strDois = NULL;
    char *strTres = NULL;
    char *strQuat = NULL;
    char *strCinco = NULL;
    int val;
    strUm = spliter(buffer, 1, 0); // número da funcionalidade
    //printf("%s\n", strUm);
    strDois = spliter(buffer, 2, 0); // arquivo.bin
    //printf("%s\n", strDois);
    strTres = spliter(buffer, 3, 0); // arquivo.index
    //printf("%s\n", strTres);
    strQuat = spliter(buffer, 4, 0); // campo de busca
    //printf("%s\n", strQuat);
    if ((!(strcmp(strQuat, "nomePessoa"))) || (!(strcmp(strQuat, "twitterPessoa")))) {
        strCinco = spliter(buffer, 2, 1); // valor = string entre aspas
    } else {
        strCinco = spliter(buffer, 5, 0); // valor = numérico
    }
    //printf("%s\n", strCinco);

    if (!(strcmp(strQuat, "idPessoa"))) {
        //caso o campo de escolha for pelo id da pessoa
        val = atoi(strCinco); // pegamos o valor numérico 
        buscaFileIndex(strDois, strTres, val);//chama a função buscaFileIndex do arq.c
    } else {
        //caso o campo de escolha for pelo nome, idade ou twitter da pessoa
        buscaFile(strDois, strQuat, strCinco);//chama a função buscaFile do arq.c
    }
}

void funcQuatro(char *buffer, listaPessoa *ram) {
    //printf("Entrei na funcionalidade 4!\n");
    char *strUm = NULL;
    char *strDois = NULL;
    char *strTres = NULL;
    char *strQuat = NULL;

    //printf("buffer = %s, sizeof(buffer)= %ld and strlen(buffer) = %ld\n", buffer, sizeof(buffer), strlen(buffer));
    strDois = spliter(buffer, 2, 0); // arquivoPessoa.bin
    //printf("%s\n", strDois);
    strTres = spliter(buffer, 3, 0); // arquivoIndex.Index
    //printf("%s\n", strTres);
    strQuat = spliter(buffer, 4, 0); // campo numérico
    //printf("%s\n", strQuat);
    //printf("Chama a função insereArq!\n");
    insereArq(strDois, strTres, atoi(strQuat), ram); //chama a função insereArq do arq.c
    //printf("Chama a função binarioNaTela1!\n");
    binarioNaTela1(strDois, strTres); //chama a função binarioNaTela1 do aux.c
}

/* void funcCinco(char *buffer){
        printf("Entrei na funcionalidade 3!\n");
        char *strUm = NULL;
        char *strDois = NULL;
        char *strTres = NULL;
        char *strQuat = NULL;
        char *strCinco = NULL;
        strUm = spliter(buffer, 1, 0);
        printf("%s\n", strUm);
        strDois = spliter(buffer, 2, 0);
        printf("%s\n", strDois);
        strTres = spliter(buffer, 3, 0);
        printf("%s\n", strTres);
        strQuat = spliter(buffer, 4, 0);
        printf("%s\n", strQuat);
        int i;int n;
        char buffer[100];
        for ( i = 0; i < n; i++)
        {
                scanf("%*c%[^\n]s", buffer);
        }
        //binarioNaTela1(nomeFileOut, nomeFileIndex);
} */

//Função conversão do arquivo csv em binário
void funcSeis(char *buffer){//char *arquivoEntradaSegue, char *arquivoSaidaSegue
    
    char *arquivoEntradaSegue = NULL;
    char *arquivoSaidaSegue = NULL;

    //pega nome do arquivo de entrada e o de saída
    arquivoEntradaSegue = spliter(buffer, 2, 0); // arquivoSegue.csv
    //printf("%s\n", strDois);
    arquivoSaidaSegue = spliter(buffer, 3, 0); // arquivoSegue.bin
    
    convArqBinSegue(arquivoEntradaSegue,arquivoSaidaSegue);
    
    binarioNaTela2(arquivoSaidaSegue);
}

void funcSete(char *buffer, Lista_Segue_RAM *ram_segue){

    char *arquivoEntradaSegue = NULL;
    char *arquivoSaidaSegue = NULL;
    
    //pega nome do arquivo de entrada e o de saída
    arquivoEntradaSegue = spliter(buffer, 2, 0); // arquivoSegue.bin
    //printf("%s\n", strDois);
    arquivoSaidaSegue = spliter(buffer, 3, 0); // arquivoSegueOrdenado.bin
    
    //carrega dados do arquivo bin segue para a ram
    carregaRamSegue(arquivoEntradaSegue, ram_segue);
    //ordena os dados na ram
    quicksortArqOrdernarLista(&ram_segue->head);

    FILE *in_segue = NULL;
    in_segue = fopen(arquivoSaidaSegue, "wb");//abre para escrita o arquivo de ordenado ou cria novo, caso não existe
    
    //escreve os dados ordenados no arquivo bin
    carreaArquivoSegue(ram_segue, in_segue);
    atualizaStatus(in_segue, "1");//atualiza a consistencia do arquivo
    fclose(in_segue);
    binarioNaTela2(arquivoSaidaSegue);
}

void funcOito(char *buffer) {
    //printf("Entrei na funcionalidade 8!\n");
    char *strDois = NULL;
    char *strTres = NULL;
    char *strQuat = NULL;
    char *strCinco = NULL;
    char *strSeis = NULL;

    strDois = spliter(buffer, 2, 0); // arquivoPessoa.bin
    //printf("%s\n", strDois);
    strTres = spliter(buffer, 3, 0); // arquivoIndex.Index
    //printf("%s\n", strTres);
    strQuat = spliter(buffer, 4, 0); //NomeDoCampo
    //printf("%s\n", strQuat);
    strCinco = spliter(buffer, 5, 0); //valor
    //printf("%s\n", strCinco);
    strSeis = spliter(buffer, 6, 0); //arquivoSegueOrdenado.bin
    //printf("%s\n", strSeis);
    
    seguidores(strDois,strTres,strQuat,atoi(strCinco), strSeis); //chama a função seguidores do arq.c
}

void init() {
    //define e aloca as estruturas e parâmetros necessários
    listaPessoa *ram = NULL;
    ram = criarLista(ram);
    
    //cria lista encadeada para os dados segue
    Lista_Segue_RAM *ram_segue = NULL;
    ram_segue = criarListaSegue(ram_segue);
    
    char buffer[100];
    //devemos ler uma linha inteira de comando !
    scanf("%[^\n]s", buffer);
    // função para separar as strings do conteúdo do buffer
    switch (buffer[0]) {
        case '1':
            //printf("Chama a funcionalidade 1\n");
            funcUM(buffer, ram);
            break;
        case '2':
            //printf("Chama a funcionalidade 2\n");
            funcDois(buffer);
            break;
        case '3':
            //printf("Chama a funcionalidade 3\n");
            funcTres(buffer);
            break;
        case '4':
            //printf("Chama a funcionalidade 4\n");
            funcQuatro(buffer, ram);
            break;

        case '5':
            printf("Chama a funcionalidade 5\n");
            break;

        case '6':
            //printf("Chama a funcionalidade 6\n");
            funcSeis(buffer);
            break;

        case '7':
            //printf("Chama a funcionalidade 7\n");
            funcSete(buffer, ram_segue);
            break;

        case '8':
            //printf("Chama a funcionalidade 8\n");
            funcOito(buffer);
            break;

        default:
            break;
    }
    freeLista(ram);
    freeListaSegue(ram_segue);
}