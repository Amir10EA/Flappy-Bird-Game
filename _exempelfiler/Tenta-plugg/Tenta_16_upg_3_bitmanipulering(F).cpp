int changeEnianness(int value){
    int temp = 0x00000000;
    temp |= (value & 0xFF000000) >> 24;
    temp |= (value & 0x00FF0000) >> 8;
    temp |= (value & 0x0000FF00) << 8;
    temp |= (value & 0x000000FF) << 24;
    return temp;
}