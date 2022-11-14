#ifndef ENEMY_TESTER
#define ENEMY_TESTER

#include "enemy.hpp"
#include <iostream>


int mainEnemyTest() {
Enemy enemy1(50, 10, 10);

std::cout << "Enemy HP: " << enemy1.GetHP() << ", speed: " << enemy1.GetSpeed() << ", value: " << enemy1.GetValue() << std::endl;

bool died = enemy1.TakeDamage(12);
std::cout << "Enemy HP: " << enemy1.GetHP() << ". Is it dead?: " << died << std::endl;

enemy1.TakeDamage(15);
died = enemy1.TakeDamage(6);
std::cout << "Enemy HP: " << enemy1.GetHP() << ". Is it dead?: " << died << std::endl;

died = enemy1.TakeDamage(48);
std::cout << "Enemy HP: " << enemy1.GetHP() << ". Is it dead?: " << died << std::endl;



return 0;
}

#endif