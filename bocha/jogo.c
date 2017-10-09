#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lib.h"
#include <locale.h>

int main() {

    int opcao;
    setlocale(LC_ALL, "");
    srand(time(0));
    start_screen();
    scanf("%d", &opcao);
    /*Principal*/
    while(opcao != 3) {

        switch(opcao) {
            case 1:
                modo_teste = 0;
                start_game();
                start_screen();
                break;
            case 2:
                mostrar_estatisticas();
                start_screen();
                break;
            case 3:
                break;
            case 999828812:
                printf("Entrando em modo de teste...\n");
                printf("calcula_erro() sempre retornará 0\n");
                printf("Não haverá colisão tangente caso a bocha cai em local vazio\n");
                system("PAUSE");
                modo_teste = 1;
                start_game();
                start_screen();
                modo_teste = 0;
                break;
            default:
                printf("Opção inválida\n");
                system("PAUSE");
                start_screen();
                break;
        }

        scanf("%d", &opcao);
    }



    return 0;
}
