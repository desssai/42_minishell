/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parsing1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncarob <ncarob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 14:27:27 by ncarob            #+#    #+#             */
/*   Updated: 2022/03/08 18:26:07 by ncarob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_check_line(char *str)
{
	int		num_of_commands;
	int		inside_s_quote;
	int		inside_d_quote;
	int		i;

	i = -1;
	inside_s_quote = 0;
	inside_d_quote = 0;
	num_of_commands = 1;
	while (str && str[++i])
	{
		if (str[i] == '\\')
			return (EXIT_FAILURE);
		else if (str[i] == ';')
			return (EXIT_FAILURE);
		else if (!inside_s_quote && !inside_d_quote && str[i] == '|')
			num_of_commands++;
		else
			ft_check_quotes(str[i], &inside_s_quote, &inside_d_quote);
	}
	if (!str || inside_s_quote || inside_d_quote)
		return (EXIT_FAILURE);
	return (num_of_commands);
}

char	*ft_replace_path(char *str, int *index, t_envars *envs)
{
	char	*value;
	int		i;

	i = *index;
	value = NULL;
	while (str[++i] && str[i] != '\'' && str[i] != '\"'
		&& str[i] != '$' && str[i] != ' ')
		;
	while (!value && envs)
	{
		if (!ft_strncmp(&str[*index + 1], envs->key, i - *index - 1))
			value = ft_strdup(envs->value);
		envs = envs->next;
	}
	if (value)
	{
		value = ft_strjoin(ft_substr(str, 0, *index), value, 1, 1);
		*index = ft_strlen(value) - 1;
		value = ft_strjoin(value, ft_strdup(&str[i]), 1, 1);
		free(str);
		return (value);
	}
	free(str);
	return (ft_strdup(""));
}

char	*ft_strip_quotes(char *str, int *index, char quote, t_envars *envs)
{
	int		i;
	char	*tmp[3];

	i = *index;
	while (str[++i] && str[i] != quote)
		if (str[i] == '$' && quote != '\'')
			str = ft_replace_path(str, &i, envs);
	if (i - *index > 1)
	{
		tmp[0] = ft_substr(str, 0, *index);
		tmp[1] = ft_substr(str, *index + 1, i - *index - 1);
		tmp[2] = ft_strdup(&str[i + 1]);
		*index = ft_strlen(tmp[0]) + ft_strlen(tmp[1]) - 1;
	}
	else
	{
		tmp[0] = ft_substr(str, 0, *index);
		*index = ft_strlen(tmp[0]) - 1;
		tmp[1] = ft_strdup(&str[i + 1]);
		tmp[2] = NULL;
	}
	tmp[0] = ft_strjoin(tmp[0], tmp[1], 1, 1);
	tmp[0] = ft_strjoin(tmp[0], tmp[2], 1, 1);
	free(str);
	return (tmp[0]);
}

char	*ft_remove_spaces(char *str)
{
	char	*tmp;
	int		i[5];

	ft_memset(&i, 0, sizeof(int) * 5);
	tmp = NULL;
	while (str[i[0]])
	{
		ft_check_quotes(str[i[0]], &i[4], &i[3]);
		if (!i[3] && !i[4] && str[i[0]] == ' ')
		{
			tmp = ft_substr(str, 0, i[0] + 1);
			i[1] = i[0];
			while (str[++i[0]] && str[i[0]] == ' ')
				;
			tmp = ft_strjoin(tmp, ft_strdup(&str[i[0]]), 1, 1);
			free(str);
			i[0] = i[1];
			str = tmp;
		}
		i[0]++;
	}
	if (!tmp)
		tmp = ft_substr(str, 0, i[0] + 1);
	return (tmp);
}

t_cmnds	**ft_parse_input(char *s, t_envars *envs)
{
	int		num_of_commands;
	t_cmnds	**commands;

	num_of_commands = ft_check_line(s);
	if (!num_of_commands)
		fatal_error(CMD_ERROR);
	commands = (t_cmnds **)malloc(sizeof(t_cmnds *) * (num_of_commands + 1));
	if (!commands)
		fatal_error(MLC_ERROR);
	ft_init_commands(s, commands, envs);
	return (commands);
}
