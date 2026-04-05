#ifndef INTERFACE_H
#define INTERFACE_H

#include "Tabuleiro.h"
#include "ManipArquivo.h"

#include <stdio.h>      // para printf() e scanf()
#include <string.h>     // para usar o fgets() e outras funcoes de strings.
#include <stdbool.h>    // para o tipo bool
#include <windows.h>    // para usar o comando system()




//  imprime o menu principal

void menu_principal();




//  le e armazena o valor na variavel que eu passei (já trata a entrada do teclado).

void ler_teclado(int* valor);




//  inicia e gerencia a partida, usando funções de apoio.

void inicia_jogo();




//  le o nome do jogador.

void ler_nome_jogador(Tabuleiro* tab);




//  le o nome do jogador.

void ler_nome_arquivo(char* nome_arquivo);




//  imprime o tabuleiro com o seu conteúdo

void imprime_tabuleiro(Tabuleiro* tab);




//  lê as coordenadas da peca que será movida para a casa vazia (linha e coluna da jogada).

void ler_jogada(Tabuleiro* tab);




//  imprime o menu durante a partida

void menu_partida(Tabuleiro*);




//  reinicia a partida

void reinicia_partida(Tabuleiro* tab);




//  imprime uma mensagem de vitória

void imprime_msg_vitoria();




#endif // INTERFACE_H
