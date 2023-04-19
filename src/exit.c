/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 14:29:23 by naharagu          #+#    #+#             */
/*   Updated: 2023/04/19 14:30:28 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "libft.h"

void	put_error_and_exit(char *str)
{
	ft_putstr_fd(str, STDERR_FILENO);
	exit(EXIT_FAILURE);
}
