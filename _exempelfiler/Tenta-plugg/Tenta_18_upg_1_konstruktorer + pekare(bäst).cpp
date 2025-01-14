#include <string>
#include <map>

struct PictureData{
 int width, height; // Bildens bredd och höjd
 unsigned int* pixels; // Pekare till själva pixeldata
 };

 class Picture{
public:
 Picture(std::string filename){
 data = new PictureData();
//  data->width = // läser in width
//  data->height = // laser in height
 data->pixels = new unsigned int[data->width*data->height];
 // laser in bilddata i arrayen ovan
 counts[data]++;
 
 
 } // constructor
 // Andra medlemsfunktioner, oväsentliga för uppgiften
~Picture(){
    counts[data]--;
    if (counts[data] == 0){
        delete[] data -> pixels;
        delete data;
        counts.erase(data);
    }
 }

  Picture(const Picture& other) {
        data = other.data;
        counts[data]++;
 }
 
 const Picture& operator=(const Picture& other) {
    if (this != &other){
        counts[data]--;
        if (counts[data] == 0){
            delete [] data -> pixels;
            delete data;
            counts.erase(data);
        }
        
        data = other.data;
        counts[data]++;
    }
    return *this;  
 }

private:
 PictureData* data;
 static std::map<PictureData*, int> counts;
}; 