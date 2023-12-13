#include "mycustom.h"

/**
 * hsh - main shell loop
 * @info: the parameter & return info struct
 * @av: the argument vector from main()
 *
 * Description:
 *	This function represents the main loop of the shell.
 *	It continuously
 *	reads input, processes built-in commands
 *	or executes external commands
 *	in a child process.
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(info_t *info, char **av)
{
	ssize_t read_result = 0;
	int builtin_result = 0;

	while (read_result != -1 && builtin_result != -2)
	{
		initiating_info(info);
		if (interactive(info))
			my_puts("$ ");
		_myputchar(BUF_FLUSH);
		read_result = input_minus_newline(info);
		if (read_result != -1)
		{
			setting_up_info(info, av);
			builtin_result = _builtin_cmd_search(info);
			if (builtin_result == -1)
				_cmd_search(info);
		}
		else if (interactive(info))
			my_putchar('\n');
		clearing_info(info, 0);
	}
	create_file_history(info);
	clearing_info(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (builtin_result == -2)
	{
		if (info->number_error == -1)
			exit(info->status);
		exit(info->number_error);
	}
	return (builtin_result);
}

/**
 * _builtin_cmd_search - finds a builtin command
 * @info: the parameter & return info struct
 *
 * Description:
 *	This function searches for a built-in command in the provided command
 *	arguments and executes the corresponding function if found.
 *
 * Return: -1 if builtin not found,
 *		0 if builtin executed successfully,
 *		1 if builtin found but not successful,
 *		-2 if builtin signals exit()
 */
int _builtin_cmd_search(info_t *info)
{
	int loop_index, built_in_result = -1;
	builtin_table builtintbl[] = {
		{"exit", my_exit},
		{"env", _env},
		{"help", _help},
		{"history", display_history_list},
		{"setenv", set_myenv},
		{"unsetenv", unset_myenv},
		{"cd", _cd},
		{"alias", _alias},
		{NULL, NULL}
	};

	for (loop_index = 0; builtintbl[loop_index].type; loop_index++)
		if (my_strcmp(info->argv[0], builtintbl[loop_index].type) == 0)
		{
			info->line_count++;
			built_in_result = builtintbl[loop_index].func(info);
			break;
		}
	return (built_in_result);
}

/**
 * _cmd_search - finds a command in PATH
 * @info: the parameter & return info struct
 *
 * Description:
 *	This function searches for an external command in the PATH environment
 *	variable and executes it in a child process if found.
 *
 * Return: void
 */
void _cmd_search(info_t *info)
{
	char *path = NULL;
	int loop_index, arg_count;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (loop_index = 0, arg_count = 0; info->arg[loop_index]; loop_index++)
		if (!my_delimiter(info->arg[loop_index], " \t\n"))
			arg_count++;
	if (!arg_count)
		return;

	path = finding_string_path(info, my_getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		_cmd_split(info);
	}
	else
	{
		if ((interactive(info) || my_getenv(info, "PATH=")
			 || info->argv[0][0] == '/')
				&& file_exe_cmd(info, info->argv[0]))
			_cmd_split(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			printerr(info, "command not found\n");
		}
	}
}

/**
 * _cmd_split - forks an exec thread to run cmd
 * @info: the parameter & return info struct
 *
 * Description:
 *	This function forks a child process
 *	and executes the command specified
 *	by the provided information struct.
 *
 * Return: void
 */
void _cmd_split(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, getenv_copy(info)) == -1)
		{
			clearing_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				printerr(info, "permission denied\n");
		}
	}
}
