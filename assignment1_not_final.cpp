#include <cassert>
#include <cstdint>
#include <iostream>
#include <vector>

#include "al/app/al_App.hpp"
#include "al/graphics/al_Image.hpp"
#include "al/math/al_Random.hpp"

using namespace al;
using namespace std;

class MyApp : public App {
 public:
  Mesh pic, rgb, hsv, extra;
  Mesh actual;

  Vec3f rgb_pos, hsv_pos, extra_pos;
 
  int key; 
  
  void onCreate() override {
    const char *filename = "data/wino2.jpg";
    auto imageData = Image(filename);
    if (imageData.array().size() == 0) {
      cout << "failed to load image" << endl;
      exit(1);
    }
    cout << "loaded image size: " << imageData.width() << ", "
         << imageData.height() << endl;

    int W = imageData.width();
    int H = imageData.height();
    
    pic.primitive(Mesh::POINTS);
    actual.primitive(Mesh::POINTS);
    rgb.primitive(Mesh::POINTS);
    hsv.primitive(Mesh::POINTS);
    extra.primitive(Mesh::LINES);



    // iterate through all the pixel, scanning each row
    for (int row = 0; row < H; row++) {
      for (int column = 0; column < W; column++) {
        auto pixel = imageData.at(column, H - row - 1);
        pic.vertex(1.0 * column / W, 1.0 * row / H, 0.0);
        pic.color(pixel.r / 255.0, pixel.g / 255.0, pixel.b / 255.0);

///////////////////rgb////////////////mapping/////
// a < v < b, -> a2 < v2 < b2  
// v2 = map(v, min, max, min_2, max_2)

// float map(float v, float min, ... )
// return () / * 

// x=.. 0, 255 -> -1, 1
// y=..
// z=..

    rgb_pos = {pixel.r /255.0, pixel.g /255.0, pixel.b /255.0};
    Color color(pixel.r/255.0, pixel.g/255.0, pixel.b/255.0);

    rgb.vertex(rgb_pos);
    rgb.color(color);

/////////////hsv///////////////////
        // double h = row / H * 360.0;
        // double s = 1 - (column / W);
        // double v = 1;
// float cmax = max(color);
// float cmin = min(color);
// float delta = cmax-cmin;

// S × cos(H*2*pi) , S × sin(H*2*pi), V

//        hsv.color(color);
        HSV c = color;
        hsv_pos = (c.s * cos(c.h * M_2PI), 
                   c.s * sin(c.h * M_2PI), 
                  c.v);

        hsv.vertex(c.s * cos(c.h * M_2PI), 
                   c.s * sin(c.h * M_2PI), 
                   c.v);

        hsv.color(c.h, c.s, c.v);

//        cout << hsv_pos << endl;
/////////////////////////////////////


          // return Vec3f(color);



        // initial setting of actual
        actual.vertex(1.0 * column / W, 1.0 * row / H, 0.0);
        actual.color(pixel.r / 255.0, pixel.g / 255.0, pixel.b / 255.0);
        

        // XXX you put more code here!
      }
    }

    // set the camera position back some (z=3) and center on (x=0.5, y=0.5)
    nav().pos(0.5, 0.5, 1);
  }


  
  // double t = 1.0;//app memeber variable
  void onAnimate(double dt) override {
    //  if (t <1.0){
    //     t += dt;//time(seconds) accumulate until the process stops
    //  }
     
    
    //  //use t as a parameter?
    //  //XXX any issues here?
    //  else{
    //     t = 1.0;  
    //  }
    //    t = 0.0;


    // hsv.color(c.h + dt/100.0, c.s , c.v)


    // XXX you put more code here!
    // hint modify `actual`
    // make an animation parameter (float) `t`

    
  
    // int size = actual.vertex().size();
    // int dist = rgb_pos.size();
    // actual.vertex()[0].lerp(actual.vertex()[actual.vertex().dist() -1], 0.01);
    // for (int i = 1; i < actual.vertex().dist(); i++) {
    //     actual.vertex()[i].lerp(actual.vertex()[i -1], 0.01);
    // }

    
  }

  bool onKeyDown(const Keyboard &k) override {
    // Use a switch to do something when a particular key is pressed
    switch (k.key()) {
      // For printable keys, we just use its character symbol:
      case '1':
        key = 1;
        break;
      case '2':
        key = 2;
        break;
      case '3':
        key = 3;
        break;
      case '4':
        key = 4;
        break;        // XXX you put more code here!
        // hint reset animation parameter

      default:
        break;
    }
    return true;
  }

  void onDraw(Graphics &g) override {
    g.clear(0.2f);
    g.meshColor();
    if (key == 1){
        g.draw(pic);
    }else if (key == 2){
        g.draw(rgb);
    }else if (key == 3){
        g.draw(hsv);
    }else if (key == 4){
      // g.draw();
    }
  }
};

int main() {
  MyApp app;
  app.configureAudio(48000, 512, 2, 0);
  app.start();
}
