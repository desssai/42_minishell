/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncarob <ncarob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 12:18:03 by ncarob            #+#    #+#             */
/*   Updated: 2022/03/07 22:09:21 by ncarob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>

# define MLC_ERROR "minishell: memory allocation error\n"
# define CMD_ERROR "minishell: parsing error\n"

// Environment variables list structure.

typedef struct s_envars
{
	char				*key;
	char				*value;
	struct s_envars		*next;
}	t_envars;

// Commands list structure.

typedef struct s_comnds
{
	char			*command;
	char			*outfile;
	char			*infile;
	char			**args;
	int				append;
	char			*flag;
	t_envars		*envs;
	struct s_comnds	*next;
}	t_cmnds;

// Command Parser.

void		ft_command_add_back(t_cmnds **commands_list, t_cmnds *new_command);
void		ft_check_quotes(char c, int *inside_s_quote, int *inside_d_quote);
t_cmnds		*ft_init_commands(char *str, t_envars *envs);
t_cmnds		*ft_command_new(char *str, t_envars *envs);
t_cmnds		*ft_parse_input(char *str, t_envars *envs);
void		ft_commands_clear(t_cmnds **commands_list);

// Environment Variables Parser.

void		ft_envar_add_back(t_envars **vars, t_envars *new_var);
void		ft_envar_del_one(t_envars **vars, char *key);
t_envars	*ft_envar_new(char *key, char *value);
void		ft_envars_clear(t_envars **vars);
void		ft_print_envars(t_envars *vars);
t_envars	*ft_init_envars(char **envp);

// Readline and prompt.

void		add_line_to_history(char *line);
void		set_prompt(t_envars **envs);
char		*read_prompt_line(void);

// Utilities.

void		fatal_error(char *msg);

#endif