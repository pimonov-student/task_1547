#pragma once

#ifndef OBJECTS_H
#define OBJECTS_H

#include <glad/glad.h>

#include <vector>

class Object
{
public:
	~Object();
	virtual void draw() = 0;
protected:
	void init_buffers();

	GLuint vertices_num;
	GLuint indices_num;
	GLfloat* vertices;
	GLuint* indices;

	GLuint VBO;
	GLuint VAO;
	GLuint EBO;
};

class Point : public Object
{
public:
	Point(GLfloat x, GLfloat y);
	void draw() override;
};

class Rectangular : public Object
{
public:
	Rectangular(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2);
	void draw() override;
};

class HLine : public Object
{
public:
	HLine(GLfloat x1, GLfloat x2, GLfloat y);
	void draw() override;
};

class VLine : public Object
{
public:
	VLine(GLfloat y1, GLfloat y2, GLfloat x);
	void draw() override;
};

class Cross : public Object
{
public:
	Cross(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2);
	void draw() override;
};

class Triangle : public Object
{
public:
	Triangle(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat x3, GLfloat y3);
	void draw() override;
};

#endif