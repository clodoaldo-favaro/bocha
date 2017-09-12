#include <stdlib.h>
#define N 10
void start_screen();
void start_game();
void lanca_bolim(int n, char cancha[n][n]);
void mostra_cancha(int n, char cancha[n][n]);
void inicializa_cancha(int n, char cancha[n][n]);
void mover_ponto(int n, int row, int col, int cancha[n][n]);



void start_screen() {
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

    int cancha[N][N];
    inicializa_cancha(N, cancha);
    lanca_bolim(N, cancha);
    mostra_cancha(N, cancha);
    system("pause");


}



void lanca_bolim(int n, char cancha[n][n]) {
    int col, row;
    char bolim = 'X';
    col = rand() % N;
    row = rand() % N;
    movimenta_ponto(N, cancha, bolim, row, col);


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
    for(i = 0; i < N; i++) {
        for(j = 0; j < N; j++) {
            cancha[i][j] = '0';
        }
    }
}

void movimenta_ponto(N, int cancha[N][N], char c, int row, int col)
{
    int i, j;

    cancha[N - 1][col] = c;

    for(i = 5; i >= row; i--) {
        system("cls");
        mostra_cancha(N, cancha);
        getchar();
        cancha[i][col] = 0;
        cancha[i - 1][col] = bolim;
    }

}


