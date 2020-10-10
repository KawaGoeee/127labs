/*
 * imgops.c - Simple operations on images
 *
 * C laboratory exercises.
 * Richard Vaughan, 2014.
 */

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*-------------------------------------------------
  PART 0: OPERATIONS ON A PIXEL 
*/

// get the value in the array at coordinate (x,y)
uint8_t get_pixel( const uint8_t array[], 
           unsigned int cols, 
           unsigned int rows,
           unsigned int x,
           unsigned int y )
{
    assert( x < cols );
    assert( y < rows );
    return array[ y*cols + x ];
}

// set the pixel at coordinate {x,y} to the specified color
void set_pixel( uint8_t array[], 
        unsigned int cols, 
        unsigned int rows,
        unsigned int x,
        unsigned int y,
        uint8_t color )
{
    assert( x < cols );
    assert( y < rows );
    array[ y * cols + x ] = color;
} 


/*-------------------------------------------------
  PART 1: OPERATIONS ON THE WHOLE IMAGE 
*/


/* TASK 1 - Easy functions to get started */

// Set every pixel to 0 (black) 
void zero( uint8_t array[], unsigned int cols, unsigned int rows )
{
  memset( array, 0, cols*rows*sizeof(uint8_t));
  // your code here.
}

// Returns a pointer to a freshly allocated array that contains the
// same values as the original array, or a null pointer if the
// allocation fails. The caller is responsible for freeing the array
// later.
uint8_t* copy( const uint8_t array[], unsigned int cols, unsigned int rows )
{
  uint8_t *arr = (uint8_t *) malloc(cols*rows*sizeof(uint8_t));
  // your code here

  // if(arr!=NULL) {
  //   return arr;
  // }else {
  //   return 1;
  // }
  return arr;
}

// Return the darkest color that appears in the array; i.e. the
// smallest value
uint8_t min( const uint8_t array[], unsigned int cols, unsigned int rows )
{
  uint8_t minValue=255;
  for(unsigned int i=0; i<cols*rows; i++) {
    minValue = minValue < array[i] ? minValue : array[i];
  }
  // your code here
  return minValue;
}

// Return the lightest color that appears in the array; i.e. the
// largest value
uint8_t max( const uint8_t array[], unsigned int cols, unsigned int rows )
{
  uint8_t maxValue=0;
  for(unsigned int i=0; i<cols*rows; i++) {
    maxValue = maxValue > array[i] ? maxValue : array[i];
  }
  // your code here
  return maxValue;
}

// TASK 2

//  Replace every instance of pre_color with post_color.
void replace_color(uint8_t array[], unsigned int cols, unsigned int rows, uint8_t pre_color, uint8_t post_color)
{
  for(unsigned int i=0; i<cols*rows; i++) {
    if(array[i]==pre_color) {
      array[i]=post_color;
    }
  }
  // your code here
}

/* TASK 3  - two functions */


// flip the image, left-to-right, like in a mirror.
void flip_horizontal( uint8_t array[], unsigned int cols, unsigned int rows )
{
  for(unsigned int i=0; i<rows; i++) {
    for(unsigned int j=0; j<cols/2; j++) {
      uint8_t copy = array[j+i*cols];
      array[j+i*cols] = array[(cols-j)-1 + i*cols];
      array[(cols-j)-1 + i*cols] = copy;
    }
  }
  // your code here
}

// flip the image top-to-bottom.
void flip_vertical( uint8_t array[], 
            unsigned int cols, 
            unsigned int rows )
{
  for(unsigned int i=0; i<cols; i++) {
    for(unsigned int j=0; j<rows/2; j++) {
      int copy = array[i+j*cols];
      array[i+j*rows] = array[i + (rows-j-1)*cols];
      array[i + (rows-j-1)*cols] = copy;
    }
  }
    // your code here
}

/* TASK 4 */

// Find the first coordinate of the first pixel with a value that
// equals color. Search from left-to-right, top-to-bottom. If it is
// found, store the coordinates in *x and *y and return 1. If it is
// not found, return 0.
int locate_color(  const uint8_t array[], 
		   unsigned int cols, 
		   unsigned int rows,
		   uint8_t color,
		   unsigned int *x,
		   unsigned int *y )
{
  for(unsigned int i=0; i<rows; i++) {
    for(unsigned int j=0; j<cols; j++) {
      if(get_pixel(array, cols, rows, j, i) == color) {
        *x = j;
        *y = i;
        return 1;
      }
    }
  }
  // your code here
  return 0;
}


/* TASK 5 */

// Invert the image, so that black becomes white and vice versa, and
// light shades of grey become the corresponding dark shade. 
void invert( uint8_t array[], 
         unsigned int cols, 
         unsigned int rows )
{
  for(unsigned int i=0; i<cols*rows; i++) {
    array[i] = 255-array[i];
  }
    // your code here
}

/* TASK 6 */

// Multiply every pixel by scale_factor, in order to brighten or
// darken the image. Resulting values are rounded to the nearest
// integer (0.5 rounded up) and any resulting value over 255 is
// thresholded to 255.
void scale_brightness( uint8_t array[],
            unsigned int cols,
            unsigned int rows,
            double scale_factor )
{
  for(unsigned int i=0; i<cols*rows; i++) {
    float v = round(array[i]*scale_factor);
    array[i] = v>255 ? 255:v;
  }
  // your code here
}


/* TASK 7 */

// Normalize the dynamic range of the image, i.e. Shift and scale the
// pixel colors so that that darkest pixel is 0 and the lightest pixel
// is 255. Hint: you already wrote min() and max(). 
void normalize( uint8_t array[],
        unsigned int cols,
        unsigned int rows )
{
  uint8_t maxValue = max(array, cols, rows);
  uint8_t minValue = min(array, cols, rows);

  double scale = 255.0/(maxValue-minValue);
  scale_brightness(array, cols, rows, scale);
  
    // your code here
}

/* TASK 8 */

// Return a new image of size rows/2 by cols/2 If the original image              
// has an odd number of columns, ignore its rightmost column. If the              
// original image has an odd number of rows, ignore its bottom row.               
// The value of a pixel at (p,q) in the new image is the average of               
// the four pixels at (2p,2q), (2p+1,2q), (2p+1,2q+1), (2p,2q+1) in               
// the original image.                                                            
uint8_t* half( const uint8_t array[],
	       unsigned int cols,
	       unsigned int rows )
{
  unsigned int newCols = cols/2==0 ? cols/2 : (cols-1)/2;
  unsigned int newRows = rows/2==0 ? rows/2 : (rows-1)/2;

  uint8_t* newImg = (uint8_t *) malloc(newCols*newRows*sizeof(uint8_t));

  assert(newImg != 0);

  for(unsigned int i=0; i<newRows; i++) {
    for(unsigned int j=0; j<newCols; j++) {
      // uint8_t colSum = get_pixel(array, cols, rows, 2j, 2i) + array[2j+1+2i*cols];
      // uint8_t rowSum = array[2j+(2i+1)*cols] + array[2j+1+(2i+1)*cols];
      uint8_t total = get_pixel(array, cols, rows, 2j, 2i)
                    + get_pixel(array, cols, rows, 2j, 2i+1)
                    + get_pixel(array, cols, rows, 2j+1, 2i)
                    + get_pixel(array, cols, rows, 2j+1, 2i+1);

      set_pixel(newImg, newCols, newRows, j, i, (int)round(total/4.0));
    }
  }
  return newImg;
  // your code here
  return NULL;
}




/*-------------------------------------------------
  PART 2: OPERATIONS ON IMAGE SUB-REGIONS

  These functions operate only on a rectangular region of the array
  defined by a (left,top) corner (i.e. closer to the image origin) and
  (right,bottom) corner (i.e. further from the image origin).

  The rectangle edges of a rectangular region are aligned with the x,y axes. 
  
  The region includes all the columns from [left, right-1] inclusive,
  and all the rows from [top, bottom-1] inclusive.
  
  In every case, you may assume that left <= right and top <= bottom:
  do not need to test for this.

  The area of the region is right-left * bottom-top pixels, which
  implies that if left == right or top == bottom, the region has no
  area and is defined as "empty". Each function notes how to handle
  empty regions.
 
  In every function, you can use assert() to test bounds on the region
  corners.
*/

/* TASK 9 */

// Set every pixel in the region to color. If the region is empty, the
// image must remained unchanged.
void region_set( uint8_t array[], 
         unsigned int cols, 
         unsigned int rows,
         unsigned int left,
         unsigned int top,
         unsigned int right,
         unsigned int bottom,
         uint8_t color )
{
  if(!(left==right) && !(top==bottom)) {

    for(unsigned int i=left; i<right; ++i) {
      for(unsigned int j=top; j<bottom; ++j) {
        set_pixel(array, cols, rows, i, j, color);
      }
    }
  }
    // your code here
}

/* TASK 10 */

// Return the sum of all the pixels in the region. Notice the large
// return type to handle potentially large numbers. Empty regions
// return the sum 0.
unsigned long int region_integrate( const uint8_t array[], 
                    unsigned int cols, 
                    unsigned int rows,
                    unsigned int left,
                    unsigned int top,
                    unsigned int right,
                    unsigned int bottom )
{
  unsigned long int sum=0;

  if(!(left==right) && !(top==bottom)) {

    for(unsigned int i=left; i<right; ++i) {
      for(unsigned int j=top; j<bottom; ++j) {
        sum += get_pixel(array, cols, rows, i, j);
      }
    }
    return sum;
  }
    // your code here
    return 0;
}

/* TASK 11 */

// Get a new image which is a copy of the region. Empty regions return
// a null pointer. If memory allocation fails, return a null
// pointer. The caller is responsible for freeing the returned array
// later.
uint8_t* region_copy( const uint8_t array[], 
              unsigned int cols, 
              unsigned int rows,
              unsigned int left,
              unsigned int top,
              unsigned int right,
              unsigned int bottom )
{
  unsigned int newCols = right-left;
  unsigned int newRows = top-bottom;
  unsigned int colorValue;

  uint8_t* newImg = (uint8_t *)malloc(newCols*newRows*sizeof(uint8_t));
  assert(newImg);

  if(!(left==right) && !(top==bottom)) {

    for(unsigned int i=left; i<right; ++i) {
      for(unsigned int j=top; j<bottom; ++j) {
        colorValue = get_pixel(array, cols, rows, i, j);
        set_pixel(newImg, newCols, newRows, i-left, j-top, colorValue);
      }
    }
    return newImg;
  }
    // your code here
    return NULL;
}


