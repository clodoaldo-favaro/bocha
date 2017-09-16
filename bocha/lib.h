#include <stdlib.h>
#include <ctype.h>
#define TAMANHO 10
#include <windows.h>
void start_screen();
void start_game();
void lanca_bolim(char cancha[TAMANHO][TAMANHO]);
void mostra_cancha(char cancha[TAMANHO][TAMANHO]);
void inicializa_cancha(char cancha[TAMANHO][TAMANHO]);
int calcula_erro(int linha_col);
void partida(char cancha[TAMANHO][TAMANHO], char alfabeto[TAMANHO]);
char *jogada(char alfabeto[TAMANHO], char cancha[TAMANHO][TAMANHO], char jogador);
int valida_jogada(char jogada[3], char alfabeto[TAMANHO]);
void lanca_bocha(char cancha[TAMANHO][TAMANHO], char jogador, int row, int col);
void colisao_tangente(char cancha[TAMANHO][TAMANHO], int row, int col, int deslocamento_horizontal, int deslocamento_vertical);



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
    char cancha[TAMANHO][TAMANHO]; /*DECLARA A CANCHA*/
    int i;

    char alfabeto[TAMANHO];
    /*Declara o alfabeto permitido para a cancha*/
    for(i = 65; i < 65 + TAMANHO; i++) {
        alfabeto[i - 65] = (char)i;
    }

    inicializa_cancha(cancha);
    lanca_bolim(cancha);
    partida(cancha, alfabeto);
    system("pause");


}



void lanca_bolim(char cancha[TAMANHO][TAMANHO]) {
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
        mostra_cancha(cancha);
        Sleep(300);
        temp = cancha[i][col];
        cancha[i][col] = 'X';
        cancha[i + 1][col] = temp;
    }
    mostra_cancha(cancha);




}

void mostra_cancha(char cancha[TAMANHO][TAMANHO]) {
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
        printf("%22d%3c", i, ' ');
        for(j = 0; j < TAMANHO; j++) {
            printf("%3c", cancha[i][j]);
        }
        printf("\n");
    }


    printf("\n\n");


}

void inicializa_cancha(char cancha[TAMANHO][TAMANHO]) {
    int i, j;
    for(i = 0; i < TAMANHO; i++) {
        for(j = 0; j < TAMANHO; j++) {
            cancha[i][j] = '-';
        }
    }
}




/***********************CHAMA VÁRIAS OUTRAS, PODE-SE DIZER QUE É A PRINCIPAL*****************************************/
void partida(char cancha[TAMANHO][TAMANHO], char alfabeto[TAMANHO]) {
    //TODO
    int duracao = 8, jogadas = 0;
    int pontos_A = 0, pontos_B = 0;
    char *alvo; /*É UM PONTEIRO, OU SEJA: RECEBE ENDEREÇO PARA UMA VARIÁVEL DE TIPO CHAR*/
    int row, col;

    char jogador_atual = 'B';
    while(jogadas < duracao) {
        (jogador_atual == 'B') ? (jogador_atual = 'A') : (jogador_atual = 'B');
        alvo = jogada(alfabeto, cancha, jogador_atual); /*RECEBE UM ENDEREÇO*/
        col = alvo[0] - 65;/*COLUNA: CONVERTE LETRA PARA NUMERO INT A = 0, B = 1*/
        row = alvo[1] - '0'; /*LINHA: CONVERTE CARACTERE DIGITO PARA INT '1' = 1*/
        printf("O jogador acertou no %s\n", alvo);
        lanca_bocha(cancha, jogador_atual, row, col);
        system("pause");
        mostra_cancha(cancha);
        jogadas++;
        free(alvo);
    }


}
/************************************************************************************************************************/

char *jogada(char alfabeto[TAMANHO], char cancha[TAMANHO][TAMANHO], char jogador) {

    char *jogada = malloc(sizeof(char) * 3); /*O PONTEIRO RECEBE UM ENDEREÇO COM O TAMANHO DE 3 BYTES*/
    int pedir = 1;
    while(pedir) {
        printf("Jogador %c\n", jogador);
        printf("\nSelecione onde deseja jogar\n");
        scanf("%2s", jogada);
        jogada[0] = toupper(jogada[0]);

        if(valida_jogada(jogada, alfabeto)) {
            pedir = 0;
        } else {
            system("pause");
            mostra_cancha(cancha);
        }

    }
    return jogada;


}

int valida_jogada(char jogada[3], char alfabeto[TAMANHO]) {

    /*Calcula erro*/
    jogada[0] = jogada[0] + calcula_erro(2); /*Calcula erro da coluna*/
    jogada[1] = jogada[1] + calcula_erro(1); /*Calcula erro da linha*/

    /*TESTES*/
    if(!isalpha(jogada[0])) {
        printf("Ponto atingido = %s. Primeiro digito não é letra. Joque novamente.\n", jogada);
        return 0;
    }
    if(jogada[0] < alfabeto[0] || jogada[0] > alfabeto[TAMANHO - 1]) {
        printf("Jogada fora dos limites laterais\n");
        return 0;
    }
    if(!isdigit(jogada[1])) {
        printf("Segundo dígito não é número\n");
        return 0;
    }
    if((jogada[1] - '0') < 0 || (jogada[1] - '0') > TAMANHO) {
        printf("Jogada fora do limite vertical\n");
        return 0;
    }
    return 1;
}

int calcula_erro(int linha_col) {
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



void lanca_bocha(char cancha[TAMANHO][TAMANHO], char jogador, int row, int col) {


    /**********************/
    /*SE CAIR EM LUGAR VAZIO*/
    if(cancha[row][col] == '-') {



        cancha[row][col] = jogador;



        /*TESTAR COLISAO TANGENTE*/





    } else {



    }
    int i, j;




}

void colisao_tangente(char cancha[TAMANHO][TAMANHO], int row, int col, int deslocamento_horizontal, int deslocamento_vertical) {
    char bocha_deslocada = cancha[row + deslocamento_horizontal][col + deslocamento_vertical];

    /*CHECAR LIMITE*/
    if( (row + deslocamento_horizontal*2 >= 0 && row + deslocamento_horizontal*2 <= TAMANHO - 1) ) {

    }


}


