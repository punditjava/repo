
void sort(char *inname, char *outname)
{
    FILE *f;
    char *name=inname, mod[2]="r\0", *line=NULL, **arr_line=NULL;
    int i, c, j, pam=0, cns=255;

    new_buffer_size(&line, cns);

    if (open_file(&name, &f, mod)==1) 
    {
        i=0;   j=0;
        puts("\nФаил перед сортировкой: \n");
        while ((c=getc(f))!=EOF) 
        {
            if (c=='\n') 
            { 
                i++;    
                line[i-1] = '\0';    
                                        
                pam=pam+i;
                
                arr_line=(char**) realloc(arr_line, pam);
                j++;
                arr_line[j-1]=line;    
                
                puts(line);      
                
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
        
        fclose(f);
        
        char *input = outname;
        if (open_file(&input, &f, "w")==1) 
        {
            for (i=0; i<j; i++) {
                fprintf(f, "%s\n", arr_line[i]);
            }
            fclose(f);
        } 
        else puts("Не удалось записать файл\n");
        
        free(arr_line);
        free(line);
    } 
    else puts("Не удалось открыть файл\n");   
} 
