#include <windows.h>
#include <iostream>
#include <memory>
#include <string>

using namespace std;

class Card {
public:
    virtual ~Card() = default;
    virtual string getDescription() const = 0;
    virtual string getPassport() const = 0;
    virtual string getInsurance() const = 0;
    virtual string getBankCard() const = 0;
};

class BasicCard : public Card {
public:
    string getDescription() const override {
        return "Универсальная электронная карта";
    }

    string getPassport() const override {
        return "";
    }

    string getInsurance() const override {
        return "";
    }

    string getBankCard() const override {
        return "";
    }
};

class CardDecorator : public Card {
protected:
    unique_ptr<Card> card_;
public:
    CardDecorator(unique_ptr<Card> card) : card_(move(card)) {}
};

class PassportDecorator : public CardDecorator {
    string series_;
    string number_;
public:
    PassportDecorator(unique_ptr<Card> card,
        const string& series,
        const string& number)
        : CardDecorator(move(card)), series_(series), number_(number) {
    }

    string getDescription() const override {
        return card_->getDescription() + "\nПаспорт: серия " + series_ + " номер " + number_;
    }

    string getPassport() const override {
        return card_->getPassport() + "\nПаспорт: серия " + series_ + " номер " + number_;
    }

    string getInsurance() const override {
        return card_->getInsurance() + "";
    }

    string getBankCard() const override {
        return card_->getBankCard() + "";
    }
};

class InsuranceDecorator : public CardDecorator {
    string policyNumber_;
public:
    InsuranceDecorator(unique_ptr<Card> card, const string& policyNumber)
        : CardDecorator(move(card)), policyNumber_(policyNumber) {
    }

    string getDescription() const override {
        return card_->getDescription() + "\nСтраховой полис: № " + policyNumber_;
    }

    string getPassport() const override {
        return card_->getPassport() + "";
    }

    string getInsurance() const override {
        return card_->getInsurance() + "\nСтраховой полис: № " + policyNumber_;
    }

    string getBankCard() const override {
        return card_->getBankCard() + "";
    }
};

class BankCardDecorator : public CardDecorator {
    string cardNumber_;
public:
    BankCardDecorator(unique_ptr<Card> card, const string& cardNumber)
        : CardDecorator(move(card)), cardNumber_(cardNumber) {
    }

    string getDescription() const override {
        return card_->getDescription() + "\nБанковская карта: номер " + cardNumber_;
    }

    string getPassport() const override {
        return card_->getPassport() + "";
    }

    string getInsurance() const override {
        return card_->getInsurance() + "";
    }

    string getBankCard() const override {
        return card_->getBankCard() + "\nБанковская карта: номер " + cardNumber_;
    }
};

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    auto basic = make_unique<BasicCard>();
    cout << "Базовая карта:\n" << basic->getDescription() << "\n\n";

    auto withPassport = make_unique<PassportDecorator>(move(basic), "", "");
    cout << "С паспортом:\n" << withPassport->getPassport() << "\n\n";

    auto withPassportAndInsurance = make_unique<InsuranceDecorator>(move(withPassport), "");
    cout << "С паспортом и страховкой:\n" << withPassportAndInsurance->getInsurance() << "\n\n";
    
    auto fullCard = make_unique<BankCardDecorator>(move(withPassportAndInsurance), "");
    cout << "Полная карта (паспорт + страховка + банк):\n" << fullCard->getBankCard() << "\n";

    return 0;
}