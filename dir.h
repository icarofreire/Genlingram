/* lib to dir; */

#include <dirent.h>

char separator()
{
#ifdef _WIN32
    return '\\';
#else
    return '/';
#endif
}

/*\/ obter extensão do arquivo(sem o ponto, ex: "txt"); */
char* get_extension(const char *file){
  char* sh = strchr(file, '.');
  int position = -1;
  if(sh != NULL){
    position = sh - file + 1;

    int len = (strlen(file) - position)+1;
    char* buf = (char*)malloc((len) * sizeof(char));;
    memcpy(buf, file+position, len);
    buf[len] = 0;

    return buf;
  }
  return NULL;
}

int listdir_ext(const char *path, const char *extension, char **point_files, int* len_point_files) 
{
  struct dirent *entry;
  DIR *dp;

  dp = opendir(path);
  if (dp == NULL) 
  {
    perror("opendir");
    return -1;
  }

  int ind = 0;
  while((entry = readdir(dp))){
    char* ext = get_extension(entry->d_name);
    if(ext != NULL && strcmp(ext, extension) == 0){
      point_files[ind] = entry->d_name;
      ind++;
    }
    free(ext);
  }
  *len_point_files = ind;

  closedir(dp);
  return 0;
}

int list_files_project(const char *path, const char *extension) 
{
  struct dirent *entry;
  DIR *dp;

  dp = opendir(path);
  if (dp == NULL) 
  {
    perror("opendir");
    return -1;
  }

  while((entry = readdir(dp))){
    if(entry->d_type == DT_DIR){// << diretório;
        if(strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
        {
          /*\/ concatenar diretório atual, com separador e próximo diretório; */
          char inner_dir[100];
          strcpy(inner_dir, path);
          inner_dir[strlen(path)] = separator();
          strcat(inner_dir, entry->d_name);

          list_files_project(inner_dir, extension);
        }
    }else{
        char* file = entry->d_name;
        printf(">> file: [%s]\n", file);
    }
  }

  closedir(dp);
  return 0;
}

/*\/ obter lista de arquivos de regras; */
char** get_files_rules(char* dir_rules, int* len_array_files){
	int len = 0;
	const int ini_max = 100;
  char** files = (char**)malloc((ini_max) * sizeof(char*));
	listdir_ext(dir_rules, "txt", files, &len);

	*len_array_files = len;

	return files;
}
