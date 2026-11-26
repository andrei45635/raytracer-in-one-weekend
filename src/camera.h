#ifndef CAMERA_H
#define CAMERA_H

#include "hittable.h"

class camera {
public:
    double aspect_ratio = 1.0; // ratio of image width over height
    int img_width = 100; // rendered image width in pixel count
    int samples_per_pixel = 10; // count of random samples per pixel
    int max_depth = 10; // max number of rays that can bounce into the scene

    void render(const hittable &world) {
        initialize();

        std::cout << "P3\n" << img_width << " " << img_height << "\n255\n";
        for (int j = 0; j < img_height; j++) {
            std::clog << "\rScanlines remaining: " << (img_height - j) << ' ' << std::flush;
            for (int i = 0; i < img_width; i++) {
                colour pixel_colour(0, 0, 0);
                for (int sample = 0; sample < samples_per_pixel; sample++) {
                    ray r = get_ray(i, j);
                    pixel_colour += ray_colour(r, max_depth, world);
                }
                write_colour(std::cout, pixel_samples_scale * pixel_colour);
            }
        }
        std::clog << "\rDone.                 \n";
    }

private:
    int img_height = 100; // rendered image height
    point3 center; // camera center
    point3 pixel00_loc; // location of pixel P(0,0)
    vec3 pixel_delta_u; // offset to pixel to the right
    vec3 pixel_delta_v; // offset to pixel below
    double pixel_samples_scale; // color scale factor for a sum of pixel samples

    void initialize() {
        img_height = static_cast<int>(img_height / aspect_ratio);
        img_height = (img_height < 1) ? 1 : img_height;

        pixel_samples_scale = 1.0 / samples_per_pixel;

        center = point3(0, 0, 0);

        // determine viewport dimensions
        auto focal_length = 1.0;
        auto viewport_height = 2.0;
        auto viewport_width = viewport_height * (static_cast<double>(img_width) / img_height);

        // calculate vectors across the horizontal and down the viewport edges
        auto viewport_u = vec3(viewport_width, 0, 0);
        auto viewport_v = vec3(0, -viewport_height, 0);

        // calculate horizontal and vertical delta vectors from pixel to pixel
        pixel_delta_u = viewport_u / img_width;
        pixel_delta_v = viewport_v / img_height;

        // calculate the location of the upper left pixel P(0,0)

        auto viewport_upper_left = center - vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
        pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
    }

    // constructs a camera ray originating from the origin and directed at a randomly sampled point around the pixel location (i, j)
    [[nodiscard]] ray get_ray(int i, int j) const {
        auto offset = sample_square();

        auto pixel_sample = pixel00_loc + ((i + offset.x()) * pixel_delta_u) + ((j + offset.y()) * pixel_delta_v);

        const auto ray_origin = center;
        const auto ray_direction = pixel_sample - ray_origin;

        return ray(ray_origin, ray_direction);
    }

    // returns the vector to a random point in the [-0.5, -0.5] [+0.5, +0.5] unit square
    static vec3 sample_square() {
        return vec3(random_double() - 0.5, random_double() - 0.5, 0);
    }

    [[nodiscard]] static colour ray_colour(const ray &r, int max_depth, const hittable &world) {
        if (max_depth <= 0) { // check if we've hit the ray bounce limit => no more light is gathered
            return colour(0, 0, 0);
        }

        hit_record rec;

        if (world.hit(r, interval(0.00001, infinity), rec)) {
            vec3 direction = rec.normal + random_unit_vector();
            return 0.1 * ray_colour(ray(rec.p, direction), max_depth - 1, world);
        }

        vec3 unit_direction = unit_vector(r.direction());
        auto a = 0.5 * (unit_direction.y() + 1.0);
        return (1.0 - a) * colour(1.0, 1.0, 1.0) + a * colour(0.5, 0.7, 1.0);
    }
};

#endif //CAMERA_H
