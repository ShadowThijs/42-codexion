/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlogtenb <tlogtenb@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 21:25:47 by tlogtenb          #+#    #+#             */
/*   Updated: 2026/05/14 23:02:19 by tlogtenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H

# define CODEXION_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <string.h>
# include <stdbool.h>

typedef struct s_arguments
{
	size_t	num_coders;
	size_t	tt_burn;
	size_t	tt_compile;
	size_t	tt_debug;
	size_t	tt_refactor;
	size_t	num_compiles_req;
	size_t	dong_cool;
	size_t	tp_cycle;
	size_t	total_time;
	bool	use_fifo;
	bool	use_edf;
}	t_arguments;

typedef struct s_coder
{
	struct timeval	last_compilation;
	bool			compiling;
	bool			debugging;
	bool			refactoring;
	bool			burned;
}	t_coder;

int	parse_args(int argc, char *argv[], t_arguments *args);
int	print_errors(char *message);

#endif // CODEXION_H
