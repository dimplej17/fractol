/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanardh <djanardh@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 15:52:38 by djanardh          #+#    #+#             */
/*   Updated: 2025/06/01 15:04:46 by djanardh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <stdio.h>
# include <unistd.h>

int		ft_printf(const char *s, ...);
int		ft_putstr(char *s);
size_t	ft_strlen_printf(char *s);
int		ft_putnbr(int num);
int		ft_putnbr_unsigned(unsigned int n);
int		ft_hexa_upper(unsigned int num);
int		ft_hexa_lower(unsigned int num);
int		ft_pointer_hexa(unsigned long p);

#endif