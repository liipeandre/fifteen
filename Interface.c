#include "Interface.h"

void menu_principal(){

    //  aqui inicia o jogo com um menu principal.

    int opcao = 0;
    do{
        //  imprimo as opcoes

        system("cls");
        printf("Jogo do Quinze !!\n\n\n");
        printf ("1 - Iniciar Jogo \n");
        printf ("2 - Carregar Jogo Salvo \n");
        printf ("3 - Sair do Jogo \n\n");
        printf ("Digite uma Opcao: ");

        // leio a opcao do teclado

        ler_teclado(&opcao);

        //  se for 1, inicia uma nova partida

        if(opcao == 1){
            inicia_jogo();
        }

        //  se for 2, carrega uma partida salva

        if(opcao == 2){
            carregar_partida();
        }

        //  se for 3, sai do laço e volta pro main()
    }
    while(opcao != 3);

    //  forço a saída do programa, independente de estar em uma funcao

    exit(0);
}




void ler_teclado(int* valor){
    //  essa funcao faz a leitura do teclado com o tratamento de erro de leitura.

    //  declaro a variavel de teste de leitura.

    bool teste_leitura_invalida = 0;

    //  e caso o usuário digite um caracter inválido, o laço continua.

    do{
        //  o scanf() retorna false quando ele lê um dado inválido (ex: um acento ou uma letra).

        teste_leitura_invalida = scanf("%d", valor);

        //  limpo o buffer do teclado, para tirar os caracteres que ainda estão lá, caso sejam inválidos.

        fflush(stdin);

        //  enquanto o teste for falso, eu repito a leitura até o usuário digitar algo válido.

    }while(teste_leitura_invalida == false);
}




void inicia_jogo(){
    //  crio a variavel tabuleiro, que armazenará tudo referente a partida.

    Tabuleiro tabuleiro;

    //  chamo a funcao que lê o nome do jogador

    ler_nome_jogador(&tabuleiro);

    //  depois a funcao que preenche o tabuleiro com a sequencia ordenada

    preenche_tabuleiro(&tabuleiro);


    //  depois chamo a funcao que embaralha o tabuleiro.

      embaralhar_tabuleiro(&tabuleiro);

    //  e enquanto a condicao de fim de jogo nao for alcançada, eu repito o que está no laço.

    do{
        //  imprimo o tabuleiro na tela.

        imprime_tabuleiro(&tabuleiro);

        //  leio a jogada (que será validada dentro dessa funcao).

        ler_jogada(&tabuleiro);
    }
    while(verifica_fim_jogo(&tabuleiro) == false);

    //  quando o laço acima acabar, o jogo terminou e imprimo a mensagem de vitoria.

    imprime_msg_vitoria();

    //  e volto para o menu principal

    menu_principal();
}




void ler_nome_jogador(Tabuleiro* tab){

    //  limpa a tela

    system("cls");

    // imprime mensagem na tela.

    printf("Digite Seu Nome: ");

    //  leio o nome do jogador do teclado (que é uma string).

    fgets(tab ->nome_do_jogador, sizeof(tab ->nome_do_jogador), stdin);
    fflush(stdin);
}




void imprime_tabuleiro(Tabuleiro* tab){

    //  declaro duas variaveis contadoras

    int numero_linha = 0;   // essa será o numero da linha na matriz
    int contador = 0;       // essa gerenciará a repetição do laço

    //  limpo a tela antes de escrever nela.

    system("cls");

    //  isso é para centralizar o tabuleiro  na tela.

    printf("\n\n\n\n");
    printf("\t\t\t     0    1    2    3  \n");

    //  vou repetir 9 vezes esse laço.

    for(contador = 0; contador < 9; contador++){

        if(contador % 2 == 0){

            //  quando o contador for par, vou imprimir a linha abaixo.

            printf("\t\t\t  +----+----+----+----+\n");
        }
        else{
            //  quando for impar eu imprimo os dados da matriz.

            //  primeiro o numero da linha

            printf("\t\t\t%d ", numero_linha);

            //  depois o conteúdo de cada coluna daquela linha da matriz

            //  1 coluna


            /*

            para imprimir ele utiliza 2 formatações:


            tab->tabuleiro_jogo[numero_linha][0] != 0?      ->  testo se o conteúdo da posicao não é o zero (casa vazia).


                    Se for verdadeiro eu coloco a seguinte formatação com a máscara de inteiro (%d):                            "| %02d "

                    Se for falso eu coloco a seguinte formatação sem a máscara %d, logo ele vai imprimir apenas espaço:            "|    "



            */

            printf(tab -> tabuleiro_jogo[numero_linha][0] != 0? "| %02d " : "|    ", tab->tabuleiro_jogo[numero_linha][0]);

            //  2 coluna

            printf(tab -> tabuleiro_jogo[numero_linha][1] != 0? "| %02d " : "|    ", tab->tabuleiro_jogo[numero_linha][1]);

            //  3 coluna

            printf(tab -> tabuleiro_jogo[numero_linha][2] != 0? "| %02d " : "|    ", tab->tabuleiro_jogo[numero_linha][2]);

            //  4 e ultima coluna

            printf(tab -> tabuleiro_jogo[numero_linha][3] != 0? "| %02d " : "|    ", tab->tabuleiro_jogo[numero_linha][3]);

            //  dou a quebra de linha no final para que ele não imprima a próxima linha da matriz ao lado da atual.

            printf("|\n");

            //  e incremento o numero_linha, para que da próxima vez eu imprima a próxima linha da matriz.

            numero_linha++;
        }
    }
}




void ler_jogada(Tabuleiro* tab){
        // imprimo a mensagem.

        printf("\n\nDigite as coordenadas da peca que sera movida para a Casa Vazia \n");
        printf("Digite -1 para abrir o menu da partida: ");

        //  declaro as variaveis que armazenarão as coordenadas da jogada.

        int linha_casa_mover = 0;
        int coluna_casa_mover = 0;

        //  leio a linha e a coluna do teclado.

        ler_teclado(&linha_casa_mover);
        ler_teclado(&coluna_casa_mover);

        //  se um dos valores lidos for -1, ele abre o menu da partida

        if(linha_casa_mover == -1 || coluna_casa_mover == -1){
            menu_partida(tab);
        }

        //   senao chamo a funcao que verifica a jogada.

        else if(verifica_jogada(tab , linha_casa_mover, coluna_casa_mover) == false){

            //  se a jogada for inválida (verifica_jogada() == false), eu imprimo uma mensagem de jogada inválida.

            system("cls");
            printf("\n\n\n\n\n\n\n\n\n\n\n\t\t  Jogada Invalida, Tente Novamente !!\n");
            printf("\t\t  Pressione Qualquer Tecla Para Continuar !! \n");

            //  essa funcao serve para parar a execução até que uma tecla seja pressionada (como o enter por exemplo).

            getchar();
        }

        // se a jogada for bem sucedida

        else{

            //  imcremento o contador de jogadas.

            tab ->jogadas_realizadas++;
        }
}




void menu_partida(Tabuleiro* tab){

    //  imprimo as opcoes

    system("cls");

    printf("Jogo Pausado !!\n\n");
    printf ("1 - Reiniciar Partida\n");
    printf ("2 - Salvar Partida \n");
    printf ("3 - Voltar a Partida\n");
    printf ("4 - Voltar ao Menu Principal\n");
    printf ("5 - Sair do Jogo \n\n");
    printf ("Digite uma Opcao: ");

    int opcao = 0;

    //leio a opcao do teclado

    ler_teclado(&opcao);

    //  se a opcao for 1, eu reinicio a partida

    if(opcao == 1){
        reinicia_partida(tab);
    }

    //  se a opcao for 2, eu salvo a partida

    if(opcao == 2){
        salvar_partida(tab);
    }
    // se a opcao for 3, eu volto para a funcao que chamou (ler_jogada)

    if(opcao == 3){
        return;
    }

    // se for 4, eu volto ao menu principal;

    if(opcao == 4){
         menu_principal();
    }

    // se for 5, eu forço a saida do programa usando o comando exit(0);

    if(opcao == 5){
        exit(0);
    }
}




void reinicia_partida(Tabuleiro* tab){
    //  copio o conteudo do tabuleiro original para o tabuleiro da partida

    memcpy(tab -> tabuleiro_jogo, tab -> tabuleiro_original, sizeof(tab -> tabuleiro_jogo));

    //  reseto o contador de jogadas

    tab -> jogadas_realizadas = 0;



    int linha = 0;
    int coluna = 0;

    //  varro a matriz para procurar e atualizar a posicao da casa vazia.

    for(linha = 0; linha < 4; linha++){
        for(coluna = 0; coluna < 4; coluna++){

            //  se eu achei a casa vazia (casa com o zero)

            if(tab ->tabuleiro_jogo[linha][coluna] == 0){

                //  eu atualizo as variaveis linha e coluna que estão dentro da variavel tab.

                tab ->linha_casa_vazia = linha;
                tab ->coluna_casa_vazia = coluna;

                //  e retorno daqui.

                return;
            }
        }
    }

    //  e saio da funcao, que leva de volta ao tabuleiro.
}




void imprime_msg_vitoria(){

    //  limpo a tela

    system("cls");

    //  e apenas parabenizo o usuário.

            printf("\n\n\n\n\n\n\n\n\n\n\n\t\t  Parabens, Voce Venceu !!\n");
            printf("\t\t  Pressione Qualquer Tecla Para Continuar !! \n");

    //  essa funcao serve para parar a execução até que uma tecla seja pressionada (como o enter por exemplo).

    getchar();
}
