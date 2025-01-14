#include <string>
#include <map>

struct PictureData{
 int width, height; 
 unsigned int* pixels; 
 }; 

 class Picture{
public:
 Picture(std::string filename);
 Picture(const Picture& other);
 ~Picture();
 const Picture& operator=(const Picture& other);

private:
 PictureData* data;
 static std::map<PictureData*, int> counts;

}; 

 Picture::Picture(std::string filename){
 data = new PictureData();
 data->pixels = new unsigned int[data->width*data->height];
 counts[data] = 1;
 } 

 Picture::Picture(const Picture& other) : data(other.data){
        counts[data]++;
 }

 Picture::~Picture(){
    if (this && --counts[data] < 1){
        delete data;
        delete[] data->pixels;
        counts.erase(data);
    }
 }

 const Picture& Picture::operator=(const Picture& other){
    if (data != other.data){
        if (this && --counts[data] < 1){
        delete data;
        delete[] data->pixels;
        counts.erase(data);
    }
        data = other.data;
        counts[data]++;
    }
    return *this;
 }