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

#ifndef PERFORMANCE_TIMER_H
#define PERFORMANCE_TIMER_H

#ifdef _WIN32
	#include <windows.h>	// Windows
#elif __APPLE__
  #include <sys/time.h>	// Mac/Unix
#elif __linux
	#include <sys/time.h>
	#include <cstddef>		// Linux
#endif

/** Performance_Timer.h
 * A cross-platform timer wrapped around a high performance Windows/Unix time function.
 *
 * Authors: Paul Solt 8-21-10
 */

namespace glutFramework {
	class PerformanceTimer
	{
	public:
		PerformanceTimer();
		~PerformanceTimer();

		/** Starts the timer */
		void start();

		/** Stops the timer */
		void stop();

		/** Checks to see if the timer is stopped */
		bool isStopped() const;

		/** Returns the elapsed time since the timer was started, or the time interval
		 between calls to start() and stop().
		 */
		double getElapsedMicroseconds();
		double getElapsedMilliseconds();
		double getElapsedSeconds();

	private:
		bool _isStopped;

	#ifdef WIN32
		LARGE_INTEGER _start;
		LARGE_INTEGER _end;
		LARGE_INTEGER _freq;
	#else
		timeval _start;
		timeval _end;
	#endif

	};
}	// namespace

#endif
