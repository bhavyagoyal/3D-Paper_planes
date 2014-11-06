/*
 * first.h
 *
 *  Created on: 5 Aug 2013
 *      Author: shivam
 */


#ifndef FIRST_H_
#define FIRST_H_


#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
//! Texture Class
 /*!
 	This class takes texture map as input and gives loaded texture map as output
 */
class Texture
{
	public:
		const char * pic;						/*!< This field has the filename of the image to be mapped*/
		GLubyte * data;							/*!< This field has the file loaded in the format RGB in a byte array */
		int terrainwidth;						/*<! this field has the texturewidth in pixels*/
		int terrainheight;						/*<! This fiels has the textureheight in pixels */
		GLuint Terrainid;						/*<! this field has the id of the loaded texture which is returned by LoadImage function*/

public:
//! Loads the Texture
	/*!
		This function loads the given image file into texture format into byte array RGB format.

	*/
	GLuint LoadImage();

	Texture(const char * d);
	Texture(void);


};



#endif /* FIRST_H_ */
