#include "Appointment.h"

Appointment::Appointment(string p, string d) {
    patientID = p;
    doctorName = d;
}

string Appointment::getPatientID() {
    return patientID;
}

string Appointment::getDoctorName() {
    return doctorName;
}


