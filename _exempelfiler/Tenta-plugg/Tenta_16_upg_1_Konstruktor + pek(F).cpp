#include <stdexcept>
#include <cstring>
class String
{
public:
    String(char *str);
    char get(int index) const
    {
        if (srep)
            return srep->chars[index];
            else 
            throw std::out_of_range("Null StringRep object");
    }
    void put(char ch, int index)
    { 
        if (srep==nullptr)throw std::out_of_range("Null StringRep object");
        if (index <0 || index>srep->size) throw std::out_of_range("fel index");
        StringRep* newRep  = new StringRep;
        newRep->size = srep->size;
        newRep->refCount = 1;
        newRep->chars = new char[srep->size];
        std::strcpy(newRep->chars, srep->chars);
        srep->refCount--;
        srep = newRep;
    }
    ~String();
    String(const String &other);
    const String &operator=(const String &other);

private:
    StringRep *srep;
};

String::String(const String &other) : srep(other.srep)
{
    if (srep != nullptr)
    {
        srep->refCount++;
    }
}

String::~String()
{
    if (srep != nullptr && --srep->refCount == 0)
    {
        delete srep;
        delete [] srep->chars;
    }
}

const String &String::operator=(const String &other)
{
    if (this == &other)
    {
        if (srep && --srep->refCount == 0)
        {
            delete srep;
            delete [] srep->chars;
        }
        
        srep = other.srep;
        if (srep)
        srep->refCount++;
    }

    return *this;
}

struct StringRep
{
    int size;
    char *chars;
    int refCount;
};