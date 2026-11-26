#include "camera.h"
#include "rtweekend.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"

//TODO: starting ch10

int main() {
    // world
    hittable_list world;
    world.add(std::make_shared<sphere>(point3(0, 0, -1), 0.5));
    world.add(std::make_shared<sphere>(point3(0, -100.5, -1), 100));


    // camera
    camera camera;

    camera.aspect_ratio = 16.0 / 9.0;
    camera.img_width = 400;
    camera.samples_per_pixel = 100;
    camera.max_depth = 100;

    camera.render(world);

    return 0;
}
