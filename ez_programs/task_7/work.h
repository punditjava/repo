
size_t check_comment(char *line)
{
    char *p = line;
    char flag = -1;
    for(; *line; ++line)
    {
    	if(*line == '\"')
    		flag = -flag;
        if(*line == '/' && *(line + 1) == '/' && flag == -1)
        {
            return line - p;
        }
    }
    return 0;
}

int delete_komments(FILE *file, char **inname)
{
    int c, i, j, flag =0, pam =0, label = 0, cns=255;
    char *line=NULL, **arr_line=NULL;
    char lol[2];
    new_buffer_size(&line, cns);

    i=0;j=0;
    puts("\nИзначальный файл:\n");
    while ((c=getc(file))!=EOF) 
    {
        if (c=='\n') 
        { 
            i++;    
            line[i-1] = '\0';

            puts(line);

            int size = check_comment(line);
            if(size != 0)
            {
                line[size] ='\0';
                flag++;
            }     
            pam=pam+i;
               
            arr_line=(char**) realloc(arr_line, pam);
            j++;
            arr_line[j-1]=line;         
               
            line=NULL;
            new_buffer_size(&line, cns);
            i=0; 
        } 
        else 
        {
            i++;
            if ((i % cns)==0) 
            {                 
               buffer_size(&line, i, cns);
            }
            line[i-1] = c;       
        }
    }
    fclose(file);

    if(flag == 0)
    {
    	puts("\nКомментариев нет!");
    }
    else
    {
    	open_file(inname, &file, "w");

    	for (i=0; i<j; i++) 
    	{
        	fprintf(file, "%s\n", arr_line[i]);
    	}
    	puts("\nКомментарии удалены успешно!");
    }	
    return 0;
}

int delete(char *inname)
{
    
    FILE *f;
    char mod[2]="r+", *name = inname;

    if (open_file(&name, &f, mod)==1) 
    {
        delete_komments(f, &name);
        fclose(f);
        return 1;
    }   
    return 0;
}