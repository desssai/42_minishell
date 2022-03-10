/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wurrigon <wurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 19:44:28 by wurrigon          #+#    #+#             */
/*   Updated: 2022/03/10 22:15:14 by wurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void built_ins(t_envars **list, t_cmnds *store, t_shell *shell)
{
	if (ft_strncmp((const char *)store->command, "pwd", 3) == 0 &&
		ft_strlen(store->command) == ft_strlen("pwd"))
		execute_pwd(shell);
	else if (ft_strncmp((const char *)store->command, "env", 3) == 0 &&
		ft_strlen(store->command) == ft_strlen("env"))
		execute_env(*list, shell);
	else if (ft_strncmp((const char *)store->command, "unset", 5) == 0 &&
		ft_strlen(store->command) == ft_strlen("unset"))
		execute_unset(list, store->args, shell);
	else if (ft_strncmp((const char *)store->command, "exit", 4) == 0 &&
		ft_strlen(store->command) == ft_strlen("exit"))
		execute_exit(shell, store);
	else if (ft_strncmp((const char *)store->command, "cd", 2) == 0 &&
		ft_strlen(store->command) == ft_strlen("cd"))
		execute_cd(list, &store, shell);
	else if (ft_strncmp((const char *)store->command, "echo", 4) == 0 &&
		ft_strlen(store->command) == ft_strlen("echo"))
		execute_echo(store, shell);
	else if (ft_strncmp((const char *)store->command, "export", 6) == 0 &&
		ft_strlen(store->command) == ft_strlen("export"))
		execute_export(list, store, shell);
}