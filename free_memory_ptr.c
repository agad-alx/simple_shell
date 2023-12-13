#include "mycustom.h"

/**
 * release_ptr - Frees a pointer and NULLs the address.
 * @ptr: Address of the pointer to free.
 *
 * Description:
 *	This function takes the address of a pointer, frees the memory it points to,
 *	and sets the pointer to NULL.
 *	It ensures safe memory deallocation and prevents
 *	potential use-after-free issues by nullifying the pointer after freeing.
 *
 * Return: 1 if the pointer was freed, otherwise 0.
 */
int release_ptr(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
