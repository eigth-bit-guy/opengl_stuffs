#include <ft2build.h>
#include FT_FREETYPE_H
#include <stdio.h>
#include <GL/glew.h>
#include <SDL2/SDL.h>

#include "common/common_shaders.h"

#define SCREEN_WIDTH 350
#define SCREEN_HEIGHT 250

GLuint program;
GLint attribute_coord;
GLint uniform_tex;
GLint uniform_color;

GLuint vbo;

FT_Library ft;
FT_Face face;

int init_ressources(FT_Library ft, FT_Face face)
{
  int error;
  
  if(FT_Init_FreeType(&ft)) {
	fprintf(stderr, "Could not init freetype library\n");
	return 1;
  }

  error = FT_New_Face(ft, "font/FantasqueSansMono-Regular.ttf", 0, &face);
  if(error == FT_Err_Unknown_File_Format){
	fprintf(stderr, "Could not open font\n");
	return 1;
  }

  program = create_program("shaders/text.v.glsl", "shaders/text.f.glsl");
  if(program == 0){
	fprintf(stderr, "Error: when create program\n");
	return 1;
  } 
  attribute_coord = get_attrib(program, "coord");
  uniform_tex = get_uniform(program, "tex");
  uniform_color = get_uniform(program, "color");

  if(attribute_coord == -1 || uniform_tex == -1 || uniform_color == -1)
		return 1;

  glGenBuffers(1, &vbo);
  printf("Testes");
  return 0;
}

void render_text(const char *text, float x, float y, float sx, float sy)
{
  const char *p;
  FT_GlyphSlot g = face->glyph;	

  for(p = text; *p; p++) {
    if(FT_Load_Char(face, *p, FT_LOAD_RENDER))
	  continue;
 
    glTexImage2D(
				 GL_TEXTURE_2D,
				 0,
				 GL_RED,
				 g->bitmap.width,
				 g->bitmap.rows,
				 0,
				 GL_RED,
				 GL_UNSIGNED_BYTE,
				 g->bitmap.buffer
				 );
 
    float x2 = x + g->bitmap_left * sx;
    float y2 = -y - g->bitmap_top * sy;
    float w = g->bitmap.width * sx;
    float h = g->bitmap.rows * sy;
 
    GLfloat box[4][4] = {
	  {x2,     -y2    , 0, 0},
	  {x2 + w, -y2    , 1, 0},
	  {x2,     -y2 - h, 0, 1},
	  {x2 + w, -y2 - h, 1, 1},
    };
 
    glBufferData(GL_ARRAY_BUFFER, sizeof box, box, GL_DYNAMIC_DRAW);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
 
    x += (g->advance.x/64) * sx;
    y += (g->advance.y/64) * sy;
  }

}

void render() {
  glClearColor(1, 1, 1, 1);
  glClear(GL_COLOR_BUFFER_BIT);

  GLfloat black[4] = {0, 0, 0, 1};
  glUniform4fv(uniform_color, 1, black);

  float sx = 2.0 / SCREEN_WIDTH;
  float sy = 2.0 / SCREEN_HEIGHT;

  render_text("The Quick Brown Fox Jumps Over The Lazy Dog",
              -1 + 8 * sx,   1 - 50 * sy,    sx, sy);
  render_text("The Misaligned Fox Jumps Over The Lazy Dog",
              -1 + 8.5 * sx, 1 - 100.5 * sy, sx, sy);
}

int main_loop(SDL_Window *window)
{
  while(1){
	SDL_Event ev;
	while(SDL_PollEvent(&ev)){
	  if(ev.type == SDL_QUIT){
		return 1;
	  }
	}
	render(window);
  }

}

void free_ressources(void)
{
  glDeleteProgram(program);
}

int main(int argc, char *argv[])
{
  SDL_Init(SDL_INIT_VIDEO);
  SDL_Window *window = SDL_CreateWindow("Simple Text Editor",
										SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
									    SCREEN_WIDTH, SCREEN_HEIGHT,
										SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

	if(window == NULL){
	  fprintf(stderr, "Error: when create window: %s\n", SDL_GetError());
	  return 1;
	}

  if(SDL_GL_CreateContext(window) == NULL){
	fprintf(stderr, "Error: when create a context: %s\n", SDL_GetError());
	return 1;
  }
  SDL_GL_SetSwapInterval(0);

  GLenum glew_status = glewInit();
  if (glew_status != GLEW_OK) {
	fprintf(stderr, "Error: glewInit: %s", glewGetErrorString(glew_status));
	return 1;
  }
  if (!GLEW_VERSION_2_0) {
    fprintf(stderr, "Error: your graphic card does not support OpenGL 2.0");
	return 1;
  }


  int ret;
  if(init_ressources(ft, face) != 0){
	fprintf(stderr, "Error: when initialize ressources\n");
	return 1;
  }

  main_loop(window);
  free_ressources();
  
  return 0;
}
