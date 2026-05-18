/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 09:28:42 by sbonneau          #+#    #+#             */
/*   Updated: 2025/12/10 01:32:55 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# define RESET "\001\033[0m\002"

# define BLACK "\001\033[30m\002"
# define RED "\001\033[31m\002"
# define GREEN "\001\033[32m\002"
# define YELLOW "\001\033[33m\002"
# define BLUE "\001\033[34m\002"
# define MAGENTA "\001\033[35m\002"
# define CYAN "\001\033[36m\002"
# define WHITE "\001\033[37m\002"

# define B_BLACK "\001\033[1;30m\002"
# define B_RED "\001\033[1;31m\002"
# define B_GREEN "\001\033[1;32m\002"
# define B_YELLOW "\001\033[1;33m\002"
# define B_BLUE "\001\033[1;34m\002"
# define B_MAGENTA "\001\033[1;35m\002"
# define B_CYAN "\001\033[1;36m\002"
# define B_WHITE "\001\033[1;37m\002"

# define UNEXCEPTED_TOKEN "syntax error near unexpected token `"
# define COMMAND_NOT_FOUND ": command not found\n"
# define HEREDOC_LIMITED "warning: here-document delimited by EOF\n"

# define EXIT_COMMAND_NOT_FOUND 127
# define EXIT_FOUND_BUT_NOT_EXECUTABLE 126
# define EXIT_COMMAND_FAILED 128

# define SIGNAL_INTERUP 130

#endif
