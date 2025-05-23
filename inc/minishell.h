/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 14:22:59 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/05/02 11:07:03 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <dirent.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/stat.h>

# include "libft.h"
# include "init.h"
# include "utils.h"
# include "tokenization.h"
# include "errors.h"
# include "builtins.h"
# include "execution.h"
# include "signals.h"

#endif
