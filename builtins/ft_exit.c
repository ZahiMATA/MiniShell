#include "minishell.h"
#include <limits.h>

/* --------- helper overflow: parse to long long, return 0 ok / 1 overflow --------- */
static int  atoll_overflow(const char *s, long long *out)
{
    int                     sign;
    unsigned long long      acc;
    unsigned long long      cut;
    unsigned int            dig;
    size_t                  i;

    i = 0;
    sign = 1;
    acc = 0;
    if (s[i] == '+' || s[i] == '-')
    {
        if (s[i] == '-')
            sign = -1;
        i++;
    }
    /* limite absolue selon le signe (LLONG_MIN = -9223372036854775808) */
    cut = (sign == 1) ? (unsigned long long)LLONG_MAX
                      :     (unsigned long long)LLONG_MAX + 1ULL;
                          //: (unsigned long long)(-(LLONG_MIN + 0LL));
    while (s[i])
    {
        dig = (unsigned int)(s[i] - '0');
        if (acc > cut / 10ULL || (acc == cut / 10ULL && dig > (cut % 10ULL)))
            return (1);
        acc = acc * 10ULL + dig;
        i++;
    }
    if (out)
        *out = (sign == 1) ? (long long)acc : -(long long)acc;
    return (0);
}

int ft_is_numeric(char *str) /* inchangé */
{
    int i;

    if (!str || !str[0])
        return (0);
    i = 0;
    if (str[i] == '+' || str[i] == '-')
        i++;
    if (!str[i])
        return (0);
    while (str[i])
    {
        if (str[i] < '0' || str[i] > '9')
            return (0);
        i++;
    }
    return (1);
}

int ft_exit(t_minishell *m, t_cmd *cmd)
{
    int         status;
    long long   ll;

    if (!cmd || !cmd->args || !cmd->args[1])
    {
        //fou la merde sur le testeur
        //ft_printf_fd(STDERR_FILENO, "exit\n");
        status = (unsigned char)m->last_status;
        mem_free_all(m);
        exit(status);
    }
    if (cmd->args[2])
    {
        ft_printf_fd(STDERR_FILENO, "%s: exit: too many arguments\n", MINISHELL);
        return (1);
    }
    if (!ft_is_numeric(cmd->args[1]) || atoll_overflow(cmd->args[1], &ll))
    {
        ft_printf_fd(STDERR_FILENO, "%s: exit: %s: numeric argument required\n",
            MINISHELL, cmd->args[1]);
        //ft_printf_fd(STDERR_FILENO, "exit\n");
        mem_free_all(m);
        exit(2);
    }
    status = (int)(unsigned char)ll;
    //ft_printf_fd(STDERR_FILENO, "exit\n");
    mem_free_all(m);
    exit(status);
}
