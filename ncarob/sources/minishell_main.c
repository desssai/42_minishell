/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wurrigon <wurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 15:21:34 by ncarob            #+#    #+#             */
/*   Updated: 2022/03/10 21:05:59 by wurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void set_shell_level(t_envars *envs, t_shell *shell)
{
	t_envars *tmp;

	tmp = envs;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, "SHLVL", 5) == 0 
			&& ft_strlen(tmp->key) == ft_strlen("SHLVL"))
			shell->shell_level = ft_atoi(tmp->value);
		tmp = tmp->next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_envars	*envs;
	t_shell		shell;

	(void)argv;
	if (argc != 1)
		return (printf("Type commands after minishell is launched stupidass\n"));
	envs = ft_init_envars(envp);
	set_shell_level(envs, &shell);
	shell.exit_status = 0;
	tty_hide_input();
	catch_signals();
	set_shell(&envs, &shell);
	ft_envars_clear(&envs);
	return (shell.exit_status);
}
