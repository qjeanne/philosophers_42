#include "philo.h"

static void	*death(void *philo1)
{
	t_philo		*philo;

	philo = (t_philo *)philo1;
	while (1)
	{
		if (!philo->is_eating && get_time()
			> (int)(philo->last_eat + philo->arg->time_to_die))
		{
			message(philo, "is died");
			pthread_mutex_unlock(&philo->arg->death);
			return ((void *)0);
		}
		usleep(1000);
	}
	return ((void *)0);
}

static void	*limit(void *arg1)
{
	t_arg	*arg;

	arg = (t_arg *)arg1;
	while (1)
	{
		if (arg->limit == arg->number)
		{
			printf("Everyone ate the required number of times\n");
			pthread_mutex_unlock(&arg->death);
			return ((void *) 0);
		}
		usleep(1000);
	}
	return ((void *) 0);
}

static void	*base(void *philo1)
{
	t_philo		*philo;
	pthread_t	t;

	philo = (t_philo *)philo1;
	philo->last_eat = get_time();
	if (pthread_create(&t, NULL, &death, philo1) != 0)
		return ((void *)0);
	pthread_detach(t);
	while (1)
	{
		take_forks(philo);
		eat(philo);
		put_forks(philo);
		message(philo, "is thinking");
	}
	return ((void *)0);
}

static int	start(t_arg *arg)
{
	int			i;
	pthread_t	t;
	pthread_t	tid;
	void		*tmp;

	i = 0;
	tid = NULL;
	arg->start = get_time();
	tmp = (void *)arg;
	if (arg->must_eat > 0)
	{
		if (pthread_create(&tid, NULL, &limit, tmp) != 0)
			return (0);
	}
	pthread_detach(tid);
	while (i < arg->number)
	{
		if (pthread_create(&t, NULL, &base, (void *)&arg->philo[i]) != 0)
			return (0);
		pthread_detach(tid);
		usleep(1000);
		i++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_arg	*arg;

	arg = (t_arg *)malloc(sizeof(t_arg));
	if (argc < 5 || argc > 6)
		return (error(NULL, "Error:\nwrong number of arguments"));
	if (!init(arg, argc, argv))
		return (error(NULL, "Error:\ninitialization problem"));
	if (!start(arg))
		return (error(arg, "Error:\npthread problem"));
	pthread_mutex_lock(&arg->death);
	pthread_mutex_unlock(&arg->death);
	error(arg, NULL);
	return (0);
}
