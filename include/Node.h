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
		h = sqrt(dx * dx + dy * dy); // 1. H is Euclidean distance to goal
		return h;

		//D influences the score on 3rd (Manhattan) and 4th (Giagonal) heuristics. Its value is subject to change and gives different results.
		//h = dx * dx + dy * dy; // 2. Euclidean no sqrt
		//float D = 1.0;  h = D * (abs(dx) + abs(dy)); //3. Manhattan, D==1 (minimum move cost)
		//float D = 1.0;  h = D * std::max(abs(dx), abs(dy)); //4. Diagonal, D==1 (minimum move cost)
		//5. Diagonal Shortcut -> begin
		float D = sqrt(2) - 1;
		if (dx <= dy)
			h = D * dx + dy;
		else
			h = dx + D * dy;
		//5. Diagonal Shortcut -> end
		//return h;

		//f = g + h; // F is just G + H
		//return f;
	}

	int row;
	int column;

	~Node();
};

