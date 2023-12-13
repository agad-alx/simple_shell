/*------- alias_handler.c -------*/

#include "mycustom.h"

/**
 * display_history_list - Displays the history list, one command per line,
 *                        preceded with line numbers starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 *        a constant function prototype.
 *
 * Description:
 * This function displays the history list with each command on a new line,
 * each preceded by line numbers starting from 0.
 *
 * Return: Always 0
 */
int display_history_list(info_t *info)
{
	list_output(info->history);
	return (0);
}

/**
 * alias_is_unset - Unsets an alias.
 * @info: Parameter struct.
 * @str: The string alias.
 *
 * Description:
 * This function unsets the alias specified by the given string.
 *
 * Return: Always 0 on success, 1 on error
 */
int alias_is_unset(info_t *info, char *str)
{
	char *alias_ptr, alias_char;
	int result;

	alias_ptr = my_strchr(str, '=');
	if (!alias_ptr)
		return (1);
	alias_char = *alias_ptr;
	*alias_ptr = 0;
	result = remove_first_node(&(info->alias),
		fetch_first_node(info->alias, node_begins_here(info->alias, str, -1)));
	*alias_ptr = alias_char;
	return (result);
}

/**
 * alias_to_set - Sets an alias to a string.
 * @info: Parameter struct.
 * @str: The string alias.
 *
 * Description:
 * This function sets the alias specified by the given string to a new value.
 *
 * Return: Always 0 on success, 1 on error
 */
int alias_to_set(info_t *info, char *str)
{
	char *alias_ptr;

	alias_ptr = my_strchr(str, '=');
	if (!alias_ptr)
		return (1);
	if (!*++alias_ptr)
		return (alias_is_unset(info, str));

	alias_is_unset(info, str);
	return (append_end_node(&(info->alias), str, 0) == NULL);
}

/**
 * alias_to_print - Prints an alias string.
 * @node: The alias node.
 *
 * Description:
 * This function prints the specified alias string.
 *
 * Return: Always 0 on success, 1 on error
 */
int alias_to_print(list_t *node)
{
	char *alias_ptr = NULL, *alias_char_ptr = NULL;

	if (node)
	{
		alias_ptr = my_strchr(node->str, '=');
		for (alias_char_ptr = node->str; alias_char_ptr <= alias_ptr;
				alias_char_ptr++)
			my_putchar(*alias_char_ptr);
		my_putchar('\'');
		my_puts(alias_ptr + 1);
		my_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _alias - Mimics the alias builtin
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *
 * Description:
 * This function mimics the behavior of the alias builtin command.
 *
 * Return: Always 0
 */
int _alias(info_t *info)
{
	int i = 0;
	char *alias_ptr = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			alias_to_print(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		alias_ptr = my_strchr(info->argv[i], '=');
		if (alias_ptr)
			alias_to_set(info, info->argv[i]);
		else
			alias_to_print(node_begins_here(info->alias, info->argv[i], '='));
	}

	return (0);
}
