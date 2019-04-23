#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
class Node
{
private:
	//size and position of the node
	int xPos;
	int yPos;
	int height;
	int width;
	//Using SFML to draw the nodes
	sf::RectangleShape rect;
public:
	bool current = true;
	bool notPath = false;
	bool Path = true;
	//Constructor for settings the Node
	Node(int xPosIn, int yPosIn, int heightIn, int widthIn, int row, int column);
	//Draw function
	void DrawNode(sf::RenderTarget &target);
	int getX(); //returns the x position
	int getY(); //returns the y position 
				//sets the different colors depending on what the node is
	void setWall();
	void setPath();
	void setGoal();
	void setStart();
	void setOpen();
	void setClosed();
	void setCurrent(bool b);
	int lowerOutcome(const Node other) const; //boolean for sorting the lowest f cost 
	float f; //total cost of the node
	float g; //distance of current to start
	float h; //distance of current to goal 
	int parent;
	//function that handles the heuristics - Euclidean distance
	int score(float parentGScore, int currentX, int currentY, int goalX, int goalY)
	{
		// Calculate F score
		float dx, dy;

		g = parentGScore + 1.0f; // G is parent's G + 1
		dx = (float)(goalX - currentX);
		dy = (float)(goalY - currentY);
		//h = sqrt(dx * dx + dy * dy); // 1. H is Euclidean distance to goal

		//h = dx * dx + dy * dy; // 2. Euclidean no sqrt
		
		//D influences the score on 3rd (Manhattan) and 4th (Giagonal) heuristics. Its value is subject to change and gives different results.

		//float D = 1.0;  h = D * (abs(dx) + abs(dy)); //3. Manhattan, D==1 (minimum move cost)

		//float D = 1.0;  h = D * std::max(abs(dx), abs(dy)); //4. Diagonal, D==1 (minimum move cost)

		//5. Diagonal Shortcut -> begin
		float D;
		D = 1.0*(sqrt(2.0) - 1.0f);
		if (abs(dx) <= abs(dy))
			h = D * abs(dx) + abs(dy);
		else
			h = abs(dx) + D * abs(dy);
		//5. Diagonal Shortcut -> end

		//h = 0; //6. Dijkstra's algorithm

		//float D = 1.0;  h = D * (abs(dx) + abs(dy)); //7. A* and Manhattan heuristic for D>>1 e.g. D==10000.0 becomes the BFS algorithm
		f = g + h; // F is just G + H
		std::cout << "g=" << g << " h=" << h << " f=" << f << "\n";
		return f;
	}

	int row;
	int column;

	~Node();
};

