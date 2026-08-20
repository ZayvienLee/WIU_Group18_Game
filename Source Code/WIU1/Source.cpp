#include <iostream>
#include <cctype>
#include "GameManager.h"

int main(void)
{
    GameManager game;
    char input = ' ';
    bool isRunning = true;

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
        // 1. Render map viewport with camera centered on Player
        game.render(15, 9);

        // 2. Prompt user input
        std::cout << std::endl << "Enter command (W/A/S/D/E/Q): ";
        std::cin >> input;
        input = static_cast<char>(toupper(input));

        // 3. Process commands
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
        }

        std::cout << std::endl;
    }

    return 0;
}