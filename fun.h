/*
 TRABALHO 2 - DISCIPLINA ESTRUTURA DE DADOS 3

 *Authors:
 *Felipe de Oliveira 10284970
 *Bruner Eduardo Augusto Albrecht 9435846

 *Novembro, 2020
 */
#ifndef FUNCIONALIDADES_H_
#define FUNCIONALIDADES_H_
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "ed.h"
#include "help.h"
/**************************************************************ASSINATURAS****************************************/
void funcUM(char *buffer, listaPessoa *ram);
void funcDois(char *buffer);
void funcTres(char *buffer);
void funcQuatro(char *buffer, listaPessoa *ram);
//void funcCinco(char *buffer);
void funcSeis(char *buffer);
void funcSete(char *buffer, Lista_Segue_RAM *ram_segue);
void funcOito(char *buffer);
void init();

#endif /* FUNCIONALIDADES_H_ */