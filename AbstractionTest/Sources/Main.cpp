/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** test main for abstractions
*/

extern "C" {

#include <fcntl.h>
#include <unistd.h>

}

#include <chrono>
#include <thread>
#include <atomic>

#include "Abstractions/SharedData.hpp"
#include "Abstractions/Process.hpp"
#include "Abstractions/Thread.hpp"
#include "Abstractions/Channel.hpp"


static inline void sleepSecond(unsigned long s)
{
	std::this_thread::sleep_for(std::chrono::seconds(s));
}

using namespace plaz::abs;

void lel(Channel<int> &c)
{
	std::cout << c.pop() << std::endl;
	sleepSecond(2);
	std::cout << c.pop() << std::endl;
	std::cout << c.pop() << std::endl;
	std::cout << c.pop() << std::endl;
	std::cout << c.pop() << std::endl;
	std::cout << c.pop() << std::endl;
	std::cout << "kek" << std::endl;
}

int main(int, char * const [])
{
	Channel<int> c(3);
	//Premier paramètre le type de retour de la procédure passé, les reste type des arguments
	//TOUJOUR utilisé thread (wrapper de thread impl pour des raisons que je n'expliquerai pas ici)
	//Le thread est lancé dès que le constructeur est appellé
	Thread<void, Channel<int> &> t(lel, c);

	c.push(1);
	c.push(2);
	c.push(3);
	c.push(4);
	c.push(5);
	std::cout << "lel" << std::endl;
	sleepSecond(2);
	std::cout << "lul" << std::endl;
	c.push(6);
	std::cout << "kuk" << std::endl;

	//TOUJOUR join à la fin même si le thread est terminé (sauf si il a été cancel)
	//t.hasReturned() dit si la procédure passé en argument s'est correctement terminé ou non,
	// et si oui la valeur de retour si elle est récupérable est retourné par t.getReturnValue
	//t.isRunning() dit si la procédure est terminé. La différence avec t.hasReturned() se fait quand
	//le thread est cancel, la procédure n'aura pas forcément retourné mais ne sera plus en court
	//t.detach() j'ai pas compris comment ça marche mais ouais
	t.join();
	return 0;
}