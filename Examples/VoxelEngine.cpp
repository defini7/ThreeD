#include <iostream>

#include "cSetup.h"
#include "cWindow.h"
#include "cThread.h"
#include "cTexture.h"
#include "sMesh.h"
#include "cCamera.h"
#include "cShader.h"
#include "cPerlinNoise.h"

int main()
{
	cSetup setup;

	if (setup.GetErrCode() == 0)
	{
		std::cout << setup.GetErrMessage() << std::endl;
		return 1;
	}

	cWindow window(1280, 960, "Hello, World!", true);

	if (!window.Construct())
	{
		std::cout << window.GetErrMessage() << std::endl;
		return 1;
	}

	cTexture image_loader;
	
	if (image_loader.LoadData("icon.png"))
	{
		window.SetIcon(
			image_loader.GetData(),
			image_loader.GetWidth(),
			image_loader.GetHeight()
		);
	}
	else
	{
		std::cout << "Can't set icon" << std::endl;
		return 1;
	}

	cThread thread;
	cCamera camera;
	cTexture grass;
	cTexture cobble;
	cPerlinNoise noise;

	noise.SetWidth(16);
	noise.SetHeight(16);

	noise.Prepare();
	noise.Generate();

	camera.fVerticalSpeed = 25.0f;
	camera.fHorizontalSpeed = 0.1f;

	if (!grass.LoadData("gfx/grass.png", true))
	{
		std::cout << grass.GetErrMessage() << std::endl;
		return false;
	}

	if (!grass.LoadTexture())
	{
		std::cout << grass.GetErrMessage() << std::endl;
		return false;
	}

	if (!cobble.LoadData("gfx/cobble.png", true))
	{
		std::cout << cobble.GetErrMessage() << std::endl;
		return false;
	}

	if (!cobble.LoadTexture())
	{
		std::cout << cobble.GetErrMessage() << std::endl;
		return false;
	}

	float fVertices[] =
	{
		// left
		0.0f, 1.0f, -1.0f, 0.0f, 0.3333333f,
		0.0f, 0.0f, -1.0f, 0.0f, 0.6666666f,
		0.0f, 1.0f, 0.0f, 0.25f, 0.3333333f,
		0.0f, 1.0f, 0.0f, 0.25f, 0.3333333f,
		0.0f, 0.0f, 0.0f, 0.25f, 0.6666666f,
		0.0f, 0.0f, -1.0f, 0.0f, 0.6666666f,

		// top
		0.0f, 0.0f, 0.0f, 0.25f, 0.6666666f,
		0.0f, 1.0f, 0.0f, 0.25f, 0.3333333f,
		1.0f, 1.0f, 0.0f, 0.50f, 0.3333333f,
		0.0f, 0.0f, 0.0f, 0.25f, 0.6666666f,
		1.0f, 0.0f, 0.0f, 0.50f, 0.6666666f,
		1.0f, 1.0f, 0.0f, 0.50f, 0.3333333f,

		// back
		0.0f, 1.0f, 0.0f, 0.25f, 0.3333333f,
		0.0f, 1.0f, -1.0f, 0.25f, 0.0f,
		1.0f, 1.0f, -1.0f, 0.50f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.25f, 0.3333333f,
		1.0f, 1.0f, 0.0f, 0.50f, 0.3333333f,
		1.0f, 1.0f, -1.0f, 0.50f, 0.0f,

		// front
		0.0f, 0.0f, -1.0f, 0.25f, 1.0f,
		0.0f, 0.0f, 0.0f, 0.25f, 0.6666666f,
		1.0f, 0.0f, 0.0f, 0.50f, 0.6666666f,
		0.0f, 0.0f, -1.0f, 0.25f, 1.0f,
		1.0f, 0.0f, -1.0f, 0.50f, 1.0f,
		1.0f, 0.0f, 0.0f, 0.50f, 0.6666666f,

		// right
		1.0f, 1.0f, -1.0f, 0.75f, 0.3333333f,
		1.0f, 1.0f, 0.0f, 0.50f, 0.3333333f,
		1.0f, 0.0f, 0.0f, 0.50f, 0.6666666f,
		1.0f, 0.0f, 0.0f, 0.50f, 0.6666666f,
		1.0f, 0.0f, -1.0f, 0.75f, 0.6666666f,
		1.0f, 1.0f, -1.0f, 0.75f, 0.3333333f,

		// bottom
		0.0f, 1.0f, -1.0f, 1.0f, 0.3333333f,
		0.0f, 0.0f, -1.0f, 1.0f, 0.6666666f,
		1.0f, 0.0f, -1.0f, 0.75f, 0.6666666f,
		0.0f, 1.0f, -1.0f, 1.0f, 0.3333333f,
		1.0f, 1.0f, -1.0f, 0.75f, 0.3333333f,
		1.0f, 0.0f, -1.0f, 0.75f, 0.6666666f,
	};

	unsigned int VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(fVertices), fVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_TEXTURE_2D);

	glfwSetInputMode(window.GetGLFWwindow(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

	cShader shader("shaders/vert.shader", "shaders/frag.shader");
	shader.Bind();

	GLfloat modelview_matrix[16];
	GLfloat proj_matrix[16];

	while (thread.Run(window))
	{
		/* OpenGL code goes here */

		camera.Apply(window, thread);
		
		glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glPushMatrix();

		camera.Rotate();
		camera.Translate();

		auto draw_cube = [&](float x, float y, float z)
		{
			glTranslatef(x, y, z);

			glGetFloatv(GL_MODELVIEW_MATRIX, modelview_matrix);
			shader.UniformMatrix4f("u_view_matrix", modelview_matrix);

			glGetFloatv(GL_PROJECTION_MATRIX, proj_matrix);
			shader.UniformMatrix4f("u_proj_matrix", proj_matrix);

			glBindVertexArray(VAO);
			glDrawArrays(GL_TRIANGLES, 0, sizeof(fVertices));

			glTranslatef(-x, -y, -z);
		};

		for (int x = 0; x < noise.GetWidth(); x++)
			for (int y = 0; y < noise.GetHeight(); y++)
			{
				float z = float(int(noise.GetValue(x, y) * 8.0f));

				float fDistance = (camera.vPos - vf3d(x, y, z)).length();

				if (fDistance < 10.0f)
				{
					glBindTexture(GL_TEXTURE_2D, grass.GetId());
					draw_cube(x, y, z);

					glBindTexture(GL_TEXTURE_2D, cobble.GetId());

					for (int i = -10; i < z; i++)
						draw_cube(x, y, i);

					glBindTexture(GL_TEXTURE_2D, 0);
				}
			}
		
		glBindTexture(GL_TEXTURE_2D, 0);

		glPopMatrix();

		thread.Refresh(window);
	}

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);

	shader.Unbind();
	shader.Disable();

	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);

	return 0;
}
