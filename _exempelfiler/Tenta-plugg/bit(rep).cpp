unsigned int get(unsigned long int uli, int nr){
    return (uli >> nr*4) & 15;
}

void set(unsigned long int& uli, int nr, unsigned int value){
    uli &= ~(15 << nr*4);
    uli |= (value << nr*4); 
}