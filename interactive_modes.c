/*------- interactive_modes.c -------*/

#include "mycustom.h"

/**
 * interactive - checks if the shell is in interactive mode
 * @info: pointer to the struct containing shell information
 *
 * This function determines whether the shell is running in interactive mode
 * by checking if the standard input is associated with a terminal and if the
 * file descriptor of the read end of the shell is less than or equal to 2.
 *
 * Return: 1 if in interactive mode, 0 otherwise
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * my_delimiter - checks if a character is a delimiter
 * @character: the character to check
 * @delimiter: the delimiter string
 *
 * This function determines whether a given character is a delimiter by
 * comparing it to a provided delimiter string. It iterates through the
 * delimiter string and returns 1 if the character is found, 0 otherwise.
 *
 * Return: 1 if the character is a delimiter, 0 if not
 */
int my_delimiter(char character, char *delimiter)
{
	while (*delimiter)
		if (*delimiter++ == character)
			return (1);
	return (0);
}

/**
 * _alphabet - checks if a character is alphabetic
 * @character: the character to check
 *
 * This function determines whether a given character
 * is an alphabetic character.
 * It checks if the character is within the ranges of lowercase or uppercase
 * letters in the ASCII character set.
 *
 * Return: 1 if the character is alphabetic, 0 if not
 */
int _alphabet(int character)
{
	if ((character >= 'a' && character <= 'z')
			|| (character >= 'A' && character <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * string_converter - converts a string to an integer
 * @s: the string to be converted
 *
 * This function converts a string representation of an integer to an actual
 * integer value. It iterates through the string, considering signs and digits,
 * and returns the converted integer. If the string does not contain any
 * numbers, it returns 0.
 *
 * Return: 0 if no numbers in the string, converted number otherwise
 */
int string_converter(char *s)
{
	int i, sign = 1, flag = 0, converted_value;
	unsigned int result = 0;

	for (i = 0; s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		converted_value = -result;
	else
		converted_value = result;

	return (converted_value);
}
