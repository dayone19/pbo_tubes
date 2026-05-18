#include "Appointment.h"

// Implementasi Constructor
Appointment::Appointment(string p, Doctor* d) {
    patientID = p;
    chosenDoctor = d;
}

// Implementasi Destructor
Appointment::~Appointment() {
   
}