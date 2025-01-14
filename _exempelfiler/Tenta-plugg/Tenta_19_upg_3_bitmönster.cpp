unsigned int get(unsigned long int uli, int nr){
    return ((uli >> (nr*4)) & 0xf);
}



void set(unsigned long int& uli, int nr, unsigned int value){ 
uli &= ~(0xf <<(nr*4));
uli |= (value << (nr*4));
}
