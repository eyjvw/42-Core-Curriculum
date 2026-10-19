/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 23:03:24 by sbonneau          #+#    #+#             */
/*   Updated: 2025/12/10 03:41:16 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_free_list(t_tokens *list)
{
	t_tokens	*tmp;

	while (list)
	{
		tmp = list->next;
		if (list->value)
			free(list->value);
		free(list);
		list = tmp;
	}
}

static void	ft_add_word(t_tokens **list, char *marked)
{
	t_tokens	*wild;
	char		*word;

	wild = NULL;
	if (ft_has_glob(marked))
	{
		word = ft_unmark(marked, true);
		if (word)
			wild = ft_expand_wildcards(word);
		free(word);
	}
	if (wild)
	{
		ft_lst_addback((void **)list, wild);
		return ;
	}
	word = ft_unmark(marked, false);
	if (word)
		ft_lst_addback((void **)list, ft_create_token(word, WORD));
	free(word);
}

static t_tokens	*ft_expand_word(t_shell *shell, char *raw)
{
	char		*expanded;
	t_tokens	*words;
	t_tokens	*tmp;
	t_tokens	*list;

	list = NULL;
	expanded = ft_expand_variables(shell, raw, true);
	if (!expanded)
		return (NULL);
	words = ft_split_words(expanded);
	free(expanded);
	tmp = words;
	while (tmp)
	{
		ft_add_word(&list, tmp->value);
		tmp = tmp->next;
	}
	ft_free_list(words);
	return (list);
}

char	**ft_expand_argv(t_shell *shell, char **argv)
{
	t_tokens	*list;
	t_tokens	*tmp;
	char		**res;
	int			i;

	list = NULL;
	i = 0;
	while (argv[i])
		ft_lst_addback((void **)&list, ft_expand_word(shell, argv[i++]));
	res = malloc(sizeof(char *) * (ft_count_args(list) + 1));
	if (!res)
		return (ft_free_list(list), NULL);
	i = 0;
	tmp = list;
	while (tmp)
	{
		res[i++] = tmp->value;
		tmp->value = NULL;
		tmp = tmp->next;
	}
	res[i] = NULL;
	ft_free_list(list);
	return (res);
}

char	*ft_expand_file(t_shell *shell, char *raw)
{
	t_tokens	*list;
	char		*file;

	list = ft_expand_word(shell, raw);
	if (!list || list->next)
	{
		ft_free_list(list);
		ft_error(raw, NULL, "ambiguous redirect");
		return (NULL);
	}
	file = list->value;
	list->value = NULL;
	ft_free_list(list);
	return (file);
}
