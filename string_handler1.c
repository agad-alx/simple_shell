#include "mycustom.h"

/**
 * my_strlen - Returns the length of a string.
 * @str: The string whose length to check.
 *
 * Description:
 *	This function calculates and returns the length
 *	of the provided string.
 *
 * Return: Integer length of the string.
 */
int my_strlen(char *str)
{
	int length = 0;

	if (!str)
		return (0);

	while (*str++)
		length++;
	return (length);
}

/**
 * my_strcmp - Performs lexicographic comparison of two strings.
 * @str1: The first string.
 * @str2: The second string.
 *
 * Description:
 *	This function compares two strings lexicographically
 *	and returns a negative value if str1 < str2,
 *	positive if str1 > str2, and zero if str1 == str2.
 *
 * Return: Negative if str1 < str2, positive if str1 > str2,
 * zero if str1 == str2.
 */
int my_strcmp(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	if (*str1 == *str2)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
}

/**
 * begin_here - Checks if needle starts with haystack.
 * @haystack: The string to search.
 * @needle: The substring to find.
 *
 * Description:
 *	This function checks if the provided substring (needle)
 *	starts with the specified string (haystack) and returns
 *	the address of the next character
 *	of haystack or NULL if needle is not found.
 *
 * Return: Address of the next character of haystack or NULL.
 */
char *begin_here(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * my_strcat - Concatenates two strings.
 * @dest: The destination buffer.
 * @src: The source buffer.
 *
 * Description:
 *	This function concatenates the source string (src)
 *	to the end of the destination string (dest)
 *	and returns a pointer
 *	to the destination buffer.
 *
 * Return: Pointer to the destination buffer.
 */
char *my_strcat(char *dest, char *src)
{
	char *result = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (result);
}
