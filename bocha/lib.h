#include <stdlib.h>
#include <ctype.h>
#define TAMANHO 10
#include <windows.h>
void start_screen();
void start_game();
void lanca_bolim(int n, char cancha[n][n]);
void mostra_cancha(char cancha[TAMANHO][TAMANHO]);
void inicializa_cancha(char cancha[TAMANHO][TAMANHO]);
void movimenta_ponto(int n, char cancha[n][n], char c, int row, int col);
int calcula_erro(int linha_col);
void partida(char cancha[TAMANHO][TAMANHO], char alfabeto[TAMANHO]);
char *jogada(char alfabeto[TAMANHO], char cancha[TAMANHO][TAMANHO], char jogador);
int valida_jogada(char jogada[3], char alfabeto[TAMANHO]);
void lanca_bocha(char cancha[TAMANHO][TAMANHO], char jogador, int row, int col);
void colisao_tangente(char cancha[TAMANHO][TAMANHO], int row, int col, int desclocamento_horizontal, int deslocamento_vertical);



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
    int i, j;

    /*********************************************************FIM TESTE*/
    char alfabeto[TAMANHO];
    /*Declara o alfabeto permitido para a cancha*/
    for(i = 65; i < 65 + TAMANHO; i++) {
        alfabeto[i - 65] = (char)i;
    }


    inicializa_cancha(cancha);


    FILE *log_endereco;
    log_endereco = fopen("C:\\Users\\clodo\\Downloads\\logs_cancha\\log_startgame().txt", "w");
    /*MOSTRA OS ENDEREÇOS DA MATRIZ************************TESTE****************************/
    for(i = 0; i < TAMANHO; i++) {
        for(j = 0; j < TAMANHO; j++) {
            fprintf(log_endereco, "start_game() Endereco de cancha[%d][%d] = %p Conteudo = %c\n", i, j, &cancha[i][j], cancha[i][j]);
        }
    }
    fclose(log_endereco);




    lanca_bolim(TAMANHO, cancha);
    partida(cancha, alfabeto);
    system("pause");


}



void lanca_bolim(int n, char cancha[n][n]) {
    int col = 0, row = 0;
    char bolim = 'X';
    while(col > n - 2 || col < 1)  {
        col = rand() % n;
    }
    while(row < n/3 || row >= 2*n/3) {
        row = rand() % n;
    }

    movimenta_ponto(n, cancha, bolim, row, col);


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

void movimenta_ponto(int n, char cancha[n][n], char c, int row, int col) {
    int i;
    char temp;

    cancha[TAMANHO - 1][col] = c; /*Ultima linha, e coluna selecionada*/

    for(i = TAMANHO - 1; i >= row; i--) { /*Começa da última linha e vai subindo até a linha escolhida*/
        system("cls");
        mostra_cancha(cancha);
        Sleep(300);
        temp = cancha[i][col];
        cancha[i][col] = c;
        cancha[i + 1][col] = temp;
    }
    mostra_cancha(cancha);
}


/***********************CHAMA VÁRIAS OUTRAS, PODE-SE DIZER QUE É A PRINCIPAL*****************************************/
void partida(char cancha[TAMANHO][TAMANHO], char alfabeto[TAMANHO]) {
    //TODO
    int duracao = 8, jogadas = 0;
    int pontos[2] = {0};
    char *alvo;
    int coluna_linha_numerica[2];

    char jogador_atual = 'B';
    while(jogadas < duracao) {
        (jogador_atual == 'B') ? (jogador_atual = 'A') : (jogador_atual = 'B');
        alvo = jogada(alfabeto, cancha, jogador_atual);
        coluna_linha_numerica[0] = alvo[0] - 65;/*COLUNA: CONVERTE LETRA PARA NUMERO INT A = 0, B = 1*/
        coluna_linha_numerica[1] = alvo[1] - '0'; /*LINHA: CONVERTE CARACTERE DIGITO PARA INT '1' = 1*/
        printf("O jogador acertou no %s\n", alvo);
        lanca_bocha(cancha, jogador_atual, coluna_linha_numerica[1], coluna_linha_numerica[0]);
        system("pause");
        mostra_cancha(cancha);



        jogadas++;
        free(alvo);
    }


}
/************************************************************************************************************************/

char *jogada(char alfabeto[TAMANHO], char cancha[TAMANHO][TAMANHO], char jogador) {

    char *jogada = malloc(sizeof(char) * 3);
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
    /*printf("Ponto atingido pela bocha: %c%c\n", jogada[0], jogada[1]);*/

    /*TESTES*/
    if(!isalpha(jogada[0])) {
        printf("Primeiro digito não é letra\n");
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

    FILE *log_endereco;
    log_endereco = fopen("C:\\Users\\clodo\\Downloads\\logs_cancha\\log_lanca_bocha().txt", "w");
    /**********************/
    /*SE CAIR EM LUGAR VAZIO*/
    if(cancha[row][col] == '-') {



        cancha[row][col] = jogador;
        fprintf(log_endereco, "Copiando %c em cancha[%d][%d] no endereco %p\n", jogador, row, col, &cancha[row][col]);


        /*TESTAR COLISAO TANGENTE*/





    } else {



    }
    int i, j;


    for(i = 0; i < TAMANHO; i++) {
        for(j = 0; j < TAMANHO; j++) {
            fprintf(log_endereco, "lanca_bocha() Endereco de cancha[%d][%d] = %p Conteudo = %c\n", i, j, &cancha[i][j], cancha[i][j]);

        }
    }
    fclose(log_endereco);


}

void colisao_tangente(char cancha[TAMANHO][TAMANHO], int row, int col, int deslocamento_horizontal, int deslocamento_vertical) {
    char bocha_deslocada = cancha[row + deslocamento_horizontal][col + deslocamento_vertical];

    /*CHECAR LIMITE*/
    if( (row + deslocamento_horizontal*2 >= 0 && row + deslocamento_horizontal*2 <= TAMANHO - 1) ) {

    }


}


