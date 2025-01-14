#include <string>
#include <vector>

class Himlakropp {

public:
virtual int getVikt() const = 0;
virtual ~Himlakropp();
protected:
Himlakropp(std::string n) : name(n){}

private:
std::string name;
Himlakropp(const Himlakropp&) = delete;
const Himlakropp& operator=(const Himlakropp&) = delete;
};

//----------------------------------------------------------------

class cirklulärHimlakropp : public Himlakropp {
public:
virtual int getVikt() const = 0;
virtual ~cirklulärHimlakropp();
int getDiameter() const { return diameter; }

protected:
cirklulärHimlakropp(std::string n, int d) : Himlakropp(n), diameter(d){}

private:
int diameter;
};

//----------------------------------------------------------------

class Måne : public cirklulärHimlakropp {
public:
static Måne* getInstance(std::string n, int d, int k);
virtual ~Måne();
int getVikt() const {
    return (10*getDiameter() - kratrar);
}
int getKratrar() const { return kratrar;}

protected:
Måne(std::string namn, int d, int k) : cirklulärHimlakropp(namn, d), kratrar(k){}  

private:
int kratrar;
};

Måne* Måne::getInstance(std::string n, int d, int k){ return new Måne(n, d, k);}

//----------------------------------------------------------------

class Planet : public cirklulärHimlakropp {
    public:
    int getVikt() const {
        return (atmosfär) ? (20*getDiameter() + måne->getVikt()) : (10*getDiameter()  + måne->getVikt()); 
    }

    bool harAtmosfär () const { return atmosfär; }
    virtual ~Planet(){
        delete måne;
        måne = nullptr; //?
    }
    Måne* getMåne() const { return måne;}

    void addMåne(Måne* other){
        if (måne && (måne != other)){
            delete måne; 
            måne = other;
        }
    }

    static Planet* getInstance(std::string namn, int d, bool a);
    static Planet* getInstance(std::string namn, int d, bool a, Måne* m);
    protected:
    Planet(std::string namn, int d, bool a, Måne* m) : cirklulärHimlakropp(namn, d), atmosfär(a), måne(m){}
    private:
    bool atmosfär;
    Måne* måne;
};

Planet* Planet::getInstance(std::string namn, int d, bool a){
    return new Planet(namn, d, a, NULL);
}
Planet* Planet::getInstance(std::string namn, int d, bool a, Måne* m){
    return new Planet(namn, d, a, m);
}

//----------------------------------------------------------------

class Stjärna : public cirklulärHimlakropp {
    public:
    int getVikt() const;

    void addKropp(Himlakropp* kropp ){
        kroppar.push_back(kropp);
    }
    virtual ~Stjärna(){
        for (Himlakropp* k : kroppar){
            delete k;
        }
        kroppar.clear();
    }

    static Stjärna* getInstance(std::string n, int d, int l);

    int getLjusstyrka() const { return ljusstyrka; } 
    
    protected: 
    Stjärna(std::string namn, int d, int l) : cirklulärHimlakropp(namn, d), ljusstyrka(l) {}

    private:
    int ljusstyrka;
    std::vector<Himlakropp*> kroppar;
};
    Stjärna* Stjärna::getInstance(std::string n, int d, int l){
    return new Stjärna(n, d, l);
    }

    int Stjärna::getVikt() const {
    int vikt = ljusstyrka * getDiameter();
    for (Himlakropp* k : kroppar) {
        if (Stjärna* s = dynamic_cast<Stjärna*>(k)) {
            vikt += s->getLjusstyrka();
        }
        vikt += k->getVikt();
    }
    return vikt;
}


   