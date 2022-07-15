/*
** EPITECH PROJECT, 2022
** arcade_2048
** File description:
** main
*/

#include <iostream>
#include "Game/Core.hpp"
#include "Error/Error.hpp"

int main(int ac, char **av)
{
    try {
        Game::Core(ac, av);
    } catch (Error &e) {
        std::cerr << e.what() << std::endl;
        return (84);
    }
    return (0);
}