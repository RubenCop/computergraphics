//
//  Framework for a raytracer
//  File: scene.cpp
//
//  Created for the Computer Science course "Introduction Computer Graphics"
//  taught at the University of Groningen by Tobias Isenberg.
//
//  Authors:
//    Maarten Everts
//    Jasper van de Gronde
//
//  This framework is inspired by and uses code of the raytracer framework of
//  Bert Freudenberg that can be found at
//  http://isgwww.cs.uni-magdeburg.de/graphik/lehre/cg2/projekt/rtprojekt.html
//

#include "scene.h"
#include "material.h"
#include <algorithm>
#include <cmath>

Color Scene::trace(const Ray &ray)
{
    // Find hit object and distance
    Hit min_hit(std::numeric_limits<double>::infinity(),Vector());
    Object *obj = NULL;
    for (unsigned int i = 0; i < objects.size(); ++i) {
        Hit hit(objects[i]->intersect(ray));
        if (hit.t<min_hit.t) {
            min_hit = hit;
            obj = objects[i];
        }
    }

    // No hit? Return background color.
    if (!obj) return Color(0.0, 0.0, 0.0);

    Material *material = obj->material;            //the hit objects material
    Point hit = ray.at(min_hit.t);                 //the hit point
    Vector N = min_hit.N;                          //the normal at hit point
    Vector V = -ray.D;                             //the view vector


    /****************************************************
    * This is where you should insert the color
    * calculation (Phong model).
    *
    * Given: material, hit, N, V, lights[]
    * Sought: color
    *
    * Hints: (see triple.h)
    *        Triple.dot(Vector) dot product
    *        Vector+Vector      vector sum
    *        Vector-Vector      vector difference
    *        Point-Point        yields vector
    *        Vector.normalize() normalizes vector, returns length
    *        double*Color        scales each color component (r,g,b)
    *        Color*Color        dito
    *        pow(a,b)           a to the power of b
    ****************************************************/

	Vector L;
	Vector R;

	Color color;

	color += material->color * material->ka;

	for (unsigned int idx = 0; idx < lights.size(); idx++)
	{
		L = (lights[idx]->position - hit).normalized();
		color += (std::max(0.0,N.dot(L)) * material->kd) * material->color * lights[idx]->color;

		R = (2*(N.dot(L))*N)-L;
		color += (std::pow(std::max(0.0,R.dot(V)),material->n) * material->ks);

	}

    //Color color = material->color;                  // place holder
    return color;
}

Color Scene::traceZ(const Ray &ray)
{
  // Find hit object and distance
  Hit min_hit(std::numeric_limits<double>::infinity(),Vector());
  Object *obj = NULL;
  for (unsigned int i = 0; i < objects.size(); ++i) {
      Hit hit(objects[i]->intersect(ray));
      if (hit.t<min_hit.t) {
          min_hit = hit;
          obj = objects[i];
      }
  }

  // No hit? Return background color.
  if (!obj) return Color(0.0, 0.0, 0.0);
  Color color = Color(min_hit.t, min_hit.t, min_hit.t)/1000;
  return color;
}

Color Scene::traceNormal(const Ray &ray)
{
  // Find hit object and distance
  Hit min_hit(std::numeric_limits<double>::infinity(),Vector());
  Object *obj = NULL;
  for (unsigned int i = 0; i < objects.size(); ++i) {
      Hit hit(objects[i]->intersect(ray));
      if (hit.t<min_hit.t) {
          min_hit = hit;
          obj = objects[i];
      }
  }

  // No hit? Return background color.
  if (!obj) return Color(0.0, 0.0, 0.0);

  Material *material = obj->material;            //the hit objects material
  Point hit = ray.at(min_hit.t);                 //the hit point
  Vector N = min_hit.N;                          //the normal at hit point
  Vector V = -ray.D;                             //the view vector

  Color color = (Color(N.data[0], N.data[1], N.data[2])+1)/2;
  cout << color << endl;

  return color;
}

void Scene::render(Image &img)
{
    int w = img.width();
    int h = img.height();
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            Point pixel(x+0.5, h-1-y+0.5, 0);
            Ray ray(eye, (pixel-eye).normalized());
            Color col;
            if (this->renderMode == "phong")
              col = trace(ray);
            if (this->renderMode == "normal")
              col = traceNormal(ray);
            if (this->renderMode == "zbuffer")
              col = traceZ(ray);

            col.clamp();
            img(x,y) = col;
        }
    }
    if(this->renderMode == "zbuffer"){ //if zbuffer, scale from closest to furthest
      double minCol = 1;
      double maxCol = 0;
      for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
          if (img(x,y).data[0] > maxCol )
            maxCol = img(x,y).data[0];
          if (img(x,y).data[0] < minCol && img(x,y).data[0] > 0.0001) //make sure that background is not used to calculate range
            minCol = img(x,y).data[0];
        }
      }

      double range = maxCol - minCol;
      for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
          if (img(x,y).data[0] > 0.0001) //make sure background is not changed
          {
            img(x,y) = 1 - (img(x,y) - minCol) / range;
          }
        }
      }
    }
}

void Scene::addObject(Object *o)
{
    objects.push_back(o);
}

void Scene::addLight(Light *l)
{
    lights.push_back(l);
}

void Scene::setEye(Triple e)
{
    eye = e;
}
