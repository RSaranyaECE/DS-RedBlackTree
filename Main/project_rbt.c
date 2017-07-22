#include <stdio.h>
#include <rb_tree.h>

/************************************************* Red Black Tree ****************************************************/
int main()
{
	int option, limit, value, index;
	char ch;

	rbt_t *root = NULL, *min, *max;

	do
	{
		/* Print options */
		printf("OPTIONS:\n\t1. Insert\n\t2. Search\n\t3. Find Min\n\t4. Find Max\n\t5. Delete Element\n\t6. Print Tree\n\t7. Exit\n\n");
	
		/* Read options */
		printf("Enter the option : ");
		scanf("%d", &option);

		switch (option)
		{
			/* Insert */
			case 1:
	
				/* Read limit */
				printf("Enter the no. of elements to be inserted : ");
				scanf("%d", &limit);

				/* Read the values */
				printf("Enter the elements : ");
				for (index = 0; index < limit; index++)
				{
					scanf("%d", &value);
					root = rbt_insert(root, value);
				}

				break;

			/* Search Element */
			case 2:

				/* Read the element */
				printf("Enter the element to be searched : ");
				scanf("%d", &value);

				/* Return value is 1 then print element is found */
				if(rbt_search_node(root, value))
					printf("Value %d is found\n", value);

				/* Return value is 0 then print element is not found */
				else
					printf("Value not found\n");

				break;

			/* Find Min */
			case 3:

				min = rbt_find_min(root);
				
				/* Print Min value */
				if (min != NULL)
					printf("Min : %d\n", min->data);

				break;

			/* Find Max */
			case 4:

				max = rbt_find_max(root);
			
				/* Print Max value */
				if (max != NULL)
					printf("Max : %d\n", max->data);

				break;

			/* Delete Element */
			case 5:

				printf("Enter the elements : ");
				scanf("%d", &value);
				
				root = rbt_delete_node(root, root, value);
				
				break;

			/* Print tree */
			case 6:

				rbt_print(root);
				
				break;

			/* Exit */
			case 7:

				return 0;

			/* Error print */
			default:

				printf("Invalid Option\n");
		}

		/* Read ch */
		printf("Do you want to continue...");
		scanf("\n%c", &ch);

	/* If ch is y/Y then continue the loop */
	}while (ch == 'y' || ch == 'Y');

	return 0;
}
