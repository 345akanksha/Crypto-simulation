#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <random>
#include <cstdlib>

using namespace std;

class CryptoTracker {
public:
    void addCrypto(const string& name, double price) {
        cryptos[name] = price;
    }

    void displayPrices() const {
        if (cryptos.empty()) {
            cout << "No cryptocurrencies available.\n";
            return;
        }
        cout << "Current Cryptocurrency Prices:\n";
        for (const auto& crypto : cryptos) {
            cout << crypto.first << ": $" << crypto.second << "\n";
        }
    }

    void updatePrice(const string& name, double price) {
        if (cryptos.find(name) != cryptos.end()) {
            cryptos[name] = price;
            cout << name << " price updated to $" << price << "\n";
        } else {
            cout << "Cryptocurrency not found!\n";
        }
    }

    void deleteCrypto(const string& name) {
        if (cryptos.erase(name)) {
            cout << name << " has been deleted from the tracker.\n";
        } else {
            cout << "Cryptocurrency not found!\n";
        }
    }

    void findPrice(const string& name) const {
        auto it = cryptos.find(name);
        if (it != cryptos.end()) {
            cout << it->first << ": $" << it->second << "\n";
        } else {
            cout << "Cryptocurrency not found!\n";
        }
    }

    void sortPrices(bool ascending = true) const {
        vector<pair<string, double>> sortedCryptos(cryptos.begin(), cryptos.end());
        if (ascending) {
            sort(sortedCryptos.begin(), sortedCryptos.end(),
                      [](const auto& a, const auto& b) { return a.second < b.second; });
        } else {
            sort(sortedCryptos.begin(), sortedCryptos.end(),
                      [](const auto& a, const auto& b) { return a.second > b.second; });
        }

        cout << "Sorted Cryptocurrency Prices:\n";
        for (const auto& crypto : sortedCryptos) {
            cout << crypto.first << ": $" << crypto.second << "\n";
        }
    }

    // Simulates price updates
    void simulatePriceUpdates() {
        mt19937 rng(random_device{}()); // Random number generator
        uniform_real_distribution<double> dist(-500.0, 500.0); // Random price change

        for (auto& crypto : cryptos) {
            crypto.second += dist(rng); // Adjust price randomly
            if (crypto.second < 0) crypto.second = 0; // Prevent negative prices
        }
    }

private:
    map<string, double> cryptos;
};

int main() {
    CryptoTracker tracker;

    // Adding some cryptocurrencies with hardcoded values
    tracker.addCrypto("Bitcoin", 40000.00);
    tracker.addCrypto("Ethereum", 2500.00);
    tracker.addCrypto("Ripple", 1.00);

    int choice;
    do {
        tracker.simulatePriceUpdates();  // Update prices each time

        cout << "\nCryptocurrency Tracker\n";
        tracker.displayPrices();
        cout << "\nMenu:\n";
        cout << "1. Refresh Prices\n";
        cout << "2. Update Price\n";
        cout << "3. Delete Cryptocurrency\n";
        cout << "4. Find Cryptocurrency Price\n";
        cout << "5. Sort Prices (Ascending)\n";
        cout << "6. Sort Prices (Descending)\n";
        cout << "7. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice) {
            case 1:
                break;  // Refresh prices (re-run the loop)
            case 2: {
                string name;
                double newPrice;
                cout << "Enter the name of the cryptocurrency: ";
                cin >> name;
                cout << "Enter the new price: ";
                cin >> newPrice;
                tracker.updatePrice(name, newPrice);
                break;
            }
            case 3: {
                string name;
                cout << "Enter the name of the cryptocurrency to delete: ";
                cin >> name;
                tracker.deleteCrypto(name);
                break;
            }
            case 4: {
                string name;
                cout << "Enter the name of the cryptocurrency to find: ";
                cin >> name;
                tracker.findPrice(name);
                break;
            }
            case 5:
                tracker.sortPrices(true);
                break;
            case 6:
                tracker.sortPrices(false);
                break;
            case 7:
                cout << "Exiting the tracker.\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }

        if (choice != 7) {
            cout << "\nPress Enter to continue...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();  // Wait for user input to continue
        }

    } while (choice != 7);

    return 0;
}
