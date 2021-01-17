/*
** EPITECH PROJECT, 2020
** B-MAT-500-PAR-5-1-304pacman-rayann.folleas
** File description:
** Pacman
*/

#include "Pacman.hpp"

Pacman::Pacman()
{
}

Pacman::~Pacman()
{
}

int strlen(char *str, char lim = '\0')
{
    int i = 0;
    while (str[i++]!=lim);
    return i - 1;
}

int strlen(std::string str, char lim = '\0')
{
    int i = 0;
    while (str.at(i++)!=lim);
    return i - 1;
}

int Pacman::init(int ac, char **av)
{
    if (ac != 4) {
        std::cout << "Usage: " << av[0] << "file c1 c2" << std::endl;
        return 84;
    }
    if (strlen(av[2]) != 1 || strlen(av[3]) != 1) {
        std::cout << "Usage: " << av[0] << "file c1 c2" << std::endl;
        return 84;
    }
    if (av[2] == av[3]) {
        std::cout << "c1 and c2 must be different" << std::endl;
        return 84;
    }
    if ((av[2][0] >= '0' && av[2][0] <= '9') || (av[3][0] >= '0' && av[3][0] <= '9')) {
        std::cout << "c1 and c2 can't be numbers" << std::endl;
        return 84;
    }
    this->c2 = av[2][0];
    this->c1 = av[3][0];
    std::ifstream t(av[1]);
    std::stringstream buffer;
    buffer << t.rdbuf();
    this->_map = buffer.str();
    if (checkMap() == 84)
        return 84;
    return 0;
}

int Pacman::checkMap()
{
    int pacmanCount = 0;
    int fantomCount = 0;

    if (this->_map.length() < 5)
        return 84;
    if (this->_map.find("\n\n") != std::string::npos)
        return 84;
    for (char c : this->_map) {
        if (c == 'P')
            pacmanCount++;
        if (c == 'F')
            fantomCount++;
        if (c != 'F' && c != 'P' && c != '0' && c != '1' && c != '\n')
            return 84;
    }
    if (pacmanCount != 1 || fantomCount != 1)
        return 84;
    return 0;
}

int Pacman::processMap()
{
    std::istringstream stream(this->_map);
    std::string line;
    int y = 0;
    int previousLineSize = strlen(this->_map, '\n');

    while (std::getline(stream, line)) {
        if (line.size() != previousLineSize)
            return 84;
        line.erase(std::remove(line.begin(), line.end(), '\n'), line.end());
        std::string tmp;
        for (int x = 0; x != line.length(); x++) {
            if (line.at(x) == 'F')
                this->_fantomPos = {x, y, 0};
            else if (line.at(x) == 'P')
                this->_pacmanPos = {x, y};
            if (line.at(x) == '0')
                tmp.push_back(c1);
            else if (line.at(x) == '1')
                tmp.push_back(c2);
            else
                tmp.push_back(line.at(x));
        }
        this->_mapTab.push_back(tmp);
        y++;
    }
    return 0;
}

void Pacman::runAlgo()
{
    std::vector<vector3> previous;
    previous.push_back(this->_fantomPos);

    while (previous.size() > 0) {
        std::vector<vector3> tmp;

        for (vector3 position : previous)
            if (checkCell(tmp, position.x,     position.y - 1,    position.l)   ||
                checkCell(tmp, position.x + 1, position.y,        position.l)   ||
                checkCell(tmp, position.x,     position.y + 1,    position.l)   ||
                checkCell(tmp, position.x - 1, position.y,        position.l)) {
                this->found = true;
                tmp.clear();
                break;
            }
        previous = tmp;
    }
}

void Pacman::display()
{
    for (std::string tmp : this->_mapTab)
        std::cout << tmp << std::endl;
}

bool Pacman::checkCell(std::vector<vector3> &tmp, int x, int y, int l)
{
    if (x < 0 || y < 0 || y >= this->_mapTab.size() || x >= this->_mapTab.at(y).length())
        return false;
    if (this->_mapTab.at(y).at(x) == 'P')
        return true;
    if (this->_mapTab.at(y).at(x) != c1)
        return false;
    std::string c = std::to_string((l+1) % 10);
    this->_mapTab.at(y).at(x) = c.at(0);
    tmp.push_back({x, y, l + 1});
    return false;
}