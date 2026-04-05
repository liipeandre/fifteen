#include "ManipArquivo.h"

void salvar_partida(Tabuleiro* tab){
    //  abro o arquivo no modo de sobrescrita ("w") usando o fopen()

    FILE* arquivo = fopen("PartidaSalva.sav", "w");

    //  testo se a abertura foi feita corretamente, se sim, eu posso escrever no arquivo.

    if(arquivo != NULL){

        //  escrevo o nome do jogador usando fprintf()

        fputs("Nome do Jogador: \n", arquivo);
        fputs(tab -> nome_do_jogador, arquivo);

        //  escrevo o contador de jogadas no arquivo.

        fputs("\nJogadas Realizadas: \n", arquivo);
        fprintf(arquivo, "%d\n\n", tab -> jogadas_realizadas);

        //  e salvo as duas matrizes no arquivo.

        //  primeiro a tabuleiro jogo

        fputs("Tabuleiro Jogo\n\n", arquivo);
        salvar_matriz_tabuleiro_jogo(arquivo, tab);

        //  depois a tabuleiro original

        fputs("\nTabuleiro Original\n\n", arquivo);
        salvar_matriz_tabuleiro_original(arquivo, tab);
    }
    else{
        system("cls");
        printf("Erro ao Abrir Arquivo !!");
        printf("Pressione qualquer tecla para continuar");
        getchar();
    }

    //  no final fecho o arquivo.

    fclose(arquivo);
    arquivo = NULL;
}




void salvar_matriz_tabuleiro_jogo(FILE* arquivo, Tabuleiro* tab){
    //  declaro um contador de linhas

    int linha = 0;

    //  vou percorrer a matriz e escrevendo no arquivo, cada linha da matriz
    //  laço vai até 3, porque minha matriz tem 4 linhas (contando o 0(zero)).

    for(linha = 0; linha < 4; linha++){
        fprintf(arquivo, "%d %d %d %d\n", tab -> tabuleiro_jogo[linha][0], tab -> tabuleiro_jogo[linha][1], tab -> tabuleiro_jogo[linha][2], tab -> tabuleiro_jogo[linha][3]);
    }
}




void salvar_matriz_tabuleiro_original(FILE* arquivo, Tabuleiro* tab){
    //  declaro um contador de linhas

    int linha = 0;

    //  vou percorrer a matriz e escrevendo no arquivo, cada linha da matriz
    //  laço vai até 3, porque minha matriz tem 4 linhas (contando o 0(zero)).

    for(linha = 0; linha < 4; linha++){
        fprintf(arquivo, "%d %d %d %d\n", tab -> tabuleiro_original[linha][0], tab -> tabuleiro_original[linha][1], tab -> tabuleiro_original[linha][2], tab -> tabuleiro_original[linha][3]);
    }
}




void carregar_partida(){
    Tabuleiro tab;

    // abro o aruivo no modo de leitura ("r")

    FILE* arquivo = fopen("PartidaSalva.sav", "r");

    //  testo se a abertura foi feita corretamente, se sim, eu posso ler do arquivo.

    if(arquivo != NULL){

            //  crio uma string que vai armazena as linha que eu nao quero.

            char lixo[20];

            //  vou ler linha a linha.

            //  linha 1 (lixo)

            fgets(lixo, 20, arquivo);

            //  linha 2 (nome_do_jogador)

            fgets(tab.nome_do_jogador, 20, arquivo);

            //  linhas 3 e 4 (lixo)

            fgets(lixo, 20, arquivo);
            fgets(lixo, 20, arquivo);

            //  linha 5 (jogadas_realizadas

            fscanf(arquivo, "%d", &tab.jogadas_realizadas);

            //  linhas 6, 7 e 8(lixo)

            fgets(lixo, 20, arquivo);
            fgets(lixo, 20, arquivo);
            fgets(lixo, 20, arquivo);

            //  linha 9 até a linha 12 (tabuleiro_jogo)

            carregar_matriz_tabuleiro_jogo(arquivo, &tab);

            //  linhas 13, 14 e 15(lixo)

            fgets(lixo, 20, arquivo);
            fgets(lixo, 20, arquivo);
            fgets(lixo, 20, arquivo);

            //  linha 16 até a linha 19 (tabuleiro_jogo)

            carregar_matriz_tabuleiro_original(arquivo, &tab);
    }
    else{
        system("cls");
        printf("Erro ao Abrir Arquivo !!");
        printf("Pressione qualquer tecla para continuar");
        getchar();
    }

    //  no final fecho o arquivo.

    fclose(arquivo);
    arquivo = NULL;

    //  e inicio a partida que fica no loop abaixo

    do{
        //  imprimo o tabuleiro na tela.

        imprime_tabuleiro(&tab);

        //  leio a jogada (que será validada dentro dessa funcao).

        ler_jogada(&tab);
    }
    while(verifica_fim_jogo(&tab) == false);

    //  quando o laço acima acabar, o jogo terminou e imprimo a mensagem de vitoria.

    imprime_msg_vitoria();

    //  e volto para o menu principal

    menu_principal();
}




void carregar_matriz_tabuleiro_jogo(FILE* arquivo, Tabuleiro* tab){
    //  declaro um contador de linhas

    unsigned int linha = 0;

    //  e leio todas as linhas do arquivo e escrevo na matriz.

    for(linha = 0; linha < 4; linha++){
        fscanf(arquivo, "%d %d %d %d", &tab ->tabuleiro_jogo[linha][0], &tab ->tabuleiro_jogo[linha][1], &tab ->tabuleiro_jogo[linha][2], &tab ->tabuleiro_jogo[linha][3]);

        //  e depois varro essa linha para achar o zero, se existir (casa vazia), para atualizar a referência que fica na variavel tabuleiro.

        //  declaro um indice para a coluna
        int coluna = 0;

        //  percorro todas as posicoes dessa linha da matriz

        for(coluna = 0; coluna < 4; coluna++){

            //  se o zero (0) for encontrado
            if(tab ->tabuleiro_jogo[linha][coluna] == 0){

                // preencho as variaveis abaixo com a posicao onde ele foi encontrado.

                tab ->linha_casa_vazia = linha;
                tab ->coluna_casa_vazia = coluna;
            }
        }
    }
}




void carregar_matriz_tabuleiro_original(FILE* arquivo, Tabuleiro* tab){
    //  declaro um contador de linhas

    unsigned int linha = 0;

    //  e leio todas as linhas do arquivo e escrevo na matriz.

    for(linha = 0; linha < 4; linha++){
        fscanf(arquivo, "%d %d %d %d", &tab ->tabuleiro_original[linha][0], &tab ->tabuleiro_original[linha][1], &tab ->tabuleiro_original[linha][2], &tab ->tabuleiro_original[linha][3]);
    }
}




