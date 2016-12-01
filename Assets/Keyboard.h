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
#pragma once

class KeyboardServer;

class KeyboardClient
{
public:
	KeyboardClient( const KeyboardServer& kServer );
	bool UpIsPressed() const;
	bool DownIsPressed() const;
	bool LeftIsPressed() const;
	bool RightIsPressed() const;
	bool SpaceIsPressed() const;
	bool EnterIsPressed() const;
	bool PIsPressed() const;
private:
	const KeyboardServer& server;
};

class KeyboardServer
{
	friend KeyboardClient;
public:
	KeyboardServer();

	void OnUpPressed();
	void OnDownPressed();
	void OnLeftPressed();
	void OnRightPressed();
	void OnSpacePressed();
	void OnEnterPressed();
	void OnPPressed();

	void OnUpReleased();
	void OnDownReleased();
	void OnLeftReleased();
	void OnRightReleased();
	void OnSpaceReleased();
	void OnEnterReleased();
	void OnPReleased();
private:
	bool upIsPressed;
	bool downIsPressed;
	bool leftIsPressed;
	bool rightIsPressed;
	bool spaceIsPressed;
	bool enterIsPressed;
	bool pIsPressed;
};