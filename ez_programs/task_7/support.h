int open_file(char **name, FILE **f, char mod[]) 
{
    if ((*f=fopen(*name, mod))==NULL) 
    {
	    puts("НЕ удалось открыть фаил!");
	    return 0;
    }
    else 
        return 1;
}

int buffer_size(char **line, int size, int cons) /*  */
{
    *line=realloc(*line, (size+cons)*sizeof(char));
    if(*line == NULL)
    {
    	puts("Нехватка памяти в buffer_size");
    	return 0;
    }
    return 1;
}

int new_buffer_size(char **line, int cons) 
{
    *line=(char*) malloc(cons*sizeof(char));
    if(*line == NULL)
    {
    	puts("Нехватка памяти в new_buffer_size");
    	return 0;
    }
    return 1;
}
