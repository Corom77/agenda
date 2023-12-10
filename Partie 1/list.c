#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

 

t_sk_list* CreateList(int max_lev){

	t_sk_list* new_list = (t_sk_list*)malloc(sizeof(t_sk_list));
	new_list->max_level = max_lev;

	new_list->head =(struct s_sk_cell**)malloc(max_lev*sizeof(struct s_sk_cell*));

	for(int i = 0; i<max_lev; i++)

		new_list->head[i] = NULL;
			
return new_list;
}




void add_cell_head(t_sk_list* l, t_sk_cell* c){


	if(l->max_level < c->level){
		printf("Cell level > max_level List");
		return;
	}
//si je pars d'un niv de liste à NULL
	
	else if(l->head[0] == NULL){
		for(int i = 0; i < c->level; i++){
			l->head[i] = c;
		}
	}
	else{
		for (int i = 0; i < c->level; i++){
			c->next[i] = l->head[i];
			l->head[i] = c;
		}
	}
}




void add_cell(t_sk_list* l, t_sk_cell* c){

	if(l->max_level < c->level){
		printf("Erreur: Cell level > List max level");
           	return;
	}
	else{

		for(int i = 0; i < c->level; i++){
			t_sk_cell* temp = l->head[i];
			//prev pointe derrière la tête de liste
			t_sk_cell* prev = NULL;

			//ajout list vide
			if(l->head[i] == NULL){
				l->head[i] = c;
				c->next[i] = NULL;
			}
			else {
				while(temp != NULL){
					if(temp->value > c->value){
						//si on a un élément dans la liste et qu'on veut ajouter une value plus grande
//initialisation de prev != temp pour éviter boucle sur lui même7

						if(prev!=NULL){
							prev->next[i] = c;
                                		}
						c->next[i] = temp;
						break;
						
						
					}
					else{
					       //on avance dans la liste
					       prev = temp;
                                               temp = temp->next[i];
				        
                                	    }
                             }
				//ajout en queue
				if(temp == NULL){
					prev->next[i] = c;
  				}
                        }
                                     
		}
}
}

/*Display_List => affiche la liste
           avec les niveaux vide*/



void Display_List(t_sk_list* new_list){
	if(new_list == NULL){
		printf("No list");
		return;
	}


	for(int i = 0; i<new_list->max_level;i++){
		printf("[list head_%d @-]-->",i);
	
	if(new_list->head[i] == NULL){
		printf("NULL\n");
	}
	else{
        	printf("%p\n",(void*)new_list->head[i]);
	}
        }

}



/*Display_List_ => Affiche la liste avec les cellules
                   sur chaques niveaux*/


void Display_List_(t_sk_list* new_list){
	if(new_list == NULL){
	   printf("No list\n");
	   return;
	}	
	  for(int i = 0; i<new_list->max_level;i++){
		printf("[list head_%d @-]-->",i);
		t_sk_cell* cur = new_list->head[i];
			while(cur != NULL){
			   printf("[%d|@-]-->",cur->value);
			   cur = cur->next[i];
			}
			printf("NULL\n");
		}
return;
}





