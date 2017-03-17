//
//  Framework for a raytracer
//  File: raytracer.cpp
//
//  Created for the Computer Science course "Introduction Computer Graphics"
//  taught at the University of Groningen by Tobias Isenberg.
//
//  Author: Maarten Everts
//
//  This framework is inspired by and uses code of the raytracer framework of
//  Bert Freudenberg that can be found at
//  http://isgwww.cs.uni-magdeburg.de/graphik/lehre/cg2/projekt/rtprojekt.html
//

#include "raytracer.h"
#include "object.h"
#include "sphere.h"
#include "plane.h"
#include "triangle.h"
#include "cylinder.h"
#include "material.h"
#include "light.h"
#include "image.h"
#include "yaml/yaml.h"
#include <ctype.h>
#include <fstream>
#include <assert.h>
#include "glm.h"

// Functions to ease reading from YAML input
void operator >> (const YAML::Node& node, Triple& t);
Triple parseTriple(const YAML::Node& node);

void operator >> (const YAML::Node& node, Triple& t)
{
    assert(node.size()==3);
    node[0] >> t.x;
    node[1] >> t.y;
    node[2] >> t.z;
}

Triple parseTriple(const YAML::Node& node)
{
    Triple t;
    node[0] >> t.x;
    node[1] >> t.y;
    node[2] >> t.z;
    return t;
}


Material* Raytracer::parseMaterial(const YAML::Node& node)
{
    Material *m = new Material();
	if (node.FindValue("color")){
		node["color"] >> m->color;
	}
    node["ka"] >> m->ka;
    node["kd"] >> m->kd;
    node["ks"] >> m->ks;
    node["n"] >> m->n;
	if (node.FindValue("texture")){
		std::string text;
		node["texture"] >> text;
		const char * c = text.c_str();
		m->texture = new Image(c);
	}
    return m;
}

Object* Raytracer::parseObject(const YAML::Node& node)
{
    Object *returnObject = NULL;
    std::string objectType;
    node["type"] >> objectType;

    if (objectType == "sphere") {
        Point pos;
        node["position"] >> pos;
        double r;
		Triple axis;
		if (node["radius"].GetType() > 1)
		{
			node["radius"][0] >> r;
			node["radius"][1] >> axis;

			cout << "axis: " << axis << endl;

		} else {
			node["radius"] >> r;
		}



		Sphere *sphere = new Sphere(pos,r);
		sphere->axis = axis;

		if (node.FindValue("angle")){
			int angle;
			node["angle"] >> angle;
			sphere->angle = angle;
		}
        returnObject = sphere;
    }

    if (objectType == "plane") {
  		Triple normal;
  		node["normal"] >> normal;
  		Plane *plane = new Plane(normal);
  		returnObject = plane;
  	}
  	if (objectType == "triangle") {
  		Triple a; //corner of triangle
  		Triple b;
  		Triple c;

  		node["a"] >> a;
  		node["b"] >> b;
  		node["c"] >> c;
  		Triangle *triangle = new Triangle(a,b,c);
  		returnObject = triangle;
  	}
    if (objectType == "cylinder") {
        Point p1;
        Point p2;
        node["p1"] >> p1;
        node["p2"] >> p2;
        double r;
        node["radius"] >> r;
        Cylinder *cylinder = new Cylinder(p1,p2,r);
        returnObject = cylinder;
    }

    if (returnObject) {
        // read the material and attach to object
        returnObject->material = parseMaterial(node["material"]);
    }

    return returnObject;
}

Light* Raytracer::parseLight(const YAML::Node& node)
{
    Point position;
    node["position"] >> position;
    Color color;
    node["color"] >> color;
    return new Light(position,color);
}

/*
* Read a scene from file
*/

bool Raytracer::readScene(const std::string& inputFilename)
{
    // Initialize a new scene
    scene = new Scene();

    if (false){
        GLMmodel *model = glmReadOBJ("sphere.obj");
        glmUnitize(model);
        cout << "Number of triangles: " << model->numtriangles << endl;
        for (unsigned int i = 0; i < model->numtriangles; i++)
        {
            //cout << "test " <<  model->triangles->vindices[triangle] << endl;
            Object *obj = NULL;

            Triple a = Triple (model->vertices[3 * model->triangles[i].vindices[0]] + 200,
                model->vertices[3 * model->triangles[i].vindices[0]] + 200,
                model->vertices[3 * model->triangles[i].vindices[0]] + 995);

            Triple b = Triple (model->vertices[3 * model->triangles[i].vindices[1]] + 200,
                model->vertices[3 * model->triangles[i].vindices[1]] + 200,
                model->vertices[3 * model->triangles[i].vindices[1]] + 995);

            Triple c = Triple (model->vertices[3 * model->triangles[i].vindices[2]+0] + 200,
                model->vertices[3 * model->triangles[i].vindices[2]] + 200,
                model->vertices[3 * model->triangles[i].vindices[2]] + 995);

            obj = new Triangle(a,b,c);
            Material *m = new Material();
            m->ka = 0.2;
            m->kd = 0.8;
            m->ks = 0;
            m->n = 1;

            m->color = Color(1.0,0.1,0.2);

            obj->material = m;


            //Triple a = new Triple(model->triangles->vindices[0][0],model->triangles->vindices[0][1],model->triangles->vindices[0][2])
            //obj = new Triangle(a,a,a)
            scene->addObject(obj);
        }
    }

    // Open file stream for reading and have the YAML module parse it
    std::ifstream fin(inputFilename.c_str());
    if (!fin) {
        cerr << "Error: unable to open " << inputFilename << " for reading." << endl;;
        return false;
    }
    try {
        YAML::Parser parser(fin);
        if (parser) {
            YAML::Node doc;
            parser.GetNextDocument(doc);

			if (doc.FindValue("Eye")){
            // Read scene configuration options
				scene->setEye(parseTriple(doc["Eye"]));
			}else if(doc.FindValue("Camera")){
				const YAML::Node& camera = doc["Camera"];
				if (camera.FindValue("eye")){
					Triple tempEye;
					camera["eye"] >> tempEye;
					scene->setEye(tempEye);
				}
				if (camera.FindValue("center")){
					camera["center"] >> scene->center;
				}
				if (camera.FindValue("up")){
					camera["up"] >> scene->up;
				}
				if (camera.FindValue("viewSize")){
					camera["viewSize"][0] >> scene->h;
                    camera["viewSize"][1] >> scene->w;
 					//camera["viewSize"] >> viewSize;
					//cout << viewSize;
					//camera["viewSize"] >> scene->image;

				}
			}

            //Read and save render mode;
			if (doc.FindValue("RenderMode"))
				doc["RenderMode"] >> scene->renderMode;
			else
				scene->renderMode = "phong";

			if (doc.FindValue("Shadows"))
				doc["Shadows"] >> scene->Shadows;
			else
				scene->Shadows = false;

			if (doc.FindValue("MaxRecursionDepth"))
				doc["MaxRecursionDepth"] >> scene->reflectCount;
			else
				scene->reflectCount = 0;

			if(doc.FindValue("SuperSampling")){
				const YAML::Node& ss = doc["SuperSampling"];
				if (ss.FindValue("factor")){
					ss["factor"] >> scene->superSampling;
				}
			} else{
				scene->superSampling = 1;
			}
			if(doc.FindValue("GoochParameters")){
				const YAML::Node& gooch = doc["GoochParameters"];
				gooch["b"] >> scene->b;
				gooch["y"] >> scene->y;
				gooch["alpha"] >> scene->alpha;
				gooch["beta"] >> scene->beta;
			}



			cout << scene->Shadows << endl;

            // Read and parse the scene objects
            const YAML::Node& sceneObjects = doc["Objects"];
            if (sceneObjects.GetType() != YAML::CT_SEQUENCE) {
                cerr << "Error: expected a sequence of objects." << endl;
                return false;
            }
            for(YAML::Iterator it=sceneObjects.begin();it!=sceneObjects.end();++it) {
                Object *obj = parseObject(*it);
                // Only add object if it is recognized
                if (obj) {
                    scene->addObject(obj);
                } else {
                    cerr << "Warning: found object of unknown type, ignored." << endl;
                }
            }

            // Read and parse light definitions
            const YAML::Node& sceneLights = doc["Lights"];
            if (sceneObjects.GetType() != YAML::CT_SEQUENCE) {
                cerr << "Error: expected a sequence of lights." << endl;
                return false;
            }
            for(YAML::Iterator it=sceneLights.begin();it!=sceneLights.end();++it) {
                scene->addLight(parseLight(*it));
            }
        }
        if (parser) {
            cerr << "Warning: unexpected YAML document, ignored." << endl;
        }
    } catch(YAML::ParserException& e) {
        std::cerr << "Error at line " << e.mark.line + 1 << ", col " << e.mark.column + 1 << ": " << e.msg << std::endl;
        return false;
    }

    cout << "YAML parsing results: " << scene->getNumObjects() << " objects read." << endl;
    return true;
}

void Raytracer::renderToFile(const std::string& outputFilename)
{
    Image img(scene->h,scene->w);
    cout << "Tracing..." << endl;
    scene->render(img);
    cout << "Writing image to " << outputFilename << "..." << endl;
    img.write_png(outputFilename.c_str());
    cout << "Done." << endl;
}
