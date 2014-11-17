
#include "obj1.h"
#include "global.h"
#include "terrain.h"
#include "particle.cpp"
#define refreshMills 20

using namespace std;


terrain a("hm1.bmp","tex.bmp"),b("hm1.bmp","tex.bmp"),c("hm1.bmp","tex.bmp"),foun("Palm.bmp","Palm.bmp");
int front=1,viewx,viewy;
bool* keyStates = new bool[256];
GLuint plane,house,tree,star,terrain1,terrain2,terrain3,cube,torus;
double theta,phi,starang=0;;
double x,t1,t2,t3,planex,planez,planey,SCALE,HEIGHTSCALE;
int t1obj=1,t2obj=1,t3obj=1;
ParticleEngine* _particleEngine;GLfloat aspect;

vector<pair<double,double>> trees = {};
vector<pair<double,double>> toruss = {};
vector<pair<double,double>> stars = {};


void keyOperations (void) {
if (keyStates[GLUT_KEY_F5]) {
  x+=10;
  if(x>360)
    x-=360;

}
if(keyStates[GLUT_KEY_F6])
{
	planey+=100*refreshMills/1000.0;
}
if(keyStates[GLUT_KEY_F3])
{

}
}

void keyPressed (int key, int x, int y) {
keyStates[key] = true;
//cout << "x " << x << " y "<< y << endl;
planex+=(x-viewx/2)*2.0/viewx;
planez-=(y-viewy/2)*2.0/viewy;
theta = -(y-viewy/2)*90/viewy;
phi = -(x-viewx/2)*120/viewx;
//cout << planex << " px "<< planez << " pz "<< endl;
if(planex<0)
{
  planex=0;
}
else if(planex > a.terrainwidth*SCALE)
{
  planex=a.terrainwidth*SCALE;
}
if(planez<6)
  planez=6;
else if(planez>20)
  planez=20;
}

void keyUp (int key, int x, int y) {
keyStates[key] = false;
}




void housef()
{
	glPushMatrix();
	glTranslatef(a.terrainheight*SCALE/2.0,a.terrainwidth*SCALE/2.0,10);
   glPushMatrix();
   glRotatef(90,1,0,0);
  	glScalef(5,10,10);
glCallList(house);
glPopMatrix();
     //glutSolidSphere(5.25,20,20);
  	
    glPopMatrix();
}



void planef()
{
  glPushMatrix();

    // glutSolidSphere(2,20,20);
    glScalef(2,2,2);
    glCallList(plane);
    glPopMatrix();
}

void treef(double aa,double bb)
{
	glPushMatrix();
	glTranslatef(aa,bb,10);
  // glPushMatrix();
   glRotatef(90,0,0,1);
  glScalef(5,5,5);
  	glCallList(tree);
    // glPopMatrix();
    // glTranslatef(0,0,1);  
    // glutSolidSphere(3,20,20);
    glPopMatrix();
}


void starf(double aa,double bb){
  glPushMatrix();
  glTranslatef(aa,bb,10);
    // glTranslatef(0,0,4);
    // glPushMatrix();
    glRotatef(starang,0,0,1);
    glRotatef(180,0,1,0); 
    glCallList(star);
    // glPopMatrix();
    // glutSolidSphere(0.8,20,20);
    glPopMatrix();
}


void cubef()
{
	glPushMatrix();
	glTranslatef(a.terrainheight*SCALE/2.0,a.terrainwidth*SCALE/2.0,5);
   glRotatef(90,0,1,0);
  	//glScalef(0.1,0.1,0.1);
  	glCallList(cube);
    glPopMatrix();
}


void torusf(double aa,double bb){
  glPushMatrix();
  glTranslatef(aa,bb,10);
  // glPushMatrix();
   // glRotatef(90,0,0,1);
  glScalef(6,6,6);
    glCallList(torus);
  glPopMatrix();
    // glPopMatrix();
    // glTranslatef(0,0,1);  
    // glutSolidSphere(6,20,20);
    // glPopMatrix();
    // glPopMatrix();

}


bool check(){
  // cout << planex << " px "<< planey<<"py"<<planez << " pz "<< endl;
  // cout<<trees[0].first <<" "<<trees[0].second<<"t"<<endl;
  for(int i=0;i<trees.size();i++){
    if(trees[trees.size()-i-1].second+40<planey){
      // cout<<"hh"<<endl;
      break;
    }
    else{
      // cout<<"here"<<endl;
      // cout<<abs(planey-trees[trees.size()-i-1].second)<<" "<<abs(planex-trees[trees.size()-i-1].second)<< endl;
      if( abs(planey-trees[trees.size()-i-1].second)<4 && abs(planex-trees[trees.size()-i-1].first)<4 && planez<=15 && planez>=7){
        cout<<"treeee"<<endl;
        return true;

      }
    }
  }

 for(int i=0;i<toruss.size();i++){
    if(toruss[toruss.size()-i-1].second+40<planey){
      // cout<<"hh"<<endl;
      break;
    }
    else{
      //cout<<"here"<<endl;
      // cout<<abs(planey-trees[trees.size()-i-1].second)<<" "<<abs(planex-trees[trees.size()-i-1].second)<< endl;
      if( abs(planey-toruss[toruss.size()-i-1].second)<4 && ((planex-toruss[toruss.size()-i-1].first)*(planex-toruss[toruss.size()-i-1].first)+(planez-10)*(planez-10))<=49){
        //cout<<"here2"<<endl;
       if( abs(planey-toruss[toruss.size()-i-1].second)<4 && ((planex-toruss[toruss.size()-i-1].first)*(planex-toruss[toruss.size()-i-1].first)+(planez-10)*(planez-10))>=10){
          cout<<"torus"<<endl;
          return true;
        }
      }
    }
  }



  if(front==1){

    // cout << planex-(a.terrainheight*SCALE/2.0) << " lllll"<< endl;
    // cout << abs(planey-(t1+a.terrainwidth*SCALE/2.0)) << " pppp"<< endl;
    // cout <<  5*abs(planex-(a.terrainheight*SCALE/2.0))+3*abs(planez-10) << " qqqqqqq"<< endl;



    if(t1obj==2){
      //cout<<t1+a.terrainwidth*SCALE/2.0<<endl;
      if(abs(planex-(a.terrainheight*SCALE/2.0))<=3.7 && abs(planez)<10 && ((planey-(t1+a.terrainwidth*SCALE/2.0))<=6.25 && (planey-(t1+a.terrainwidth*SCALE/2.0))>=-15)  ) {
        // cout << planex << " x "<< planey << " y "<< planez << endl;
        // cout << "lower part"<< endl;
        return true;
      }
      else if(5*abs(planex-(a.terrainheight*SCALE/2.0))+3*abs(planez-10)<=18.5 && abs(planez)>10 && planez<=15 && ((planey-(t1+a.terrainwidth*SCALE/2.0))<=6.25 && (planey-(t1+a.terrainwidth*SCALE/2.0))>=-15) )
      { 
        //   cout << planex << " x "<< planey << " y "<< planez << endl;
        // cout << "upper part"<< endl;
          return true;

      }
    }

    else if(t1obj==1)
    {

    }
  }
  else if(front==2){

    // cout << planex-(a.terrainheight*SCALE/2.0) << " lllll"<< endl;
    // cout << abs(planey-(t2+a.terrainwidth*SCALE/2.0)) << " pppp"<< endl;
    // cout <<  5*abs(planex-(a.terrainheight*SCALE/2.0))+3*abs(planez-10) << " qqqqqqq"<< endl;
    if(t2obj==2){
      // cout<<t2+a.terrainwidth*SCALE/2.0<<endl;
      if(abs(planex-(a.terrainheight*SCALE/2.0))<=3.7 && abs(planez)<10 && ((planey-(t2+a.terrainwidth*SCALE/2.0))<=6.25 && (planey-(t2+a.terrainwidth*SCALE/2.0))>=-15)  ) {
        // cout << planex << " x "<< planey << " y "<< planez << endl;
        // cout << "lower part"<< endl;
        return true;
      }
      else if(5*abs(planex-(a.terrainheight*SCALE/2.0))+3*abs(planez-10)<=18.5 && abs(planez)>10 && planez<15 && ((planey-(t2+a.terrainwidth*SCALE/2.0))<=6.25 && (planey-(t2+a.terrainwidth*SCALE/2.0))>=-15) )
      { 
        //   cout << planex << " x "<< planey << " y "<< planez << endl;
        // cout << "upper part"<< endl;
          return true;

      }
    }
  }
  else{

    // cout << planex-(a.terrainheight*SCALE/2.0) << " lllll"<< endl;
    // cout << abs(planey-(t3+a.terrainwidth*SCALE/2.0)) << " pppp"<< endl;
    // cout <<  5*abs(planex-(a.terrainheight*SCALE/2.0))+3*abs(planez-10) << " qqqqqqq"<< endl;
    if(t3obj==2){
      // cout<<t3+a.terrainwidth*SCALE/2.0<<endl;
    if(abs(planex-(a.terrainheight*SCALE/2.0))<=3.7 && abs(planez)<10 && ((planey-(t3+a.terrainwidth*SCALE/2.0))<=6.25 && (planey-(t3+a.terrainwidth*SCALE/2.0))>=-15) ) {
        // cout << planex << " x "<< planey << " y "<< planez << endl;
        // cout << "lower part"<< endl;
        return true;
      }
      else if(5*abs(planex-(a.terrainheight*SCALE/2.0))+3*abs(planez-10)<=18.5 && abs(planez)>10 && planez<15 && ((planey-(t3+a.terrainwidth*SCALE/2.0))<=6.25 && (planey-(t3+a.terrainwidth*SCALE/2.0))>=-15) )
      { 
        //   cout << planex << " x "<< planey << " y "<< planez << endl;
        // cout << "upper part"<< endl;
          return true;

      }
    }
  }

return false;

}


bool check2(){
  for(int i=0;i<stars.size();i++){
    if(stars[stars.size()-i-1].second+40<planey){
      // cout<<"hh"<<endl;
      break;
    }
    else{
      // cout<<"here"<<endl;
      // cout<<abs(planey-trees[trees.size()-i-1].second)<<" "<<abs(planex-trees[trees.size()-i-1].second)<< endl;
      if( abs(planey-stars[stars.size()-i-1].second)<=2 && ((planex-stars[stars.size()-i-1].first)*(planex-stars[stars.size()-i-1].first)+(planez-10)*(planez-10))<=4){
        cout<<"star"<<endl;
        return true;

      }
    }
  }
}




/*********************************DISPLAY*********************************/

void display(void)
{

  // cout<<a.terrainheight*SCALE/2.0<<" "<<a.terrainwidth*SCALE/2.0<<endl;
   random_device rd;
   mt19937 gen(rd());
   uniform_int_distribution<> dis(0, 2);
   

   	keyOperations();
   	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   	glMatrixMode(GL_PROJECTION);
	  glLoadIdentity();
	  gluPerspective(60.0f, aspect, 0.05f, 1000.0f);
   	glMatrixMode(GL_MODELVIEW);
   	glLoadIdentity();
    gluLookAt(a.terrainheight*SCALE/2.0,-20+planey,15,a.terrainheight*SCALE/2.0,planey,10,0,0,1);
   

    glPushMatrix();
    glTranslatef(0,t1,0);
    glPushMatrix();
    glTranslatef(0,0,5);
    glCallList(terrain1);
    glPopMatrix();
    if(t1obj==0)
   		{
      //housef();
        glTranslatef(a.terrainheight*SCALE/2.0,a.terrainwidth*SCALE/2.0,5);
        glScalef(20.0f, 20.0f, 20.0f);
        glRotatef(90,1,0,0);
        _particleEngine->draw();
      }
   	
   	else
   		housef();
   	glPopMatrix();
    
   
    glPushMatrix();
    glTranslatef(0,t2,0);
    glPushMatrix();
    glTranslatef(0,0,5);
    glCallList(terrain2);
    glPopMatrix();
    
	 if(t2obj==0)
   		{
      //housef();
        glTranslatef(a.terrainheight*SCALE/2.0,a.terrainwidth*SCALE/2.0,5);
        glScalef(20.0f, 20.0f, 20.0f);
        glRotatef(90,1,0,0);
        _particleEngine->draw();
      }
   
   	else
   		housef();
   	glPopMatrix();

    glPushMatrix();
    glTranslatef(0,t3,0);
    glPushMatrix();
    glTranslatef(0,0,5);
   	glCallList(terrain3);
   	glPopMatrix();
   	if(t3obj==0)
   		{
      //housef();
        glTranslatef(a.terrainheight*SCALE/2.0,a.terrainwidth*SCALE/2.0,5);
        glScalef(20.0f, 20.0f, 20.0f);
        glRotatef(90,1,0,0);
        _particleEngine->draw();
      }
   	else if(t3obj==1)
   		toruss.push_back(make_pair(a.terrainheight*SCALE/2.0,t3+a.terrainwidth*SCALE/2.0));
   	else
   		housef();
   	glPopMatrix();


    for(int i=0;i<trees.size();i++){
      if(trees[trees.size()-i-1].second+50<planey){
        break;
      }
      else{
        treef(trees[trees.size()-i-1].first,trees[trees.size()-i-1].second);
      }
    }

    for(int i=0;i<toruss.size();i++){
      if(toruss[toruss.size()-i-1].second+50<planey){
        break;
      }
      else{
        torusf(toruss[toruss.size()-i-1].first,toruss[toruss.size()-i-1].second);
      }
    }

    for(int i=0;i<stars.size();i++){
      if(stars[stars.size()-i-1].second+50<planey){
        break;
      }
      else{
        starf(stars[stars.size()-i-1].first,stars[stars.size()-i-1].second);
      }
    }




	
  if(front==1 && planey>(t1+(a.terrainwidth)*SCALE)+10)
  {
    front=2;
    t1+=(a.terrainwidth+b.terrainwidth+c.terrainwidth)*SCALE;
    t1obj=dis(gen);t1obj%=2;
    int y=dis(gen);
    int z=dis(gen);
    if(y%3==0)
    {
      if(z%4==0)
        trees.push_back(make_pair(a.terrainwidth*SCALE/2.0,t1+a.terrainheight*SCALE/2.0-15));
      else if(z%4==1)
        trees.push_back(make_pair(a.terrainwidth*SCALE/2.0,t1+a.terrainheight*SCALE/2.0+15));
      else if(z%4==2)
        trees.push_back(make_pair(a.terrainwidth*SCALE/2.0-7,t1+a.terrainheight*SCALE/2.0));
      else
        tress.push_back(make_pair(a.terrainwidth*SCALE/2.0+7,t1+a.terrainheight*SCALE/2.0));
    }
    else if(y%3==1 && t1obj!=0)
     {

      if(z%4==0)
        toruss.push_back(make_pair(a.terrainwidth*SCALE/2.0,t1+a.terrainheight*SCALE/2.0-15));
      else if(z%4==1)
        toruss.push_back(make_pair(a.terrainwidth*SCALE/2.0,t1+a.terrainheight*SCALE/2.0+15));
      else if(z%4==2)
        toruss.push_back(make_pair(a.terrainwidth*SCALE/2.0-7,t1+a.terrainheight*SCALE/2.0));
      else
        toruss.push_back(make_pair(a.terrainwidth*SCALE/2.0+7,t1+a.terrainheight*SCALE/2.0));
    
     } 
   
  }
  else if(front==2 && planey>(t2+(b.terrainwidth)*SCALE)+10)
  {
    front=3;
    t2+=(a.terrainwidth+b.terrainwidth+c.terrainwidth)*SCALE;
    t2obj=dis(gen);t2obj%=2;
    int y=dis(gen);
    
      trees.push_back(make_pair(a.terrainwidth*SCALE/2.0+6,t2+a.terrainheight*SCALE/2.0+15));
    
  }
  else if(front==3 && planey>(t3+(c.terrainwidth)*SCALE+10))
  {
    front=1;
    t3+=(a.terrainwidth+b.terrainwidth+c.terrainwidth)*SCALE;
    t3obj=dis(gen);t3obj%=2;
    int y=dis(gen);
    trees.push_back(make_pair(a.terrainwidth*SCALE/2.0+6,t3+a.terrainheight*SCALE/2.0+15));
    
  }
	// cout << "t1 "<<t1 << " t2 "<< t2 << " t3 "<< t3 << endl;
 //  cout<<a.terrainheight*SCALE<<endl;
	// cout << "planey "<<planey << endl;
	/***********************************************************PHYSICS *******************************************************/
	// cout << planex << " px "<< planez << " pz "<< endl;
	glPushMatrix();
	glTranslatef(planex,planey,planez);
    glRotatef(90,1,0,0);
   	glRotatef(theta,1,0,0);
   	glRotatef(phi,0,1,0);
    // glutSolidSphere(0.3f,10,10);
   planef();
   	glPopMatrix();

    //glutSolidSphere(20,20,20);
    if(check()){
      cout<<"hit"<<endl;
    }

    if(check2()){
      cout<<"bonus"<<endl;
    }


   glFlush ();
   glutSwapBuffers();
}

/********************************INIT***************************************/



void init()
{

   for(int i=0;i<256;i++)
   	keyStates[i]=false;
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_BLEND);
   glShadeModel (GL_SMOOTH);
   glEnable(GL_LIGHTING);
   glEnable(GL_NORMALIZE);
    glClearColor (0.4, 0.4,1.0, 1.0);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   Objectrender dirtbike("plane-fd.obj","wall.bmp");
   Objectrender hous("House.obj","wall.bmp");
   Objectrender tre("Palm.obj","Palm.bmp");
   Objectrender cub("cube.obj","cube.bmp");
   Objectrender sta("star.obj","cube.bmp");
   Objectrender toru("toru.obj","ball.bmp");
   cerr << "error crossed"<< endl;
   a.Read();
   b.Read();
   c.Read();
   foun.LoadFountain();

   _particleEngine=new ParticleEngine(foun.ad.Terrainid);
   
   x=0;t1=0;t2=(a.terrainwidth)*SCALE;t3=t2+(b.terrainwidth)*SCALE;planey=0;
   trees.push_back(make_pair(a.terrainheight*SCALE/2.0 + 7,t1+(a.terrainwidth)*SCALE/2.0));
   trees.push_back(make_pair(a.terrainheight*SCALE/2.0 - 7,t1+(a.terrainwidth)*SCALE/2.0));
   trees.push_back(make_pair(a.terrainheight*SCALE/2.0 + 7,t2+(a.terrainwidth)*SCALE/2.0));
   trees.push_back(make_pair(a.terrainheight*SCALE/2.0 - 7,t2+(a.terrainwidth)*SCALE/2.0));

   // toruss.push_back(make_pair(a.terrainheight*SCALE/2.0 ,t1+(a.terrainwidth)*SCALE/2.0));
   // toruss.push_back(make_pair(a.terrainheight*SCALE/2.0 ,t1+(a.terrainwidth)*SCALE/2.0));

   // toruss.push_back(make_pair(a.terrainheight*SCALE/2.0 ,t2+(a.terrainwidth)*SCALE/2.0));
   // toruss.push_back(make_pair(a.terrainheight*SCALE/2.0 ,t2+(a.terrainwidth)*SCALE/2.0));


   stars.push_back(make_pair(a.terrainheight*SCALE/2.0 ,t1+(a.terrainwidth)*SCALE/2.0));
   // toruss.push_back(make_pair(a.terrainheight*SCALE/2.0 ,t1+(a.terrainwidth)*SCALE/2.0));


   planex=a.terrainwidth*SCALE/2.0;
   planez=10.0;
   
   plane = glGenLists(1);
   glNewList(plane, GL_COMPILE);
   dirtbike.Render();
   glEndList();
   
   house=glGenLists(10);
   glNewList(house,GL_COMPILE);
   hous.Render();
   glEndList();
   
   tree=glGenLists(3);
   glNewList(tree,GL_COMPILE);
   tre.Render();
   glEndList();

   star=glGenLists(5);
   glNewList(star,GL_COMPILE);
   sta.Render();
   glEndList();

   
   cube=glGenLists(4);
   glNewList(cube,GL_COMPILE);
   cub.Render();
   glEndList();


   torus=glGenLists(6);
   glNewList(torus,GL_COMPILE);
   toru.Render();
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
   _particleEngine->advance(TIMER_MS / 1000.0f);
   starang+=5;
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
