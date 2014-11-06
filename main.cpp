
#include "obj1.h"
#include "global.h"
#include "terrain.h"
#define refreshMills 10

using namespace std;


terrain a;
bool* keyStates = new bool[256];
GLuint object1;
Objectrender dirtbike("quad.obj","ball.bmp");
double x;
void keyOperations (void) {
if (keyStates[GLUT_KEY_F5]) {
  x+=10;
  if(x>360)
    x-=360;

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
   glRotatef(x,0,0,1);
   dirtbike.Render();
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
   a.textures="ball.bmp";
   x=0;
   a.Read();
   // 	object1 = glGenLists(1);
		//  		glNewList(object1, GL_COMPILE);
		//  		   dirtbike.Render();
		//  		   glEndList();
    GLfloat mat_specular[] = { 1, 1,1, 1};


 GLfloat light_position[] = { 0, 40, 0.0, 1.0 };
 glLightfv(GL_LIGHT0,GL_DIFFUSE,mat_specular);
  // glLightfv(GL_LIGHT0,GL_DIFFUSE,mat_shininess);
   	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
     glEnable(GL_LIGHT0);
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
