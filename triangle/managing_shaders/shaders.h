#ifndef _shaders_
#define _shaders_

//read shader file
char *file_read(const char *file_name);
//print erros log
void print_log(GLuint object);
//create the shader from the file_read
GLuint create_shader(const char *file_name, GLenum type);

#endif
