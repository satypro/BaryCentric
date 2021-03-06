// BarycentrixView.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <GL/glut.h>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

struct CSCLCP
{
	float cs;
	float cl;
	float cp;
	int  CLS;
};

vector<CSCLCP> csclcp;

void displayLable(void)
{
	glClearColor(255, 255, 255, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	
	for (int i = 0; i < csclcp.size(); i++)
	{
		glPointSize(3);
		glBegin(GL_POINTS);

		//lets calculate the Barycentric Coordinates
		float x = -1 * csclcp[i].cs + 0 * csclcp[i].cl + 1 * csclcp[i].cp;
		float y = -1 * csclcp[i].cs + 1 * csclcp[i].cl + -1 * csclcp[i].cp;

		if (csclcp[i].CLS == 8) // Tree
			glColor3f(255, 0, 0);
		if (csclcp[i].CLS == 5) // Roof
			glColor3f(0, 255, 0);
		if (csclcp[i].CLS == 2) // Impervious surface
			glColor3f(0, 0, 255);
		if (csclcp[i].CLS == 1) // low vegetation
			glColor3f(0, 255, 255);

		glVertex3f(x, y, 1.0);
		glEnd();
	}

	//[-1,-1], [0,1], [1,-1]
	glLineWidth(1);
	glBegin(GL_LINES);
	glColor3f(0, 0, 0);
	glVertex3f(0, 1, 0);
	glVertex3f(-1, -1, 0);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0, 0, 0);
	glVertex3f(-1, -1, 0);
	glVertex3f(1, -1, 0);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0, 0, 0);
	glVertex3f(0, 1.0, 0.0);
	glVertex3f(1.0, -1.0, 0.0);
	glEnd();


	/*Centroid*/
	glLineWidth(0.1);
	glBegin(GL_LINES);
	glColor3f(0, 0, 0);
	glVertex3f(0, 1, 0);
	glVertex3f(0.0, -0.33, 0.0);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0, 0, 0);
	glVertex3f(-1, -1, 0);
	glVertex3f(0.0, -0.33, 0.0);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0, 0, 0);
	glVertex3f(1, -1, 0.0);
	glVertex3f(0.0, -0.33, 0.0);
	glEnd();

	glFlush();
}

void display(void)
{
	glClearColor(255, 255, 255, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	//[-1,-1], [0,1], [1,-1]
	glLineWidth(1);
	glBegin(GL_LINES);
	glColor3f(0, 0, 0);
	glVertex3f(0, 1, 0);
	glVertex3f(-1, -1, 0);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0, 0, 0);
	glVertex3f(-1, -1, 0);
	glVertex3f(1, -1, 0);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0, 0, 0);
	glVertex3f(0, 1.0, 0.0);
	glVertex3f(1.0, -1.0, 0.0);
	glEnd();

	for (int i = 0; i < csclcp.size(); i++)
	{
		glPointSize(3);
		glBegin(GL_POINTS);

		//lets calculate the Barycentric Coordinates
		float x = -1 * csclcp[i].cs + 0 * csclcp[i].cl + 1 * csclcp[i].cp;
		float y = -1 * csclcp[i].cs + 1 * csclcp[i].cl + -1 * csclcp[i].cp;

		glColor3f(255, 0, 0);

		glVertex3f(x, y, 1.0);
		glEnd();
	}

	/*Centroid*/
	glLineWidth(0.1);
	glBegin(GL_LINES);
	glColor3f(0, 0, 0);
	glVertex3f(0, 1, 0);
	glVertex3f(0.0, -0.33, 0.0);
	glEnd();


	glBegin(GL_LINES);
	glColor3f(0, 0, 0);
	glVertex3f(-1, -1, 0);
	glVertex3f(0.0, -0.33, 0.0);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0, 0, 0);
	glVertex3f(1, -1, 0.0);
	glVertex3f(0.0, -0.33, 0.0);
	glEnd();

	glFlush();
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(400, 400);
	glutCreateWindow("Barycentric View");

	std::ifstream infile("E:\\Research\\Barycentric_Work\\Optimal_Scale_3DVT\\prob_input.txt");
	std::string line;
	float X;
	float Y;
	float Z;
	float Prob0;
	float Prob1;
	float Prob2;
	float cs;
	float cl;
	float cp;
	int PT;
	float Intensity;
	int CLS;
	int count = 1;

	while (true)
	{
		infile>>X>>Y>>Z>>Intensity>>Prob0>>Prob1>>Prob2>>cs>>cl>>cp>>PT>>CLS;

		CSCLCP input;

		// 3dvtget
		input.cs = cp;
		input.cl = cl;
		input.cp = cs;

		//DCM AND 2DEGT
		/*input.cs = cs;
		input.cl = cl;
		input.cp = cp;
		*/

		input.CLS = CLS;

		csclcp.push_back(input);
		//std::cout << count << " " << X << " "<< Y << "  " << Z <<std::endl;
		count++;
		if (infile.eof())
			break;
	}

	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}