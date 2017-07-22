#ifndef RB_TREE_H
#define RB_TREE_H

#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_COLOR_RED     "\x1b[31m"

#define BLACK 0
#define RED 1
#define CHECK 2
#define LEFT 3
#define RIGHT 4
#define STOP 5

typedef struct _rbtree
{
	int data;
	int color;
	struct _rbtree *left, *right;
} rbt_t;

rbt_t *rbt_insert(rbt_t *root, int value);
void rbt_print(rbt_t *root);

rbt_t *rbt_find_min(rbt_t *root);
rbt_t *rbt_find_max(rbt_t *root);
int rbt_search_node(rbt_t *root, int element);
rbt_t *rbt_delete_node(rbt_t *m_root, rbt_t *root, int value);

int select_case(rbt_t *m_root, rbt_t **root);
void man_input(rbt_t **root);

#endif
