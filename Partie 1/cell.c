#include "cell.h"
#include <stddef.h>  //à mettre dans main.c
#include <stdio.h> //à mettre dans le main
#include <stdlib.h> //main

/*renvoie la nouvelle cellule 
  t_sk_cell -> pointeur*/

t_sk_cell* CreateCell_level(int p_level,int val){


 t_sk_cell *new_cell = (t_sk_cell*)malloc(sizeof(t_sk_cell));
    new_cell->value = val;
    new_cell->level = p_level;

    // Correction ici pour allouer p_level + 1 pointeurs
    new_cell->next = (struct s_sk_cell**)malloc((p_level + 1) * sizeof(struct s_sk_cell*));

    for (int i = 0; i <= p_level; i++) {
        new_cell->next[i] = NULL;
    }
    return new_cell;
}

void Display_Cell(t_sk_cell* new_cell) {
    if (!new_cell) {
        printf("No Cell\n");
        return;
    }

    printf("[ %d | @-]-->", new_cell->value);

    for (int i = 0; i < new_cell->level; i++) {
        if (new_cell->next[i]) {
            printf("[%d | @-]-->", new_cell->next[i]->value);
        } else {
            printf("NULL");
        }
    }

    printf("\n");
}

