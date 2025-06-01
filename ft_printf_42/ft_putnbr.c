/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanardh <djanardh@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 15:06:00 by djanardh          #+#    #+#             */
/*   Updated: 2025/03/18 19:25:02 by djanardh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	num_reverse(char array[12], int i, int sign)
{
	int	count;
	int	temp;

	count = 0;
	if (sign == 1)
	{
		temp = write(1, "-", 1);
		if (temp == -1)
			return (-1);
		count++;
	}
	while (--i >= 0)
	{
		temp = write(1, &array[i], 1);
		if (temp == -1)
			return (-1);
		count++;
	}
	return (count);
}

int	ft_putnbr(int num)
{
	char	array[12];
	long	n;
	int		i;
	int		sign;

	sign = 0;
	i = 0;
	n = num;
	if (n < 0)
	{
		n = -n;
		sign = 1;
	}
	if (n == 0)
		array[i++] = '0';
	while (n > 0)
	{
		array[i++] = '0' + (n % 10);
		n /= 10;
	}
	return (num_reverse(array, i, sign));
}

// int	main(void)
// {
// 	int n = 12345;
// 	ft_putnbr_1(n, 1);
// 	return (0);
// }
