#include "fractol.h"

double	ft_atod(char *str)
{
	int		i;
	int		integer;
	double	decimal;
	int		sign;
	int		count;

	count = 0;
	integer = 0;
	decimal = 0;
	i = 0;
	sign = 1;
	while ((str[i] == ' ') || (str[i] == '\t') || (str[i] == '\n')
		|| (str[i] == '\v') || (str[i] == '\f') || (str[i] == '\r'))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	if (!((str[i] >= '0' && str[i] <= '9') || str[i] == '.'))
		return (0);
	while (str[i] >= '0' && str[i] <= '9')
	{
		integer = integer * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] == '.')
	{
		i++;
		while (str[i] >= '0' && str[i] <= '9')
		{
			decimal = decimal * 10 + (str[i] - '0');
			count++;
			i++;
		}
		decimal = decimal / pow(10, count);
	}
	else
		return (integer * sign);
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
