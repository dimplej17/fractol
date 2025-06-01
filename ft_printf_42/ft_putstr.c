/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanardh <djanardh@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 14:14:07 by djanardh          #+#    #+#             */
/*   Updated: 2025/06/01 15:05:40 by djanardh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// Parameters: s: The string to output. fd: file descriptor on which to write.
// Description: Outputs the string ’s’ to the specified file descriptor.
int	ft_putstr(char *s)
{
	size_t	s_len;

	if (s == NULL)
		return (write(1, "(null)", 6));
	s_len = ft_strlen_printf(s);
	return (write(1, s, s_len));
}

// int	main(void)
// {
// 	char *print_string = "Cows are cute";
// 	ft_putstr_fd(print_string, 1);
// 	return (0);
// }