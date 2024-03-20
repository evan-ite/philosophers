/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 12:24:59 by evan-ite          #+#    #+#             */
/*   Updated: 2024/03/20 11:36:36 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <limits.h>
#include <stdint.h>

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
