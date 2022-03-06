/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncarob <ncarob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 15:21:34 by ncarob            #+#    #+#             */
/*   Updated: 2022/03/06 15:31:14 by ncarob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	set_prompt(t_envars **envs)
{
	char	*line;

	line = NULL;
	while (1)
	{
		line = read_prompt_line();
		if (!line)
			break ;
		else
			ft_parse_input(line, *envs);
		free(line);
	}
	exit(EXIT_SUCCESS);
}

int	main(int argc, char **argv, char **envp)
{
	t_envars	*envs;

	(void)argv;
	if (argc != 1)
		return (printf("Type commands after minishell is launched stupidass\n"));
	envs = ft_init_envars(envp);
	set_prompt(&envs);
	ft_envars_clear(&envs);
	return (0);
}
