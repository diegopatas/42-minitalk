/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz <ddiniz@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 13:05:41 by ddiniz            #+#    #+#             */
/*   Updated: 2022/11/11 12:08:36 by ddiniz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minitalk_bonus.h>

static	void	signal_handler(int signal, siginfo_t *siginfo, void *context)
{
	static unsigned char	target_char;
	static int				count;
	unsigned char			mask;

	(void)context;
	if (signal == SIGUSR1)
	{
		mask = 1 << (7 - count);
		target_char = target_char | mask;
		count++;
	}
	else if (signal == SIGUSR2)
	{
		mask = 1 << (7 - count);
		target_char = target_char & ~mask;
		count++;
	}
	kill(siginfo->si_pid, SIGUSR1);
	if (count == 8)
	{
		write(1, &target_char, 1);
		count = 0;
		target_char = 0;
	}
	return ;
}

int	main(void)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(sigaction));
	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = signal_handler;
	sigemptyset(&act.sa_mask);
	ft_printf("Server's PID: %d\n", (int)getpid());
	if (sigaction(SIGUSR1, &act, 0) < 0)
	{
		ft_printf("Fatal: SIGUSR1 setting failed!%c\n", 0);
		exit(EXIT_FAILURE);
	}
	if (sigaction(SIGUSR2, &act, 0) < 0)
	{
		ft_printf("Fatal: SIGUSR2 setting failed!%c\n", 0);
		exit(EXIT_FAILURE);
	}
	while (1)
		pause();
	return (EXIT_SUCCESS);
}
