#include "transform.h"
#include "vect.h"
#include <math.h>

VEC2D point_3t2(VEC3D vec, ANG3D ang, VEC3D cpos, VEC3D ddist) {
    VEC2D p_vec;
    p_vec.k = 1;
    VEC3D rot_vec;
    rot_vec.w = 1;
    
    rot_vec.i = cos(ang.y) * (sin(ang.z) * (vec.j - cpos.j) + cos(ang.z) * (vec.i - cpos.i)) - sin(ang.y) * (vec.k - cpos.k);
    rot_vec.j = sin(ang.x) * (cos(ang.y) * (vec.k - cpos.k) + sin(ang.y) * (sin(ang.z) * (vec.j - cpos.j) + cos(ang.z) * (vec.i - cpos.i))) + cos(ang.x) * (cos(ang.z) * (vec.j - cpos.j) - sin(ang.z) * (vec.i - cpos.i));
    rot_vec.k = cos(ang.x) * (cos(ang.y) * (vec.k - cpos.k) + sin(ang.y) * (sin(ang.z) * (vec.j - cpos.j) + cos(ang.z) * (vec.i - cpos.i))) - sin(ang.x) * (cos(ang.z) * (vec.j - cpos.j) - sin(ang.z) * (vec.i - cpos.i));

    p_vec.i = ((ddist.k * rot_vec.i) / (rot_vec.k)) + ddist.i;
    p_vec.j = ((ddist.k * rot_vec.j) / (rot_vec.k)) + ddist.j;

    return p_vec;
}