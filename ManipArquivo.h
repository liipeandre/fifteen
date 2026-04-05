#ifndef MANIPARQUIVO_H_INCLUDED
#define MANIPARQUIVO_H_INCLUDED

#include "Interface.h"
#include "Tabuleiro.h"
#include <stdio.h>

//  funcao que salva a partida no arquivo.

void salvar_partida(Tabuleiro*);




//  uma funcao que só salva a matriz tabuleiro_jogo no arquivo.

void salvar_matriz_tabuleiro_jogo(FILE* arquivo, Tabuleiro* tab);




//  uma funcao que só salva a matriz tabuleiro_origianl no arquivo.

void salvar_matriz_tabuleiro_original(FILE*, Tabuleiro*);




// funcao que carrega a partida do arquivo.

void carregar_partida();




//  uma funcao que só carrega a matriz ntabuleiro_jogo do arquivo.

void carregar_matriz_tabuleiro_jogo(FILE* arquivo, Tabuleiro* tab);




//  uma funcao que só carrega a matriz tabuleiro_origianl do arquivo.

void carregar_matriz_tabuleiro_original(FILE* arquivo, Tabuleiro* tab);




#endif // MANIPARQUIVO_H_INCLUDED
