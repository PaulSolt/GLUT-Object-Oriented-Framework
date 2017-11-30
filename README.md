GLUT Object Oriented Framework
Copyright 2010 � Paul Solt
Update Date: 8/22/10
Release 1.0.0
-------------------------------

Overview:
---------
The GLUT Object Oriented Framework is a set of classes that wrap around the GLUT C-style function calls to create an animation framework. It provides a simple object oriented wrapper that has virtual methods to override default behavior. Four lines of code within a main function can be used to get a graphics window that draws an animated teapot.

	Teapot Demo:
	------------
	// main.cpp
	#include "GlutFramework.h"
	using namespace glutFramework;
	int main(int argc, char *argv[]) {
		GlutFramework framework;
		framework.startFramework(argc, argv);
	    return 0;
	}

	Subclass Example:
   	-----------------
   	MySubClassOfGlutFramework framework;
   	framework.startFramework();

Cross-platform Support:
-----------------------
1. Xcode 3.1 project that builds against Mac OSX 10.5
	a. New projects must add GLUT and OpenGL frameworks
2. Visual Studio 2010 project for Windows .NET 2.0
	a. GLUT must be installed and setup http://www.xmission.com/~nate/glut.html
	b. Setup GLUT via: http://www.cs.uiowa.edu/~cwyman/classes/common/howto/winGLUT.html
3. Project that builds for Linux
 	a. Must install cmake
	b. Create a folder, can have any name
	c. Go inside the folder, **run cmake ..**. After cmake created the Makefile, run **make**

Animation Framework:
--------------------
PerformanceTimer is a cross-platform high performance timer that can be used in Windows, Mac, and Unix to get very accurate time deltas. Time deltas are used to create a stable framerate for animation.
