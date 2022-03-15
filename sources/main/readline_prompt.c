/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_prompt.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wurrigon <wurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 18:23:49 by ncarob            #+#    #+#             */
/*   Updated: 2022/03/15 21:27:09 by wurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_line_to_history(char *line)
{
	if (line && *line)
		add_history(line);
}

void	set_shell(t_envars **envs, t_shell *shell, char **envp)
{
	char	*line;
	t_cmnds	**commands;
	int		i;

	(void)shell;
	line = NULL;
	// rl_outstream = stderr;
	while (1)
	{
		line = readline("minishell> ");
		if (!line)
			break ;
		i = -1;
		commands = ft_parse_input(line, *envs);
		while (commands && commands[++i])
			execute_command(commands[i], shell, envp);
		ft_commands_clear(commands);
		add_line_to_history(line);
		free(line);
	}
}
