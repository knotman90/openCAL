#include "life.h"
#include <stdio.h>
#include <stdlib.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <time.h>


void display(void)
{
	CALint i, j, state;
	CALreal color;
	CALbyte b;

	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();

	glTranslatef(-life.model->columns / 2.0f, life.model->rows / 2.0f, 0);
	glScalef(1, -1, 1);

	for (i = 0; i < life.model->rows; i++)
		for (j = 0; j < life.model->columns; j++)
		{
			state = calGet2Di(life.model, life.Q, i, j);
			if (state == STATE_ALIVE)
			{
				color = 1;
				glColor3f(color, color, color);
				glRecti(j, i, j + 1, i + 1);
			}
		}

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glColor3d(0, 1, 0);
	glRectd(0, 0, life.model->columns, life.model->rows);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glPopMatrix();

	glutSwapBuffers();
}

void simulationRun(void)
{
	CALbyte again;

	//simulation main loop
	life.run->step++;

	//exectutes the global transition function
	//the steering function and check for the stop condition
	again = calRunCAStep2D(life.run);

	//graphic rendering
	printf("step: %d\r", life.run->step);
	fflush(stdout);
	glutPostRedisplay();

	//check for the stop condition
	if (!again)
	{
		//breaking the simulation
		glutIdleFunc(NULL);
		printf("\nSimulation terminated\n");
		fflush(stdout);

		//graphic rendering
		glutPostRedisplay();
		return;
	}
}

void init(void)
{
	glClearColor(0.0, 0.0, 1.0, 0.0);
	glShadeModel(GL_FLAT);

	printf("The Conway's Game of Life model\n");
	printf("Left click on the graphic window to start the simulation\n");
	printf("Right click on the graphic window to stop the simulation\n");
}

void reshape(int w, int h)
{
	GLfloat aspect, dim;

	glViewport(0, 0, (GLsizei)w, (GLsizei)h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	(ROWS > COLS) ? (dim = ROWS*0.5f) : (dim = COLS*0.5f);
	
	aspect = (GLfloat)w / (GLfloat)h;
	if (w <= h)
		glOrtho(-dim, dim, -dim / aspect, dim / aspect, 1.0, -1.0);
	else
		glOrtho(-dim*aspect, dim*aspect, -dim, dim, 1.0, -1.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void mouse(int button, int state, int x, int y)
{
	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN)
			glutIdleFunc(simulationRun);
		break;
	case GLUT_MIDDLE_BUTTON:
	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN)
			glutIdleFunc(NULL);
		break;
	default:
		break;
	}
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		exit(0);
	default:
		break;
	}
}

int main(int argc, char** argv)
{
	CADef(&life);
	Init(&life);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutMainLoop();

	isoExit(&life);

	return 0;
}
