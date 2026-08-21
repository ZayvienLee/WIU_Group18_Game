#include <iostream>
#include <cctype>
#include <conio.h>

#include "GameManager.h"
#include "StoryManager.h"

// The libraries to check for memory leaks
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

// This is needed to clear the console
static void clearConsole()
{
    // \033[H moves the cursor to the top-left corner
   // \033[2J clears the entire screen
    std::cout << "\033[H\033[2J" << std::flush;
}

int main(void)
{
    {
        char choice;
        bool menuRunning = true;

        while (menuRunning) {

            std::cout << "========================================" << std::endl;
            std::cout << "          WELCOME TO DEAD HOUR          " << std::endl;
            std::cout << "========================================" << std::endl;
            std::cout << std::endl;

            std::cout << "1. Start Game" << std::endl;
            std::cout << "2. Legend" << std::endl;
            std::cout << "Enter your choice:";
            std::cin >> choice;

            clearConsole();

            if (choice == '1') {
                                                
                StoryManager story;
                std::cout << std::endl;

                story.storyIntro();
                std::cout << std::endl;
                std::cout << "Press Enter to start the game..." << std::endl;

                std::cin.ignore();
                std::cin.get();

                clearConsole();

                GameManager game;
                char input = ' ';
                bool isRunning = true;

                // Add the obstacles to the map
                game.getMap().generateRandomObstacles(30); // Stating the number of obstacles to include

                std::cout << "========================================" << std::endl;
                std::cout << "    POST-APOCALYPTIC SURVIVAL GAME      " << std::endl;
                std::cout << "========================================" << std::endl;
                std::cout << "Controls:" << std::endl;
                std::cout << "  [W/A/S/D] - Move Up / Left / Down / Right" << std::endl;
                std::cout << "  [E]       - Enter Building (on '.' entrance tile)" << std::endl;
                std::cout << "  [Q]       - Quit Game" << std::endl;
                std::cout << "========================================" << std::endl << std::endl;

                while (isRunning)
                {

                    // Render map viewport with camera centered on Player
                    game.render(15, 9);

                    // Prompt user input
                    std::cout << std::endl << "Enter command (W/A/S/D/E/Q): ";

                    // For Quest UI
                    std::cout << " Quests Done: " << game.getStoryManager().getCompletedQuestsCount() << "/3" << std::endl;

                    // Get the input from the player
                    input = _getch();
                    input = static_cast<char>(toupper(input));

                    clearConsole();

                    std::cout << std::endl << "Action: " << input << std::endl;

                    // Process commands
                    if (input == 'Q')
                    {
                        isRunning = false;
                        std::cout << std::endl << "Exiting survival game..." << std::endl;
                    }
                    else if (input == 'W' || input == 'A' || input == 'S' || input == 'D' || input == 'E')
                    {
                        game.handlePlayerInput(input);
                    }
                    else
                    {
                        std::cout << "[INVALID] Input not recognized. Use W, A, S, D, E, or Q." << std::endl;

                        std::cin.ignore();
                        std::cin.get();
                    }

                    std::cout << std::endl;
                }

                menuRunning = false;
            }

            else if (choice == '2') {

                std::cout << std::endl;
                std::cout << "P - Player" << std::endl;
                std::cout << "Z - Zombie" << std::endl;
                std::cout << "A - Apartment / Starting Point" << std::endl;
                std::cout << "S - Supermarket" << std::endl;
                std::cout << "H - Hospital" << std::endl;
                std::cout << "PS - Police Station" << std::endl;
                std::cout << "C - School" << std::endl;
                std::cout << "G - Gas Station" << std::endl;
                std::cout << "F - Safe House" << std::endl;
                std::cout << "M - Military Base" << std::endl;
                std::cout << "E - Evacuation Point" << std::endl;
                std::cout << "f - Food" << std::endl;
                std::cout << "w - Water" << std::endl;
                std::cout << "m - Medicine" << std::endl;
                std::cout << "a - Ammunition" << std::endl;
                std::cout << "g - Gun / Firearm" << std::endl;
                std::cout << "k - Knife" << std::endl;
                std::cout << "i - Iris / NPC" << std::endl;
                std::cout << "h - Hank (Police Officer) / NPC" << std::endl;
                std::cout << "d - Dr. Chen / NPC" << std::endl;

                std::cout << std::endl;

                std::cout << "Press Enter to exit back to main menu..." << std::endl;

                std::cin.ignore();
                std::cin.get();

                clearConsole();
            }
            else
            {
                std::cout << "Invalid choice! Pick either 1 or 2." << std::endl;
                std::cout << std::endl;

                std::cin.ignore();
                std::cin.get();

                clearConsole();
            }

        }
    }

    // THe lines of code to dump memory leaks
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    _CrtDumpMemoryLeaks();

    return 0;
}