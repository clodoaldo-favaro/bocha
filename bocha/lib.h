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
void partida();



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
    int i, max_colunas;
    char alfabeto_colunas[23];
    /*Declara o alfabeto permitido para a cancha*/
    for(i = 65, max_colunas = 0; i < 65 + TAMANHO; i++) {
        alfabeto_colunas[max_colunas] = (char)i;
        max_colunas++;
    }

    inicializa_cancha(TAMANHO, cancha);
    lanca_bolim(TAMANHO, cancha);
    /*partida(TAMANHO, cancha);*/
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

void partida() {
    //TODO
    int duracao = 4, jogadas = 0;
    while(jogadas < duracao) {
        printf("Jogador A\n");
        char *alvo = jogada();
    }


}

char *jogada() {
    //TODO
    char joga[2] = {'-'};
    char letra = toupper(joga[0]);
    char numero = joga[1];
    while(!isalpha(letra) && !isdigit(numero)) {
        printf("Selecione onde deseja jogar\n");
        scanf("%2s", joga);
        char letra = toupper(joga[0]);
        char numero = joga[1];

    }


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


