#include <stdio.h>
#include <GL/glew.h>
#include <SDL2/SDL.h>


char *file_read(const char *file_name)
{
  Sint64 res_size, nb_read_total, nb_read;

  SDL_RWops *rw = SDL_RWFromFile(file_name, "rb");
  if(rw == NULL) return NULL;

  res_size = SDL_RWsize(rw);
  char* res = (char*)malloc(res_size + 1);

  nb_read_total = 0;
  nb_read = 1;
  char* buf = res;
  while(nb_read_total < res_size && nb_read != 0){
	nb_read = SDL_RWread(rw, buf, 1, (res_size - nb_read_total));
	nb_read_total += nb_read;
	buf += nb_read;
  }
  SDL_RWclose(rw);
  if(nb_read_total != res_size){
	free(res);
	return NULL;
  }
  res[nb_read_total] = '\0';
  return res;
}


void print_log(GLuint object)
{
  GLiny log_length = 0;
  if(glIsShader(object)){
	glGetShaderiv(object, GL_INFO_LENGTH, &log_length);
  }else if(glIsProgram(object)){
	glGetProgramiv(object, GL_INFO_LOG_LENGTH, &log_length);
  }else{
	fprintf(stderr, "printLog: Not a shader or a program\n");
	return;
  }

  char *log = (char*)malloc(log_length);
  if(glIsShader(object)){
	glGetShaderInfoLog(object, log_length, NULL, log);
  }else if(glIsProgram(object)){
	glGetProgramInfoLog(object, log_length, NULL, log);
  }
  fprintf(stderr, log);
  free(log);
}

//GLSL version
GLuint create_shader(const char *file_name, GLenum type)
{
  const GLchar *source = file_read(file_name);
  if(source == NULL){
	fprintf(stderr, "Error opening: %s\n", file_name);
	return 0;
  }
  GLuint res = glCreateShader(type);
  const char *sources[] =
	{#ifdef GL_ES_VERSION_2_0
	 "#version 100\n"
    #else
	 "#version 120\n"
    #endif
	 ,
	 source};
  glShaderSource(res, 2, sourcesm NULL);
  free((void*)source);

  glCompileShader(res);
  GLint compile_ok = GL_FALSE;
  glGetShaderiv(res, GL_COMPILE_STATUS, &compile_ok);
  if(compile_ok == GL_FALSE){
	fprintf(stderr, file_name);
	print_log(res);
	glDeleteShader(res);
	return 0;
  }
  return res;
}
