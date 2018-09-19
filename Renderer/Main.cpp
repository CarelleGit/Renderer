#include "Context.h"
#include "Render.h"
#include "GLM/ext.hpp"

int main()
{
	context game;
	game.init(800, 600, "CrashingVS");

	vertex triVerts[] = 
	{
		{{-.5f, -.5f, 0, 1}, {0,  0}},
		{{ .5f, -.5f, 0, 1}, {0,  1}},
		{{   0,  .5f, 0, 1}, {0.5,1}}
	};
	unsigned int triIndices[] = { 2,1,0 };
	
	geometry triangle = makeGeometry(triVerts, 3, triIndices, 3);

	const char * basicVert = "#version 410\n"
		"layout(location = 0) in vec4 position;\n"
		"void main() {gl_Position = position;}";

	const char * mvpVert = "#version 430\n"
		"layout (location = 0) in vec4 position;\n"
		"layout (location = 1) in vec2 uv;\n"
		"out vec2 vUV;\n"
		"layout (location = 0) uniform mat4 proj;\n"
		"layout (location = 1) uniform mat4 view;\n"
		"layout (location = 2) uniform mat4 model;\n"
		"void main() {gl_Position = proj * view * model * position; vUV = uv;}";


	const char * basicFrag = "#version 330\n"
		"out vec4 vertColor;\n"
		"void main() {vertColor = vec4(1.0, 0.0, 0.0, 1.0);}";

	const char * texFrag = "#version 430\n"
		"in vec2 vUV;\n"
		"out vec4 vertColor;\n"
		"layout(location = 3) uniform sampler2D albedo;\n"
		"void main() {vertColor = texture(albedo, vUV); }";

	shader basicShade = makeShader(basicVert, basicFrag);
	shader mvpShader = makeShader(mvpVert, basicFrag);
	shader texShader = makeShader(mvpVert, texFrag);
	unsigned char whitePix[] = { 255, 255, 255 };
	texture whiteTex = makeTexture(1, 1, 3, whitePix);

	glm::mat4 cam_proj = glm::perspective(glm::radians(45.f), 800.0f / 600.0f, 0.1f,1000.0f);
	glm::mat4 cam_view = glm::lookAt(glm::vec3(0, 0, -2), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	glm::mat4 triangle_model = glm::identity<glm::mat4>();

	while (true)
	{
		game.tick();
		game.clear();

		triangle_model = glm::rotate(triangle_model, glm::radians(15.f), glm::vec3(0, 1, 0));

		setUniform(texShader, 0, cam_proj);
		setUniform(texShader, 1, cam_view);
		setUniform(texShader, 2, triangle_model);
		setUniform(texShader, 3, whiteTex, 0);

		draw(texShader, triangle);
	}

	game.term();
	return 0;
}