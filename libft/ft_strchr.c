/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD:libft/ft_strchr.c
/*   Created: 2024/11/02 21:04:10 by mzhitnik          #+#    #+#             */
/*   Updated: 2024/11/09 13:24:41 by mzhitnik         ###   ########.fr       */
=======
/*   Created: 2025/03/13 15:14:49 by ekashirs          #+#    #+#             */
/*   Updated: 2025/03/17 14:24:29 by ekashirs         ###   ########.fr       */
>>>>>>> af99a88 (add some builtin funcs):src/builtins/pwd.c
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
<<<<<<< HEAD:libft/ft_strchr.c
	if (str == NULL)
		return (NULL);
	while (*str)
=======
	char	*cur_dir;

	cur_dir = getcwd(cur_dir, LEN_PATH);
	if (cur_dir == NULL)
	{
		error_msg(ERR_GETCWD, "", ERR_NOFILE);
		cmd->status = EXIT_FAILURE;
		return ;
	}
	else
>>>>>>> af99a88 (add some builtin funcs):src/builtins/pwd.c
	{
		if (*str == (unsigned char)c)
			return ((char *)str);
		str++;
	}
<<<<<<< HEAD:libft/ft_strchr.c
	if (c == '\0')
		return ((char *)str);
	return (NULL);
=======
>>>>>>> af99a88 (add some builtin funcs):src/builtins/pwd.c
}
