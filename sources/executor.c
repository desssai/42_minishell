/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wurrigon <wurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 20:09:53 by wurrigon          #+#    #+#             */
/*   Updated: 2022/03/16 18:27:11 by wurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char **get_command_arguments(t_list *args)
{
	t_list	*curr;
	char 	**cmd_args;
	int		quan;
	int		i;
	
	i = 0;
	curr = args;
	quan = get_args_quantity(args);
	cmd_args = (char **)malloc(sizeof(char *) * quan);
	if (!cmd_args)
		fatal_error(MLC_ERROR);
	while (i < quan)
	{
		cmd_args[i] = ft_strdup(curr->content);
		if (!cmd_args[i])
			fatal_error(MLC_ERROR);
		curr = curr->next; 
		i++;
	}
	cmd_args[i] = NULL;
	return (cmd_args);
}


void execute_system_bin(t_cmnds *command, t_shell *shell, char **envp)
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
			write(STDERR_FILENO, "minishell: ", 12);
			write(STDERR_FILENO, command->args->content, ft_strlen(command->args->content));
			write(STDERR_FILENO, " : command not found\n", 21);
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

void execute_command(t_cmnds *command, t_shell *shell, char **envp)
{
	if (is_built_in(command->args->content))
		built_ins(&(command->envs), command, shell, envp);
	else
	{
		execute_system_bin(command, shell, envp);
	}
}