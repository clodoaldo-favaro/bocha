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
    while(opcao == 1) {
        start_game();
        start_screen();
        scanf("%d", &opcao);
    }



    return 0;
}
