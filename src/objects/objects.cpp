#include "objects.h"

Object::~Object()
{
	delete[] vertices;
	delete[] indices;
}
void Object::init_buffers()
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices_num, vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_num, indices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

Point::Point(GLfloat x, GLfloat y)
{
	vertices_num = 3 * sizeof(GLfloat);
	indices_num = 1 * sizeof(GLuint);
	vertices = new GLfloat[3]{
		x, y, 0.0f
	};
	indices = new GLuint[1]{
		0
	};

	init_buffers();
}
void Point::draw()
{
	glBindVertexArray(VAO);
	glDrawElements(GL_POINTS, 1, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

Rectangular::Rectangular(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2)
{
	vertices_num = 12 * sizeof(GLfloat);
	indices_num = 6 * sizeof(GLuint);
	vertices = new GLfloat[12]{
		x1, y1, 0.0f,
		x1, y2, 0.0f,
		x2, y2, 0.0f,
		x2, y1, 0.0f
	};
	indices = new GLuint[6]{
		0, 1, 2,
		0, 2, 3
	};

	init_buffers();
}
void Rectangular::draw()
{
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

HLine::HLine(GLfloat x1, GLfloat x2, GLfloat y)
{
	vertices_num = 6 * sizeof(GLfloat);
	indices_num = 2 * sizeof(GLuint);
	vertices = new GLfloat[6]{
		x1, y, 0.0f,
		x2, y, 0.0f,
	};
	indices = new GLuint[2]{
		0, 1
	};

	init_buffers();
}
void HLine::draw()
{
	glBindVertexArray(VAO);
	glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

VLine::VLine(GLfloat y1, GLfloat y2, GLfloat x)
{
	vertices_num = 6 * sizeof(GLfloat);
	indices_num = 2 * sizeof(GLuint);
	vertices = new GLfloat[6]{
		x, y1, 0.0f,
		x, y2, 0.0f,
	};
	indices = new GLuint[2]{
		0, 1
	};

	init_buffers();
}
void VLine::draw()
{
	glBindVertexArray(VAO);
	glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

Cross::Cross(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2)
{
	vertices_num = 12 * sizeof(GLfloat);
	indices_num = 4 * sizeof(GLuint);
	vertices = new GLfloat[12]{
		x1, y1, 0.0f,
		x1, y2, 0.0f,
		x2, y2, 0.0f,
		x2, y1, 0.0f
	};
	indices = new GLuint[4]{
		0, 2,
		1, 3
	};

	init_buffers();
}
void Cross::draw()
{
	glBindVertexArray(VAO);
	glDrawElements(GL_LINES, 4, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

Triangle::Triangle(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat x3, GLfloat y3)
{
	vertices_num = 9 * sizeof(GLfloat);
	indices_num = 3 * sizeof(GLuint);
	vertices = new GLfloat[9]{
		x1, y1, 0.0f,
		x2, y2, 0.0f,
		x3, y3, 0.0f
	};
	indices = new GLuint[3]{
		0, 1, 2
	};

	init_buffers();
}
void Triangle::draw()
{
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}