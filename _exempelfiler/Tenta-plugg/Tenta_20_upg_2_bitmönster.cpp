#include <iostream>
using namespace std;

unsigned int bitskiftLeft( unsigned int value, int steps );
unsigned int bitskiftRight( unsigned int value, int steps );
void visaBitar( unsigned int value );

unsigned int bitskiftLeft( unsigned int value, int steps ){
    cout << "bitskift vänster " << steps << " bitar:" << endl;
    cout << endl; 
    return value << steps;
}

unsigned int bitskiftRight( unsigned int value, int steps ){
    cout << "bitskift höger " << steps << " bitar:" << endl;
    cout << endl; 
    return value >> steps;
}

void visaBitar(unsigned int value) {
    cout << "( Tal i decimalform = Tal i binärform )" << endl;
    cout << value << " = "; 
    int counter = 0;
    for (int i = 31; i >= 0; i--) { 
        counter++;
        if (value & (1U << i)) {
            cout << 1;
        } else {
            cout << 0;
        }
        if (counter % 8 == 0 && i != 0) { 
            cout << " ";
        }
    }
    cout << endl; 
    cout << endl; 
}

int main () {
visaBitar( 780 );
visaBitar( bitskiftLeft(780, 8) );
visaBitar( bitskiftRight(780, 8) );

return 0;
}
