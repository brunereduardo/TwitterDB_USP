/*
 *TRABALHO 2 - DISCIPLINA ESTRUTURA DE DADOS 3

 *Authors:
 *Felipe de Oliveira 10284970
 *Bruner Eduardo Augusto Albrecht 9435846

 *Novembro, 2020
 */
#include "ed.h"
#include "arq.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/************************************ORDENAÇÃO DO ARQUIVO Index**************************************************/
node *criaNo(int idPessoa, int rrn);
void freeLista(listaPessoa *ram);
listaPessoa * criarLista(listaPessoa * ram);
void insereLista(listaPessoa *ram, int idPessoa, int rrn);
int removeLista(listaPessoa *ram, int idPessoa);
int buscaLista(listaPessoa *ram, int idPessoa);
void carregaArquivo(FILE *arqDestino, listaPessoa *ram);
void carregaRam(listaPessoa *ram, FILE *arqFonte);
void imprimirListaRam(listaPessoa *ram);
/************************************ORDENAÇÃO DO ARQUIVO SEGUE**************************************************/
node_segue *criaNoSegue(char removido, int idPessoaQueSegue, int idPessoaQueESeguida, char grauAmizade[3], char dataInicioQueSegue[], char dataFimQueSegue[]);
void freeListaSegue(Lista_Segue_RAM *ram);
Lista_Segue_RAM * criarListaSegue(Lista_Segue_RAM * ram);
void insereListaSegue(Lista_Segue_RAM *ram, char removido, int idPessoaQueSegue, int idPessoaQueESeguida, char *grauAmizade, char *dataInicioQueSegue, char *dataFimQueSegue);
void carregaRamSegue(char *arqEntrada, Lista_Segue_RAM *ram);
void carreaArquivoSegue(Lista_Segue_RAM *ram, FILE *arqDestino);
void imprimirListaSegueRam(Lista_Segue_RAM *ram);
//void atualizaStatus(FILE *arq, char *status);// NÃO É PRA ESTAR AQUI -> mover para arq
node_segue * quicksortArqEndNo(node_segue *aux);
node_segue * quicksortArqParticiona(node_segue *inicio, node_segue *fim, node_segue **novoInicio, node_segue **novoFim);
node_segue * quicksortArqRecursividade(node_segue *inicio, node_segue *fim);
void quicksortArqOrdernarLista(node_segue **cabeca);
node_segue *buscaBinaria(node_segue *ini, node_segue *fim, int qntSeguidores, int id);
/**************************************************************_ESTRUTURA_DE_DADOS_INDEX*************************************************/
void tratamentoString(char *campo, int size);

node *criaNo(int idPessoa, int rrn) {
    //cria o nó que mantem as infos sobre o idPessoa, rrn e um ponteiro para o próximo nó
    node *new = NULL;
    new = (node*) malloc(sizeof (node));
    new->idPessoa = idPessoa;
    new->rrn = rrn;
    new->next = NULL;
    return new;
}

void freeLista(listaPessoa *ram) {
    //Libera a memória alocada para os nós 
    int n = ram->qntPessoas;
    int i;
    node * aux = NULL;
    node * nxt = NULL;
    if (n > 0)// caso a lista tenha algum nó dentro dela
    {
        aux = ram->head;
        for (i = 0; i < n; i++) {
            nxt = aux->next;
            free(aux);
            aux = nxt;
        }
        free(ram);
    }
    if (n == 0)//caso a lista já esteja vazia
    {
        free(ram);
    }
}

listaPessoa * criarLista(listaPessoa * ram) {
    //Função para a criação da lista encadeada ordenada. 
    ram = (listaPessoa *) malloc(sizeof (struct listaPessoa*));
    ram->head = NULL; // ponteiro para o começo da lista
    ram->tail = NULL; // ponteiro para o fim da lista
    ram->qntPessoas = 0; // número que representa a quantidade de pessoas
    return ram;
}

int buscaLista(listaPessoa *ram, int idPessoa) {
    //Função que busca na lista encadeada ordenada um idPessoa passado por parâmentro e retorna seu rrn. 
    node *aux = NULL;
    node *reserv = NULL;
    if (ram->head == NULL) {
        //caso a lista não tenha elementos
        //printf("Lista Vazia!\n");
        return -1;
    }
    if (ram->head != NULL) {
        //caso a lista tenha elementos
        aux = ram->head; //começamos com o primeiro elemento
        //busca enquanto o idPessoa for diferente do elemento da lista em questão ou até que o ponteiro passe do ultimo elemento
        while ((aux != NULL) && (idPessoa != aux->idPessoa)) {
            reserv = aux; // pegamos o ponteiro analisado e reservamos ele
            aux = aux->next; // pegamos o próximo elemento onde iremos procurar o id maior que oq foi passado como parâmetro
        }
        if (aux != NULL) {
            //caso temos o idPessoa especificado no parâmetro da função, retornamos o seu rrn.
            return aux->rrn;
        }
        if (aux == NULL) {
            //caso não temos o idPessoa especificado no parâmetro da função, retornamos -1.
            return -1;

        }
    }
}

void insereLista(listaPessoa *ram, int idPessoa, int rrn) {
    //Função que insere na lista encadeada ordenada um idPessoa e rrn, passados por parâmentro.
    node *aux = NULL;
    node *in = NULL;
    node *reserv = NULL;

    if (ram->qntPessoas == 0) {
        //caso não exista nós na lista, criamos um e inserimos este na mesma.
        ram->head = criaNo(idPessoa, rrn);
        ram->tail = ram->head; // o ponteiro do início e do fim apontam para o primeiro elemento
        ram->qntPessoas = ram->qntPessoas + 1; // aumentamos o número da quantidade de pessoas.
    } else {
        if ((buscaLista(ram, idPessoa)) != -1) {
            //se retornar um valor diferente de -1, já existe este id na lista
            //printf("Já existe esse idPessoa na ram\n");
            exit(0);
        }
        // inserindo de forma ordenada na lista. Primeiro criamos o nó   
        in = criaNo(idPessoa, rrn);
        aux = ram->head; // pegamos o primeiro elemento com o ponteiro auxiliar 

        if (in->idPessoa < ram->head->idPessoa) {
            //inserindo entre o head e o primeiro elemente 
            in->next = ram->head; //aponta para o primeiro elemento da lista
            ram->head = in; //o ponteiro do início da lista aponta para o novo nó
            ram->qntPessoas = ram->qntPessoas + 1; //aumentamos o número da quantidade de pessoas
        }

        if (in->idPessoa > ram->tail->idPessoa) {
            //inserindo depois do ultimo elemente 
            ram->tail->next = in; //o ultimo elemento da lista aponta para o novo nó
            ram->tail = in; //o ponteiro do fim da lista aponta para o novo nó
            ram->qntPessoas = ram->qntPessoas + 1; //aumentamos o número da quantidade de pessoas
        }
        if ((in->idPessoa > ram->head->idPessoa) && (in->idPessoa < ram->tail->idPessoa)) {
            //inserindo entre elementos
            while ((in->idPessoa > aux->idPessoa) && (aux != NULL)) {
                //busca enquanto o idPessoa for diferente do elemento da lista em questão ou até que o ponteiro passe do ultimo elemento
                reserv = aux; // pegamos o ponteiro analisado e reservamos ele
                aux = aux->next; // pegamos o próximo elemento onde iremos procurar o id maior que oq foi inserido
            }
            in->next = aux; // apontamos o próximo elemento do novo nó para o ponteiro que tem o idPessoa maior 
            reserv->next = in; // apontamos o próximo elemento do nó com idPessoa menor para o novo nó 
            ram->qntPessoas = ram->qntPessoas + 1; //aumentamos o número da quantidade de pessoas
        }
    }
}

int removeLista(listaPessoa *ram, int idPessoa) {
    //Função que remove da lista encadeada ordenada um idPessoa passado por parâmentro.
    node *aux = NULL;
    node *reserv = NULL;
    int retorno;

    if (ram->head == NULL) {
        //caso a lista não tenha elementos
        //printf("Lista Vazia!\n");
        return -1;
    }

    //tenho que colocar um if da busca na lista-> caso o elemento não esteja na mesma, damos exit(1) da função
    if ((buscaLista(ram, idPessoa)) == -1) {
        //se retornar um valor igual a -1, não temos este idPessoa na lista
        return -1;
        //exit(1);
    }

    if ((ram->head != NULL) && (idPessoa == ram->head->idPessoa)) {
        //remove o primeiro elemento da lista encadeada ordenada
        aux = ram->head; // auxiliar aponta para o primeiro elemento
        ram->head = aux->next; // o ponteiro do início da lista aponta para o segundo elemento
        ram->qntPessoas = ram->qntPessoas - 1; // diminuímos o número da quantidade de pessoas.
        retorno = aux->rrn; // retorna o rrn do idPessoa que foi removido
        free(aux); //libera a memória utilizada pelo nó
        return retorno;
    }

    if ((ram->head != NULL)) {
        //remove qualquer elemento
        aux = ram->head; // auxiliar aponta para o primeiro elemento
        while ((aux != NULL) && (idPessoa != aux->idPessoa)) {
            //busca enquanto o idPessoa for diferente do elemento da lista em questão ou até que o ponteiro passe do ultimo elemento
            reserv = aux; // pegamos o ponteiro analisado e reservamos ele
            aux = aux->next; // pegamos o próximo elemento onde iremos procurar o id maior que oq foi inserido
        }

        if ((aux != NULL) && (idPessoa != ram->tail->idPessoa)) {
            //caso ele ache e não seja o ultimo( remove qualquer elemento)
            reserv->next = aux->next; // pegamos o elemento anterior e apontamos para o próximo que é apontado pelo ponteiro auxiliar
            ram->qntPessoas = ram->qntPessoas - 1; // diminuímos o número da quantidade de pessoas.
            retorno = aux->rrn; // retorna o rrn do idPessoa que foi removido
            free(aux); //libera a memória utilizada pelo nó
            return retorno;

        }

        if ((aux != NULL) && (idPessoa == ram->tail->idPessoa)) {
            //caso ele ache e seja o ultimo
            ram->tail = reserv; //fazemos o ponteiro do fim da lista apontar para o elemento anterior
            reserv->next = NULL; //fazemos o elemento anterior apontar para null
            ram->qntPessoas = ram->qntPessoas - 1; // diminuímos o número da quantidade de pessoas.
            retorno = aux->rrn; // retorna o rrn do idPessoa que foi removido
            free(aux); //libera a memória utilizada pelo nó
            return retorno;
        }


    }
}

void carregaArquivo(FILE *arqDestino, listaPessoa *ram) {
    //carrega os dados da lista encadeada ordenada (memoria ram) para o arquivoDestino
    int i;
    node *aux = ram->head; // auxiliar aponta para o primeiro elemento da lista

    if (ram->head == NULL) {
        //caso a lista não tenha elementos
        // printf("Lista Vazia!");
        return;
    }

    if (ram->head != NULL) {
        //caso a lista tenha elementos
        fseek(arqDestino, 8, SEEK_SET); // pulamos o cabeçalho
        for (i = 0; i < ram->qntPessoas; i++) {
            //vamos do primeiro elemento até o ultimo, baseando no número da quantidade de pessoas da lista
            fwrite(&(aux->idPessoa), sizeof (int), 1, arqDestino); // escrevemos o idPessoa no arquivo destino
            fwrite(&(aux->rrn), sizeof (int), 1, arqDestino); // escrevemos o rrn no arquivo destino
            aux = aux->next; // vamos para o próximo elemento
        }
    }
}

void carregaRam(listaPessoa *ram, FILE *arqFonte) {
    //carrega os dados do arquivoFonte para a lista encadeada ordenada (memoria ram) 
    char status; // variável para pegar o status do arquivo
    int idAux, rrnAux; // auxiliares

    if (arqFonte == NULL) {
        printf("Falha no carregamento do arquivo.\n");
        exit(0);
    }
    //lemos o status do arquivo 
    fread(&(status), sizeof (char), 1, arqFonte);
    // verificar se está consistênte
    if (status == '0') {
        printf("Falha no processamento do arquivo.\n");
        exit(0);
    }
    // depois do status, andamos 7bytes para chegar no primeiro Id
    fseek(arqFonte, 7, SEEK_CUR);
    //enquanto conseguirmos ler um idPessoa do arquivo, e guardamos no iDauxiliar , continuamos o laço
    while (fread(&(idAux), sizeof (int), 1, arqFonte) != 0) {
        //lemos o rrn do arquivo e guardamos no rrn auxiliar 
        fread(&(rrnAux), sizeof (int), 1, arqFonte);
        //chamamos a função de inserir na lista encadeada ordenada
        insereLista(ram, idAux, rrnAux);
    }


}

void imprimirListaRam(listaPessoa *ram) {
    node *aux;
    aux = ram->head; // auxiliar aponta para o primeiro elemento da lista 
    printf("Lista de Index\n");
    while (aux != NULL) {
        // enquanto o auxiliar não for nulo, continuamos imprimindo os seguintes valores
        printf("(ID: %d , ", aux->idPessoa);
        printf("RRN: %d)\n", aux->rrn);
        //vamos para o próximo elemento
        aux = aux->next;
    }
    printf("\n");
    return;
}

/***********************************ORDENAÇÃO DO ARQUIVO SEGUE**********************************/
//cria o nó que mantem as infos sobre a atividade *segue*-removido|idSegue|idESeguido|GrauAmizade|DataInicio|DataFim e um ponteiro para o próximo nó

node_segue *criaNoSegue(char removido, int idPessoaQueSegue, int idPessoaQueESeguida, char grauAmizade[3], char * dataInicioQueSegue, char * dataFimQueSegue) {

    node_segue *novo = NULL;
    novo = (node_segue*) malloc(sizeof (node_segue));
    novo->removido = removido;
    novo->idPessoaQueSegue = idPessoaQueSegue;
    novo->idPessoaQueESeguida = idPessoaQueESeguida;
    strncpy(novo->grauAmizade, grauAmizade, 3);
    strncpy(novo->dataInicioQueSegue, dataInicioQueSegue, 11);
    //printf("DATA PAU: %s\n", novo->dataInicioQueSegue);
    strncpy(novo->dataFimQueSegue, dataFimQueSegue, 11);
    novo->rrnAux = 0;
    novo->next = NULL;
    return novo;
}

//Libera a memória alocada para os nós 

void freeListaSegue(Lista_Segue_RAM *ram_segue) {

    int n = ram_segue->qntSeguidores;
    int i;
    node_segue * aux = NULL;
    node_segue * nxt = NULL;
    if (n > 0)// caso a lista tenha algum nó dentro dela
    {
        aux = ram_segue->head;
        for (i = 0; i < n; i++) {
            nxt = aux->next;
            free(aux);
            aux = nxt;
        }
        free(ram_segue);
    }
    if (n == 0)//caso a lista já esteja vazia
    {
        free(ram_segue);
    }
}

//cria a lista de relação *Segue*

Lista_Segue_RAM * criarListaSegue(Lista_Segue_RAM * ram_segue) {
    //Função para a criação da lista encadeada ordenada. 
    ram_segue = (Lista_Segue_RAM *) malloc(sizeof (struct Lista_Segue_RAM*));
    ram_segue->head = NULL; // ponteiro para o começo da lista
    ram_segue->tail = NULL; // ponteiro para o fim da lista
    ram_segue->qntSeguidores = 0; // número que representa a quantidade de pessoas
    return ram_segue;
}

//insere na lista segue

void insereListaSegue(Lista_Segue_RAM *ram_segue, char removido, int idPessoaQueSegue, int idPessoaQueESeguida, char *grauAmizade, char *dataInicioQueSegue, char *dataFimQueSegue) {
    //Função que insere na lista encadeada ordenada um idPessoa e rrn, passados por parâmentro.
    node_segue *aux = NULL;
    node_segue *in = NULL;
    node_segue *reserv = NULL;

    if (ram_segue->qntSeguidores == 0) {
        //caso não exista nós na lista, criamos um e inserimos este na mesma.
        ram_segue->head = criaNoSegue(removido, idPessoaQueSegue, idPessoaQueESeguida, grauAmizade, dataInicioQueSegue, dataFimQueSegue);
        ram_segue->tail = ram_segue->head; // o ponteiro do início e do fim apontam para o primeiro elemento
        ram_segue->qntSeguidores = ram_segue->qntSeguidores + 1; // aumentamos o número da quantidade de pessoas.
        ram_segue->head->rrnAux = ram_segue->qntSeguidores;
    } else {
        in = criaNoSegue(removido, idPessoaQueSegue, idPessoaQueESeguida, grauAmizade, dataInicioQueSegue, dataFimQueSegue);
        aux = ram_segue->tail; // pegamos o primeiro elemento com o ponteiro auxiliar 
        aux->next = in;
        ram_segue->tail = in;
        //reserv->next = in;// apontamos o próximo elemento do nó com idPessoa menor para o novo nó 
        ram_segue->qntSeguidores = ram_segue->qntSeguidores + 1; //aumentamos o número da quantidade de pessoas
        in->rrnAux = ram_segue->qntSeguidores;
    }
    return;
}

//carrega dados de segue.bin para a RAM_segue, através de lista encadeada

void carregaRamSegue(char *arqEntrada, Lista_Segue_RAM *ram_segue) {
    //carrega os dados do arquivoDestino para a lista encadeada ordenada (memoria ram_segue) 
    FILE *aux = fopen(arqEntrada, "rb"); //abrimos o arquivo para leitura binária 
    char status; // variável para pegar o status do arquivo
    int qntd;
    char removido;
    int idPessoaQueSegue;
    int idPessoaQueESeguida;
    char grauAmizade[3];
    char dataInicioQueSegue[11];
    char dataFimQueSegue[11];

    if (aux == NULL) {
        printf("Falha no carregamento do arquivo.\n");
        exit(0);
    }
    //lemos o status do arquivo 
    fread(&(status), sizeof (char), 1, aux);
    // verificar se está consistênte
    if (status == '0') {
        printf("Falha no carregamento do arquivo.\n");
        exit(0);
    }
    fread(&qntd, sizeof (int), 1, aux);
    // depois do status, andamos 27bytes para chegar no primeiro Id
    fseek(aux, 27, SEEK_CUR);

    //enquanto conseguirmos ler um idPessoa do arquivo, e guardamos no iDauxiliar , continuamos o laço
    while (fread(&(removido), sizeof (char), 1, aux) != 0) {
        fread(&(idPessoaQueSegue), sizeof (int), 1, aux);
        fread(&(idPessoaQueESeguida), sizeof (int), 1, aux);
        fread(grauAmizade, 3, 1, aux);
        fread(dataInicioQueSegue, 10, 1, aux);
        fread(dataFimQueSegue, 10, 1, aux);

        dataInicioQueSegue[10] = '\0';
        dataFimQueSegue[10] = '\0';



        //chamamos a função de inserir na lista encadeada ordenada
        insereListaSegue(ram_segue, removido, idPessoaQueSegue, idPessoaQueESeguida, grauAmizade, dataInicioQueSegue, dataFimQueSegue);
    }
    //fechamos o arquivo
    fclose(aux);

}

//carrega dados de segue.bin para a RAM_segue, através de lista encadeada Função 8

void carregaRamSegue2(char *arqEntrada, Lista_Segue_RAM *ram_segue) {
    //carrega os dados do arquivoDestino para a lista encadeada ordenada (memoria ram_segue) 
    FILE *aux = fopen(arqEntrada, "rb"); //abrimos o arquivo para leitura binária 
    char status; // variável para pegar o status do arquivo
    int qntd;
    char removido;
    int idPessoaQueSegue;
    int idPessoaQueESeguida;
    char grauAmizade[3];
    char dataInicioQueSegue[11];
    char dataFimQueSegue[11];

    if (aux == NULL) {
        printf("Falha no processamento do arquivo.\n");
        exit(0);
    }
    //lemos o status do arquivo 
    fread(&(status), sizeof (char), 1, aux);
    // verificar se está consistênte
    if (status == '0') {
        printf("Falha no processamento do arquivo.\n");
        exit(0);
    }
    fread(&qntd, sizeof (int), 1, aux);
    // depois do status, andamos 27bytes para chegar no primeiro Id
    fseek(aux, 27, SEEK_CUR);

    //enquanto conseguirmos ler um idPessoa do arquivo, e guardamos no iDauxiliar , continuamos o laço
    while (fread(&(removido), sizeof (char), 1, aux) != 0) {
        fread(&(idPessoaQueSegue), sizeof (int), 1, aux);
        fread(&(idPessoaQueESeguida), sizeof (int), 1, aux);
        fread(grauAmizade, 3, 1, aux);
        fread(dataInicioQueSegue, 10, 1, aux);
        fread(dataFimQueSegue, 10, 1, aux);

        dataInicioQueSegue[10] = '\0';
        dataFimQueSegue[10] = '\0';



        //chamamos a função de inserir na lista encadeada ordenada
        insereListaSegue(ram_segue, removido, idPessoaQueSegue, idPessoaQueESeguida, grauAmizade, dataInicioQueSegue, dataFimQueSegue);
    }
    //fechamos o arquivo
    fclose(aux);

}

//carrega os dados da lista encadeada ordenada (memoria ram_segue) para o arquivoDestino 

void carreaArquivoSegue(Lista_Segue_RAM *ram_segue, FILE *arqDestino) {

    int i;
    char grau = '$';
    node_segue *aux = ram_segue->head; // auxiliar aponta para o primeiro elemento da lista

    //Fazer cabeçalho
    headSegue cabecalhoSegue;

    if (arqDestino == NULL) {
        printf("Falha no processamento do arquivo.\n"); //Falha no carregamento do arquivo.
    }
    //
    //prepara cabeçalho no arquivo
    strncpy(&(cabecalhoSegue.status), "0", 1); // 0 inconsistente pois estamos abrindo para a escrita;
    strncpy(cabecalhoSegue.space, "0", 1); // passando o "0" deixamos claro para a função de tratamento, que tem que preenche tudo com $
    tratamentoString(cabecalhoSegue.space, sizeof (cabecalhoSegue.space)); //chamamos o tratamento


    if (ram_segue->head == NULL) {
        //caso a lista não tenha elementos
        int qntd_segue = 0; //quantidade de registros 0
        fwrite(&cabecalhoSegue.status, sizeof (char), 1, arqDestino);
        fwrite(&(qntd_segue), sizeof (int), 1, arqDestino);
        fwrite(cabecalhoSegue.space, sizeof (cabecalhoSegue.space), 1, arqDestino);
        printf("Lista Vazia!");

    } else {

        fseek(arqDestino, 0, SEEK_SET);
        fwrite(&cabecalhoSegue.status, sizeof (char), 1, arqDestino); //<<------------ COMEÇA FALHA DE SEGMENTAÇÃO AQUI
        fwrite(&(ram_segue->qntSeguidores), sizeof (int), 1, arqDestino);
        fwrite(cabecalhoSegue.space, sizeof (cabecalhoSegue.space), 1, arqDestino);

        //preenche dados no arquivo
        for (i = 0; i < ram_segue->qntSeguidores; i++) {
            //vamos do primeiro elemento até o ultimo, baseando no número da quantidade de pessoas da lista
            fwrite(&(aux->removido), sizeof (char), 1, arqDestino);
            fwrite(&(aux->idPessoaQueSegue), sizeof (int), 1, arqDestino); // escrevemos o idPessoaQueSegue no arquivo destino
            fwrite(&(aux->idPessoaQueESeguida), sizeof (int), 1, arqDestino); // escrevemos o idPessoaQueéSeguida no arquivo destino
            fwrite((aux->grauAmizade), sizeof (char), 2, arqDestino); //grua de amizar junto com o \0. Exemplo 2\0
            fwrite(&(grau), sizeof (char), 1, arqDestino); //inclui o sifrão na sequencia do grau de amizade
            fwrite(aux->dataInicioQueSegue, sizeof (char), 10, arqDestino); //data de inicio segue, eliminando o \0 no final
            fwrite(aux->dataFimQueSegue, sizeof (char), 10, arqDestino); //data de fim segue, eliminando o \0 no final
            aux = aux->next; // vamos para o próximo elemento
        }
    }
    return;
}

//Imprimir lista encadeada

void imprimirListaSegueRam_segue(Lista_Segue_RAM *ram_segue) {
    node_segue *aux;
    aux = ram_segue->head; // auxiliar aponta para o primeiro elemento da lista 
    printf("Lista de infos\n");
    while (aux != NULL) {

        // enquanto o auxiliar não for nulo, continuamos imprimindo os seguintes valores
        printf("\nID segue: %d\n", aux->idPessoaQueSegue);
        printf("ID e seguido: %d\n", aux->idPessoaQueESeguida);
        printf("Grau: %s\n", aux->grauAmizade);
        printf("DATA1: %s\n", aux->dataInicioQueSegue);
        printf("DATA2: %s\n", aux->dataFimQueSegue);
        //vamos para o próximo elemento
        aux = aux->next;
    }
    printf("\n");
    printf("Quantidade: %d\n", ram_segue->qntSeguidores);
    return;
}

//Função de aux quick sort,  Retorna o ultimo no da lista

node_segue *quicksortArqEndNo(node_segue * aux) {
    while (aux != NULL && aux->next != NULL)
        aux = aux->next;
    return aux;
}

//Particiona a lista tomando o último elemento como o pivo

node_segue *quicksortArqParticiona(node_segue *incio, node_segue *fim, node_segue **novoInicio, node_segue **novoFim) {
    node_segue *pivot = fim;
    node_segue *prev = NULL, *aux = incio, *cauda = pivot;

    // Durante a partição, tanto o inio como o final da lista podem mudar
    // valores atualizados nas variáveis novoInicio e novoFim
    while (aux != pivot) {

        //O nó->idPessoaQueSegue que tiver valor menor que o pivô - torna-se o novo inicio
        if (aux->idPessoaQueSegue < pivot->idPessoaQueSegue) {

            if ((*novoInicio) == NULL)
                (*novoInicio) = aux;

            prev = aux;
            aux = aux->next;
        } else if (aux->idPessoaQueSegue > pivot->idPessoaQueSegue) {
            // Mover o nó auxpara a próxima cauda e mudar a cauda
            if (prev) {
                prev->next = aux->next;
            }
            node_segue *tmp = aux->next;
            aux->next = NULL;
            cauda->next = aux;
            cauda = aux;
            aux = tmp;
        } else {
            //Se nó->idPessoaQueSegue tiver valor igual ao pivô->idPessoaQueSegue

            //Desempata com idPessoaQueESeguida
            if (aux->idPessoaQueESeguida < pivot->idPessoaQueESeguida) {
                //O primeiro nó que tem um valor menor que o pivô - torna-se o novo inicio
                if ((*novoInicio) == NULL)
                    (*novoInicio) = aux;

                prev = aux;
                aux = aux->next;
            } else if (aux->idPessoaQueESeguida > pivot->idPessoaQueESeguida) {
                // Mover o nó auxpara a próxima cauda e mudar a cauda
                if (prev) {
                    prev->next = aux->next;
                }
                node_segue *tmp = aux->next;
                aux->next = NULL;
                cauda->next = aux;
                cauda = aux;
                aux = tmp;
            }

        }
    }

    // Se os dados dinâmicos forem o menor elemento na lista atual o pivô se torna a cabeça
    if ((*novoInicio) == NULL)
        (*novoInicio) = pivot;

    // atualiza o novoFim para o último nó atual
    (*novoFim) = cauda;


    return pivot;
}

//Faz a classificação do no final

node_segue *quicksortArqRecursividade(node_segue *inicio, node_segue *fim) {
    //condição para rodar o metodo
    if (!inicio || inicio == fim) {
        return inicio;
    }

    node_segue *novoInicio = NULL, *novoFim = NULL;

    // Particiona a lista, novoInicio e novoFim serão atualizados pela função de partição
    node_segue *pivot = quicksortArqParticiona(inicio, fim, &novoInicio, &novoFim);


    // Se pivot é o menor elemento - não há necessidade de chamar a recursão par ao lado esquerdo do pivo.
    if (novoInicio != pivot) {
        //Definir o nó antes do nó tmp como NULL
        node_segue *tmp = novoInicio;
        while (tmp->next != pivot)
            tmp = tmp->next;
        tmp->next = NULL;

        //chama o metodo recursivo para sublista antes do pivot
        novoInicio = quicksortArqRecursividade(novoInicio, tmp);

        // Altera o próximo do último nó da metade esquerda para girar
        tmp = quicksortArqEndNo(novoInicio);
        tmp->next = pivot;
    }

    //chama o metodo recursivo para sublista após do pivot
    pivot->next = quicksortArqRecursividade(pivot->next, novoFim);

    return novoInicio;
}

//Função de ordenação aux

void quicksortArqOrdernarLista(node_segue **inicio) {
    (*inicio) = quicksortArqRecursividade(*inicio, quicksortArqEndNo(*inicio));
    return;
}

node_segue *buscaBinaria(node_segue *ini, node_segue *fim, int qntSeguidores, int id) {
    if ( (ini->idPessoaQueSegue == id) && (fim->idPessoaQueSegue == id) ) {
        return ini;
    }
    if (qntSeguidores < 1) {
        return NULL; // se a quantidade chegar a um, e passar pelos ifs anteriores, significa que o id não se encontra no ArquivoSegueOrdenado
    } else {
        int i;
        node_segue *aux = ini;
        node_segue *reserv = NULL;
        node_segue *find = NULL;

        int qAux = (qntSeguidores % 2 != 0) ? ((qntSeguidores / 2) + 1) : (qntSeguidores / 2);

        for (i = 1; i < qAux; i++) {
            reserv = aux;
            aux = aux->next;
        }

        if(aux->idPessoaQueSegue == id){
            //quando o elemento do meio está ao redor de dois elementos que ainda possuem o mesmo id
            //printf("O Aux->Id = %d == id buscado = %d AND qAux = %d e a qntSeguidores = %d\n", aux->idPessoaQueSegue, id, qAux, qntSeguidores);
            if( (reserv->idPessoaQueSegue == id) && (aux->next->idPessoaQueSegue == id)){
                //printf("(reserv->idPessoaQueSegue == id) && (aux->next->idPessoaQueSegue == id)\n");
                find = buscaBinaria(ini, reserv, (qAux-1),id);
            }
            if(aux->next->idPessoaQueSegue != id){
                //ultimo elemento com o id especificado
                //printf("(aux->next->idPessoaQueSegue != id)\n");
                find = buscaBinaria(ini, aux, (qAux -1), id);
            }
            if(reserv->idPessoaQueSegue != id){
                //printf("(reserv->idPessoaQueSegue != id)\n");
                // caso o anterior esteja com um id diferente, significa que o já temos o ponteiro para o primeiro elemento
                return aux;
            }
        }
        if(aux->idPessoaQueSegue < id){
            //printf("O Aux->Id = %d < id buscado = %d AND qAux = %d e a qntSeguidores = %d\n", aux->idPessoaQueSegue, id, qAux, qntSeguidores);
            aux = aux->next;
            find = buscaBinaria(aux, fim, (qAux-1), id);
        }
        if(aux->idPessoaQueSegue > id){
            //printf("O Aux->Id = %d > id buscado = %d AND qAux = %d e a qntSeguidores = %d\n", aux->idPessoaQueSegue, id, qAux, qntSeguidores);
            find = buscaBinaria(ini, reserv, (qAux-1), id);
            
        }
        return find;
    }
}