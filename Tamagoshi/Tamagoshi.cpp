#include <iostream>
#include <thread>
#include <chrono>
#include <string>

class Animal {
private:
    std::string name;
    int happiness;
    int hunger;
    bool alive;

public:
    Animal(const std::string& animalName) : name(animalName), happiness(50), hunger(50), alive(true) {}

    void feed() {
        if (alive) {
            hunger -= 10;
            if (hunger < 0)
                hunger = 0;
            happiness += 5;
            if (happiness > 100)
                happiness = 100;
            std::cout << "Yummy! Hunger decreased and happiness increased." << std::endl;
        }
    }

    void love() {
        if (alive) {
            happiness += 10;
            if (happiness > 100)
                happiness = 100;
            std::cout << "Feeling loved! Happiness increased." << std::endl;
        }
    }

    void changeClothes() {
        if (alive) {
            happiness += 5;
            if (happiness > 100)
                happiness = 100;
            std::cout << "Looking stylish! Happiness increased." << std::endl;
        }
    }

    void updateStats() {
        if (alive) {
            happiness -= 2;
            hunger += 3;
            if (hunger >= 100 || happiness <= 0) {
                die();
            }
        }
    }

    void die() {
        alive = false;
        std::cout << "Oh no! The animal has died." << std::endl;
    }

    bool isAlive() const {
        return alive;
    }

    int getHappiness() const {
        return happiness;
    }

    int getHunger() const {
        return hunger;
    }

    std::string getName() const {
        return name;
    }

    void setName(const std::string& newName) {
        name = newName;
    }

    void printAsciiDrawing() const {
        std::cout << "   (\\__/)" << std::endl;
        std::cout << "   (o^.^)" << std::endl;
        std::cout << " z(_(\")(\")" << std::endl;
    }
};

int main() {
    std::string animalName;
    std::cout << "Enter the name of your animal: ";
    std::getline(std::cin, animalName);
    Animal animal(animalName);

    std::thread statsThread([&]() {
        while (animal.isAlive()) {
            std::this_thread::sleep_for(std::chrono::seconds(30));
            animal.updateStats();
        }
        });

    while (animal.isAlive()) {
        std::cout << "-----------------------" << std::endl;
        std::cout << "Name: " << animal.getName() << std::endl;
        std::cout << "Happiness: " << animal.getHappiness() << std::endl;
        std::cout << "Hunger: " << animal.getHunger() << std::endl;
        std::cout << "-----------------------" << std::endl;
        std::cout << "What would you like to do with " << animal.getName() << "?" << std::endl;
        std::cout << "1. Feed" << std::endl;
        std::cout << "2. Love" << std::endl;
        std::cout << "3. Change Clothes" << std::endl;
        std::cout << "4. Change Name" << std::endl;
        std::cout << "Enter your choice (1-4): ";

        int choice;
        std::cin >> choice;
        std::cin.ignore();  // Ignore the newline character after reading the choice

        switch (choice) {
        case 1:
            animal.feed();
            break;
        case 2:
            animal.love();
            break;
        case 3:
            animal.changeClothes();
            break;
        case 4: {
            std::string newName;
            std::cout << "Enter the new name for " << animal.getName() << ": ";
            std::getline(std::cin, newName);
            animal.setName(newName);
            std::cout << "Name changed to " << animal.getName() << "!" << std::endl;
            break;
        }
        default:
            std::cout << "Invalid choice. Try again." << std::endl;
            continue;
        }

        std::cout << std::endl;
        animal.printAsciiDrawing();
        std::cout << std::endl;
    }

    statsThread.join();

    return 0;
}

