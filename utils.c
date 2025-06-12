#include "fractol.h"

int	skip_whitespace_and_sign(char *str, int *sign)
{
	int	i;

	i = 0;
	while ((str[i] == ' ') || (str[i] == '\t') || (str[i] == '\n')
		|| (str[i] == '\v') || (str[i] == '\f') || (str[i] == '\r'))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			*sign = -1;
		i++;
	}
	return (i);
}

int	parse_integer_part(char *str, int *i)
{
	int	integer;

	integer = 0;
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		integer = integer * 10 + (str[*i] - '0');
		(*i)++;
	}
	return (integer);
}

double	parse_decimal_part(char *str, int *i)
{
	double	decimal;
	int		count;

	decimal = 0;
	count = 0;
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		decimal = decimal * 10 + (str[*i] - '0');
		count++;
		(*i)++;
	}
	return (decimal / pow(10, count));
}

double	ft_atod(char *str)
{
	int		i;
	int		sign;
	int		integer;
	double	decimal;

	sign = 1;
	i = skip_whitespace_and_sign(str, &sign);
	if (!((str[i] >= '0' && str[i] <= '9') || str[i] == '.'))
		return (0);
	integer = parse_integer_part(str, &i);
	decimal = 0;
	if (str[i] == '.')
	{
		i++;
		decimal = parse_decimal_part(str, &i);
	}
	return ((integer + decimal) * sign);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	index;

	index = 0;
	while (s1[index] != '\0' || s2[index] != '\0')
	{
		if (s1[index] != s2[index])
			return (s1[index] - s2[index]);
		else if (s1[index] == s2[index])
			index++;
	}
	return (0);
}
