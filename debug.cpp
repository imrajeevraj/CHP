#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

int main() {
    int K;
    double S, SLO1, SLO2, tp_ub, tp_base;
    cin >> K >> S >> SLO1 >> SLO2 >> tp_ub >> tp_base;

    double dist_base, tp_th;
    cin >> dist_base >> tp_th;

    int N;
    cin >> N;

    string line;
    getline(cin, line); // consume newline
    for (int i = 0; i < N; ++i) {
        getline(cin, line);
    }

    while (true) {
        string token;
        if (!(cin >> token)) break;
        if (token == "END") break;

        double timestamp = stod(token);
        
        int num_events;
        cin >> num_events;
        
        getline(cin, line); // consume the newline after num_events

        cout << "Time: " << timestamp << " Events: " << num_events << "\n";

        for (int i = 0; i < num_events; ++i) {
            getline(cin, line);
            stringstream ss(line);
            string event_type;
            ss >> event_type;
            cout << "  Event: " << event_type << "\n";
        }
    }

    return 0;
}
