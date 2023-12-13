#include "mycustom.h"

/**
 * atoi_errs - Converts a string to an integer with error handling.
 * @s: The string to be converted.
 *
 * Description: This function converts a string to an integer
 * with error handling.
 * If there are no numbers in the string, it returns 0.
 * If an error occurs during conversion, it returns -1.
 *
 * Return: The converted number or -1 on error.
 */
int atoi_errs(char *s)
{
	int index;
	unsigned long int result = 0;

	if (*s == '+')
		s++;
	for (index = 0; s[index] != '\0'; index++)
	{
		if (s[index] >= '0' && s[index] <= '9')
		{
			result *= 10;
			result += (s[index] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * printerr - Prints an error message.
 * @info: The parameter & return info struct.
 * @estr: String containing the specified error type.
 *
 * Description: This function prints an error message
 * with detailed information,
 * including filename, line number, program name,
 * and the specified error string.
 *
 * Return: Nothing.
 */
void printerr(info_t *info, char *estr)
{
	_myputs(info->fname);
	_myputs(": ");
	output_decimal(info->line_count, STDERR_FILENO);
	_myputs(": ");
	_myputs(info->argv[0]);
	_myputs(": ");
	_myputs(estr);
}

/**
 * output_decimal - Prints a decimal (integer) number (base 10).
 * @input: The input.
 * @fd: The file descriptor to write to.
 *
 * Description: This function prints a decimal (integer) number
 * to the specified file descriptor.
 * It supports error handling for stderr and
 * uses the specified file descriptor for stdout.
 *
 * Return: The number of characters printed.
 */
int output_decimal(int input, int fd)
{
	int (*sh_putchar)(char) = my_putchar;
	int i, count = 0;
	unsigned int value, current;

	if (fd == STDERR_FILENO)
		sh_putchar = _myputchar;
	if (input < 0)
	{
		value = -input;
		sh_putchar('-');
		count++;
	}
	else
		value = input;
	current = value;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (value / i)
		{
			sh_putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	sh_putchar('0' + current);
	count++;

	return (count);
}

/**
 * digit_converter - Converts a number to a string.
 * @num: Number.
 * @base: Base.
 * @flags: Argument flags.
 *
 * Description: This function converts a number to a string
 * with specified base and flags.
 * It supports the conversion of unsigned numbers and handles negative numbers.
 *
 * Return: The converted string.
 */
char *digit_converter(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long value = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		value = -num;
		sign = '-';
	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[value % base];
		value /= base;
	} while (value != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * delete_remarks - Replaces the first instance of '#' with '\0'.
 * @buf: Address of the string to modify.
 *
 * Description: This function replaces the first instance of '#' with '\0'
 * in the provided string, effectively removing comments.
 *
 * Return: Always 0.
 */
void delete_remarks(char *buf)
{
	int index;

	for (index = 0; buf[index] != '\0'; index++)
		if (buf[index] == '#' && (!index || buf[index - 1] == ' '))
		{
			buf[index] = '\0';
			break;
		}
}
