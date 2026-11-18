#include "lib/vec3.h"
#include "lib/colour.h"
#include "lib/ray.h"

#include <iostream>

//TODO: starting ch6

double hit_sphere(const point3& center, double radius, const ray& ray) {
    const vec3 oc = center - ray.origin();
    const auto a = ray.direction().length_squared();
    const auto h = dot(ray.direction(), oc);
    const auto c = oc.length_squared() - radius * radius;
    const auto discriminant = h * h - a * c;

    if (discriminant < 0.0) {
        return -1.0;
    } else {
        return (h - std::sqrt(discriminant)) / a;
    }

    return discriminant >= 0;
}

static colour ray_colour(const ray& r) {
    auto t = hit_sphere(point3(0, 0, -1), 0.5, r);
    if (t > 0.0) {
        vec3 N = unit_vector(r.at(t) - vec3(0, 0, -1));
        return 0.5 * colour(N.x() + 1, N.y() + 1, N.z() + 1);
    }

    const vec3 unit_direction = unit_vector(r.direction());
    const auto a = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - a) * colour(1.0, 1.0, 1.0) + a * colour(0.5, 0.7, 1.0);
}

int main() {

    auto aspect_ratio = 16.0 / 9.0;
    int img_width = 400;

    // calculate the image height and ensure that it's at least 1
    int img_height = static_cast<int>(img_width / aspect_ratio);
    img_height = (img_height < 1) ? 1 : img_height;

    // camera
    auto focal_length = 1.0;

    // viewport widths less than 1 are fine since they are reals
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * (static_cast<double>(img_width) / img_height);
    auto camera_center = point3(0, 0, 0);

    // calculate the vectors across the horizontal and down the vertical viewport edge
    auto viewport_u = vec3(viewport_width, 0, 0);
    auto viewport_v = vec3(0, -viewport_height, 0);

    //calculate the horizontal and vertical delta vectors from pixel to pixel
    auto pixel_delta_u = viewport_u / img_width;
    auto pixel_delta_v = viewport_v / img_height;

    // calculate the location of the upper left pixel
    auto viewport_upper_left = camera_center - vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
    auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    // render
    std::cout << "P3\n" << img_width << " " << img_height << "\n255\n";

    for (int j = 0; j < img_height; ++j) {
        std::clog << "\r Scanlines remaining: " << (img_height - j) << ' ' << std::flush;
        for (int i = 0; i < img_width; ++i) {
            auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
            auto ray_direction = pixel_center - camera_center;
            ray r(camera_center, ray_direction);
            colour pixel_colour = ray_colour(r);
            write_colour(std::cout, pixel_colour);
        }
    }

    std::clog << "\rDone.                 \n";

    return 0;
}
