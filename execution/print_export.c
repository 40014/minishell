#include "../minishell.h"

int count_nodes2(t_env *envp)
{
    int count;

    count = 0;
    while (envp)
    {
        count++;
        envp = envp->next;
    }
    return (count);
}
char **convert_envp_to_arr2(t_env *envp)
{
    int count;
    char **envp_arr;
    char *temp;
    char *temp2;
    int j;

    count = count_nodes2(envp);
    envp_arr = malloc(sizeof(char *) * (count + 1));
    j = 0;
    while (envp)
    {
        if (envp->val != NULL)
        {
            if (envp->val[0] == '/0')
                envp_arr[j] = ft_strjoin(envp->var, "\"\"", 1, 1);
            else
            {
                temp = ft_strjoin("\"", envp->val, 1, 1);
                temp2 = ft_strjoin(temp, "\"", 1, 1);
                envp_arr[j] = ft_strjoin(envp->var, temp2, 1, 1);
                free(temp);
                free(temp2);
            }
        }
        else
            envp_arr[j] = ft_strjoin(envp->var, "", 1, 1);
        j++;
        envp = envp->next;
    }
    envp_arr[j] = NULL;
    return (envp_arr);
}

int count_args(char **args)
{
    int count;

    count = 0;
    while(args[count] != NULL)
        count++;
    return(count);
}
void print_export_env(char **arr)
{
    int i;

    i = 0;
    while(arr[i] != NULL)
    {
        printf("declare -x ");
        printf("%s\n", arr[i]);
        i++;
    }
}
void ft_print_env2(t_env *envp)
{
    char **env_arr;
    int count;
    int i;
    int j;
    char *temp;
   
    env_arr = convert_envp_to_arr2(envp);
    count = count_args(env_arr);
    i = 0;
    while (i < count)
    {
        j = i;
        while (j > 0 && ft_strcmp(env_arr[j], env_arr[j - 1]) < 0)
        {
            temp = env_arr[j - 1];
            env_arr[j - 1] = env_arr[j];
            env_arr[j] = temp;
            j--;
        }
        i++;
    }
    print_export_env(env_arr);
    ft_free_arr(env_arr);
}


