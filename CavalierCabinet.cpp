#include <GL/glew.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

// window dimentions
int WIDTH = 1024;
int HEIGHT = 768;

enum DisplayType {
    Isometric,
    Military,
    Cavalier,
    Cabinet
};

DisplayType display = Isometric;

void drawUnitCube() {
  glColor3f(0.0f,0.0f,0.0f);
  glBegin(GL_LINE_LOOP);
  glVertex3f(0.0f, 1.0f, 1.0f);
  glVertex3f(0.0f,0.0f, 1.0f);
  glVertex3f( 1.0f,0.0f, 1.0f);
  glVertex3f( 1.0f, 1.0f, 1.0f);
  glEnd();
  glBegin(GL_LINE_LOOP);
  glVertex3f( 1.0f, 1.0f,0.0f);
  glVertex3f( 1.0f,0.0f,0.0f);
  glVertex3f(0.0f,0.0f,0.0f);
  glVertex3f(0.0f, 1.0f,0.0f);
  glEnd();
  glBegin(GL_LINE_LOOP);
  glVertex3f( 1.0f, 1.0f, 1.0f);
  glVertex3f( 1.0f,0.0f, 1.0f);
  glVertex3f( 1.0f,0.0f,0.0f);
  glVertex3f( 1.0f, 1.0f,0.0f);
  glEnd();
  glBegin(GL_LINE_LOOP);
  glVertex3f(0.0f, 1.0f,0.0f);
  glVertex3f(0.0f,0.0f,0.0f);
  glVertex3f(0.0f,0.0f, 1.0f);
  glVertex3f(0.0f, 1.0f, 1.0f);
  glEnd();
  glBegin(GL_LINE_LOOP);
  glVertex3f( 1.0f, 1.0f,0.0f);
  glVertex3f(0.0f, 1.0f,0.0f);
  glVertex3f(0.0f, 1.0f, 1.0f);
  glVertex3f( 1.0f, 1.0f, 1.0f);
  glEnd();
  glBegin(GL_LINE_LOOP);
  glVertex3f( 1.0f, 0.0f, 1.0f);
  glVertex3f(0.0f, 0.0f, 1.0f);
  glVertex3f(0.0f, 0.0f,0.0f);
  glVertex3f( 1.0f, 0.0f,0.0f);
  glEnd();
}

void drawCoordinateAxisZ() {
  glLineWidth(2);
  glBegin(GL_LINES);
  glVertex3f(0.0f, 0.0f, 0.0f); // z-axis
  glVertex3f(0.0f, 0.0f, 2.0f);
  glEnd();
  glLineWidth(1);

  // z-axis tip
  glBegin(GL_TRIANGLES);
  glVertex3f( 0.0f, 0.0f, 2.0f);
  glVertex3f(-0.05f, 0.05f, 1.9f);
  glVertex3f( 0.05f, 0.05f, 1.9f);
  glVertex3f( 0.0f,  0.0f, 2.0f);
  glVertex3f( 0.05f, -0.05f, 1.9f);
  glVertex3f(-0.05f, -0.05f, 1.9f);
  glVertex3f( 0.0f,  0.0f, 2.0f);
  glVertex3f( 0.05f,  0.05f, 1.9f);
  glVertex3f( 0.05f, -0.05f, 1.9f);
  glVertex3f( 0.0f,  0.0f, 2.0f);
  glVertex3f(-0.05f, -0.05f, 1.9f);
  glVertex3f(-0.05f,  0.05f, 1.9f);
  glEnd();
  glBegin(GL_POLYGON);
  glVertex3f( 0.05f, -0.05f, 1.9f);
  glVertex3f( 0.05f,  0.05f, 1.9f);
  glVertex3f(-0.05f,  0.05f, 1.9f);
  glVertex3f(-0.05f, -0.05f, 1.9f);
  glEnd();
}

void drawCoordinateAxisX() {
    glPushMatrix();
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    drawCoordinateAxisZ();
    glPopMatrix();
}

void drawCoordinateAxisY() {
    glPushMatrix();
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    drawCoordinateAxisZ();
    glPopMatrix();
}

/**
 * handleRender
 *  Passes the render event to the engine
 */
void handleRender() {
    // Clear the window with current clearing color
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    float m[16]; // identity
    glGetFloatv(GL_MODELVIEW_MATRIX, m);

    switch(display) {
        
        case Cavalier: {
            float angle = (M_PI / 180.0f) * (-45.0f);
            m[8] = -cos(angle);
            m[9] = sin(angle);

            break;
        }
        case Cabinet: {
            float angle = (M_PI / 180.0f) * (-45.0f);
            m[8] = -cos(angle)/2.0f;
            m[9] = sin(angle)/2.0;

            break;
        }
    }

    glLoadMatrixf(m);


    glColor3f(0.0f, 0.0f, 1.0f);
    drawCoordinateAxisZ();
    glColor3f(0.0f, 1.0f, 0.0f);
    drawCoordinateAxisY();
    glColor3f(1.0f, 0.0f, 0.0f);
    drawCoordinateAxisX();

    drawUnitCube();

    // Do the buffer Swap
    glutSwapBuffers();
    glutReportErrors();
}

/**
 * handleIdle
 *  Passes the idle event to the engine
 */
void handleIdle() {
    glutPostRedisplay();
}

void handleReshape(int width, int height) {
    float aspect = (float) width / (float) height;

    // Start 2d
    glViewport(0, 0, width, height); //set the viewport to the current window specifications
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-5.0 * aspect, 5.0 * aspect, -5.0, 5.0, -10.0f, 1.0f);
}

/**
 * handleKeydown
 *  Passes the key press event to the engine
 */
void mouse(int button, int state, int mousex, int mousey)
{
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {	
		display = Cavalier;
    	glutSetWindowTitle("1*  Cavalier");
	}
    else if(button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)
    {
        display = Cabinet;
        glutSetWindowTitle("2* Cabinet");
    }

    handleRender();
}

/**
 * Main
 */
int main(int argc, char* argv[]) {
	printf("\nYou only have to click in the window\nLeft Click for Cavalier Projection \nRight Click for Cabinet Projection\n");
    // OpenGL Declarations
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("1   Cavalier, 2   Cabinet");

    // Bind the render/idle/reshape events to their handlers
    glutDisplayFunc(handleRender);
    glutIdleFunc(handleIdle);
    glutReshapeFunc(handleReshape);

    // Bind the keybord events to their handlers
    //glutKeyboardFunc(handleKeydown);
    glutMouseFunc(mouse);//keyboard event handler

    // Initialize GLEW
	glewInit();


    // White background
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glShadeModel(GL_SMOOTH);

    glutMainLoop();

    return 0;
}
