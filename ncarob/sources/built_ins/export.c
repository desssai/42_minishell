/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wurrigon <wurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 21:41:59 by wurrigon          #+#    #+#             */
/*   Updated: 2022/03/12 19:53:40 by wurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int get_list_size(t_envars *list)
{
	t_envars	*tmp;
	int			size_of_list;

	tmp = list;
	size_of_list = 0;
	while (tmp != NULL)
	{
		size_of_list++;
		tmp = tmp->next;
	}
	if (size_of_list == 0)
		return 0;
	return (size_of_list);
}

void handle_export_without_args(t_envars *list)
{
	int size;

	size = get_list_size(list);
}

void execute_export(t_envars **list, t_cmnds *commands, t_shell *shell)
{
	int i;

	i = 0;
	// No options
	// It will simply print all names marked for an export to a child process
	if (!commands->args)
	{
		// sort list "declare -x" and display it
		shell->exit_status = 0;		
		handle_export_without_args(*list);
	}
	while (commands>args[i])
	{
		// Wrong arguments
		// bash: export: `.=.': not a valid identifier
		// Only chars allowed in key
		if (is_valid_env_key(commands->args[i]) == 1)
		{
			shell->exit_status = EXIT_ERR;
			write(STDERR_FILENO, "minishell: export: `", 20);
			write(STDERR_FILENO, commands->args[i], ft_strlen(commands->args[i]));
			write(STDERR_FILENO, "': not a valid identifier\n", 27);
		}
		// Multiple arguments 
		// It will export all key-values pairs
		i++;
	}
}