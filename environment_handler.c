#include "mycustom.h"

/**
 * _env - Prints the current environment.
 * @info: Structure containing potential arguments. Used to maintain
 *        a constant function prototype.
 *
 * This function prints the current environment by iterating through
 * the linked list of environment strings and using print_strings_list.
 *
 * Return: Always 0
 */
int _env(info_t *info)
{
	print_strings_list(info->env);
	return (0);
}

/**
 * my_getenv - Gets the value of an environment variable.
 * @info: Structure containing potential arguments. Used to maintain
 *          a constant function prototype.
 * @var_name: Environment variable name.
 *
 * This function retrieves the value of the specified environment variable
 * by iterating through the linked list of environment strings.
 *
 * Return: The value of the specified environment variable.
 */
char *my_getenv(info_t *info, const char *var_name)
{
	list_t *node = info->env;
	char *env_var_ptr;

	while (node)
	{
		env_var_ptr = begin_here(node->str, var_name);
		if (env_var_ptr && *env_var_ptr)
			return (env_var_ptr);
		node = node->next;
	}
	return (NULL);
}

/**
 * set_myenv - Initializes a new environment variable
 * or modifies an existing one.
 * @info: Structure containing potential arguments. Used to maintain
 *          a constant function prototype.
 *
 * This function initializes a new environment variable
 * or modifies an existing one
 * by calling the my_setenv function and checking
 * for the correct number of arguments.
 *
 * Return: Always 0
 */
int set_myenv(info_t *info)
{
	if (info->argc != 3)
	{
		_myputs("Invalid number of arguments\n");
		return (1);
	}
	if (my_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * unset_myenv - Removes an environment variable.
 * @info: Structure containing potential arguments. Used to maintain
 *          a constant function prototype.
 *
 * This function removes an environment variable by calling the my_unsetenv
 * function and checking for the correct number of arguments.
 *
 * Return: Always 0
 */
int unset_myenv(info_t *info)
{
	int index;

	if (info->argc == 1)
	{
		_myputs("Insufficient number of arguments.\n");
		return (1);
	}
	for (index = 1; index <= info->argc; index++)
		my_unsetenv(info, info->argv[index]);

	return (0);
}

/**
 * fill_up_linked_env - Populates the environment linked list.
 * @info: Structure containing potential arguments. Used to maintain
 *        a constant function prototype.
 *
 * This function populates the environment linked list by iterating through
 * the array of environment strings and using append_end_node.
 *
 * Return: Always 0
 */
int fill_up_linked_env(info_t *info)
{
	list_t *node = NULL;
	size_t index;

	for (index = 0; environ[index]; index++)
		append_end_node(&node, environ[index], 0);
	info->env = node;
	return (0);
}
