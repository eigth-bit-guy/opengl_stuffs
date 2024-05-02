#include <stdio.h>
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include "shaders.h"

int render(SDL_Window *window)
{
  

  return 0;
}

int main_loop(SDL_Window *window)
{
  while(1){
	SDL_PollEvent ev;
	while(SDL_PollEvent(&ev)){
	  if(ev.type == SDL_QUIT)
		return;
	}
	render(window);
  }

  return 0;
}

void free_ressources()
{
  glDeleteProgram(program);
}


int main(int argc, char *argv[])
{
  SDL_Init(SDL_INIT_VIDEO);
  SDL_Window *window = SDL_CreateWindow("Managing Shaders",
										SDL_WINDOWPOS_CENTERED,
										SDL_WINDOWPOS_CENTERED,
										340,
										180,
										SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
  SDL_GL_CreateContext(window);
  GLenum glew = glewInit();
  if(glew != GLEW_OK){
	fprintf(stderr, "Error: when initialize glew\n", glewGetErrorString(glew));
	return 1;
  }

  main_loop(window);
  free_ressources();
  
  return 0;
}
