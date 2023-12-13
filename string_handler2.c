#include "mycustom.h"

/**
 * my_strcpy - Copy a string.
 * @dest: The destination buffer to copy into.
 * @src: The source string to copy from.
 *
 * Description:
 *	This function copies the contents of the source string (src) to the
 *	destination buffer (dest) including the null terminator. It returns a
 *	pointer to the destination buffer.
 *
 * Return: Pointer to the destination buffer (dest).
 */
char *my_strcpy(char *dest, char *src)
{
	int index = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[index])
	{
		dest[index] = src[index];
		index++;
	}
	dest[index] = 0;
	return (dest);
}

/**
 * my_strdup - Duplicate a string.
 * @str: The string to duplicate.
 *
 * Description:
 *	This function duplicates the input string (str) by dynamically allocating
 *	memory for a new string, copying the characters from the input string,
 *	and returning a pointer to the duplicated string. It returns NULL if
 *	memory allocation fails.
 *
 * Return: Pointer to the duplicated string or NULL if memory allocation fails.
 */
char *my_strdup(const char *str)
{
	int length = 0;
	char *result;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	result = malloc(sizeof(char) * (length + 1));
	if (!result)
		return (NULL);
	for (length++; length--;)
		result[length] = *--str;
	return (result);
}

/**
 * my_puts - Print a string to standard output.
 * @str: The string to be printed.
 *
 * Description:
 *	This function prints the input string (str) to the standard output
 *	using the my_putchar function. It does nothing if the input string is NULL.
 *
 * Return: Nothing.
 */
void my_puts(char *str)
{
	int index = 0;

	if (!str)
		return;
	while (str[index] != '\0')
	{
		my_putchar(str[index]);
		index++;
	}
}

/**
 * my_putchar - Write a character to standard output.
 * @c: The character to print.
 *
 * Description:
 *	This function writes the specified character (c)
 *	to the standard output.
 *	It uses a static buffer to accumulate characters
 *	and flushes the buffer
 *	to the standard output when it's full or
 *	when a special flushing character
 *	(BUF_FLUSH) is encountered. The function
 *	returns 1 on success and -1 on
 *	error with appropriate errno set.
 *
 * Return: On success, returns 1. On error,
 * returns -1 with errno set appropriately.
 */
int my_putchar(char c)
{
	static int index;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || index >= WRITE_BUF_SIZE)
	{
		write(1, buf, index);
		index = 0;
	}
	if (c != BUF_FLUSH)
		buf[index++] = c;
	return (1);
}
