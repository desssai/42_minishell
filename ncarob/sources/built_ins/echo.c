/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wurrigon <wurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 21:42:05 by wurrigon          #+#    #+#             */
/*   Updated: 2022/03/10 21:46:58 by wurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void execute_echo(t_cmnds *commands, t_shell *shell)
{
	write(STDOUT_FILENO, *(commands->args), ft_strlen(*(commands->args)));
	if (commands->flag)
		write(STDOUT_FILENO, "$", 1);
	else if (!commands->flag)
		write(STDOUT_FILENO, "\n", 1);
}	