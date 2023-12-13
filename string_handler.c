
#include "mycustom.h"

/**
 * my_strncpy - Copies a string.
 * @dest: The destination string to be copied to.
 * @src: The source string.
 * @num_chars: The number of characters to be copied.
 *
 * Description: This function copies a specified number of characters from
 * the source string to the destination string. If the source string is shorter
 * than the specified number of characters, the remaining characters in the
 * destination string are filled with null characters.
 *
 * Return: A pointer to the destination string.
 */
char *my_strncpy(char *dest, char *src, int num_chars)
{
	int copy_index, additional_index;
	char *result = dest;

	copy_index = 0;
	while (src[copy_index] != '\0' && copy_index < num_chars - 1)
	{
		dest[copy_index] = src[copy_index];
		copy_index++;
	}
	if (copy_index < num_chars)
	{
		additional_index = copy_index;
		while (additional_index < num_chars)
		{
			dest[additional_index] = '\0';
			additional_index++;
		}
	}
	return (result);
}

/**
 * my_strncat - Concatenates two strings.
 * @dest: The first string.
 * @src: The second string.
 * @max_bytes: The maximum number of bytes to be used.
 *
 * Description: This function concatenates the specified number of bytes
 * from the source string to the end of the destination string. It ensures
 * that the resulting string is null-terminated.
 * If the source string is shorter than the specified number of bytes,
 * the entire source string is concatenated.
 *
 * Return: A pointer to the destination string.
 */
char *my_strncat(char *dest, char *src, int max_bytes)
{
	int dest_index, src_index;
	char *result = dest;

	dest_index = 0;
	src_index = 0;
	while (dest[dest_index] != '\0')
		dest_index++;
	while (src[src_index] != '\0' && src_index < max_bytes)
	{
		dest[dest_index] = src[src_index];
		dest_index++;
		src_index++;
	}
	if (src_index < max_bytes)
		dest[dest_index] = '\0';
	return (result);
}

/**
 * my_strchr - Locates a character in a string.
 * @str: The string to be parsed.
 * @target_char: The character to look for.
 *
 * Description: This function searches for the specified character in
 * the given string. If the character is found, a pointer to the location
 * in memory is returned; otherwise, NULL is returned.
 *
 * Return: A pointer to the memory area of str where the character is found,
 * or NULL.
 */
char *my_strchr(char *str, char target_char)
{
	do {
		if (*str == target_char)
			return (str);
	} while (*str++ != '\0');

	return (NULL);
}
