#include <stdio.h>
#include <stdlib.h>
#include <rb_tree.h>

/* Right Rotation */
int right_rotation(rbt_t **g_parent)
{
	/* Parent */
	rbt_t *parent = (*g_parent)->left;

	/* Rotation */
	(*g_parent)->left = parent->right;
	parent->right = *g_parent;
	*g_parent = parent;

	/* Recolor */
	parent->color = BLACK;
	parent->right->color = RED;
}

/* Left Rotation*/
int left_rotation(rbt_t **g_parent)
{
	/* Parent */
	rbt_t *parent = (*g_parent)->right;
	
	/* Rotation */
	(*g_parent)->right = parent->left;
	parent->left = *g_parent;
	*g_parent = parent;

	/* Recolor */
	parent->color = BLACK;
	parent->left->color = RED;
}

/* Left Triangle Rotation */
int left_triangle_rotation(rbt_t **g_parent)
{
	/* Parent and Child*/
	rbt_t *parent = (*g_parent)->left;
	rbt_t *child = (*g_parent)->left->right;

	/* Rotation */
	(*g_parent)->left = child;
	parent->right = child->left;
	child->left = parent;
}

/* Right Triangle Rotation */
int right_triangle_rotation(rbt_t **g_parent)
{
	/* Parent and Child */
	rbt_t *parent = (*g_parent)->right;
	rbt_t *child = (*g_parent)->right->left;

	/* Rotation */
	(*g_parent)->right = child;
	parent->left = child->right;
	child->right = parent;
}

/* Check Properties */
void check_properties(rbt_t *m_root, rbt_t **root, int flag)
{
	/* Left parent */
	if (flag == LEFT)
	{
		/* Sibiling is Red */
		if ((*root)->right != NULL && (*root)->right->color == RED)
		{
			/* Recolor sibiling and Parent */
			(*root)->right->color = BLACK;
			(*root)->left->color = BLACK;

			/* Recolor parent if its not root */
			if (*root != m_root)
				(*root)->color = RED;
		}

		/* No sibiling or Sibiling is Black */
		else if ((*root)->right == NULL || (*root)->right->color == BLACK)
		{
			/* Left parent and Left Child -> Left Rotation  */
			if ((*root)->left->left != NULL && (*root)->left->left->color == RED)
				right_rotation(root);
			
			/* Left Parent and Right Child -> Right and Left Rotation */
			else if ((*root)->left->right != NULL && (*root)->left->right->color == RED)
			{
				left_triangle_rotation(root);
				right_rotation(root);
			}
		}
	}

	/* Right Parent */
	if (flag == RIGHT)
	{
		/* Sibiling is Red */
		if ((*root)->left != NULL && (*root)->left->color == RED)
		{
			/* Recolor sibiling and Parent */
			(*root)->right->color = BLACK;
			(*root)->left->color = BLACK;

			/* Recolor parent if its not root */
			if (*root != m_root)
				(*root)->color = RED;
		}

		/* No sibiling or Sibiling is Black */
		else if ((*root)->left == NULL || (*root)->left->color == BLACK)
		{
			/* Right parent and Right Child -> Right Rotation  */
			if ((*root)->right->right != NULL && (*root)->right->right->color == RED)
				left_rotation(root);
			
			/* Right Parent and Left Child -> Left and Right Rotation */
			else if ((*root)->right->left != NULL && (*root)->right->left->color == RED)
			{
				right_triangle_rotation(root);
				left_rotation(root);
			}
		}
	}
}

// Insert tree
int insert_value(rbt_t *m_root, rbt_t **root, int value)
{
	int r_value;

	// Create a node
	if (*root == NULL)
	{
		*root = malloc(sizeof(rbt_t));

		(*root)->left = NULL;
		(*root)->right = NULL;
		(*root)->data = value;
		(*root)->color = RED;

		return (*root)->color;
	}

	// value is lessthan then goto right side of the tree
	if (value > (*root)->data)
	{
		r_value = insert_value(m_root, &(*root)->right, value);
		
		/* R_value is CHECK then call check_properties function with RIGHT */
		if (r_value == CHECK)
		{
			check_properties(m_root, root, RIGHT);
			return (*root)->color;
		}
	}

	// value is greaterthan then goto right side of the tree
	else if (value < (*root)->data)
	{
		r_value = insert_value(m_root, &(*root)->left, value);
		
		/* R_value is CHECK then call check_properties function LEFT */
		if (r_value == CHECK)
		{
			check_properties(m_root, root, LEFT);
			return (*root)->color;
		}
	}

	// Error print
	else
	{
		printf("Error..The value is already present in the tree\n");
		return -1;
	}

	/* R_value and node color same then return CHECK */
	if ((*root)->color == r_value)
		return CHECK;

	/* Error Return */
	else if (r_value == -1)
		return r_value;

	/* Return node color */
	return (*root)->color;
}

/* Insert Function */
rbt_t *rbt_insert(rbt_t *root, int value)
{
	/* Empty Tree */
	if (root == NULL)
	{
		/* Create node and insert with black color */
		root = malloc(sizeof (rbt_t));	

		root->left = NULL;
		root->right = NULL;
		root->data = value;
		root->color = BLACK;
	}

	/* Call insert_value Function */
	else
		insert_value(root, &root, value);

	/* Return root */
	return root;
}

// Height of tree
int rbt_height_of_tree(rbt_t *root)
{
	if (root != NULL)
	{
		// height of leftside of root
		int left = 1 + rbt_height_of_tree(root->left);
	
		// height of rightside of root
		int right = 1 + rbt_height_of_tree(root->right);

		// left value is greater that return left
		if (left >= right)
			return left;

		// return right
		else
			return right;
	}

	// root is null then return -1
	else
		return 0;
}

// BFS_print_level
void rbt_print_level(rbt_t *root, int breadth)
{
	// when breadth reaches 0 then print root data
	if (breadth == 0)
	{
		if (root != NULL)
		{
			if (root->color == RED)
				printf(ANSI_COLOR_RED "%d" ANSI_COLOR_RESET "\t", root->data);
	
			else
				printf("%d\t", root->data);
		}
	}

	// root is not null then call the function recursively with root left node and right node with decrement the breadth
	else if (root != NULL)
	{
		rbt_print_level(root->left, breadth - 1);		
		rbt_print_level(root->right, breadth - 1);		
	}
}

// BFS_print tree
void rbt_print(rbt_t *root)
{
	if (root == NULL)
	{
		printf("Empty tree\n");
		return;
	}
	
	// calculate level
	int no_level = rbt_height_of_tree(root), index;

	// call rbt_print level function upto no_level
	for (index = 0; index < no_level; index++)
	{
		rbt_print_level(root, index);
		printf("\n");
	}
}

/* Find Min */
rbt_t *rbt_find_min(rbt_t *root)
{
	if (root == NULL)
	{
		printf("Empty tree\n");
		return NULL;
	}

	/* Return Left most node */
	else if (root->left == NULL)
		return root;
	
	return rbt_find_min(root->left);
}

/* Find Max */
rbt_t *rbt_find_max(rbt_t *root)
{
	if (root == NULL)
	{
		printf("Empty tree\n");
		return NULL;
	}

	/* Return Right most node */
	else if (root->right == NULL)
		return root;
	
	return rbt_find_max(root->right);
}

// Search node
int rbt_search_node(rbt_t *root, int element)
{
	// root is null then return 0
	if (root == NULL)
		return 0;

	// element is found return 1
	if (root->data == element)
		return 1;

	else
	{
		// elment found in left side return 1
		if (rbt_search_node(root->left, element))
			return 1;
		
		// elment found in right side return 1
		else if (rbt_search_node(root->right, element))
			return 1;

		// element is not found return 0
		else
			return 0;
	}
}

int flag;

int case1(rbt_t *m_root, rbt_t **root)
{
	if (*root == m_root)
		return STOP;
}

int case2(rbt_t *m_root, rbt_t **root)
{
	left_rotation(root);
	select_case(m_root, &(*root)->left);
}
/*
int find_parent(rbt_t *root, rbt_t **p_root, int element)
{
	// root is null then return 0
	if (root == NULL)
		return 0;

	// element is found return 1
	if (root->data == element)
		return 1;

	else
	{
		// elment found in left side return 1
		if (find_parent(root->left, p_root, element))
		{
			*p_root = root;
			return 0;
		}
		// elment found in right side return 1
		else if (find_parent(root->right, p_root, element))
		{
			*p_root = root;
			return 0;
		}

		// element is not found return 0
		else
			return 0;
	}
}
*/

int sc_flag;

int case3(rbt_t *m_root, rbt_t **root)
{
	(*root)->right->color = RED;

	if (*root == m_root)
		case1(m_root, root);

	else
	{
	/*	rbt_t *p_root;
		find_parent(m_root, &p_root, (*root)->data);
		printf("%d--------ins--\n", p_root->data);
		select_case(m_root, &p_root);*/

		sc_flag = 1;
	}
}

int case4(rbt_t *m_root, rbt_t **root)
{
	(*root)->color = BLACK;
	(*root)->right->color = RED;

	return STOP;
}

int case5(rbt_t *m_root, rbt_t **root)
{
	right_triangle_rotation(root);

	(*root)->right->color = BLACK;
	(*root)->right->right->color = RED;
	select_case(m_root, root);
}

int case6(rbt_t *m_root, rbt_t **root)
{
	int f = 1;
	if (*root == m_root)
		f = 0;
	
	/* Parent */
	rbt_t *parent = (*root)->right;
	
	/* Rotation */
	(*root)->right = parent->left;
	parent->left = *root;
	*root = parent;

	parent->left->color = BLACK;		
	parent->right->color = BLACK;

	if (parent->left->left == NULL && f)
		parent->color = RED;

	return STOP;
}

int select_case(rbt_t *m_root, rbt_t **root)
{
	if ((*root)->right->color == BLACK && (*root)->right->right != NULL && (*root)->right->right->color == RED)
	{
		case6(m_root, root);
	}
	else if ((*root)->color == RED)
		case4(m_root, root);

	else if ((*root)->right->color == RED)
	{
		if ((*root)->right->left == NULL && (*root)->right->right == NULL || (*root)->right->left->color == BLACK && (*root)->right->right->color == BLACK)
			case2(m_root, root);
	}
	
	else if ((*root)->right->color == BLACK)
	{
		if ((*root)->right->left == NULL && (*root)->right->right == NULL || (*root)->right->left->color == BLACK && (*root)->right->right->color == BLACK)
			case3(m_root, root);

		else if ((*root)->right->left->color == RED && ((*root)->right->right == NULL || (*root)->right->right->color == BLACK))
			case5(m_root, root);
	}
}

int sc, sc_1;

// Delete a node from tree
rbt_t *rbt_delete_node(rbt_t *m_root, rbt_t *root, int value)
{
	// Error print
	if (root == NULL)
		printf("Empty tree\n");

	else
	{
		// search left side nodes
		if(root->left != NULL && root->data > value)
		{
			root->left = rbt_delete_node(m_root, root->left, value);

			if (flag)
			{
				flag = 0;
				select_case(m_root, &root);
				
				if (sc_flag)
				{
					sc_flag = 0;
					sc = 1;
				}
			}
		}

		// search right side nodes
		else if (root->right != NULL && root->data < value)
		{
			root->right = rbt_delete_node(m_root, root->right, value);
		
			if (flag)
			{
				flag = 0;
				select_case(m_root, &root);
				
				if (sc_flag)
				{
					sc_flag = 0;
					sc = 1;
				}
			}
		}

		// element is found
		else if (root->data == value)
		{
			// delete node having only right child
			if (root->left == NULL)
			{
				// copy left node
				rbt_t *temp = root->right;
				
				if (root->color == BLACK)
				{
					if(temp != NULL)
						temp->color = BLACK;

					else
						flag = 1;
				}

				// free root
				free(root);
				// return copied left node
				return temp;
			}

			// delete node having only left child
			else if (root->right == NULL)
			{
				// copy left node
				rbt_t *temp = root->left;
				
				if (root->color == BLACK)
				{
					if(temp != NULL)
						temp->color = BLACK;
					
					else
						flag = 1;
				}

				// free root
				free(root);
				// return copied left node
				return temp;
			}

			// delete node having 2 children
			else
			{
				// find min in right side of root
				rbt_t *min = rbt_find_min(root->right);

				// copy data
				root->data = min->data;

				// recursive call to delete dublication of min
				root->right = rbt_delete_node(m_root, root->right, min->data);
				
				if (flag)
				{
					flag = 0;
					select_case(m_root, &root);
				}
			}		
		}

		// Error if element is not found
		else
			printf("Element is not present\n");
	}

	if (sc_1)
	{
		sc_1 = 0;
		select_case(m_root, &root);
	}
	if (sc)
	{
		sc = 0;
		sc_1 = 1;
	}

	return root;
}

// Insert tree
rbt_t *man_insert_tree(rbt_t *root, int value, int color)
{
	// Create a node
	if (root == NULL)
	{
		root = malloc(sizeof(rbt_t));

		root->left = NULL;
		root->right = NULL;
		root->data = value;
		root->color = color;

		return root;
	}

	// value is lessthan then goto right side of the tree
	if (value > root->data)

		root->right = man_insert_tree(root->right, value, color);

	// value is greaterthan then goto right side of the tree
	else if (value < root->data)

		root->left = man_insert_tree(root->left, value, color);

	// Error print
	else
	{
		printf("Error..The value is already present in the tree\n");
	
		return root;
	}

	// return created node addrs
	return root;
}

void man_input(rbt_t **root)
{
	int value, color;

	printf("Enter the value : ");
	scanf("%d", &value);

	printf("Enter the color : ");
	scanf("%d", &color);

	*root = man_insert_tree(*root, value, color);
}
