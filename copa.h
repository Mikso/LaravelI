#ifndef _COPA_H
#define _COPA_H
#include <stdio.h>
#include <stdbool.h>
#include<string.h>
#define ARQ_SEL "selecoes.dat"
#define ARQ_JOGO "jogos.dat"
#define ARQ_LIST_JOGOS "jogos.txt"

typedef struct {
    int dia;
    int mes;
} tdata;

typedef struct {
    int id;
    char nome[31];
    char grupo;
} tselecao;

typedef struct {
    char grupo;
    tdata data;
    char estadio[21];
    int id_mandante;
    int id_visitante;
} tjogo;

/* cadastra as sele��es de um grupo */
void cad_selecao(void);

/* altera o nome de uma sele��o dado seu id */
void alterar_selecao(void);

/* lista no v�deo todas as sele��es cadastradas */
void list_selecoes(void);

/* lista no v�deo as sele��es de um grupo */
void list_selecoes_grupo(void);

/* cadastra os jogos da 1� fase da Copa da R�ssia */
void cad_jogo(void);

/* lista no v�deo/arquivo os jogos de um grupo */
void list_jogos_grupo(void);

/* lista no v�deo os jogos de uma data */
void list_jogos_data(void);

#endif
