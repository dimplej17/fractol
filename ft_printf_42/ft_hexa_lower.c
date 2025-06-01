/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexa_lower.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanardh <djanardh@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 21:17:27 by djanardh          #+#    #+#             */
/*   Updated: 2025/05/02 12:07:31 by djanardh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	ft_hex_alpha_lower(unsigned long rem)
{
	if (rem == 10)
		return ('a');
	else if (rem == 11)
		return ('b');
	else if (rem == 12)
		return ('c');
	else if (rem == 13)
		return ('d');
	else if (rem == 14)
		return ('e');
	else
		return ('f');
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

int	ft_hexa_lower(unsigned int num)
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
			array[i++] = ft_hex_alpha_lower(rem);
		else
			array[i++] = rem + '0';
		n /= 16;
	}
	return (array_reverse(array, i));
}

// int	main(void)
// {
// 	hexa_lower(255);
// 	write(1, '\n', 1);
// 	hexa_lower(31);
// 	write(1, '\n', 1);
// 	return (0);
// }