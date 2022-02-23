#include "philo.h"

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->arg->forks[philo->left_fork]);
	message(philo, "take left fork");
	pthread_mutex_lock(&philo->arg->forks[philo->right_fork]);
	message(philo, "take right fork");
}

void	put_forks(t_philo *philo)
{
	message(philo, "is sleeping");
	pthread_mutex_unlock(&philo->arg->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->arg->forks[philo->right_fork]);
	usleep(philo->arg->time_to_sleep * 1000);
}

void	message(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->arg->message);
	if (philo->arg->limit != philo->arg->number)
		printf("%d\t%d %s\n",
			get_time() - philo->arg->start, philo->number + 1, str);
	pthread_mutex_unlock(&philo->arg->message);
}

int	get_time(void)
{
	static struct timeval	tv;
	int						msec;

	gettimeofday(&tv, NULL);
	msec = (tv.tv_sec * 1000 + tv.tv_usec / 1000);
	return (msec);
}

void	eat(t_philo *philo)
{
	char	*str;

	philo->is_eating = 1;
	philo->last_eat = get_time();
	str = ft_strjoin("is eating ", ft_itoa(philo->eat + 1));
	message(philo, str);
	free(str);
	usleep(philo->arg->time_to_eat * 1000);
	philo->eat++;
	if (philo->eat == (int)philo->arg->must_eat)
		philo->arg->limit++;
	philo->is_eating = 0;
}
