#include <stdlib.h>
#include <ctype.h>
#define TAMANHO 10
#include <windows.h>
void start_screen();
void start_game();
void lanca_bolim(int n, char cancha[n][n]);
void mostra_cancha(int n, char cancha[n][n]);
void inicializa_cancha(int n, char cancha[n][n]);
void movimenta_ponto(int n, char cancha[n][n], char c, int row, int col);
int calcula_erro(int linha_col);
void partida(int n, char cancha[n][n], char alfabeto[n]);
char *jogada(char alfabeto[TAMANHO], char cancha[TAMANHO][TAMANHO], char jogador);
int valida_jogada(char jogada[3], char alfabeto[TAMANHO]);



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

    inicializa_cancha(TAMANHO, cancha);
    lanca_bolim(TAMANHO, cancha);
    partida(TAMANHO, cancha, alfabeto);
    system("pause");


}



void lanca_bolim(int n, char cancha[n][n]) {
    int col = 0, row = 0;
    char bolim = 'X';
    while(col == n || col < 1)  {
        col = rand() % n;
    }
    while(row > n/2 || row == 0) {
        row = rand() % n;
    }

    movimenta_ponto(n, cancha, bolim, row, col);


}

void mostra_cancha(int n, char cancha[n][n]) {
    system("cls");
    int i, j;
    printf("\n\n");
    printf("%25c", ' ');
    /*Mostra as letras*/
    for(i = 0; i < n; i++) {
        printf("%3c", 65 + i);
    }
    printf("\n\n");
    for(i = 0; i < n; i++) {
        printf("%22d%3c", i, ' ');
        for(j = 0; j < n; j++) {
            printf("%3c", cancha[i][j]);
        }
        printf("\n");
    }


    printf("\n\n");


}

void inicializa_cancha(int n, char cancha[n][n]) {
    int i, j;
    for(i = 0; i < TAMANHO; i++) {
        for(j = 0; j < TAMANHO; j++) {
            cancha[i][j] = '-';
        }
    }
}

void movimenta_ponto(int n, char cancha[n][n], char c, int row, int col) {
    int i;
    char bolim = c;
    cancha[TAMANHO - 1][col] = c; /*Ultima linha, e coluna selecionada aleatoriamente*/

    for(i = TAMANHO - 1; i >= row; i--) { /*O bolim come�a da �ltima linha e vai subindo at� a linha escolhida*/
        system("cls");
        mostra_cancha(TAMANHO, cancha);
        Sleep(300);
        cancha[i][col] = bolim;
        cancha[i + 1][col] = '-';
    }

}

void partida(int n, char cancha[n][n], char alfabeto[TAMANHO]) {
    //TODO
    int duracao = 8, jogadas = 0;
    int pontos[2] = {0};
    char *alvo;
    char jogador_atual = 'B';
    while(jogadas < duracao) {
        (jogador_atual == 'A') ? (jogador_atual = 'B') : (jogador_atual = 'A');
        alvo = jogada(alfabeto, cancha, jogador_atual);
        printf("Voc� acertou no %s\n", alvo);
        system("pause");
        mostra_cancha(TAMANHO, cancha);
        jogadas++;
        free(alvo);
    }


}

char *jogada(char alfabeto[TAMANHO], char cancha[TAMANHO][TAMANHO], char jogador) {

    char *jogada = malloc(sizeof(char) * 3);
    int pedir = 1;
    while(pedir) {
        printf("Jogador %c\n", jogador);
        printf("\nSelecione onde deseja jogar\n");
        scanf("%2s", jogada);

        if(valida_jogada(jogada, alfabeto)) {
            pedir = 0;
        } else {
            system("pause");
            mostra_cancha(TAMANHO, cancha);
        }

    }
    return jogada;


}

int valida_jogada(char jogada[3], char alfabeto[TAMANHO]) {

    /*Calcula erro*/
    jogada[0] = jogada[0] + calcula_erro(2); /*Calcula erro da coluna*/
    jogada[1] = jogada[1] + calcula_erro(1); /*Calcula erro da linha*/
    printf("Ponto atingido pela bocha: %c%c\n", jogada[0], jogada[1]);

    /*TESTES*/
    if(!isalpha(jogada[0])) {
        printf("Primeiro digito n�o � letra\n");
        return 0;
    }
    if(jogada[0] < alfabeto[0] || jogada[0] > alfabeto[TAMANHO - 1]) {
        printf("Jogada fora dos limites laterais\n");
        return 0;
    }
    if(!isdigit(jogada[1])) {
        printf("Segundo d�gito n�o � n�mero\n");
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


