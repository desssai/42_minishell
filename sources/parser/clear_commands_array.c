/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_commands_array.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wurrigon <wurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 14:53:20 by ncarob            #+#    #+#             */
/*   Updated: 2022/03/22 18:06:52 by wurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_free_command_redirects(t_cmnds *command)
{
	int	i;

	i = -1;
	while (command->redirs && command->redirs[++i])
	{
		free(command->redirs[i]->filename);
		free(command->redirs[i]);
	}
	if (command->redirs)
		free(command->redirs);
}

int	ft_array_clear(char ***array)
{
	int	i;

	i = -1;
	if (!*array)
		return (1);
	while ((*array)[++i])
		free((*array)[i]);
	free(*array);
	*array = NULL;
	return (1);
}

void	ft_commands_clear(t_cmnds ***commands)
{
	int	i;

	i = -1;
	if (!commands || !(*commands))
		return ;
	while (((*commands)[++i]))
	{
		ft_free_command_redirects((*commands)[i]);
		ft_lstclear(&(*commands)[i]->args);
		free((*commands)[i]);
	}
	free((*commands));
	(*commands) = NULL;
}
