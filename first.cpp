
#include "first.h"
#include <GL/glu.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <cmath>

using namespace std;


Texture :: Texture(const char * a){
	pic=a;
}
Texture :: Texture()
{

}

GLuint Texture ::  LoadImage()
{
		GLuint g;
		FILE * picfile;
		picfile = fopen(pic, "rb");
		if (picfile == NULL)
		{	printf("NOT FOUND\n");
			return 0;
		}
		GLubyte * exp=(GLubyte*)malloc(54);
		fread(exp,1,54,picfile);
		terrainwidth=exp[18]+exp[19]*256.0+exp[20]*65536.0;
		terrainheight=exp[22]+exp[23]*256.0+exp[24]*65536.0;
		free(exp);

		data = (GLubyte*)malloc(terrainwidth * terrainheight * 3);
		fread(data,1, terrainwidth * terrainheight*3, picfile);
		fclose(picfile);

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	  glGenTextures(1, &g);
		glBindTexture(GL_TEXTURE_2D, g);
		for(int i=0;i<terrainwidth*terrainheight*3;i+=3){
			GLubyte temp;
			temp=data[i+2];
			data[i+2]=data[i];
			data[i]=temp;
		}
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, terrainwidth, terrainheight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		free(data);
		return g;
}


GLuint Texture :: LoadImageFoun(char * alpha)
{		
		//rgbdatat being read
		FILE * picfile,* alphafile;
		picfile = fopen(pic, "rb");
		if (picfile == NULL)
		{	printf("NOT FOUND\n");
			return 0;
		}
		GLubyte * exp=(GLubyte*)malloc(54);
		fread(exp,1,54,picfile);
		int RGBcompwidth=exp[18]+exp[19]*256.0+exp[20]*65536.0;
		int RGBcompheight=exp[22]+exp[23]*256.0+exp[24]*65536.0;
		free(exp);

		GLubyte * rgbdata = (GLubyte*)malloc(RGBcompwidth * RGBcompheight * 3);
		fread(rgbdata,1,RGBcompwidth * RGBcompheight * 3, picfile);
		fclose(picfile);

		//alpha value file being read
		alphafile=fopen(alpha,"rb");
		if(alphafile==NULL)
		{
			printf("NOT FOUND\n");
			return 0;
		}
		GLubyte * exp1=(GLubyte*)malloc(54);
		fread(exp1,1,54,alphafile);
		int alphacompwidth=exp[18]+exp[19]*256.0+exp[20]*65536.0;
		int alphacompheight=exp[22]+exp[23]*256.0+exp[24]*65536.0;
		free(exp1);
		GLubyte * data1=(GLubyte*)malloc(alphacompheight*alphacompwidth*3);
		fread(data1,1,alphacompwidth*alphacompheight*3,alphafile);
		fclose(alphafile);

		GLubyte *rgbadata=(GLubyte*)malloc(RGBcompwidth*RGBcompheight*4);
		for(int i=0;i<RGBcompheight;i++)
			{
				for(int j=0;j<RGBcompwidth;j++)
					{
						for(int k=0;k<3;k++)
						{
							rgbadata[4*RGBcompwidth*i+4*j+k]=rgbdata[3*RGBcompwidth*i+3*j+k];
						}	
							GLubyte tmp=rgbadata[4*RGBcompwidth*i+4*j];
							rgbadata[4*RGBcompwidth*i+4*j]=rgbadata[4*RGBcompwidth*i+4*j+2];
							rgbadata[4*RGBcompwidth*i+4*j+2]=tmp;
						rgbadata[4*RGBcompwidth*i+4*j+3]=data1[3*RGBcompwidth*i+3*j];
					}
			}

		GLuint g;
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	  	glGenTextures(1, &g);
		glBindTexture(GL_TEXTURE_2D, g);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, RGBcompwidth, RGBcompheight, 0, GL_RGBA, GL_UNSIGNED_BYTE, rgbadata);
		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		free(rgbdata);
		free(data1);
		free(rgbadata);
		return g;
				





}