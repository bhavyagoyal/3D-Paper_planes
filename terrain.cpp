/*
 * terrain.cpp
 *
 *  Created on: 7 Aug 2013
 *      Author: shivam
 */
#include "terrain.h"
#include "global.h"
#include "first.h"
#include "vec3f.h"

 
typedef float f;
float frustum[6][4];


//double floorsize;
		//!< This field stores the information of the frustum used for culling
//! Extract the frustum
/*!
	This function extracts the equation of frustum in matrix format using projection matrix and modelview matrix
*/
void ExtractFrustum()
{
   float   proj[16];
   float   modl[16];
   float   clip[16];
   float   t;

   /* Get the current PROJECTION matrix from OpenGL */
   glGetFloatv( GL_PROJECTION_MATRIX, proj );

   /* Get the current MODELVIEW matrix from OpenGL */
   glGetFloatv( GL_MODELVIEW_MATRIX, modl );

   /* Combine the two matrices (multiply projection by modelview) */
   clip[ 0] = modl[ 0] * proj[ 0] + modl[ 1] * proj[ 4] + modl[ 2] * proj[ 8] + modl[ 3] * proj[12];
   clip[ 1] = modl[ 0] * proj[ 1] + modl[ 1] * proj[ 5] + modl[ 2] * proj[ 9] + modl[ 3] * proj[13];
   clip[ 2] = modl[ 0] * proj[ 2] + modl[ 1] * proj[ 6] + modl[ 2] * proj[10] + modl[ 3] * proj[14];
   clip[ 3] = modl[ 0] * proj[ 3] + modl[ 1] * proj[ 7] + modl[ 2] * proj[11] + modl[ 3] * proj[15];

   clip[ 4] = modl[ 4] * proj[ 0] + modl[ 5] * proj[ 4] + modl[ 6] * proj[ 8] + modl[ 7] * proj[12];
   clip[ 5] = modl[ 4] * proj[ 1] + modl[ 5] * proj[ 5] + modl[ 6] * proj[ 9] + modl[ 7] * proj[13];
   clip[ 6] = modl[ 4] * proj[ 2] + modl[ 5] * proj[ 6] + modl[ 6] * proj[10] + modl[ 7] * proj[14];
   clip[ 7] = modl[ 4] * proj[ 3] + modl[ 5] * proj[ 7] + modl[ 6] * proj[11] + modl[ 7] * proj[15];

   clip[ 8] = modl[ 8] * proj[ 0] + modl[ 9] * proj[ 4] + modl[10] * proj[ 8] + modl[11] * proj[12];
   clip[ 9] = modl[ 8] * proj[ 1] + modl[ 9] * proj[ 5] + modl[10] * proj[ 9] + modl[11] * proj[13];
   clip[10] = modl[ 8] * proj[ 2] + modl[ 9] * proj[ 6] + modl[10] * proj[10] + modl[11] * proj[14];
   clip[11] = modl[ 8] * proj[ 3] + modl[ 9] * proj[ 7] + modl[10] * proj[11] + modl[11] * proj[15];

   clip[12] = modl[12] * proj[ 0] + modl[13] * proj[ 4] + modl[14] * proj[ 8] + modl[15] * proj[12];
   clip[13] = modl[12] * proj[ 1] + modl[13] * proj[ 5] + modl[14] * proj[ 9] + modl[15] * proj[13];
   clip[14] = modl[12] * proj[ 2] + modl[13] * proj[ 6] + modl[14] * proj[10] + modl[15] * proj[14];
   clip[15] = modl[12] * proj[ 3] + modl[13] * proj[ 7] + modl[14] * proj[11] + modl[15] * proj[15];

   /* Extract the numbers for the RIGHT plane */
   frustum[0][0] = clip[ 3] - clip[ 0];
   frustum[0][1] = clip[ 7] - clip[ 4];
   frustum[0][2] = clip[11] - clip[ 8];
   frustum[0][3] = clip[15] - clip[12];

   /* Normalize the result */
   t = sqrt( frustum[0][0] * frustum[0][0] + frustum[0][1] * frustum[0][1] + frustum[0][2] * frustum[0][2] );
   frustum[0][0] /= t;
   frustum[0][1] /= t;
   frustum[0][2] /= t;
   frustum[0][3] /= t;

   /* Extract the numbers for the LEFT plane */
   frustum[1][0] = clip[ 3] + clip[ 0];
   frustum[1][1] = clip[ 7] + clip[ 4];
   frustum[1][2] = clip[11] + clip[ 8];
   frustum[1][3] = clip[15] + clip[12];

   /* Normalize the result */
   t = sqrt( frustum[1][0] * frustum[1][0] + frustum[1][1] * frustum[1][1] + frustum[1][2] * frustum[1][2] );
   frustum[1][0] /= t;
   frustum[1][1] /= t;
   frustum[1][2] /= t;
   frustum[1][3] /= t;

   /* Extract the BOTTOM plane */
   frustum[2][0] = clip[ 3] + clip[ 1];
   frustum[2][1] = clip[ 7] + clip[ 5];
   frustum[2][2] = clip[11] + clip[ 9];
   frustum[2][3] = clip[15] + clip[13];

   /* Normalize the result */
   t = sqrt( frustum[2][0] * frustum[2][0] + frustum[2][1] * frustum[2][1] + frustum[2][2] * frustum[2][2] );
   frustum[2][0] /= t;
   frustum[2][1] /= t;
   frustum[2][2] /= t;
   frustum[2][3] /= t;

   /* Extract the TOP plane */
   frustum[3][0] = clip[ 3] - clip[ 1];
   frustum[3][1] = clip[ 7] - clip[ 5];
   frustum[3][2] = clip[11] - clip[ 9];
   frustum[3][3] = clip[15] - clip[13];

   /* Normalize the result */
   t = sqrt( frustum[3][0] * frustum[3][0] + frustum[3][1] * frustum[3][1] + frustum[3][2] * frustum[3][2] );
   frustum[3][0] /= t;
   frustum[3][1] /= t;
   frustum[3][2] /= t;
   frustum[3][3] /= t;

   /* Extract the FAR plane */
   frustum[4][0] = clip[ 3] - clip[ 2];
   frustum[4][1] = clip[ 7] - clip[ 6];
   frustum[4][2] = clip[11] - clip[10];
   frustum[4][3] = clip[15] - clip[14];

   /* Normalize the result */
   t = sqrt( frustum[4][0] * frustum[4][0] + frustum[4][1] * frustum[4][1] + frustum[4][2] * frustum[4][2] );
   frustum[4][0] /= t;
   frustum[4][1] /= t;
   frustum[4][2] /= t;
   frustum[4][3] /= t;

   /* Extract the NEAR plane */
   frustum[5][0] = clip[ 3] + clip[ 2];
   frustum[5][1] = clip[ 7] + clip[ 6];
   frustum[5][2] = clip[11] + clip[10];
   frustum[5][3] = clip[15] + clip[14];

   /* Normalize the result */
   t = sqrt( frustum[5][0] * frustum[5][0] + frustum[5][1] * frustum[5][1] + frustum[5][2] * frustum[5][2] );
   frustum[5][0] /= t;
   frustum[5][1] /= t;
   frustum[5][2] /= t;
   frustum[5][3] /= t;
}
//! Tells whether the point is in frustum or not
/*!
	this function checks with all the six planes of the frustum whether point lies inside the frustum or not
	/param x This has value of the x co-ordinate of the point
	/param Y This has value of the y co-ordinate of the point
	/param z This has value of the z co-ordinate of the point


*/
bool PointInFrustum( float x, float y, float z )
{
   int p;

   for( p = 0; p < 6; p++ )
      if( frustum[p][0] * x + frustum[p][1] * y + frustum[p][2] * z + frustum[p][3] <= -60 )
         return false;
   return true;
}

using namespace std;
GLuint terr;																			//!< Stores the display list id of the terrain

//! Reads the heightmap
/*!
		This function reads the texture images specified in the terrain object and reads the heightmap. It fills the texture array with textures
*/


Vec3f retvec(int i,int j,GLubyte* data,int terrainwidth)
{
  return Vec3f(i*SCALE,j*SCALE,data[(j)*terrainwidth*3+i*3+1]*SCALE*HEIGHTSCALE);
}
void terrain :: Read(void){
      SCALE=0.2;
      HEIGHTSCALE=0.1;
 			Texture a(textures);
 			a.Terrainid=a.LoadImage();
 			ad=a;
      FILE * picfile;
      picfile = fopen(heightmap, "rb");
      if (picfile == NULL)
      {
        return ;
      }
      GLubyte * exp=(GLubyte*)malloc(54);
      fread(exp,1,54,picfile);
      terrainwidth=exp[18]+exp[19]*256.0+exp[20]*65536.0;
      terrainheight=exp[22]+exp[23]*256.0+exp[24]*65536.0;
      normals=new normal*[terrainwidth];
      free(exp);
      data = (GLubyte*)malloc(terrainwidth * terrainheight * 3);
      fread(data,1, terrainwidth * terrainheight*3, picfile);
      fclose(picfile);
      Vec3f q,w,e,r;
      normals[0]=new normal[terrainheight];
      normals[terrainwidth-1]=new normal[terrainheight];
      for(int i=1;i<terrainwidth-1;i++)
      {
        normals[i]=new normal[terrainheight];
        for(int j=1;j<terrainheight-1;j++)
        {
            q=q.cross_ter(retvec(i,j,data,terrainwidth)-retvec(i+1,j,data,terrainwidth),retvec(i,j,data,terrainwidth)-retvec(i,j+1,data,terrainwidth));
            w=q.cross_ter(retvec(i,j,data,terrainwidth)-retvec(i,j+1,data,terrainwidth),retvec(i,j,data,terrainwidth)-retvec(i-1,j,data,terrainwidth));
            e=q.cross_ter(retvec(i,j,data,terrainwidth)-retvec(i-1,j,data,terrainwidth),retvec(i,j,data,terrainwidth)-retvec(i,j-1,data,terrainwidth));
            r=q.cross_ter(retvec(i,j,data,terrainwidth)-retvec(i,j-1,data,terrainwidth),retvec(i,j,data,terrainwidth)-retvec(i+1,j,data,terrainwidth));
            if(q.v[2]<0)
              q-=q;
            if(w.v[2]<0)
              w-=w;
            if(e.v[2]<0)
              e-=e;
            if(r.v[2]<0)
              r-=r;
            normals[i][j].x=(q.v[0]+w.v[0]+e.v[0]+r.v[0])/4.0;
            normals[i][j].y=(q.v[1]+w.v[1]+e.v[1]+r.v[1])/4.0;
            normals[i][j].z=(q.v[2]+w.v[2]+e.v[2]+r.v[2])/4.0;

        }
      }
      for(int j=0;j<terrainheight;j++)
      {
        normals[0][j]=normals[1][j];
        normals[terrainwidth-1][j]=normals[terrainwidth-2][j];
      }
      for(int j=0;j<terrainwidth;j++)
      {
        normals[j][0]=normals[j][1];
        normals[j][terrainheight-1]=normals[j][terrainheight-2];
      }



          return;

}

void terrain :: LoadFountain()
{
  Texture a(textures);
  a.Terrainid=a.LoadImageFoun(heightmap);
  ad=a;
}

void terrain :: Render(){

   return Render1(ad);

}

//! renders the terrain
/*!
	This function renders the terrain on the heightmap and applying the textures specified on the scaled heightmap.
	/param Texture a[]  This stores the textures in the an array which are chosen to be applied accordingly
*/

void terrain :: Render1(Texture a)
{
	//ExtractFrustum();
  glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, (ad).Terrainid);
	int w=(ad).terrainwidth;
	int h=(ad).terrainheight;
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

  // glBegin(GL_QUADS);
  // glTexCoord2f(0,0);
  // glNormal3f(0,0,1);
  // glVertex3f(-20,-20,0);
  // glTexCoord2f(0,1);
  // glNormal3f(0,0,1);
  // glVertex3f(-20,20,0);
  // glTexCoord2f(1,1);
  // glNormal3f(0,0,1);
  // glVertex3f(20,20,0);
  // glTexCoord2f(1,0);
  // glNormal3f(0,0,1);
  // glVertex3f(20,-20,0);
  // glEnd();

  for(int j=0;j<terrainwidth-1;j++)
      { int i=0;

        while(i<terrainheight-1)
        {
              

            //if(PointInFrustum(i*SCALE,getHeight(i,j),j*SCALE)){
                
              glBegin(GL_TRIANGLE_STRIP);
                            glTexCoord2f(f(i)/terrainwidth,f(j)/terrainheight);
                            glNormal3f(normals[i][j].x,normals[i][j].y,normals[i][j].z);
                            glVertex3f(i*SCALE,j*SCALE,data[(j)*terrainwidth*3+i*3+1]*SCALE*HEIGHTSCALE);

                            glTexCoord2f(f(i+1.0)/terrainwidth,f(j)/terrainheight);
                            glNormal3f(normals[i+1][j].x,normals[i+1][j].y,normals[i+1][j].z);
                            glVertex3f((i+1)*SCALE,j*SCALE,data[(j)*terrainwidth*3+(i+1)*3+1]*SCALE*HEIGHTSCALE);

                            glNormal3f(normals[i+1][j].x,normals[i+1][j].y,normals[i+1][j].z);
                            glTexCoord2f(f(i)/terrainwidth,f(j+1)/terrainheight);
                            glVertex3f(i*SCALE,(j+1)*SCALE,data[(j+1)*terrainwidth*3+i*3+1]*SCALE*HEIGHTSCALE);

                            glNormal3f(normals[i+1][j+1].x,normals[i+1][j+1].y,normals[i+1][j+1].z);
                            glTexCoord2f(f(i+1)/terrainwidth,f(j+1)/terrainheight);
                            glVertex3f((i+1)*SCALE,(j+1)*SCALE,data[(j+1)*terrainwidth*3+(i+1)*3+1]*SCALE*HEIGHTSCALE);

                     glEnd();//}
                            i++;
              
        }
      }


int j=terrainwidth-1;
       int i=0;

        while(i<terrainheight-1)
        {
              

            //if(PointInFrustum(i*SCALE,getHeight(i,j),j*SCALE)){
                
              glBegin(GL_TRIANGLE_STRIP);
                            glTexCoord2f(f(i)/terrainwidth,f(j)/terrainheight);
                            glNormal3f(normals[i][j-1].x,normals[i][j-1].y,normals[i][j-1].z);
                            glVertex3f(i*SCALE,j*SCALE,data[(j-1)*terrainwidth*3+i*3+1]*SCALE*HEIGHTSCALE);

                            glTexCoord2f(f(i+1.0)/terrainwidth,f(j)/terrainheight);
                            glNormal3f(normals[i+1][j-1].x,normals[i+1][j-1].y,normals[i+1][j-1].z);
                            glVertex3f((i+1)*SCALE,j*SCALE,data[(j)*terrainwidth*3+(i+1)*3+1]*SCALE*HEIGHTSCALE);

                            glNormal3f(normals[i+1][j-1].x,normals[i+1][j-1].y,normals[i+1][j-1].z);
                            glTexCoord2f(f(i)/terrainwidth,f(j+1)/terrainheight);
                            glVertex3f(i*SCALE,(j+1)*SCALE,data[(j)*terrainwidth*3+i*3+1]*SCALE*HEIGHTSCALE);

                            glNormal3f(normals[i+1][j].x,normals[i+1][j].y,normals[i+1][j].z);
                            glTexCoord2f(f(i+1)/terrainwidth,f(j+1)/terrainheight);
                            glVertex3f((i+1)*SCALE,(j+1)*SCALE,data[(j)*terrainwidth*3+(i+1)*3+1]*SCALE*HEIGHTSCALE);

                     glEnd();//}
                            i++;
              
        
      }




//
// double sca=0.25;
// for(int i=0;i<(int)(floorsize/sca);i++)
// {
//   for(int j=0;j<(int)(floorsize)/sca;j++)
//   {
//
//
//     glBegin(GL_QUADS);
//     glTexCoord2f(f(i)*sca/floorsize,f(j)*sca/floorsize);
//     glNormal3f(0.0f,0.0f,1.0f);
//     glVertex3f(-floorsize+2*i*sca,-floorsize+2*j*sca,0);
//     glTexCoord2f(f(i)*sca/floorsize,f(j+1)*sca/floorsize);
//     glNormal3f(0.0f,0.0f,1.0f);
//     glVertex3f(-floorsize+2*i*sca,-floorsize+2*j*sca+2*sca,0);
//     glTexCoord2f(f(i+1)*sca/floorsize,f(j+1)*sca/floorsize);
//     glNormal3f(0.0f,0.0f,1.0f);
//     glVertex3f(-floorsize+2*i*sca+2*sca,-floorsize+2*j*sca+2*sca,0);
//     glTexCoord2f(f(i+1)*sca/floorsize,f(j)*sca/floorsize);
//     glNormal3f(0.0f,0.0f,1.0f);
//     glVertex3f(-floorsize+2*i*sca+2*sca,-floorsize+2*j*sca,0);
//     glEnd();
// }}
//


	glDisable(GL_TEXTURE_2D);
  return ;
	//glFlush();
}


void lp1(Texture a, double b1,double b2,double ht)
{

  //   glEnable(GL_TEXTURE_2D);
  //
  //
  // glBindTexture(GL_TEXTURE_2D, a.Terrainid);
  //   glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
  // gluQuadricTexture(quadlp1,1);
  // gluQuadricTexture(quadlp1s,1);
  // gluSphere(quadlp1s,b1,20,20);
  // gluCylinder(quadlp1,b1,b2,ht,20,100);
  //      glDisable(GL_TEXTURE_2D);
}



GLfloat terrain :: getHeight(int i,int j){
	return (i<=0 or i>=terrainwidth-1 or j>=terrainheight-1 or j<=0)?data[abs(j-1)*terrainwidth*3+(i)*3+1]*SCALE*HEIGHTSCALE:data[(j)*terrainwidth*3+(i)*3+1]*SCALE*HEIGHTSCALE;
}




// terrain :: terrain(char * a)
// {
// 	heightmap=a;
// }


terrain :: terrain(void)
{

}

terrain :: terrain(char *a, char *b)
{
  heightmap=a;
  textures=b;
                      
}