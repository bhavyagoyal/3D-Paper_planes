
#include "obj1.h"
#include "global.h"
#include "terrain.h"
#define refreshMills 10

using namespace std;


terrain a("hm1.bmp","tex.bmp"),b("hm1.bmp","tex.bmp"),c("hm1.bmp","tex.bmp");
int front=1,viewx,viewy;
bool* keyStates = new bool[256];
GLuint object1,object2,terrain1,terrain2,terrain3;
double theta,phi;
double x,t1,t2,t3,planex,planez,planey,SCALE,HEIGHTSCALE;
GLfloat aspect;
void keyOperations (void) {
if (keyStates[GLUT_KEY_F5]) {
  x+=10;
  if(x>360)
    x-=360;

}
if(keyStates[GLUT_KEY_F6])
{
	planey+=10;
}
if(keyStates[GLUT_KEY_F3])
{

}
}

void keyPressed (int key, int x, int y) {
keyStates[key] = true;
cout << "x " << x << " y "<< y << endl;
planex+=(x-viewx/2)*2.0/viewx;
planez-=(y-viewy/2)*2.0/viewy;
theta = -(y-viewy/2)*90/viewy;
phi = -(x-viewx/2)*120/viewx;
cout << planex << " px "<< planez << " pz "<< endl;
if(planex<0)
{
  planex=0;
}
else if(planex > a.terrainwidth*SCALE)
{
  planex=a.terrainwidth*SCALE;
}
if(planez<0)
  planez=0;
else if(planez>20)
  planez=20;
}

void keyUp (int key, int x, int y) {
keyStates[key] = false;
}




void mod1()
{

}








/*********************************DISPLAY*********************************/

void display(void)
{
   


   	keyOperations();
   	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, aspect, 0.05f, 1000.0f);
   	glMatrixMode(GL_MODELVIEW);
   	glLoadIdentity();
    gluLookAt(a.terrainheight*SCALE/2.0,-20+planey,10,a.terrainheight*SCALE/2.0,planey,10,0,0,1);
   

    glPushMatrix();
    glTranslatef(0,t1,0);
    glCallList(terrain1);
   
    glTranslatef(a.terrainheight*SCALE/2.0,a.terrainwidth*SCALE/2.0,5);
    glRotatef(90,1,0,0);
  	glScalef(25,25,25);
  	glCallList(object2);
    glPopMatrix();
   
    glPushMatrix();
    glTranslatef(0,t2,0);
    glCallList(terrain2);
    
    glTranslatef(a.terrainheight*SCALE/2.0,a.terrainwidth*SCALE/2.0,5);
    glRotatef(90,1,0,0);
  	glScalef(25,25,25);
  	glCallList(object2);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0,t3,0);
   	glCallList(terrain3);
   	
   	glTranslatef(a.terrainheight*SCALE/2.0,a.terrainwidth*SCALE/2.0,5);
    glRotatef(90,1,0,0);
  	glScalef(25,25,25);
  	glCallList(object2);
   	glPopMatrix();


	if(front==1 && planey>(t1+(a.terrainwidth)*SCALE)+10)
	{
		front=2;
		t1+=(a.terrainwidth+b.terrainwidth+c.terrainwidth)*SCALE;
	}
	else if(front==2 && planey>(t2+(b.terrainwidth)*SCALE)+10)
	{
		front=3;
		t2+=(a.terrainwidth+b.terrainwidth+c.terrainwidth)*SCALE;
	}
	else if(front==3 && planey>(t3+(c.terrainwidth)*SCALE+10))
	{
		front=1;
		t3+=(a.terrainwidth+b.terrainwidth+c.terrainwidth)*SCALE;
	}
	cout << "t1 "<<t1 << " t2 "<< t2 << " t3 "<< t3 << endl;
	cout << "planey "<<planey << endl;
	
	cout << planex << " px "<< planez << " pz "<< endl;
	glPushMatrix();
	glTranslatef(planex,planey,planez);
    glRotatef(90,1,0,0);
   	glRotatef(theta,1,0,0);
   	glRotatef(phi,0,1,0);
   	glCallList(object1);
   	glPopMatrix();
	
	
   glFlush ();
   glutSwapBuffers();
}

/********************************INIT***************************************/



void init()
{

   for(int i=0;i<256;i++)
   	keyStates[i]=false;
   glClearColor (0.4, 0.4,1.0, 1.0);
   glShadeModel (GL_SMOOTH);
   glEnable(GL_LIGHTING);
   glEnable(GL_NORMALIZE);
   glEnable(GL_DEPTH_TEST);
   //a.textures="ball.bmp";
   // b.textures="wall.bmp";
   // c.textures="tex.bmp";
   
   Objectrender dirtbike("plane-fd.obj","wall.bmp");
   Objectrender house("House.obj","wall.bmp");
   cerr << "error crossed"<< endl;
   a.Read();
   b.Read();
   c.Read();
   x=0;t1=0;t2=(a.terrainwidth)*SCALE;t3=t2+(b.terrainwidth)*SCALE;planey=0;
   planex=a.terrainwidth*SCALE/2.0;
   planez=10.0;
   object1 = glGenLists(1);
   glNewList(object1, GL_COMPILE);
   glScalef(3,3,3);
   dirtbike.Render();
   glEndList();
   object2=glGenLists(10);
   glNewList(object2,GL_COMPILE);
   house.Render();
   glEndList();
   terrain1 = glGenLists(12);
   glNewList(terrain1, GL_COMPILE);
   a.Render();
   glEndList();
   terrain2 = glGenLists(2);
   glNewList(terrain2, GL_COMPILE);
   b.Render();
   glEndList();
   terrain3 = glGenLists(23);
   glNewList(terrain3, GL_COMPILE);
   c.Render();
   glEndList();
   
   GLfloat mat_specular[] = { 1, 1,1, 1};

   theta =0;
   phi=0;
 GLfloat light_position[] = { 100, 100, 100.0, 1.0 };
 glLightfv(GL_LIGHT0,GL_DIFFUSE,mat_specular);
  // glLightfv(GL_LIGHT0,GL_DIFFUSE,mat_shininess);
   	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
     glEnable(GL_LIGHT0);
}




void reshape (int w, int h)
{
   if (h == 0) h = 1;                // To prevent divide by 0
   aspect = (GLfloat)w / (GLfloat)h;
   viewx=w;
   viewy=h;
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
   //cerr<< "init "<< endl;
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
