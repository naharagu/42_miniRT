/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 06:19:05 by naharagu          #+#    #+#             */
/*   Updated: 2023/02/12 09:49:26 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	size_t	s_len;
	char	*res;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (!len || s_len <= start)
		return (ft_strdup(""));
	if (len >= s_len - (size_t)start)
		len = s_len - start;
	res = malloc((len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	ft_strlcpy(res, s + start, len + 1);
	return (res);
}

#include "libft.h"
#include <stdio.h>
#include <string.h>

int main()
{
    //case 1. normal
    printf("%s\n", ft_substr("hello42tokyo", 5, 7));
    printf("%s\n", ft_substr("hello42tokyo", 5, 2));

    //case 2-1. len = 0
    printf("%s\n", ft_substr("hello42tokyo", 5, 0));
    //case 2-2. start > s_len
    printf("%s\n", ft_substr("hello42tokyo", 100, 1));

    //case 3. len > s_len - start
    printf("%s\n", ft_substr("hello42tokyo", 5, 100));

    //case 4 s = NULL;
    printf("%s\n", ft_substr("", 100, 0));
}
