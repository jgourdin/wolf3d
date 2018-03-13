/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strclr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourdin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 13:55:22 by jgourdin          #+#    #+#             */
/*   Updated: 2016/11/29 12:46:21 by jgourdin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strclr(char *s)
{
	int	i;

	if (!s)
		return ;
	i = ft_strlen(s);
	while (s != '\0' && i >= 0)
	{
		s[i] = '\0';
		i--;
	}
}
