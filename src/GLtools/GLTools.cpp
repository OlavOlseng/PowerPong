/*
 *  gltools.cpp
 *
 *  Created by Richard Wright on 10/16/06.
 *  OpenGL SuperBible, 5th Edition
 *
 */
/* Copyright (c) 2005-2010, Richard S. Wright Jr.
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, 
are permitted provided that the following conditions are met:

Redistributions of source code must retain the above copyright notice, this list 
of conditions and the following disclaimer.

Redistributions in binary form must reproduce the above copyright notice, this list 
of conditions and the following disclaimer in the documentation and/or other 
materials provided with the distribution.

Neither the name of Richard S. Wright Jr. nor the names of other contributors may be used 
to endorse or promote products derived from this software without specific prior 
written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY 
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES 
OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT 
SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, 
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED 
TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR 
BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN 
ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "GLTools.h"
#include "math3d.h"
#include "GLTriangleBatch.h"
#include <stdio.h>
#include <assert.h>
#include <stdarg.h>

#ifdef linux
#include <cstdlib> 
#endif
#ifdef __APPLE__
#include <unistd.h>
#endif

///////////////////////////////////////////////////////////////////////////////
// Get the OpenGL version number
void gltGetOpenGLVersion(GLint &nMajor, GLint &nMinor)
	{
    #ifndef OPENGL_ES       
    glGetIntegerv(GL_MAJOR_VERSION, &nMajor);
    glGetIntegerv(GL_MINOR_VERSION, &nMinor);
    #else
    const char *szVersionString = (const char *)glGetString(GL_VERSION);
    if(szVersionString == NULL)
        {
        nMajor = 0;
        nMinor = 0;
        return;
        }
    
    // Get major version number. This stops at the first non numeric character
    nMajor = atoi(szVersionString);
    
    // Get minor version number. Start past the first ".", atoi terminates on first non numeric char.
    nMinor = atoi(strstr(szVersionString, ".")+1);
	#endif
	}


// Draw a torus (doughnut)  at z = fZVal... torus is in xy plane
void gltMakeTorus(GLTriangleBatch& torusBatch, GLfloat majorRadius, GLfloat minorRadius, GLint numMajor, GLint numMinor)
	{
    double majorStep = 2.0f*M3D_PI / numMajor;
    double minorStep = 2.0f*M3D_PI / numMinor;
    int i, j;
	
    torusBatch.BeginMesh(numMajor * (numMinor+1) * 6);
    for (i=0; i<numMajor; ++i) 
		{
		double a0 = i * majorStep;
		double a1 = a0 + majorStep;
		GLfloat x0 = (GLfloat) cos(a0);
		GLfloat y0 = (GLfloat) sin(a0);
		GLfloat x1 = (GLfloat) cos(a1);
		GLfloat y1 = (GLfloat) sin(a1);

		M3DVector3f vVertex[4];
		M3DVector3f vNormal[4];
		M3DVector2f vTexture[4];
		
		for (j=0; j<=numMinor; ++j) 
			{
			double b = j * minorStep;
			GLfloat c = (GLfloat) cos(b);
			GLfloat r = minorRadius * c + majorRadius;
			GLfloat z = minorRadius * (GLfloat) sin(b);
			
			// First point
			vTexture[0][0] = (float)(i)/(float)(numMajor);
			vTexture[0][1] = (float)(j)/(float)(numMinor);
			vNormal[0][0] = x0*c;
			vNormal[0][1] = y0*c;
			vNormal[0][2] = z/minorRadius;
			m3dNormalizeVector3(vNormal[0]);
			vVertex[0][0] = x0 * r;
			vVertex[0][1] = y0 * r;
			vVertex[0][2] = z;
			
			// Second point
			vTexture[1][0] = (float)(i+1)/(float)(numMajor);
			vTexture[1][1] = (float)(j)/(float)(numMinor);
			vNormal[1][0] = x1*c;
			vNormal[1][1] = y1*c;
			vNormal[1][2] = z/minorRadius;
			m3dNormalizeVector3(vNormal[1]);
			vVertex[1][0] = x1*r;
			vVertex[1][1] = y1*r;
			vVertex[1][2] = z;

			// Next one over
			b = (j+1) * minorStep;
			c = (GLfloat) cos(b);
			r = minorRadius * c + majorRadius;
			z = minorRadius * (GLfloat) sin(b);
						
			// Third (based on first)
			vTexture[2][0] = (float)(i)/(float)(numMajor);
			vTexture[2][1] = (float)(j+1)/(float)(numMinor);
			vNormal[2][0] = x0*c;
			vNormal[2][1] = y0*c;
			vNormal[2][2] = z/minorRadius;
			m3dNormalizeVector3(vNormal[2]);
			vVertex[2][0] = x0 * r;
			vVertex[2][1] = y0 * r;
			vVertex[2][2] = z;
			
			// Fourth (based on second)
			vTexture[3][0] = (float)(i+1)/(float)(numMajor);
			vTexture[3][1] = (float)(j+1)/(float)(numMinor);
			vNormal[3][0] = x1*c;
			vNormal[3][1] = y1*c;
			vNormal[3][2] = z/minorRadius;
			m3dNormalizeVector3(vNormal[3]);
			vVertex[3][0] = x1*r;
			vVertex[3][1] = y1*r;
			vVertex[3][2] = z;

			torusBatch.AddTriangle(vVertex, vNormal, vTexture);			
			
			// Rearrange for next triangle
			memcpy(vVertex[0], vVertex[1], sizeof(M3DVector3f));
			memcpy(vNormal[0], vNormal[1], sizeof(M3DVector3f));
			memcpy(vTexture[0], vTexture[1], sizeof(M3DVector2f));
			
			memcpy(vVertex[1], vVertex[3], sizeof(M3DVector3f));
			memcpy(vNormal[1], vNormal[3], sizeof(M3DVector3f));
			memcpy(vTexture[1], vTexture[3], sizeof(M3DVector2f));
					
			torusBatch.AddTriangle(vVertex, vNormal, vTexture);			
			}
		}
	torusBatch.End();
	}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Make a sphere
void gltMakeSphere(GLTriangleBatch& sphereBatch, GLfloat fRadius, GLint iSlices, GLint iStacks)
	{
    GLfloat drho = (GLfloat)(3.141592653589) / (GLfloat) iStacks;
    GLfloat dtheta = 2.0f * (GLfloat)(3.141592653589) / (GLfloat) iSlices;
	GLfloat ds = 1.0f / (GLfloat) iSlices;
	GLfloat dt = 1.0f / (GLfloat) iStacks;
	GLfloat t = 1.0f;	
	GLfloat s = 0.0f;
    GLint i, j;     // Looping variables
    
    sphereBatch.BeginMesh(iSlices * iStacks * 6);
	for (i = 0; i < iStacks; i++) 
		{
		GLfloat rho = (GLfloat)i * drho;
		GLfloat srho = (GLfloat)(sin(rho));
		GLfloat crho = (GLfloat)(cos(rho));
		GLfloat srhodrho = (GLfloat)(sin(rho + drho));
		GLfloat crhodrho = (GLfloat)(cos(rho + drho));
		
        // Many sources of OpenGL sphere drawing code uses a triangle fan
        // for the caps of the sphere. This however introduces texturing 
        // artifacts at the poles on some OpenGL implementations
        s = 0.0f;
		M3DVector3f vVertex[4];
		M3DVector3f vNormal[4];
		M3DVector2f vTexture[4];

		for ( j = 0; j < iSlices; j++) 
			{
			GLfloat theta = (j == iSlices) ? 0.0f : j * dtheta;
			GLfloat stheta = (GLfloat)(-sin(theta));
			GLfloat ctheta = (GLfloat)(cos(theta));
			
			GLfloat x = stheta * srho;
			GLfloat y = ctheta * srho;
			GLfloat z = crho;
        
			vTexture[0][0] = s;
			vTexture[0][1] = t;
			vNormal[0][0] = x;
			vNormal[0][1] = y;
			vNormal[0][2] = z;
			vVertex[0][0] = x * fRadius;
			vVertex[0][1] = y * fRadius;
			vVertex[0][2] = z * fRadius;
			
            x = stheta * srhodrho;
			y = ctheta * srhodrho;
			z = crhodrho;

 			vTexture[1][0] = s;
			vTexture[1][1] = t - dt;
			vNormal[1][0] = x;
			vNormal[1][1] = y;
			vNormal[1][2] = z;
			vVertex[1][0] = x * fRadius;
			vVertex[1][1] = y * fRadius;
			vVertex[1][2] = z * fRadius;
			

			theta = ((j+1) == iSlices) ? 0.0f : (j+1) * dtheta;
			stheta = (GLfloat)(-sin(theta));
			ctheta = (GLfloat)(cos(theta));
			
			x = stheta * srho;
			y = ctheta * srho;
			z = crho;
        
            s += ds;
			vTexture[2][0] = s;
			vTexture[2][1] = t;
			vNormal[2][0] = x;
			vNormal[2][1] = y;
			vNormal[2][2] = z;
			vVertex[2][0] = x * fRadius;
			vVertex[2][1] = y * fRadius;
			vVertex[2][2] = z * fRadius;
			
            x = stheta * srhodrho;
			y = ctheta * srhodrho;
			z = crhodrho;

 			vTexture[3][0] = s;
			vTexture[3][1] = t - dt;
			vNormal[3][0] = x;
			vNormal[3][1] = y;
			vNormal[3][2] = z;
			vVertex[3][0] = x * fRadius;
			vVertex[3][1] = y * fRadius;
			vVertex[3][2] = z * fRadius;
		
			sphereBatch.AddTriangle(vVertex, vNormal, vTexture);			
			
			// Rearrange for next triangle
			memcpy(vVertex[0], vVertex[1], sizeof(M3DVector3f));
			memcpy(vNormal[0], vNormal[1], sizeof(M3DVector3f));
			memcpy(vTexture[0], vTexture[1], sizeof(M3DVector2f));
			
			memcpy(vVertex[1], vVertex[3], sizeof(M3DVector3f));
			memcpy(vNormal[1], vNormal[3], sizeof(M3DVector3f));
			memcpy(vTexture[1], vTexture[3], sizeof(M3DVector2f));
					
			sphereBatch.AddTriangle(vVertex, vNormal, vTexture);			
			}
        t -= dt;
        }
		sphereBatch.End();
    }
    

////////////////////////////////////////////////////////////////////////////////////////
void gltMakeDisk(GLTriangleBatch& diskBatch, GLfloat innerRadius, GLfloat outerRadius, GLint nSlices, GLint nStacks)
	{
	// How much to step out each stack
	GLfloat fStepSizeRadial = outerRadius - innerRadius;
	if(fStepSizeRadial < 0.0f)			// Dum dum...
		fStepSizeRadial *= -1.0f;

	fStepSizeRadial /= float(nStacks);
	
	GLfloat fStepSizeSlice = (3.1415926536f * 2.0f) / float(nSlices);
	
	diskBatch.BeginMesh(nSlices * nStacks * 6);
	
	M3DVector3f vVertex[4];
	M3DVector3f vNormal[4];
	M3DVector2f vTexture[4];
	
	float fRadialScale = 1.0f / outerRadius;
	
	for(GLint i = 0; i < nStacks; i++)			// Stacks
		{
		float theyta;
		float theytaNext;
		for(GLint j = 0; j < nSlices; j++)     // Slices
			{
			float inner = innerRadius + (float(i)) * fStepSizeRadial;
			float outer = innerRadius + (float(i+1)) * fStepSizeRadial;
			
			theyta = fStepSizeSlice * float(j);
			if(j == (nSlices - 1))
				theytaNext = 0.0f;
			else
				theytaNext = fStepSizeSlice * (float(j+1));
				
			// Inner First
			vVertex[0][0] = cos(theyta) * inner;	// X	
			vVertex[0][1] = sin(theyta) * inner;	// Y
			vVertex[0][2] = 0.0f;					// Z
			
			vNormal[0][0] = 0.0f;					// Surface Normal, same for everybody
			vNormal[0][1] = 0.0f;
			vNormal[0][2] = 1.0f;
			
			vTexture[0][0] = ((vVertex[0][0] * fRadialScale) + 1.0f) * 0.5f;	
			vTexture[0][1] = ((vVertex[0][1] * fRadialScale) + 1.0f) * 0.5f;
			
			// Outer First
			vVertex[1][0] = cos(theyta) * outer;	// X	
			vVertex[1][1] = sin(theyta) * outer;	// Y
			vVertex[1][2] = 0.0f;					// Z
			
			vNormal[1][0] = 0.0f;					// Surface Normal, same for everybody
			vNormal[1][1] = 0.0f;
			vNormal[1][2] = 1.0f;
			
			vTexture[1][0] = ((vVertex[1][0] * fRadialScale) + 1.0f) * 0.5f;
			vTexture[1][1] = ((vVertex[1][1] * fRadialScale) + 1.0f) * 0.5f;
			
			// Inner Second
			vVertex[2][0] = cos(theytaNext) * inner;	// X	
			vVertex[2][1] = sin(theytaNext) * inner;	// Y
			vVertex[2][2] = 0.0f;					// Z
			
			vNormal[2][0] = 0.0f;					// Surface Normal, same for everybody
			vNormal[2][1] = 0.0f;
			vNormal[2][2] = 1.0f;
			
			vTexture[2][0] = ((vVertex[2][0] * fRadialScale) + 1.0f) * 0.5f;
			vTexture[2][1] = ((vVertex[2][1] * fRadialScale) + 1.0f) * 0.5f;
			
			
			// Outer Second
			vVertex[3][0] = cos(theytaNext) * outer;	// X	
			vVertex[3][1] = sin(theytaNext) * outer;	// Y
			vVertex[3][2] = 0.0f;					// Z
			
			vNormal[3][0] = 0.0f;					// Surface Normal, same for everybody
			vNormal[3][1] = 0.0f;
			vNormal[3][2] = 1.0f;
			
			vTexture[3][0] = ((vVertex[3][0] * fRadialScale) + 1.0f) * 0.5f;
			vTexture[3][1] = ((vVertex[3][1] * fRadialScale) + 1.0f) * 0.5f;
			
			diskBatch.AddTriangle(vVertex, vNormal, vTexture);			
			
			// Rearrange for next triangle
			memcpy(vVertex[0], vVertex[1], sizeof(M3DVector3f));
			memcpy(vNormal[0], vNormal[1], sizeof(M3DVector3f));
			memcpy(vTexture[0], vTexture[1], sizeof(M3DVector2f));
			
			memcpy(vVertex[1], vVertex[3], sizeof(M3DVector3f));
			memcpy(vNormal[1], vNormal[3], sizeof(M3DVector3f));
			memcpy(vTexture[1], vTexture[3], sizeof(M3DVector2f));
					
			diskBatch.AddTriangle(vVertex, vNormal, vTexture);			
			}
		}
	
	diskBatch.End();
	}

// Draw a cylinder. Much like gluCylinder
void gltMakeCylinder(GLTriangleBatch& cylinderBatch, GLfloat baseRadius, GLfloat topRadius, 
			GLfloat fLength, GLint numSlices, GLint numStacks)
	{	
    float fRadiusStep = (topRadius - baseRadius) / float(numStacks);

	GLfloat fStepSizeSlice = (3.1415926536f * 2.0f) / float(numSlices);

	M3DVector3f vVertex[4];
	M3DVector3f vNormal[4];
	M3DVector2f vTexture[4];

    cylinderBatch.BeginMesh(numSlices * numStacks * 6);

    GLfloat ds = 1.0f / float(numSlices);
	GLfloat dt = 1.0f / float(numStacks);
	GLfloat s;
	GLfloat t;

	for (int i = 0; i < numStacks; i++) 
		{
		if(i == 0)			
			t = 0.0f;
		else
			t = float(i) * dt;

		float tNext;
		if(i == (numStacks - 1))
			tNext = 1.0f;
		else
			tNext = float(i+1) * dt;
	
		float fCurrentRadius = baseRadius + (fRadiusStep * float(i));
		float fNextRadius = baseRadius + (fRadiusStep * float(i+1));
		float theyta;
		float theytaNext;

		float fCurrentZ = float(i) * (fLength / float(numStacks)); 
		float fNextZ = float(i+1) * (fLength / float(numStacks));
		
		float zNormal = 0.0f;
		if(!m3dCloseEnough(baseRadius - topRadius, 0.0f, 0.00001f))
			{
			// Rise over run...
			zNormal = (baseRadius - topRadius);
			}
		
		for (int j = 0; j < numSlices; j++) 
			{		
			if(j == 0)
				s = 0.0f;
			else
				s = float(j) * ds;

			float sNext;
			if(j == (numSlices -1))
				sNext = 1.0f;
			else
				sNext = float(j+1) * ds;

			theyta = fStepSizeSlice * float(j);
			if(j == (numSlices - 1))
				theytaNext = 0.0f;
			else
				theytaNext = fStepSizeSlice * (float(j+1));
				
			// Inner First
			vVertex[1][0] = cos(theyta) * fCurrentRadius;	// X	
			vVertex[1][1] = sin(theyta) * fCurrentRadius;	// Y
			vVertex[1][2] = fCurrentZ;						// Z
			
			vNormal[1][0] = vVertex[1][0];					// Surface Normal, same for everybody
			vNormal[1][1] = vVertex[1][1];
			vNormal[1][2] = zNormal;
			m3dNormalizeVector3(vNormal[1]);
			
			vTexture[1][0] = s;					// Texture Coordinates, I have no idea...
			vTexture[1][1] = t;
	
			// Outer First
			vVertex[0][0] = cos(theyta) * fNextRadius;	// X	
			vVertex[0][1] = sin(theyta) * fNextRadius;	// Y
			vVertex[0][2] = fNextZ;						// Z
			
			if(!m3dCloseEnough(fNextRadius, 0.0f, 0.00001f)) {
				vNormal[0][0] = vVertex[0][0];					// Surface Normal, same for everybody
				vNormal[0][1] = vVertex[0][1];					// For cones, tip is tricky
				vNormal[0][2] = zNormal;
				m3dNormalizeVector3(vNormal[0]);
				}
			else
				memcpy(vNormal[0], vNormal[1], sizeof(M3DVector3f));
		
			
			vTexture[0][0] = s;					// Texture Coordinates, I have no idea...
			vTexture[0][1] = tNext;
			
			// Inner second
			vVertex[3][0] = cos(theytaNext) * fCurrentRadius;	// X	
			vVertex[3][1] = sin(theytaNext) * fCurrentRadius;	// Y
			vVertex[3][2] = fCurrentZ;						// Z
			
			vNormal[3][0] = vVertex[3][0];					// Surface Normal, same for everybody
			vNormal[3][1] = vVertex[3][1];
			vNormal[3][2] = zNormal;
			m3dNormalizeVector3(vNormal[3]);

			vTexture[3][0] = sNext;					// Texture Coordinates, I have no idea...
			vTexture[3][1] = t;

			// Outer second
			vVertex[2][0] = cos(theytaNext) * fNextRadius;	// X	
			vVertex[2][1] = sin(theytaNext) * fNextRadius;	// Y
			vVertex[2][2] = fNextZ;						// Z
			
			if(!m3dCloseEnough(fNextRadius, 0.0f, 0.00001f)) {
				vNormal[2][0] = vVertex[2][0];					// Surface Normal, same for everybody
				vNormal[2][1] = vVertex[2][1];
				vNormal[2][2] = zNormal;
				m3dNormalizeVector3(vNormal[2]);
				}
			else
				memcpy(vNormal[2], vNormal[3], sizeof(M3DVector3f));
				

			vTexture[2][0] = sNext;					// Texture Coordinates, I have no idea...
			vTexture[2][1] = tNext;
		
			cylinderBatch.AddTriangle(vVertex, vNormal, vTexture);			
			
			// Rearrange for next triangle
			memcpy(vVertex[0], vVertex[1], sizeof(M3DVector3f));
			memcpy(vNormal[0], vNormal[1], sizeof(M3DVector3f));
			memcpy(vTexture[0], vTexture[1], sizeof(M3DVector2f));
			
			memcpy(vVertex[1], vVertex[3], sizeof(M3DVector3f));
			memcpy(vNormal[1], vNormal[3], sizeof(M3DVector3f));
			memcpy(vTexture[1], vTexture[3], sizeof(M3DVector2f));
					
			cylinderBatch.AddTriangle(vVertex, vNormal, vTexture);			
			}
        }
	cylinderBatch.End();
	}
	
	
///////////////////////////////////////////////////////////////////////////////////////
// Make a cube, centered at the origin, and with a specified "radius"
/*void gltMakeCube(GLBatch& cubeBatch, GLfloat fRadius )
    {
    cubeBatch.Begin(GL_TRIANGLES, 36, 1);
            
    /////////////////////////////////////////////
    // Top of cube
    cubeBatch.Normal3f(0.0f, fRadius, 0.0f);
    cubeBatch.MultiTexCoord2f(0, fRadius, fRadius);
    cubeBatch.Vertex3f(fRadius, fRadius, fRadius);
    
    cubeBatch.Normal3f(0.0f, fRadius, 0.0f);
    cubeBatch.MultiTexCoord2f(0, fRadius, 0.0f);
    cubeBatch.Vertex3f(fRadius, fRadius, -fRadius);
    
    cubeBatch.Normal3f(0.0f, fRadius, 0.0f);
    cubeBatch.MultiTexCoord2f(0, 0.0f, 0.0f);
    cubeBatch.Vertex3f(-fRadius, fRadius, -fRadius);
    
    cubeBatch.Normal3f(0.0f, fRadius, 0.0f);
    cubeBatch.MultiTexCoord2f(0, fRadius, fRadius);
    cubeBatch.Vertex3f(fRadius, fRadius, fRadius);
    
    cubeBatch.Normal3f(0.0f, fRadius, 0.0f);
    cubeBatch.MultiTexCoord2f(0, 0.0f, 0.0f);
    cubeBatch.Vertex3f(-fRadius, fRadius, -fRadius);
    
    cubeBatch.Normal3f(0.0f, fRadius, 0.0f);
    cubeBatch.MultiTexCoord2f(0, 0.0f, fRadius);
    cubeBatch.Vertex3f(-fRadius, fRadius, fRadius);
    
    
    ////////////////////////////////////////////
    // Bottom of cube
    cubeBatch.Normal3f(0.0f, -fRadius, 0.0f);
    cubeBatch.MultiTexCoord2f(0, 0.0f, 0.0f);
    cubeBatch.Vertex3f(-fRadius, -fRadius, -fRadius);
    
    cubeBatch.Normal3f(0.0f, -fRadius, 0.0f);
    cubeBatch.MultiTexCoord2f(0, fRadius, 0.0f);
    cubeBatch.Vertex3f(fRadius, -fRadius, -fRadius);
    
    cubeBatch.Normal3f(0.0f, -fRadius, 0.0f);
    cubeBatch.MultiTexCoord2f(0, fRadius, fRadius);
    cubeBatch.Vertex3f(fRadius, -fRadius, fRadius);
    
    cubeBatch.Normal3f(0.0f, -fRadius, 0.0f);
    cubeBatch.MultiTexCoord2f(0, 0.0f, fRadius);
    cubeBatch.Vertex3f(-fRadius, -fRadius, fRadius);
    
    cubeBatch.Normal3f(0.0f, -fRadius, 0.0f);
    cubeBatch.MultiTexCoord2f(0, 0.0f, 0.0f);
    cubeBatch.Vertex3f(-fRadius, -fRadius, -fRadius);
    
    cubeBatch.Normal3f(0.0f, -fRadius, 0.0f);
    cubeBatch.MultiTexCoord2f(0, fRadius, fRadius);
    cubeBatch.Vertex3f(fRadius, -fRadius, fRadius);
    
    ///////////////////////////////////////////
    // Left side of cube
    cubeBatch.Normal3f(-fRadius, 0.0f, 0.0f);
    cubeBatch.MultiTexCoord2f(0, fRadius, fRadius);
    cubeBatch.Vertex3f(-fRadius, fRadius, fRadius);
    
    cubeBatch.Normal3f(-fRadius, 0.0f, 0.0f);
    cubeBatch.MultiTexCoord2f(0, fRadius, 0.0f);
    cubeBatch.Vertex3f(-fRadius, fRadius, -fRadius);
    
    cubeBatch.Normal3f(-fRadius, 0.0f, 0.0f);
    cubeBatch.MultiTexCoord2f(0, 0.0f, 0.0f);
    cubeBatch.Vertex3f(-fRadius, -fRadius, -fRadius);
    
    cubeBatch.Normal3f(-fRadius, 0.0f, 0.0f);
    cubeBatch.MultiTexCoord2f(0, fRadius, fRadius);
    cubeBatch.Vertex3f(-fRadius, fRadius, fRadius);
    
    cubeBatch.Normal3f(-fRadius, 0.0f, 0.0f);
    cubeBatch.MultiTexCoord2f(0, 0.0f, 0.0f);
    cubeBatch.Vertex3f(-fRadius, -fRadius, -fRadius);
    
    cubeBatch.Normal3f(-fRadius, 0.0f, 0.0f);
    cubeBatch.MultiTexCoord2f(0, 0.0f, fRadius);
    cubeBatch.Vertex3f(-fRadius, -fRadius, fRadius);
    
    // Right side of cube
    cubeBatch.Normal3f(fRadius, 0.0f, 0.0f);
    cubeBatch.MultiTexCoord2f(0, 0.0f, 0.0f);
    cubeBatch.Vertex3f(fRadius, -fRadius, -fRadius);
    
    cubeBatch.Normal3f(fRadius, 0.0f, 0.0f);
    cubeBatch.MultiTexCoord2f(0, fRadius, 0.0f);
    cubeBatch.Vertex3f(fRadius, fRadius, -fRadius);
    
    cubeBatch.Normal3f(fRadius, 0.0f, 0.0f);
    cubeBatch.MultiTexCoord2f(0, fRadius, fRadius);
    cubeBatch.Vertex3f(fRadius, fRadius, fRadius);
    
    cubeBatch.Normal3f(fRadius, 0.0f, 0.0f);
    cubeBatch.MultiTexCoord2f(0, fRadius, fRadius);
    cubeBatch.Vertex3f(fRadius, fRadius, fRadius);
    
    cubeBatch.Normal3f(fRadius, 0.0f, 0.0f);
    cubeBatch.MultiTexCoord2f(0, 0.0f, fRadius);
    cubeBatch.Vertex3f(fRadius, -fRadius, fRadius);
    
    cubeBatch.Normal3f(fRadius, 0.0f, 0.0f);
    cubeBatch.MultiTexCoord2f(0, 0.0f, 0.0f);
    cubeBatch.Vertex3f(fRadius, -fRadius, -fRadius);
    
    // Front and Back
    // Front
    cubeBatch.Normal3f(0.0f, 0.0f, fRadius);
    cubeBatch.MultiTexCoord2f(0, fRadius, 0.0f);
    cubeBatch.Vertex3f(fRadius, -fRadius, fRadius);
    
    cubeBatch.Normal3f(0.0f, 0.0f, fRadius);
    cubeBatch.MultiTexCoord2f(0, fRadius, fRadius);
    cubeBatch.Vertex3f(fRadius, fRadius, fRadius);
    
    cubeBatch.Normal3f(0.0f, 0.0f, fRadius);
    cubeBatch.MultiTexCoord2f(0, 0.0f, fRadius);
    cubeBatch.Vertex3f(-fRadius, fRadius, fRadius);
    
    cubeBatch.Normal3f(0.0f, 0.0f, fRadius);
    cubeBatch.MultiTexCoord2f(0, 0.0f, fRadius);
    cubeBatch.Vertex3f(-fRadius, fRadius, fRadius);
    
    cubeBatch.Normal3f(0.0f, 0.0f, fRadius);
    cubeBatch.MultiTexCoord2f(0, 0.0f, 0.0f);
    cubeBatch.Vertex3f(-fRadius, -fRadius, fRadius);
    
    cubeBatch.Normal3f(0.0f, 0.0f, fRadius);
    cubeBatch.MultiTexCoord2f(0, fRadius, 0.0f);
    cubeBatch.Vertex3f(fRadius, -fRadius, fRadius);
    
    // Back
    cubeBatch.Normal3f(0.0f, 0.0f, -fRadius);
    cubeBatch.MultiTexCoord2f(0, fRadius, 0.0f);
    cubeBatch.Vertex3f(fRadius, -fRadius, -fRadius);
    
    cubeBatch.Normal3f(0.0f, 0.0f, -fRadius);
    cubeBatch.MultiTexCoord2f(0, 0.0f, 0.0f);
    cubeBatch.Vertex3f(-fRadius, -fRadius, -fRadius);
    
    cubeBatch.Normal3f(0.0f, 0.0f, -fRadius);
    cubeBatch.MultiTexCoord2f(0, 0.0f, fRadius);
    cubeBatch.Vertex3f(-fRadius, fRadius, -fRadius);
    
    cubeBatch.Normal3f(0.0f, 0.0f, -fRadius);
    cubeBatch.MultiTexCoord2f(0, 0.0f, fRadius);
    cubeBatch.Vertex3f(-fRadius, fRadius, -fRadius);
    
    cubeBatch.Normal3f(0.0f, 0.0f, -fRadius);
    cubeBatch.MultiTexCoord2f(0, fRadius, fRadius);
    cubeBatch.Vertex3f(fRadius, fRadius, -fRadius);

	cubeBatch.Normal3f(0.0f, 0.0f, -fRadius);
	cubeBatch.MultiTexCoord2f(0, fRadius, 0.0f);
	cubeBatch.Vertex3f(fRadius, -fRadius, -fRadius);   
    cubeBatch.End();
	}	

*/

// Define targa header. This is only used locally.
#pragma pack(1)
typedef struct
{
    GLbyte	identsize;              // Size of ID field that follows header (0)
    GLbyte	colorMapType;           // 0 = None, 1 = paletted
    GLbyte	imageType;              // 0 = none, 1 = indexed, 2 = rgb, 3 = grey, +8=rle
    unsigned short	colorMapStart;          // First colour map entry
    unsigned short	colorMapLength;         // Number of colors
    unsigned char 	colorMapBits;   // bits per palette entry
    unsigned short	xstart;                 // image x origin
    unsigned short	ystart;                 // image y origin
    unsigned short	width;                  // width in pixels
    unsigned short	height;                 // height in pixels
    GLbyte	bits;                   // bits per pixel (8 16, 24, 32)
    GLbyte	descriptor;             // image descriptor
} TGAHEADER;
#pragma pack(8)


	
/////////////////////////////////////////////////////////////////
// Check for any GL errors that may affect rendering
// Check the framebuffer, the shader, and general errors
bool gltCheckErrors(GLuint progName)
{
    bool bFoundError = false;
	GLenum error = glGetError();
		
	if (error != GL_NO_ERROR)
	{
	    fprintf(stderr, "A GL Error has occured\n");
        bFoundError = true;
	}
#ifndef OPENGL_ES
	GLenum fboStatus = glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER);

	if(fboStatus != GL_FRAMEBUFFER_COMPLETE)
	{
        bFoundError = true;
		fprintf(stderr,"The framebuffer is not complete - ");
		switch (fboStatus)
		{
		case GL_FRAMEBUFFER_UNDEFINED:
			// Oops, no window exists?
            fprintf(stderr, "GL_FRAMEBUFFER_UNDEFINED\n");
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
			// Check the status of each attachment
            fprintf(stderr, "GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT\n");
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
			// Attach at least one buffer to the FBO
            fprintf(stderr, "GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT\n");
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
			// Check that all attachments enabled via
			// glDrawBuffers exist in FBO
            fprintf(stderr, "GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER\n");
            break;
		case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
			// Check that the buffer specified via
			// glReadBuffer exists in FBO
            fprintf(stderr, "GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER\n");
			break;
		case GL_FRAMEBUFFER_UNSUPPORTED:
			// Reconsider formats used for attached buffers
            fprintf(stderr, "GL_FRAMEBUFFER_UNSUPPORTED\n");
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:
			// Make sure the number of samples for each 
			// attachment is the same 
            fprintf(stderr, "GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE\n");
			break; 
		case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS:
			// Make sure the number of layers for each 
			// attachment is the same 
            fprintf(stderr, "GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS\n");
			break;
		}
	}

#endif

	if (progName != 0)
	{
		glValidateProgram(progName);
		int iIsProgValid = 0;
		glGetProgramiv(progName, GL_VALIDATE_STATUS, &iIsProgValid);
		if(iIsProgValid == 0)
		{
            bFoundError = true;
			fprintf(stderr, "The current program(%d) is not valid\n", progName);
		}
	}
    return bFoundError;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
// Create a matrix that maps geometry to the screen. 1 unit in the x directionequals one pixel 
// of width, same with the y direction.
/*void gltGenerateOrtho2DMat(GLuint screenWidth, GLuint screenHeight, 
                           M3DMatrix44f &orthoMatrix, GLBatch &screenQuad)
{
    float right = (float)screenWidth;
	float left  = 0.0f;
	float top = (float)screenHeight;
	float bottom = 0.0f;
	
    // set ortho matrix
	orthoMatrix[0] = (float)(2 / (right - left));
	orthoMatrix[1] = 0.0;
	orthoMatrix[2] = 0.0;
	orthoMatrix[3] = 0.0;

	orthoMatrix[4] = 0.0;
	orthoMatrix[5] = (float)(2 / (top - bottom));
	orthoMatrix[6] = 0.0;
	orthoMatrix[7] = 0.0;

	orthoMatrix[8] = 0.0;
	orthoMatrix[9] = 0.0;
	orthoMatrix[10] = (float)(-2 / (1.0 - 0.0));
	orthoMatrix[11] = 0.0;

	orthoMatrix[12] = -1*(right + left) / (right - left);
	orthoMatrix[13] = -1*(top + bottom) / (top - bottom);
	orthoMatrix[14] = -1.0f;
	orthoMatrix[15] =  1.0;

    // set screen quad vertex array
	screenQuad.Reset();
	screenQuad.Begin(GL_TRIANGLE_STRIP, 4, 1);
		screenQuad.Color4f(0.0f, 1.0f, 0.0f, 1.0f);
		screenQuad.MultiTexCoord2f(0, 0.0f, 0.0f); 
		screenQuad.Vertex3f(0.0f, 0.0f, 0.0f);

		screenQuad.Color4f(0.0f, 1.0f, 0.0f, 1.0f);
		screenQuad.MultiTexCoord2f(0, 1.0f, 0.0f);
		screenQuad.Vertex3f((float)screenWidth, 0.0f, 0.0f);

		screenQuad.Color4f(0.0f, 1.0f, 0.0f, 1.0f);
		screenQuad.MultiTexCoord2f(0, 0.0f, 1.0f);
		screenQuad.Vertex3f(0.0f, (float)screenHeight, 0.0f);

		screenQuad.Color4f(0.0f, 1.0f, 0.0f, 1.0f);
		screenQuad.MultiTexCoord2f(0, 1.0f, 1.0f);
		screenQuad.Vertex3f((float)screenWidth, (float)screenHeight, 0.0f);
	screenQuad.End();
}
*/
