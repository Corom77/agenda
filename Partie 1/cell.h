//#ifndef CELL_H
//#define CELL_H
typedef struct s_sk_cell{
	int value;
	int level; //pour savoir quel niveau
	struct s_sk_cell **next;
}t_sk_cell;

t_sk_cell* CreateCell_level(int p_level, int val);
void Display_Cell(t_sk_cell* new_cell);

//#endif
