#include <windows.h>
#include <iostream>
#include <string>

using namespace std;

class UniversalCard {
private:
    bool hasPassport_ = false;
    bool hasInsurance_ = false;
    bool hasBankCard_ = false;

    string passportSeries_;
    string passportNumber_;
    string insuranceNumber_;
    string bankCardNumber_;

public:
    void addPassport(const string& series, const string& number) {
        hasPassport_ = true;
        passportSeries_ = series;
        passportNumber_ = number;
    }

    void addInsurance(const string& number) {
        hasInsurance_ = true;
        insuranceNumber_ = number;
    }

    void addBankCard(const string& number) {
        hasBankCard_ = true;
        bankCardNumber_ = number;
    }

    string getDescription() const {
        string result = "Универсальная электронная карта";
        if (hasPassport_) {
            result += "\nПаспорт: серия " + passportSeries_ + " номер " + passportNumber_;
        }
        if (hasInsurance_) {
            result += "\nСтраховой полис: № " + insuranceNumber_;
        }
        if (hasBankCard_) {
            result += "\nБанковская карта: номер " + bankCardNumber_;
        }
        return result;
    }
};

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    UniversalCard basicCard;
    cout << "Базовая карта:\n" << basicCard.getDescription() << "\n\n";

    UniversalCard cardWithPassport;
    cardWithPassport.addPassport("", "");
    cout << "С паспортом:\n" << cardWithPassport.getDescription() << "\n\n";

    UniversalCard cardWithPassportAndInsurance;
    cardWithPassportAndInsurance.addPassport("", "");
    cardWithPassportAndInsurance.addInsurance("");
    cout << "С паспортом и страховкой:\n" << cardWithPassportAndInsurance.getDescription() << "\n\n";

    UniversalCard fullCard;
    fullCard.addPassport("", "");
    fullCard.addInsurance("");
    fullCard.addBankCard("");
    cout << "Полная карта (паспорт + страховка + банк):\n" << fullCard.getDescription() << "\n";

    return 0;
}