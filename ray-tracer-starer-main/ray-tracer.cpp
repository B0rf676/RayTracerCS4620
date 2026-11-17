/// Include the image write library and enable it
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

/// Uncomment these lines if you want to debug using couts
#include <iostream>
#include <vector>
#include "Vector3.hpp"
#include "Triangle.hpp"
#include "file_util.h"

using namespace std;

const int w = 680;
const int h = 680;

unsigned char pixels[w * h * 3];

vector<Triangle> triangles;

Vector3 background_color = Vector3{0, 128, 0};

float trace_ray_distance(Vector3 origin, Vector3 direction){

  float closest_t = INFINITY;

  for(const Triangle &triangle : triangles){
    //Find where we hit the plane
      Vector3 edge_one = triangle.one - triangle.two;
      Vector3 edge_two = triangle.three - triangle.two;
      Vector3 p = edge_two.cross(edge_one);
      Vector3 abc = p.Normalize();
      float d = -abc.dot(triangle.one);

      float t = -(abc.dot(origin) + d)/abc.dot(direction);

      if(t > closest_t || t <= 0){
        continue;
      }

      Vector3 collision_point = direction * t + origin;

      Vector3 minus_one = collision_point - triangle.one;
      Vector3 minus_two = collision_point - triangle.two;
      Vector3 minus_three = collision_point - triangle.three;

      float triangle_area = p.length()/2;

      float area_one = minus_two.cross(minus_three).length()/2;
      float area_two = minus_three.cross(minus_one).length()/2;
      float area_three = minus_one.cross(minus_two).length()/2;

      float u = area_one / triangle_area;
      float v = area_two / triangle_area;
      float a = area_three / triangle_area;

      float sum = u + v + a;

      float diff = abs(1 - sum);
      if(diff > .00001f || isnan(sum)){
        //i'm not in the triangle
      }
      else{
        //i'm in the triangle
        closest_t = t;
      }
  }
  return closest_t;
}

Vector3 trace_ray(Vector3 origin, Vector3 direction, float red, float green, float blue, int bounces = 5){

  Vector3 color = Vector3{background_color.x, background_color.y, background_color.z};
  if(bounces <= 0){
    return background_color;
  }

  float closest_t = INFINITY;

  for(const Triangle &triangle : triangles){
    //Find where we hit the plane
      Vector3 edge_one = triangle.one - triangle.two;
      Vector3 edge_two = triangle.three - triangle.two;
      Vector3 p = edge_two.cross(edge_one);
      Vector3 abc = p.Normalize();
      float d = -abc.dot(triangle.one);

      float t = -(abc.dot(origin) + d)/abc.dot(direction);

      Vector3 collision_point = direction * t + origin;

      if(t > closest_t || t <= 0){
        continue;
      }

      Vector3 minus_one = collision_point - triangle.one;
      Vector3 minus_two = collision_point - triangle.two;
      Vector3 minus_three = collision_point - triangle.three;

      float triangle_area = p.length()/2;

      float area_one = minus_two.cross(minus_three).length()/2;
      float area_two = minus_three.cross(minus_one).length()/2;
      float area_three = minus_one.cross(minus_two).length()/2;

      float u = area_one / triangle_area;
      float v = area_two / triangle_area;
      float a = area_three / triangle_area;

      float sum = u + v + a;

      float diff = abs(1 - sum);
      if(diff > .00001f || isnan(sum)){
        //i'm not in the triangle
      }
      else{
        //i'm in the triangle
        closest_t = t;

        Vector3 base_color = Vector3{red, green, blue};
        Vector3 light_direction = Vector3{.5, 1, .5}.Normalize();
        
        Vector3 ambient = base_color * .1;
        Vector3 normal = p.Normalize();

        float strength = max(0.f, light_direction.dot(normal));

        Vector3 diffuse = base_color * strength;
        if(trace_ray_distance(collision_point, light_direction) != INFINITY){
          diffuse = Vector3{0,0,0};
        }

        Vector3 reflective = Vector3{0, 0, 0};
        if(true){
          Vector3 reflection_direction = direction - normal * 2 * normal.dot(direction);
          reflective = trace_ray(collision_point, reflection_direction, red, green, blue, bounces - 1) * 0.5;
          diffuse *= 0.5;
          ambient *= 0.5;
        }

        Vector3 _color = ambient + diffuse + reflective;

        color = _color;
      }
  }
  return color;
}

int main()
{

  float red;
  float green;
  float blue;

  ///Parsing obj 
  vector<string> lines = readLines("test2.obj");

  vector<Vector3> vertices;

  for(const string& line: lines){
    //cout << line << endl;
    vector<string> parts = split(line, ' ');
    //cout << parts[0] << endl;

    if(parts[0] == "v"){
      Vector3 vertex = Vector3{stof(parts[1]), stof(parts[2]), stof(parts[3])};
      //cout << "Vertices: " << vertex.x << ", " << vertex.y << ", " << vertex.z << endl;
      vertices.push_back(vertex);
    }
    else if(parts[0] == "f"){

      vector<float> faceIndex;

      for(size_t i = 1; i < parts.size(); i++){
        if(parts[i].empty()){
          continue;
        }

        vector<string> splitParts = split(parts[i], '/');
        float vertexIndex = stof(splitParts[0]) - 1;
        faceIndex.push_back(vertexIndex);
      }

      for(size_t i = 1; i + 1 < faceIndex.size(); i++){

      Vector3 vertex1 = vertices[faceIndex[0]];
      Vector3 vertex2 = vertices[faceIndex[i]];
      Vector3 vertex3 = vertices[faceIndex[i + 1]];

      Triangle triangle = Triangle{vertex1, vertex2, vertex3};
      triangles.push_back(triangle);

      }
    }
  }  

  cout << "Triangles loaded: " << triangles.size() << endl;

  vector<string> realColor = readLines("test2.mtl");

  cout << "Material file read" << endl;

  for(const string& line: realColor){
    vector<string> colorLines = split(line, ' ');
    if(colorLines[0].empty()){
      continue;
    }
    else if(colorLines[0] == "Kd"){
      red = stof(colorLines[1]) * 255;
      blue = stof(colorLines[2]) * 255;
      green = stof(colorLines[3]) * 255;
    }
  }

  cout << "Colors loaded" << endl;


  Vector3 camera_origin = Vector3{0, 0, 1};
  Vector3 camera_look_at = Vector3{0, 0, 0};
  Vector3 camera_up = Vector3{0, 1, 0};

  /// Loop over each line doing down
  for (int y = 0; y < h; y++)
  {
    //Progress bar cause this could take a while
    if (y % 10 == 0) {
      cout << "Progress: " << (y * 100 / h) << "% (Row " << y << "/" << h << ")" << endl;
    }

    /// While going down, loop over every pixel going right
    for (int x = 0; x < w; x++)
    {

      /// Figure out our index in the 1d array of pixels
      int index = y * w * 3 + x * 3;

      /// The value of the red channel (0-255)
      unsigned char r = background_color.x;

      /// The value of the green channel (0-255)
      unsigned char g = background_color.y;

      /// The value of the blue channel (0-255)
      unsigned char b = background_color.z;

      // How do I ray trace?

      Vector3 target{
          x / (float)w * 2 - 1, -(y / (float)h * 2 - 1), 0};

      Vector3 temp = (target - camera_origin);
      Vector3 ray = temp.Normalize();

      Vector3 color = trace_ray(camera_origin, ray, red, green, blue);

      r = color.x;
      g = color.y;
      b = color.z;

      /// Assign the r, g, and b values to the pixel at index
      pixels[index] = r;
      pixels[index + 1] = g;
      pixels[index + 2] = b;
    }
  }

  /// Write the final image as a png
  stbi_write_png("image.png", w, h, 3, pixels, w * 3);
  return 0;
}