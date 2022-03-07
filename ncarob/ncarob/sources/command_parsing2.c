/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parsing2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncarob <ncarob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 14:27:27 by ncarob            #+#    #+#             */
/*   Updated: 2022/03/07 22:08:30 by ncarob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmnds	*ft_init_commands(char *str, t_envars *envs)
{
	t_cmnds	*command;
	t_cmnds	*commands_list;
	char	**command_blocks;

	commands_list = NULL;
	command_blocks = ft_split(str, '|');
	if (!command_blocks)
		return (NULL);
	while (*command_blocks)
	{
		command = ft_command_new(*command_blocks, envs);
		if (!command)
			fatal_error(MLC_ERROR);
		ft_command_add_back(&commands_list, command);
		free(*command_blocks);
		command_blocks++;
	}
	free(command_blocks);
}

t_cmnds	*ft_command_new(char *str, t_envars *envs)
{
	t_cmnds	*command;
	int		i;
	int		j;

	command = (t_cmnds *)malloc(sizeof(t_cmnds));
	if (!command)
		return (NULL);
	i = -1;
	while (str && str[++i] && (str[i] != ' ' || str[i] != '<' || str[i] != '>'))
		;
	j = i;
	command->command = ft_substr(str, 0, i);
	command->flag = ft_get_command_flag(&str);
	command->infile = ft_get_command_infile(&str);
	command->outfile = ft_get_command_outfile(&str);
	command->envs = envs;
	command->next = NULL;
	return (command);
}

void	ft_command_add_back(t_cmnds **commands_list, t_cmnds *new_command)
{
	t_cmnds	*copy;

	copy = *commands_list;
	if (!(*commands_list))
	{
		new_command->next = *commands_list;
		*commands_list = new_command;
	}
	else
	{
		while (copy->next)
			copy = copy->next;
		copy->next = new_command;
		new_command->next = NULL;
	}
}

void	ft_commands_clear(t_cmnds **commands_list)
{
	t_cmnds	*prev;

	if (!(*commands_list))
		return ;
	prev = NULL;
	while (*commands_list)
	{
		prev = (*commands_list);
		(*commands_list) = (*commands_list)->next;
		if (prev)
		{
			free(prev->outfile);
			free(prev->command);
			free(prev->infile);
			free(prev->flag);
			while (prev->args)
			{
				free(*(prev->args));
				prev->args++;
			}
			free(prev);
		}
	}
	*commands_list = NULL;
}

void	ft_check_quotes(char c, int *inside_s_quote, int *inside_d_quote)
{
	if (!*inside_d_quote && !*inside_s_quote && c == '\'')
		*inside_s_quote = 1;
	else if (!*inside_d_quote && !*inside_s_quote && c == '\"')
		*inside_d_quote = 1;
	else if (!*inside_d_quote && *inside_s_quote && c == '\'')
		inside_s_quote = 0;
	else if (*inside_d_quote && !*inside_s_quote && c == '\"')
		*inside_d_quote = 0;
}
