#include <stdio.h>
#include <GL/glew.h>
#include <SDL2/SDL.h>

#define TRUE 1
#define FALSE 0

GLuint program;
GLint attribute_coord2d;

int init_ressources(void)
{
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

void free_ressources()
{
  glDeleteProgram(program);
}

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

int main(int argc, char *argv)
{
  SDL_Init(SDL_INIT_VIDEO);
  SDL_Window *window = SDL_CreateWindow("Triangle",
										 SDL_WINDOWPOS_CENTERED,
										 SDL_WINDOWPOS_CENTERED,
										 540,
										 380,
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
