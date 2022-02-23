#include "philo.h"

static int	init_philo(t_arg *arg)
{
	int		n;

	n = 0;
	arg->philo = (t_philo *)malloc(sizeof(t_philo) * arg->number);
	if (!arg->philo)
		return (0);
	while (n < arg->number)
	{
		arg->philo[n].number = n;
		arg->philo[n].is_eating = 0;
		arg->philo[n].eat = 0;
		arg->philo[n].left_fork = n;
		arg->philo[n].right_fork = (n + 1) % arg->number;
		arg->philo[n].arg = arg;
		n++;
	}
	return (1);
}

int	init_m(t_arg *arg)
{
	int		i;

	i = 0;
	pthread_mutex_init(&arg->message, NULL);
	pthread_mutex_init(&arg->death, NULL);
	pthread_mutex_lock(&arg->death);
	arg->forks = (pthread_mutex_t *)malloc(
			sizeof(pthread_mutex_t) * arg->number);
	if (!arg->forks)
		return (0);
	while (i < arg->number)
	{
		pthread_mutex_init(&arg->forks[i], NULL);
		i++;
	}
	return (1);
}

int	init(t_arg *arg, int argc, char **argv)
{
	arg->number = ft_atoi(argv[1]);
	arg->time_to_die = ft_atoi(argv[2]);
	arg->time_to_eat = ft_atoi(argv[3]);
	arg->time_to_sleep = ft_atoi(argv[4]);
	arg->must_eat = 0;
	arg->limit = 0;
	if (argc == 6)
	{
		arg->must_eat = ft_atoi(argv[5]);
		if (arg->must_eat < 1)
			return (0);
	}
	if (arg->number < 1)
		return (0);
	if (!init_philo(arg) || !init_m(arg))
		return (0);
	return (1);
}
