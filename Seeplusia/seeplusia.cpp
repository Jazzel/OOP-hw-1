#include "seeplusia.hpp"
#include "mover.hpp"

// ! Use "Better Comments" extension for better comments :)
// * ----------------- Defining variables

// ? Apples and crystals are initialized with default values of 20 and 0
int applesLeft = 20, nCrystalsFound = 0;

// ? Default state for game is running and for wizard is Enchanted Forest
string gameState = "Running";
string currentState = "Enchanted Forest";

// ? Checks for diamond picks at 4 different places
// ! These check will be marked false if the player picks the respected diamond
bool diamondAtMarshOfUndead = true;
bool diamondAtWerewolfHill = true;
bool diamondAtSwampsOfDespair = true;
bool diamondAtEistenTunnel = true;

/**
 * ? Function for updating wizard state/location
 * ? --------------------------------------------------------------------------------
 * * Take argument (string) updateState and assigns the value to currentState declared above
 * ? --------------------------------------------------------------------------------
*/
void updateWizardState(string _updateState)
{
	currentState = _updateState;
}

/**
 * ? Function for updating game state
 * ? --------------------------------------------------------------------------------
 * * Take argument (string) updateState and assigns the value to gameState declared above
 * ? --------------------------------------------------------------------------------
 * @param _updateState
*/
void updateGameState(string _updateState)
{
	gameState = _updateState;
}

// ? Game over function
/** 
 * ? --------------------------------------------------------------------------------
 * * Checks if apples are 0 or less than 0 then the game is over 
 * * so updateGameState function is called with the argument "Lost"
 * ? --------------------------------------------------------------------------------
*/
void checkApples()
{
	if (applesLeft <= 0)
	{
		updateGameState("Lost");
	}
}

// ? Another shape for checkApples function
// ! Used ploymorphism
/**
 * ? --------------------------------------------------------------------------------
 * * Function now takes one integer parameter and checks if the user can go to next location or not.
 * * it checks if after moving to next place or the apples after subtraction becomes less 0 or less than o
 * * then the game is over
 * * else the game continues
 * * again here updateGameState function was called.
 * ? --------------------------------------------------------------------------------
 * @param applesToSubtract
 */
bool checkApples(int applesToSubtract)
{
	if ((applesLeft - applesToSubtract) <= 0)
	{
		updateGameState("Lost");
		return false;
	}
	return true;
}

/**
 * ? Game lost function at Sands of Quick
 * ? --------------------------------------------------------------------------------
 * * 1 apple is subtracted until the no of apples become 0
 * ? --------------------------------------------------------------------------------
 */
void gameLostAtSandsOfQuick()
{
	while (applesLeft != 0)
	{
		// TODO: sleep for 0.1 second
		applesLeft -= 1;
	}
}

/**
 * ? Apples decrement function
 * ? --------------------------------------------------------------------------------
 * * subtract apples from the applesLeft counter
 * * checkApples is called here if after subtraction the no. of apples
 * * becomes  
 * ? --------------------------------------------------------------------------------
 * @param applesToSubtract
 */
void applesDecrement(int applesToSubtract)
{
	if (checkApples(applesToSubtract))
	{
		applesLeft -= applesToSubtract;
	}
}

/**
 * ? Pick diamonds function
 * ? --------------------------------------------------------------------------------
 * * picks diamonds and increment the nCrystalsFound counter
 * * also each place has a bool check if that diamond is picked the check is marked false
 * * so if the check is only true user can pick the diamond making the user pick only 1 time.
 * ? --------------------------------------------------------------------------------
 * @param currentState 
 */
void pickDiamonds(string currentState)
{

	if (currentState == "Marsh of Undead" && diamondAtMarshOfUndead)
	{
		diamondAtMarshOfUndead = false;
		nCrystalsFound++;
	}
	else if (currentState == "Werewolf Hill" && diamondAtWerewolfHill)
	{
		diamondAtWerewolfHill = false;
		nCrystalsFound++;
	}
	else if (currentState == "Swamps of Despair" && diamondAtSwampsOfDespair)
	{
		diamondAtSwampsOfDespair = false;
		nCrystalsFound++;
	}
	else if (currentState == "Eisten Tunnel" && diamondAtEistenTunnel)
	{
		diamondAtEistenTunnel = false;
		nCrystalsFound++;
	}
	else
	{
		cout << "Diamond already connected from " << currentState << endl;
	}
}

/**
 * ? bonus apples function
 * ? --------------------------------------------------------------------------------
 * * add given apples to current apples counter 
 * ? --------------------------------------------------------------------------------
 * @param _addApples 
 */
void bonusApples(int _addApples)
{
	applesLeft += _addApples;
}

/**
 * ? Reset state function 
 * ? --------------------------------------------------------------------------------
 * * will reset wizard state and game state to default
 * * default states: Wizard -- Enchanted Forest && Game -- Running  
 * * resets the diamond checks and also the apples and crystal counters
 * ? --------------------------------------------------------------------------------
 */
void reset()
{
	updateWizardState("Enchanted Forest");
	applesLeft = 20;
	nCrystalsFound = 0;
	diamondAtMarshOfUndead = true;
	diamondAtWerewolfHill = true;
	diamondAtSwampsOfDespair = true;
	diamondAtEistenTunnel = true;
	updateGameState("Running");
}

/**
 * ? makeMove function
 * ? --------------------------------------------------------------------------------
 * * Takes direction as a parameter - East, South, West, North, Reset
 * * - Decides how many apples need to be subtracted according to direction and currentWizard state
 * *   using applesDecrement function 
 * * - Changes wizard state to next location 
 * *   using updateWizardState function 
 * * - Update game state to Lost, Running & Won according to conditions
 * *   using updateGameState function
 * * - Extra special functions are called at different times 
 * *   including -- gameLostAtSandsOfQuick, bonusApples, reset, pickDiamonds
 * ? --------------------------------------------------------------------------------
 * ! - 4 special functions are called - moveEast, moveWest moveNorth, moveSouth
 * !   which moves the wizard according to direction given.
 * @param direction 
 */
void makeMove(string direction)
{
	// * checking if game is in running state
	if (gameState == "Running")
	{
		// * checking directions of user input
		if (direction == "East")
		{
			// * check currentState and calling functions according to needs.
			if (currentState == "Enchanted Forest")
			{
				// * default function calls - defined before function call
				moveEast();
				updateWizardState("Sands of Quick");
				applesDecrement(1);
				// * gameLostAtSandsOfQuick function call to game over
				// * as the user cannot move in any direction now
				gameLostAtSandsOfQuick();
			}
			else if (currentState == "Marsh of Undead")
			{
				// * default function calls - defined before function call
				moveEast();
				updateWizardState("Wampire Cave");
				applesDecrement(1);
			}
			else if (currentState == "Wampire Cave")
			{
				// * default function calls - defined before function call
				moveEast();
				updateWizardState("Marsh of Undead");
				applesDecrement(1);
				// * pickDiamond call to pick diamond at Marsh of Undead
				// * the check for Marsh of Undead will be marked false
				pickDiamonds(currentState);
			}
			else if (currentState == "Swamps of Despair")
			{
				// * default function calls - defined before function call
				moveEast();
				updateWizardState("Wampire Cave");
				applesDecrement(1);
			}
			else if (currentState == "Elvin Waterfall")
			{
				// * default function calls - defined before function call
				moveEast();
				updateWizardState("Werewolf Hill");
				applesDecrement(2);
				// * pickDiamond call to pick diamond at Werewolf Hill
				// * the check for Werewolf Hill will be marked false
				pickDiamonds(currentState);
			}
			else if (currentState == "Eisten Tunnel")
			{
				// * default function calls - defined before function call
				moveEast();
				updateWizardState("Elvin Waterfall");
				applesDecrement(2);
			}
			else
			{
				// * printing error message for testing
				cout << "Cannot move East !" << endl;
			}
			// * Checking number of apples after every move so the game state can be update
			// * if required !
			checkApples();
		}
		else if (direction == "West")
		{
			if (currentState == "Marsh of Undead")
			{
				// * default function calls - defined before function call
				moveWest();
				updateWizardState("Wampire Cave");
				applesDecrement(1);
			}
			else if (currentState == "Apples Orchard")
			{
				// * default function calls - defined before function call
				moveWest();
				updateWizardState("Werewolf Hill");
				applesDecrement(1);
				// * pickDiamond call to pick diamond at Werewolf Hill
				// * the check for Werewolf Hill will be marked false
				pickDiamonds(currentState);
			}
			else if (currentState == "Wampire Cave")
			{
				// * default function calls - defined before function call
				moveWest();
				updateWizardState("Swamps of Despair");
				applesDecrement(1);
				// * pickDiamond call to pick diamond at Swamps of Despair
				// * the check for Swamps of Despair will be marked false
				pickDiamonds(currentState);
			}
			else if (currentState == "Werewolf Hill")
			{
				// * default function calls - defined before function call
				moveWest();
				updateWizardState("Elvin Waterfall");
				applesDecrement(2);
			}
			else if (currentState == "Elvin Waterfall")
			{
				// * default function calls - defined before function call
				moveWest();
				updateWizardState("Eisten Tunnel");
				applesDecrement(2);
				// * pickDiamond call to pick diamond at Eisten Tunnel
				// * the check for Eisten Tunnel will be marked false
				pickDiamonds(currentState);
			}
			else if (currentState == "Bridge of Death")
			{
				// ! number of crystals are required to be 4 else the game will be lost
				if (nCrystalsFound == 4)
				{
					// * default function calls - defined before function call
					moveWest();
					updateWizardState("Wizard's Castle");
					applesDecrement(5);
					// * updateGameState function call to update game state to Won
					// * The game will be won as both condtions for diamonds and apples is true
					updateGameState("Won");
				}
				else
				{
					// * updateGameState function call to update game state to Lost
					updateGameState("Lost");
				}
			}
			else
			{
				// * printing error message for testing
				cout << "Cannot move West !" << endl;
			}
			// * Checking number of apples after every move so the game state can be update
			// * if required !
			checkApples();
		}
		else if (direction == "North")
		{
			if (currentState == "Wampire Cave")
			{
				// * default function calls - defined before function call
				moveNorth();
				updateWizardState("Enchanted Forest");
				applesDecrement(3);
			}
			else if (currentState == "Werewolf Hill")
			{
				// * default function calls - defined before function call
				moveNorth();
				updateWizardState("Wampire Cave");
				applesDecrement(3);
			}
			else if (currentState == "Swamps of Despair")
			{
				// * default function calls - defined before function call
				moveNorth();
				updateWizardState("Bridge of Death");
				applesDecrement(1);
			}
			else if (currentState == "Eisten Tunnel")
			{
				// ! number of crystals are required to be 3 or greator than 3
				// ! else the game will be lost
				// ~!
				if (nCrystalsFound >= 3)
				{
					// * default function calls - defined before function call
					moveNorth();
					moveNorth();
					updateWizardState("Wizard's Castle");
					applesDecrement(10);

					// * updateGameState function call to update game state to Won
					// * The game will be won as both condtions for diamonds and apples is true
					updateGameState("Won");
				}
				else
				{
					// * updateGameState function call to update game state to Lost
					updateGameState("Lost");
				}
			}
			else
			{
				// * printing error message for testing
				cout << "Cannot move North !" << endl;
			}
			// * Checking number of apples after every move so the game state can be update
			// * if required !
			checkApples();
		}
		else if (direction == "South")
		{
			if (currentState == "Enchanted Forest")
			{
				// * default function calls - defined before function call
				moveSouth();
				updateWizardState("Wampire Cave");
				applesDecrement(3);
			}
			else if (currentState == "Wampire Cave")
			{
				// * default function calls - defined before function call
				moveSouth();
				updateWizardState("Werewolf Hill");
				applesDecrement(3);
				// * pickDiamond call to pick diamond at Werewolf Hill
				// * the check for Werewolf Hill will be marked false
				pickDiamonds(currentState);
			}
			else if (currentState == "Marsh of Undead")
			{
				// * default function calls - defined before function call
				moveSouth();
				updateWizardState("Apples Orchard");
				applesDecrement(1);
				// * bonusApples call -- to add apples in current apples counter
				bonusApples(6);
			}
			else
			{
				// * printing error message for testing
				cout << "Cannot move South !" << endl;
			}
			// * Checking number of apples after every move so the game state can be update
			// * if required !
			checkApples();
		}
		else if (direction == "Reset")
		{
			// * Reset Function call to reset the game.
			reset();
		}
	}
	// * Calling checkApples again just for two step verification for game state !
	checkApples();
}
