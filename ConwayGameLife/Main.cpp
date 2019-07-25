#include "stdafx.h"
#include <SFML\Graphics.hpp>
#include <stdlib.h>

using namespace sf;

#define Alive 1
#define Dead 0

const int NUM_ROW = 256;

int static countNeightbours(int x, int y, int grid[][NUM_ROW]) {

	int sum = 0;

	for (int i = -1; i < 2; i++)
	{
		for (int j = -1; j < 2; j++)
		{

			int neighbourX = (i + x + NUM_ROW) % NUM_ROW;
			int neighbourY = (j + y + NUM_ROW) % NUM_ROW;

			sum += grid[neighbourX][neighbourY];
		}

	}


	return sum - grid[x][y];

}

void static randomize(int grid[][NUM_ROW]) {

	srand(time(NULL));

	for (int x = 0; x < NUM_ROW; x++)
	{
		for (int y = 0; y < NUM_ROW; y++)
		{

			grid[x][y] = rand() % 2;

		}

	}
}

int main()
{
	
	int oldGrid[NUM_ROW][NUM_ROW] = {};
	randomize(oldGrid);
	int newGrid[NUM_ROW][NUM_ROW];

	memcpy(newGrid, oldGrid, sizeof(newGrid));

	RenderWindow window(VideoMode(640, 640), "Conway's Game of Life");
	window.setPosition(Vector2i((1280 - window.getSize().y) / 2, 0));

	while (window.isOpen()) {

		Event event;

		while (window.pollEvent(event)) {

			if (event.type == Event::Closed) {

				window.close();

			}
			
		}

			window.clear(Color::White);


			//Drawing the array

			

			for (int x = 0; x < NUM_ROW; x++)
			{
				for (int y = 0; y < NUM_ROW; y++)
				{

					
					RectangleShape rect(Vector2f(((float)window.getSize().x / NUM_ROW), ((float)window.getSize().x / NUM_ROW)));
					rect.setPosition(x * rect.getSize().x, y * rect.getSize().y);

					if (newGrid[x][y]) {

						rect.setFillColor(Color(x , y, 255, 200));
					}
					else {
						rect.setFillColor(Color::Black);
						//rect.setFillColor(Color(x, y, 255, 200));
					}

					
					window.draw(rect);
				}

				
			}
			
			window.display();

			/*
			The rules of the simulation
			*/

			for (int x = 0; x < NUM_ROW; x++)
			{
				for (int y = 0; y < NUM_ROW; y++)
				{

					int sum = countNeightbours(x, y, oldGrid);

					if (oldGrid[x][y]) { //Alive

						newGrid[x][y] = (sum < 2 || sum >3) ? Dead : Alive;
					}
					else { //Dead

						newGrid[x][y] = sum == 3 ? Alive : Dead;

					}

				}

			}

			memcpy(oldGrid, newGrid, sizeof(oldGrid));

	}


	return 0;
}