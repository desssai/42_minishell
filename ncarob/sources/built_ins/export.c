/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wurrigon <wurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 21:41:59 by wurrigon          #+#    #+#             */
/*   Updated: 2022/03/11 18:37:59 by wurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int get_list_size(t_envars *list)
{
	t_envars	*tmp;
	int			size_of_list;

	tmp = list;
	size_of_list = 0;
	while (tmp != NULL)
	{
		size_of_list++;
		tmp = tmp->next;
	}
	if (size_of_list == 0)
		return 0;	
}

void handle_export_without_args(t_envars *list)
{
	int size;

	size = get_list_size(list);
}

void execute_export(t_envars **list, t_cmnds *commands, t_shell *shell)
{
	(void)shell;

	if (!commands->args)
	{
		shell->exit_status = 0;		
		// sort list and display it
		handle_export_without_args(*list);
	}
	
}