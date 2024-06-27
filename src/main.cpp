#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader/shader.h"
#include "objects/objects.h"
#include "libbitmap.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <filesystem>
#include <windows.h>

namespace fs = std::filesystem;
std::string curr_dir = fs::current_path().string();
GLFWwindow* window;
GLuint w_width = 1600;
GLuint w_height = 900;
GLuint viewport_x1, viewport_y1, viewport_x2, viewport_y2;
GLfloat middle_viewport_x, middle_viewport_y;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}
int init_gl()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(w_width, w_height, "test", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(viewport_x1, viewport_y1, viewport_x2, viewport_y2);

	std::string vPath = curr_dir + "\\bin\\debug\\shaders\\vertex_shader.vs";
	std::string fPath = curr_dir + "\\bin\\debug\\shaders\\fragment_shader.fs";
	Shader program(vPath.c_str(), fPath.c_str());

	processInput(window);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(program.ID);
}
GLfloat clip_x(GLfloat input)
{
	GLfloat output = input > middle_viewport_x ? (input - middle_viewport_x) / (viewport_x2 - middle_viewport_x) : 
												-(middle_viewport_x - input) / (middle_viewport_x - viewport_x1);
	return output;
}
GLfloat clip_y(GLfloat input)
{
	GLfloat output = input > middle_viewport_y ? (input - middle_viewport_y) / (viewport_y2 - middle_viewport_y) : 
												 -(middle_viewport_y - input) / (middle_viewport_y - viewport_y1);
	return output;
}

int main()
{
	std::ifstream fin(curr_dir + "\\bin\\debug\\input.txt");
	if (fin.is_open())
	{
		std::string line;
		std::string curr_command;
		while (std::getline(fin, line))
		{
			std::stringstream s_line(line);
			s_line >> curr_command;

			if (curr_command == "point")
			{
				GLfloat x, y;
				s_line >> x >> y;
				Point point(clip_x(x), clip_y(y));
				point.draw();
			}
			else if (curr_command == "rect")
			{
				GLfloat x1, y1, x2, y2;
				s_line >> x1 >> y1 >> x2 >> y2;
				Rectangular rect(clip_x(x1), clip_y(y1), clip_x(x2), clip_y(y2));
				rect.draw();
			}
			else if (curr_command == "hline")
			{
				GLfloat x1, x2, y;
				s_line >> x1 >> x2 >> y;
				HLine hline(clip_x(x1), clip_x(x2), clip_y(y));
				hline.draw();
			}
			else if (curr_command == "vline")
			{
				GLfloat y1, y2, x;
				s_line >> y1 >> y2 >> x;
				VLine vline(clip_y(y1), clip_y(y2), clip_x(x));
				vline.draw();
			}
			else if (curr_command == "cross")
			{
				GLfloat x1, y1, x2, y2;
				s_line >> x1 >> y1 >> x2 >> y2;
				Cross cross(clip_x(x1), clip_y(y1), clip_x(x2), clip_y(y2));
				cross.draw();
			}
			else if (curr_command == "tri")
			{
				GLfloat x1, y1, x2, y2, x3, y3;
				s_line >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
				Triangle tri(clip_x(x1), clip_y(y1), clip_x(x2), clip_y(y2), clip_x(x3), clip_y(y3));
				tri.draw();
			}
			else
			{
				viewport_x1 = atoi(curr_command.c_str());
				s_line >> viewport_y1 >> viewport_x2 >> viewport_y2;
				middle_viewport_x = (GLfloat(viewport_x1) + viewport_x2) / 2;
				middle_viewport_y = (GLfloat(viewport_y1) + viewport_y2) / 2;
				if (init_gl() == -1)
				{
					return -1;
				}
			}
		}
	}

	Bitmap bmp;
	bmp.m_width = w_width;
	bmp.m_height = w_height;
	bmp.m_buffer = new uint8_t[w_width * w_height * 3];

	uint8_t* tmp_buffer = new uint8_t[w_width * w_height * 3];
	glReadPixels(0, 0, w_width, w_height, GL_BGR, GL_UNSIGNED_BYTE, tmp_buffer);
	for (int i = 0; i < w_height; ++i)
	{
		for (int j = 0; j < w_width * 3; ++j)
		{
			bmp.m_buffer[i * w_width * 3 + j] = tmp_buffer[(w_height - 1 - i) * w_width * 3 + j];
		}
	}
	delete[] tmp_buffer;

	bmp.save("output.bmp");
	
	glfwTerminate();
}