/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wurrigon <wurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 21:42:20 by wurrigon          #+#    #+#             */
/*   Updated: 2022/03/10 21:46:15 by wurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"

void execute_pwd(t_shell *shell)
{
	char dir[MAX_PATH];
	
	shell->exit_status = 0;
	if (getcwd(dir, MAX_PATH) == NULL)
		fatal_error(MLC_ERROR);
	write(STDOUT_FILENO, dir, ft_strlen(dir));
	write(STDOUT_FILENO, "\n", 1);
}