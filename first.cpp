
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
			temp=data[i+1];
			data[i+1]=data[i];
			data[i]=temp;
		}
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, terrainwidth, terrainheight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//	free(data);
		return g;
}
