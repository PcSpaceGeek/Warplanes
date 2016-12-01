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
#include "Keyboard.h"


KeyboardClient::KeyboardClient( const KeyboardServer& kServer )
	: server( kServer )
{}

bool KeyboardClient::UpIsPressed() const
{
	return server.upIsPressed;
}
bool KeyboardClient::DownIsPressed() const
{
	return server.downIsPressed;
}
bool KeyboardClient::LeftIsPressed() const
{
	return server.leftIsPressed;
}
bool KeyboardClient::RightIsPressed() const
{
	return server.rightIsPressed;
}
bool KeyboardClient::SpaceIsPressed() const
{
	return server.spaceIsPressed;
}
bool KeyboardClient::EnterIsPressed() const
{
	return server.enterIsPressed;
}
bool KeyboardClient::PIsPressed() const
{
	return server.pIsPressed;
}



KeyboardServer::KeyboardServer()
:	upIsPressed( false ),
	downIsPressed( false ),
	leftIsPressed( false ),
	rightIsPressed( false ),
	spaceIsPressed( false ),
	enterIsPressed( false ),
	pIsPressed( false )
{}

void KeyboardServer::OnUpPressed()
{
	upIsPressed = true;
}
void KeyboardServer::OnDownPressed()
{
	downIsPressed = true;
}
void KeyboardServer::OnLeftPressed()
{
	leftIsPressed = true;
}
void KeyboardServer::OnRightPressed()
{
	rightIsPressed = true;
}
void KeyboardServer::OnSpacePressed()
{
	spaceIsPressed = true;
}
void KeyboardServer::OnEnterPressed()
{
	enterIsPressed = true;
}
void KeyboardServer::OnPPressed()
{
	pIsPressed = true;
}

void KeyboardServer::OnUpReleased()
{
	upIsPressed = false;
}
void KeyboardServer::OnDownReleased()
{
	downIsPressed = false;
}
void KeyboardServer::OnLeftReleased()
{
	leftIsPressed = false;
}
void KeyboardServer::OnRightReleased()
{
	rightIsPressed = false;
}
void KeyboardServer::OnSpaceReleased()
{
	spaceIsPressed = false;
}
void KeyboardServer::OnEnterReleased()
{
	enterIsPressed = false;
}
void KeyboardServer::OnPReleased()
{
	pIsPressed = false;
}