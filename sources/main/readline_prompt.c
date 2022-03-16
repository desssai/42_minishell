/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_prompt.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wurrigon <wurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 18:23:49 by ncarob            #+#    #+#             */
/*   Updated: 2022/03/16 13:56:57 by wurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*read_prompt_line(void)
{
	static char	*line_read;

	line_read = NULL;
	if (line_read)
	{
		free(line_read);
		line_read = NULL;
	}
	line_read = readline("minishell> ");
	return (line_read);
}

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
	(void)envp;
	line = NULL;
	rl_outstream = stderr;
	while (1)
	{
		line = read_prompt_line();
		if (!line)
			exit(1);
		else
		{
			i = -1;
			commands = ft_parse_input(line, *envs);
			while (commands && commands[++i])
				built_ins(envs, commands[i], shell, envp);
			ft_commands_clear(commands);
		}
		add_line_to_history(line);
		free(line);
	}
}
