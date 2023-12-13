#include "mycustom.h"

/**
 * node_tolist_index - Adds a node to the start of the list.
 * @head: Address of the pointer to the start node.
 * @str: String field of the node.
 * @num: Node index used by history.
 *
 * Description:
 *    This function adds a node to the start of the list.
 *    If successful, it allocates
 *    memory for the new node, initializes its fields,
 *    and returns the address of the
 *    new start node; otherwise, it returns NULL.
 *
 * Return: Address of the new start node or NULL on failure.
 */
list_t *node_tolist_index(list_t **head, const char *str, int num)
{
	list_t *new_start;

	if (!head)
		return (NULL);

	new_start = malloc(sizeof(list_t));
	if (!new_start)
		return (NULL);

	my_mem_set((void *)new_start, 0, sizeof(list_t));
	new_start->num = num;

	if (str)
	{
		new_start->str = my_strdup(str);
		if (!new_start->str)
		{
			free(new_start);
			return (NULL);
		}
	}

	new_start->next = *head;
	*head = new_start;
	return (new_start);
}

/**
 * append_end_node - Adds a node to the end of the list.
 * @head: Address of the pointer to the start node.
 * @str: String field of the node.
 * @num: Node index used by history.
 *
 * Description:
 *    This function adds a node to the end of the list.
 *    If successful, it allocates
 *    memory for the new node, initializes its fields,
 *    and returns the address of the
 *    new node; otherwise, it returns NULL.
 *
 * Return: Address of the new node or NULL on failure.
 */
list_t *append_end_node(list_t **head, const char *str, int num)
{
	list_t *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);

	my_mem_set((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;

	if (str)
	{
		new_node->str = my_strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}

	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;

	return (new_node);
}

/**
 * print_strings_list - Prints only the str element of a list_t linked list.
 * @current: Pointer to the start node.
 *
 * Description:
 *    This function prints only the str element
 *    of a list_t linked list, handling
 *    NULL values, and returns the size of the list.
 *
 * Return: Size of the list.
 */
size_t print_strings_list(const list_t *current)
{
	size_t i = 0;

	while (current)
	{
		my_puts(current->str ? current->str : "(nil)");
		my_puts("\n");
		current = current->next;
		i++;
	}
	return (i);
}

/**
 * remove_first_node - Deletes node at given index.
 * @start: Address of the pointer to the start node.
 * @index: Index of node to delete.
 *
 * Description:
 *    This function deletes the node at the given index in the list.
 *    If successful,
 *    it returns 1; otherwise, it returns 0.
 *
 * Return: 1 on success, 0 on failure.
 */
int remove_first_node(list_t **start, unsigned int index)
{
	list_t *node, *prev;
	unsigned int i = 0;

	if (!start || !*start)
		return (0);

	if (!index)
	{
		node = *start;
		*start = (*start)->next;
		free(node->str);
		free(node);
		return (1);
	}

	node = *start;
	while (node)
	{
		if (i == index)
		{
			prev->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		prev = node;
		node = node->next;
	}
	return (0);
}

/**
 * give_up_list - Frees all nodes of a list.
 * @start_ptr: Address of the pointer to the start node.
 *
 * Description:
 *    This function frees all nodes of a list
 *    and sets the start pointer to NULL,
 *    handling NULL values.
 *
 * Return: Void.
 */
void give_up_list(list_t **start_ptr)
{
	list_t *node, *next, *start;

	if (!start_ptr || !*start_ptr)
		return;

	start = *start_ptr;
	node = start;
	while (node)
	{
		next = node->next;
		free(node->str);
		free(node);
		node = next;
	}
	*start_ptr = NULL;
}
