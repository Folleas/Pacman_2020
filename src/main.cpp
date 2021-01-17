/*
** EPITECH PROJECT, 2020
** B-MAT-500-PAR-5-1-304pacman-rayann.folleas
** File description:
** main
*/

#include "Pacman.hpp"

int main(int ac, char **av)
{
    Pacman engine;
    if (engine.init(ac, av) == 84)
        return 84;
    if (engine.processMap() == 84)
        return 84;
    engine.runAlgo();
    engine.display();
    return 0;
}