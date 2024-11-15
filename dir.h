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

int list_files_recursive(const char *path, const char *extension, char** files, int *indice_file_add) 
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

          list_files_recursive(inner_dir, extension, files, indice_file_add);
        }
    }else{
        char* file = entry->d_name;
        char* ext = get_extension(file);
        if(ext != NULL && strcmp(ext, extension) == 0){

          /*\/ concatenar diretório atual com separador; */
          char *path_file = (char*)malloc((100) * sizeof(char*));
          strcpy(path_file, path);
          path_file[strlen(path)] = separator();
          strcat(path_file, file);

          files[*indice_file_add] = path_file;
          (*indice_file_add)++;
        }
        free(ext);
    }
  }

  closedir(dp);
  return 0;
}

/*\/ obter lista de arquivos de forma recursiva; */
char** get_files_recursive(char* dir, int* len_array_files, const char *extension){
	const int ini_max = 100;
  char** files = (char**)malloc((ini_max) * sizeof(char*));

  int len = 0;
	list_files_recursive(dir, extension, files, &len);

	*len_array_files = len;

	return files;
}
