#include <iostream>
#include <vector>

using namespace std;

// Forward declarations
class Hotel;
class User;
class Administrator;
class Person;
class Location;
class Price;

// Price class
class Price {
private:
    double value;

public:
    Price(double value) : value(value) {}
    double getValue() const { return value; }
};

// Location class
class Location {
private:
    string city;

public:
    Location(string city) : city(city) {}
    string getCity() const { return city; }
};

// Person class
class Person {
private:
    string name;
    string address;

public:
    Person(string name, string address) : name(name), address(address) {}
    string getName() const { return name; }
    string getAddress() const { return address; }
};

// Hotel class
class Hotel {
private:
    string name;
    Location location;
    int numRooms;
    vector<string> facilities;
    Price price;
    bool approved;
    vector<string> feedbacks;
    int totalRating;
    int numRatings;

public:
    Hotel(string name, Location location, int numRooms, vector<string> facilities, Price price)
        : name(name), location(location), numRooms(numRooms), facilities(facilities), price(price), approved(false), totalRating(0), numRatings(0) {}

    string getName() const { return name; }
    Location getLocation() const { return location; }
    int getNumRooms() const { return numRooms; }
    vector<string> getFacilities() const { return facilities; }
    Price getPrice() const { return price; }
    bool isApproved() const { return approved; }
    void setApproved(bool status) { approved = status; }
    void decrementNumRooms() { --numRooms; }
    void addFeedback(const string& feedback) { feedbacks.push_back(feedback); }
    double getAverageRating() const { return numRatings > 0 ? static_cast<double>(totalRating) / numRatings : 0.0; }
    void addRating(int rating) {
        totalRating += rating;
        numRatings++;
    }
};

// User class
class User : public Person {
private:
    string username;
    string password;

public:
    User(string username, string password, string name, string address)
        : Person(name, address), username(username), password(password) {}

    string getUsername() const { return username; }
    string getPassword() const { return password; }

    void modifyDetails(string newUsername, string newPassword) {
        username = newUsername;
        password = newPassword;
    }
};

// Hotel Agent class
class HotelAgent : public User {
public:
    HotelAgent(string username, string password, string name, string address)
        : User(username, password, name, address) {}

    void addHotelDetails(vector<Hotel>& hotels, string name, Location location, int numRooms, vector<string> facilities, Price price) {
        hotels.push_back(Hotel(name, location, numRooms, facilities, price));
    }

    void updateHotelDetails(vector<Hotel>& hotels, int hotelIndex, string name, Location location, int numRooms, vector<string> facilities, Price price) {
        hotels[hotelIndex] = Hotel(name, location, numRooms, facilities, price);
    }
};

// Administrator class
class Administrator {
public:
    void approveHotelDetails(vector<Hotel>& hotels, int hotelIndex) {
        hotels[hotelIndex].setApproved(true);
    }

    void deleteUser(vector<User>& users, int userIndex) {
        users.erase(users.begin() + userIndex);
    }

    void deleteHotel(vector<Hotel>& hotels, int hotelIndex) {
        hotels.erase(hotels.begin() + hotelIndex);
    }
};

// Function to search hotels based on location and maximum price
// Function to search hotels based on location and maximum price
// Function to search hotels based on location and maximum price
vector<Hotel> searchHotels(const vector<Hotel>& hotels, const Location& location, const Price& maxPrice) {
    vector<Hotel> matchedHotels;

    for (const auto& hotel : hotels) {
        if (hotel.isApproved() && hotel.getLocation().getCity() == location.getCity() && hotel.getPrice().getValue() <= maxPrice.getValue()) {
            matchedHotels.push_back(hotel);
        }
    }

    return matchedHotels;
}


// Function to display the menu options
void displayMenu() {
    cout << "===== Hotel Management System =====" << endl;
    cout << "1. Register as a Hotel Agent" << endl;
    cout << "2. Register as a User" << endl;
    cout << "3. Add Hotel Details" << endl;
    cout << "4. Update Hotel Details" << endl;
    cout << "5. Approve Hotel Details" << endl;
    cout << "6. Search and Book Hotels" << endl;
    cout << "7. Provide Feedback" << endl;
    cout << "8. Rate Hotels" << endl;
    cout << "9. Exit" << endl;
    cout << "===================================" << endl;
    cout << "Enter your choice: ";
}

int main() {
    vector<Hotel> hotels;
    vector<HotelAgent> hotelAgents; // Separate vector for HotelAgents
    vector<User> users;
    Administrator admin;

    int choice;
    bool exitProgram = false;

    while (!exitProgram) {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1: {
                string username, password, name, address;
                cout << "Enter username: ";
                cin >> username;
                cout << "Enter password: ";
                cin >> password;
                cout << "Enter name: ";
                cin >> name;
                cout << "Enter address: ";
                cin >> address;

                HotelAgent agent(username, password, name, address);
                hotelAgents.push_back(agent); // Store the Hotel Agent separately
                users.push_back(agent);

                cout << "Registered as a Hotel Agent successfully!" << endl;
                break;
            }
            case 2: {
                string username, password, name, address;
                cout << "Enter username: ";
                cin >> username;
                cout << "Enter password: ";
                cin >> password;
                cout << "Enter name: ";
                cin >> name;
                cout << "Enter address: ";
                cin >> address;

                User user(username, password, name, address);
                users.push_back(user);

                cout << "Registered as a User successfully!" << endl;
                break;
            }
            case 3: {
                if (hotelAgents.empty()) {
                    cout << "No registered agents found. Please register as a Hotel Agent first." << endl;
                } else {
                    string name, city;
                    Location location(city);
                    int numRooms;
                    vector<string> facilities;
                    double priceValue;
                    Price price(priceValue);

                    cout << "Enter hotel name: ";
                    cin.ignore();
                    getline(cin, name);
                    cout << "Enter hotel city: ";
                    getline(cin, city);
                    cout << "Enter number of rooms: ";
                    cin >> numRooms;
                    cin.ignore();

                    cout << "Enter facilities (one per line, enter 'done' to finish): " << endl;
                    string facility;
                    while (getline(cin, facility) && facility != "done") {
                        facilities.push_back(facility);
                    }

                    cout << "Enter price per night: ";
                    cin >> priceValue;

                    if (!hotelAgents.empty()) {
                        cout << "Available Hotel Agents:" << endl;
                        for (int i = 0; i < hotelAgents.size(); ++i) {
                            cout << i + 1 << ". " << hotelAgents[i].getUsername() << endl;
                        }

                        int agentChoice;
                        cout << "Select the agent (enter number): ";
                        cin >> agentChoice;

                        if (agentChoice > 0 && agentChoice <= hotelAgents.size()) {
                            hotelAgents[agentChoice - 1].addHotelDetails(hotels, name, location, numRooms, facilities, price);
                            cout << "Hotel details added successfully!" << endl;
                        } else {
                            cout << "Invalid choice." << endl;
                        }
                    }
                }
                break;
            }
            case 4: {
                if (hotelAgents.empty()) {
                    cout << "No registered agents found. Please register as a Hotel Agent first." << endl;
                } else {
                    if (hotels.empty()) {
                        cout << "No hotels added yet. Please add hotel details first." << endl;
                    } else {
                        cout << "Available Hotels:" << endl;
                        for (int i = 0; i < hotels.size(); ++i) {
                            cout << i + 1 << ". " << hotels[i].getName() << endl;
                        }

                        int hotelChoice;
                        cout << "Select the hotel (enter number): ";
                        cin >> hotelChoice;

                        if (hotelChoice > 0 && hotelChoice <= hotels.size()) {
                            string name, city;
                            Location location(city);
                            int numRooms;
                            vector<string> facilities;
                            double priceValue;
                            Price price(priceValue);

                            cout << "Enter updated hotel name: ";
                            cin.ignore();
                            getline(cin, name);
                            cout << "Enter updated hotel city: ";
                            getline(cin, city);
                            cout << "Enter updated number of rooms: ";
                            cin >> numRooms;
                            cin.ignore();

                            cout << "Enter updated facilities (one per line, enter 'done' to finish): " << endl;
                            string facility;
                            while (getline(cin, facility) && facility != "done") {
                                facilities.push_back(facility);
                            }

                            cout << "Enter updated price per night: ";
                            cin >> priceValue;

                            hotelAgents[0].updateHotelDetails(hotels, hotelChoice - 1, name, location, numRooms, facilities, price);
                            cout << "Hotel details updated successfully!" << endl;
                        } else {
                            cout << "Invalid choice." << endl;
                        }
                    }
                }
                break;
            }
            case 5: {
                if (hotels.empty()) {
                    cout << "No hotels added yet. Please add hotel details first." << endl;
                } else {
                    cout << "Available Hotels:" << endl;
                    for (int i = 0; i < hotels.size(); ++i) {
                        cout << i + 1 << ". " << hotels[i].getName() << endl;
                    }

                    int hotelChoice;
                    cout << "Select the hotel (enter number): ";
                    cin >> hotelChoice;

                    if (hotelChoice > 0 && hotelChoice <= hotels.size()) {
                        admin.approveHotelDetails(hotels, hotelChoice - 1);
                        cout << "Hotel details approved successfully!" << endl;
                    } else {
                        cout << "Invalid choice." << endl;
                    }
                }
                break;
            }
            case 6: {
                string city;
                double maxPrice;

                cout << "Enter hotel location: ";
                cin.ignore();
                getline(cin, city);
                cout << "Enter maximum price per night: ";
                cin >> maxPrice;

                Location location(city);
                Price price(maxPrice);

                vector<Hotel> matchedHotels = searchHotels(hotels, location, price);
                if (!matchedHotels.empty()) {
                    cout << "Available Hotels:" << endl;
                    for (const auto& hotel : matchedHotels) {
                        cout << "Name: " << hotel.getName() << endl;
                        cout << "City: " << hotel.getLocation().getCity() << endl;
                        cout << "Facilities: ";
                        for (const auto& facility : hotel.getFacilities()) {
                            cout << facility << " ";
                        }
                        cout << endl;
                        cout << "Price per night: " << hotel.getPrice().getValue() << endl;
                        cout << "---------------------------" << endl;
                    }

                    int hotelChoice;
                    cout << "Select the hotel to book (enter number): ";
                    cin >> hotelChoice;

                    if (hotelChoice > 0 && hotelChoice <= matchedHotels.size()) {
                        Hotel& selectedHotel = matchedHotels[hotelChoice - 1];
                        if (selectedHotel.getNumRooms() > 0) {
                            selectedHotel.decrementNumRooms();
                            cout << "Room booked successfully!" << endl;
                        } else {
                            cout << "No available rooms in the selected hotel." << endl;
                        }
                    } else {
                        cout << "Invalid choice." << endl;
                    }
                } else {
                    cout << "No hotels found matching the search criteria." << endl;
                }
                break;
            }
            case 7: {
                if (hotels.empty()) {
                    cout << "No hotels added yet. Please add hotel details first." << endl;
                } else {
                    cout << "Available Hotels:" << endl;
                    for (int i = 0; i < hotels.size(); ++i) {
                        cout << i + 1 << ". " << hotels[i].getName() << endl;
                    }

                    int hotelChoice;
                    cout << "Select the hotel to provide feedback (enter number): ";
                    cin >> hotelChoice;

                    if (hotelChoice > 0 && hotelChoice <= hotels.size()) {
                        string feedback;
                        cout << "Enter your feedback: ";
                        cin.ignore();
                        getline(cin, feedback);

                        hotels[hotelChoice - 1].addFeedback(feedback);
                        cout << "Feedback added successfully!" << endl;
                    } else {
                        cout << "Invalid choice." << endl;
                    }
                }
                break;
            }
            case 8: {
                if (hotels.empty()) {
                    cout << "No hotels added yet. Please add hotel details first." << endl;
                } else {
                    cout << "Available Hotels:" << endl;
                    for (int i = 0; i < hotels.size(); ++i) {
                        cout << i + 1 << ". " << hotels[i].getName() << endl;
                    }

                    int hotelChoice;
                    cout << "Select the hotel to rate (enter number): ";
                    cin >> hotelChoice;

                    if (hotelChoice > 0 && hotelChoice <= hotels.size()) {
                        int rating;
                        cout << "Enter your rating (1-5): ";
                        cin >> rating;

                        if (rating >= 1 && rating <= 5) {
                            hotels[hotelChoice - 1].addRating(rating);
                            cout << "Rating added successfully!" << endl;
                        } else {
                            cout << "Invalid rating. Please enter a value between 1 and 5." << endl;
                        }
                    } else {
                        cout << "Invalid choice." << endl;
                    }
                }
                break;
            }
            case 9: {
                exitProgram = true;
                break;
            }
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }

        cout << endl;
    }

    return 0;
}
