/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stringarray/ft_strsplit_str.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_memory.h"
#include "libft_string.h"
#include "libft_stringarray.h"



static t_u32	count_distinct_sub_in_str(char const* str, char const* sub)
{
	t_u32	occ;
	t_u32	i;
	t_u32	j;

	occ = 0;
	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i + j] && sub[j] && str[i + j] == sub[j])
		{
			if (sub[j + 1] == '\0')
			{
				++occ;
				i += j;
				break ;
			}
			++j;
		}
		++i;
	}
	return (occ);
}

static char		*get_next_chunk(char const* str, char const* sub, t_u32 *i)
{
	char	*result;
	t_u32	sub_len;
	t_u32	str_len;
	t_s32	new_len;

	sub_len = ft_strlen(sub);
	str_len = ft_strlen(str);
	new_len = ft_stristr(str + *i, sub);
	if (new_len > -1)
	{
		result = ft_strsub(str, *i, (t_u32)new_len);
		*i += new_len + sub_len * (t_s32)(new_len != -1);
	}
	else
	{
		result = ft_strdup(str + *i);
		*i = str_len;
	}
	return (result);
}

char			**ft_strsplit_str(char const* str, char const* sub)
{
	char	**result;
	t_u32	reslen;
	t_u32	i;
	t_u32	j;

#if LIBFTCONFIG_HANDLE_NULLPOINTERS
	if (str == NULL || sub == NULL)
		return (NULL);
#endif
	if (sub[0] == '\0')
		return (ft_strdivide(str, 1));
	reslen = count_distinct_sub_in_str(str, sub) + 1;
	if (!(result = ft_strarrnew(reslen)))
		return (NULL);
	i = 0;
	j = 0;
	if (reslen == 1)
		result[0] = ft_strdup(str);
	else
		while (j < reslen)
		{
			result[j] = get_next_chunk(str, sub, &i);
			++j;
		}
	return (result);
}
