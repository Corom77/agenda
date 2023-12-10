#include "cell.h"

typedef struct s_sk_list{
	struct s_sk_cell **head;
	int max_level;
}t_sk_list;

t_sk_list* CreateList(int);
void Display_List(t_sk_list*);
void Display_List_(t_sk_list*);
void add_cell(t_sk_list*,t_sk_cell*);
void add_cell_head(t_sk_list*,t_sk_cell*);

