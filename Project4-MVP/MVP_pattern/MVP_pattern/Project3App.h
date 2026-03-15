#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <vector>

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
    string getDescription() const override;
    string getPassport() const override;
    string getInsurance() const override;
    string getBankCard() const override;
};

class CardDecorator : public Card {
protected:
    unique_ptr<Card> card_;
public:
    CardDecorator(unique_ptr<Card> card);
};

class PassportDecorator : public CardDecorator {
    string series_;
    string number_;
public:
    PassportDecorator(unique_ptr<Card> card,
        const string& series,
        const string& number);
    string getDescription() const override;
    string getPassport() const override;
    string getInsurance() const override;
    string getBankCard() const override;
};

class InsuranceDecorator : public CardDecorator {
    string policyNumber_;
public:
    InsuranceDecorator(unique_ptr<Card> card, const string& policyNumber);
    string getDescription() const override;
    string getPassport() const override;
    string getInsurance() const override;
    string getBankCard() const override;
};

class BankCardDecorator : public CardDecorator {
    string cardNumber_;
public:
    BankCardDecorator(unique_ptr<Card> card, const string& cardNumber);
    string getDescription() const override;
    string getPassport() const override;
    string getInsurance() const override;
    string getBankCard() const override;
};

class Project3App {
public:
    Project3App();
    ~Project3App();

    void Run();
    string GetFullDescription() const;
    vector<string> GetComponents() const;

private:
    unique_ptr<Card> card_;
    vector<string> components_;

    void BuildCard();
    void DisplayCardInfo();
    void DisplayDescription();
    void DisplayPassport();
    void DisplayInsurance();
    void DisplayBankCard();
};
