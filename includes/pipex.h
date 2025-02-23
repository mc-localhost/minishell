/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaaser <aelaaser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 20:15:54 by aelaaser          #+#    #+#             */
/*   Updated: 2025/02/23 15:04:16 by aelaaser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <errno.h>
# include <string.h>
# include "../libft/libft.h"
# include "minishell.h"

int		open_file(t_token_type type, char *filename, int output);
void	error_exit(const char *msg, int r);
int		ft_arr_size(char **str);
char	**optmize_cmd(char **cmd, char *argv);
void	free_arr(char **str);
char	*find_path(char *cmd, char **envp);
#endif