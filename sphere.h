#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"

class sphere : public hittable {
    public:
        sphere(const point3& center, double radius, shared_ptr<material> mat) : center(center), radius(fmax(0, radius)), mat(mat) {}

        // const override means that this function wont change any member variables and won't call any functions that may
        // override means that the class is a member function that inherits from a class that contains a virtual of same name and sig
        bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
            vec3 oc = center - r.origin();
            auto a = r.direction().length_squared();
            auto h = dot(r.direction(), oc);
            auto c = oc.length_squared() - radius*radius;

            auto discriminant = h*h - a*c;
            if (discriminant < 0) {
                return false;
            }

            auto sqrtd = sqrt(discriminant);
            
            // find the nearest root that lies in the the acceptable range.
            auto root = (h - sqrtd) / a;
            if (!ray_t.surrounds(root)) { // i guess the nearer value is substracting the discriminant. 
                root = (h + sqrtd) / a; // outside range, try adding
                if (!ray_t.surrounds(root))
                    return false; // if still bad, return false;
            }

            rec.t = root;
            rec.p = r.at(rec.t); // this is the point that makes contact with the sphere
            vec3 outward_normal = (rec.p - center) / radius;
            rec.set_face_normal(r, outward_normal);
            rec.mat = mat;

            return true;
        }
    private:
        point3 center;
        double radius;
        shared_ptr<material> mat;
};
#endif