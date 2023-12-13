#include "mycustom.h"

/**
 * chain_is_true - Tests if the current character
 * in the buffer is a chain delimiter.
 *
 * @info: Pointer to the parameter struct.
 * @buf: The character buffer.
 * @current_position: Address of the current position in buf.
 *
 * Return: 1 if it is a chain delimiter, 0 otherwise.
 */
int chain_is_true(info_t *info, char *buf, size_t *current_position)
{
	size_t index = *current_position;

	if (buf[index] == '|' && buf[index + 1] == '|')
	{
		buf[index] = 0;
		index++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[index] == '&' && buf[index + 1] == '&')
	{
		buf[index] = 0;
		index++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[index] == ';')
	{
		buf[index] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*current_position = index;
	return (1);
}

/**
 * checking_the_chain - Checks if we should continue chaining
 * based on the last status.
 *
 * @info: Pointer to the parameter struct.
 * @buf: The character buffer.
 * @current_position: Address of the current position in buf.
 * @i: Starting position in buf.
 * @len: Length of buf.
 *
 * Description: This function checks the command buffer type
 * and updates the buffer
 * according to the chaining logic based on the last status.
 */
void checking_the_chain(info_t *info, char *buf,
		size_t *current_position, size_t i, size_t len)
{
	size_t index = *current_position;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			index = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			index = len;
		}
	}

	*current_position = index;
}

/**
 * alias_changed - Replaces an alias in the tokenized string.
 *
 * @info: Pointer to the parameter struct.
 *
 * Return: 1 if the alias is replaced, 0 otherwise.
 *
 * Description: This function iterates through a limited
 * number of iterations (10) to find and replace an alias
 * in the tokenized string, updating the parameter struct.
 */
int alias_changed(info_t *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_begins_here(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = my_strchr(node->str, '=');
		if (!p)
			return (0);
		p = my_strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * vars_changed - Replaces variables in the tokenized string.
 *
 * @info: Pointer to the parameter struct.
 *
 * Return: 1 if variables are replaced, 0 otherwise.
 *
 * Description: This function iterates through the tokenized string,
 * identifies variables
 * prefixed with '$', and replaces them with corresponding values
 * from the environment or
 * predefined variables.
 */
int vars_changed(info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!my_strcmp(info->argv[i], "$?"))
		{
			string_changed(&(info->argv[i]),
						   my_strdup(digit_converter(info->status, 10, 0)));
			continue;
		}
		if (!my_strcmp(info->argv[i], "$$"))
		{
			string_changed(&(info->argv[i]),
						   my_strdup(digit_converter(getpid(), 10, 0)));
			continue;
		}
		node = node_begins_here(info->env, &info->argv[i][1], '=');
		if (node)
		{
			string_changed(&(info->argv[i]),
						   my_strdup(my_strchr(node->str, '=') + 1));
			continue;
		}
		string_changed(&info->argv[i], my_strdup(""));
	}
	return (0);
}

/**
 * string_changed - Replaces a string.
 *
 * @old: Address of the old string.
 * @new: New string.
 *
 * Return: 1 if the string is replaced, 0 otherwise.
 *
 * Description: This function replaces an old string with
 * a new one and updates the
 * address accordingly.
 */
int string_changed(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
