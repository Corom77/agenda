#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <timer.h>
#include "list.h"



void tab(int valeur, int* res) {
    int cellulepaire;
    //int cont = (valeur / 2) - 1;
   // int nbr = valeur % 2;
    //if (nbr == 1) { cellulepaire = valeur - 1; } else { cellulepaire = valeur; }

    for (int i = 1; i <= valeur; i++) {
        res[i] = 0;
    }
// boucle cont ne marche pas
    for (int a = 0; a <= valeur; a += 2) { res[a] = res[a] + 1; }
    for (int a = 0; a <= valeur; a += 4) {res[a] = res[a] + 1;}
    //for (int a = 0; a <= valeur; a += 8) {res[a] = res[a] + 1;}
}

void arraytolist( int n, int valeur,int levels){
   
    for( int i=0,i<= valeur,i++){
     int levels[valeur];
    tab(valeur,levels);
    CreateList(valeur);
    add_cell(tab[i+1],s_sk_cell.head[i] );
    
    }

int main(){

/*--------------------------PARTIE 1 -------------------------------------*//*
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
*/
/*------------------------------------------------------------------------------*/
/*partie 2--------------------------------------------------------*/
  int n;
    scanf("%d",&n);
    int valeur = pow(2,n)-1;
    int levels[valeur];
    tab(valeur,levels);
    for (int i =1;i<=valeur;i++){printf("[%d]",levels[i]);} 

// ------------------------------------------------------------------
return 0;

}
