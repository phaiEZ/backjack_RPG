#include "card.h"
#include <iostream>
#include <time.h>

int pick_card() {
    srand(time(NULL));
    a = rand();
    a = (a % 10) + 1;
    same = true;
    while (same == true) {
        same = false;
        for (int j = 0; j < 9; j++) {
            if (a == card[j]) {
                same = true;
                a = rand();
                a = (a % 10) + 1;
            }
        }
    }
    card[c] = a;
    c = c + 1;
    return (a);
}

int clear_card() {

    for (j = 0; j < 9; j++) {
        card[j] = NULL;
        return 0;
    }
}

int winer(int a, int b) {
    if (a == b) {
        printf("draw  ;-; \n");
        return 0;
    }
    if (a > b) {
        printf("hero is winner  ^^ \n");
        return 0;
    }
    if (a < b) {
        printf("hero is lose  TT \n");
        return 0;
    }
}

int too_more(int a) {
    if (a > 21) {
        return(1);
    }
    else {
        return(0);
    }
}
