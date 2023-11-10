#include <iostream>

using namespace std;

struct TrainJourney {
    int availableSeats;
    int passengers;
    int totalMoney;
};

const int MAX_SEATS = 80;
const int GROUP_DISCOUNT_THRESHOLD = 10;
const int TICKET_PRICE = 25;

TrainJourney upTrains[4];
TrainJourney downTrains[4];

void initializeDay() {
    for (int i = 0; i < 4; ++i) {
        upTrains[i] = {MAX_SEATS, 0, 0};
        downTrains[i] = {MAX_SEATS, 0, 0};
    }
}

void displayScreen() {
    cout << "\tTrain Times\t\tAvailable Seats\n\n";
    for (int i = 0; i < 4; ++i) {
    	cout << i + 1 ;
        cout << "\tUp at " << i * 2 + 9 << ":00\t\t" << upTrains[i].availableSeats;
        if (upTrains[i].availableSeats == 0) {
            cout << " (Closed)";
        }
        cout << endl;

        cout << "\tDown at " << i * 2 + 10 << ":00\t\t" << downTrains[i].availableSeats;
        if (downTrains[i].availableSeats == 0) {
            cout << " (Closed)";
        }
        cout << endl;
    }
    cout << "-----------------------------------------\n";
}

void purchaseTickets(int trainIndex, int numTickets) {
    TrainJourney& currentTrain = (trainIndex % 2 == 0) ? upTrains[trainIndex / 2] : downTrains[trainIndex / 2];

    if (currentTrain.availableSeats >= numTickets) {
        currentTrain.passengers += numTickets;

        // Apply group discount
        int numGroups = numTickets / GROUP_DISCOUNT_THRESHOLD;
        currentTrain.totalMoney += (numTickets - numGroups) * TICKET_PRICE;

        currentTrain.availableSeats -= numTickets;

        cout << "Tickets purchased successfully!\n";
    } else {
        cout << "Not enough seats available for the selected train.\n";
    }
}

void endOfDay() {
    int totalPassengers = 0;
    int totalMoney = 0;
    int maxPassengers = 0;
    int maxPassengersIndex = 0;

    for (int i = 0; i < 4; ++i) {
        totalPassengers += upTrains[i].passengers + downTrains[i].passengers;
        totalMoney += upTrains[i].totalMoney + downTrains[i].totalMoney;

        if (upTrains[i].passengers > maxPassengers) {
            maxPassengers = upTrains[i].passengers;
            maxPassengersIndex = i;
        }

        if (downTrains[i].passengers > maxPassengers) {
            maxPassengers = downTrains[i].passengers;
            maxPassengersIndex = i;
        }
    }

    cout << "End of the day summary:\n";
    cout << "Total passengers: " << totalPassengers << endl;
    cout << "Total money collected: $" << totalMoney << endl;

    cout << "Train journey with the most passengers today:\n";
    cout << "Up at " << maxPassengersIndex * 2 + 9 << ":00 - " << upTrains[maxPassengersIndex].passengers << " passengers\n";
    cout << "Down at " << maxPassengersIndex * 2 + 10 << ":00 - " << downTrains[maxPassengersIndex].passengers << " passengers\n";
}

int main() {
    initializeDay();
    cout<<"\tELECTRIC MOUNTAINS RAILWAYS\n\n";

    while (true) {
        displayScreen();

        cout << "\tEnter the train index (1-8) and the number of tickets to purchase (0 to exit): ";
        int trainIndex, numTickets;
        cin >> trainIndex;

        if (trainIndex == 0) {
            break;
        }

        cout << "\tEnter the number of tickets to purchase: ";
        cin >> numTickets;

        if (trainIndex >= 1 && trainIndex <= 8 && numTickets >= 0) {
            purchaseTickets(trainIndex - 1, numTickets);
        } else {
            cout << "Invalid input. Please try again.\n";
        }
    }

    endOfDay();

    return 0;
}

