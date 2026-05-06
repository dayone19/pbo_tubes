#include "QueueSystem.h"

void QueueSystem::addQueue(string id) {
    antrian.push_back(id);
}

void QueueSystem::showQueue() {
    if (antrian.empty()) {
        cout << "++++++++++++++++++++++++++++++++++++++" << endl;
        cout << "----- BELUM ADA ANTRIAN HARI INI -----" << endl;
        cout << "++++++++++++++++++++++++++++++++++++++" << endl;
    } else {
        cout << "++++++++++++++++++" << endl;
        cout << "\n--- ANTRIAN ---\n";
        cout << "++++++++++++++++++" << endl;
        for (int i = 0; i < antrian.size(); i++) {
            cout << i + 1 << ". " << antrian[i] << endl;
        }
    }
}

void QueueSystem::removeQueue(string id) {
    for (int i = 0; i < antrian.size(); i++) {
        if (antrian[i] == id) {
            antrian.erase(antrian.begin() + i);
            break;
        }
    }
}
