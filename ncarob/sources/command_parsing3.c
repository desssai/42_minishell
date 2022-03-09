/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parsing3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncarob <ncarob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 14:27:27 by ncarob            #+#    #+#             */
/*   Updated: 2022/03/09 15:29:58 by ncarob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_get_command_infile(char *line, t_cmnds *command)
{
	int	i[4];

	ft_memset(&i, 0, sizeof(int) * 4);
	i[0] = ft_strlen(line);
	while (--i[0] >= 0)
	{
		ft_check_quotes(line[i[0]], &i[2], &i[3]);
		if (!i[2] && !i[3] && line[i[0]] == '<' && !i[1]++)
			break ;
	}
	if (i[1])
	{
		if (i[0] && line[i[0] - 1] == '<')
			command->limiter = 1;
		while (line[++i[0]] && line[i[0]] == ' ')
			;
		i[1]--;
		while (line[i[0] + i[1]]
			&& line[i[0] + i[1]] != ' ' && line[i[0] + i[1]] != '>')
			i[1]++;
	}
	command->infile = ft_substr(line, i[0], i[1]);
}

void	ft_get_command_outfile(char *line, t_cmnds *command)
{
	int	i[4];

	ft_memset(&i, 0, sizeof(int) * 4);
	i[0] = ft_strlen(line);
	while (--i[0] >= 0)
	{
		ft_check_quotes(line[i[0]], &i[2], &i[3]);
		if (!i[2] && !i[3] && line[i[0]] == '>' && !i[1]++)
			break ;
	}
	if (i[1])
	{
		if (i[0] && line[i[0] - 1] == '>')
			command->append = 1;
		while (line[++i[0]] && line[i[0]] == ' ')
			;
		i[1]--;
		while (line[i[0] + i[1]]
			&& line[i[0] + i[1]] != ' ' && line[i[0] + i[1]] != '<')
			i[1]++;
	}
	command->outfile = ft_substr(line, i[0], i[1]);
}

static void	ft_go_through_redirects(char *str, int *i)
{
	if (str[(*i)] && (str[*i] == '<' || str[*i] == '>'))
		(*i)++;
	while (str[++(*i)] && str[*i] == ' ')
		;
	while (str[++(*i)] && str[*i] != ' ')
		;
}

char	*ft_remove_redirects(char *str)
{
	char	*tmp;
	int		i[5];

	ft_memset(&i, 0, sizeof(int) * 5);
	tmp = NULL;
	while (str[i[0]])
	{
		ft_check_quotes(str[i[0]], &i[4], &i[3]);
		if (!i[3] && !i[4] && (str[i[0]] == '<' || str[i[0]] == '>'))
		{
			tmp = ft_substr(str, 0, i[0]);
			i[1] = i[0];
			ft_go_through_redirects(str, &i[0]);
			tmp = ft_strjoin(tmp, ft_strdup(&str[i[0]]), 1, 1);
			free(str);
			i[0] = i[1];
			str = tmp;
		}
		i[0]++;
	}
	if (!tmp)
		return (str);
	return (tmp);
}

// void	ft_get_command_flags(char *line, t_cmnds *command)
// {
// 	int	i;
// 	int	j;

// 	i = -1;
// 	while (line[++i])
// 	{
// 		if (line[i] == '-')
// 		{
// 			j = i + 1;
// 			if (line[++i] != '-')
// 		}
// 	}
// }