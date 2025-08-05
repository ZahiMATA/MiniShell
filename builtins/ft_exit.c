int	ft_is_numeric(char *str) //TODO a mettre dans libft
{
	int	i;

	if (!str || !str[0])
		return (0);

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;

	if (!str[i]) // juste un + ou - seul
		return (0);

	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(char **argv)
{
    int i;

    i = 0;
    write(1, "exit\n", 5);
    if(!argv[1])
        exit(0);
    if (!ft_is_numeric(argv[1]))
    {
        write(2, "exit: numeric argument required\n", 32);
        exit(255);
    }
    else if (argv[2])
    {
        write(2, "exit: too many arguments\n", 26);
        return(1);
    }
    exit(ft_atoi(argv[1]) % 256); // modUlo car peux afficher que 8bit
}
int main()
{
}