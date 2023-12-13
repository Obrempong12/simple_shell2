#include "shell.h"

/**
 * chain_delimiter - a func that tests if char in buffer is a chain delimeter.
 * @para: parameter.
 * @buf: the buffer of char.
 * @b: address of current position in buf
 * Return: 1 if chain delimeter, 0 otherwise
 */

int chain_delimiter(info_t *para, char *buf, size_t *b)
{
	size_t k = *b;

	if (buf[k] == '|' && buf[k + 1] == '|')
	{
		buf[k] = 0;
		k++;
		para->cmd_buf_type = CMD_OR;
	}
	else if (buf[k] == '&' && buf[k + 1] == '&')
	{
		buf[k] = 0;
		k++;
		para->cmd_buf_type = CMD_AND;
	}
	else if (buf[k] == ';')
	{
		buf[k] = 0;
		para->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*b = k;
	return (1);
}

/**
 * chain_status - function that checks the status of the chain
 * @para: the parameter
 * @buf: the buffer
 * @b: address of buffer
 * @k: position in buffer
 * @length: length of buffer
 * Return: Void
 */
void chain_status(info_t *para, char *buf, size_t *b, size_t k, size_t length)
{
	size_t q = *b;

	if (para->cmd_buf_type == CMD_AND)
	{
		if (para->status)
		{
			buf[k] = 0;
			q = length;
		}
	}
	if (para->cmd_buf_type == CMD_OR)
	{
		if (!para->status)
		{
			buf[k] = 0;
			q = length;
		}
	}

	*b = q;
}

/**
 * substitute_alias - substitutes an aliases in the string
 * @para: the parameter of structure
 * Return: 1 if substituted, 0 if otherwise
 */
int substitute_alias(info_t *para)
{
	int m;
	list_t *node;
	char *b;

	for (m = 0; m < 10; m++)
	{
		node = node_starts_with(para->alias, para->argv[0], '=');
		if (!node)
			return (0);
		free(para->argv[0]);
		b = _strchr(node->str, '=');
		if (!b)
			return (0);
		b = _strdup(b + 1);
		if (!b)
			return (0);
		info->argv[0] = b;
	}
	return (1);
}

/**
 * substitute_vars - substitutes vars in the string.
 * @para: the parameter structure.
 * Return: if substituted 1, if otherwise 0.
 */
int substitute_vars(info_t *para)
{
	int m = 0;
	list_t *node;

	for (m = 0; info->argv[m]; m++)
	{
		if (info->argv[m][0] != '$' || !info->argv[m][1])
		continue;

		if (!_strcmp(para->argv[m], "$?"))
		{
			substitute_string(&(para->argv[m]),
			_strdup(convert_number(para->status, 10, 0)));
			continue;
		}
		if (!_strcmp(para->argv[m], "$$"))
		{
			substitute_string(&(para->argv[m]),
			_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(para->env, &para->argv[m][1], '=');
		if (node)
		{
			substitute_string(&(para->argv[m]),
			_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		substitute_string(&para->argv[m], _strdup(""));

	}
	return (0);
}

/**
 * substitute_string - substitutes string
 * @old: address of pointer of old string
 * @new: pointer to new string
 * Return: 1 if substituted, 0 otherwise
 */
int substitute_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
