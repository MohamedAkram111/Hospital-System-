#include <iostream>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

class Person {
public:
    int ID;
    string name;
    string address;
    string phoneNumber;

    Person(int id, string n, string addr, string phone)
        : ID(id), name(n), address(addr), phoneNumber(phone) {}

    virtual void getDetails() const {
        cout << "ID: " << ID << "\nName: " << name << "\nAddress: " << address << "\nPhone: " << phoneNumber << endl;
    }
};

class Prescription {
private:
    int prescriptionNumber;
    Person* patient;
    Person* doctor;
    vector<string> medications;
    string instructions;

public:
    Prescription(int num, Person* pat, Person* doc, vector<string> meds, string instr)
        : prescriptionNumber(num), patient(pat), doctor(doc), medications(meds), instructions(instr) {}

    void addMedicine(const string& medicine) {
        medications.push_back(medicine);
    }

    void getDetails() const {
        cout << "Prescription Number: " << prescriptionNumber << "\nPatient: " << patient->name << "\nDoctor: " << doctor->name << "\nInstructions: " << instructions << "\nMedications: ";
        for (const auto& med : medications)
            cout << med << " ";
        cout << endl;
    }
};

class Patient : public Person {
private:
    int patientNumber;
    tm dateOfBirth;
    string medicalCondition;
    vector<Prescription> prescribedMedications;

public:
    Patient(int id, string n, string addr, string phone, int pNum, tm dob, string medCond)
        : Person(id, n, addr, phone), patientNumber(pNum), dateOfBirth(dob), medicalCondition(medCond) {}

    void addPrescription(const Prescription& prescription) {
        prescribedMedications.push_back(prescription);
    }

    void getDetails() const override {
        Person::getDetails();
        cout << "Patient Number: " << patientNumber << "\nDate of Birth: " << (dateOfBirth.tm_year + 1900) << "-" << (dateOfBirth.tm_mon + 1) << "-" << dateOfBirth.tm_mday << "\nMedical Condition: " << medicalCondition << endl;
    }

    void getMedicalHistory() const {
        cout << "Medical Condition: " << medicalCondition << "\nPrescriptions: ";
        for (const auto& prescription : prescribedMedications)
            prescription.getDetails();
    }
};

class Doctor : public Person {
private:
    int doctorNumber;
    string specialty;
    vector<Patient*> patientsUnderCare;

public:
    Doctor(int id, string n, string addr, string phone, int dNum, string spec)
        : Person(id, n, addr, phone), doctorNumber(dNum), specialty(spec) {}

    void addPatient(Patient* patient) {
        patientsUnderCare.push_back(patient);
    }

    void diagnosePatient(Patient* patient, const string& diagnosis) {
        patient->getDetails();
        cout << "Diagnosis: " << diagnosis << endl;
    }

    void getDetails() const override {
        Person::getDetails();
        cout << "Doctor Number: " << doctorNumber << "\nSpecialty: " << specialty << endl;
    }
};

class Nurse : public Person {
private:
    int nurseNumber;
    string department;
    vector<Patient*> patientsUnderCare;

public:
    Nurse(int id, string n, string addr, string phone, int nNum, string dept)
        : Person(id, n, addr, phone), nurseNumber(nNum), department(dept) {}

    void checkPatient(Patient* patient) {
        patient->getDetails();
    }

    void updatePatientStatus(Patient* patient, const string& status) {
        patient->getDetails();
        cout << "Updated Status: " << status << endl;
    }

    void getDetails() const override {
        Person::getDetails();
        cout << "Nurse Number: " << nurseNumber << "\nDepartment: " << department << endl;
    }
};

class Appointment {
private:
    int appointmentNumber;
    Patient* patient;
    Doctor* doctor;
    tm dateTime;

public:
    Appointment(int num, Patient* pat, Doctor* doc, tm dt)
        : appointmentNumber(num), patient(pat), doctor(doc), dateTime(dt) {}

    void schedule() {
        cout << "Appointment scheduled for:\n";
        patient->getDetails();
        cout << "with\n";
        doctor->getDetails();
        cout << "on " << asctime(&dateTime) << endl;
    }

    void reschedule(tm newDateTime) {
        dateTime = newDateTime;
        cout << "Appointment rescheduled to " << asctime(&dateTime) << endl;
    }

    void cancel() {
        cout << "Appointment canceled for:\n";
        patient->getDetails();
    }
};

class Hospital {
private:
    vector<Patient> patients;
    vector<Doctor> doctors;
    vector<Appointment> appointments;

public:
    void addPatient(const Patient& patient) {
        patients.push_back(patient);
    }

    void addDoctor(const Doctor& doctor) {
        doctors.push_back(doctor);
    }

    void scheduleAppointment(const Appointment& appointment) {
        appointments.push_back(appointment);
    }
};

int main() {
    // Example usage
    tm dob = {};
    dob.tm_year = 90;
    dob.tm_mon = 1;   // Month
    dob.tm_mday = 1;  // Day of the month
    tm dob1 = {};
    dob1.tm_year = 91;
    dob1.tm_mon = 2;   // Month
    dob1.tm_mday = 2;  // Day of the month
    tm dob2 = {};
    dob2.tm_year = 95;
    dob2.tm_mon = 6;   // Month
    dob2.tm_mday = 21;  // Day of the month
    tm dob3 = {};
    dob3.tm_year = 98;
    dob3.tm_mon = 12;   // Month
    dob3.tm_mday = 15;  // Day of the month
    tm dob4 = {};
    dob4.tm_year = 2000;
    dob4.tm_mon = 8;   // Month
    dob4.tm_mday = 10;  // Day of the month






    Patient patient1(1, "Mohamed Salem", "Elsalam street", "123456789", 1001, dob, "Diabetes");
    Doctor doctor1(2, "Dr. Islam", "Zagazig", "987654321", 2001, "Endocrinology");
    Patient patient2(3, "Mohamed Ahmed", "Faquos", "123456780", 1000, dob1, "Rheumatoid Arthritis");
    Doctor doctor2(4, "Dr. Said", "Zagazig", "987654320", 2000, "Rheumatology");
    Patient patient3(5, "Asmaa Mohamed", "Farouq Street", "023456780", 1002, dob2, "Migraine");
    Doctor doctor3(6, "Dr. Soha", "Zagazig", "087654320", 2002, "Neurology");
    Patient patient4(7, "Sama Mohamed", "Farouq Street", "103456780", 1003, dob3, "Peptic ulcer");
    Doctor doctor4(8, "Dr. Alaa", "Zagazig", "107654320", 2003, "Internal Medicine");
    Patient patient5(9, "Osama Yousef", "Kafr Sakr", "113456780", 1004, dob4, "Gout");
    Doctor doctor5(10, "Dr. Alaa", "Zagazig", "117654320", 2003, "Orthopedics");



    Prescription prescription1(3001, &patient1, &doctor1, {"Insulin"}, "Take daily");
    patient1.addPrescription(prescription1);
    Prescription prescription2(2001, &patient2, &doctor2, {"Methotrexate"}, "Take Weekly");
    patient2.addPrescription(prescription2);
    Prescription prescription3(1001, &patient3, &doctor3, {"Imitrex"}, "Take daily");
    patient3.addPrescription(prescription3);
    Prescription prescription4(1001, &patient4, &doctor4, {"Omez(PPIs)"}, "Take daily");
    patient4.addPrescription(prescription4);
    Prescription prescription5(1001, &patient5, &doctor5, {"Colchicine"}, "Take daily");
    patient5.addPrescription(prescription5);



    Hospital hospital;
    hospital.addPatient(patient1);
    hospital.addDoctor(doctor1);
    hospital.addPatient(patient2);
    hospital.addDoctor(doctor2);
    hospital.addPatient(patient3);
    hospital.addDoctor(doctor3);
    hospital.addPatient(patient4);
    hospital.addDoctor(doctor4);
    hospital.addPatient(patient5);
    hospital.addDoctor(doctor5);




    tm appointmentDate = {};
    appointmentDate.tm_year = 2024;
    appointmentDate.tm_mon = 6;    // Month
    appointmentDate.tm_mday = 15;  // Day of the month
    Appointment appointment1(4001, &patient1, &doctor1, appointmentDate);
    hospital.scheduleAppointment(appointment1);
    appointment1.schedule();
    Appointment appointment2(3001, &patient2, &doctor2, appointmentDate);
    hospital.scheduleAppointment(appointment2);
    appointment2.schedule();
    Appointment appointment3(2001, &patient3, &doctor3, appointmentDate);
    hospital.scheduleAppointment(appointment3);
    appointment3.schedule();
    Appointment appointment4(1001, &patient4, &doctor4, appointmentDate);
    hospital.scheduleAppointment(appointment4);
    appointment4.schedule();
    Appointment appointment5(5001, &patient5, &doctor5, appointmentDate);
    hospital.scheduleAppointment(appointment5);
    appointment5.schedule();





    return 0;
}
