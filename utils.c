#include "philo.h"

int	error(t_arg *arg, char *str)
{
	int		i;

	if (str)
		printf("%s\n", str);
	if (arg)
	{
		if (arg->forks)
		{
			i = 0;
			while (i < arg->number)
				pthread_mutex_destroy(&arg->forks[i++]);
			free(arg->forks);
		}
		if (arg->philo)
		{
			free(arg->philo);
		}
		pthread_mutex_destroy(&arg->message);
		pthread_mutex_destroy(&arg->death);
		free(arg);
	}
	return (0);
}

int	ft_isspace(char ch)
{
	if (ch == '\t' || ch == '\n' || ch == '\v' || ch == '\f' || ch == '\r'
		|| ch == ' ')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int			sign;
	long int	answer;

	sign = 1;
	answer = 0;
	while (ft_isspace(*str) == 1)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = sign * (-1);
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		answer = (answer * 10) + (*str++ - '0');
		if (answer == 999999999)
		{
			if (sign == -1)
				return (0);
			return (-1);
		}
	}
	return (answer * sign);
}

size_t	ft_strlen(const char *s)
{
	size_t	size;

	size = 0;
	while (s[size] != '\0')
		size++;
	return (size);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	size;

	if (!s1 || !s2)
		return (0);
	size = ft_strlen(s1) + ft_strlen(s2);
	str = malloc(size + 1);
	if (str == 0)
		return (0);
	while (*s1 != '\0')
		*str++ = *s1++;
	while (*s2 != '\0')
		*str++ = *s2++;
	*str = '\0';
	return (str - size);
}
