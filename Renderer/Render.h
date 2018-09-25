#pragma once

#include "GLM/glm.hpp"
#include "Glew/glew.h"

struct  vertex
{
	glm::vec4 pos;
	glm::vec4 norm;
	glm::vec2 uv;
};

struct geometry
{
	GLuint vao, vbo, ibo; //Buffers
	GLuint size;		  //Index count
};

struct shader
{
	GLuint program;
};

struct texture
{
	GLuint handle;
	unsigned int width, height, channels;
};

struct light
{
	glm::vec3 direction;
};
geometry makeGeometry(vertex * verts, size_t vertCount, unsigned int * indices, size_t indexCount);

void freeGeometry(geometry &geo);

shader makeShader(const char * vertSource, const char * fragSource);

void freeShader(shader &shad);

texture loadTex(const char * imagePath);

texture makeTexture(unsigned width, unsigned height, unsigned channel, const unsigned char *pixels);

void freeTexture(texture &tex);

void draw(const shader &shad, const geometry & geo);

void setUniform(const shader &shade,GLuint location,const glm::mat4 &value);
void setUniform(const shader &shad, GLuint locations, const texture &value, GLuint textureSlot);
void setUniform(const shader &shade, GLuint location, const glm::vec3 &value);