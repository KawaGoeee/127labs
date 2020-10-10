#include <stdio.h>

// declaration of function to test
int InRectangle( float pt[2], float rect[4] );
 
int main()
{
  // define a rectangle from (1,1) to (2,2)
  float rect[4] = {1.0, 1.0, 2.0, 2.0 };
 
  // define a point that is inside the rectangle
  float p_in[2] = { 1.5, 1.5 };
 
  // define a point that is outside the rectangle
  float p_out[2] = {2.5, 0.5};
 
  // define a point that is on the edge of the rectangle
  float p_edge[2] = {1.0, 1.0};
 
  // =============================
 
  // test 1
  if( InRectangle( p_in, rect ) == 0 )
  {
    puts( "error: should return true for p_in." );
    return 1; // indicate error
  }
 
  // test 2
  if( InRectangle( p_out, rect ) != 0 )
  {
    puts( "error: should return false for p_out." );
    return 1; // indicate error
  }
 
  // test 3
  if( InRectangle( p_edge, rect ) == 0 )
  {
    puts( "error: should return true for p_edge." );
    return 1; // indicate error
  }
 
  printf("success!\n");
  return 0; // all tests passed
}


int InRectangle( float pt[2], float rect[4] ) {
  float x1, x2, y1, y2;

  x1 = rect[0] < rect[2] ? rect[0] : rect[2];
  x2 = rect[0] > rect[2] ? rect[0] : rect[2];
  y1 = rect[1] < rect[3] ? rect[1] : rect[3];
  y2 = rect[1] > rect[3] ? rect[1] : rect[3];

  // compare coordinates
  int res;
  if((pt[0]>=x1 && pt[0]<=x2) && (pt[1]>=y1 && pt[1]<=y2)) {
    res=1;
  }else {
    res=0;
  }
  return res;
}