#include "fractol.h"

void	put_pixel(mlx_image_t *img, int x, int y, int color)
{
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
		mlx_put_pixel(img, x, y, color);
}

int	get_color(int iter)
{
	if (iter == MAX_ITER)
		return (0x000000FF);         // black for inside
	return (0xFFFFFF - iter * 1000); // gradient
}

double	ft_atof(char *str)
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
