/******************************************************************************************
*	Warplanes                                   										  *
*	Copyright 2016 - Barna Birtók - PcSpaceGeep									   		  *
*	Created with the use of Chili DirectX Framework Version 11.12.17					  *
*																						  *
*	Warplanes is free software: you can redistribute it and/or modify	                  *
*	it under the terms of the GNU General Public License as published by				  *
*	the Free Software Foundation, either version 3 of the License, or					  *
*	(at your option) any later version.													  *
*																						  *
*	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,   *
*	INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A         *
*	PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT    *
*	HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF  *
*	CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE  *
*	OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.									      *
*																						  *
*	Dependencies: Requires the DXSDK to run.											  *
******************************************************************************************/
#include "Timer.h"

Timer::Timer()
{
	__int64 frequency;
	QueryPerformanceFrequency( (LARGE_INTEGER*)&frequency );
	invFreqMilli = 1.0f / (float)((double)frequency / 1000.0);
	StartWatch();
}

void Timer::StopWatch()
{
	if( !watchStopped )
	{
		QueryPerformanceCounter( (LARGE_INTEGER*)&currentCount );
		watchStopped = true;
	}
}

void Timer::StartWatch()
{
	watchStopped = false;
	QueryPerformanceCounter( (LARGE_INTEGER*)&startCount );
}

float Timer::GetTimeMilli() const
{
	if( !watchStopped )
	{
		QueryPerformanceCounter( (LARGE_INTEGER*)&currentCount );
		return (float)(currentCount - startCount) * invFreqMilli;
	}
	else
	{
		return (float)(currentCount - startCount) * invFreqMilli;
	}
}