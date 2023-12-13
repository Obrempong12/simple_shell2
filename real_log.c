#include "shell.h"

/**
 **_memset - fills memory with a constant byte
 *@p: the pointer to the memory area
 *@f: the byte to fill *p with
 *@q: the amount of bytes to be filled
 *Return: (p) a pointer to the memory area p
 */
char *_memset(char *p, char f, unsigned int q)
{
	unsigned int m;

	for (m = 0; m < q; m++)
		p[m] = f;
	return (p);
}

/**
 * sfree - frees a string of strings
 * @ss: string of strings
 */
void sfree(char **ss)
{
	char **a = ss;

	if (!ss)
		return;
	while (*ss)
		free(*ss++);
	free(a);
}

/**
 * _realloc - reallocates a block of memory
 * @p: pointer to previous malloc block
 * @prev_size: previous block size of byte
 * @new_size: new block size of byte
 * Return: pointer to the previous block
 */
void *_realloc(void *p, unsigned int prev_size, unsigned int new_size)
{
	char *q;

	if (!p)
		return (malloc(new_size));
	if (!new_size)
		return (free(p), NULL);
	if (new_size == prev_size)
		return (p);

	q = malloc(new_size);
	if (!q)
		return (NULL);

	prev_size = prev_size < new_size ? prev_size : new_size;
	while (prev_size--)
		q[prev_size] = ((char *)p)[prev_size];
	free(p);
	return (q);
}
