#include "shell.h"

/**
 * add_start_node - function that adds a node to the start of list
 * @ph: address of pointer to head node
 * @str: string field of node
 * @index: node index
 * Return: size of list
 */
list_t *add_start_node(list_t **ph, const char *str, int index)
{
	list_t *new_h;

	if (!ph)
		return (NULL);
	new_h = malloc(sizeof(list_t));
	if (!new_h)
		return (NULL);
	_memset((void *)new_h, 0, sizeof(list_t));
	new_h->index = index;
	if (str)
	{
		new_h->str = _strdup(str);
		if (!new_h->str)
		{
			free(new_h);
			return (NULL);
		}
	}
	new_h->next = *ph;
	*ph = new_h;
	return (new_h);
}

/**
 * add_end_node - function that adds a node to the end of list
 * @ph: address of pointer to head node
 * @str: str field of node
 * @index: node index
 * Return: size of list
 */
list_t *add_end_node(list_t **ph, const char *str, int index)
{
	list_t *new_node, *node;

	if (!ph)
		return (NULL);

	node = *ph;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->index = index;
	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*ph = new_node;
	return (new_node);
}

/**
 * print_str_list - prints only the str element of a list_a linked list
 * @b: pointer to first node
 * Return: size of list
 */
size_t print_str_list(const list_t *b)
{
	size_t m = 0;

	while (b)
	{
		_put(b->str ? b->str : "(nil)");
		_put("\n");
		b = b->next;
		m++;
	}
	return (m);
}

/**
 * delete_node_index - deletes node at given index
 * @ph: address of pointer to first node
 * @index: index of node to be deleted
 * Return: 1 on success, otherwise 0
 */
int delete_node_index(list_t **ph, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int m = 0;

	if (!ph || !*ph)
		return (0);

	if (!index)
	{
		node = *ph;
		*ph = (*ph)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *ph;
	while (node)
	{
		if (m == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		m++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_node_list - frees all nodes of a list
 * @ph: address of pointer to head node
 * Return: void
 */
void free_node_list(list_t **ph)
{
	list_t *node, *next_node, *head;

	if (!ph || !*ph)
		return;
	head = *ph;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*ph = NULL;
}
