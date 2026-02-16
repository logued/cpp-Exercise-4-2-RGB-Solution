#include <iostream>
using namespace std;

// Exercise 4 Question 2 - RGB Pixel struct            Feb 2026

// Rgb struct (class) represents a one pixel with Red, Green & Blue channels
// Each channel (colour) is represented by an intensity value in range 0.0->1.0 (floating point value)

struct Rgb {
    // Member variables (fields) are PUBLIC in a struct
    float _red;    // red, green, and blue data members (fields)
    float _green;
    float _blue;

    // No-argument Constructor that uses an initializer list to
    // set default values of 0.0 for the three fields.
    Rgb() : _red(0), _green(0), _blue(0) {}   // _red(0) initializes field _red to zero

    // Constructor that takes three float values representing
    // the intensity of Red, Green, Blue (1.0 is full intensity)
    Rgb(float red, float green, float blue) : _red(red), _green(green), _blue(blue) {}
};

void display_pixel_rgb(const Rgb &pixel);

void apply_red_filter(Rgb &pixel);

void blackout_image_array_notation(int width, int height, Rgb image[]);

void blackout_image_pointer_notation(int width, int height, Rgb *ptr_Rgb);

int main() {
    std::cout << "RGB Pixel representation" << std::endl;

    // create some Rgb structs (objects) - (these are struct variables on the stack)
    const Rgb whitePixel(1.0, 1.0, 1.0); // const - so that it can not be changed
    const Rgb blackPixel(0.0, 0.0, 0.0);
    const Rgb pinkPixel(1.0, .75, .79);    // look up Hex value for pink to find proportions of R

    Rgb aPixel(.2,.8,.6); // non-const pixel that we can modify

    display_pixel_rgb(whitePixel);  // pass by reference
    display_pixel_rgb(blackPixel);
    display_pixel_rgb(pinkPixel);

    //TODO apply the red filter to the whitePixel
    // then, display whitePixel
    cout << "aPixel to modify = " ;
    display_pixel_rgb(aPixel);
    apply_red_filter(aPixel);   // apply filter to the pixel (it will be changed)
    cout << "aPixel after red filter was applied = ";
    display_pixel_rgb(aPixel);

    //TODO Dynamically Allocate a block of memory
    // to store an image of size 20 x 10 pixels

    int width = 10; // image dimensions (that we may read from a file)
    int height = 10;
    int total_pixels = width * height; // image size in pixels (width x height)

    Rgb * image = new Rgb[total_pixels];  // constant pointer to an image
    // The above call will result in the no-argument constructor
    // being called for each Rgb object in the array,
    // setting all fields to 0.0

    cout << "R,G,and B values for all pixels making up the image:" << endl;
    for (int i = 0; i < total_pixels; i++) {
        cout << image[i]._red << ":"      // fields are public in a struct
             << image[i]._green << ":"
             << image[i]._blue << " ";
        if (i % width == width - 1) {
            cout << endl;
        }
    }

    blackout_image_array_notation(width, height, image);

    blackout_image_pointer_notation(width, height, image);

    delete [] image;    // FREE up the allocated memory array to avoid memory leaks.
    image = nullptr;    // prevent dangling pointers.

    // Extra:
    // If we wanted to Dynamically Allocate the memory block,
    // but with no constructor call, then we could do the following:
    char *buffer = new char[total_pixels * sizeof(float) * 3]; // 'char' is 1 byte long
    float *ptr_float = (float *) buffer;  // cast to a 'pointer to float'
    // now use the pointer to float to
    // access each float value, let's set the first pixel's values
    *ptr_float = 0.2; // sets red
    ptr_float++; // move to green part
    *ptr_float++ = 0.4;    // set green & move on // access element, then afterwards increment pointer
    *ptr_float = 0.6; // set blue

    cout << "Access first pixel in array using ptr_float:" << endl;
    ptr_float = reinterpret_cast<float *>(buffer);  // reset to point at start  // old cast = "(float*)buffer"
    cout << "First pixel, red value = " << *ptr_float << endl;
    ptr_float++;    // move forward by one float length
    cout << "First pixel, green value = " << *ptr_float << endl;
    ptr_float++;
    cout << "First pixel, blue value = " << *ptr_float << endl;

    // if we wish to access the array elements as Rgb structs
    // then we declare a pointer to an Rgb struct, and use it
    // to dereference Rgb structs
    Rgb *ptr_Rgb = (Rgb *) buffer;    // point at first element in array
    // now use pointer to Rgb struct to access
    cout << "Access first pixel in array using ptr_Rgb:"<<endl;

    cout << "First pixel, red value = " << ptr_Rgb->_red << endl;
    cout << "First pixel, green value = " << ptr_Rgb->_green << endl;
    cout << "First pixel, blue value = " << ptr_Rgb->_blue << endl;

    delete [] buffer;   // free up the dynamically allocated buffer memory block
    // Note that the buffer was declared as an array of char, so we need to use the "[]"
    // when deleting/freeing up the buffer memory.

    buffer = nullptr;
    cout << "Program finished, goodbye!";
    return 0;
}

// Display the Red, Green and Blue channel intensities
// for a nRgb pixel object.
//
void display_pixel_rgb(const Rgb &pixel) {    // parameter is a reference to a constant Rgb struct
    cout << "Red=" << pixel._red << ":"
         << " Green=" << pixel._green << ":"
         << " Blue=" << pixel._blue << endl;
}

// Reference parameter does not use "const" because
// the reference needs to modify the passed Rgb struct
//
void apply_red_filter(Rgb &pixel) {

    //TODO a red filter sets all other fields to zero
    // (and leaves red as it was) code here....

    pixel._green = 0.0;
    pixel._blue = 0.0;
}

// Array notation.  The image[] parameter is an array of Rgb structs.
// It is equivalent to a pointer to an Rgb struct, but here we access it
// using array notation. (Array notation is easier to read)
//
void blackout_image_array_notation(int width, int height, Rgb image[]) {
    for (int i = 0; i < width * height; i++) {
        image[i]._red = 0.0;
        image[i]._green = 0.0;
        image[i]._blue = 0.0;
    }
}

// Uses pointer notation.  Parameter declared as a pointer to an Rgb struct.
// In this function, we manipulate the pointer using pointer arithmetic to
// iterate through the elements of the array.
// Each Rgb struct represents one pixel.
//
void blackout_image_pointer_notation(int width, int height, Rgb *ptr_Rgb) {

    for (int i = 0; i < width * height; i++) {
        ptr_Rgb->_red = 0.0;
        ptr_Rgb->_green = 0.0;
        ptr_Rgb->_blue = 0.0;
        ptr_Rgb++;  // increment pointer (by the length of one Rgb structure)
    }
}