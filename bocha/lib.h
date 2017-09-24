#include <stdlib.h>
#include <ctype.h>
#define TAMANHO 10
#include <windows.h>
#include <math.h>
void start_screen();
void start_game();
void lanca_bolim();
void mostra_cancha();
void inicializa_cancha();
int calcula_erro(int linha_col);
void partida();
char *jogada(char jogador);
int valida_jogada(char jogada[3]);
void lanca_bocha(char jogador, int row, int col);
void colisao_tangente(int row, int col);
int calcula_pontos(char jogador);
void colisao_direta(int row, int col, char jogador);
void movimentar_colisao_direta(char bocha, int start_row, int end_row, int col);
void vai_dois_volta_um(char bocha, int start_row, int end_row, int col);

/*DECLARA A CANCHA GLOBAL*/
char cancha[TAMANHO][TAMANHO];
char alfabeto[TAMANHO];
char vazio = '-';
int testa_cima = 1, testa_baixo = 1;
int row_original, col_original;


void start_screen() {
    system("cls");
    printf("\n\n\n");
    printf("%25c****************************\n", ' ');
    printf("%25c*                          *\n",' ');
    printf("%25c*      **************      *\n", ' ');
    printf("%25c*      * BOCHA 2017 *      *\n", ' ');
    printf("%25c*      **************      *\n", ' ');
    printf("%25c*                          *\n", ' ');
    printf("%25c****************************\n", ' ');
    printf("\n\n");
    printf("%32c1. NOVO JOGO\n",' ');
    printf("%32c2. SAIR\n",' ');
}

void start_game()  {

    system("cls");
    int i;


    /*Inicializa o alfabeto permitido para a cancha*/
    for(i = 65; i < 65 + TAMANHO; i++) {
        alfabeto[i - 65] = (char)i;
    }

    inicializa_cancha();
    lanca_bolim();
    partida();
    system("pause");


}



void lanca_bolim() {
    int col = 0, row = 0;
    /*CALCULA ONDE O BOLIM SERÁ JOGADO*/
    while(col > TAMANHO - 2 || col < 1)  {
        col = rand() % TAMANHO;
    }
    while(row < TAMANHO/3 || row >= 2*TAMANHO/3) {
        row = rand() % TAMANHO;
    }
    /*ANIMAÇÃO*/
    int i;
    char temp;

    for(i = TAMANHO - 1; i >= row; i--) { /*Começa da última linha e vai subindo até a linha escolhida*/
        system("cls");
        mostra_cancha();
        Sleep(300);
        temp = cancha[i][col];
        cancha[i][col] = 'X';
        cancha[i + 1][col] = temp;
    }
    mostra_cancha();




}

void mostra_cancha() {
    system("cls");
    int i, j;
    printf("\n\n");
    printf("%25c", ' ');
    /*Mostra as letras*/
    for(i = 0; i < TAMANHO; i++) {
        printf("%3c", 65 + i);
    }
    printf("\n\n");
    for(i = 0; i < TAMANHO; i++) {
        printf("%22d%3c", 10 - i, ' ');
        for(j = 0; j < TAMANHO; j++) {
            printf("%3c", cancha[i][j]);
        }
        printf("\n");
    }


    printf("\n");


}

void inicializa_cancha() {
    int i, j;
    for(i = 0; i < TAMANHO; i++) {
        for(j = 0; j < TAMANHO; j++) {
            cancha[i][j] = vazio;
        }
    }
}




/***********************CHAMA VÁRIAS OUTRAS, PODE-SE DIZER QUE É A PRINCIPAL*****************************************/
void partida() {
    //TODO
    int duracao = 8, jogadas = 0;
    int pontos_A = 0, pontos_B = 0, jogadas_A = 0, jogadas_B = 0;
    char *alvo; /*É UM PONTEIRO, OU SEJA: RECEBE ENDEREÇO PARA UMA VARIÁVEL DE TIPO CHAR*/


    char jogador_atual = 'B';
    while(jogadas < duracao) {
        /*DEFINE O JOGADOR ATUAL*/
        if(jogador_atual == 'B') {
            jogador_atual = 'A';
            jogadas_A++;
        }else {
            jogador_atual = 'B';
            jogadas_B++;
        }

        alvo = jogada(jogador_atual); /*RECEBE UM ENDEREÇO*/

        col_original = alvo[0] - 65;/*COLUNA: CONVERTE LETRA PARA NUMERO INT A = 0, B = 1*/
        if(strlen(alvo) == 3) {
            row_original = 0 + (alvo[2] - '0'); /*JA VALIDOU E DEU 10*/

        }else {
            row_original = TAMANHO - (alvo[1] - '0'); /*LINHA: CONVERTE CARACTERE DIGITO PARA INT '1' = 1*/

        }

        printf("O jogador acertou no %s\n", alvo);
        lanca_bocha(jogador_atual, row_original, col_original);
        system("pause");
        mostra_cancha();
        pontos_A = calcula_pontos('A');
        pontos_B = calcula_pontos('B');
        printf("%28cEquipe A%10cEquipe B\n", ' ', ' ');
        printf("%10cPontos:%17c %d%17c%d\n",' ',' ', pontos_A, ' ', pontos_B);
        printf("%10cJogadas restantes:%7c%d%17c%d\n", ' ', ' ', duracao/2 - jogadas_A, ' ', duracao/2 - jogadas_B);
        jogadas++;
        free(alvo);
    }
    /*Fim do jogo, mostra vencedor*/
    if(pontos_A > pontos_B) {
        printf("Vencedor: equipe A!\n");
    }else if(pontos_A < pontos_B) {
        printf("Vencedor: equipe B!\n");
    }else {
        printf("Empate!\n");
    }


}
/************************************************************************************************************************/

char *jogada(char jogador) {

    char *jogada = malloc(sizeof(char) * 4); /*O PONTEIRO RECEBE UM ENDEREÇO COM O TAMANHO DE 3 BYTES*/
    int pedir = 1;
    while(pedir) {
        printf("\nJogador %c\n", jogador);
        printf("Selecione onde deseja jogar\n");
        fflush(stdin);
        gets(jogada);


        jogada[0] = toupper(jogada[0]);

        if(valida_jogada(jogada)) {
            pedir = 0;

        } else {
            system("pause");
            mostra_cancha();
        }

    }
    return jogada;


}

int valida_jogada(char jogada[4]) {

    /*Calcula erro*/
    int erro, numero;
    jogada[0] = jogada[0] + calcula_erro(2); /*Calcula erro da coluna*/

    if(strlen(jogada) == 3) {


        erro = calcula_erro(1);

        numero = (jogada[1] - '0') * 10 + (jogada[2] - '0') + erro;
        if(numero < 10) {
            jogada[2] = '\0';
            jogada[1] = numero + '0';
        }



    }else if(strlen(jogada) == 2) {


        erro = calcula_erro(1);

        numero = (jogada[1] - '0') + erro;
        if(numero < 10) {

            jogada[2] = '\0';
            jogada[1] = numero + '0';

        }
    }


    /*TESTES*/
    if(!isalpha(jogada[0])) {
        printf("%s:  primeiro digito não é letra. Joque novamente.\n", jogada);
        return 0;
    }
    if(jogada[0] < alfabeto[0] || jogada[0] > alfabeto[TAMANHO - 1]) {
        printf("%s: jogada fora dos limites laterais. Jogue novamente.\n", jogada);
        return 0;
    }
    if(!isdigit(jogada[1])) {
        printf("%s: segundo dígito não é número. Jogue novamente.\n", jogada);
        return 0;
    }
    if(numero  <= 0 || numero > TAMANHO) {
        printf("%c%d: jogada fora do limite vertical. Jogue novamente.\n", jogada[0], numero);
        return 0;
    }


    return 1;
}

int calcula_erro(int linha_col) {
    /*TESTE TESTE TESTE*/
    return 0;
    /*TESTE TESTE TESTE*/
    /*linha_col == 1, erro de linha*/
    /*linha_col == 2, erro de coluna*/
    int erro_linha[] = {-2, -1, 0, 1, 2};
    int erro_coluna[] = {-1, 0, 1};
    if(linha_col == 1) {
        return erro_linha[rand() % 5];
    } else if (linha_col == 2){
        return erro_coluna[rand() % 3];
    } else {
        return 0;
    }

}


/*VAI RECEBER O row_original e o col_original, que é onde a bocha atingiu*/
void lanca_bocha(char jogador, int row, int col) {

    testa_cima = 1;
    testa_baixo = 1;
    /**********************/
    /*SE CAIR EM LUGAR VAZIO*/
    if(cancha[row][col] == vazio) {
        cancha[row][col] = jogador;



    } else {
        /*CAIU EM CIMA DE OUTRO OBJETO*/
        /*PODE ALTERAR O ROW E COL ORIGINAIS*/
        colisao_direta(row, col, jogador);


    }


    /*TESTAR COLISOES TANGENTES*/
    /*colisao_tangente(row_original, col_original);*/





}

void colisao_tangente(int row, int col) {

    /*--------ESQUERDA----------*/
    /*PARA MOVER A BOCHA À ESQUERDA, A BOCHA LANÇADA DEVE TER CAÍDO NA COLUNA 2 OU MAIOR*/
    if(col >= 2) {
        /*CHECAR SE TEM ALGO À ESQUERDA DA BOCHA LANÇADA (MAS NÃO O BOLIM)*/
        if(cancha[row][col - 1] == 'A' || cancha[row][col - 1] == 'B') {
            /*HÁ UM OBJETO IMEDIATAMENTE À ESQUERDA DE ONDE CAIU A BOCHA LANÇADA*/
            /*CHECAR SE O LOCAL MAIS ESQUERDA ESTÁ VAZIO*/
            if(cancha[row][col - 2] == vazio) {
                /*MOVER UMA CASA À ESQUERDA*/
                cancha[row][col - 2] = cancha[row][col - 1];
                cancha[row][col - 1] = vazio;
            }
        }
    }
    /*-------------------------------*/


    /*-----------DIREITA-----------*/
    /*CHECAR LIMITE À DIREITA DO LOCAL ONDE CAIU A BOCHA LANÇADA*/
    if(col  < TAMANHO - 2) {
        /*CHECAR SE TEM ALGO À DIREITA DA BOCHA LANÇADA*/
        if(cancha[row][col + 1] == 'A' || cancha[row][col + 1] == 'B') {
            /*HÁ UM OBJETO IMEDIATAMENTE À DIREITA DE ONDE CAIU A BOCHA LANÇADA*/
            /*CHECAR SE O LOCAL MAIS À DIREITA ESTÁ VAZIO*/
            if(cancha[row][col + 2] == vazio) {
                /*MOVER UMA CASA À DIREITA*/
                cancha[row][col + 2] = cancha[row][col + 1];
                cancha[row][col + 1] = vazio;
            }
        }
    }
    /*-------------------------------*/


    /*ACIMA*/
    /*CHECAR LIMITE ACIMA DE ONDE CAIU A BOCHA LANÇADA*/
    if(row >= 2 && testa_cima) {
        /*CHECAR SE TEM ALGO ACIMA DE ONDE CAIU A BOCHA (NÃO O BOLIM)*/
        if(cancha[row - 1][col] == 'A' || cancha[row - 1][col] == 'B') {
            /*HÁ UMA BOCHA ACIMA DE ONDE CAIU A BOCHA LANÇADA*/
            /*CHECAR SE HÁ ESPAÇO PARA MOVER*/
            if(cancha[row - 2][col] == vazio) {
                /*MOVER UMA CASA ACIMA*/
                cancha[row - 2][col] = cancha[row - 1][col];
                cancha[row - 1][col]= vazio;
            }
        }
    }
    /*----------------------------------------------*/

    /*ABAIXO*/
    /*CHECAR LIMITE ABAIXO DE ONDE CAIU A BOCHA LANÇADA*/
    if(row < TAMANHO  - 2 && testa_baixo) {
        /*CHECAR SE HÁ OUTRA BOCHA ABAIXO DE ONDE CAIU A BOCHA LANÇADA*/
        if(cancha[row + 1][col] == 'A' || cancha[row + 1][col] == 'B') {
            /*HÁ UMA BOCHA ABAIXO DE ONDE CAIU A BOCHA LANÇADA*/
            /*CHECAR SE O ESPAÇO ESTÁ LIVRE PARA MOVER*/
            if(cancha[row + 2][col] == vazio) {
                /*MOVER UMA CASA ABAIXO*/
                cancha[row + 2][col] = cancha[row + 1][col];
                cancha[row + 1][col] = vazio;
            }
        }
    }
    /*---------------------------------------------*/

    /*ACIMA-ESQUERDA*/
    /*CHECAR LIMITE ACIMA-ESQUERDA DE ONDE CAIU A BOCHA LANÇADA*/
    if(row >= 2 && col >= 2) {
        /*CHECAR SE HÁ ALGUMA BOCHA ACIMA E À ESQUERDA*/
        if(cancha[row - 1][col - 1] == 'A' || cancha[row - 1][col - 1] == 'B' ) {
            /*HÁ UMA BOCHA ACIMA E À ESQUERDA*/
            /*CHECAR SE HÁ ESPAÇO PARA ELA SER MOVIDA*/
            if(cancha[row - 2][col - 2] == vazio) {
                /*MOVER ACIMA E À ESQUERDA*/
                cancha[row - 2][col - 2] = cancha[row - 1][col - 1];
                cancha[row - 1][col - 1] = vazio;
            }
        }
    }
    /*---------------------------------------------*/


    /*ACIMA-DIREITA*/
    /*CHECAR LIMITE ACIMA-DIREITA DE ONDE CAIU A BOCHA LANÇADA*/
    if(row >= 2 && col < TAMANHO - 2) {
        /*CHECAR SE HÁ UMA BOCHA ACIMA E À DIREITA*/
        if(cancha[row - 1][col + 1] == 'A' || cancha[row - 1][col + 1] == 'B') {
            /*HÁ UMA BOCHA ACIMA E À DIREITA*/
            /*VERIFICA SE HÁ ESPAÇO PARA MOVER*/
            if(cancha[row - 2][col + 2] == vazio) {
                /*MOVER ACIMA E À DIREITA*/
                cancha[row - 2][col + 2] = cancha[row - 1][col + 1];
                cancha[row - 1][col + 1] = vazio;
            }
        }
    }
    /*--------------------------------------------------*/

    /*ABAIXO-ESQUERDA*/
    /*CHECAR LIMITE ABAIXO-ESQUERDA DE ONDE CAIU A BOCHA LANÇADA*/
    if(row < TAMANHO - 2 && col >=2) {
        /*CHECAR SE HÁ BOCHA ABAIXO E À ESQUERDA*/
        if(cancha[row + 1][col - 1] == 'A' || cancha[row + 1][col - 1] == 'B') {
            /*HÁ BOCHA ABAIXO E À ESQUERDA*/
            /*VERIFICA SE HÁ ESPAÇO PARA MOVER*/
            if(cancha[row + 2][col - 2] == vazio) {
                /*MOVER ABAIXO E À ESQUERDA*/
                cancha[row + 2][col - 2] = cancha[row + 1][col - 1];
                cancha[row + 1][col - 1] = vazio;
            }
        }
    }
    /*----------------------------------------------*/


    /*ABAIXO-DIREITA*/
    /*CHECAR LIMITE ABAIXO-DIREITA DE ONDE CAIU A BOCHA LANÇADA*/
    if(row < TAMANHO - 2 && col < TAMANHO - 2) {
        /*CHECAR SE HÁ BOCHA ABAIXO E À DIREITA*/
        if(cancha[row + 1][col + 1] == 'A' || cancha[row + 1][col + 1] == 'B') {
            /*HÁ BOCHA ABAIXO E À DIREITA*/
            /*VERIFICA SE HÁ ESPAÇO PARA MOVER*/
            if(cancha[row + 2][col + 2] == vazio) {
                /*MOVER ABAIXO E À DIREITA*/
                cancha[row + 2][col + 2] = cancha[row + 1][col + 1];
                cancha[row + 1][col + 1] = vazio;
            }
        }
    }
    /*----------------------------------------------*/




}


void colisao_direta(int row, int col, char jogador) {

   /*PRIMEIRO TESTE: VERIFICAR SE O LOCAL DE COLISÃO ESTÁ NA LINHA 3 OU MAIOR(MAIS PARA BAIXO NA MATRIZ) */
   if(row >= 3) {
        /*3 CASAS ACIMA VAZIAS*/
        if( (cancha[row - 1][col] == vazio) && (cancha[row - 2][col] == vazio) && (cancha[row - 3][col] == vazio) ) {
            cancha[row - 3][col] = cancha[row][col];
            cancha[row][col] = jogador;   /*OK*/
        }else {
            /*UMA OU MAIS CASAS OCUPADAS*/

            /*PRIMEIRA CASA OCUPADA*/
            if( (cancha[row - 1][col] != vazio) && (cancha[row - 2][col] == vazio) && (cancha[row - 3][col] == vazio) ) {
                cancha[row - 3][col] = cancha[row - 1][col];
                cancha[row - 1][col] = cancha[row][col];
                cancha[row][col] = jogador; /*OK*/
            }
            /*SEGUNDA CASA OCUPADA*/
            else if( (cancha[row - 1][col] == vazio) && (cancha[row - 2][col] != vazio) && (cancha[row - 3][col] == vazio) ) {
                cancha[row - 3][col] = cancha[row - 2][col];
                cancha[row - 2][col] = cancha[row][col];
                cancha[row][col] = jogador; /*OK*/
            }
            /*TERCEIRA CASA OCUPADA*/
            else if( (cancha[row - 1][col] == vazio) && (cancha[row - 2][col] == vazio) && (cancha[row - 3][col] != vazio) ) {
                /*SE TIVER ESPAÇO VAZIO ACIMA DA TERCEIRA CASA*/
                if(cancha[row - 4][col] == vazio && row > 3) {
                    cancha[row - 4][col] = cancha[row - 3][col];
                    cancha[row - 3][col] = cancha[row][col];
                    cancha[row][col] = jogador; /*OK*/
                }else {
                    /*SENÃO MOVE SÓ DUAS VEZES E PÁRA*/
                    cancha[row - 2][col] = cancha[row][col];
                    cancha[row][col] = jogador; /*OK*/
                }

            }
            /*PRIMEIRA E SEGUNDA CASAS OCUPADAS*/
            else if( (cancha[row - 1][col] != vazio) && (cancha[row - 2][col] != vazio) && (cancha[row - 3][col] == vazio) ) {
                cancha[row - 3][col] = cancha[row - 2][col];
                cancha[row - 2][col] = cancha[row - 1][col];
                cancha[row - 1][col] = cancha[row][col];
                cancha[row][col] = jogador; /*OK*/
            }
            /*PRIMEIRA E TERCEIRA CASAS OCUPADAS*/
            else if( (cancha[row - 1][col] != vazio) && (cancha[row - 2][col] == vazio) && (cancha[row - 3][col] != vazio) ) {
                cancha[row - 2][col] = cancha[row - 1][col];
                cancha[row - 1][col] = cancha[row][col];
                cancha[row][col] = jogador;
            }
            /*SEGUNDA E TERCEIRA CASAS OCUPADAS*/
            else if( (cancha[row - 1][col] == vazio) && (cancha[row - 2][col] != vazio) && (cancha[row - 3][col] != vazio) ) {
                cancha[row - 1][col] = cancha[row][col];
                cancha[row][col] = jogador;
            }
            /*TODAS AS CASAS ACIMA OCUPADAS*/
            else {
                /*SE HOUVER ESPAÇO UMA CASA ABAIXO*/
                if(row < TAMANHO - 1) {
                    /*SE O ESPAÇO ESTIVER VAZIO*/
                    if(cancha[row + 1][col] == vazio) {
                        cancha[row + 1][col] = jogador;
                    }else {
                        /*CHECAR DIAGONAIS INFERIORES*/
                        if(cancha[row + 1][col - 1] == vazio && col > 0) {
                           cancha[row + 1][col - 1] = jogador;
                        }else if(cancha[row + 1][col + 1] == vazio && col < TAMANHO - 1) {
                            cancha[row + 1][col + 1] = jogador;
                        }else {
                            /*CHECAR OS LADOS*/
                            if(cancha[row][col - 1] == vazio && col > 0) {
                                cancha[row][col - 1] = jogador;
                            }else if(cancha[row][col + 1] == vazio && col < TAMANHO - 1) {
                                cancha[row][col + 1] = jogador;
                            }else if(cancha[row][col - 1] == vazio && col > 0) {
                                cancha[row][col - 1] = jogador;
                            }else {
                                /*CHECAR DIAGONAIS SUPERIORES*/
                                if(cancha[row - 1][col - 1] == vazio && col > 0) {
                                    cancha[row - 1][col - 1] = jogador;
                                }else if(cancha[row - 1][col + 1] == vazio && col < TAMANHO - 1) {
                                    cancha[row - 1][col + 1] = jogador;
                                }else {
                                    /*CHECAR ALGUMAS CASAS ALEATÓRIAS*/
                                    if(cancha[row][col - 2] == vazio && col >= 2) {
                                        cancha[row][col - 2] = jogador;
                                    }else if(cancha[row - 1][col - 2] == vazio && col >= 2) {
                                        cancha[row - 1][col - 2] = jogador;
                                    }else if(cancha[row][col + 2] == vazio && col < TAMANHO - 2) {
                                        cancha[row][col + 2] = jogador;
                                    }else if(cancha[row - 1][col + 2] == vazio && col < TAMANHO - 2) {
                                        cancha[row - 1][col + 2] = jogador;
                                    }
                                }
                            }
                        }
                    }
                }else {
                    /*CHECAR NOS LADOS*/
                    if(cancha[row][col - 1] == vazio && col > 0) {
                        cancha[row][col - 1] = jogador;
                    }else if(cancha[row][col + 1] == vazio && col < TAMANHO - 1) {
                        cancha[row][col + 1] = jogador;
                    }else {
                        /*CHECAR DIAGONAIS SUPERIORES*/
                        if(cancha[row - 1][col - 1] == vazio && col > 0) {
                            cancha[row - 1][col - 1] = jogador;
                        }else if(cancha[row - 1][col + 1] == vazio && col < TAMANHO - 1) {
                            cancha[row - 1][col + 1]= jogador;
                        }
                    }
                }
            }
        }
   }else if(row == 2) {

   }else if(row == 1) {

   }else if(row == 0) {

   }
}

int calcula_pontos(char jogador) {

    int i, j, bolim_row, bolim_col, achou = 0, pontuacao = 0, distancia;
    /*GUARDAR POSIÇÃO DO BOLIM*/
    for(i = 0; i < TAMANHO && !achou; i++) {
        for(j = 0; j < TAMANHO && !achou; j++) {
            if(cancha[i][j] == 'X') {
                bolim_row = i;
                bolim_col = j;
                achou = 1;

            }
        }
    }
    /*PROCURAR PELO CARACTERE DA EQUIPE NA MATRIZ E CALCULAR OS PONTOS*/
    for(i = 0; i < TAMANHO; i++) {
        for(j = 0; j < TAMANHO; j++) {
            if(cancha[i][j] == jogador) {
                /*ENCONTROU O CARACTERE*/
                distancia = sqrt(pow(i - bolim_row, 2) + pow(j - bolim_col, 2));
                if(distancia == 1) {
                    /*DISTANCIA = 1 VALE 2 PONTOS, O RESTO VALE 1*/
                    pontuacao += 2;
                }else {
                    pontuacao++;
                }
            }
        }
    }
    return pontuacao;


}

void movimentar_colisao_direta(char bocha, int start_row, int end_row, int col) {
    int i;
    char temp = cancha[start_row][col]; /*GUARDA O OBJETO QUE ESTAVA NO LOCAL ATINGIDO*/
    cancha[start_row][col] = bocha; /*OBJETO QUE FOI LANÇADO AGORA OCUPA A POSIÇÃO*/
    for(i = start_row - 1; i >= end_row; i--) { /*Começa da última linha e vai subindo até a linha escolhida*/
        system("cls");
        mostra_cancha();
        Sleep(300);
        /*testar se está vazio*/
        if(cancha[i][col] == vazio) {
            cancha[i][col] = temp;
        }else {
            cancha[i - 1][col] = cancha[i][col];
            cancha[i][col] = temp;
        }
        if(start_row - i >= 2) {
            cancha[i + 1][col] = vazio;
        }
    }
    mostra_cancha();
}

void vai_dois_volta_um(char bocha, int start_row, int end_row, int col) {
    int i;
    char temp = cancha[start_row][col];
    cancha[start_row][col] = bocha;
    for(i = start_row - 1; i >= end_row; i--) {
        system("cls");
        mostra_cancha();
        Sleep(300);
        if(cancha[i][col] == vazio) {
            cancha[i][col] = temp;
        }
        if(start_row - i >= 2) {
            cancha[i + 1][col] = vazio;
        }
    }
    system("cls");
    mostra_cancha();
    Sleep(300);
    cancha[i + 2][col] = temp;
    cancha[i + 1][col] = vazio;
    system("cls");
    mostra_cancha();
}


