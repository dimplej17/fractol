/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_unsigned.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanardh <djanardh@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 18:57:13 by djanardh          #+#    #+#             */
/*   Updated: 2025/03/26 17:12:59 by djanardh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	num_reverse(char array[12], int i)
{
	int	count;
	int	temp;

	count = 0;
	while (--i >= 0)
	{
		temp = write(1, &array[i], 1);
		if (temp == -1)
			return (-1);
		count++;
	}
	return (count);
}

int	ft_putnbr_unsigned(unsigned int n)
{
	char	array[12];
	int		i;

	i = 0;
	if (n == 0)
		array[i++] = '0';
	while (n > 0)
	{
		array[i++] = '0' + (n % 10);
		n /= 10;
	}
	return (num_reverse(array, i));
}
