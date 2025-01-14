unsigned int swap(unsigned int bits){
    unsigned int temp1 = (0x0000ffff & bits) << 16;
    unsigned int temp2 = (0xffff0000 & bits) >> 16; 
    return temp1 | temp2;
}