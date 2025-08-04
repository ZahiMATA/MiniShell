/*
[<][makefile][tr a A][|][tr b B][>][ficout]
->
typedef struct _s_cmd
{
	char	**args; = [tr][a][b]
	char	*file_in; = "makefile"
	char	*file_out; NULL
	int		append_mode;
	int		heredoc_mode;
	struct	s_cmd	*next;
}	t_cmd;


typedef struct _s_cmd
{
	char	**args; = [tr][b][B]
	char	*file_in; = -1
	char	*file_out; = ficout
	int		append_mode; > -> 0 : >> -> 1
	int		heredoc_mode;
	struct	s_cmd	*next; ->NULL
}	t_cmd;


*/