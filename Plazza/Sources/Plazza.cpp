/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** main function
*/

#include <thread>
#include "KitchenData.hpp"
#include "Abstractions/DataQueue.hpp"
#include "AKitchen.hpp"
#include "Plazza.hpp"
#include "Pizza.hpp"
#include "Reception.hpp"
#include "Abstractions/SharedData.hpp"
#include "Abstractions/Thread.hpp"
#include "PlazzaServerAPIManager.hpp"

int main(int ac, const char **av) {
    if (ac <= 3 || ac >= 6)
        return (84);
    plaz::Reception *reception = new plaz::Reception(av[1], av[2], av[3]);
    plaz::server::PlazzaServerAPIManager manager;

    manager.runApi(reception, (ac == 5) ? std::string(av[4]) : std::string(""));
    if (!reception->isServerMode()) {
        reception->receiveOrders();
    } else {
        std::cout << "Plazza launched in server mode..." << std::endl;
        reception->serverModeReception();

    }
    delete reception;
    return (0);
}