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

#include "D3DGraphics.h"
#include "Keyboard.h"

class Game
{
public:
	Game( HWND hWnd,const KeyboardServer& kServer );
	void Go();
private:
	enum fieldState
	{
		EMPTY,
		AIRPLANE_BODY,
		UP_AIRPLANE_HEAD,
		DOWN_AIRPLANE_HEAD,
		LEFT_AIRPLANE_HEAD,
		RIGHT_AIRPLANE_HEAD,
		OVERLAP,
		MISS,
		DESTROYED_AIRPLANE_BODY,
		DESTROYED_AIRPLANE_HEAD
	};
	enum airplaneDirection
	{
		UP,
		RIGHT,
		DOWN,
		LEFT
	};

	enum gamestates
	{
		P1_AIRPLANE_PLACEMENT,
		P2_AIRPLANE_PLACEMENT,
		P1_ATTACK,
		P2_ATTACK,
		P1_WIN,
		P2_WIN
	};
private:
	void ComposeFrame();
	/********************************/
	/*  User Functions              */

	// TODO: User functions go here
	void drawGrid();
	void drawAirplaneUp(int x, int y, int r, int g, int b);
	void drawAirplaneDown(int x, int y, int r, int g, int b);
	void drawAirplaneLeft(int x, int y, int r, int g, int b);
	void drawAirplaneRight(int x, int y, int r, int g, int b);
	void drawCursor(int x, int y, int r, int g, int b);
	void drawAirplanes();
	void drawOverlap();
	void drawShot(int x, int y, int r, int g, int b);
	void drawHeadShot(int x, int y, int r, int g, int b);
	void drawMiss(int x, int y, int r, int g, int b);

	bool overlapCheck(int x, int y);
	void airplanePositioning();
	void airplaneMovement();
	void airplaneRotation();
	void airplaneOverlap();
	void airpalnePalcement();
	void deleteAirplane();
	void attack();
	void radar();

	void AIairplaneRotation();
	void AIairplanePositioning();

	void cursorMovement();
	
	void setFieldState(int hIndex, int vIndex, int layer, fieldState state);
	void setFieldState(int player, int hIndex, int vIndex, int layer, fieldState state);
	fieldState getFieldState(int hIndex, int vIndex, int layer);
	fieldState getFieldState(int player, int hIndex, int vIndex, int layer);
	/********************************/
private:
	D3DGraphics gfx;
	KeyboardClient kbd;

	/********************************/
	/*  User Variables              */
	
	// TODO: User variables go here
	int gridSize;
	int cursorX, cursorY;
	int airplaneX, airplaneY;
	int indent;
	int player;
	int up_airplane_body_locations[10][2];
	int right_airplane_body_locations[10][2];
	int down_airplane_body_locations[10][2];
	int left_airplane_body_locations[10][2];
	int p1Airplanes, p2Airplanes;
	int p1AirplanesDestroyed, p2AirplanesDestroyed;
	const int airplanes = 5;
	const int baseX = 9;
	const int baseY = 9;
	const int gridDistance = 10;
	static const int tableSize = 15;

	bool keyPressedLastFrame;
	bool rotatedLastFrame;
	bool placedLastFrame;
	bool firedLastFrame;
	bool Overlap;
	bool p1Attacked;
	bool p2Attacked;

	fieldState p1field[tableSize][tableSize][2];
	fieldState p2field[tableSize][tableSize][2];
	airplaneDirection airplane_direction;
	gamestates gamestate;

	/********************************/
};