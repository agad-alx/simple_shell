#include "mycustom.h"

/**
 * my_mem_set - Fills memory with a constant byte.
 * @mem_ptr:    Pointer to the memory area.
 * @byte_value: The byte to fill *mem_ptr with.
 * @num_bytes:  The number of bytes to be filled.
 *
 * Description:
 *     This function fills the specified memory area
 *     starting at mem_ptr with
 *     the specified byte_value for the given num_bytes.
 *
 * Return: A pointer to the memory area mem_ptr.
 */
char	*my_mem_set(char *mem_ptr, char byte_value, unsigned int num_bytes)
{
	unsigned int i;

	for (i = 0; i < num_bytes; i++)
		mem_ptr[i] = byte_value;
	return (mem_ptr);
}

/**
 * release_str - Frees a string of strings.
 * @str_arr:   String of strings to be freed.
 *
 * Description:
 *     This function frees the memory occupied
 *     by the string of strings pointed
 *     to by str_arr. It also frees the array of pointers to strings.
 */
void	release_str(char **str_arr)
{
	char **a = str_arr;

	if (!str_arr)
		return;
	while (*str_arr)
		free(*str_arr++);
	free(a);
}

/**
 * mem_realloc - Reallocates a block of memory.
 * @ptr:       Pointer to the previous malloc'ated block.
 * @size_bef:  Byte size of the previous block.
 * @size_now:  Byte size of the new block.
 *
 * Description:
 *     This function reallocates a block of memory pointed to by ptr to the
 *     specified size_now. It copies the content from the old block to the new
 *     block and returns a pointer to the new block. If the reallocation fails,
 *     it returns NULL.
 *
 * Return: Pointer to the old block if successful, otherwise NULL.
 */
void	*mem_realloc(void *ptr, unsigned int size_bef, unsigned int size_now)
{
	char *new_ptr;

	if (!ptr)
		return (malloc(size_now));
	if (!size_now)
		return (free(ptr), NULL);
	if (size_now == size_bef)
		return (ptr);

	new_ptr = malloc(size_now);
	if (!new_ptr)
		return (NULL);

	size_bef = size_bef < size_now ? size_bef : size_now;
	while (size_bef--)
		new_ptr[size_bef] = ((char *)ptr)[size_bef];
	free(ptr);
	return (new_ptr);
}
