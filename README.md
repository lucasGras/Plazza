# Plazza - EPITECH Project
###### Lucas Gras | Clément Tinarelli | Adrien Iacono

> The purpose of this project is to make you realize a simulation of a pizzeria, which is composed of the reception that accepts new commands, of several kitchens, themselves with several cooks, themselves cooking several pizzas.You will learn to deal with various problems, including load balancing, process and thread synchronization and communication.

## USAGE

To make the project:
```bash
$> make && ./plazza [multiplier] [cooks] [timer] [--enable-api | --server]
```

- `multiplier`: is a multiplier for the cooking time of the pizza.
- `timer`: is the number of cooks per kitchen.
- `timer`: is the time in milliseconds, used by the kitchen stock to replace ingredient.
- `--enable-api`: enable the plazza-api, use this flag when you are using the mobile client application or the GearVR mobile application.
- `--server`: run the plazza as a server, the pizza orders are now sended from the mobile application.

> You can't run the plazza with both flags !

To run unit tests:
```bash
$> make tests_run
```

> Note that the plazzaApi will certainly be shuted down after the end of the project, don't expect the flags to work properly.

## Examples

![mobileApplication](/resources/demo-mobile-application.jpg)
![mobileApplication2](/resources/demo-mobile-application-2.jpg)