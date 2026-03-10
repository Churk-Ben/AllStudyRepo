#include "Toy.hpp"

int main() {
    ToyFactory factory;
    factory.add_cat("Fluffy");
    factory.add_dog("Buddy");
    factory.add_robot("R2");
    factory.display_all();
}

