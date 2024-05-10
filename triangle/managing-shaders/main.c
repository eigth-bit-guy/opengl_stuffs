#include <stdio.h>
#include <GL/glew.h>
#include <SDL2/SDL.h>

#include "opengl_c.h"

void main_loop(SDL_Window *window)
{
  while(1){
	SDL_Event ev;
	while(SDL_PollEvent(&ev)){
	  if(ev.type == SDL_QUIT)
		return;
	}
	render(window);
  }

}

int main(int argc, char *argv[])
{
  SDL_Init(SDL_INIT_VIDEO);
  SDL_Window *window = SDL_CreateWindow("Triangle",
										 SDL_WINDOWPOS_CENTERED,
										 SDL_WINDOWPOS_CENTERED,
										 500,
										 350,
										 SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
  SDL_GL_CreateContext(window);
  GLenum glew = glewInit();
  if(glew != GLEW_OK){
	fprintf(stderr, "Error: when initialize glew\n", glewGetErrorString(glew));
	return 1;
  }

  if(!init_ressources()){
	fprintf(stderr, "Error: when initialize ressources\n");
	return 1;
  }
  main_loop(window);
  free_ressources();
  printf("Exit...\n");
  return 0;
}
