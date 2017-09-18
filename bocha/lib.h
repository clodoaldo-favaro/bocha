#include <stdlib.h>
#include <ctype.h>
#define TAMANHO 10
#include <windows.h>
#include <math.h>
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
int calcula_pontos(char jogador, char cancha[TAMANHO][TAMANHO]);
void colisao_direta(char cancha[TAMANHO][TAMANHO], int row, int col, char jogador, int deslocar);



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
    /*CALCULA ONDE O BOLIM SER� JOGADO*/
    while(col > TAMANHO - 2 || col < 1)  {
        col = rand() % TAMANHO;
    }
    while(row < TAMANHO/3 || row >= 2*TAMANHO/3) {
        row = rand() % TAMANHO;
    }
    /*ANIMA��O*/
    int i;
    char temp;

    for(i = TAMANHO - 1; i >= row; i--) { /*Come�a da �ltima linha e vai subindo at� a linha escolhida*/
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
        printf("%22d%3c", 10 - i, ' ');
        for(j = 0; j < TAMANHO; j++) {
            printf("%3c", cancha[i][j]);
        }
        printf("\n");
    }


    printf("\n");


}

void inicializa_cancha(char cancha[TAMANHO][TAMANHO]) {
    int i, j;
    for(i = 0; i < TAMANHO; i++) {
        for(j = 0; j < TAMANHO; j++) {
            cancha[i][j] = '-';
        }
    }
}




/***********************CHAMA V�RIAS OUTRAS, PODE-SE DIZER QUE � A PRINCIPAL*****************************************/
void partida(char cancha[TAMANHO][TAMANHO], char alfabeto[TAMANHO]) {
    //TODO
    int duracao = 8, jogadas = 0;
    int pontos_A = 0, pontos_B = 0, jogadas_A = 0, jogadas_B = 0;
    char *alvo; /*� UM PONTEIRO, OU SEJA: RECEBE ENDERE�O PARA UMA VARI�VEL DE TIPO CHAR*/
    int row, col;

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

        alvo = jogada(alfabeto, cancha, jogador_atual); /*RECEBE UM ENDERE�O*/

        col = alvo[0] - 65;/*COLUNA: CONVERTE LETRA PARA NUMERO INT A = 0, B = 1*/
        if(strlen(alvo) == 3) {
            row = 0 + (alvo[2] - '0'); /*JA VALIDOU E DEU 10*/

        }else {
            row = TAMANHO - (alvo[1] - '0'); /*LINHA: CONVERTE CARACTERE DIGITO PARA INT '1' = 1*/

        }

        printf("O jogador acertou no %s\n", alvo);
        lanca_bocha(cancha, jogador_atual, row, col);
        system("pause");
        mostra_cancha(cancha);
        pontos_A = calcula_pontos('A', cancha);
        pontos_B = calcula_pontos('B', cancha);
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

char *jogada(char alfabeto[TAMANHO], char cancha[TAMANHO][TAMANHO], char jogador) {

    char *jogada = malloc(sizeof(char) * 4); /*O PONTEIRO RECEBE UM ENDERE�O COM O TAMANHO DE 3 BYTES*/
    int pedir = 1;
    while(pedir) {
        printf("\nJogador %c\n", jogador);
        printf("Selecione onde deseja jogar\n");
        fflush(stdin);
        gets(jogada);


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

int valida_jogada(char jogada[4], char alfabeto[TAMANHO]) {

    /*Calcula erro*/
    int teste, erro, numero;
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
        printf("%s:  primeiro digito n�o � letra. Joque novamente.\n", jogada);
        return 0;
    }
    if(jogada[0] < alfabeto[0] || jogada[0] > alfabeto[TAMANHO - 1]) {
        printf("%s: jogada fora dos limites laterais. Jogue novamente.\n", jogada);
        return 0;
    }
    if(!isdigit(jogada[1])) {
        printf("%s: segundo d�gito n�o � n�mero. Jogue novamente.\n", jogada);
        return 0;
    }
    if(numero  <= 0 || numero > TAMANHO) {
        printf("%c%d: jogada fora do limite vertical. Jogue novamente.\n", jogada[0], numero);
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





    } else { /*COLIS�O DIRETA*/
        colisao_direta(cancha, row, col, jogador, 3);


    }





}

void colisao_tangente(char cancha[TAMANHO][TAMANHO], int row, int col, int deslocamento_horizontal, int deslocamento_vertical) {



}


void colisao_direta(char cancha[TAMANHO][TAMANHO], int row, int col, char jogador, int deslocar) {

    /*PARA ENTRAR NESSA FUN��O, cancha[row][col] N�O EST� VAZIA*/

    char temp;
    int espacos = 0, movimentos = 0, limite = row;
    while(limite >= 0) {/*CALCULA O MAXIMO DE MOVIMENTO POSSIVEL*/
        limite--;
        if(cancha[limite][col] == '-') { /*Se tiver espa�o vago, pode mover*/
            movimentos++;
        }
        if(movimentos == deslocar) {
            break;
        }

    }
    printf("Maximo de movimentos possiveis %d\n", movimentos);
    if(movimentos > 0) { /*PODE DESLOCAR*/
        temp = cancha[row][col]; /*GUARDA O OBJETO ATINGIDO*/
        cancha[row][col] = jogador;/*COLOCA A BOCHA NO LOCAL*/
        /*COME�A A MOVER*/
        while(movimentos > 0) {
            if(cancha[row - 1][col] == '-') {
                cancha[row - 1][col] = temp;

                row--;

                temp = '-';
                movimentos++;
            }else {
                if(row - 2 >= 0) {
                    cancha[row - 2][col] = cancha[row - 1][col];
                    cancha[row - 1][col] = temp;
                }
            }
        }
    }









}

int calcula_pontos(char jogador, char cancha[TAMANHO][TAMANHO]) {

    int i, j, bolim_row, bolim_col, achou = 0, pontuacao = 0, distancia;
    /*GUARDAR POSI��O DO BOLIM*/
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


