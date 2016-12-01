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
#include "Game.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>

Game::Game(HWND hWnd, const KeyboardServer& kServer)
	: gfx(hWnd),
	kbd(kServer),
	gridSize(600 / tableSize),
	cursorX(0),
	cursorY(0),
	airplaneX(tableSize / 2),
	airplaneY(tableSize / 2),
	indent(2),
	player(1),
	keyPressedLastFrame(false),
	rotatedLastFrame(false),
	placedLastFrame(false),
	firedLastFrame(false),
	Overlap(false),
	airplane_direction(UP),
	p1Airplanes(0),
	p2Airplanes(0),
	p1AirplanesDestroyed(0),
	p2AirplanesDestroyed(0),
	gamestate(P1_AIRPLANE_PLACEMENT),
	p1Attacked(false),
	p2Attacked(false)
{
	//p2Airplanes = airplanes;
	//p1Airplanes = airplanes;
	srand((unsigned int)time(NULL));
	for (int hIndex = 0;hIndex < tableSize;hIndex++)
	{
		for (int vIndex = 0; vIndex < tableSize; vIndex++)
		{
			for (int layer = 0;layer <= 2;layer++)
			{
				setFieldState(hIndex, vIndex, layer, EMPTY);
			}
		}
	}
	player = 2;
	for (int hIndex = 0;hIndex < tableSize;hIndex++)
	{
		for (int vIndex = 0; vIndex < tableSize; vIndex++)
		{
			for (int layer = 0;layer <= 2;layer++)
			{
				setFieldState(hIndex, vIndex, layer, EMPTY);
			}
		}
	}
	player = 1;
	up_airplane_body_locations[0][0] = 0;
	up_airplane_body_locations[0][1] = 0;
	up_airplane_body_locations[1][0] = -2;
	up_airplane_body_locations[1][1] = 1;
	up_airplane_body_locations[2][0] = -1;
	up_airplane_body_locations[2][1] = 1;
	up_airplane_body_locations[3][0] = 0;
	up_airplane_body_locations[3][1] = 1;
	up_airplane_body_locations[4][0] = 1;
	up_airplane_body_locations[4][1] = 1;
	up_airplane_body_locations[5][0] = 2;
	up_airplane_body_locations[5][1] = 1;
	up_airplane_body_locations[6][0] = 0;
	up_airplane_body_locations[6][1] = 2;
	up_airplane_body_locations[7][0] = -1;
	up_airplane_body_locations[7][1] = 3;
	up_airplane_body_locations[8][0] = 0;
	up_airplane_body_locations[8][1] = 3;
	up_airplane_body_locations[9][0] = 1;
	up_airplane_body_locations[9][1] = 3;
	down_airplane_body_locations[0][0] = 0;
	down_airplane_body_locations[0][1] = 0;
	down_airplane_body_locations[1][0] = -2;
	down_airplane_body_locations[1][1] = -1;
	down_airplane_body_locations[2][0] = -1;
	down_airplane_body_locations[2][1] = -1;
	down_airplane_body_locations[3][0] = 0;
	down_airplane_body_locations[3][1] = -1;
	down_airplane_body_locations[4][0] = 1;
	down_airplane_body_locations[4][1] = -1;
	down_airplane_body_locations[5][0] = 2;
	down_airplane_body_locations[5][1] = -1;
	down_airplane_body_locations[6][0] = 0;
	down_airplane_body_locations[6][1] = -2;
	down_airplane_body_locations[7][0] = -1;
	down_airplane_body_locations[7][1] = -3;
	down_airplane_body_locations[8][0] = 0;
	down_airplane_body_locations[8][1] = -3;
	down_airplane_body_locations[9][0] = 1;
	down_airplane_body_locations[9][1] = -3;
	left_airplane_body_locations[0][0] = 0;
	left_airplane_body_locations[0][1] = 0;
	left_airplane_body_locations[1][0] = 1;
	left_airplane_body_locations[1][1] = -2;
	left_airplane_body_locations[2][0] = 1;
	left_airplane_body_locations[2][1] = -1;
	left_airplane_body_locations[3][0] = 1;
	left_airplane_body_locations[3][1] = 0;
	left_airplane_body_locations[4][0] = 1;
	left_airplane_body_locations[4][1] = 1;
	left_airplane_body_locations[5][0] = 1;
	left_airplane_body_locations[5][1] = 2;
	left_airplane_body_locations[6][0] = 2;
	left_airplane_body_locations[6][1] = 0;
	left_airplane_body_locations[7][0] = 3;
	left_airplane_body_locations[7][1] = -1;
	left_airplane_body_locations[8][0] = 3;
	left_airplane_body_locations[8][1] = 0;
	left_airplane_body_locations[9][0] = 3;
	left_airplane_body_locations[9][1] = 1;
	right_airplane_body_locations[0][0] = 0;
	right_airplane_body_locations[0][1] = 0;
	right_airplane_body_locations[1][0] = -1;
	right_airplane_body_locations[1][1] = -2;
	right_airplane_body_locations[2][0] = -1;
	right_airplane_body_locations[2][1] = -1;
	right_airplane_body_locations[3][0] = -1;
	right_airplane_body_locations[3][1] = 0;
	right_airplane_body_locations[4][0] = -1;
	right_airplane_body_locations[4][1] = 1;
	right_airplane_body_locations[5][0] = -1;
	right_airplane_body_locations[5][1] = 2;
	right_airplane_body_locations[6][0] = -2;
	right_airplane_body_locations[6][1] = 0;
	right_airplane_body_locations[7][0] = -3;
	right_airplane_body_locations[7][1] = -1;
	right_airplane_body_locations[8][0] = -3;
	right_airplane_body_locations[8][1] = 0;
	right_airplane_body_locations[9][0] = -3;
	right_airplane_body_locations[9][1] = 1;
}

void Game::Go()
{
	gfx.BeginFrame();
	switch (gamestate)
	{
	case P1_AIRPLANE_PLACEMENT:
		player = 1;
		airplaneRotation();
		airplaneMovement();
		airplaneOverlap();
		airpalnePalcement();
		if (p1Airplanes == airplanes)
		{
			gamestate = P2_AIRPLANE_PLACEMENT;
		}
		break;
	case P2_AIRPLANE_PLACEMENT:
		player = 2;
		AIairplanePositioning();
		if (p2Airplanes == airplanes)
		{
			gamestate = P1_ATTACK;
		}
		break;
	case P1_ATTACK:
		if (p2AirplanesDestroyed == airplanes)
		{
			gamestate = P2_WIN;
		}
		else
		{
			player = 1;
			p2Attacked = false;
			cursorMovement();
			attack();
			if (p1Attacked)
			{
				gamestate = P2_ATTACK;
			}
		}
		break;
	case P2_ATTACK:
		if (p1AirplanesDestroyed == airplanes)
		{
			gamestate = P1_WIN;
		}
		else
		{
			player = 2;
			p1Attacked = false;
			p2Attacked = true;
			//p2 attack logic
			drawShot(cursorX, cursorY, 255, 255, 255);
			if (p2Attacked)
			{
				gamestate = P1_ATTACK;
			}
		}
		break;
	case P1_WIN:
		break;
	case P2_WIN:
		break;
	}
	ComposeFrame();
	gfx.EndFrame();
}

void Game::drawGrid()
{
	for (int y = baseY; y <= gridSize*tableSize + gridDistance; y = y + gridSize)
	{
		gfx.drawLine(baseX, baseX + gridSize*tableSize, y, y, 75, 75, 75);
		gfx.drawLine(baseX + gridSize*tableSize + gridDistance, baseY + 2 * gridSize*tableSize + gridDistance, y, y, 75, 75, 75);
	}
	for (int x = 9; x <= gridSize*tableSize + gridDistance; x = x + gridSize)
	{
		gfx.drawLine(x, x, baseY, baseY + gridSize*tableSize, 75, 75, 75);
		gfx.drawLine(x + gridSize*tableSize + gridDistance, x + gridSize*tableSize + gridDistance, baseY, baseY + gridSize*tableSize, 75, 75, 75);
	}
}

void Game::drawAirplaneUp(int x, int y, int r, int g, int b)
{
	x = baseX + x*gridSize;
	y = baseY + y*gridSize;
	gfx.drawRectangle(x + indent, x - indent + gridSize, y + indent, y + indent + gridSize,r,g,b);
	gfx.drawRectangle(x + indent - 2 * gridSize, x - indent + 3 * gridSize, y + indent + gridSize, y - indent + 2 * gridSize, r, g, b);
	gfx.drawRectangle(x + indent, x - indent + gridSize, y - indent + 2 * gridSize, y + indent + 3 * gridSize, r, g, b);
	gfx.drawRectangle(x + indent - gridSize, x - indent + 2 * gridSize, y + indent + 3 * gridSize, y - indent + 4 * gridSize, r, g, b);
}
void Game::drawAirplaneRight(int x, int y, int r, int g, int b)
{
	x = baseX + x*gridSize;
	y = baseY + y*gridSize;
	gfx.drawRectangle(x - indent, x - indent + gridSize, y + indent, y - indent + gridSize, r, g, b);
	gfx.drawRectangle(x + indent - gridSize, x - indent, y + indent - 2 * gridSize, y - indent + 3 * gridSize, r, g, b);
	gfx.drawRectangle(x - indent - 2 * gridSize, x + indent - gridSize, y + indent, y - indent + gridSize, r, g, b);
	gfx.drawRectangle(x + indent - 3 * gridSize, x - indent - 2 * gridSize, y + indent - gridSize, y - indent + 2 * gridSize, r, g, b);
}
void Game::drawAirplaneDown(int x, int y, int r, int g, int b)
{
	x = baseX + x*gridSize;
	y = baseY + y*gridSize;
	gfx.drawRectangle(x + indent, x - indent + gridSize, y - indent, y - indent + gridSize, r, g, b);
	gfx.drawRectangle(x + indent - 2 * gridSize, x - indent + 3 * gridSize, y + indent - gridSize, y - indent, r, g, b);
	gfx.drawRectangle(x + indent, x - indent + gridSize, y - indent - 2*gridSize, y + indent - gridSize, r, g, b);
	gfx.drawRectangle(x + indent - gridSize, x - indent + 2 * gridSize, y + indent - 3 * gridSize, y - indent - 2 * gridSize, r, g, b);
}
void Game::drawAirplaneLeft(int x, int y, int r, int g, int b)
{
	x = baseX + x*gridSize;
	y = baseY + y*gridSize;
	gfx.drawRectangle(x + indent, x + indent + gridSize, y + indent, y - indent + gridSize, r, g, b);
	gfx.drawRectangle(x + indent + gridSize, x - indent + 2*gridSize, y + indent - 2 * gridSize, y - indent + 3 * gridSize, r, g, b);
	gfx.drawRectangle(x - indent + 2 * gridSize, x + indent + 3 * gridSize, y + indent, y - indent + gridSize, r, g, b);
	gfx.drawRectangle(x + indent + 3 * gridSize, x - indent + 4 * gridSize, y + indent - gridSize, y - indent + 2 * gridSize, r, g, b);
}
void Game::drawAirplanes()
{
	for (int hIndex = 0;hIndex < tableSize;hIndex++)
	{
		for (int vIndex = 0; vIndex < tableSize; vIndex++)
		{
			if (p1field[hIndex][vIndex][0] == UP_AIRPLANE_HEAD)
			{
				drawAirplaneUp(hIndex, vIndex, 0, 100, 0);
			}
			else if (p1field[hIndex][vIndex][0] == DOWN_AIRPLANE_HEAD)
			{
				drawAirplaneDown(hIndex, vIndex, 0, 100, 0);
			}
			else if (p1field[hIndex][vIndex][0] == LEFT_AIRPLANE_HEAD)
			{
				drawAirplaneLeft(hIndex, vIndex, 0, 100, 0);
			}
			else if (p1field[hIndex][vIndex][0] == RIGHT_AIRPLANE_HEAD)
			{
				drawAirplaneRight(hIndex, vIndex, 0, 100, 0);
			}
		}
	}
}
void Game::airplanePositioning()
{
	switch (airplane_direction)
	{
	case UP:
		drawAirplaneUp(airplaneX, airplaneY, 0, 100, 0);
		break;
	case RIGHT:
		drawAirplaneRight(airplaneX, airplaneY, 0, 100, 0);
		break;
	case DOWN:
		drawAirplaneDown(airplaneX, airplaneY, 0, 100, 0);
		break;
	case LEFT:
		drawAirplaneLeft(airplaneX, airplaneY, 0, 100, 0);
		break;
	default:
		break;
	}
}
void Game::drawOverlap()
{
	for (int i = 0;i <= tableSize-1;i++)
	{
		for (int j = 0;j <= tableSize-1;j++)
		{
			if (getFieldState(i, j, 1) == OVERLAP)
			{
				gfx.drawRectangle(baseX + indent + i*gridSize, baseX - indent + (i + 1)*gridSize, baseY + indent + j*gridSize, baseY - indent + (j + 1)*gridSize, 255, 0, 0);
			}
		}
	}
}

void Game::drawCursor(int x, int y, int r, int g, int b)
{
	int secondGridStart = baseX + tableSize*gridSize + gridDistance;
	gfx.drawLine(secondGridStart + x*gridSize + indent, secondGridStart + (x + 1)*gridSize - indent, baseY + y*gridSize + indent, baseY + y*gridSize + indent, r, g, b);
	gfx.drawLine(secondGridStart + (x + 1)*gridSize - indent, secondGridStart + (x + 1)*gridSize - indent, baseY + y*gridSize + indent, baseY + (y + 1)*gridSize - indent, r, g, b);
	gfx.drawLine(secondGridStart + x*gridSize + indent, secondGridStart + (x + 1)*gridSize - indent, baseY + (y + 1)*gridSize - indent, baseY + (y + 1)*gridSize - indent, r, g, b);
	gfx.drawLine(secondGridStart + x*gridSize + indent, secondGridStart + x*gridSize + indent, baseY + y*gridSize + indent, baseY + (y + 1)*gridSize - indent, r, g, b);
}
void Game::drawShot(int x, int y, int r, int g, int b)
{
	int secondGridStart = baseX + tableSize*gridSize + gridDistance;
	gfx.drawLine(secondGridStart + indent + x*gridSize, secondGridStart - indent + (x+1)*gridSize, baseY + indent + y*gridSize, baseY - indent + (y + 1)*gridSize, r, g, b);
	gfx.drawLine(secondGridStart + indent + x*gridSize, secondGridStart - indent + (x + 1)*gridSize, baseY - indent + (y + 1)*gridSize, baseY + indent + y*gridSize, r, g, b);
}
void Game::drawHeadShot(int x, int y, int r, int g, int b)
{
	int secondGridStart = baseX + tableSize*gridSize + gridDistance;
	gfx.drawLine(secondGridStart + indent + x*gridSize, secondGridStart - indent + (x + 1)*gridSize, baseY + indent + y*gridSize, baseY - indent + (y + 1)*gridSize, r, g, b);
	gfx.drawLine(secondGridStart + indent + x*gridSize, secondGridStart - indent + (x + 1)*gridSize, baseY - indent + (y + 1)*gridSize, baseY + indent + y*gridSize, r, g, b);

	gfx.drawLine(secondGridStart + x*gridSize + indent, secondGridStart + (x + 1)*gridSize - indent, baseY + y*gridSize + indent, baseY + y*gridSize + indent, r, g, b);
	gfx.drawLine(secondGridStart + (x + 1)*gridSize - indent, secondGridStart + (x + 1)*gridSize - indent, baseY + y*gridSize + indent, baseY + (y + 1)*gridSize - indent, r, g, b);
	gfx.drawLine(secondGridStart + x*gridSize + indent, secondGridStart + (x + 1)*gridSize - indent, baseY + (y + 1)*gridSize - indent, baseY + (y + 1)*gridSize - indent, r, g, b);
	gfx.drawLine(secondGridStart + x*gridSize + indent, secondGridStart + x*gridSize + indent, baseY + y*gridSize + indent, baseY + (y + 1)*gridSize - indent, r, g, b);

}
void Game::drawMiss(int x, int y, int r, int g, int b)
{
	int secondGridStart = baseX + tableSize*gridSize + gridDistance;
	gfx.drawCircle(secondGridStart + x*gridSize + gridSize / 2, baseY + y*gridSize + gridSize / 2, gridSize / 3 - indent, r, g, b);
}

void Game::airplaneMovement()
{
	if (!keyPressedLastFrame)
	{
		if (kbd.DownIsPressed())
		{
			keyPressedLastFrame = true;
			airplaneY++;
			switch (airplane_direction)
			{
				case UP:
					if (airplaneY > tableSize - 4)
					{
						airplaneY = tableSize - 4;
					}
					break;
				case RIGHT:
					if (airplaneY > tableSize - 3)
					{
						airplaneY = tableSize - 3;
					}
					break;
				case DOWN:
					if (airplaneY > tableSize - 1)
					{
						airplaneY = tableSize - 1;
					}
					break;
				case LEFT:
					if (airplaneY > tableSize - 3)
					{
						airplaneY = tableSize - 3;
					}
					break;
			}
		}
		if (kbd.UpIsPressed())
		{
			keyPressedLastFrame = true;
			airplaneY--;
			switch (airplane_direction)
			{
			case UP:
				if (airplaneY < 0)
				{
					airplaneY = 0;
				}
				break;
			case RIGHT:
				if (airplaneY < 2)
				{
					airplaneY = 2;
				}
				break;
			case DOWN:
				if (airplaneY < 3)
				{
					airplaneY = 3;
				}
				break;
			case LEFT:
				if (airplaneY < 2)
				{
					airplaneY = 2;
				}
				break;
			}
		}
		if (kbd.RightIsPressed())
		{
			keyPressedLastFrame = true;
			airplaneX++;
			switch (airplane_direction)
			{
			case UP:
				if (airplaneX > tableSize - 3)
				{
					airplaneX = tableSize - 3;
				}
				break;
			case RIGHT:
				if (airplaneX > tableSize - 1)
				{
					airplaneX = tableSize - 1;
				}
				break;
			case DOWN:
				if (airplaneX > tableSize - 3)
				{
					airplaneX = tableSize - 3;
				}
				break;
			case LEFT:
				if (airplaneX > tableSize - 4)
				{
					airplaneX = tableSize - 4;
				}
				break;
			}
		}
		if (kbd.LeftIsPressed())
		{
			keyPressedLastFrame = true;
			airplaneX--;
			switch (airplane_direction)
			{
			case UP:
				if (airplaneX  < 2)
				{
					airplaneX = 2;
				}
				break;
			case RIGHT:
				if (airplaneX  < 3)
				{
					airplaneX = 3;
				}
				break;
			case DOWN:
				if (airplaneX  < 2)
				{
					airplaneX = 2;
				}
				break;
			case LEFT:
				if (airplaneX  < 0)
				{
					airplaneX = 0;
				}
				break;
			}
		}
	}
	else if (!(kbd.DownIsPressed() || kbd.UpIsPressed() || kbd.LeftIsPressed() || kbd.RightIsPressed()))
	{
		keyPressedLastFrame = false;
	}
}
void Game::airplaneRotation()
{
	if (!rotatedLastFrame)
	{
		if (kbd.SpaceIsPressed())
		{
			rotatedLastFrame = true;
			switch (airplane_direction)
			{
			case UP:
				airplane_direction = RIGHT;
				if (airplaneY > tableSize - 3)
				{
					airplaneY = tableSize - 3;
				}
				if (airplaneX  < 3)
				{
					airplaneX = 3;
				}
				if (airplaneY < 2)
				{
					airplaneY = 2;
				}
				break;
			case RIGHT:
				airplane_direction = DOWN;
				if (airplaneY < 3)
				{
					airplaneY = 3;
				}
				if (airplaneX > tableSize - 3)
				{
					airplaneX = tableSize - 3;
				}
				if (airplaneX  < 2)
				{
					airplaneX = 2;
				}
				break;
			case DOWN:
				airplane_direction = LEFT;
				if (airplaneY > tableSize - 3)
				{
					airplaneY = tableSize - 3;
				}
				if (airplaneY < 2)
				{
					airplaneY = 2;
				}
				if (airplaneX > tableSize - 4)
				{
					airplaneX = tableSize - 4;
				}
				break;
			case LEFT:
				airplane_direction = UP;
				if (airplaneY > tableSize - 4)
				{
					airplaneY = tableSize - 4;
				}
				if (airplaneX > tableSize - 3)
				{
					airplaneX = tableSize - 3;
				}
				if (airplaneX  < 2)
				{
					airplaneX = 2;
				}
				break;
			}
		}
	}
	else if (!(kbd.SpaceIsPressed()))
	{
		rotatedLastFrame = false;
	}
}
void Game::airplaneOverlap()
{
	for (int i = 0;i <= tableSize-1;i++)
	{
		for (int j = 0;j <= tableSize-1;j++)
		{
			setFieldState(i, j, 1, EMPTY);
		}
	}
	switch (airplane_direction)
	{
	case UP:
		for (int i = 0; i <= 9;i++)
		{
			if (overlapCheck(airplaneX + up_airplane_body_locations[i][0], airplaneY + up_airplane_body_locations[i][1])) 
			{ 
				setFieldState(airplaneX + up_airplane_body_locations[i][0], airplaneY + up_airplane_body_locations[i][1], 1, OVERLAP);
			}
		}
		break;
	case RIGHT:
		for (int i = 0; i <= 9;i++)
		{
			if (overlapCheck(airplaneX + right_airplane_body_locations[i][0], airplaneY + right_airplane_body_locations[i][1])) 
			{ 
				setFieldState(airplaneX + right_airplane_body_locations[i][0], airplaneY + right_airplane_body_locations[i][1], 1, OVERLAP);
			}
		}
		break;
	case DOWN:
		for (int i = 0; i <= 9;i++)
		{
			if (overlapCheck(airplaneX + down_airplane_body_locations[i][0], airplaneY + down_airplane_body_locations[i][1])) 
			{ 
				setFieldState(airplaneX + down_airplane_body_locations[i][0], airplaneY + down_airplane_body_locations[i][1], 1, OVERLAP);
			}
		}
		break;
	case LEFT:
		for (int i = 0; i <= 9;i++)
		{
			if (overlapCheck(airplaneX + left_airplane_body_locations[i][0], airplaneY + left_airplane_body_locations[i][1])) 
			{ 
				setFieldState(airplaneX + left_airplane_body_locations[i][0], airplaneY + left_airplane_body_locations[i][1], 1, OVERLAP);
			}
		}
		break;
	}
	Overlap = false;
	for (int i = 0;i <= tableSize - 1;i++)
	{
		for (int j = 0;j <= tableSize - 1;j++)
		{
			if (getFieldState(i, j, 1) == OVERLAP)
			{
				Overlap = true;
				break;
			}
		}
	}
}
bool Game::overlapCheck(int x, int y)
{
	if (getFieldState(x, y, 0) == AIRPLANE_BODY || getFieldState(x, y, 0) == UP_AIRPLANE_HEAD || getFieldState(x, y, 0) == RIGHT_AIRPLANE_HEAD
		|| getFieldState(x, y, 0) == DOWN_AIRPLANE_HEAD	|| getFieldState(x, y, 0) == LEFT_AIRPLANE_HEAD)
	{
		return true;
	}
	else return false;
}
void Game::airpalnePalcement()
{
	if (!placedLastFrame)
	{
		if (kbd.EnterIsPressed())
		{
			placedLastFrame = true;
			p1Airplanes++;
			if (p1field[airplaneX][airplaneY][0] == EMPTY && !(Overlap))
			{
				switch (airplane_direction)
				{
				case UP:
					setFieldState(airplaneX, airplaneY, 0, UP_AIRPLANE_HEAD);
					for (int i = 1; i <= 9;i++)
					{
						setFieldState(airplaneX + up_airplane_body_locations[i][0], airplaneY + up_airplane_body_locations[i][1], 0, AIRPLANE_BODY);
					}
					break;
				case RIGHT:
					setFieldState(airplaneX, airplaneY, 0, RIGHT_AIRPLANE_HEAD);
					for (int i = 1; i <= 9;i++)
					{
						setFieldState(airplaneX + right_airplane_body_locations[i][0], airplaneY + right_airplane_body_locations[i][1], 0, AIRPLANE_BODY);
					}
					break;
				case DOWN:
					setFieldState(airplaneX, airplaneY, 0, DOWN_AIRPLANE_HEAD);
					for (int i = 1; i <= 9;i++)
					{
						setFieldState(airplaneX + down_airplane_body_locations[i][0], airplaneY + down_airplane_body_locations[i][1], 0, AIRPLANE_BODY);
					}
					break;
				case LEFT:
					setFieldState(airplaneX, airplaneY, 0, LEFT_AIRPLANE_HEAD);
					for (int i = 1; i <= 9;i++)
					{
						setFieldState(airplaneX + left_airplane_body_locations[i][0], airplaneY + left_airplane_body_locations[i][1], 0, AIRPLANE_BODY);
					}
					break;
				}
			}
			else
			{
				p1Airplanes--;
				deleteAirplane();
			}
		}
	}
	else if (!kbd.EnterIsPressed())
	{
		placedLastFrame = false;
	}
}
void Game::deleteAirplane()
{
	switch (airplane_direction)
	{
	case UP:
		if (getFieldState(airplaneX, airplaneY, 0) == UP_AIRPLANE_HEAD)
		{
			for (int i = 0;i <= 9;i++)
			{
				setFieldState(airplaneX + up_airplane_body_locations[i][0], airplaneY + up_airplane_body_locations[i][1], 0, EMPTY);
			}
		}
		break;
	case RIGHT:
		if (getFieldState(airplaneX, airplaneY, 0) == RIGHT_AIRPLANE_HEAD)
		{
			for (int i = 0;i <= 9;i++)
			{
				setFieldState(airplaneX + right_airplane_body_locations[i][0], airplaneY + right_airplane_body_locations[i][1], 0, EMPTY);
			}
		}
		break;
	case DOWN:
		if (getFieldState(airplaneX, airplaneY, 0) == DOWN_AIRPLANE_HEAD)
		{
			for (int i = 0;i <= 9;i++)
			{
				setFieldState(airplaneX + down_airplane_body_locations[i][0], airplaneY + down_airplane_body_locations[i][1], 0, EMPTY);
			}
		}
		break;
	case LEFT:
		if (getFieldState(airplaneX, airplaneY, 0) == LEFT_AIRPLANE_HEAD)
		{
			for (int i = 0;i <= 9;i++)
			{
				setFieldState(airplaneX + left_airplane_body_locations[i][0], airplaneY + left_airplane_body_locations[i][1], 0, EMPTY);
			}
		}
		break;
	}
}
void Game::setFieldState(int hIndex, int vIndex, int layer, fieldState state)
{
	if (player == 1)
	{
		p1field[hIndex][vIndex][layer] = state;
	}
	else if (player == 2)
	{
		p2field[hIndex][vIndex][layer] = state;
	}
}
void Game::setFieldState(int player, int hIndex, int vIndex, int layer, fieldState state)
{
	if (player == 1)
	{
		p1field[hIndex][vIndex][layer] = state;
	}
	else if (player == 2)
	{
		p2field[hIndex][vIndex][layer] = state;
	}
}
Game::fieldState Game::getFieldState(int hIndex, int vIndex, int layer)
{
	if (player == 1)
	{
		return p1field[hIndex][vIndex][layer];
	}
	else if (player == 2)
	{
		return p2field[hIndex][vIndex][layer];
	}
}
Game::fieldState Game::getFieldState(int player, int hIndex, int vIndex, int layer)
{
	if (player == 1)
	{
		return p1field[hIndex][vIndex][layer];
	}
	else if (player == 2)
	{
		return p2field[hIndex][vIndex][layer];
	}
}

void Game::AIairplaneRotation()
{
	int aDirection = rand() % 4;
	switch (aDirection)
	{
	case 0:
		airplane_direction =  UP;
		break;
	case 1:
		airplane_direction =  RIGHT;
		break;
	case 2:
		airplane_direction =  DOWN;
		break;
	case 3:
		airplane_direction =  LEFT;
		break;
	}
}
void Game::AIairplanePositioning()
{
	AIairplaneRotation();
	switch (airplane_direction)
	{
	case UP:
		airplaneX = 2 + rand() % 11;
		airplaneY = rand() % 12;
		airplaneOverlap();
		if (!(Overlap))
		{
			p2Airplanes++;
			setFieldState(airplaneX, airplaneY, 0, UP_AIRPLANE_HEAD);
			for (int i = 1; i <= 9;i++)
			{
				setFieldState(airplaneX + up_airplane_body_locations[i][0], airplaneY + up_airplane_body_locations[i][1], 0, AIRPLANE_BODY);
			}
		}
		break;
	case RIGHT:
		airplaneX = 3 + rand() % 12;
		airplaneY = 2 + rand() % 11;
		airplaneOverlap();
		if (!(Overlap))
		{
			p2Airplanes++;
			setFieldState(airplaneX, airplaneY, 0, RIGHT_AIRPLANE_HEAD);
			for (int i = 1; i <= 9;i++)
			{
				setFieldState(airplaneX + right_airplane_body_locations[i][0], airplaneY + right_airplane_body_locations[i][1], 0, AIRPLANE_BODY);
			}
		}
		break;
	case DOWN:
		airplaneX = 2 + rand() % 11;
		airplaneY = 3 + rand() % 12;
		airplaneOverlap();
		if (!(Overlap))
		{
			p2Airplanes++;
			setFieldState(airplaneX, airplaneY, 0, DOWN_AIRPLANE_HEAD);
			for (int i = 1; i <= 9;i++)
			{
				setFieldState(airplaneX + down_airplane_body_locations[i][0], airplaneY + down_airplane_body_locations[i][1], 0, AIRPLANE_BODY);
			}
		}
		break;
	case LEFT:
		airplaneX = rand() % 12;
		airplaneY = 2 + rand() % 11;
		airplaneOverlap();
		if (!(Overlap))
		{
			p2Airplanes++;
			setFieldState(airplaneX, airplaneY, 0, LEFT_AIRPLANE_HEAD);
			for (int i = 1; i <= 9;i++)
			{
				setFieldState(airplaneX + left_airplane_body_locations[i][0], airplaneY + left_airplane_body_locations[i][1], 0, AIRPLANE_BODY);
			}
		}
		break;
	}
}

void Game::cursorMovement()
{
	if (!keyPressedLastFrame)
	{
		if (kbd.DownIsPressed())
		{
			keyPressedLastFrame = true;
			cursorY++;
			if (cursorY > tableSize - 1)
			{
				cursorY = tableSize - 1;
			}
		}
		if (kbd.UpIsPressed())
		{
			keyPressedLastFrame = true;
			cursorY--;
			if (cursorY < 0)
			{
				cursorY = 0;
			}
		}
		if (kbd.RightIsPressed())
		{
			keyPressedLastFrame = true;
			cursorX++;
			if (cursorX > tableSize - 1)
			{
				cursorX = tableSize - 1;
			}
		}
		if (kbd.LeftIsPressed())
		{
			keyPressedLastFrame = true;
			cursorX--;
			if (cursorX  < 0)
			{
				cursorX = 0;
			}
		}
	}
	else if (!(kbd.DownIsPressed() || kbd.UpIsPressed() || kbd.LeftIsPressed() || kbd.RightIsPressed()))
	{
		keyPressedLastFrame = false;
	}
}
void Game::attack()
{
	if (!firedLastFrame)
	{
		if (kbd.EnterIsPressed())
		{
			p1Attacked = true;
			firedLastFrame = true;
			if (getFieldState(2, cursorX, cursorY, 0) == UP_AIRPLANE_HEAD || getFieldState(2, cursorX, cursorY, 0) == RIGHT_AIRPLANE_HEAD
				|| getFieldState(2, cursorX, cursorY, 0) == DOWN_AIRPLANE_HEAD || getFieldState(2, cursorX, cursorY, 0) == LEFT_AIRPLANE_HEAD)
			{
				setFieldState(2, cursorX, cursorY, 1, DESTROYED_AIRPLANE_HEAD);
				p1AirplanesDestroyed++;
			}
			else if (getFieldState(2, cursorX, cursorY, 0) == AIRPLANE_BODY)
			{
				setFieldState(2, cursorX, cursorY, 1, DESTROYED_AIRPLANE_BODY);
			}
			else
			{
				setFieldState(2, cursorX, cursorY, 1, MISS);
			}
		}
	}
	else if (!kbd.EnterIsPressed())
	{
		firedLastFrame = false;
	}
}
void Game::radar()
{
	for (int i = 0;i <= tableSize - 1;i++)
	{
		for (int j = 0;j <= tableSize - 1; j++)
		{
			if (getFieldState(2, i, j, 1) == DESTROYED_AIRPLANE_HEAD)
			{
				drawHeadShot(i, j, 255, 0, 0);
			}
			else if (getFieldState(2, i, j, 1) == DESTROYED_AIRPLANE_BODY)
			{
				drawShot(i, j, 255, 0, 0);
			}
			else if (getFieldState(2, i, j, 1) == MISS)
			{
				drawMiss(i, j, 0, 0, 255);
			}
		}
	}
}

void Game::ComposeFrame()
{
	drawGrid();
	drawAirplanes();
	switch (gamestate)
	{
	case P1_AIRPLANE_PLACEMENT:
		airplanePositioning();
		drawOverlap();
		break;
	case P2_AIRPLANE_PLACEMENT:
		break;
	case P1_ATTACK:
		radar();
		drawCursor(cursorX, cursorY, 0, 0, 255);
		break;
	case P2_ATTACK:
		break;
	case P1_WIN:
		radar();
		break;
	case P2_WIN:
		radar();
		break;
	}
}