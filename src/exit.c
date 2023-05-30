/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saikeda <saikeda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 14:29:23 by naharagu          #+#    #+#             */
/*   Updated: 2023/05/30 23:02:55 by saikeda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "libft.h"

void	put_error_and_exit(char *message)
{
	ft_putstr_fd("Error\n", STDERR_FILENO);
	ft_putstr_fd(message, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	put_rtfile_error_and_exit(char *message)
{
	ft_putstr_fd("Error\n", STDERR_FILENO);
	ft_putstr_fd("RT file error: ", STDERR_FILENO);
	ft_putstr_fd(message, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	exit(EXIT_FAILURE);
}

int	exit_window(const char *msg)
{
	printf("%s\n", msg);
	sleep(1);
	exit(1);
	return (1);
}
