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
                start_game();
                start_screen();
                break;
            case 2:
                mostrar_estatisticas();
                start_screen();
                break;
            default:
                printf("Opção inválida\n");
                start_screen();
                break;
        }

        scanf("%d", &opcao);
    }



    return 0;
}
