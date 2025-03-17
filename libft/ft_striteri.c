/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD:libft/ft_striteri.c
/*   Created: 2024/07/17 15:14:38 by mzhitnik          #+#    #+#             */
/*   Updated: 2024/11/07 13:35:49 by mzhitnik         ###   ########.fr       */
=======
/*   Created: 2025/03/13 14:17:32 by ekashirs          #+#    #+#             */
<<<<<<< HEAD:libft/ft_striteri.c
/*   Updated: 2025/03/17 14:06:11 by ekashirs         ###   ########.fr       */
>>>>>>> af99a88 (add some builtin funcs):src/builtins/env.c
=======
/*   Updated: 2025/03/17 16:48:31 by ekashirs         ###   ########.fr       */
>>>>>>> 8e9793e (update builtin):src/builtins/env.c
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
<<<<<<< HEAD:libft/ft_striteri.c
	unsigned int	i;
=======
	t_list	*current;
>>>>>>> 8e9793e (update builtin):src/builtins/env.c

<<<<<<< HEAD:libft/ft_striteri.c
	if (!s || !f)
		return ;
=======
	if(cmd->args[0])
	{
		error_msg (ERR_ENV, cmd->args[0], ERR_NOFILE);
		cmd->status = EXIT_FAILURE;
		return ;
	}
<<<<<<< HEAD:libft/ft_striteri.c
>>>>>>> af99a88 (add some builtin funcs):src/builtins/env.c
	i = 0;
	while (s[i] != '\0')
	{
		f(i, &s[i]);
		i++;
=======
	current = cmd->envp;
	while(current)
	{
		if(ft_strchr(current->content, '='))
			printf("%s\n", current->content);
		current = current->next;
>>>>>>> 8e9793e (update builtin):src/builtins/env.c
	}
}
