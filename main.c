#include "mycustom.h"

/**
 * main - Entry point of the shell.
 * @ac: Argument count.
 * @av: Argument vector.
 *
 * Description:
 *     The main function initializes the shell information structure, processes
 *     command line arguments, opens a file descriptor for reading commands
 *     from a file (if specified), populates the environment variables list,
 *     reads command history, and starts the shell execution loop.
 *
 * Return: 0 on success, 1 on error.
 */
int main(int ac, char **av)
{
	info_t info[] = { INFO_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fd)
		: "r" (fd));

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_myputs(av[0]);
				_myputs(": 0: Unable to open file: ");
				_myputs(av[1]);
				_myputchar('\n');
				_myputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fd;
	}

	/* Populating environment variables list */
	fill_up_linked_env(info);

	/* Reading command history */
	history_recall(info);

	/* Starting the shell execution loop */
	hsh(info, av);

	return (EXIT_SUCCESS);
}
