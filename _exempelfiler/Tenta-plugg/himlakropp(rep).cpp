#include <vector>
#include <string>

using namespace std;

class Himlakropp {

    public:
    string getNamn() const {
        return namn;
    }
    int getDiameter() const {
        return diameter;
    }
    virtual int getVikt() const = 0;
    virtual ~Himlakropp();

    protected:
    Himlakropp(string n, int d) : namn(n), diameter(d) {}

    private:
    string namn;
    int diameter;
    Himlakropp(const Himlakropp& other) = delete;
    const Himlakropp& operator=(const Himlakropp& other) = delete;
};

class Måne : public Himlakropp {

    public:
    int getVikt() const {
        return 10*getDiameter()-kratrar;
    }
    int getKratrar() const { 
        return kratrar; 
    }
    static Måne* getInstance(string n, int d, int k);
    protected:
    Måne(string n, int d, int k) : Himlakropp(n, d), kratrar(k){}
    
    private:
    int kratrar;
};

Måne* Måne::getInstance(std::string n, int d, int k){ return new Måne(n, d, k);}

class Planet : public Himlakropp {

public:
int getVikt() const {
    return 0;
}
void addMåne(Måne* m){
    if (måne != m){
    delete måne;
    måne = m;
    }
}
~Planet(){ delete måne; }
static Planet* getInstance(string n, int d, bool atm);
static Planet* getInstance(string n, int d, bool atm, Måne* m);

protected:
Planet (string n, int d, bool atm) : Himlakropp(n, d), atmosfär(atm){
}
Planet (string n, int d, bool atm, Måne* m) : Himlakropp(n, d), atmosfär(atm), måne(m){
}

private:
bool atmosfär;
Måne* måne;

};

Planet* Planet::getInstance(string n, int d, bool atm){ return new Planet(n,d,atm);}
Planet* Planet::getInstance(string n, int d, bool atm, Måne* m){return new Planet(n,d,atm,m);}

class Stjärna : public Himlakropp{

    public:
    int getLjusstyrka() const { return ljusstyrka; }
    
    int getVikt() const{
        int vikt = ljusstyrka*getDiameter();
        for (Himlakropp* k : kroppar){
            vikt += k->getVikt();
            if (Stjärna* s = dynamic_cast<Stjärna*>(k)){
                vikt += ljusstyrka;
            }
        }
    } 
    static Stjärna* getInstance(string n, int d, int l);   
    void addKropp(Himlakropp* k){
        kroppar.push_back(k);
    }
    

    protected: 
    Stjärna(string n, int d, int l) : Himlakropp(n,d), ljusstyrka(l){}

    private:
    int ljusstyrka;
    vector<Himlakropp*> kroppar;
};
Stjärna* Stjärna::getInstance(string n, int d, int l) { return new Stjärna(n,d,l); }