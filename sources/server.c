/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz <ddiniz@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 13:05:41 by ddiniz            #+#    #+#             */
/*   Updated: 2022/11/09 23:04:20 by ddiniz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minitalk.h>

void	signal_handler(int signal)
{
	static unsigned char	target_char;
	static int				count;
	unsigned char			mask;

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
	ft_printf("Server's PID: %d\n", (int)getpid());
	if (signal(SIGUSR1, signal_handler) == SIG_ERR)
	{
		ft_printf("Fatal: signal setting failed!%c\n", 0);
		exit(EXIT_FAILURE);
	}
	if (signal(SIGUSR2, signal_handler) == SIG_ERR)
	{
		ft_printf("Fatal: signal setting failed!%c\n", 0);
		exit(EXIT_FAILURE);
	}
	while (1)
		pause();
	return (0);
}
