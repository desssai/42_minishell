/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wurrigon <wurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 15:21:34 by ncarob            #+#    #+#             */
/*   Updated: 2022/03/10 20:05:03 by wurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_envars	*envs;
	t_shell		shell;

	shell.exit_status = -1;
	(void)argv;
	if (argc != 1)
		return (printf("Type commands after minishell is launched stupidass\n"));
	envs = ft_init_envars(envp);
	set_shell(&envs, &shell);
	
	ft_envars_clear(&envs);
	return (shell.exit_status);
}
