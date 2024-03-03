#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <unordered_map>

class Car {
public:
    std::string make;
    std::string model;
    int year;
    double dailyRate;
    bool rented;

    Car(std::string mk, std::string mdl, int yr, double rate) 
        : make(mk), model(mdl), year(yr), dailyRate(rate), rented(false) {}

    void displayDetails() const {
        std::cout << make << " " << model << " (" << year << ") - $" 
                  << dailyRate << " per day - " << (rented ? "Rented" : "Available") << "\n";
    }
};

class RentalSystem {
private:
    std::vector<Car> cars;
    std::unordered_map<int, std::vector<Car>> customerRentals;

    void displayAvailableCars() const {
        for (int i = 0; i < cars.size(); ++i) {
            if (!cars[i].rented) {
                std::cout << i + 1 << ". ";
                cars[i].displayDetails();
            }
        }
    }

    bool isValidIndex(int index) const {
        return index >= 0 && index < cars.size() && !cars[index].rented;
    }

    void rentACar(int customerId) {
        std::cout << "Select the car you wish to rent by number:\n";
        displayAvailableCars();
        int choice;
        std::cin >> choice;
        --choice; // Adjust for 0-based index
        if (isValidIndex(choice)) {
            cars[choice].rented = true;
            customerRentals[customerId].push_back(cars[choice]);
            std::cout << "You have successfully rented the " << cars[choice].make << " " << cars[choice].model << ".\n";
        } else {
            std::cout << "Invalid selection or car not available.\n";
        }
    }

    void returnACar(int customerId) {
        if (customerRentals.find(customerId) == customerRentals.end() || customerRentals[customerId].empty()) {
            std::cout << "You have no cars rented.\n";
            return;
        }

        std::cout << "Your rented cars:\n";
        for (int i = 0; i < customerRentals[customerId].size(); ++i) {
            std::cout << i + 1 << ". ";
            customerRentals[customerId][i].displayDetails();
        }

        std::cout << "Select the car you wish to return by number:\n";
        int choice;
        std::cin >> choice;
        --choice; // Adjust for 0-based index

        if (choice >= 0 && choice < customerRentals[customerId].size()) {
            for (auto &car : cars) {
                if (car.make == customerRentals[customerId][choice].make && 
                    car.model == customerRentals[customerId][choice].model &&
                    car.year == customerRentals[customerId][choice].year) {
                    car.rented = false;
                    break;
                }
            }

            std::cout << "You have successfully returned the " << customerRentals[customerId][choice].make 
                      << " " << customerRentals[customerId][choice].model << ".\n";
            customerRentals[customerId].erase(customerRentals[customerId].begin() + choice);
        } else {
            std::cout << "Invalid selection.\n";
        }
    }

public:
    RentalSystem() {
      cars.emplace_back("Toyota", "Camry", 2020, 50.00);
      cars.emplace_back("Honda", "Accord Hybrid", 2024, 79.00);
      cars.emplace_back("Nissan", "Altima", 2020, 60.00);
      cars.emplace_back("Ford", "Mustang", 2024, 145.00);
      cars.emplace_back("Chevrolet", "Tahoe", 2023, 100.00);
      cars.emplace_back("Kia", "EV9", 2024, 98.00);
      cars.emplace_back("Hyundai", "Sonata", 2022, 80.00);
      cars.emplace_back("Volkswagen", "Passat", 2018, 65.00);
      cars.emplace_back("Subaru", "Legacy", 2020, 90.00);
      cars.emplace_back("Mazda", "Mazda6", 2020, 85.00);
      cars.emplace_back("Buick", "Regal", 2019, 90.00);
      cars.emplace_back("Ferrari", "Roma Spider", 2024, 250.00);
    }

    void run() {
        while (true) {
            std::cout << "Welcome to David's Car Rental" << std::endl;
            std::cout << "1. Rent a car\n2. Return a car\n3. Exit\nChoose an option: ";
            int choice;
            std::cin >> choice;

            if (choice == 1) {
                std::cout << "Enter your customer ID: ";
                int customerId;
                std::cin >> customerId;
                rentACar(customerId);
            } else if (choice == 2) {
                std::cout << "Enter your customer ID: ";
                int customerId;
                std::cin >> customerId;
                returnACar(customerId);
            } else if (choice == 3) {
                break;
            } else {
                std::cout << "Invalid option, please try again.\n";
            }

            // Clear input buffer
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
};

int main() {
    RentalSystem system;
    system.run();
    return 0;
}
