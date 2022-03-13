/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wurrigon <wurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 21:41:59 by wurrigon          #+#    #+#             */
/*   Updated: 2022/03/13 18:40:27 by wurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void execute_env(t_envars **list, t_shell *shell)
{

	t_envars *tmp;

	tmp = *list;
	shell->exit_status = 0;
	while (tmp)
	{
		write(STDOUT_FILENO, tmp->key, ft_strlen(tmp->key));
		write(STDOUT_FILENO, "=", 1);
		write(STDOUT_FILENO, tmp->value, ft_strlen(tmp->value));
		write(STDOUT_FILENO, "\n", 1);
		tmp = tmp->next;
	}
}