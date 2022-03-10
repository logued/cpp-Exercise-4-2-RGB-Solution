#include <iostream>
using namespace std;

// Question 1 - RGB Pixel                   Feb 2022

// Rgb struct (class) represents a pixel with Red, Green & Blue channels
// Each channel (colour) is represented by an intensity value  in range 0.0->1.0

struct Rgb {
    // Constructor that sets default values of 0 if no arguments are provided
    Rgb() : r(0), g(0), b(0) {}

    // Constructor that takes three float values representing
    // the intensity of Red, Green, Blue (1.0 is full intensity)
    Rgb(float rr, float gg, float bb) : r(rr), g(gg), b(bb) {}

    // Member variables (fields)
    float r, g, b;
};

void display_pixel_rgb( const Rgb& pixel);
void apply_red_filter( Rgb& pixel );
void blackout_image_array_notation(int width, int height, Rgb image[]);
void blackout_image_poinyter_notation(int width, int height, Rgb* ptr_image);

int main() {
    std::cout << "RGB Pixel representation" << std::endl;

    // create some Rgb structs (objects) - (these are struct variables on the stack)
    Rgb whitePixel(1.0, 1.0, 1.0);
    Rgb blackPixel(0.0, 0.0, 0.0);
    Rgb pinkPixel(1.0, .75, .79);    // look up Hex value for pink to find proportions of RGB

    display_pixel_rgb( whitePixel);
    display_pixel_rgb( blackPixel );
    display_pixel_rgb( pinkPixel );

    //TODO apply the red filter to the whitePixel
    // then, display whitePixel
    apply_red_filter(whitePixel);
    display_pixel_rgb(whitePixel);

    //TODO Dynamically Allocate a block of memory
    // to store an image of pixels of size 200 x 100

    int num_pixels = 200 * 100; // image size in pixels
    Rgb* image = new Rgb[num_pixels]; // will call no arg constructor for each Rgb object

    // allocate memory with no constructor call
//    char* buffer = new char[num_pixels*sizeof(float)*3];
//    float* ptr_float = (float*)buffer;
//    // now use the pointer to float to
//    // access each float value
//    Rgb* ptr_Rgb = (Rgb*)buffer;
//    // now use pointer to Rgb struct to access
//    ptr_Rgb->r =0.23;


    for( int i=0; i<num_pixels; i++) {
        cout << image[i].r <<":"
            << image[i].g <<":"
            << image[i].b << ",";
    }

    blackout_image_array_notation(200,100,image);
    blackout_image_poinyter_notation(200,100,image);


    return 0;
}

// Display the Red, Green and Blue channel intensities for and Rgb pixel object
// Pass-by-Value is used here
void display_pixel_rgb( const Rgb& pixel ) {
    cout << "Red=" << pixel.r
         << " Green=" << pixel.g
         << " Blue=" << pixel.b << endl;
}

void apply_red_filter( Rgb& pixel ) {

    //TODO a red filter sets all other fields to zero
    // (and leaves red as it was) code here....

    pixel.g = 0.0;
    pixel.b = 0.0;
}

void blackout_image_array_notation(int width, int height, Rgb image[]) {
    for(int i=0; i<width*height; i++) {
        image[i].r = 0.0;
        image[i].g = 0.0;
        image[i].b = 0.0;
    }
}

void blackout_image_poinyter_notation(int width, int height, Rgb* image) {

    Rgb* ptr = image;
    for(int i=0; i<width*height; i++) {
        ptr->r = 0.0;
        ptr->g = 0.0;
        ptr->b = 0.0;
        ptr++;
    }
}