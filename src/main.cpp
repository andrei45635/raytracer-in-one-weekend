#include "lib/vec3.h"
#include "lib/colour.h"

#include <iostream>

//TODO: starting ch4

int main() {
    constexpr int img_width{256};
    constexpr int img_height{256};

    std::cout << "P3\n" << img_width << " " << img_height << "\n255\n";

    for (int j = 0; j < img_height; ++j) {
        std::clog << "\r Scanlines remaining: " << (img_height - j) << ' ' << std::flush;
        for (int i = 0; i < img_width; ++i) {
            auto pixel_colour = colour(static_cast<double>(i) / (img_width - 1), static_cast<double>(j) / (img_height - 1), 0);
            write_colour(std::cout, pixel_colour);
        }
    }

    std::clog << "\rDone.                 \n";

    return 0;
}
