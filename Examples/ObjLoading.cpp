#include <iostream>

#include "cSetup.h"
#include "cWindow.h"
#include "cThread.h"
#include "cTexture.h"
#include "sMesh.h"
#include "cCamera.h"
#include "cShader.h"

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

	glEnable(GL_TEXTURE_2D);

	sMesh mesh;
	LoadFromObjectFile(mesh, "hub.obj", "hub.png");

	float* fVertices;

	unsigned int nVerticesSize;
	unsigned int nVerticesCount;

	GenerateBuffers(mesh, fVertices, nVerticesSize, nVerticesCount);

	unsigned int VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, nVerticesSize, fVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glfwSetInputMode(window.GetGLFWwindow(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

	cShader shader("shaders/vert.shader", "shaders/frag.shader");
	shader.Bind();

	glBindTexture(GL_TEXTURE_2D, mesh.nTextureId);
	glBindVertexArray(VAO);

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

		glGetFloatv(GL_MODELVIEW_MATRIX, modelview_matrix);

		glUniformMatrix4fv(
			glGetUniformLocation(shader.GetId(), "view_matrix"),
			1, GL_FALSE, modelview_matrix
		);

		glGetFloatv(GL_PROJECTION_MATRIX, proj_matrix);

		glUniformMatrix4fv(
			glGetUniformLocation(shader.GetId(), "proj_matrix"),
			1, GL_FALSE, proj_matrix
		);

		glDrawArrays(GL_TRIANGLES, 0, nVerticesSize);

		glPopMatrix();

		thread.Refresh(window);
	}

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);

	shader.Unbind();
	shader.Delete();
	shader.Disable();

	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);

	return 0;
}
