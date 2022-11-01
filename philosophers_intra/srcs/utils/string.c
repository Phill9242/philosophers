/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phiolive <phiolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 15:45:38 by phiolive          #+#    #+#             */
/*   Updated: 2022/10/15 15:45:39 by phiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_isspace(int c)
{
	return (c == ' ' || (c >= '\t' && c <= '\r'));
}

void	*ft_memcpy(void *dst, const void *src, size_t len)
{
	unsigned char	*pointer;
	unsigned char	*dst_pointer;

	if (!dst && !src)
		return (dst);
	pointer = (unsigned char *) src ;
	dst_pointer = (unsigned char *) dst;
	while (len--)
		*dst_pointer++ = *pointer++;
	return (dst);
}

long long int	ft_atol(const char *nptr)
{
	long long int	res;
	int				sign;
	int				i;

	res = 0;
	sign = 1;
	i = 0;
	while (ft_isspace(*nptr))
		++nptr;
	if (nptr[i] == '-' && ++i)
		sign = -1;
	else if (nptr[i] == '+')
		++i;
	while (ft_isdigit(nptr[i]))
		res = (res * 10) + (nptr[i++] - '0');
	return (res * sign);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	nof_bytes;
	void	*ptr;

	nof_bytes = nmemb * size;
	ptr = malloc(nof_bytes);
	if (!ptr || nof_bytes > 2147483647)
		return (NULL);
	memset(ptr, 0, nmemb);
	return (ptr);
}
