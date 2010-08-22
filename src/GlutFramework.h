/*
 * The MIT License
 *
 * Copyright (c) 2010 Paul Solt, PaulSolt@gmail.com 
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef ANIMATION_FRAMEWORK_H
#define ANIMATION_FRAMEWORK_H

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <math.h>
#include <string.h>

// **Note:** Include GLUT after the standard c++ libraries to prevent linker errors

// Mac and PC compatible
#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#else
#include <windows.h> 
#include <GL/glut.h> 
#endif

#include "Keyboard.h"
#include "PerformanceTimer.h"
#include "Vector.h"

/** GlutFramework.h
 *
 * The GlutFramework defines a super class that can be used to create a graphics 
 * application that requires an animation loop. The frame rate is set by default
 * to 60 frames per second.
 *
 * Users should sub-class the framework to define application specific logic.
 *
 * @author Paul Solt 8-21-10
 */
namespace glutFramework {
		
	class GlutFramework {
		
	private:
		double frameTimeElapsed;
		
	protected:
		Keyboard keyStates;
		PerformanceTimer frameRateTimer;
		PerformanceTimer displayTimer;
		
		std::string title;
		double elapsedTimeInSeconds;  
		static GlutFramework *instance;
		
		
		Vector<float> eyeVector;
		Vector<float> centerVector;
		Vector<float> upVector;
		
		float position;
		float direction;
		
	public:
		// Constants
		const static double FPS;			// Frames per second
		const static double FRAME_TIME;		// Frame time is in milliseconds
		
		const static int WINDOW_WIDTH = 640;
		const static int WINDOW_HEIGHT = 480;
		const static int WINDOW_X_POSITION = 100;
		const static int WINDOW_Y_POSITION = 100;
		
		
	public:
		GlutFramework();
		virtual ~GlutFramework();
		
		/** startFramework will initialize framework and start the Glut run loop. It
		 * must be called after the GlutFramework class is created to start the application. 
		 */
		void startFramework(int argc, char *argv[]);
		
		// ****************************
		// ** Subclass and Implement ** 
		// ****************************
		
		/** Any loading logic can be down in this method when the application starts. */
		virtual void load();
		
		/** The display function is called at a specified frames-per-second (FPS). Any
		 animation drawing code can be run in the display method.
		 @param dTime - the change in time (seconds)
		 */
		virtual void display(float dTime);
		
		/** The keyboard function is called when a standard key is pressed down.
		 @param key - the key press
		 @param x - the x coordinate of the mouse
		 @param y - the y coordinate of the mouse
		 */
		virtual void keyboard( unsigned char key, int x, int y );
		
		/** The keyboard function is called when a standard key is "unpressed".
		 @param key - the key press
		 @param x - the x coordinate of the mouse
		 @param y - the y coordinate of the mouse
		 */
		virtual void keyboardUp( unsigned char key, int x, int y );
		
		/** The keyboard function is called when a special key is pressed down.
		 (F1 keys, Home, Inser, Delete, Page Up/Down, End, arrow keys) 
		 http://www.opengl.org/resources/libraries/glut/spec3/node54.html
		 @param key - the key press
		 @param x - the x coordinate of the mouse
		 @param y - the y coordinate of the mouse
		 */
		virtual void specialKeyboard( int key, int x, int y );
		
		/** The keyboard function is called when a special key is "unpressed.
		 (F1 keys, Home, Inser, Delete, Page Up/Down, End, arrow keys) 
		 @param key - the key press
		 @param x - the x coordinate of the mouse
		 @param y - the y coordinate of the mouse
		 */
		virtual void specialKeyboardUp( int key, int x, int y ); 
		
		/** Sets the intitial matricies that are used to setup OpenGL. */
		void setDisplayMatricies();
		
		/** Sets up basic lighting */
		void setupLights();
		
		/** A helper function that allows the camera position and orientation to be changed. 
		 @param eyeX, eyeY, eyeZ - the vector describing the "eye" or camera position 
		 @param centerX, centerY, centerZ - the vector describing the "object" that the eye is looking at
		 @param upX, upY, upZ - the vector describing orientation. Normally (0,1,0) 
		 */
		void setLookAt(float eyeX, float eyeY, float eyeZ, 
					   float centerX, float centerY, float centerZ,
					   float upX, float upY, float upZ);
		
		/** The position of the "eye" or camera in 3D space 
		 @return a 3D vector
		 */
		Vector<float> getEyeVector() const;
		
		/** The position that the "eye" or camera is looking at in 3D space 
		 @return a 3D vector
		 */
		Vector<float> getCenterVector() const;
		
		/** The up vector, used to determine orientation. Normally set to (0,1,0) 
		 @return a 3D vector
		 */
		Vector<float> getUpVector() const;
		
		/** Sets the title of the window to a specific string. Invoke before startFramework() 
		 @param title - the name of the window 
		 */
		void setTitle(std::string theTitle);
		
		/** Initializes GLUT and registers the callback functions. */
		void init();
		
		/** The instance will be set when the framework is started, this step is necessary
		 * to initialize the static instance that is used for the object oriented wrapper calls 
		 */
		void setInstance(); 
		
		/** The run method is called by GLUT and contains the logic to set the framerate of the application. */
		void run();
		
		/** The displayFramework() function sets up initial GLUT state and calculates the
		 change in time between each frame. It calls the display(float) function which can
		 be subclassed.
		 */
		void displayFramework();
		
		// ** Static functions which are passed to GLUT function callbacks **
		// http://www.parashift.com/c++-faq-lite/pointers-to-members.html#faq-33.1
		static void displayWrapper();
		static void runWrapper();
		static void keyboardWrapper(unsigned char key, int x, int y);
		static void keyboardUpWrapper(unsigned char key, int x, int y);
		static void specialKeyboardWrapper(int key, int x, int y);
		static void specialKeyboardUpWrapper(int key, int x, int y);
	};
	
} // namespace 
#endif
