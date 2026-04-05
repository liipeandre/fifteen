#ifndef TABULEIRO_H_INCLUDED
#define TABULEIRO_H_INCLUDED

#include <string.h>      //  para usar o memcpy();
#include <stdlib.h>      //  para outras coisas
#include <stdbool.h>     //  para o tipo bool
#include <math.h>        //  para usar o abs()
#include <time.h>        //  para usar o rand() e srand()

typedef struct Tabuleiro{

//  armazena o nome do jogador

    char nome_do_jogador[20];

//  contador de jogadas

    int jogadas_realizadas;

//  as duas matrizes (a original que é gerada no inicio do jogo e a do jogo, que é alterada a cada jogada

    int tabuleiro_original[4][4];
    int tabuleiro_jogo[4][4];

//  a linha e coluna da casa vazia (que é representada pelo valor zero).

    int linha_casa_vazia;
    int coluna_casa_vazia;

}Tabuleiro;




//  preenche o tabuleiro com a sequencia ordenada

void preenche_tabuleiro(Tabuleiro*);




//  embaralha o tabuleiro, realizando jogadas aleatórias

void embaralhar_tabuleiro (Tabuleiro*);




//  faz a validação da jogada.

bool verifica_jogada(Tabuleiro*, int linha_jogada, int coluna_jogada);




//  faz a troca de duas peças no tabuleiro.

void troca_peca(int* origem, int* destino);




//  verifica se o jogo acabou

bool verifica_fim_jogo (Tabuleiro*);

#endif // TABULEIRO_H_INCLUDED
