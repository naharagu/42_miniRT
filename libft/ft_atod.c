/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 06:19:05 by naharagu          #+#    #+#             */
/*   Updated: 2023/04/25 22:03:47 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "errno.h"
#include "float.h"

void	atod_helper(const char *str, double *res)
{
	double	i;

	while (ft_isdigit(*str))
	{
		if (*res > ((DBL_MAX - (double)(*str - '0')) / 10))
		{
			errno = ERANGE;
			*res = DBL_MAX;
			return ;
		}
		*res = *res * 10 + (double)(*str++ - '0');
	}
	i = 0.1;
	if (*str == '.')
	{
		str++;
		while (ft_isdigit(*str))
		{
			*res += (double)(*str++ - '0') *i;
			i *= 0.1;
			str++;
		}
	}
	return ;
}

double	ft_atod(const char *str)
{
	double		res;
	double		sign;

	sign = 1.0;
	res = 0.0;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			sign = -1.0;
	atod_helper(str, &res);
	return (sign * res);
}

// #include <stdio.h>

// int main()
// {
// 	double a = ft_atod("123.456");
// 	printf("%f\n", a);
// 	double b = ft_atod("-123.456");
// 	printf("%f\n", b);
// }
