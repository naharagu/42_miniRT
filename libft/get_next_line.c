/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 21:18:48 by naharagu          #+#    #+#             */
/*   Updated: 2023/04/19 21:32:08 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*safe_free(char *buff, char *input)
{
	if (buff)
	{
		free(buff);
		buff = NULL;
	}
	if (input)
	{
		free(input);
		input = NULL;
	}
	return (NULL);
}

char	*read_input(int fd, char *input)
{
	char	*buf;
	char	*tmp;
	ssize_t	count;

	if (input == NULL)
		input = ft_strdup("");
	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (input == NULL || buf == NULL)
		return (safe_free(buf, input));
	count = 1;
	while (count && ft_strchr(input, '\n') == 0)
	{
		count = read(fd, buf, BUFFER_SIZE);
		if (count == -1 || (count == 0 && input[0] == '\0'))
			return (safe_free(buf, input));
		buf[count] = '\0';
		tmp = input;
		input = ft_strjoin(tmp, buf);
		safe_free(NULL, tmp);
	}
	safe_free(buf, NULL);
	return (input);
}

char	*get_one_line(char *input)
{
	char	*output;
	size_t	i;

	output = malloc((ft_strlen(input) + 1) * sizeof(char));
	if (output == NULL)
		return (NULL);
	i = 0;
	while (input[i])
	{
		output[i] = input[i];
		if (output[i++] == '\n')
			break ;
	}
	output[i] = '\0';
	return (output);
}

char	*get_after_new_line(char *input)
{
	char	*new_input;
	size_t	i;

	i = 0;
	while (input[i] && input[i] != '\n')
		i++;
	if (input[i] == '\0')
		return (safe_free(NULL, input));
	new_input = ft_strdup(&input[++i]);
	safe_free(NULL, input);
	return (new_input);
}

char	*get_next_line(int fd)
{
	static char	*input;
	char		*output;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	input = read_input(fd, input);
	if (input == NULL)
		return (NULL);
	output = get_one_line(input);
	if (output == NULL)
		return (safe_free(NULL, input));
	input = get_after_new_line(input);
	return (output);
}
