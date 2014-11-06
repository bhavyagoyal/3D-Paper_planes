

#include "global.h"
#include "terrain.h"
#define refreshMills 10

using namespace std;


terrain a;
bool* keyStates = new bool[256];

void keyOperations (void) {
if (keyStates[GLUT_KEY_F5]) {

}
}

void keyPressed (int key, int x, int y) {
keyStates[key] = true;
}

void keyUp (int key, int x, int y) {
keyStates[key] = false;
}
/*********************************DISPLAY*********************************/

void display(void)
{
   keyOperations();
   glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
    gluLookAt(0,-40,20,0,0,0,0,0,1);
   a.Render();
   glFlush ();
   glutSwapBuffers();
}

/********************************INIT***************************************/



void init()
{

   glClearColor (1.0, 1.0,1.0, 1.0);
   glShadeModel (GL_SMOOTH);
   glEnable(GL_LIGHTING);
   glEnable(GL_NORMALIZE);
   glEnable(GL_DEPTH_TEST);
   a.textures="t.bmp";
   a.Read();
}




void reshape (int w, int h)
{
   if (h == 0) h = 1;                // To prevent divide by 0
   GLfloat aspect = (GLfloat)w / (GLfloat)h;
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(60.0f, aspect, 0.05f, 1000.0f);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

void timer(int value) {
   glutPostRedisplay();      // Post re-paint request to activate display()
   glutTimerFunc(refreshMills, timer, 0); // next timer call milliseconds later
}



int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize (500, 500);
   glutInitWindowPosition (100, 100);
   glutCreateWindow("Paper Planes");
   init ();
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutSpecialFunc(keyPressed);
   glutSpecialUpFunc(keyUp);
   glutTimerFunc(refreshMills,timer,0);
   glutPostRedisplay();
   glutMainLoop();
   return 0;
}
