typedef unsigned int Unit32;
typedef unsigned char Byte;
enum Color {RED=0, GREEN=1, BLUE=2, ALPHA=3};

Byte getColorComponent(Unit32 pixel, Color color){
    return ((pixel << color*8) & 0xFF);
}

void setColorComponent(Unit32 pixel, Byte value, Color color){
    pixel &= ~(0xFF000000 >> color*8); //nollställ values plats
    Unit32 mask = ((value | 0x00000000) << 24); //nu har vi en mask med value på positionen längst åt vänster
    mask = mask >> color*8; //flyttar value till sin rätta position
    pixel |= mask;
}