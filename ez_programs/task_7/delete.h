
size_t check_comment(char *line)
{
    char *p = line;
    char flag = -1;
    for(; *line; ++line)
    {
    	if(*line == '\"')
        {
    		flag = -flag;
        }
        if(*line == '/' && *(line + 1) == '/' && flag == -1)
        {
            return line - p;
        }
    }
    return -1;
}

int delete_sort(FILE *file, char **inname,char **outname)
{
    int c, i, j, flag =0, pam =0, cns=255;
    char *line=NULL, **arr_line=NULL;

    if(new_buffer_size(&line, cns) == 0)
    {
        exit(0);
    }

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
            if(size != -1)
            {
                line[size] ='\0';
                flag++;
            }     
            pam=pam + i + 3;
               
            
            arr_line=(char**) realloc(arr_line, pam);
            if(arr_line == NULL)
            {
                puts("Нехватка памяти!");
                exit(1);
            }
            j++;
            arr_line[j-1]=line;         
               
            line=NULL;
            if(new_buffer_size(&line, cns) == 0)
            {
                exit(1);
            }
            i=0; 
        } 
        else 
        {
            i++;
            if ((i % cns)==0) 
            {                 
               if(buffer_size(&line, i, cns) == 0)
               {
                    exit(1);
               }
            }
            line[i-1] = c;       
        }
    }
    free(line);
    fclose(file);

    if(flag == 0)
    {
        puts("\nКомментариев нет!");
    }
    else
    {
        puts("\nКомментарии удалены успешно!\n");
        for (i=0; i<j; i++) 
        {
            puts(arr_line[i]);
        }
    }

    for (i=0; i<j-1; i++) 
    {
        pam=i;
        for (c=i+1; c<j; c++) 
        {                 
            cns=strcmp(arr_line[pam], arr_line[c]);
            if (cns>0) 
            { 
                pam=c; cns=arr_line[c][0]; 
            }
        }
            
        if (pam!=0) 
        {
            line=arr_line[pam]; 
            arr_line[pam]=arr_line[i];
            arr_line[i]=line;
        }
            
    }

    puts("\nСортировка строк в алфавитном порядке: \n");
    for (i=0; i<j; i++) 
    {
        puts(arr_line[i]);
    }
      
  
    if (open_file(outname, &file, "w")==1) 
    {
        for (i=0; i<j; i++) {
            fprintf(file, "%s\n", arr_line[i]);
        }
        fclose(file);
    } 
    else puts("Не удалось записать файл\n");
       
    for (i = 0; i < j - 2; ++i)
    {
        free(arr_line[i]);
    }
    free(arr_line[j - 1]);
    free(arr_line);
    free(line);	
    return 0;
}

int delete(char *inname, char *outname)
{
    
    FILE *f;
    char mod[2]="r+";

    if (open_file(&inname, &f, mod)==1) 
    {
        delete_sort(f, &inname, &outname);
       
        return 1;
    }   
    return 0;
}