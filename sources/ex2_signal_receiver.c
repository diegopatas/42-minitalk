/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_receiver.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz <ddiniz@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 21:15:27 by ddiniz            #+#    #+#             */
/*   Updated: 2022/10/21 10:30:05 by ddiniz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#define _GNU_SOURCE

void	print_sigset(FILE *file_target, const char *prefix, const sigset_t *signal_set);

static int count_othersignals[NSIG];
static volatile sig_atomic_t flag_sigint = 0;

static void handler(int signal)
{
	if (signal == SIGINT)
		flag_sigint = 1;
	else
		count_othersignals[signal]++;
}

int	main(int argc, char *argv[])
{
	int	id_signal;
	int	num_secs;
	sigset_t	pending_mask;
	sigset_t	blocking_mask;
	sigset_t	empty_mask;

	printf("%s: PID is %ld\n", argv[0], (long)getpid());
	/* Here is setting severals signal handlers */
	for (id_signal = 1; id_signal < NSIG; id_signal++)
		(void)signal(id_signal, handler);
	if (argc > 1)
	{
		num_secs = atoi(argv[1]);
		/* Here I fill the blocking var with all signal integers */
		sigfillset(&blocking_mask);
		/* Here a set a mask to block the signals */
		if (sigprocmask(SIG_SETMASK, &blocking_mask, NULL) == -1)
			exit(0);
		printf("%s: sleeping for %d seconds\n", argv[0], num_secs);
		sleep(num_secs);
		/* Here I handle signal that maybe will be sent to the program */
		if (sigpending(&pending_mask) == -1)
			exit(0);
		printf("%s: pending signals are: \n", argv[0]);
		print_sigset(stdout, "\t\t", &pending_mask);
		/* Here I define another var as the new mask */
		sigemptyset(&empty_mask);
		if (sigprocmask(SIG_SETMASK, &empty_mask, NULL) == -1)
			exit(0);
	}
	/* Here the program runs until it gets a signal that would change the control flow */
	while (!flag_sigint)
		continue ;
	/* Next, I show the results */
	for (id_signal = 1; id_signal < NSIG; id_signal++)
		if (count_othersignals[id_signal] != 0)
			printf("%s: signal %d caught %d time%s\n",
			argv[0], id_signal, count_othersignals[id_signal], (count_othersignals[id_signal] == 1) ? "" : "s");
	exit(EXIT_SUCCESS);
}
