#include <string>
#include <iostream>

class Person {
    public:
    
    std::string getNamn() const { return namn;}
    int getArsinkomst() const { return arsinkomst;}
    virtual void skrivUt() const = 0; // "Abstrakt"" klass!¬
    virtual ~Person(){}; // Alltid vid arv!¬
    
    protected:
    Person(std::string namn, int arsinkomst) : namn(namn), arsinkomst(arsinkomst) {}; // Förbjud objektskapande, tillåt subklasser.¬

    private:
    // ta bort kopiering.¬
    Person(const Person& other) = delete;
    // ta bort tilldelning¬
    Person& operator=(const Person& other) = delete;
    std::string namn;
    int arsinkomst;
};

class Anstalld : public Person {
    public:
    static Anstalld* getInstance(std::string namn, int manadslon) {
        return new Anstalld(namn, manadslon);  
    }
    void skrivUt() const override {
        std::cout << "namn: " << getNamn() << "arsinkomst: " << manadslon*12 << "manadslon: " << manadslon << std::endl;
    }
    private:
    int manadslon;
    Anstalld(std::string namn, int manadslon) : Person(namn, (manadslon*12)), manadslon(manadslon){};

};