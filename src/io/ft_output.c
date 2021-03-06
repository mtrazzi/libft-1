/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_output.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2019/02/07 02:47:29 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_io.h"



inline int	ft_output_char(char c)
{
	return (ft_write_str(STDOUT, &c));
}



inline int	ft_output_str(char const *str)
{
	return (ft_write_str(STDOUT, str));
}



inline int	ft_output_line(char const *str)
{
	return (ft_write_line(STDOUT, str));
}



inline int	ft_output_strls(char const **strls)
{
	return (ft_write_strls(STDOUT, strls));
}



inline int	ft_output_memory(t_u8 const *ptr, t_size n, t_u8 cols)
{
	return (ft_write_memory(STDOUT, ptr, n, cols));
}
