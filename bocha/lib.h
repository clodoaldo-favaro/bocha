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
int calcula_pontos(char jogador);
void colisao_tangente(int row, int col, int up, int down, int left, int right, int left_up, int right_up, int left_down, int right_down);
void colisao_direta(int row, int col, char jogador);
void empurra_baixo(int row, int col, char jogador);
void mostrar_estatisticas();
void atualizar_estatisticas(int resultado);

/*DECLARA A CANCHA GLOBAL*/
char cancha[TAMANHO][TAMANHO];
char alfabeto[TAMANHO];
char vazio = '-';
int modo_teste;



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
    printf("%32c2. ESTATÍSTICAS\n",' ');
    printf("%32c3. SAIR\n",' ');
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
    int duracao = 8, jogadas = 0, resultado;
    int pontos_A = 0, pontos_B = 0, jogadas_A = 0, jogadas_B = 0;
    int row, col;
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

        col = alvo[0] - 65;/*COLUNA: CONVERTE LETRA PARA NUMERO INT A = 0, B = 1*/
        if(strlen(alvo) == 3) {
            row = (alvo[2] - '0'); /*JA VALIDOU E DEU 10*/
            //SE FOR 10, É A LINHA 0
        }else {
            row = TAMANHO - (alvo[1] - '0'); /*LINHA: CONVERTE CARACTERE DIGITO PARA INT '1' = 1*/
            //EXEMPLO: SE EU QUISER JOGAR NA LINHA 1, NA MATRIZ ELA SERA A LINHA TAMANHO - 1 = 9

        }

        printf("O jogador acertou no %s\n", alvo);
        lanca_bocha(jogador_atual, row, col);
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
        resultado = 1;
    }else if(pontos_A < pontos_B) {
        printf("Vencedor: equipe B!\n");
        resultado = 2;
    }else {
        printf("Empate!\n");
        resultado = 3;
    }
    atualizar_estatisticas(resultado);


}


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

    //TESTES INICIAIS
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


    /*Calcula erro*/
    int erro, numero;

    if(jogada[0] >= 'A' && jogada[0] <= 'A' + TAMANHO - 1) {
        //COLUNA OK
        //CALCULAR UM ERRO VÁLIDO
        erro = calcula_erro(2);
        while(jogada[0] + erro < 'A' || jogada[0] + erro > 'A' + TAMANHO - 1) {
            erro = calcula_erro(2);
        }
        jogada[0] = jogada[0] + erro;
    }

    if(strlen(jogada) == 3) {
        //3 caracteres = A10, B10, C10, etc

        erro = calcula_erro(1); //ERRO PARA LINHA
        numero = (jogada[1] - '0') * 10 + (jogada[2] - '0'); //CONVERTE OS ÚLTIMOS DOIS DÍGITOS EM NÚMERO
        if(numero  <= 0 || numero > TAMANHO) {
            printf("%c%d: jogada fora do limite vertical. Jogue novamente.\n", jogada[0], numero);
            return 0;
        }
        //CALCULA ERRO NOVAMENTE ENQUANTO NÃO DER UM RESULTADO VÁLIDO
        while(numero + erro <= 0 || numero + erro > TAMANHO) {
            erro = calcula_erro(1);
        }
        numero = numero + erro;

        if(numero < 10) {
            //SE POR UM ACASO O NÚMERO FOR MENOR QUE 0,
            jogada[2] = '\0';
            jogada[1] = numero + '0';
        }



    }else if(strlen(jogada) == 2) {


        erro = calcula_erro(1);
        numero = (jogada[1] - '0');
         if(numero  <= 0 || numero > TAMANHO) {
            printf("%c%d: jogada fora do limite vertical. Jogue novamente.\n", jogada[0], numero);
            return 0;
        }
        while(numero + erro <= 0 || numero + erro > TAMANHO) {
            erro = calcula_erro(1);
        }
        numero = numero + erro;

        if(numero < 10) {

            jogada[2] = '\0';
            jogada[1] = numero + '0';

        }
    }






    return 1;
}

int calcula_erro(int linha_col) {

    if(modo_teste) {
        return 0;
    }



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



void lanca_bocha(char jogador, int row, int col) {

    //CAIU EM LUGAR VAZIO
    if(cancha[row][col] == vazio) {
        cancha[row][col] = jogador;
        if(!modo_teste) {
            colisao_tangente(row, col, 1, 1, 1, 1, 1, 1, 1, 1);
        }

    } else {
        //CAIU EM UMA CASA OCUPADA POR OUTRO OBJETO
        colisao_direta(row, col, jogador);
    }
}

void colisao_tangente(int row, int col, int up, int down, int left, int right, int left_up, int right_up, int left_down, int right_down) {
    int i, j;
    //VERIFICA ESQUERDA
    //PARA MOVER A BOCHA À ESQUERDA, A BOCHA LANÇADA DEVE TER CAÍDO NA COLUNA 2 OU MAIOR, E A OPCAO LEFT DEVE SER 1
    if(col >= 2 && left) {
        //CHECAR SE TEM BOCHA(A OU B) À ESQUERDA DO LOCAL
        if(cancha[row][col - 1] == 'A' || cancha[row][col - 1] == 'B') {
            /*HÁ UM OBJETO IMEDIATAMENTE À ESQUERDA DE ONDE CAIU A BOCHA LANÇADA*/
            /*CHECAR SE O LOCAL MAIS ESQUERDA ESTÁ VAZIO*/
            if(cancha[row][col - 2] == vazio) {
                /*MOVER UMA CASA À ESQUERDA*/
                cancha[row][col - 2] = cancha[row][col - 1];
                cancha[row][col - 1] = vazio;
            }else {
                j = col - 2;
                while(cancha[row][j] != vazio && j >= 0) {
                    j--;
                }
                if(j >= 0) {
                    while(j <= col - 2) {
                        cancha[row][j] = cancha[row][j + 1];
                        j++;
                    }
                    cancha[row][j] = vazio;
                }
            }
        }
    }
    /*-------------------------------*/


    /*-----------DIREITA-----------*/
    /*CHECAR LIMITE À DIREITA DO LOCAL ONDE CAIU A BOCHA LANÇADA E SE RIGHT ESTÁ ATIVADO*/
    if(col  < TAMANHO - 2 && right) {
        /*CHECAR SE TEM ALGO À DIREITA DA BOCHA LANÇADA*/
        if(cancha[row][col + 1] == 'A' || cancha[row][col + 1] == 'B') {
            /*HÁ UM OBJETO IMEDIATAMENTE À DIREITA DE ONDE CAIU A BOCHA LANÇADA*/
            /*CHECAR SE O LOCAL MAIS À DIREITA ESTÁ VAZIO*/
            if(cancha[row][col + 2] == vazio) {
                /*MOVER UMA CASA À DIREITA*/
                cancha[row][col + 2] = cancha[row][col + 1];
                cancha[row][col + 1] = vazio;
            }else {
                j = col + 2;
                //Vai percorrendo à direita até achar um espaço vazio ou passar da da borda
                while(cancha[row][j] != vazio && j < TAMANHO) {
                    j++;
                }
                if(j < TAMANHO) {
                    while(j >= col + 2) {
                        cancha[row][j] = cancha[row][j - 1];
                        j--;
                    }
                    cancha[row][j] = vazio;
                }
            }
        }
    }
    /*-------------------------------*/


    /*ACIMA*/
    /*CHECAR LIMITE ACIMA DE ONDE CAIU A BOCHA LANÇADA E SE A OPÇÃO UP ESTÁ ATIVADA*/
    if(row >= 2 && up) {
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
    /*CHECAR LIMITE ABAIXO DE ONDE CAIU A BOCHA LANÇADA E SE DOWN ESTÁ ATIVADO*/
    if(row < TAMANHO  - 2 && down) {
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
    /*CHECAR LIMITE ACIMA-ESQUERDA DE ONDE CAIU A BOCHA LANÇADA E SE LEFT UP ESTÁ ATIVADO*/
    if(row >= 2 && col >= 2 && left_up) {
        /*CHECAR SE HÁ ALGUMA BOCHA ACIMA E À ESQUERDA*/
        if(cancha[row - 1][col - 1] == 'A' || cancha[row - 1][col - 1] == 'B' ) {
            /*HÁ UMA BOCHA ACIMA E À ESQUERDA*/
            /*CHECAR SE HÁ ESPAÇO PARA ELA SER MOVIDA*/
            if(cancha[row - 2][col - 2] == vazio) {
                /*MOVER ACIMA E À ESQUERDA*/
                cancha[row - 2][col - 2] = cancha[row - 1][col - 1];
                cancha[row - 1][col - 1] = vazio;
            }else {
                //Espaço não está vazio, começar o loop para encontrar o primeiro espaço vazio
                //acima e à esquerda
                i = row - 2;
                j = col - 2;
                //Vai percorrendo no sentido diagonal superior esquerdo até achar um espaço vazio ou ultrapassar as bordas
                while(cancha[i][j] != vazio && i >= 0 && j >= 0) {
                    i--;
                    j--;
                }
                //Se não ultrapassou as bordas, é porque conseguiu encontrar um espaço vazio
                if(i >= 0 && j >= 0) {
                    //A partir do espaço vazio encontrado, move o objeto localizado abaixo e à direita
                    while(i <= row - 2) {
                        cancha[i][j] = cancha[i + 1][j + 1];
                        i++;
                        j++;
                    }
                    cancha[i][j] = vazio;
                }
            }
        }
    }
    /*---------------------------------------------*/


    //ACIMA-DIREITA
    /*CHECAR LIMITE ACIMA-DIREITA DE ONDE CAIU A BOCHA LANÇADA E SE RIGHT UP ESTÁ ATIVADO*/
    if(row >= 2 && col < TAMANHO - 2 && right_up) {
        /*CHECAR SE HÁ UMA BOCHA ACIMA E À DIREITA*/
        if(cancha[row - 1][col + 1] == 'A' || cancha[row - 1][col + 1] == 'B') {
            /*HÁ UMA BOCHA ACIMA E À DIREITA*/
            /*VERIFICA SE HÁ ESPAÇO PARA MOVER*/
            if(cancha[row - 2][col + 2] == vazio) {
                /*MOVER ACIMA E À DIREITA*/
                cancha[row - 2][col + 2] = cancha[row - 1][col + 1];
                cancha[row - 1][col + 1] = vazio;
            }else {
                //O ESPAÇO NÃO ESTÁ VAZIO, COMEÇAR O LOOP PARA ENCONTRAR O PRIMEIRO ESPAÇO VAZIO
                //NO SENTIDO DIAGONAL SUPERIOR DIREITO
                i = row - 2;
                j = col + 2;
                while(cancha[i][j] != vazio && i >= 0 && j < TAMANHO) {
                    //VAI SUBINDO NO SENTIDO DIAGONAL SUPERIOR DIREITO ATÉ ACHAR UM ESPAÇO VAZIO OU ULTRAPASSAR AS BORDAS
                    i--;
                    j++;
                }
                //Se não ultrapassou as bordas, encontrou um espaço vazio, então é possível deslocar
                if(i >= 0 && j < TAMANHO) {
                    //A partir do espaço vazio localizado, copia para o espaço atual o objeto
                    //contido na posição diagonal inferior esquerda
                    while(i <= row - 2) {
                        cancha[i][j] = cancha[i + 1][j - 1];//Uma linha abaixo (i + 1) e uma coluna à esquerda (j - 1)
                        i++; //Move para a linha abaixo
                        j--; //Move para a coluna à esquerda
                    }
                    //Aqui estamos em i == row - 1, e j = col + 1, local onde a bocha inicial foi deslocada, então aqui será vazio
                    cancha[i][j] = vazio;
                }
            }
        }
    }
    /*--------------------------------------------------*/

    /*ABAIXO-ESQUERDA*/
    /*CHECAR LIMITE ABAIXO-ESQUERDA DE ONDE CAIU A BOCHA LANÇADA E SE LEFT DOWN ESTÁ ATIVADA*/
    if(row < TAMANHO - 2 && col >=2 && left_down) {
        /*CHECAR SE HÁ BOCHA ABAIXO E À ESQUERDA*/
        if(cancha[row + 1][col - 1] == 'A' || cancha[row + 1][col - 1] == 'B') {
            /*HÁ BOCHA ABAIXO E À ESQUERDA*/
            /*VERIFICA SE HÁ ESPAÇO PARA MOVER*/
            if(cancha[row + 2][col - 2] == vazio) {
                /*MOVER ABAIXO E À ESQUERDA*/
                cancha[row + 2][col - 2] = cancha[row + 1][col - 1];
                cancha[row + 1][col - 1] = vazio;
            }else {
                i = row + 2;
                j = col - 2;
                while(cancha[i][j] != vazio && i < TAMANHO && j >= 0) {
                    i++;
                    j--;
                }
                if(i < TAMANHO && j >= 0) {
                    while(i >= row + 2) {
                        cancha[i][j] = cancha[i - 1][j + 1];
                        i--;
                        j++;
                    }
                    cancha[i][j] = vazio;
                }
            }
        }
    }
    /*----------------------------------------------*/


    /*ABAIXO-DIREITA*/
    /*CHECAR LIMITE ABAIXO-DIREITA DE ONDE CAIU A BOCHA LANÇADA E SE RIGHT DOWN ESTÁ ATIVADO*/
    if(row < TAMANHO - 2 && col < TAMANHO - 2 && right_down) {
        /*CHECAR SE HÁ BOCHA ABAIXO E À DIREITA*/
        if(cancha[row + 1][col + 1] == 'A' || cancha[row + 1][col + 1] == 'B') {
            /*HÁ BOCHA ABAIXO E À DIREITA*/
            /*VERIFICA SE HÁ ESPAÇO PARA MOVER*/
            if(cancha[row + 2][col + 2] == vazio) {
                /*MOVER ABAIXO E À DIREITA*/
                cancha[row + 2][col + 2] = cancha[row + 1][col + 1];
                cancha[row + 1][col + 1] = vazio;
            }else {
                i = row + 2;
                j = col + 2;
                while(cancha[i][j] != vazio && i < TAMANHO && j < TAMANHO) {
                    i++;
                    j++;
                }
                if(i < TAMANHO && j < TAMANHO) {
                    while(i >= row + 2) {
                        cancha[i][j] = cancha[i - 1][j - 1];
                        i--;
                        j--;
                    }
                    cancha[i][j] = vazio;
                }

            }
        }
    }
    /*----------------------------------------------*/




}


void colisao_direta(int row, int col, char jogador) {
    int i , j;
   /*PRIMEIRO TESTE: VERIFICAR SE O LOCAL DE COLISÃO ESTÁ NA LINHA 3 OU MAIOR(MAIS PARA BAIXO NA MATRIZ) */
   if(row >= 3) {
        /*3 CASAS ACIMA VAZIAS*/
        if( (cancha[row - 1][col] == vazio) && (cancha[row - 2][col] == vazio) && (cancha[row - 3][col] == vazio) ) {
            cancha[row - 3][col] = cancha[row][col];
            cancha[row][col] = jogador;   /*OK*/
            /*CHAMA COLISAO TANGENTE*/
            /*NÃO PRECISA CHECAR ACIMA*/
            colisao_tangente(row, col, 0, 1, 1, 1, 1, 1, 1, 1);/*OK*/
            /*---------------TUDO CERTO ATÉ AQUI-----------------------*/

        }else {
            /*UMA OU MAIS CASAS OCUPADAS*/

            /*PRIMEIRA CASA OCUPADA*/
            if( (cancha[row - 1][col] != vazio) && (cancha[row - 2][col] == vazio) && (cancha[row - 3][col] == vazio) ) {
                cancha[row - 3][col] = cancha[row - 1][col];
                cancha[row - 1][col] = cancha[row][col];
                cancha[row][col] = jogador; /*OK*/
                /*CHAMA COLISAO TANGENTE, NÃO CHECAR ACIMA*/
                colisao_tangente(row, col, 0, 1, 1, 1, 1, 1, 1, 1); /*OK*/
                /*------------------TUDO CERTO--------------*/
            }
            /*SEGUNDA CASA OCUPADA*/
            else if( (cancha[row - 1][col] == vazio) && (cancha[row - 2][col] != vazio) && (cancha[row - 3][col] == vazio) ) {
                cancha[row - 3][col] = cancha[row - 2][col];
                cancha[row - 2][col] = cancha[row][col];
                cancha[row][col] = jogador; /*OK*/
                /*CHAMA COLISAO TANGENTE, NÃO CHECAR ACIMA*/
                colisao_tangente(row, col, 0, 1, 1, 1, 1, 1, 1, 1); /*OK*/
                /*----------------TUDO CERTO--------------------------*/
            }
            /*TERCEIRA CASA OCUPADA*/
            else if( (cancha[row - 1][col] == vazio) && (cancha[row - 2][col] == vazio) && (cancha[row - 3][col] != vazio) ) {
                /*TESTAR SE TEM 4 OU MAIS CASAS ACIMA*/
                if(row > 3) {
                    /*ENCONTRAR ESPAÇO VAZIO*/
                    /*COMEÇANDO A PARTIR DE UM ESPAÇO ACIMA DE ROW - 3, OU SEJA, ROW - 4*/
                    /*ELE PERCORRE ATÉ ACHAR UM ESPAÇO VAZIO, OU ATÉ i ser igual a 0*/
                    i = row - 4;
                    while(cancha[i][col] != vazio && i >= 0) {
                        /*NÃO ENCONTROU VAZIO E i NÃO PASSOU DA BORDA DA CANCHA*/
                        i--;
                    }
                    /*SE i FOR MENOR QUE ZERO, SIGNIFICA QUE PERCORREU PASSOU DA CANCHA SEM ENCONTRAR ESPAÇO VAZIO*/
                    /*ENTÃO, A BOCHA ATINGIDA EM cancha[row][col] SÓ VAI SE MOVIMENTAR DUAS VEZES, POIS NÃO TEM COMO EMPURRAR O QUE ESTÁ ACIMA*/
                    if(i < 0) {
                        /*MOVE SÓ DUAS VEZES*/
                        cancha[row - 2][col] = cancha[row][col];
                        cancha[row][col] = jogador;
                    }else {
                        /*EMPURRA ATÉ O PRIMEIRA ESPAÇO VAZIO QUE ACHOU*/

                        /*COMEÇANDO POR j = i, OU SEJA, DO ESPAÇO VAZIO*/
                        /*VAI ATÉ O ROW - 4 QUE SERÁ OCUPADO PELO ROW - 3*/
                        for(j = i; j <= row - 4; j++) {
                            /*PRIMEIRA ITERAÇÃO, CANCHA[J][COL] É O ESPAÇO VAZIO*/
                            /*LINHA ATUAL RECEBE A LINHA DE BAIXO*/
                            cancha[j][col] = cancha[j + 1][col];
                        }
                        /*TERMINANDO ISSO, AGORA PODEMOS COLOCAR CANCHA[ROW][COL] EM CANCHA[ROW - 3][COL]*/
                        cancha[row - 3][col] = cancha[row][col];
                        cancha[row][col] = jogador;
                    }
                    /*----------TUDO OK------------*/
                }else {
                    /*SENÃO MOVE SÓ DUAS VEZES E PÁRA*/
                    cancha[row - 2][col] = cancha[row][col];
                    cancha[row][col] = jogador; /*OK*/
                    /*----------------TUDO CERTO----------------*/
                }
                /*CHAMA COLISAO TANGENTE, NÃO CHECAR ACIMA*/
                colisao_tangente(row, col, 0, 1, 1, 1, 1, 1, 1, 1); /*OK*/
                /*-----------TUDO CERTO---------------*/
            }
            //PRIMEIRA E SEGUNDA CASAS OCUPADAS
            else if( (cancha[row - 1][col] != vazio) && (cancha[row - 2][col] != vazio) && (cancha[row - 3][col] == vazio) ) {
                cancha[row - 3][col] = cancha[row - 2][col];
                cancha[row - 2][col] = cancha[row - 1][col];
                cancha[row - 1][col] = cancha[row][col];
                cancha[row][col] = jogador; /*OK*/
                /*CHAMA COLISAO TANGENTE, NÃO CHECAR ACIMA*/
                colisao_tangente(row, col, 0, 1, 1, 1, 1, 1, 1, 1); /*OK*/
                /*---------------------TUDO CERTO-----------------*/
            }
            /*PRIMEIRA E TERCEIRA CASAS OCUPADAS*/
            else if( (cancha[row - 1][col] != vazio) && (cancha[row - 2][col] == vazio) && (cancha[row - 3][col] != vazio) ) {
                /*SE TIVER ESPAÇO PARA MOVER PRA CIMA*/
                if(row > 3) {
                    i = row - 4;
                    /*PROCURA ESPAÇO VAZIO*/
                    while(cancha[i][col] != vazio && i >= 0) {
                        i--;
                    }
                    if(i < 0) {
                        /*NÃO ENCONTROU ESPAÇO VAZIO*/
                        cancha[row - 2][col] = cancha[row - 1][col];
                        cancha[row - 1][col] = cancha[row][col];
                        cancha[row][col] = jogador;
                    }else {
                        for(j = i; j <= row - 4; j++) {
                            cancha[j][col] = cancha[j + 1][col];
                        }
                        cancha[row - 3][col] = cancha[row - 1][col];
                        cancha[row - 1][col] = cancha[row][col];
                        cancha[row][col] = jogador;
                    }
                }else {
                    /*CANCHA[ROW][COL] SOBE 1, E CANCHA[ROW - 1][COL] SOBE 1*/
                    cancha[row - 2][col] = cancha[row - 1][col];
                    cancha[row - 1][col] = cancha[row][col];
                    cancha[row][col] = jogador; /*OK*/
                }
                /*CHAMA COLISAO TANGENTE, NÃO CHECAR ACIMA*/
                colisao_tangente(row, col, 0, 1, 1, 1, 1, 1, 1, 1); /*OK*/
                /*-----------TUDO CERTO-----------------*/
            }
            /*SEGUNDA E TERCEIRA CASAS OCUPADAS*/
            else if( (cancha[row - 1][col] == vazio) && (cancha[row - 2][col] != vazio) && (cancha[row - 3][col] != vazio) ) {
                /*SE TIVER ESPAÇO NA QUARTA CASA*/
                if(row > 3) {
                    i = row - 4;
                    /*PROCURA ESPAÇO VAZIO*/
                    while(cancha[i][col] != vazio && i >= 0) {
                        i--;
                    }
                    if(i < 0) {
                        cancha[row - 1][col] = cancha[row][col];
                        cancha[row][col] = jogador;
                    }else {
                        for(j = i; j <= row - 3; j++) {
                            cancha[j][col] = cancha[j + 1][col];
                        }
                        cancha[row - 2][col] = cancha[row][col];
                        cancha[row][col] = jogador;
                    }
                }else {
                    cancha[row - 1][col] = cancha[row][col];
                    cancha[row][col] = jogador; /*OK*/

                }
                /*CHAMA COLISAO TANGENTE, NÃO CHECAR ACIMA*/
                colisao_tangente(row, col, 0, 1, 1, 1, 1, 1, 1, 1); /*OK*/
                /*-----------TUDO CERTO------------------*/
            }
            //3 CASAS ACIMAS OCUPADAS, VERICAR SE HÁ 1 ESPAÇO LIVRE ACIMAS DAS 3 PARA IR EMPURRANDO
            else {
                i = row - 4;
                //PROCURAR ESPACOS VAZIOS ACIMA
                    while(cancha[i][col] != vazio && i >= 0) {
                        i--;
                    }
                    if(i < 0) {
                        //NÃO LOCALIZOU ESPAÇO VAZIO ACIMA, PROCURAR ESPACO ABAIXO
                        empurra_baixo(row, col, jogador);
                    }else {
                        /*EMPURRA PRA CIMA*/
                        for(j = i; j <= row - 1; j++) {
                            cancha[j][col] = cancha[j + 1][col];
                        }
                        cancha[row][col] = jogador;
                        colisao_tangente(row, col, 0, 1, 1, 1, 1, 1, 1, 1);
                    }
            }
        }
   }else if(row == 2) {
        if(cancha[row - 1][col] == vazio && cancha[row - 2][col] == vazio) { //DOIS ESPAÇOS ACIMA VAZIOS
            cancha[row - 1][col] = cancha[row][col];
            cancha[row][col] = jogador;
            colisao_tangente(row, col, 0, 1, 1, 1, 1, 1, 1, 1);
        }else if(cancha[row - 1][col] != vazio && cancha[row - 2][col] == vazio) { //1 ACIMA OCUPADO, 2 ACIMA VAZIO
            cancha[row - 2][col] = cancha[row - 1][col];
            cancha[row - 1][col] = cancha[row][col];
            cancha[row][col] = jogador;
            colisao_tangente(row, col, 0, 1, 1, 1, 1, 1, 1, 1);
        }else if(cancha[row - 1][col] == vazio && cancha[row - 2][col] != vazio) {
            cancha[row - 1][col] = cancha[row][col];
            cancha[row][col] = jogador;
            colisao_tangente(row, col, 0, 1, 1, 1, 1, 1, 1, 1);
        }else {
            //DUAS CASAS OCUPADAS, PROCURAR ABAIXO
            empurra_baixo(row, col, jogador);
        }
   }else if(row == 1) {
       if(cancha[row - 1][col] == vazio) {
            cancha[row - 1][col] = cancha[row][col];
            cancha[row][col] = jogador;
            colisao_tangente(row, col, 0, 1, 1, 1, 1, 1, 1, 1);
       }else {
            //NÃO TEM ESPAÇO EM CIMA, PROCURAR EMBAIXO
            empurra_baixo(row, col, jogador);
       }
   }else if(row == 0) {
       empurra_baixo(row, col, jogador);
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

void empurra_baixo(int row, int col, char jogador) {
    int i, j;
    i = row + 1; //COMEÇA A PROCURAR A PARTIR DE UMA CASA ABAIXO, PARA AO ACHAR VAZIO
    while(cancha[i][col] != vazio && i < TAMANHO) {
        i++;
    }
    for(j = i; j >= row + 2; j--) {
        cancha[j][col] = cancha[j - 1][col]; //MOVE PARA BAIXO
    }
    cancha[row + 1][col] = jogador;
    colisao_tangente(row + 1, col, 0, 0, 1, 1, 1, 1, 1, 1);

}

void mostrar_estatisticas() {

    FILE *stats;
    int linha = 1;
    //vetor de caracteres onde será armazenado a string lida do arquivo
    char texto[20];
    //TESTA SE CONSEGUIU ABRIR
    if( (stats = fopen("stats.txt", "r")) != NULL)  {
        system("cls");
        //Percorre uma linha por vez fgets() lê uma string até achar um caractere de nova linha.
        while(fgets(texto, 19, stats) != NULL) {
            switch(linha) {

                case 1:
                    printf("Partidas jogadas: %s", texto);
                    break;
                case 2:
                    printf("Vitórias da equipe A: %s", texto);
                    break;
                case 3:
                    printf("Vitórias da equipe B: %s", texto);
                    break;
                case 4:
                    printf("Empates: %s", texto);
                    break;
                default:
                    break;
            }
            linha++;
        }
    }else {
        printf("Não foi possível abrir o arquivo\n");
        system("PAUSE");
        start_screen();
    }
    fclose(stats);
    system("PAUSE");


}

void atualizar_estatisticas(int resultado) {
    if(modo_teste) {
        return;
    }
    FILE *stats;
    char partidas[5], vitorias_A[5], vitorias_B[5], empates[5];

    if( (stats = fopen("stats.txt", "r")) != NULL) {
        fgets(partidas, 6, stats);
        //printf("%s\n", partidas);
        fgets(vitorias_A, 6, stats);
        //printf("%s\n", vitorias_A);
        fgets(vitorias_B, 6, stats);
        //printf("%s\n", vitorias_B);
        fgets(empates, 6, stats);
        //printf("%s\n", empates);
    }
    fclose(stats);

    int partidas_int = atoi(partidas);
    int vit_A_int = atoi(vitorias_A);
    int vit_B_int = atoi(vitorias_B);
    int emp_int = atoi(empates);
    partidas_int++;
    switch(resultado) {
        case 1:
            vit_A_int++;
            break;
        case 2:
            vit_B_int++;
            break;
        case 3:
            emp_int++;
            break;
        default:
            break;
    }

    if( (stats = fopen("stats.txt", "w")) != NULL) {
        fprintf(stats, "%d\n", partidas_int);
        fprintf(stats, "%d\n", vit_A_int);
        fprintf(stats, "%d\n", vit_B_int);
        fprintf(stats, "%d\n", emp_int);
    }
    fclose(stats);
}




