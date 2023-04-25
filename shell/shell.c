#include "main.h"


/**
 * get_input - Gets user input from the command line.
 *
 * @prompt: The prompt to display to the user.
 *
 * Return: A pointer to the input string entered by the user.
 */

char *get_input(const char *prompt)
{
	char *ptr = NULL;
	size_t n = 0;
	ssize_t char_input;

	printf("%s", prompt);
	char_input = getline(&ptr, &n, stdin);

	if (char_input == -1)
	{
		printf("Exiting shell....\n");
		return (NULL);
	}

	return (ptr);
}

/**
 * split_string - Splits a string into tokens using a specified delimiter.
 *
 * @input: The string to split.
 * @delim: The delimiter to use for splitting.
 * @num_toks: pointer to an integer where the number of tokens will be stored.
 *
 * Return: retruns  an array of strings containing the tokens.
 */

char **split_string(char *input, const char *delim, int *num_toks)
{
	char *tok;
	char *input_copy = strdup(input);
	char **toks = NULL;

	tok = strtok(input, delim);

	while (tok != NULL)
	{
	(*num_toks)++;
	tok = strtok(NULL, delim);
	}
	(*num_toks)++;

	toks = malloc(sizeof(char *) * (*num_toks));

	tok = strtok(input_copy, delim);

	for (int i = 0; tok != NULL; i++)
	{
	toks[i] = strdup(tok);
	tok = strtok(NULL, delim);
	}
	toks[*num_toks - 1] = NULL;

	free(input_copy);

	return (toks);
}

/**
 * execute_command - handles the execution of a command
 * @args: input arg
 * @envp: input envp
 * Return: void
 */

void execute_command(char **args, char **envp)
{
	pid_t pid = fork();
	int status;

	if (pid < 0)
	{
	perror("fork() failed");
	exit(1);
	}
	else if (pid == 0)
	{

	if (execve(args[0], args, envp) == -1)
	{
	perror("execve() failed");
	exit(1);
	}
	}
	else
	{
	if (waitpid(pid, &status, 0) == -1)
	{
	perror("waitpid() failed");
	exit(1);
	}
	}
}

/**
 * main - function for the simple shell program.
 *
 * @argc: The number of arguments passed to the program.
 * @envp: An array of strings containing the environment variables.
 *
 * Return: 0 on success, 1 on failure.
 */

int main(int argc, char **envp)
{
	(void)argc;
	char *prompt;
	char *input;
	int num_args = 0;
	char **toks;

	while (1)
	{
	prompt = PROMPT;
	input = get_input(prompt);
	if (input == NULL)
		break;
	if (strlen(input) == 1)
		continue;
	toks = split_string(input, " \n", &num_args);
	if (strcmp(toks[0], "exit") == 0)
	{
	free(input);
	free(toks);
	break;
	}
	if (strcmp(toks[0], "exit") == 0)
	{
	free(input);
	free(toks);
	break;
	}
	else
	{
	execute_command(toks, envp);
	free(input);
	free(toks);
	}
	}

	printf("Exiting shell...\n");
	return (0);
}
