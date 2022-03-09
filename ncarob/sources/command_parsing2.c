/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parsing2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncarob <ncarob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 14:27:27 by ncarob            #+#    #+#             */
/*   Updated: 2022/03/09 15:12:07 by ncarob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_init_commands(char *str, t_cmnds **commands, t_envars *envs)
{
	int	i;
	int	j;
	int	k;
	int	inside_s_quote;
	int	inside_d_quote;

	i = -1;
	j = 0;
	k = 0;
	inside_s_quote = 0;
	inside_d_quote = 0;
	while (str[++i])
	{
		ft_check_quotes(str[i], &inside_s_quote, &inside_d_quote);
		if (!inside_d_quote && !inside_s_quote && str[i] == '|')
		{
			commands[k++] = ft_command_new(ft_substr(str, j, i - j), envs);
			if (!commands[k - 1])
				fatal_error(MLC_ERROR);
			j = i + 1;
		}
	}
	commands[k++] = ft_command_new(ft_substr(str, j, i - j), envs);
	if (!commands[k - 1])
		fatal_error(MLC_ERROR);
}

char	*ft_remove_quotes(char *str, t_envars *envs)
{
	int	i;

	i = -1;
	while (str && str[++i])
	{
		if (str[i] == '\'')
			str = ft_strip_quotes(str, &i, '\'', NULL);
		else if (str[i] == '\"')
			str = ft_strip_quotes(str, &i, '\"', envs);
		else if (str[i] == '$')
			str = ft_replace_path(str, &i, envs);
	}
	return (str);
}

t_cmnds	*ft_command_new(char *str, t_envars *envs)
{
	t_cmnds	*command;

	if (!str)
		return (NULL);
	command = (t_cmnds *)malloc(sizeof(t_cmnds));
	ft_memset(command, 0, sizeof(t_cmnds));
	if (!command)
		return (NULL);
	ft_get_command_infile(str, command);
	ft_get_command_outfile(str, command);
	str = ft_remove_redirects(str);
	str = ft_remove_spaces(str);
	str = ft_remove_quotes(str, envs);
	command->envs = envs;
	free(str);
	return (command);
}

	// ft_get_command_flag(str, command);

void	ft_commands_clear(t_cmnds **commands)
{
	int	i;
	// int	k;

	i = -1;
	if (!commands)
		return ;
	while (commands[++i])
	{
		free(commands[i]->outfile);
		// free(commands[i]->command);
		free(commands[i]->infile);
		// free(commands[i]->flag);
		// k = -1;
		// while (commands[i]->args[++k])
		// 	free(commands[i]->args[k]);
		// free(commands[i]->args);
		if (commands[i])
			free(commands[i]);
	}
	free(commands);
	commands = NULL;
}

void	ft_check_quotes(char c, int *inside_s_quote, int *inside_d_quote)
{
	if (!*inside_d_quote && !*inside_s_quote && c == '\'')
		*inside_s_quote = 1;
	else if (!*inside_d_quote && !*inside_s_quote && c == '\"')
		*inside_d_quote = 1;
	else if (!*inside_d_quote && *inside_s_quote && c == '\'')
		*inside_s_quote = 0;
	else if (*inside_d_quote && !*inside_s_quote && c == '\"')
		*inside_d_quote = 0;
}
