/*------- directory_handler.c -------*/

#include "mycustom.h"

/**
 * my_exit - exits the shell
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *
 * This function exits the shell with a given exit status. If an exit
 * argument is provided, it sets the exit status accordingly. If the
 * argument is not a valid number, it prints an error message.
 *
 * Return: exits with a given exit status (0) if info->argv[0] != "exit"
 */
int my_exit(info_t *info)
{
	int check_exit;

	if (info->argv[1])  /* If there is an exit argument */
	{
		check_exit = atoi_errs(info->argv[1]);
		if (check_exit == -1)
		{
			info->status = 2;
			printerr(info, "Invalid exit code: ");
			my_puts(info->argv[1]);
			my_putchar('\n');
			return (1);
		}
		info->number_error = atoi_errs(info->argv[1]);
		return (-2);
	}
	info->number_error = -1;
	return (-2);
}

/**
 * _cd - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *
 * This function changes the current directory of the process. If no
 * argument is provided, it changes to the home directory. If the argument
 * is "-", it changes to the previous directory. If a valid directory path
 * is provided, it changes to that directory. It updates the environment
 * variables PWD and OLDPWD accordingly.
 *
 * Return: Always 0
 */
int _cd(info_t *info)
{
	char *current_dir, *dir, buffer[1024];
	int chdir_out;

	current_dir = getcwd(buffer, 1024);
	if (!current_dir)
		my_puts("TODO: >>getcwd failure emsg here<<\n");

	if (!info->argv[1])
	{
		dir = my_getenv(info, "HOME=");
		if (!dir)
			chdir_out = chdir((dir = my_getenv(info, "PWD=")) ? dir : "/");
		else
			chdir_out = chdir(dir);
	}
	else if (my_strcmp(info->argv[1], "-") == 0)
	{
		if (!my_getenv(info, "OLDPWD="))
		{
			my_puts(current_dir);
			my_putchar('\n');
			return (1);
		}
		my_puts(my_getenv(info, "OLDPWD=")), my_putchar('\n');
		chdir_out = chdir((dir = my_getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_out = chdir(info->argv[1]);
	if (chdir_out == -1)
	{
		printerr(info, "Failed to change directory to ");
		_myputs(info->argv[1]), _myputchar('\n');
	}
	else
	{
		chdir_out = chdir_out;
		my_setenv(info, "OLDPWD", my_getenv(info, "PWD="));
		my_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _help - displays information about built-in shell commands
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *
 * This function displays information about built-in shell commands.
 * Currently, it only prints a message indicating that the function is
 * not yet implemented.
 *
 * Return: Always 0
 */
int _help(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	my_puts("Help command works. Functionality not yet implemented.\n");
	if (0)
		my_puts(*arg_array);
	return (0);
}
