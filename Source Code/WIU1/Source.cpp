#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <iostream>
#include <cctype>
#include <conio.h>
#include "GameManager.h"
#include "StoryManager.h"
#include "GameObject.h"
#include "Item.h"
#include "Weapon.h"

// This is needed to 'clear' the console
static void clearConsole()
{
    // \033[H moves the cursor to the top-left corner
    // \033[2J clears the entire screen
    std::cout << "\033[H\033[2J" << std::flush;
}

static void instructionControls()
{
    std::cout << "Controls:" << std::endl;
    std::cout << "  [W/A/S/D] - Move Up / Left / Down / Right" << std::endl;
    std::cout << "  [E]       - Interact / Enter Door / Pick Up Item" << std::endl;
    std::cout << "  [I]       - Open Inventory" << std::endl;
    std::cout << "  [G]       - Open Quest Menu" << std::endl;
    std::cout << "  [F]       - Attack" << std::endl;
    std::cout << "  [U]       - Use / Consume Item / Equip Weapon" << std::endl;
    std::cout << "  [Q]       - Drop Item" << std::endl;
    std::cout << "  [T]       - Controls & Legend" << std::endl;
    std::cout << "  [O]       - Unequip Weapon" << std::endl;
    std::cout << "  [X]       - Quit Game" << std::endl;
    std::cout << "========================================" << std::endl << std::endl;

    std::cout << std::endl;
}

static void showLegend()
{
    std::cout << std::endl
        << "Legend (1/2): " << std::endl
        << "  " << Colour::GREEN << "P" << Colour::RESET << " - Player" << std::endl
        << "  " << Colour::BOLD_RED << "Z" << Colour::RESET << " - Zombie" << std::endl
        << "  A - Apartment (Starting Point)" << std::endl
        << "  S - Supermarket" << std::endl
        << "  H - Hospital" << std::endl
        << "  PS - Police Station" << std::endl
        << "  C - School" << std::endl
        << "  G - Gas Station" << std::endl
        << "  F - Safe House" << std::endl
        << "  M - Military Base" << std::endl
        << "  E - Evacuation Point" << std::endl
        << "  _ - Outdoor Walkable Path" << std::endl
        << "  . - Outdoor: Building Entrance / Inddor: Inddor Walkable Path" << std::endl
        << "  # - Building Wall / Furniture" << std::endl
        << "  X - Inaccessable Building Area" << std::endl;

    std::cout << std::endl << "Press Enter for next page" << std::endl;
        
    std::cin.clear();
    std::cin.get();

    clearConsole();

    std::cout << std::endl
        << "Legend (2/2): " << std::endl
        << "  " << Colour::GREEN << "f" << Colour::RESET << " - Food" << std::endl
        << "  " << Colour::BLUE << "w" << Colour::RESET << " - Water" << std::endl
        << "  " << Colour::CYAN << "m" << Colour::RESET << " - Medicine" << std::endl
        << "  " << Colour::YELLOW << "a" << Colour::RESET << " - Ammunition" << std::endl
        << "  " << Colour::MAGENTA << "g" << Colour::RESET << " - Gun / Firearm" << std::endl
        << "  " << Colour::MAGENTA << "k" << Colour::RESET << " - Knife" << std::endl
        << "  " << Colour::BOLD_MAGENTA << "t" << Colour::RESET << " - Temozolomide" << std::endl
        << "  " << Colour::BOLD_MAGENTA << "p" << Colour::RESET << " - Toolbox Parts" << std::endl
        << "  " << Colour::BOLD_CYAN << "K" << Colour::RESET << " - Key Card" << std::endl
        << "  " << Colour::BOLD_CYAN << "A" << Colour::RESET << " - Access Card" << std::endl
        << "  " << Colour::CYAN << "i" << Colour::RESET << " - NPC Iris" << std::endl
        << "  " << Colour::CYAN << "h" << Colour::RESET << " - NPC Hank (Police Officer)" << std::endl
        << "  " << Colour::CYAN << "t" << Colour::RESET << " - NPC Timothy" << std::endl
        << "  " << Colour::CYAN << "d" << Colour::RESET << " - NPC Dr. Chen" << std::endl
        << "  " << Colour::CYAN << "n" << Colour::RESET << " - NPC Marco" << std::endl
        << "  " << Colour::CYAN << "j" << Colour::RESET << " - NPC Captain Reyes" << std::endl
        << "  " << Colour::CYAN << "q" << Colour::RESET << " - NPC Marissa" << std::endl;

    std::cout << std::endl;
}

int main(void)
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    char choice;
    bool menuRunning = true;

    while (menuRunning) {

        std::cout << R"(
                         ______   _______  _______  ______              _______           _______
                        (  __  \ (  ____ \(  ___  )(  __  \   |\     /|(  ___  )|\     /|(  ____ )
                        | (  \  )| (    \/| (   ) || (  \  )  | )   ( || (   ) || )   ( || (    )|
                        | |   ) || (__    | (___) || |   ) |  | (___) || |   | || |   | || (____)|
                        | |   | ||  __)   |  ___  || |   | |  |  ___  || |   | || |   | ||     __)
                        | |   ) || (      | (   ) || |   ) |  | (   ) || |   | || |   | || (\ (
                        | (__/  )| (____/\| )   ( || (__/  )  | )   ( || (___) || (___) || ) \ \__
                        (______/ (_______/|/     \|(______/   |/     \|(_______)(_______)|/   \__/)"

            << std::endl << std::endl;

        std::cout
            << "                                                      1. Start Game" << std::endl
            << "                                                      2. Legend" << std::endl << std::endl
            << "                                                      Enter your choice: ";

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
            game.getMap().generateRandomLayout(300, 20); // Stating the number of obstacles and items to include
            game.getMap().randomiseLocationLayouts(0.10f, 0.04f); // This is based on the density of the location (area)
            game.getMap().spawnRandomZombies(35);

            instructionControls();

            std::cin.clear();
            std::cin.get();

            clearConsole();

            // The starting line for the game
            std::cout << "Alex: Haven-7. That's my only shot at salvation and freedom. I better start making my move." << std::endl;

            while (isRunning)
            {

                // Render map viewport with camera centered on Player
                game.render(15, 9);


                std::cout
                    << std::endl
                    << Colour::BOLD_RED << "Health: " << game.getPlayer()->getHealth() << "/" << game.getPlayer()->getMaxHealth() << Colour::RESET << " | "
                    << Colour::BOLD_GREEN << "Hunger: " << game.getPlayer()->getHunger() << "/100" << Colour::RESET << " | "
                    << Colour::BOLD_BLUE << "Thirst: " << game.getPlayer()->getThirst() << "/100" << Colour::RESET << " | "
                    << Colour::BOLD_YELLOW << "Quests Done: " << game.getStoryManager().getCompletedQuestsCount() << "/5" << Colour::RESET << std::endl // For Quest UI
                    << Colour::BOLD_MAGENTA << "Total Zombies Killed: " << game.getStoryManager().getZombiesKilled() << Colour::RESET << std::endl
                    << Colour::BOLD_YELLOW << "Ammunition: " << game.getPlayer()->getAmmoCount() << Colour::RESET << std::endl;

                // Prompt user input
                std::cout << "Enter command (W/A/S/D/E/I/G/F/U/Q/T/O/X): ";

                // Get the input from the player
                input = _getch();
                input = static_cast<char>(toupper(input));

                // Process commands
                if (input == 'X')
                {
                    isRunning = false;
                    std::cout << std::endl << "Exiting survival game..." << std::endl;
                }
                else if (input == 'W' || input == 'A' || input == 'S' || input == 'D')
                {
                    clearConsole();

                    game.handlePlayerInput(input);
                    game.checkGroundItemInspection();
                    game.checkNPCInspection();
                }
                else if (input == 'E')
                {

                    clearConsole();

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

                    game.interactWithNPC();
                }
                else if (input == 'I')
                {
                    clearConsole();

                    game.getPlayer()->showInventory();

                    std::cout << "Press Enter to return..." << std::endl;

                    std::cin.clear();
                    std::cin.get();

                    clearConsole();
                }
                else if (input == 'F')
                {
                    std::cout << "[ATTACK] Choose which direction to attack (W/A/S/D): " << std::endl;
                    char attackInput = _getch();

                    attackInput = static_cast<char>(toupper(attackInput));

                    clearConsole();

                    if (attackInput == 'W' || attackInput == 'A' || attackInput == 'S' || attackInput == 'D')
                    {
                        game.handlePlayerAttack(attackInput);
                    }
                    else
                    {
                        std::cout << "[INVALID] Attack Input not recognized." << std::endl;
                    }
                }
                else if (input == 'U')
                {
                    clearConsole();

                    game.getPlayer()->showInventory();
                    std::cout << std::endl << "Enter item slot number to USE / EQUIP (1-" << game.getPlayer()->getInventoryCapacity() << "): ";
                    int slot;
                    if (std::cin >> slot)
                    {
                        Item* target = game.getPlayer()->getItemByNumber(slot);
                        if (target != nullptr)
                        {
                            if (!target->isConsumable())
                            {
                                if (Weapon* weaponTarget = dynamic_cast<Weapon*>(target))
                                {
                                    game.getPlayer()->removeItem(weaponTarget, slot);
                                    game.getPlayer()->equipWeapon(weaponTarget);

                                    std::cout << "[EQUIPPED] " << weaponTarget->getName() << std::endl;
                                }
                                else
                                {
                                    std::cout << "[ITEM] " << target->getName() << " can't be used this way." << std::endl;
                                }
                            }
                            else
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
                        else
                        {
                            std::cout << "[NO ITEM] No Item exists in this slot." << std::endl;
                        }
                    }

                    std::cout << "Press Enter to return..." << std::endl;

                    std::cin.ignore();
                    std::cin.get();

                    clearConsole();

                }
                else if (input == 'Q')
                {
                    clearConsole();

                    game.getPlayer()->showInventory();
                    std::cout << std::endl << "Enter item slot number to DROP (1-" << game.getPlayer()->getInventoryCapacity() << "): ";
                    int slot;
                    if (std::cin >> slot)
                    {
                        game.handleItemDrop(slot);
                    }

                    std::cout << "Press Enter to return..." << std::endl;

                    std::cin.ignore();
                    std::cin.get();

                    clearConsole();
                }
                else if (input == 'T')
                {
                    clearConsole();

                    instructionControls();

                    std::cout << "Press Enter to see Legend..." << std::endl;

                    std::cin.clear();
                    std::cin.get();

                    clearConsole();

                    showLegend();

                    std::cout << "Press Enter to return..." << std::endl;

                    std::cin.clear();
                    std::cin.get();

                    clearConsole();
                }
                else if (input == 'O')
                {
                    clearConsole();

                    Weapon* weaponTarget = game.getPlayer()->getWeapon();

                    if (weaponTarget != nullptr)
                    {
                        if (game.getPlayer()->unequipWeapon()) {
                            std::cout << "[UNEQUIPPED] " << weaponTarget->getName() << " added to inventory!" << std::endl;
                        }
                        else {
                            std::cout << "[INVENTORY FULL] Could not unequip." << std::endl;
                        }
                    }
                }
                else if (input == 'G')
                {
                    clearConsole();

                    game.getStoryManager().showQuests();

                    std::cout << std::endl << "Press Enter to return..." << std::endl;

                    std::cin.clear();
                    std::cin.get();

                    clearConsole();
                }
                else
                {
                    clearConsole();

                    std::cout << "[INVALID] Input not recognized." << std::endl;
                }

                // Shows the action executed
                std::cout << std::endl << "Action executed: " << input << std::endl;

                std::cout << std::endl;

                /* End conditions */

                if (game.getHasWon())
                {
                    std::cout << std::endl
                        << "==========================================" << std::endl
                        << "   You made it out. Welcome to Haven-7.   " << std::endl
                        << "==========================================" << std::endl;

                    isRunning = false;
                }

                if (!game.getPlayer()->getIsAlive())
                {
                    std::cout << std::endl << "You have died. GAME OVER." << std::endl;
                    isRunning = false;
                }
            }

            menuRunning = false;
        }

        else if (choice == '2') {

            showLegend();

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

    _CrtDumpMemoryLeaks(); // Remove checks before submission

    return 0;
}