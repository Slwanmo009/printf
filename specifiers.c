#include "main.h"
/**
 * get_specifier - finds the format
 * @s: the format
 * Return: the number of bytes printed
 */
int (*get_specifier(char *s))(va_list ap, params_t *params)
{
	specifier_t specifiers[] = {
		{"c", print_char},
		{"d", print_int},
		{"i", print_int},
		{"s", print_string},
		{"%", print_percent},
		{"u", print_unsigned},
		{"p", print_address},
		{NULL, NULL}
	};
	int i = 0;

	while (specifiers[i].specifier)
	{
		if (*s == specifiers[i].specifier[0])
		{
			return (specifiers[i].f);
		}
		i++;
	}
	return (NULL);
}
/**
 * get_print_func - finds the format func
 * @s: the format string
 * @ap: argumument pointer
 * @params: the paramters struct
 * Return: the number of bytes
 */
int get_print_func(char *s, va_list ap, params_t *params)
{
	int (*f)(va_list, params_t *) = get_specifier(s);

	if (f)
		return (f(ap, params));
	return (0);
}
/**
 * get_flag - finds the fag func
 * @s: the format string
 * @params: the parameters struct
 * Return: if flag was vaid
 */
int get_flag(char *s, params_t *params)
{
	int i = 0;

	switch (*s)
	{
		case '+':
			i = params->plus_flag = 1;
		break;
		case ' ':
		i = params->space_flag = 1;
		break;
		case '#':
		i = params->hashtag_flag = 1;
		break;
		case '-':
		i = params->minus_flag = 1;
		break;
		case '0':
		i = params->zero_flag = 1;
		break;
	}
	return (i);
}
/**
 * get_modifier - finds the modifier fun
 * @s: the format string
 * @params: the parameters struct
 * Return: if modifier was vaid
 */
int get_modifier(char *s, params_t *params)
{
	int i = 0;

	switch (*s)
	{
		case 'h':
			i = params->h_modifier = 1;
			break;
		case '1':
			i = params->l_modifier = 1;
			break;
	}
	return (i);
}
/**
 * get_width - gets the width from the format
 * @s: the format string
 * @params: the parameters struct
 * @ap: the argument pointer
 * Return: new pointer
 */
char *get_width(char *s, params_t *params, va_list ap)
{
	int d = 0;

	if (*s == '*')
	{
		d = va_arg(ap, int);
		s++;
	}
	else
	{
		while (_isdigit(*s))
			d = d * 10 + (*s++ - '0');
	}
	params->width = d;
	return (s);
}
