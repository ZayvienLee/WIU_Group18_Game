#include <iostream>
#include <cctype>
#include <conio.h>

#include "GameManager.h"
#include "StoryManager.h"

// The libraries to check for memory leaks
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "Item.h"

// This is needed to 'clear' the console
static void clearConsole()
{
    // \033[H moves the cursor to the top-left corner
   // \033[2J clears the entire screen
    std::cout << "\033[H\033[2J" << std::flush;
}

int main(void)
{
    char choice;
    bool menuRunning = true;

    while (menuRunning) {

        std::cout << "========================================" << std::endl
                  << "          WELCOME TO DEAD HOUR          " << std::endl
                  << "========================================" << std::endl
                  << std::endl;

        std::cout << "1. Start Game" << std::endl
            << "2. Legend" << std::endl
            << "Enter your choice: ";

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
            game.getMap().spawnRandomItems(15); // Stating the number of items to include

            std::cout << "========================================" << std::endl;
            std::cout << "    POST-APOCALYPTIC SURVIVAL GAME      " << std::endl;
            std::cout << "========================================" << std::endl;
            std::cout << "Controls:" << std::endl;
            std::cout << "  [W/A/S/D] - Move Up / Left / Down / Right" << std::endl;
            std::cout << "  [E]       - Interact / Enter Door / Pick Up Item" << std::endl;
            std::cout << "  [I]       - Open Inventory" << std::endl;
            std::cout << "  [U]       - Use / Consume Item" << std::endl;
            std::cout << "  [Q]       - Drop Item" << std::endl;
            std::cout << "  [X]       - Quit Game" << std::endl;
            std::cout << "========================================" << std::endl << std::endl;

            std::cin.ignore();
            std::cin.get();

            clearConsole();

            while (isRunning)
            {

                // Render map viewport with camera centered on Player
                game.render(15, 9);


                std::cout << std::endl
                    << "Hunger: " << game.getPlayer()->getHunger()
                    << "/100 | Thirst: " << game.getPlayer()->getThirst()
                    << "/100 | Quests Done: " << game.getStoryManager().getCompletedQuestsCount() << "/3" << std::endl; // For Quest UI

                // Prompt user input
                std::cout << "Enter command (W/A/S/D/E/I/U/Q/X): ";

                // Get the input from the player
                input = _getch();
                input = static_cast<char>(toupper(input));

                clearConsole();

                std::cout << std::endl << "Action executed: " << input << std::endl;

                // Process commands
                if (input == 'X')
                {
                    isRunning = false;
                    std::cout << std::endl << "Exiting survival game..." << std::endl;
                }
                else if (input == 'W' || input == 'A' || input == 'S' || input == 'D')
                {
                    game.handlePlayerInput(input);
                }
                else if (input == 'E')
                {
                    // Check door interaction first; if not entering,
                    // Attempt pickup, depending on location
                    int pX = game.getLocationStatus() ? game.getPlayer()->getIndoorX() : game.getPlayer()->getOutdoorX();
                    int pY = game.getLocationStatus() ? game.getPlayer()->getIndoorY() : game.getPlayer()->getOutdoorY();

                    if (!game.getLocationStatus() && game.getMap().isEntrance(pX, pY))
                    {
                        game.handlePlayerInput('E');
                    }
                    else
                    {
                        game.handleItemPickup();
                    }
                }
                else if (input == 'I')
                {
                    game.getPlayer()->showInventory();

                    std::cin.ignore();
                    std::cin.get();

                    clearConsole();
                }
                else if (input == 'U')
                {
                    game.getPlayer()->showInventory();
                    std::cout << std::endl << "Enter item slot number to USE (1-10): ";
                    int slot;
                    if (std::cin >> slot)
                    {
                        Item* target = game.getPlayer()->getItemByNumber(slot);
                        if (target != nullptr)
                        {
                            target->consume(*(game.getPlayer()));
                            target->setQuantity(target->getQuantity() - 1); // Used one item

                            
                            if (target->getQuantity() > 0)
                            {
                                std::cout << "[USED] Consumed one instance of Item successfully!" << std::endl;
                            }
                            else if (target->getQuantity() <= 0)
                            {
                                game.getPlayer()->removeItem(target, slot);
                                delete target; // Clean memory after single-use consumption

                                std::cout << "[ALL USED] All instances of Item have been completely consumed." << std::endl;
                            }
                        }
                    }

                    std::cin.ignore();
                    std::cin.get();

                    clearConsole();

                }
                else if (input == 'Q')
                {
                    game.getPlayer()->showInventory();
                    std::cout << std::endl << "Enter item slot number to DROP (1-" << game.getPlayer()->getInventoryCapacity() << "): ";
                    int slot;
                    if (std::cin >> slot)
                    {
                        game.handleItemDrop(slot);
                    }

                    std::cin.ignore();
                    std::cin.get();

                    clearConsole();
                }
                else
                {
                    std::cout << "[INVALID] Input not recognized." << std::endl;
                }

                std::cout << std::endl;
            }

            menuRunning = false;
        }

        else if (choice == '2') {

            std::cout << std::endl
                    << "P - Player"
                    << "Z - Zombie" << std::endl
                    << "A - Apartment / Starting Point"
                    << "S - Supermarket" << std::endl
                    << "H - Hospital" << std::endl
                    << "PS - Police Station" << std::endl
                    << "C - School" << std::endl
                    << "G - Gas Station" << std::endl
                    << "F - Safe House" << std::endl
                    << "M - Military Base" << std::endl
                    << "E - Evacuation Point" << std::endl
                    << "f - Food" << std::endl
                    << "w - Water" << std::endl
                    << "m - Medicine" << std::endl
                    << "a - Ammunition" << std::endl
                    << "g - Gun / Firearm" << std::endl
                    << "k - Knife" << std::endl
                    << "i - Iris / NPC" << std::endl
                    << "h - Hank (Police Officer) / NPC" << std::endl
                    << "d - Dr. Chen / NPC" << std::endl;

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

    // THe lines of code to dump memory leaks
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    _CrtDumpMemoryLeaks();

    return 0;
}