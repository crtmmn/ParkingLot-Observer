#include <iostream>
#include <vector>
using namespace std;

class Observer {
public:
    virtual void update(int numEmptySpots) = 0;
};

class Subject {
public:
    virtual void registerObserver(Observer* observer) = 0;
    virtual void unregisterObserver(Observer* observer) = 0;
    virtual void notifyObservers() = 0;
};

class InfoDisplay : public Observer {
private:
    static int id;
    int infoDisplayID;
public:
    InfoDisplay() {
        id++;
        infoDisplayID = id;
    }
    void update(int numEmptySpots) override {
        std::cout << "Info Display: " << GetID() << " Number of empty spots available: " << numEmptySpots << std::endl;
    }
    int GetID() {
        return infoDisplayID;
    }
};
int InfoDisplay::id = 0;

class Car {
private:
    string licensePlate;
public:
    Car(string inplicensePlate) {
        licensePlate = inplicensePlate;
    }
    string GetLicensePlate() {
        return licensePlate;
    }
};

class ParkingLot : public Subject {
private:
    int numEmptySpots;
    std::vector<Observer*> observers;
public:
    ParkingLot() : numEmptySpots(0) {}
    void setNumEmptySpots(int numSpots) {
        numEmptySpots = numSpots;
        notifyObservers();
    }
    void registerObserver(Observer* observer) override {
        observers.push_back(observer);
    }
    void unregisterObserver(Observer* observer) override {
            auto it = std::find(observers.begin(), observers.end(),
                        observer);
        if (it != observers.end()) {
            observers.erase(it);
        } }
    void notifyObservers() override {
        for (Observer* observer : observers) {
            observer->update(numEmptySpots);
        }
    }
    bool Park(Car car) {
        if(numEmptySpots > 0) {
            cout << car.GetLicensePlate() << " parked correctly." << endl;
            setNumEmptySpots(numEmptySpots-1);
            return true;
        }
        else {
            cout << car.GetLicensePlate() << " don't have empty spot to park." << endl;
            return false;
        }
    }
    bool Exit(Car car) {
        numEmptySpots += 1;
        cout << car.GetLicensePlate() << " exited parking." << endl;
        notifyObservers();
        return true;
    }
    int GetEmptySpots() {
        return numEmptySpots;
    }
};

int main() {

    ParkingLot parkingLot;
    InfoDisplay infoDisplay;
    InfoDisplay infoDisplay2;
    InfoDisplay infoDisplay3;

    Car car1("LDZ1");
    Car car2("LDZ2");
    Car car3("LDZ3");
    Car car4("LDZ4");
    Car car5("LDZ5");

    parkingLot.registerObserver(&infoDisplay);
    parkingLot.registerObserver(&infoDisplay2);
    parkingLot.registerObserver(&infoDisplay3);
    parkingLot.setNumEmptySpots(3);

    cout << endl;
    parkingLot.Park(car1);
    cout << endl;
    parkingLot.Park(car2);
    cout << endl;
    parkingLot.Park(car3);
    cout << endl;
    parkingLot.Park(car4);
    cout << endl;
    parkingLot.Park(car5);
    cout << endl;
    parkingLot.Exit(car1);
    return 0;
}
