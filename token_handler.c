#include "mycustom.h"

/**
 * split_into_words - Splits a string into words,
 * ignoring repeat delimiters.
 *
 * @a: The input string to be split.
 * @b: The delimiter string used for splitting.
 *
 * Return: A pointer to an array of strings containing the split words,
 *         or NULL if memory allocation fails or no words are found.
 */
char **split_into_words(char *a, char *b)
{
	int x, y, z, w, count = 0;
	char **result;

	if (a == NULL || a[0] == 0)
		return (NULL);
	if (!b)
		b = " ";
	for (x = 0; a[x] != '\0'; x++)
		if (!my_delimiter(a[x], b) &&
				(my_delimiter(a[x + 1], b) || !a[x + 1]))
			count++;
	if (count == 0)
		return (NULL);
	result = malloc((1 + count) * sizeof(char *));
	if (!result)
		return (NULL);
	for (x = 0, y = 0; y < count; y++)
	{
		while (my_delimiter(a[x], b))
			x++;
		z = 0;
		while (!my_delimiter(a[x + z], b) && a[x + z])
			z++;
		result[y] = malloc((z + 1) * sizeof(char));
		if (!result[y])
		{
			for (z = 0; z < y; z++)
				free(result[z]);
			free(result);
			return (NULL);
		}

		for (w = 0; w < z; w++)
			result[y][w] = a[x++];
		result[y][w] = 0;
	}

	result[y] = NULL;
	return (result);
}

/**
 * split_into_words2 - Splits a string into words
 * using a single-character delimiter.
 *
 * @a: The input string to be split.
 * @b: The single-character delimiter used for splitting.
 *
 * Return: A pointer to an array of strings containing the split words,
 *         or NULL if memory allocation fails or no words are found.
 */
char **split_into_words2(char *a, char b)
{
	int x, y, z, w, count = 0;
	char **result;

	if (a == NULL || a[0] == 0)
		return (NULL);

	for (x = 0; a[x] != '\0'; x++)
		if ((a[x] != b && a[x + 1] == b) ||
			(a[x] != b && !a[x + 1]) || a[x + 1] == b)
			count++;
	if (count == 0)
		return (NULL);

	result = malloc((1 + count) * sizeof(char *));
	if (!result)
		return (NULL);

	for (x = 0, y = 0; y < count; y++)
	{
		while (a[x] == b && a[x] != b)
			x++;
		z = 0;
		while (a[x + z] != b && a[x + z] && a[x + z] != b)
			z++;
		result[y] = malloc((z + 1) * sizeof(char));
		if (!result[y])
		{
			for (z = 0; z < y; z++)
				free(result[z]);
			free(result);
			return (NULL);
		}

		for (w = 0; w < z; w++)
			result[y][w] = a[x++];
		result[y][w] = 0;
	}

	result[y] = NULL;
	return (result);
}
