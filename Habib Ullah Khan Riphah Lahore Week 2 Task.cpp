#include <iostream>
using namespace std;
#include <vector>

using namespace std;

const int TOTAL_COACHES = 6;
const int SEATS_PER_COACH = 80;
const int EXTRA_COACHES_LAST_TRAIN = 2;
const int RETURN_TICKET_COST = 25;

class TrainJourney {
	public:
		int passengers_booked;
		int money_collected;

		TrainJourney() : passengers_booked(0), money_collected(0) {}
};

int main() {
	const int NUM_JOURNEYS = 4;
	vector<TrainJourney> journeys_up(NUM_JOURNEYS);
	vector<TrainJourney> journeys_down(NUM_JOURNEYS);
	vector<int> available_seats(NUM_JOURNEYS, TOTAL_COACHES * SEATS_PER_COACH);

	int total_passengers = 0;
	int total_money = 0;
	int max_passengers = 0;
	int max_passengers_index = -1;
	int total_passengers_free = 0;

	while (true) {
		int passengers;
		cout << "Enter the number of passengers (1-480) or '0' to exit: ";
		cin >> passengers;
		cout<<"..........................................."<<endl;

		if (passengers == 0) {
			break;
		}

		if (!(1 <= passengers && passengers <= 480)) {
			cout << "Invalid number of passengers. Please enter a value between 1 and 480." << endl;
			continue;
		}

		int train_time;
		cout << "Enter the train time (9, 11, 13, 15): ";
		cin >> train_time;

		if (!(train_time == 9 || train_time == 11 || train_time == 13 || train_time == 15)) {
			cout << "Invalid train time. Please enter a valid time." << endl;
			cout<<"..........................................."<<endl;
			continue;
		}

		int return_train_time = (train_time + 1) % 24;
		int train_index = (train_time - 9) / 2;

		if (train_time == 11) {
			train_index = 1;
		}

		int ticket_choice;
		cout << "Do you want tickets for the journey up (1), down (2), or both (3)?: ";
		cin >> ticket_choice;

		int ticket_cost = 0;
		int free_tickets = 0;

		if (ticket_choice == 1 || ticket_choice == 3) {
			if (available_seats[train_index] >= passengers) {
				available_seats[train_index] -= passengers;
				int remaining_passengers = passengers;
				free_tickets = remaining_passengers / 10;
				remaining_passengers -= free_tickets;
				int single_journey_cost = remaining_passengers * RETURN_TICKET_COST;
				journeys_up[train_index].passengers_booked += passengers;
				journeys_up[train_index].money_collected += single_journey_cost;
				total_passengers += passengers;
				total_money += single_journey_cost;
				total_passengers_free += free_tickets;

				if (passengers > max_passengers) {
					max_passengers = passengers;
					max_passengers_index = train_index;
				}

				ticket_cost += single_journey_cost;
				cout << "Tickets booked for " << passengers << " passengers for the journey up." << endl;
				cout << free_tickets << " passengers travel for free on the journey up." << endl;
				cout<<"..........................................."<<endl;
			} else {
				cout << "Journey up is full! Tickets cannot be booked for this journey." << endl;
				cout<<"..........................................."<<endl;
			}
		}

		if (ticket_choice == 2 || ticket_choice == 3) {
			if (return_train_time == 11) {
				train_index = 1;
			}

			if (available_seats[train_index] >= passengers) {
				available_seats[train_index] -= passengers;
				int remaining_passengers = passengers;
				free_tickets = remaining_passengers / 10;
				remaining_passengers -= free_tickets;
				int single_journey_cost = remaining_passengers * RETURN_TICKET_COST;
				journeys_down[train_index].passengers_booked += passengers;
				journeys_down[train_index].money_collected += single_journey_cost;
				total_passengers += passengers;
				total_money += single_journey_cost;
				total_passengers_free += free_tickets;

				if (passengers > max_passengers) {
					max_passengers = passengers;
					max_passengers_index = train_index;
				}

				ticket_cost += single_journey_cost;
				cout << "Tickets booked for " << passengers << " passengers for the journey down." << endl;
				cout<<"..........................................."<<endl;
				cout << free_tickets << " passengers travel for free on the journey down." << endl;
			} else {
				cout << "Journey down is full! Tickets cannot be booked for this journey." << endl;
			}
		}
		cout<<"..........................................."<<endl;
		cout << "Total cost for the selected journey(s): $" << ticket_cost << endl;
	}

	cout << "\nTotals for Journeys Up (Passengers / Money Collected):" << endl;
	cout<<"..........................................."<<endl;
	for (int i = 0; i < NUM_JOURNEYS; ++i) {
		cout << "Journey " << i + 1 << ": " << journeys_up[i].passengers_booked << " / $"
		     << journeys_up[i].money_collected << endl;
	}

	cout << "\nTotals for Journeys Down (Passengers / Money Collected):" << endl;
	cout<<"..........................................."<<endl;
	for (int i = 0; i < NUM_JOURNEYS; ++i) {
		cout << "Journey " << i + 1 << ": " << journeys_down[i].passengers_booked << " / $"
		     << journeys_down[i].money_collected << endl;
	}

	cout << "\nTotal Passengers for the day: " << total_passengers << endl;
	cout<<"..........................................."<<endl;
	cout << "Total Money Collected for the day: $" << total_money << endl;

	if (max_passengers_index != -1) {
		cout << "The most popular journey of the day is Train " << max_passengers_index + 1
		     << " with " << max_passengers << " passengers." << endl;
	} else {
		cout << "No journeys were made today." << endl;
		cout<<"..........................................."<<endl;
	}

	cout << "Total passengers who travel for free: " << total_passengers_free << endl;
	cout<<"..........................................."<<endl;

	return 0;
}
