#include "Tabuleiro.h"


void preenche_tabuleiro(Tabuleiro* tab){

    //  crio uma matriz , que será inicializada com a sequência ordenada.

    int matriz_sequencia_ordenada[4][4] = {{1, 2, 3, 4},{5, 6, 7, 8},{9, 10, 11, 12},{13, 14, 15, 0}};

    //  e uso a funcao memcpy(destino, origem, num_bytes), que copia um bloco de memória, para um outro.

    //  nesse caso vou copiar a matriz_sequencia ordenada para a matriz que está dentro do tab.

    //  obs:    sizeof(tab -> tabuleiro_jogo), indica quantos bytes vou copiar. nao pode ser maior que a variavel de destino, para não dar vazamento de memória.

    memcpy(tab -> tabuleiro_jogo, matriz_sequencia_ordenada, sizeof(tab -> tabuleiro_jogo));

    //  atualizo a posicao da casa vazia.

    tab ->linha_casa_vazia = 3;
    tab ->coluna_casa_vazia = 3;

    //  e inicializo o contador de jogadas para zero (0)

    tab ->jogadas_realizadas = 0;
}




void embaralhar_tabuleiro(Tabuleiro* tab){

    //  uso um contador de mexidas, para gerenciar o numero de mexidas necessárias.

    int contador_mexidas = 0;

    //  crio a semente para o rand(), que é o srand();

    srand((unsigned)time(NULL));

    //  enquanto não der 50 mexidas válidas, eu continuo no laço.

    while(contador_mexidas < 51){
        int jogada_valida = false;



        //  e armazeno a resultado do rand(), que será a peça escolhida.

        unsigned int peca_escolhida = (rand() % 4) + 1;

         /*
               1
             4 0 3      - é escolhida uma peça que está ao redor da casa vazia aleatóriamente e é feito a jogada ali.
               2
                        Obs1: ver o desenho ao lado.
                        Obs2: casa vazia é a casa 0.
        */

        if(peca_escolhida == 1){

            //  se o rand() retornar 1, a peça escolhida será a do norte, logo eu chamo a funcao que faz a jogada e pego o retorno dela.

            jogada_valida = verifica_jogada(tab, tab -> linha_casa_vazia + 1 , tab -> coluna_casa_vazia);
        }
        else if(peca_escolhida == 2){

            //  se o rand() retornar 2, a peça escolhida será a do sul, logo eu chamo a funcao que faz a jogada e pego o retorno dela.

            jogada_valida = verifica_jogada(tab, tab -> linha_casa_vazia - 1 , tab -> coluna_casa_vazia);
        }
        else if(peca_escolhida == 3){

            //  se o rand() retornar 3, a peça escolhida será a do leste, logo eu chamo a funcao que faz a jogada e pego o retorno dela.

            jogada_valida = verifica_jogada(tab, tab -> linha_casa_vazia , tab -> coluna_casa_vazia + 1);
        }
        else{

            //  se o rand() retornar 4, a peça escolhida será a do oeste, logo eu chamo a funcao que faz a jogada e pego o retorno dela.

            jogada_valida = verifica_jogada(tab, tab -> linha_casa_vazia, tab -> coluna_casa_vazia - 1);
        }

        //  se o retorno da funcao que verifica jogada for true, a jogada foi feita com sucesso e devo incrementar o contador de mexidas.

        if(jogada_valida == true){
            contador_mexidas++;
        }
    }

    //  no final, tenho que copiar a matriz que foi embaralhada para a matriz_original, que será salva para caso de o usuário recomeçar a partida.

    memcpy(tab -> tabuleiro_original , tab -> tabuleiro_jogo, sizeof(tab -> tabuleiro_original));
}




bool verifica_jogada(Tabuleiro* tab, int linha_peca_mexer, int coluna_peca_mexer){

    //  primeiro devemos testar se a casa está dentro do tabuleiro 4x4, se ela não estiver.

    if(linha_peca_mexer < 0 || linha_peca_mexer > 3 || coluna_peca_mexer < 0 || coluna_peca_mexer > 3){

        //  retorno false, pois a jogada não é válida.

        return false;
    }

    //  senao vamos fazer uma subtração das coordenadas da casa vazia com as da peca que eu vou mexer.

    //  a funcao abs() serve para eu ignorar o sinal (pois tanto faz a ordem da subtração, eu quero é o alcance da casa vazia para as outras).

    int resultado_linha = abs(linha_peca_mexer - (tab -> linha_casa_vazia));
    int resultado_coluna = abs(coluna_peca_mexer - (tab -> coluna_casa_vazia));

//  se o alcance da linha ou da coluna for maior que 1, é porque a casa que o usuário digitou não está ao lado da casa vazia.

    if(resultado_linha > 1 || resultado_coluna > 1){

        //  retorno false, pois a jogada não é válida.

        return false;
    }

//  se a casa estiver na diagonal, o resultado da linha será igual ao da coluna.

    if(resultado_linha == resultado_coluna){

        //  retorno false, pois a jogada não é válida.

        return false;
    }

//  se chegou até aqui é porque a casa é uma das quatro (norte, sul, leste e oeste) que estão ao redor da casa vazia, então eu só faço a troca da peça.

    troca_peca(&tab -> tabuleiro_jogo [linha_peca_mexer] [coluna_peca_mexer], &tab -> tabuleiro_jogo [tab -> linha_casa_vazia] [tab -> coluna_casa_vazia]);

//  atualizo as linha e colunas da casa vazia (a casa da peça que eu mexi estará vazia agora).

    tab -> linha_casa_vazia = linha_peca_mexer;
    tab -> coluna_casa_vazia = coluna_peca_mexer;

//  e retorno true, indicando que a jogada foi bem sucedida.

    return true;
}




void troca_peca(int* origem, int* destino){
//  aqui eu faço a troca da peça da origem pro destino.
//  O operador (*) asterisco, indica que a operação será na variavel que o ponteiro aponta.

//  o destino recebe a origem.

    *destino = *origem;

//  e a origem vira a casa vazia.

    *origem = 0;
}




bool verifica_fim_jogo (Tabuleiro* tab){

    //  crio uma matriz gabarito, que será inicializada com a sequência ordenada.

    int matriz_gabarito[4][4] = {{1, 2, 3, 4},{5, 6, 7, 8},{9, 10, 11, 12},{13, 14, 15, 0}};

    //  crio as variaveis que serão a linha e a coluna da matriz.

    int linha = 0;
    int coluna = 0;

//  percorro a matriz até o fim, comparando casa a casa.

    for(linha = 0; linha < 4; linha++){
        for(coluna = 0; coluna < 4; coluna++){

        //  se uma casa do tabuleiro estiver diferente do gabarito.

            if(tab ->tabuleiro_jogo[linha][coluna] != matriz_gabarito[linha][coluna]){

                //  retorno false, porque a matriz de jogadas não está igual ao gabarito.

                return false;
            }
        }
    }

    //  se a funcao chegou aqui é que todas as casa do tabuleiro estão iguais ao gabarito.
    //  entao a condicao de fim de jogo é válida, então retorno true.

    return true;
}
