#include "mycustom.h"

/**
 * getenv_copy - Returns a copy of the environment strings.
 * @info: Structure containing potential arguments.
 *
 * Description:
 *    This function returns a copy of the environment strings stored in the
 *    info structure. If the environment has been modified, it updates the copy
 *    before returning.
 *
 * Return: A copy of the environment strings.
 */
char **getenv_copy(info_t *info)
{
	if (!info->environ || info->modified_env)
	{
		info->environ = strs_list(info->env);
		info->modified_env = 0;
	}

	return (info->environ);
}

/**
 * my_unsetenv - Remove an environment variable.
 * @info: Structure containing potential arguments.
 * @var: The string representing the environment variable property.
 *
 * Description:
 *    This function removes the specified environment variable
 *    from the environment
 *    in the info structure.
 *
 * Return: 1 on successful removal, 0 otherwise.
 */
int my_unsetenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = begin_here(node->str, var);
		if (p && *p == '=')
		{
			info->modified_env = remove_first_node(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->modified_env);
}

/**
 * my_setenv - Initialize a new environment variable or modify an existing one.
 * @info: Structure containing potential arguments.
 * @var: The string representing the environment variable property.
 * @value: The string representing the environment variable value.
 *
 * Description:
 * This function initializes a new environment variable
 * or modifies an existing one
 * in the environment stored in the info structure.
 *
 * Return: Always 0.
 */
int my_setenv(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(my_strlen(var) + my_strlen(value) + 2);
	if (!buf)
		return (1);
	my_strcpy(buf, var);
	my_strcat(buf, "=");
	my_strcat(buf, value);
	node = info->env;
	while (node)
	{
		p = begin_here(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->modified_env = 1;
			return (0);
		}
		node = node->next;
	}
	append_end_node(&(info->env), buf, 0);
	free(buf);
	info->modified_env = 1;
	return (0);
}
