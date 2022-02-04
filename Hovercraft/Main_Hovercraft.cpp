#include "Game_Hovecraft.h"

int main()
{	//Rezizable on --- if you want to change set it on false ---
	Game_Hovercraft Hovercraft("Hovercraft", 1980, 1080, 4, 4, true);


	//MAIN LOOP
	while (!Hovercraft.getWindowShouldClose())
	{
		//UPDATE INPUT ---
		Hovercraft.update();
		Hovercraft.render();
		
	}

	return 0;

}

