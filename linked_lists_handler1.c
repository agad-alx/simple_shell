#include "mycustom.h"

/**
 * length_linked_list - Determines the length of a linked list.
 * @current: Pointer to the first node.
 *
 * Description:
 *   This function traverses the linked list starting
 *   from the given node
 *   and counts the number of nodes in the list.
 *
 * Return: Size of the linked list.
 */
size_t length_linked_list(const list_t *current)
{
	size_t count = 0;

	while (current)
	{
		current = current->next;
		count++;
	}
	return (count);
}

/**
 * strs_list - Returns an array of strings from the list->str field.
 * @head: Pointer to the first node.
 *
 * Description:
 *   This function creates and returns an array of strings,
 *   where each string is a duplicate
 *   of the corresponding node's str field in the linked list.
 *
 * Return: Array of strings or NULL on failure.
 */
char **strs_list(list_t *head)
{
	list_t *node = head;
	size_t array_size = length_linked_list(head);
	size_t array_index;
	char **strs;
	char *str;

	if (!head || !array_size)
		return (NULL);

	strs = malloc(sizeof(char *) * (array_size + 1));
	if (!strs)
		return (NULL);

	for (array_index = 0; node; node = node->next, array_index++)
	{
		size_t k;
		str = malloc(my_strlen(node->str) + 1);
		if (!str)
		{
			for (k = 0; k < array_index; k++)
				free(strs[k]);
			free(strs);
			return (NULL);
		}

		str = my_strcpy(str, node->str);
		strs[array_index] = str;
	}

	strs[array_index] = NULL;
	return (strs);
}

/**
 * list_output - Prints all elements of a list_t linked list.
 * @current: Pointer to the first node.
 *
 * Description:
 *   This function prints the content
 *   of each node in the linked list,
 *   including the node's number, string,
 *   and a newline character.
 *
 * Return: Size of the linked list.
 */
size_t list_output(const list_t *current)
{
	size_t count = 0;

	while (current)
	{
		my_puts(digit_converter(current->num, 10, 0));
		my_putchar(':');
		my_putchar(' ');
		my_puts(current->str ? current->str : "(nil)");
		my_puts("\n");
		current = current->next;
		count++;
	}

	return (count);
}

/**
 * node_begins_here - Returns the node
 * whose string starts with a prefix.
 * @node: Pointer to the list head.
 * @prefix: String to match.
 * @c: The next character after the prefix to match.
 *
 * Description:
 *   This function searches the linked list
 *   for a node whose string starts
 *   with the specified prefix.
 *   It can also check if the next character
 *   after the prefix matches a given character.
 *
 * Return: Matching node or NULL if not found.
 */
list_t *node_begins_here(list_t *node, char *prefix, char c)
{
	char *match = NULL;

	while (node)
	{
		match = begin_here(node->str, prefix);
		if (match && ((c == -1) || (*match == c)))
			return (node);
		node = node->next;
	}

	return (NULL);
}

/**
 * fetch_first_node - Gets the index of a node.
 * @head: Pointer to the list head.
 * @node: Pointer to the node.
 *
 * Description:
 *   This function determines the index
 *   of a given node in the linked list.
 *   If the node is not found, it returns -1.
 *
 * Return: Index of the node or -1 if not found.
 */
ssize_t fetch_first_node(list_t *head, list_t *node)
{
	size_t index = 0;

	while (head)
	{
		if (head == node)
			return (index);
		head = head->next;
		index++;
	}

	return (-1);
}
