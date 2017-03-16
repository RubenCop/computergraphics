//
//  Framework for a raytracer
//  File: scene.h
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

#ifndef SCENE_H_KNBLQLP6
#define SCENE_H_KNBLQLP6

#include <vector>
#include "triple.h"
#include "light.h"
#include "object.h"
#include "image.h"

class Scene
{
private:
    std::vector<Object*> objects;
    std::vector<Light*> lights;
    Triple eye;
public:
    //string renderMode added to save render mode (phong, normal, z-buffer)


    std::string renderMode;
	bool Shadows;
	bool traceShad(const Ray &ray);
	int reflectCount;
	int superSampling;

	Triple center;
	Triple up;
	Image image;

    int h, w;

    Scene() {
        h = 400;
        w = 400;
		center = Triple(200,200,0);
		up = Triple(0,1,0);
		
    }
    
    //Gooch
    double b,y,alpha, beta;

    Color trace(const Ray &ray, int reflectCount); //phong
    Color traceZ(const Ray &ray); //z-buffer
    Color traceNormal(const Ray &ray); //normal
	Color traceGooch(const Ray &ray); //Gooch
    void render(Image &img);
    Point sample(int currentSample, int totalSamples, int x, int y, int h);
    void addObject(Object *o);
    void addLight(Light *l);
    void setEye(Triple e);
    unsigned int getNumObjects() { return objects.size(); }
    unsigned int getNumLights() { return lights.size(); }
};

#endif /* end of include guard: SCENE_H_KNBLQLP6 */
