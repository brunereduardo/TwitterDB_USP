/*
 *TRABALHO 2 - DISCIPLINA ESTRUTURA DE DADOS 3

 *Authors:
 *Felipe de Oliveira 10284970
 *Bruner Eduardo Augusto Albrecht 9435846

 *Novembro, 2020
 */
#ifndef ESTRUTURA_H_
#define ESTRUTURA_H_
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


/**************************************************************ESTRUTURA DE DADOS****************************/
struct no {
    int idPessoa;
    int rrn;
    struct no * next;
}; //nó para guardar as informações
typedef struct no node;

struct listPessoas {
    int qntPessoas;
    node *head;
    node *tail;
}; //lista encadeada 
typedef struct listPessoas listaPessoa;

struct no_segue {
    char removido;
    int idPessoaQueSegue;
    int idPessoaQueESeguida;
    char grauAmizade[3];
    char dataInicioQueSegue[11];//declarei 11 porque insiro um \0 para não ter junção com o dataFimQueSegue. Na escrita do arqSegue, faço o tratamento
    char dataFimQueSegue[11];//idem
    int rrnAux;
    struct no_segue * next;
};
typedef struct no_segue node_segue;

struct listSegue {
    int qntSeguidores;
    node_segue *head;
    node_segue *tail;
};
typedef struct listSegue Lista_Segue_RAM;

/**************************************************************ASSINATURAS PARA ARQUIVO INDEX****************************************/
node *criaNo(int idPessoa, int rrn);
void freeLista(listaPessoa *ram);
listaPessoa * criarLista(listaPessoa * ram);
void insereLista(listaPessoa *ram, int idPessoa, int rrn);
int removeLista(listaPessoa *ram, int idPessoa);
int buscaLista(listaPessoa *ram, int idPessoa);
void carregaArquivo(FILE *arqDestino, listaPessoa *ram);
void carregaRam(listaPessoa *ram, FILE *arqFonte);
void imprimirListaRam(listaPessoa *ram);
/************************************ASSINATURAS PARA ARQUIVO SEGUE**************************************************/
node_segue *criaNoSegue(char removido, int idPessoaQueSegue,int idPessoaQueESeguida,char grauAmizade[3], char dataInicioQueSegue[], char dataFimQueSegue[]);
void freeListaSegue(Lista_Segue_RAM *ram);
Lista_Segue_RAM * criarListaSegue(Lista_Segue_RAM * ram);
void insereListaSegue(Lista_Segue_RAM *ram, char removido, int idPessoaQueSegue, int idPessoaQueESeguida, char *grauAmizade, char *dataInicioQueSegue, char *dataFimQueSegue);
void carregaRamSegue(char *arqEntrada, Lista_Segue_RAM *ram);
void carregaRamSegue2(char *arqEntrada, Lista_Segue_RAM *ram_segue);
void carreaArquivoSegue(Lista_Segue_RAM *ram, FILE *arqDestino);
void imprimirListaSegueRam(Lista_Segue_RAM *ram);
node_segue * quicksortArqEndNo(node_segue *aux);
node_segue * quicksortArqParticiona(node_segue *inicio, node_segue *fim, node_segue **novoInicio, node_segue **novoFim);
node_segue * quicksortArqRecursividade(node_segue *inicio, node_segue *fim);
void quicksortArqOrdernarLista(node_segue **cabeca);
node_segue *buscaBinaria(node_segue *ini, node_segue *fim, int qntSeguidores, int id);
#endif