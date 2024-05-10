#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include "opengl_c.h"

GLuint program;
GLint attribute_coord2d;

int init_ressources(void)
{
  //provavelemente será deletado
  GLint ok = GL_FALSE;
  GLint link_ok = GL_FALSE;
  GLuint vs = glCreateShader(GL_VERTEX_SHADER);
  const char *vs_source = "#version 120\n"
	"attribute vec2 coord2d;"
    "void main(void)"
	"{"
	"	gl_Position = vec4(coord2d, 0.0, 1.0);"
	"}";

  glShaderSource(vs, 1, &vs_source, NULL);
  glCompileShader(vs);
  glGetShaderiv(vs, GL_COMPILE_STATUS, &ok);
  if(!ok){
	fprintf(stderr, "Error: in vertex shader\n");
	return FALSE;
  }

  GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
  const char *fs_source = "#version 120\n"
	"void main(void){"
	"gl_FragColor[0] = gl_FragCoord.x/640.0;"
    "gl_FragColor[1] = gl_FragCoord.y/480.0;"
    "gl_FragColor[2] = 0.5;"
	"}";
  glShaderSource(fs, 1, &fs_source, NULL);
  glCompileShader(fs);
  glGetShaderiv(fs, GL_COMPILE_STATUS, &ok);
  if(!ok){
	fprintf(stderr, "Error: in fragment shader\n");
	return FALSE;
  }

  program = glCreateProgram();
  glAttachShader(program, vs);
  glAttachShader(program, fs);
  glLinkProgram(program);
  glGetProgramiv(program, GL_LINK_STATUS, &link_ok);
  if(!link_ok){
	fprintf(stderr, "Error: in glLinkProgram\n");
	return FALSE;
  }

  const char *attribute_name = "coord2d";
  attribute_coord2d = glGetAttribLocation(program, attribute_name);
  if(attribute_coord2d == -1){
	fprintf(stderr, "Could not bind attribute\n");
	return FALSE;
  }
  
  return TRUE;
}

void render(SDL_Window *window)
{
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);

  glUseProgram(program);
  glEnableVertexAttribArray(attribute_coord2d);

  GLfloat triangle_vertices[] = {
	0.0, 0.8,
	-0.8, -0.8,
	0.8, -0.8,
  };

  glVertexAttribPointer(
						attribute_coord2d,
						2,
						GL_FLOAT,
						GL_FALSE,
						0,
						triangle_vertices);
  glDrawArrays(GL_TRIANGLES, 0, 3);
  glDisableVertexAttribArray(attribute_coord2d);
  SDL_GL_SwapWindow(window);
  
}

char* file_read(const char* filename) {
	SDL_RWops *rw = SDL_RWFromFile(filename, "rb");
	if (rw == NULL) return NULL;
	
	Sint64 res_size = SDL_RWsize(rw);
	char* res = (char*)malloc(res_size + 1);
	if(res == NULL){
	  fprintf(stderr,"Error: when allocate memory rw buff\n");
	  exit(1);
	}

	Sint64 nb_read_total = 0, nb_read = 1;
	char* buf = res;
	while (nb_read_total < res_size && nb_read != 0) {
		nb_read = SDL_RWread(rw, buf, 1, (res_size - nb_read_total));
		nb_read_total += nb_read;
		buf += nb_read;
	}
	SDL_RWclose(rw);
	if (nb_read_total != res_size) {
		free(res);
		return NULL;
	}
	
	res[nb_read_total] = '\0';
	return res;
}

void print_log(GLuint object)
{
  
}

void free_ressources(void)
{
  glDeleteProgram(program);
}

