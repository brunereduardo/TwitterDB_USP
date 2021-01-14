/*
 *TRABALHO 2 - DISCIPLINA ESTRUTURA DE DADOS 3

 *Authors:
 *Felipe de Oliveira 10284970
 *Bruner Eduardo Augusto Albrecht 9435846

 *Novembro, 2020
 */
#ifndef ARQUIVO_H_
#define ARQUIVO_H_
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "ed.h"


/****************************************************ESTRUTURA DE DADOS****************************/
typedef struct {
    char status; // status do arquivo
    int quantidadePessoas; //quantidade Pessoas
    char space[59]; // lixo para completar o 64 bytes
} headPessoa; // cabeçalho  = 64 bytes

typedef struct {
    char removido; // campo para marcar o registro como logicamente removido 
    int idPessoas; // campo com o id da pessoa
    char nomePessoa[40]; // campo com o nome da pessoa
    int idadePessoa; // campo com a idade da pessoa
    char twitterPessoa[15]; // campo com a identificação do twitter da pessoa
} dataPessoa; // tamanho = 64bytes

//Para o arquivo indexa:

typedef struct {
    char status; // status do arquivo
    char space[7]; // lixo para completar o 64 bytes
} headIndex; // // cabeçalho  = 8 bytes

typedef struct {
    int idPessoas; // campo com o id da pessoa
    int rrn; // campo com o rrn referente ao id da pessoa no arquivo pessoa
} dataIndex;

typedef struct{
    char status;
    int qntdSeguidores;
    char space[27];
}headSegue;

typedef struct {
    char removido; // campo para marcar o registro como logicamente removido 
    int idPessoa; // campo id da pessoa 
    int idPessoaQueESeguida;//campo id da pessoa é seguida
    char grau[3]; // grau da pessoa
    char dataInicioSegue[10]; // campo data de inicio da amizade
    char dataFimSegue[10]; // campo com a data de fim da amizade
} dataSegue; // tamanho = 64bytes

/**************************************************************ASSINATURAS****************************************/
void atualizaStatus(FILE * arq, char *status);
void atualizaCampo(char *arq, int rrn, int campo, char *string, int number);
void leituraArq(char *fileEntrada, char *filePessoa, char *fileIndexaPessoa, listaPessoa *ram);
void insereArq(char *arqPessoa, char * arqIndexa, int n, listaPessoa *ram);
void printFile(char *entrada);
void buscaFile(char *arqPessoa, char *campo, char *valor);
void buscaFileIndex(char *arqPessoa, char * arqIndexa, int id);
void convArqBinSegue(char *fileEntradaSegue, char *fileSaidaSegue);
void seguidores(char *arqPessoa,char *arqIndex,char *campo,int id, char *arqSegueOrdenado); 

#endif /* ARQUIVO_H_ */