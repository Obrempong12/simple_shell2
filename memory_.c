#include "shell.h"

/**
 * pfree - function that frees a pointer and NULLs the address
 * @p: address of the freed pointers
 * Return: 1 if freed, otherwise 0.
 */
int pfree(void **p)
{
	if (p && *p)
	{
		free(*p);
		*p = NULL;
		return (1);
	}
	return (0);
}
