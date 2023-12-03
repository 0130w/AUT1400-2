#ifndef Q2_H
#define Q2_H
#include <fstream>

namespace q2{

struct Patient
{
    std::string name;
    size_t age;
    size_t smokes;
    size_t area_q;
    size_t alkhol;
};

inline std::vector<Patient> read_file(std::string filename) {
    std::ifstream in(filename, std::ios_base::in);
    if(!in.is_open()) {
        throw std::runtime_error("fail to open file with filename: " + filename);
    }
    std::vector<Patient> patients;
    std::string line;
    // ignore the first two lines
    std::getline(in, line);
    std::getline(in, line);

    while(std::getline(in, line)) {
        std::istringstream ss(line);
        Patient patient;
        std::string token;
        std::string name, surname;
        std::getline(ss, name, ',');
        std::getline(ss, surname, ',');
        name.erase(std::remove(name.begin(), name.end(), ' '), name.end());
        surname.erase(std::remove(surname.begin(), surname.end(), ' '), surname.end());
        patient.name = name + " " + surname;
        std::getline(ss, token, ',');
        patient.age = std::stoul(token);
        std::getline(ss, token, ',');
        patient.smokes = std::stoul(token);
        std::getline(ss, token, ',');
        patient.area_q = std::stoul(token);
        std::getline(ss, token, ',');
        patient.alkhol = std::stoul(token);

        patients.push_back(patient);
    }
    return patients;
}

inline void sort(std::vector<Patient>& patients) {
    return std::sort(patients.begin(), patients.end(), [](Patient &a, Patient &b) {
        auto func = [](Patient &patient) {
            return 3 * patient.age + 5 * patient.smokes + 2 * patient.area_q + 4 * patient.alkhol;
        };
        return func(a) > func(b);
    });
}

};

#endif //Q2_H