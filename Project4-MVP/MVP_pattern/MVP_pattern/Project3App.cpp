#include "Project3App.h"

#ifdef _WIN32
#include <windows.h>
#endif

string BasicCard::getDescription() const {
    return "Универсальная электронная карта";
}

string BasicCard::getPassport() const {
    return "";
}

string BasicCard::getInsurance() const {
    return "";
}

string BasicCard::getBankCard() const {
    return "";
}

CardDecorator::CardDecorator(unique_ptr<Card> card)
    : card_(move(card)) {
}

PassportDecorator::PassportDecorator(unique_ptr<Card> card,
    const string& series,
    const string& number)
    : CardDecorator(move(card)), series_(series), number_(number) {
}

string PassportDecorator::getDescription() const {
    string base = card_->getDescription();
    if (!series_.empty() || !number_.empty()) {
        return base + "\n  + Паспорт: серия " + series_ + " номер " + number_;
    }
    return base;
}

string PassportDecorator::getPassport() const {
    string base = card_->getPassport();
    if (!series_.empty() || !number_.empty()) {
        if (!base.empty()) base += "\n";
        return base + "Паспорт: серия " + series_ + " номер " + number_;
    }
    return base;
}

string PassportDecorator::getInsurance() const {
    return card_->getInsurance();
}

string PassportDecorator::getBankCard() const {
    return card_->getBankCard();
}

InsuranceDecorator::InsuranceDecorator(unique_ptr<Card> card, const string& policyNumber)
    : CardDecorator(move(card)), policyNumber_(policyNumber) {
}

string InsuranceDecorator::getDescription() const {
    string base = card_->getDescription();
    if (!policyNumber_.empty()) {
        return base + "\n  + Страховой полис: " + policyNumber_;
    }
    return base;
}

string InsuranceDecorator::getPassport() const {
    return card_->getPassport();
}

string InsuranceDecorator::getInsurance() const {
    string base = card_->getInsurance();
    if (!policyNumber_.empty()) {
        if (!base.empty()) base += "\n";
        return base + "Страховой полис: " + policyNumber_;
    }
    return base;
}

string InsuranceDecorator::getBankCard() const {
    return card_->getBankCard();
}

BankCardDecorator::BankCardDecorator(unique_ptr<Card> card, const string& cardNumber)
    : CardDecorator(move(card)), cardNumber_(cardNumber) {
}

string BankCardDecorator::getDescription() const {
    string base = card_->getDescription();
    if (!cardNumber_.empty()) {
        return base + "\n  + Банковская карта: номер " + cardNumber_;
    }
    return base;
}

string BankCardDecorator::getPassport() const {
    return card_->getPassport();
}

string BankCardDecorator::getInsurance() const {
    return card_->getInsurance();
}

string BankCardDecorator::getBankCard() const {
    string base = card_->getBankCard();
    if (!cardNumber_.empty()) {
        if (!base.empty()) base += "\n";
        return base + "Банковская карта: номер " + cardNumber_;
    }
    return base;
}


Project3App::Project3App() {
}

Project3App::~Project3App() {
}

void Project3App::BuildCard() {
    auto basic = make_unique<BasicCard>();

    auto withPassport = make_unique<PassportDecorator>(
        move(basic), "", "");
    components_.push_back("Паспорт");

    auto withInsurance = make_unique<InsuranceDecorator>(
        move(withPassport), "");
    components_.push_back("Страховой полис");

    card_ = make_unique<BankCardDecorator>(
        move(withInsurance), "");
    components_.push_back("Банковская карта");
}

void Project3App::DisplayCardInfo() {
    cout << "ПРОЕКТ 3: ПАТТЕРН ДЕКОРАТОР" << endl;
    cout << "(Универсальная электронная карта)" << endl;
    cout << endl;
    cout << "Информация о карте:" << endl;
    cout << "─────────────────────────────────────────────────────────────" << endl;
    cout << card_->getDescription() << endl;
    cout << "─────────────────────────────────────────────────────────────" << endl;

    cout << endl;
    cout << "Доступ к отдельным компонентам:" << endl;
    DisplayInsurance();
    DisplayPassport();
    DisplayBankCard();
    }

void Project3App::DisplayPassport() {
    cout << "  Паспорт:    " << (card_->getPassport().empty() ? "<не добавлен>" : card_->getPassport()) << endl;
}
void Project3App::DisplayInsurance() {
    cout << "  Страховка:  " << (card_->getInsurance().empty() ? "<не добавлен>" : card_->getInsurance()) << endl;
}
void Project3App::DisplayBankCard() {
    cout << "  Банк карта: " << (card_->getBankCard().empty() ? "<не добавлен>" : card_->getBankCard()) << endl;
}

string Project3App::GetFullDescription() const {
    if (card_) {
        return card_->getDescription();
    }
    return "";
}

vector<string> Project3App::GetComponents() const {
    return components_;
}

void Project3App::Run() {
#ifdef _WIN32
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
#endif

    BuildCard();
    DisplayCardInfo();
}
