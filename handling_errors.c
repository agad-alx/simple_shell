#include "mycustom.h"

/**
 * _myputs - Prints an input string to the standard error (stderr).
 * @str: The string to be printed.
 *
 * Description:
 * This function prints the input string to the standard error (stderr).
 * If the input string is NULL, the function returns without printing anything.
 *
 * Return: Nothing.
 */
void _myputs(char *str)
{
	int index = 0;

	if (!str)
		return;
	while (str[index] != '\0')
	{
		_myputchar(str[index]);
		index++;
	}
}

/**
 * _myputchar - Writes the character to stderr.
 * @ch: The character to print.
 *
 * Description:
 * This function writes the character to the standard error (stderr).
 * If the buffer is full (WRITE_BUF_SIZE) or the character is BUF_FLUSH,
 * it flushes the buffer to stderr using the write system call.
 *
 * Return: On success, 1 is returned. On error, -1 is returned,
 * and errno is set appropriately.
 */
int _myputchar(char ch)
{
	static int counter;
	static char buffer[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || counter >= WRITE_BUF_SIZE)
	{
		write(2, buffer, counter);
		counter = 0;
	}
	if (ch != BUF_FLUSH)
		buffer[counter++] = ch;
	return (1);
}

/**
 * my_putfd - Writes the character to the given file descriptor.
 * @ch: The character to print.
 * @fd: The file descriptor to write to.
 *
 * Description:
 * This function writes the character to the specified file descriptor.
 * If the buffer is full (WRITE_BUF_SIZE) or the character is BUF_FLUSH,
 * it flushes the buffer to the specified file descriptor
 * using the write system call.
 *
 * Return: On success, 1 is returned. On error, -1 is returned,
 * and errno is set appropriately.
 */
int my_putfd(char ch, int fd)
{
	static int counter;
	static char buffer[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || counter >= WRITE_BUF_SIZE)
	{
		write(fd, buffer, counter);
		counter = 0;
	}
	if (ch != BUF_FLUSH)
		buffer[counter++] = ch;
	return (1);
}

/**
 * my_putsfd - Prints an input string to the given file descriptor.
 * @str: The string to be printed.
 * @fd: The file descriptor to write to.
 *
 * Description:
 * This function prints the input string to the specified file descriptor.
 * If the input string is NULL, it returns 0 without printing anything.
 * Otherwise, it iterates through the string
 * and calls my_putfd for each character.
 *
 * Return: The number of characters written.
 */
int my_putsfd(char *str, int fd)
{
	int index = 0;

	if (!str)
		return (0);
	while (*str)
	{
		index += my_putfd(*str++, fd);
	}
	return (index);
}
