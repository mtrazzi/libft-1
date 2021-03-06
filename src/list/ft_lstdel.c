/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list/ft_lstdel.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_memory.h"
#include "libft_list.h"



void	ft_lstdelone(s_list **alst, void (*del)(void *, t_size))
{
#if LIBFTCONFIG_HANDLE_NULLPOINTERS
	if (alst == NULL || del == NULL)
		return ;
#endif
	if (*alst)
	{
		del((*alst)->item, (*alst)->item_size);
		ft_memfree(*alst);
		*alst = NULL;
	}
}



void	ft_lstdel(s_list **alst, void (*del)(void *, t_size))
{
	s_list *lst;
	s_list *tmp;

#if LIBFTCONFIG_HANDLE_NULLPOINTERS
	if (alst == NULL || del == NULL)
		return ;
#endif
	lst = *alst;
	while (lst)
	{
		del(lst->item, lst->item_size);
		tmp = lst;
		lst = lst->next;
		ft_memfree(tmp);
	}
	*alst = NULL;
}



void	ft_lstpop(s_list **alst, void (*del)(void *, t_size))
{
	s_list	*lst;
	s_list	*lst_prev;

#if LIBFTCONFIG_HANDLE_NULLPOINTERS
	if (alst == NULL || del == NULL)
		return ;
#endif
	lst = *alst;
	lst_prev = NULL;
	while (lst)
	{
		if (lst->next == NULL)
		{
			del((lst)->item, (lst)->item_size);
			ft_memfree(lst);
			if (lst_prev)
				lst_prev->next = NULL;
			return ;
		}
		lst_prev = lst;
		lst = lst->next;
	}
}


