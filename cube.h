#ifndef CUBE_H
#define CUBE_H

#include "hittable.h"

class cube : public hittable {
    public:
        cube(const point3& vmin, const point3& vmax, shared_ptr<material> mat) : mat(mat) {
            bounds[0] = vmin;
            bounds[1] = vmax;
        }
        bool hit (const ray& r, interval ray_t, hit_record& rec) const override {
            // should i just utilize the invterval ray_t class ?
            auto txmin = (bounds[0].x() - r.origin().x()) / r.direction().x(); // where the ray interesects with the plane defined by the x-coordinate of the min point of the bounding box
            auto txmax = (bounds[1].x() - r.origin().x()) / r.direction().x();

            if (txmin > txmax) swap(txmin,txmax); // swap for naming convetion if the ray comes from a direction relative to the maximum aligned plane 

            auto tymin = (bounds[0].y() - r.origin().y()) / r.direction().y();
            auto tymax = (bounds[1].y() - r.origin().y()) / r.direction().y();

            if (tymin > tymax) swap(tymin, tymax);

            if ((txmin > tymax) || (tymin > txmax)) {
                return false;
            }

            if (tymin > txmin) txmin = tymin;
            if (tymax < txmax) txmax = tymax;

            auto tzmin = (bounds[0].z() - r.origin().z()) / r.direction().z();
            auto tzmax = (bounds[1].z() - r.origin().z()) / r.direction().z();

            if (tzmin > tzmax) swap(tzmin, tzmax);

            if ((txmin > tzmax) || (tzmin > txmax)) {
                return false;
            }

            if (tzmin > txmin) txmin = tzmin;
            if (tzmax < txmax) txmax = tzmax;

            // check if our interval surround? 

            if (!ray_t.surrounds(txmin)) {
                return false;
            }

            rec.mat = mat;
            rec.t = txmin;
            rec.p = r.at(rec.t);
            // we need to get the surface normal at this point 
            // define the cetner of the cube? 
            // probably is a conventient equation
            vec3 center = (bounds[0] + bounds[1]) / 2;
            vec3 center_to_intersection = (rec.p - center); // unnoramlized
            vec3 divisor_factor = (bounds[1] - bounds[0]) / 2;
            double bias = 1.00001;
            vec3 normal = vec3(
                (int) (center_to_intersection.x() / divisor_factor.x()),
                (int) (center_to_intersection.y() / divisor_factor.y()),
                (int) (center_to_intersection.z() / divisor_factor.z())
            );

            //normal = normal * bias;
            rec.set_face_normal(r, normal);
            return true;

        }
    private:
        vec3 bounds[2];
    public:
        shared_ptr<material> mat;

};

#endif