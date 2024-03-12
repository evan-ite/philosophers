/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:33:56 by evan-ite          #+#    #+#             */
/*   Updated: 2024/03/12 15:50:50 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <limits.h>
#include <stdint.h>

void	ft_putendl_fd(char *s, int fd)
{
	while (*s != '\0')
	{
		write(fd, s, 1);
		s++;
	}
	write(fd, "\n", 1);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s || !(*s))
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s)
{
	int		size;
	int		i;
	char	*dup;

	size = ft_strlen(s);
	dup = (char *)malloc(size * sizeof(char) + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

void	*ft_calloc(size_t nmemb, size_t bytesize)
{
	void			*array;
	size_t			i;
	unsigned char	*ptr;

	if (nmemb == 0 || bytesize == 0)
		return (ft_strdup(NULL));
	if (nmemb > SIZE_MAX / bytesize || nmemb > INT_MAX / bytesize)
		return (NULL);
	array = malloc(nmemb * bytesize);
	if (!array)
		return (NULL);
	ptr = array;
	i = 0;
	while (i < (nmemb * bytesize))
	{
		ptr[i] = 0;
		i++;
	}
	return (array);
}

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\f' || c == '\n')
		return (1);
	else if (c == '\r' || c == '\t' || c == '\v')
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *s)
{
	int	sign;
	int	value;

	sign = 1;
	value = 0;
	while (ft_isspace(*s))
		s++;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			sign *= -1;
		s++;
	}
	while (*s != '\0')
	{
		if (*s >= '0' && *s <= '9')
			value = value * 10 + (*s - '0');
		else
			return (sign * value);
		s++;
	}
	return (sign * value);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*newstr;
	int		i;
	int		j;

	if (!s1)
		s1 = "";
	if (!s2)
		s2 = "";
	newstr = (char *)malloc(\
		(ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!newstr)
		return (NULL);
	i = -1;
	while (s1[++i])
		newstr[i] = s1[i];
	j = -1;
	while (s2[++j])
		newstr[i++] = s2[j];
	newstr[i] = '\0';
	return (newstr);
}
