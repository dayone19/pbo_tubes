#include "QueueSystem.h"
#include "../color.h"

void QueueSystem::addQueue(string id) {
    antrian.push_back(id);
}

void QueueSystem::showQueue() {
    if(antrian.empty()) { 
            cout << turquoise << "+++++++++++++++++++++++++++++++++++++" << endl;
            cout << "---- " << putih << "BELUM ADA ANTRIAN HARI INI" << turquoise << " ----" << endl;
            cout << turquoise << "+++++++++++++++++++++++++++++++++++++" << endl;
        } else {
            cout << hijauTerang << "++++++++++++++++++++++++" << reset << endl;
            cout << hijauTerang << " ------" << salmon << " ANTRIAN " << hijauTerang <<  "------ \n";
            cout << hijauTerang << "++++++++++++++++++++++++" << reset << endl;
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
