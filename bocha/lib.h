#include <stdlib.h>
#define TAMANHO 10
#include <windows.h>
void start_screen();
void start_game();
void lanca_bolim(int n, char cancha[n][n]);
void mostra_cancha(int n, char cancha[n][n]);
void inicializa_cancha(int n, char cancha[n][n]);
void movimenta_ponto(int n, char cancha[n][n], char c, int row, int col);



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
    char cancha[TAMANHO][TAMANHO];
    inicializa_cancha(TAMANHO, cancha);
    lanca_bolim(TAMANHO, cancha);
    system("pause");


}



void lanca_bolim(int n, char cancha[n][n]) {
    int col, row;
    char bolim = 'X';
    col = rand() % n;
    row = rand() % n;
    movimenta_ponto(n, cancha, bolim, row, col);


}

void mostra_cancha(int n, char cancha[n][n]) {
    system("cls");
    int i, j;
    printf("\n\n\n");
    for(i = 0; i < n; i++) {
        printf("%25c", ' ');
        for(j = 0; j < n; j++) {
            printf("%3c", cancha[i][j]);
        }
        printf("\n");
    }

}

void inicializa_cancha(int n, char cancha[n][n]) {
    int i, j;
    for(i = 0; i < TAMANHO; i++) {
        for(j = 0; j < TAMANHO; j++) {
            cancha[i][j] = '0';
        }
    }
}

void movimenta_ponto(int n, char cancha[n][n], char c, int row, int col) {
    int i;
    char bolim = c;
    cancha[TAMANHO - 1][col] = c; /*Ultima linha, e coluna selecionada aleatoriamente*/

    for(i = TAMANHO - 1; i >= row; i--) { /*O bolim começa da última linha e vai subindo até a linha escolhida*/
        system("cls");
        mostra_cancha(TAMANHO, cancha);
        Sleep(300);
        cancha[i][col] = bolim;
        cancha[i + 1][col] = '0';
    }

}


