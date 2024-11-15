/* lib to dir; */

#include <dirent.h>

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

int listdir_ext(const char *path, const char *extension) 
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
    // puts(entry->d_name);
    char* ext = get_extension(entry->d_name);
    if(ext != NULL && strcmp(ext, extension) == 0){
      printf("[%s][%s]\n", entry->d_name, ext);
    }
    free(ext);
  }

  closedir(dp);
  return 0;
}