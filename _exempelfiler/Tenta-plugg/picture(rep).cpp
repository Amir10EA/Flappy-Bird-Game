#include <string>
#include <map>
using namespace std;

struct PictureData{
 int width, height; // Bildens bredd och höjd
 unsigned int* pixels; // Pekare till själva pixeldata
 }; 


class Picture{
public:
 Picture(std::string filename){
 data = new PictureData();
 data->pixels = new unsigned int[data->width*data->height];
 counts[data] = 1;
 }
 Picture(const Picture& other);
 ~Picture();
 const Picture& operator=(const Picture& other);

private:
 PictureData* data;
 static std::map<PictureData*, int> counts;
}; 



Picture::Picture(const Picture& other) : data(other.data){
if (data){
    counts[data]++;
}
}
 Picture::~Picture(){
if (data && --counts[data] < 1){
    delete[] data->pixels;
    delete data;
    counts.erase(data);
}
 }
 const Picture& Picture::operator=(const Picture& other){
if (data != other.data){
    if (data && --counts[data] < 1){
    delete[] data->pixels;
    delete data;
    counts.erase(data);
}
data = other.data;
counts[data]++;
}
return *this;
}

