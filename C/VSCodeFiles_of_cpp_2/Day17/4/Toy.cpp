#include "Toy.hpp"
#include <iostream>

using namespace std;

Toy::Toy(string name_, ToyType type_) : name(move(name_)), type(type_) {}

string Toy::name_str() const
{
    return name;
}

string Toy::type_str() const
{
    switch (type)
    {
    case ToyType::Cat:
        return "Cat";
    case ToyType::Dog:
        return "Dog";
    case ToyType::Robot:
        return "Robot";
    default:
        return "Unknown";
    }
}

CatToy::CatToy(const string &n) : Toy(n, ToyType::Cat) {}

void CatToy::special() const { cout << name << " (Cat): purr and meow\n"; }

DogToy::DogToy(const string &n) : Toy(n, ToyType::Dog) {}

void DogToy::special() const { cout << name << " (Dog): bark and wag tail\n"; }

RobotToy::RobotToy(const string &n) : Toy(n, ToyType::Robot) {}

void RobotToy::special() const { cout << name << " (Robot): dance and light up\n"; }

void ToyFactory::add_cat(const string &name) { toys.emplace_back(make_unique<CatToy>(name)); }

void ToyFactory::add_dog(const string &name) { toys.emplace_back(make_unique<DogToy>(name)); }

void ToyFactory::add_robot(const string &name) { toys.emplace_back(make_unique<RobotToy>(name)); }

void ToyFactory::display_all() const
{
    for (const auto &t : toys)
    {
        cout << t->name_str() << ", " << t->type_str() << ": ";
        t->special();
    }
}
