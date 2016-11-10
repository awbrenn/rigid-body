//
// Created by awbrenn on 10/18/16.
//
#define GL_GLEXT_PROTOTYPES 1

#include "Shader.h"

Shader::Shader(char *frag, char *vert, char *diffuse_texture) {
  program = loadShaders(frag, vert, diffuse_texture);
}

void load_diffuse_texture(char *filename) {
  FILE *fptr;
  char buf[512], *parse;
  int im_size, im_width, im_height, max_color;
  unsigned char *texture_bytes;

  fptr=fopen(filename,"r");
  fgets(buf,512,fptr);
  do{
    fgets(buf,512,fptr);
  } while(buf[0]=='#');
  parse = (char *)strtok(buf," \t");
  im_width = atoi(parse);

  parse = (char *)strtok(NULL," \n");
  im_height = atoi(parse);

  fgets(buf,512,fptr);
  parse = (char *)strtok(buf," \n");
  max_color = atoi(parse);

  im_size = im_width*im_height;
  texture_bytes = (unsigned char *)calloc(3,im_size);
  fread(texture_bytes,3,im_size,fptr);
  fclose(fptr);


  glBindTexture(GL_TEXTURE_2D,0);
  glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,im_width,im_height,0,GL_RGB,
               GL_UNSIGNED_BYTE,texture_bytes);
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
  glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
  free(texture_bytes);
}

char* Shader::readShaderProgram(char *filename) {
  FILE *fp;
  char *content = NULL;
  int fd, count;
  fd = open(filename,O_RDONLY);
  count = lseek(fd,0,SEEK_END);
  close(fd);
  content = (char *)calloc(1,(count+1));
  fp = fopen(filename,"r");
  count = fread(content,sizeof(char),count,fp);
  content[count] = '\0';
  fclose(fp);
  return content;
}

void Shader::setUniformParameter(unsigned int p, char* varName, unsigned int value) {
  int location = glGetUniformLocation(p, varName);
  glUniform1i(location, value);
}

unsigned int Shader::loadShaders(char *frag, char *vert, char *diffuse_texture) {
  char *vs, *fs;
  GLuint v, f, p;

  v = glCreateShader(GL_VERTEX_SHADER);
  f = glCreateShader(GL_FRAGMENT_SHADER);

  vs = readShaderProgram(vert);
  fs = readShaderProgram(frag);

  glShaderSource(v,1,(const char **)&vs,NULL);
  glShaderSource(f,1,(const char **)&fs,NULL);

  free(vs);
  free(fs);

  glCompileShader(v);
  glCompileShader(f);

  // print out any erros with shaders
  GLsizei lengthf;
  GLchar infologf[10000];
  glGetShaderInfoLog(f, 10000, &lengthf, infologf);
  std::cout << "Frag shader compilation: " << lengthf << "\n" << infologf << std::endl;

  GLsizei lengthv;
  GLchar infologv[10000];
  glGetShaderInfoLog(v, 10000, &lengthv, infologv);
  std::cout << "Vert shader compilation: " << lengthv << "\n" << infologv << std::endl;

  p = glCreateProgram();
  if (p == 0) { std::cerr << "Failed to create program" << std::endl; exit(EXIT_FAILURE); }
  glAttachShader(p,f);
  glAttachShader(p,v);
  glLinkProgram(p);

  // print out errors with linking
  GLint link_status;
  glGetProgramiv(p, GL_LINK_STATUS, &link_status);
  if (link_status == GL_FALSE) {
      GLsizei length;
      GLchar infolog[10000];
      glGetProgramInfoLog(p, 10000, &length, infolog);
      std::cout << "Failed to link program: " << length << "\n" << infolog << std::endl;
      exit(EXIT_FAILURE);
  }

  load_diffuse_texture(diffuse_texture);

  glUseProgram(p);
  setUniformParameter(p, (char *) "myDiffuse", 0);
//  setUniformParameter(p, (char *) "myNormal", 1);
//  setUniformParameter(p, (char *) "mySpecular", 2);
//  setUniformParameter(p, (char *) "myShadow", 3);
  glUseProgram(0);
  return p;
}