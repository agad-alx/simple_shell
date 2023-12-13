#include "mycustom.h"

/**
 * initiating_info - Initializes the info_t struct.
 * @info: Pointer to the info_t struct to be initialized.
 *
 * This function initializes the specified info_t structure, setting several
 * fields to default values, such as arg, argv, path, and argc.
 */
void initiating_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * setting_up_info - Initializes the info_t struct.
 * @info: Pointer to the info_t struct to be initialized.
 * @av: Argument vector.
 *
 * This function initializes the specified info_t structure using the given
 * argument vector (av). It sets fname, argv, and argc based on the provided
 * arguments. If arg is not NULL, it also allocates and populates argv based on
 * the contents of arg. Additionally, it performs alias
 * and variable replacement.
 */
void setting_up_info(info_t *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = split_into_words(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = my_strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		alias_changed(info);
		vars_changed(info);
	}
}

/**
 * clearing_info - Frees info_t struct fields.
 * @info: Pointer to the info_t struct to be cleared.
 * @full: Flag indicating whether to free all fields.
 *
 * This function frees the dynamically allocated fields in the specified
 * info_t structure. If the full flag is set, it frees additional fields such
 * as arg, env, history, alias, environ, and cmd_buf. It also closes the
 * read file descriptor if it's greater than 2.
 */
void clearing_info(info_t *info, int full)
{
	release_str(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (full)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			give_up_list(&(info->env));
		if (info->history)
			give_up_list(&(info->history));
		if (info->alias)
			give_up_list(&(info->alias));
		release_ptr((void **)info->environ);
		info->environ = NULL;
		release_ptr((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		my_putchar(BUF_FLUSH);
	}
}
