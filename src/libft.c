/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourgea <rbourgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 07:10:53 by rbourgea          #+#    #+#             */
/*   Updated: 2023/10/17 07:13:52 by rbourgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/ft_ping.h"

void	*ft_memcpy(void *destination, const void *source, size_t size)
{
	unsigned	char			*str1;
	const	unsigned	char	*str2;

	str1 = (unsigned char *)destination;
	str2 = (unsigned char *)source;
	if (!size || destination == source)
		return (destination);
	while (size--)
		*str1++ = *str2++;
	return (destination);
}

void	*ft_memset(void *pointer, int value, size_t count)
{
	unsigned	int		i;
	unsigned	char	*c;

	i = 0;
	c = (unsigned char *)pointer;
	while (i < count)
		c[i++] = (unsigned char)value;
	pointer = (void *)c;
	return (pointer);
}
