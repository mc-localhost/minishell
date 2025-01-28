/*	FOR GARBAGE COLLECTOR	*/

typedef struct s_alloc_node
{
	void				*ptr;
	struct s_alloc_node	*next;
}						t_alloc_node;

/*	FOR ENVIRONMENT VARIABLES	*/

typedef struct s_env_node
{
	char				*key;
	char				*value;
	struct s_env_node *next; // technically prev, not next
}						t_env_node;

/*	FOR PARSING		*/

typedef enum e_token_type
{
	TOKEN_STRING,
	TOKEN_CMD,
	TOKEN_BUILTIN,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_EOF,
	TOKEN_INVALID
}						t_token_type;

typedef struct s_token
{
	t_token_type		type;
	// for command name
	char				*value;
	// for command flags and etc.
	char				**args;
	// for redirections
	char				*file;
}						t_token;

/*	FOR STORING VARS AND COMMANDS	*/

typedef struct s_data
{
	t_token				*tokens;
	t_env_node			*envs;
}						t_data;