/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexa_upper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanardh <djanardh@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 21:16:17 by djanardh          #+#    #+#             */
/*   Updated: 2025/03/26 19:36:26 by djanardh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	ft_hex_alpha(unsigned long rem)
{
	if (rem == 10)
		return ('A');
	else if (rem == 11)
		return ('B');
	else if (rem == 12)
		return ('C');
	else if (rem == 13)
		return ('D');
	else if (rem == 14)
		return ('E');
	else
		return ('F');
}

static int	array_reverse(char array[20], int i)
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

int	ft_hexa_upper(unsigned int num)
{
	unsigned long	rem;
	char			array[20];
	int				i;
	unsigned long	n;

	n = (unsigned long)num;
	i = 0;
	if (n == 0)
		array[i++] = '0';
	while (n > 0)
	{
		rem = n % 16;
		if (rem > 9 && rem < 16)
			array[i++] = ft_hex_alpha(rem);
		else
			array[i++] = rem + '0';
		n /= 16;
	}
	return (array_reverse(array, i));
}

// int	main(void)
// {
// 	hexa_upper(32);
// 	hexa_upper(33);
// 	return (0);
// }