#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include "list.h"

int main(){

int val;
printf("Quel nombre de niveaux pour votre liste?\n");
scanf("%d",&val);
t_sk_list* new_list = CreateList(val);
Display_List(new_list);


int val_cell;
int lev_cell;
do{
printf("Valeur de la cellule à ajouter?\n");
scanf("%d",&val_cell);
printf("Nombre de niveaux de la cellule?\n");
scanf("%d",&lev_cell);

t_sk_cell* new_cell = CreateCell_level(lev_cell,val_cell);
add_cell(new_list,new_cell);
Display_List_(new_list);
}while(lev_cell<=val);
printf("Erreur: niv cellule > niv liste\n");

return 0;

}
