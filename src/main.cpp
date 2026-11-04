#include <iostream>


//TODO: Left at vec3 class

int main() {
    constexpr int img_width{256};
    constexpr int img_height{256};

    std::cout << "P3\n" << img_width << " " << img_height << "\n255\n";

    for (int j = 0; j < img_height; ++j) {
        std::clog << "\r Scanlines remaining: " << (img_height - j) << ' ' << std::flush;
        for (int i = 0; i < img_width; ++i) {
            const auto r = static_cast<double>(i) / (img_width - 1);
            const auto g = static_cast<double>(j) / (img_height - 1);
            constexpr auto b = 0.0;

            const int ir = static_cast<int>(255.999 * r);
            const int ig = static_cast<int>(255.999 * g);
            constexpr int ib = static_cast<int>(255.999 * b);

            std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }

    std::clog << "\rDone.                 \n";

    return 0;
}
