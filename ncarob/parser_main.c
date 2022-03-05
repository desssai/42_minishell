/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncarob <ncarob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 15:21:34 by ncarob            #+#    #+#             */
/*   Updated: 2022/03/05 23:18:30 by ncarob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	*read_prompt_line(void)
// {
// 	static char	*line_read;

// 	line_read = NULL;
// 	if (line_read)
// 	{
// 		free(line_read);
// 		line_read = NULL;
// 	}
// 	line_read = readline("minishell> ");
// 	return (line_read);
// }

// void	set_prompt(t_env_vars *envs)
// {
// 	char	*line;

// 	line = NULL;
// 	while (1)
// 	{
// 		line = read_prompt_line();
// 		if (!line)
// 			break ;
// 		else
// 			ft_parse_input(line, envs);
// 		free(line);
// 	}
// 	exit(EXIT_SUCCESS);
// }

int	main(int argc, char **argv, char **envp)
{
	t_envars	**envs;

	(void)argv;
	if (argc != 1)
		return (printf("Type commands after minishell is launched stupidass\n"));
	envs = ft_init_envars(envp);
	ft_print_envars(*envs);
	// set_prompt(envs);
	return (0);
}
