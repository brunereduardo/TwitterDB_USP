/*
 *TRABALHO 2 - DISCIPLINA ESTRUTURA DE DADOS 3

 *Authors:
 *Felipe de Oliveira 10284970
 *Bruner Eduardo Augusto Albrecht 9435846

 *Novembro, 2020
 */

#ifndef AUXILIARES_H_
#define AUXILIARES_H_
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "ed.h"
/***************************************_ASSINATURAS_*************************************************/
void binarioNaTela1(char *nomeArquivoBinario, char *nomeArquivoIndice); /* Correção do arquivo binário. */
void binarioNaTela2(char *nomeArquivoBinario);
void trim(char *str); /* Pode ser útil pra você (extra). */
void scan_quote_string(char *str); /* Use para ler strings entre aspas. */
char *spliter(char * buffer, int position, int special);
void tratamentoString(char *campo, int size);

#endif /* AUXILIARES_H_ */