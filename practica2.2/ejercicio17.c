#include <stdio.h>
#include <string.h>
#include <dirent.h> 
#include <stdlib.h>
#include <fcntl.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>



int main(int argc, char ** argv) {

    struct dirent *dp;
    struct stat file_info;
    ssize_t r;
    char buf[50];
    int blocks;



    if(argc != 2){
        fprintf(stderr,"Usage: ./ejercicio17 <dirname>\n",argv[0]);
        return -1;
    }
    
    char * dirname;
    dirname = malloc(strlen(argv[1])+1);
    dirname = argv[1];

    DIR *dir = opendir(dirname);

    while ((dp = readdir(dir)) != NULL)
	{
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
        {
			
            if (dp->d_type == DT_REG) {
                printf("%s* \n",dp->d_name);
            }
            else if (dp->d_type == DT_DIR) {
                printf("%s/ \n",dp->d_name);
                }
            else if (dp->d_type == DT_LNK) {
                int rl = readlink(dp->d_name, buf, sizeof(buf));
                if (rl == -1)
                    perror("Error al leer el enlace");
                else{
                    buf[sizeof(buf)] = '\0';
                    printf("%s -> %s\n", dp->d_name, buf);
                } 
                }

			//blocks += file_info.st_blocks;
           // printf("%ldK      %s\n",file_info.st_blocks/2,dp->d_name);

           // get_size_dir(path,blocks);
        }
    }
    closedir(dir);



    return 0;
   
}

