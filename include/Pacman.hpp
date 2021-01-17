/*
** EPITECH PROJECT, 2020
** B-MAT-500-PAR-5-1-304pacman-rayann.folleas
** File description:
** Pacman
*/

#ifndef PACMAN_HPP_
#define PACMAN_HPP_

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>

typedef struct vector3 {
    int x;
    int y;
    int l;
}vector3;

class Pacman {
    public:
        Pacman();
        ~Pacman();

        int init(int ac, char **av);
        int processMap();
        bool checkCell(std::vector<vector3> &tmp, int x, int y, int l);
        void runAlgo();
        void display();

        int checkMap();
    private:
        bool found = false;
        vector3 _fantomPos;
        vector3 _pacmanPos;
        std::vector<std::string> _mapTab;
        std::string _map;
        char c1;
        char c2;
};

#endif /* !PACMAN_HPP_ */