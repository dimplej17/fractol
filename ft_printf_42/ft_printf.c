/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanardh <djanardh@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 14:40:19 by djanardh          #+#    #+#             */
/*   Updated: 2025/03/31 14:31:28 by djanardh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

int	ft_print_arguments(char c, va_list args)
{
	if (c == 'c')
		return (ft_putchar((char)va_arg(args, int)));
	else if (c == '%')
		return (write(1, "%", 1));
	else if (c == 's')
		return (ft_putstr(va_arg(args, char *)));
	else if (c == 'i' || c == 'd')
		return (ft_putnbr(va_arg(args, int)));
	else if (c == 'u')
		return (ft_putnbr_unsigned(va_arg(args, unsigned int)));
	else if (c == 'X')
		return (ft_hexa_upper(va_arg(args, unsigned int)));
	else if (c == 'x')
		return (ft_hexa_lower(va_arg(args, unsigned int)));
	else if (c == 'p')
		return (ft_pointer_hexa((unsigned long)va_arg(args, void *)));
	return (0);
}

int	ft_printf(const char *s, ...)
{
	int		i;
	va_list	args;
	int		count;
	int		temp;

	count = 0;
	i = 0;
	va_start(args, s);
	while (s[i] != '\0')
	{
		if (s[i] == '%')
		{
			i++;
			temp = ft_print_arguments(s[i], args);
		}
		else
			temp = write(1, &s[i], 1);
		if (temp == -1)
			return (-1);
		count += temp;
		i++;
	}
	va_end(args);
	return (count);
}

// int	main(void)
// {
// 	int		i;
// 	// int		a;
// 	// void	*ptr;
// 	// a = 8;
// 	// ptr = &a;
// 	i = ft_printf("%i %d", 1.45564, 6.778);
// 	printf("Numbers: %d\n", i);
// 	printf("%i %d", 1.45564, 6.778);
// 	// printf(" %d %d %d %d %d %d %d", 2147483647, -2147483648,
// 	// 	9223372036854775807, -9223372036854775808,
// 	// 	18446744073709551615, 0, -42));
// 	// int j = ft_printf(" NULL %s NULL ", NULL);
// 	// printf("Numbers: %d\n", j);
// 	// printf(" NULL %s NULL ", NULL);
// 	return (0);
// }
