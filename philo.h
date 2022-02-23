#ifndef PHILO_H
# define PHILO_H

# include "string.h"
# include "unistd.h"
# include "stdio.h"
# include "stdlib.h"
# include "sys/time.h"
# include "pthread.h"

struct	s_arg;

typedef struct s_philo
{
	int				number;
	int				is_eating;
	int				last_eat;
	int				left_fork;
	int				right_fork;
	int				eat;
	struct s_arg	*arg;
}				t_philo;

typedef struct s_arg
{
	int				number;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			must_eat;
	t_philo			*philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	death;
	int				limit;
	pthread_mutex_t	message;
	int				start;
}				t_arg;

int		error(t_arg *arg, char *str);
int		ft_atoi(const char *str);
int		init(t_arg *arg, int argc, char **argv);
int		get_time(void);
void	message(t_philo *philo, char *str);
void	take_forks(t_philo *philo);
void	put_forks(t_philo *philo);
void	eat(t_philo *philo);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_itoa(int n);

#endif
