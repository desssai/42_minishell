/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wurrigon <wurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 18:32:06 by wurrigon          #+#    #+#             */
/*   Updated: 2022/03/16 20:09:13 by wurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void execute_bin(t_cmnds *command, t_shell *shell, char **envp)
{
	pid_t 		pid;
	char 		*path;
	char		**cmd_args;
	int			status;
	
	(void)shell;
	cmd_args = get_command_arguments(command->args);
	path = command->args->content;
	pid = fork();
	if (pid == 0)
	{
		if (execve(path, cmd_args, envp) == -1)
		{
			write(STDERR_FILENO, "minishell: ", 11);
			write(STDERR_FILENO, command->args->content, ft_strlen(command->args->content));
			write(STDERR_FILENO, ": command not found\n", 21);
			exit(EXIT_ERR);
		}
		free(cmd_args);
	}
	else
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, (void *)sigint_handler);
		waitpid(-1, &status, 0);
	}
}