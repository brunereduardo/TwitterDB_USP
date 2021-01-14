/*
 *TRABALHO 2 - DISCIPLINA ESTRUTURA DE DADOS 3
 *Authors:
 *Felipe de Oliveira 10284970
 *Bruner Eduardo Augusto Albrecht 9435846
 *Novembro, 2020
 */

#include "arq.h"
#include "help.h"
#include "ed.h"
/**************************************************************_ASSINATURAS_*************************************************/
void leituraArq(char *fileEntrada, char *filePessoa, char *fileIndexaPessoa, listaPessoa *ram);
void insereArq(char *arqPessoa, char * arqIndexa, int n, listaPessoa *ram);
void atualizaStatus(FILE * arq, char *status);
void atualizaCampo(char *arq, int rrn, int campo, char *string, int number);
void printFile(char *entrada);
void buscaFile(char *arqPessoa, char *campo, char *valor);
void buscaFileIndex(char *arqPessoa, char * arqIndexa, int id);
void convArqBinSegue(char *fileEntradaSegue, char *fileSaidaSegue);
void seguidores(char *arqPessoa,char *arqIndex,char *campo,int id, char *arqSegueOrdenado); 

/**************************************************************_FUNCIONALIDADES_*************************************************/

void atualizaStatus(FILE * arq, char *status) {
    // função que modifica o status de qualquer arquivo que já foi aberto para modificação 
    fseek(arq, 0, SEEK_SET); //voltamos ao primeiro byte do arquivo
    fwrite(status, sizeof (char), 1, arq); //escrevemos o status passado por parâmetro no arquivo especificado.
    //fclose(arq);// fecha o arquivo
}

/* void atualizaCampo(char *arq, int rrn , int campo, char *string , int number){ 
        //string = novo  campo removido ou nomePessoa ou twitterPessoa
        //number = idPessoa ou idadePessoa
        FILE *aux = fopen(arq, "ab");// abrindo o arquivo binário no final, para poder escrever sem que de overwriting
        dataPessoa reserv;// estrutura de dados auxiliar que pega as infos para o registro Pessoa
        atualizaStatus(aux, "0");//atualiza o status para inconsistente 
        // Escolheremos a mudança pelo número do campo do registro: 1-removido, 2-idPessoa, 3-nomePessoa, 4-idadePessoa e 5-twitterPessoa
        switch(campo){
                case 1 :
                        if( (string != NULL) && ( (string == "0") || (string == "1")) && (rrn !=0)){
                                //alterando o campo removido
                                fseek(aux, (rrn*64)+0 , SEEK_SET);// movemos o disco até o registro apartir do começo do arquivo
                                fwrite(string, sizeof(char), 1, aux); //escrevemos a string no arquivo
                        }
                        break;
                case 2 : 
                        if(rrn !=0 ){
                                //alterando o campo idPessoa
                                fseek(aux, (rrn*64)+1 , SEEK_SET);// movemos o disco até o registro apartir do começo do arquivo
                                fwrite(&(number), sizeof(int), 1, aux); //escrevemos a número no arquivo
                        }
                        break;
                case 3 : 
                        if( (string != NULL) && (rrn !=0) ){
                                //alterando o campo nomePessoa
                                trim(string);//tratamos os espaços com a função trim
                                strcpy(reserv.nomePessoa, string);// copiamos a string para dentro da estrutura de auxilo 
                                tratamentoArq(reserv.nomePessoa,sizeof(reserv.nomePessoa));//colocamos os $ nos lixos 
                                fseek(aux, (rrn*64)+5 , SEEK_SET);// movemos o disco até o registro apartir do começo do arquivo
                                fwrite(reserv.nomePessoa, sizeof(reserv.nomePessoa), 1, aux); //escrevemos a string no arquivo
                        }
                        break;
                case 4 : 
                        if( (number > -2)&& (rrn !=0) ){
                                //alterando o campo idadePessoa
                                fseek(aux, (rrn*64)+45 , SEEK_SET);// movemos o disco até o registro apartir do começo do arquivo
                                fwrite(&(number), sizeof(int), 1, aux);//escrevemos a string no arquivo 
                        }
                        break;
                case 5 : 
                        if( (string != NULL) && (rrn !=0) ){
                                //alterando o campo twitterPessoa
                                trim(string);//tratamos os espaços com a função trim
                                strcpy(reserv.twitterPessoa, string);// copiamos a string para dentro da estrutura de auxilo 
                                tratamentoArq(reserv.twitterPessoa,sizeof(reserv.twitterPessoa));//colocamos os $ nos lixos 
                                fseek(aux, (rrn*64)+49 , SEEK_SET);// movemos o disco até o registro apartir do começo do arquivo
                                fwrite(reserv.twitterPessoa, sizeof(reserv.twitterPessoa), 1, aux); //escrevemos a string no arquivo
                        }
                        break;
                default: 
                        ;// não faz nada 
                        break;
        }
        atualizaStatus(aux, "1");//atualiza o status para consistente 
        fclose(aux);//fecha o arquivo
} */

void leituraArq(char *fileEntrada, char *filePessoa, char *fileIndexaPessoa, listaPessoa *ram) { // devemos pegar da entrada os nomes do arquivo e passar pras variáveis 
    FILE * arquivoEntrada = NULL; // ponteiros para os arquivos
    FILE * arquivoPessoa = NULL;
    FILE * arquivoIndexaPessoa = NULL;
    char buffer[50]; // buffer para pegar o cabeçalho do .csv
    int auxRrn, byteOffSet; // variáveis de auxilo
    headPessoa cabecalhoPessoa; // estrutura de dados auxiliar que pega as infos para o cabeçalho do aruivo Pessoa
    dataPessoa registroPessoa; // estrutura de dados auxiliar que pega as infos para o registro Pessoa
    headIndex cabecalhoIndex; // estrutura de dados auxiliar que pega as infos para o cabeçalho do aruivo indexaPessoa
    dataIndex auxIndex; // estrutura de dados auxiliar que pega as infos para o registro do aruivo indexaPessoa

    int flag = 1; // Utilizada para verificar se podemos gravar ou não
    // atribuindo ao auxRrn o valor zero(cabeçalho) pois queremos que os rrn dos registrom comecem a partir do numero 1. 
    //Assim Não teremos probelmas de utilizar o rrn = 0 no calculo do byteoffset e assim acabar mexendo no cabeçalho 
    auxRrn = 0;
    // primeiro abrir os arquivos para leitura e para escrita
    arquivoEntrada = fopen(fileEntrada, "r");
    arquivoPessoa = fopen(filePessoa, "wb");
    arquivoIndexaPessoa = fopen(fileIndexaPessoa, "wb");
    //conferir se não deu problema na abertura dos arquivos
    if (arquivoEntrada == NULL) {
        printf("Falha no carregamento do arquivo.\n");
        exit(0);
    }
    if (arquivoPessoa == NULL) {
        printf("Falha no carregamento do arquivo.\n");
        exit(0);
    }
    if (arquivoIndexaPessoa == NULL) {
        printf("Falha no carregamento do arquivo.\n");
        exit(0);
    }
    //iniciando o cabeçalho do arquivo pessoa
    //strcpy(&cabecalhoPessoa.status, "0");
    cabecalhoPessoa.status = '0'; // 0-> inconsistente pois estamos abrindo para a escrita;
    cabecalhoPessoa.quantidadePessoas = 0;
    strcpy(cabecalhoPessoa.space, "0");
    tratamentoString(cabecalhoPessoa.space, sizeof (cabecalhoPessoa.space));

    //escrevendo o cabeçalho no arquivoPessoas
    fwrite(&(cabecalhoPessoa.status), sizeof (char), 1, arquivoPessoa);
    fwrite(&(cabecalhoPessoa.quantidadePessoas), sizeof (int), 1, arquivoPessoa);
    fwrite(cabecalhoPessoa.space, sizeof (cabecalhoPessoa.space), 1, arquivoPessoa);

    //iniciando o cabeçalho do arquivo indexaPessoa
    cabecalhoIndex.status = '0'; // 0-> inconsistente pois estamos abrindo para a escrita;
    strcpy(cabecalhoIndex.space, "0"); // passando o "0" deixamos claro para a função de tratamento, que tem que preenche tudo com $
    tratamentoString(cabecalhoIndex.space, sizeof (cabecalhoIndex.space)); //chamamos o tratamento

    //escrevendo o cabeçalho no arquivoIndexaPessoa
    fwrite(&(cabecalhoIndex.status), sizeof (char), 1, arquivoIndexaPessoa);
    fwrite(cabecalhoIndex.space, sizeof (cabecalhoIndex.space), 1, arquivoIndexaPessoa);

    // realizar a leitura do cabeçalho do arquivo de entrada
    fscanf(arquivoEntrada, "%[^\n]", buffer);

    while (fscanf(arquivoEntrada, "%d%*c", &registroPessoa.idPessoas) == 1) {
        //pega o id de cada linha até o arquivo acabar. Se não tiver um id, eu simplesmente não leio.
        //limpando o buffer
        strncpy(buffer, "\0", sizeof (buffer)); // coloca um \0, depois a strncpy vai preencher os bytes restantes do buffer com \0

        //if(fscanf(arquivoEntrada, "%[^,]s", registroPessoa.nomePessoa) < 1)
        if (fscanf(arquivoEntrada, "%[^,]s", buffer) < 1) {
            //caso seja nulo, colocamos um \0
            strcpy(registroPessoa.nomePessoa, "\0");
        }
        trim(buffer);
        strncpy(registroPessoa.nomePessoa, buffer, sizeof (registroPessoa.nomePessoa));
        //Tratamento de preenchimento ou não do campo
        //trim(registroPessoa.nomePessoa);// limpando os espaços antes e depois do nome
        tratamentoString(registroPessoa.nomePessoa, sizeof (registroPessoa.nomePessoa)); //completando o resto com $

        //campos int nulos ficam iguais a -1
        if (fscanf(arquivoEntrada, "%*c%d", &registroPessoa.idadePessoa) < 1) {
            registroPessoa.idadePessoa = -1;
        }

        strncpy(buffer, "\0", sizeof (buffer)); // coloca um \0, depois a strncpy vai preencher os bytes restantes do buffer com \0
       
        if (fscanf(arquivoEntrada, "%*c%[^\n]s", buffer) < 1) {
            //caso seja nulo, colocamos um \0
            strcpy(registroPessoa.twitterPessoa, "\0");
            flag = 0;
            // este campo NÃO DEVE SER NULO: ENTÃO POSTAR UMA MENSAGEM DE ERRO E NÃO GUARDAR NO ARQUIVO
        }
        trim(buffer);
        strncpy(registroPessoa.twitterPessoa, buffer, sizeof (registroPessoa.twitterPessoa));
        //Tratamento de preenchimento ou não do campo
        tratamentoString(registroPessoa.twitterPessoa, sizeof (registroPessoa.twitterPessoa)); //completando o resto com $

        if (flag == 1) {
            //Deu certo, então salvo no arquivo binário de saida
            
            strcpy(&(registroPessoa.removido), "1"); //escreve no campo removido
            //escrevendo no arquivoPessoa.bin
            fwrite(&(registroPessoa.removido), sizeof (char), 1, arquivoPessoa);
            fwrite(&(registroPessoa.idPessoas), sizeof (int), 1, arquivoPessoa);
            fwrite(registroPessoa.nomePessoa, sizeof (registroPessoa.nomePessoa), 1, arquivoPessoa);
            fwrite(&(registroPessoa.idadePessoa), sizeof (int), 1, arquivoPessoa);
            fwrite(registroPessoa.twitterPessoa, sizeof (registroPessoa.twitterPessoa), 1, arquivoPessoa);
            // adiciona na lista encadeada ordenada
            insereLista(ram, registroPessoa.idPessoas, auxRrn);
            //Se não estivéssemos utilizando a lista encadeada, era só escrever no arquivo indexaPessoa
            //fwrite(&(cabecalhoIndex.status), sizeof(char),1,arquivoIndexaPessoa);
            //fwrite(cabecalhoIndex.space, sizeof(cabecalhoIndex.space),1,arquivoIndexaPessoa);
        }
        auxRrn++; // atualiza o rrn
    }
    // voltando para alterar o campo qntPessoas do cabeçalho do arquivo Pessoa
    fseek(arquivoPessoa, 1, SEEK_SET);
    fwrite(&(ram->qntPessoas), sizeof (int), 1, arquivoPessoa);
    // Carrecando as informações da ram para o arquivoIndexaPessoa.bin
    carregaArquivo(arquivoIndexaPessoa, ram);
    //atualiza os status dos arquivos pra consistentes
    atualizaStatus(arquivoPessoa, "1");
    atualizaStatus(arquivoIndexaPessoa, "1");
    //fechando os arquivos;
    fclose(arquivoPessoa);
    fclose(arquivoIndexaPessoa);
    fclose(arquivoEntrada);
}

void insereArq(char *arqPessoa, char * arqIndexa, int n, listaPessoa *ram) {
    FILE * p = fopen(arqPessoa, "rb+");
    FILE * in = fopen(arqIndexa, "rb+");
    dataPessoa reserv;
    char buffer[100];
    char aux;
    char *campU = NULL;
    char *campD = NULL;
    char *campT = NULL;
    char *campQ = NULL;
    int idAux;
    int rrnAux;
    int i;
    if (p == NULL)// verificando se houve algum problema em lidar com o arquivo
    {
        printf("Falha no processamento do arquivo.\n");
        exit(0);
    }
    if (in == NULL)// verificando se houve algum problema em lidar com o arquivo
    {
        printf("Falha no processamento do arquivo.\n");
        exit(0);
    }
    fread(&aux, sizeof (char), 1, p);
    if (!(strcmp(&aux, "0"))) {
        printf("Falha no processamento do arquivo.\n"); //  caso o arquivoPessoa esteja inconsistente 
        exit(0);
    }
    fread(&aux, sizeof (char), 1, in);
    if (!(strcmp(&aux, "0"))) {
        printf("Falha no processamento do arquivo.\n"); //  caso o arquivoIndex esteja inconsistente 
        exit(0);
    }
    fseek(p, -1, SEEK_CUR); // voltanto para o início do arquivo
    fseek(in, -1, SEEK_CUR); // voltanto para o início do arquivo
    carregaRam(ram, in); // carregamos pra ram o arquivo index
    fseek(p, -63, SEEK_END);
    fread(&idAux, sizeof (int), 1, p);
    rrnAux = buscaLista(ram, idAux);
    atualizaStatus(p, "0"); //atualiza o status para inconsistente
    fseek(p, 0, SEEK_END); // será se precisa colocar fseek(p,1, SEEK_End); ?
    for (i = 0; i < n; i++) {
        scanf("%*c%[^\n]s", buffer); // pegamos n vezes a entrada do terminal
        //printf("%s\n",buffer);// é necessário que os campos string estejam entre aspas duplas
        campU = spliter(buffer, 1, 1); // idadePessoa
        //printf("%s\n",campU);
        campD = spliter(buffer, 2, 1); //nomePessoa
        //printf("%s\n",campD);
        campT = spliter(buffer, 3, 1); // idadePessoa
        //printf("%s\n",campT);
        campQ = spliter(buffer, 4, 1); //twitterPessoa
        //printf("%s\n",campQ);

        trim(campD);
        trim(campQ);
        // comparar para os casos que vierem nulos
        if (((strcmp(campU, "-1")) != 0) && ((strcmp(campQ, "NULO")) != 0)) {
            //printf("AQUI #268!\n");
            strcpy(&reserv.removido, "1"); // coloca como não removido
            reserv.idPessoas = atoi(campU); // transforma o id texto em id numérico
            //printf("AQUI #271!\n");
            strncpy(reserv.nomePessoa, campD, sizeof (reserv.nomePessoa)); //copia o nomePessoa(depois de arrumado pela trim()) para a estrutura auxiliar , truncando o tamanho até o espaço permitido pelo campo
            //strcpy(reserv.nomePessoa, campD);
            tratamentoString(reserv.nomePessoa, sizeof (reserv.nomePessoa)); // faz o tratamento dos espaços restantes com $
            if (!(strcmp(campT, "NULO"))) {
                reserv.idadePessoa = -1; // se a idade for nula , colocamos -1
            } else {
                reserv.idadePessoa = atoi(campT);
            }// transforma a idade texto em idade numérico
            //printf("AQUI #278!\n");
            strncpy(reserv.twitterPessoa, campQ, sizeof (reserv.twitterPessoa)); //copia o twitterPessoa(depois de arrumado pela trim()) para a estrutura auxiliar , truncando o tamanho até o espaço permitido pelo campo
            //strcpy(reserv.twitterPessoa, campQ);
            //printf("AQUI #280!\n");
            tratamentoString(reserv.twitterPessoa, sizeof (reserv.twitterPessoa)); // faz o tratamento dos espaços restantes com $
            //printf("AQUI #282!\n");
            rrnAux++; // atualizamos o rrn
            //printf("AQUI #284!\n");
            if (buscaLista(ram, reserv.idPessoas) != -1) {
                strncpy(buffer, "\0", sizeof (buffer)); //limpando o buffer
                continue; // retorne um número diferente de -1, significa que esse id já exite no arquivo index
            }
            insereLista(ram, reserv.idPessoas, rrnAux);
            //printf("AQUI #289!\n");
            fwrite(&(reserv.removido), sizeof (char), 1, p);
            fwrite(&(reserv.idPessoas), sizeof (int), 1, p);
            fwrite(reserv.nomePessoa, sizeof (reserv.nomePessoa), 1, p);
            fwrite(&(reserv.idadePessoa), sizeof (int), 1, p);
            fwrite(reserv.twitterPessoa, sizeof (reserv.twitterPessoa), 1, p);
            strncpy(buffer, "\0", sizeof (buffer)); //limpando o buffer
            //fseek(p, 0, SEEK_CUR);
            //printf("AQUI #296!\n");
        }
    }
    //imprimirListaRam(ram);
    fseek(p, 1, SEEK_SET);// volta para a posição que contem a quantidade de pessoas
    fwrite(&(ram->qntPessoas), sizeof (int), 1, p);// escreve a nova quantidade de pessoas
    carregaArquivo(in, ram);//carrega para o arquivo a nova lista de pessoas
    atualizaStatus(p, "1");//atualiza o status para consistente
    atualizaStatus(in, "1");
    fclose(p);
    fclose(in);
}

void printFile(char *entrada) {
    //essa função foi feita exclusivamente para o arquivo Pessoa
    // ela imprimi os dados que constam no arquivo pessoa como não removidos
    FILE * source = fopen(entrada, "rb");
    int aux;
    char status; // variável de auxilio 
    dataPessoa registroPessoa; // estrutura de dados auxiliar que pega as infos do registro lido do arquivo
    if (source == NULL) {
        printf("Falha no processamento do arquivo.\n");
        exit(0);
    }
    // lendo o status do arquivo 
    fread(&(status), sizeof (char), 1, source);
    fread(&(aux), sizeof (int), 1, source);
    // verificar se está consistênte

    //confere o status e se o arquivo possui registors para serem impressos
    if (status == '0') {
        printf("Falha no processamento do arquivo.\n");
        exit(0);
    }
    if (aux == 0) {
        printf("Registro Inexistente.\n");
        exit(0);
    }

    // depois do status, andamos 59 bytes para chegar no primeiro Id
    fseek(source, 59, SEEK_CUR);
    //enquanto conseguirmos ler o campo removido, nos manteremos no laço para a impressão dos dados
    while (fread(&(registroPessoa.removido), sizeof (char), 1, source) != 0) {
        //apos termos guardado o campo removido na estrutura auxiliar, verificamos se o registro já não foi removido
        if (registroPessoa.removido == '1') {
            //lemos os campos e guardamos estes na estrutura auxiliar
            fread(&(registroPessoa.idPessoas), sizeof (int), 1, source);
            fread(registroPessoa.nomePessoa, sizeof (registroPessoa.nomePessoa), 1, source);
            fread(&(registroPessoa.idadePessoa), sizeof (int), 1, source);
            fread(registroPessoa.twitterPessoa, sizeof (registroPessoa.twitterPessoa), 1, source);
            //print dos valores
            printf("Dados da pessoa de código: %d \n", registroPessoa.idPessoas);
            //verificamos o campo nomePessoa
            if (strlen(registroPessoa.nomePessoa) == 0) {
                printf("Nome: - \n");
            } else {
                printf("Nome: %s \n", registroPessoa.nomePessoa);
            }
            //verificamos o campo idadePessoa
            if (registroPessoa.idadePessoa < 1) {
                printf("Idade: - \n");
            } else {
                printf("Idade: %d \n", registroPessoa.idadePessoa);
            }
            printf("Twitter: %s \n", registroPessoa.twitterPessoa);
            printf("\n");
        } else {
            //se o campo removido estava marcado com "0", pulamos para o próximo registro
            fseek(source, 63, SEEK_CUR);
        }
    }
    //fechamos o arquivo
    fclose(source);
}

void buscaFile(char *arqPessoa, char *campo, char *valor) {
    //Esta função busca no arquivo passado como parâmetro, o valor referente ao campo passado na chamada da mesma. EXCLUSIVA DO ARQUIVO PESSOA
    FILE *pessoa = fopen(arqPessoa, "rb");
    char status;
    int val; // variável auxiliar
    int flag = 0; // variável auxiliar para impressão
    dataPessoa registroPessoa; // estrutura de dados auxiliar que pega as infos do registro lido do arquivo
    // comparamos se o campo passado no parâmetro da função é igual aos especificados no trabalho
    if (pessoa == NULL) {
        printf("Falha no processamento do arquivo.\n");
        exit(0);
    }
    fread(&(status), sizeof (char), 1, pessoa);
    if (status == '0') {
        printf("Falha no processamento do arquivo.\n");
        exit(0);
    }
    fseek(pessoa, -1, SEEK_CUR);

    if (!(strcmp(campo, "idadePessoa"))) {
        val = atoi(valor); //chamamos a função atoi para transformar a string em valor numérico
        fseek(pessoa, 64, SEEK_SET); // indo para o primeiro registro
        //enquanto conseguirmos ler o campo removido, nos manteremos no laço para a busca dos dados
        while (fread(&(registroPessoa.removido), sizeof (char), 1, pessoa) != 0) {
            //apos termos guardado o campo removido na estrutura auxiliar, verificamos se o registro já não foi removido
            if (registroPessoa.removido == '1') {
                fseek(pessoa, 44, SEEK_CUR); // 44 pois já lemos o primeiro campo , removido, oq faz com  q o ponteiro esteja na proxima posição
                fread(&(registroPessoa.idadePessoa), sizeof (int), 1, pessoa);
                //andamos 4 posições no arquivo. Levando para a próximo posição do registro( twitterPessoa - byte 49).
                if (registroPessoa.idadePessoa == val) {
                    //lemos os campos e guardamos estes na estrutura auxiliar
                    fread(registroPessoa.twitterPessoa, sizeof (registroPessoa.twitterPessoa), 1, pessoa);
                    fseek(pessoa, -63, SEEK_CUR); // voltamos 63 posições para voltar no campo idPessoa
                    fread(&(registroPessoa.idPessoas), sizeof (int), 1, pessoa);
                    fread(registroPessoa.nomePessoa, sizeof (registroPessoa.nomePessoa), 1, pessoa);
                    //print dos valores
                    printf("Dados da pessoa de código: %d \n", registroPessoa.idPessoas);
                    //verificamos o campo nomePessoa
                    if (strlen(registroPessoa.nomePessoa) == 0) {
                        printf("Nome: - \n");
                    } else {
                        printf("Nome: %s \n", registroPessoa.nomePessoa);
                    }
                    //verificamos o campo idadePessoa
                    if (registroPessoa.idadePessoa == -1) {
                        printf("Idade: - \n");
                    } else {
                        printf("Idade: %d \n", registroPessoa.idadePessoa);
                    }
                    printf("Twitter: %s \n", registroPessoa.twitterPessoa);
                    printf("\n");
                    flag = flag + 1; // um elemento encontrado com o valor pedido
                    fseek(pessoa, 19, SEEK_CUR); // vamos para o próximo registro, a partir da posição byte 45 (45+19 = byte 64)
                } else {
                    // andando para o próximo registro
                    fseek(pessoa, 15, SEEK_CUR); //vamos para o próximo registro, a partir da posição byte 49 (49+15 = byte 64)
                }

            } else {
                fseek(pessoa, 63, SEEK_CUR); // vai para o proximo id
            }

        }
        if (flag == 0) {// caso não tenha nenhum registro com a idade escolhida ou os registros foram todos marcados como removidos
            printf("Registro inexistente\n");
            exit(0); //termina a função 
        } else {
            exit(0); //termina a função 
        }

    }

    if (!(strcmp(campo, "nomePessoa"))) {
        // comparamos se o campo passado no parâmetro da função é igual aos especificados no trabalho
        fseek(pessoa, 64, SEEK_SET); // indo para o primeiro registro
        //enquanto conseguirmos ler o campo removido, nos manteremos no laço para a busca dos dados
        while (fread(&(registroPessoa.removido), sizeof (char), 1, pessoa) != 0) {
            //apos termos guardado o campo removido na estrutura auxiliar, verificamos se o registro já não foi removido
            if (registroPessoa.removido == '1') {
                fseek(pessoa, 4, SEEK_CUR); // 4 pois já lemos o primeiro campo , removido, oq faz com  q o ponteiro esteja na proxima posição
                fread(registroPessoa.nomePessoa, sizeof (registroPessoa.nomePessoa), 1, pessoa);
                //andmos 40 posições no arquivo. Levando para a próximo posição do registro( idadePessoa - byte 45)
                if (!(strcmp(registroPessoa.nomePessoa, valor))) {
                    //lemos os campos e guardamos estes na estrutura auxiliar
                    fread(&(registroPessoa.idadePessoa), sizeof (int), 1, pessoa);
                    fread(registroPessoa.twitterPessoa, sizeof (registroPessoa.twitterPessoa), 1, pessoa);
                    fseek(pessoa, -63, SEEK_CUR); // voltamos 63 posições para cair no campo idPessoa
                    fread(&(registroPessoa.idPessoas), sizeof (int), 1, pessoa);
                    //print dos valores
                    printf("Dados da pessoa de código: %d \n", registroPessoa.idPessoas);
                    //verificamos o campo nomePessoa
                    if (strlen(registroPessoa.nomePessoa) == 0) {
                        printf("Nome: - \n");
                    } else {
                        printf("Nome: %s \n", registroPessoa.nomePessoa);
                    }
                    //verificamos o campo idadePessoa
                    if (registroPessoa.idadePessoa < 1) {
                        printf("Idade: - \n");
                    } else {
                        printf("Idade: %d \n", registroPessoa.idadePessoa);
                    }
                    printf("Twitter: %s \n", registroPessoa.twitterPessoa);
                    printf("\n");
                    flag++;
                    //termina a função pois já achou os dados 
                    break;
                } else {
                    // andando para o próximo registro 
                    fseek(pessoa, 19, SEEK_CUR); //vamos para o próximo registro, a partir da posição byte 45 (45+19 = byte 64)
                }
            } else {
                fseek(pessoa, 63, SEEK_CUR); //vamos para o próximo registro, a partir da posição byte 1 (1+63 = byte 64)
            }
        }
        if (flag == 0) {
            printf("Registro inexistente\n");
            exit(0);
        } else {
            exit(0); //termina a função 
        }
    }

    if (!(strcmp(campo, "twitterPessoa"))) {
        // comparamos se o campo passado no parâmetro da função é igual aos especificados no trabalho
        fseek(pessoa, 64, SEEK_SET); // indo para o primeiro registro
        //enquanto conseguirmos ler o campo removido, nos manteremos no laço para a busca dos dados
        while (fread(&(registroPessoa.removido), sizeof (char), 1, pessoa) != 0) {
            if (registroPessoa.removido == '1') {
                //apos termos guardado o campo removido na estrutura auxiliar, verificamos se o registro já não foi removido
                fseek(pessoa, 48, SEEK_CUR); // 48 pois já lemos o primeiro campo , removido, oq faz com  q o ponteiro esteja na proxima posição
                fread(registroPessoa.twitterPessoa, sizeof (registroPessoa.twitterPessoa), 1, pessoa);
                //andmos 15 posições no arquivo. Levando para a primeira posição do próximo registro.
                if (!(strcmp(registroPessoa.twitterPessoa, valor))) {
                    //lemos os campos e guardamos estes na estrutura auxiliar
                    fseek(pessoa, -63, SEEK_CUR); // voltamos 63 posições para cair no campo idPessoa
                    fread(&(registroPessoa.idPessoas), sizeof (int), 1, pessoa);
                    fread(registroPessoa.nomePessoa, sizeof (registroPessoa.nomePessoa), 1, pessoa);
                    fread(&(registroPessoa.idadePessoa), sizeof (int), 1, pessoa);
                    //print dos valores
                    printf("Dados da pessoa de código: %d \n", registroPessoa.idPessoas);
                    //verificamos o campo nomePessoa
                    if (strlen(registroPessoa.nomePessoa) == 0) {
                        printf("Nome: - \n");
                    } else {
                        printf("Nome: %s \n", registroPessoa.nomePessoa);
                    }
                    //verificamos o campo idadePessoa
                    if (registroPessoa.idadePessoa == -1) {
                        printf("Idade: - \n");
                    } else {
                        printf("Idade: %d \n", registroPessoa.idadePessoa);
                    }
                    printf("Twitter: %s \n", registroPessoa.twitterPessoa);
                    printf("\n");
                    flag++;
                    //termina a função pois já achou os dados 
                    break;
                }
            } else {
                fseek(pessoa, 63, SEEK_CUR); //vamos para o próximo registro, a partir da posição byte 1 (1+63 = byte 64)
            }
        }
        if (flag == 0) {// caso não tenha nenhum registro com a idade escolhida ou os registros foram todos marcados como removidos
            printf("Registro inexistente\n");
            exit(0); //termina a função 
        } else {
            exit(0); //termina a função 
        }
    }

    fclose(pessoa);
}

void buscaFileIndex(char *arqPessoa, char * arqIndexa, int id) {
    ///Esta função busca no arquivo passado como parâmetro, o id referente ao campo passado na chamada da mesma. EXCLUSIVA DO ARQUIVO INDEXA
    FILE *pessoa = fopen(arqPessoa, "rb"); //abrindo o arquivo binário  para leitura
    FILE *indexa = fopen(arqIndexa, "rb"); //abrindo o arquivo index para leitura
    int aux; // variável auxiliar para a busca na estrutura de Dados
    char status;
    dataPessoa tag; // estrutura de dados auxiliar que pega as infos do registro lido do arquivo
    listaPessoa * ramAux = criarLista(ramAux);

    if (pessoa == NULL) {
        printf("Falha no processamento do arquivo.\n");
        exit(0);
    }
    if (indexa == NULL) {
        printf("Falha no processamento do arquivo.\n");
        exit(0);
    }
    fread(&(status), sizeof (char), 1, pessoa);
    if (status == '0') {
        printf("Falha no processamento do arquivo.\n");
        exit(0);
    }
    fseek(pessoa, -1, SEEK_CUR);
    fread(&(status), sizeof (char), 1, indexa);
    if (status == '0') {
        printf("Falha no processamento do arquivo.\n");
        exit(0);
    }
    fseek(indexa, -1, SEEK_CUR);

    if (id != 0) {
        //caso o arquivo Index não vier ordenado a estrutura de dados o ordenará. caso contrário a inserção só sera feita no final
        carregaRam(ramAux, indexa); //inserimos todos os (id, rrn) na estrutura
        aux = buscaLista(ramAux, id); // buscando o id passado como parâmetro na busca
        if (aux == -1) {
            printf("Registro inexistente.\n");
            exit(0); // não achou o elemento, interrompendo o fluxo do programa
        } else {
            //lemos os campos e guardamos estes na estrutura auxiliar
            aux+=1;
            fseek(pessoa, (aux * 64), SEEK_SET);
            fread(&(tag.removido), sizeof (char), 1, pessoa);
            fread(&(tag.idPessoas), sizeof (int), 1, pessoa);
            fread(tag.nomePessoa, sizeof (tag.nomePessoa), 1, pessoa);
            fread(&(tag.idadePessoa), sizeof (int), 1, pessoa);
            fread(tag.twitterPessoa, sizeof (tag.twitterPessoa), 1, pessoa);
            if (tag.removido == '1') {
                //apos termos guardado o campo removido na estrutura auxiliar, verificamos se o registro já não foi removido
                //print dos valores
                printf("Dados da pessoa de código %d \n", tag.idPessoas);
                //verificamos o campo nomePessoa
                if (strlen(tag.nomePessoa) == 0) {
                    printf("Nome: - \n");
                } else {
                    printf("Nome: %s \n", tag.nomePessoa);
                }
                //verificamos o campo idadePessoa
                if (tag.idadePessoa == -1) {
                    printf("Idade: - \n");
                } else {
                    printf("Idade: %d anos\n", tag.idadePessoa);
                }
                printf("Twitter: %s \n", tag.twitterPessoa);
                printf("\n");
            }
        }

    }
    fclose(pessoa);
    fclose(indexa);
    freeLista(ramAux);
}

//função carrega dados do csv para o arquivoSegue.bin
void convArqBinSegue(char *fileEntradaSegue, char *fileSaidaSegue) {
    FILE *arquivoEntradaSegue = NULL;
    FILE *arquivoSaidaSegue = NULL;

    //estrutura auxiliar para escrita do cabeçalho
    headSegue cabecalhoSegue;
    
    //arquivo csv
    arquivoEntradaSegue = fopen(fileEntradaSegue, "r");
    
    ////para gravar o cabeçalho
    int quantidade_pessoas = 0;

    if (arquivoEntradaSegue != NULL) {
        
        //ARQUIVO BINARIO SEGUE QUE SERÁ CRIADO
        arquivoSaidaSegue = fopen(fileSaidaSegue, "wb");

        char sifrao = '$';
        dataSegue registro;

        cabecalhoSegue.status = '0';
        fwrite(&(cabecalhoSegue.status), sizeof (char), 1, arquivoSaidaSegue);

        //quantide seguidores
        int quant = 0;
        fwrite(&(quant), sizeof (int), 1, arquivoSaidaSegue);

        //lixo
        strncpy(cabecalhoSegue.space, "0", 1);
        //função que vai completar com '$' o espaço
        tratamentoString(cabecalhoSegue.space, sizeof (cabecalhoSegue.space));
        //printf("Tratamento Lixo: %s\n",cabecalhoSegue.space);
        fwrite(cabecalhoSegue.space, sizeof (cabecalhoSegue), 1, arquivoSaidaSegue);


        fscanf(arquivoEntradaSegue, "%*[^\r\n]"); //pula a primeira linha do csv quem tem um cabeçalho dos campos

        //escreve as linhas do registro
        while (fscanf(arquivoEntradaSegue, "%d%*c%d%*c%[^,]%*c%[^,]%*c%s", &registro.idPessoa, &registro.idPessoaQueESeguida, registro.grau, registro.dataInicioSegue, registro.dataFimSegue) == 5) {
            char removido = '1';
            fwrite(&removido, sizeof (removido), 1, arquivoSaidaSegue);

            //grava id do registro
            fwrite(&registro.idPessoa, sizeof (int), 1, arquivoSaidaSegue);
            //grava id do registro que é seguido
            fwrite(&registro.idPessoaQueESeguida, sizeof (int), 1, arquivoSaidaSegue);
            //grava grau de amizade
            registro.grau[1] = '\0';
            fwrite(registro.grau, sizeof (char), 2, arquivoSaidaSegue);
            fwrite(&sifrao, sizeof (char), 1, arquivoSaidaSegue);//incluido ao grua \0 e o $
            //grava a data de inicio da amizade
            fwrite(registro.dataInicioSegue, sizeof (char), 10, arquivoSaidaSegue);
            //grava a data de fim da amizade
            fwrite(registro.dataFimSegue, sizeof (char), 10, arquivoSaidaSegue);
            quantidade_pessoas++;
            /*
            printf("\n");
            printf("ID Pessoa: %d\n",registro.idPessoa);
            printf("ID Pessoa que e Seguida: %d\n",registro.idPessoaQueESeguida);
            printf("Grau: %s\n",registro.grau);
            printf("Data inicio: %s\n",registro.dataInicioSegue);
            printf("Data fim: %s\n",registro.dataFimSegue);
             */
        }
        // Pronto! Já leu o registro INTEIRO em apenas uma linha de código. Agora só escreve ele aqui

    } else {
        printf("Falha no carregamento do arquivo.\n");
        exit(0);
    }

    //printf("QUANTIDADE E REGISTROS FEITOS: %d\n", quantidade_pessoas);
    //volta no cabeçalho e escreve a quantidade de registros
    fseek(arquivoSaidaSegue, 1, SEEK_SET);
    fwrite(&(quantidade_pessoas), sizeof (int), 1, arquivoSaidaSegue);

    //escreve o arquivo como consistente, fim da escrita
    char consistencia = '1';
    fseek(arquivoSaidaSegue, 0, SEEK_SET);
    fwrite(&(consistencia), sizeof (char), 1, arquivoSaidaSegue);

    fclose(arquivoEntradaSegue);
    fclose(arquivoSaidaSegue);

}

void seguidores(char *arqPessoa,char *arqIndex,char *campo,int id, char *arqSegueOrdenado){
    
    if(!(strcmp(campo, "idPessoa"))){
        node_segue *firstPoint = NULL;
        int rrnSegue;
        char status;
        dataSegue registroSegue;
        Lista_Segue_RAM *ram = NULL;
        ram = criarListaSegue(ram);
        carregaRamSegue2(arqSegueOrdenado,ram);
        
        FILE * arqSegue = fopen(arqSegueOrdenado, "rb");
        
        if(arqSegue == NULL){
            printf("Falha no processamento do arquivo.\n");
            freeListaSegue(ram);
            exit(0);
        }
        
        fread(&(status), sizeof (char), 1, arqSegue);
        
        if (status == '0') {
            printf("Falha no processamento do arquivo.\n");
            freeListaSegue(ram);
            exit(0);
        }
        
        fseek(arqSegue, -1, SEEK_CUR);
        buscaFileIndex(arqPessoa, arqIndex,id);//imprime as informações do id especificado 
        //retorna o ponteiro para o primeiro elemento da lista que contém o id buscado 
        firstPoint = buscaBinaria(ram->head, ram->tail, ram->qntSeguidores, id);
        if(firstPoint == NULL){
            printf("Falha no firstPoint do arquivo.\n");
            freeListaSegue(ram);
            exit(0);
        }
        while( (firstPoint!=NULL) && (firstPoint->idPessoaQueSegue == id) ){
            if(firstPoint->removido == '1'){
                //print dos valores
                printf("Segue a pessoa de código: %d\n", firstPoint->idPessoaQueESeguida);
                printf("Justificativa para seguir: %s\n", (!strcmp(firstPoint->grauAmizade, "0")) ? "segue porque é uma celebridade": ( (!strcmp(firstPoint->grauAmizade, "1")) ? "segue porque é amiga de minha amiga": ( (!strcmp(firstPoint->grauAmizade, "2")) ? "segue porque é minha amiga": "-")));
                printf("Começou a seguir em: %s\n", firstPoint->dataInicioQueSegue);
                printf("Parou de seguir em: %s\n", firstPoint->dataFimQueSegue);
                printf("\n");
            }
            firstPoint = firstPoint->next;
        }
        fclose(arqSegue);
        freeListaSegue(ram);
    }
}