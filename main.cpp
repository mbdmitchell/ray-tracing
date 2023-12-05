#include <algorithm>
#include <fstream>
#include <gsl/gsl>
#include <iostream>

#include "format"
#include "json.hpp"

#include "Render.h"
#include "ImageDimensions.h"
#include "HittableEntities/Sphere.h"
#include "material/Material.h"

using json = nlohmann::json;

template <int A, int B>
struct AspectRatio {
    static constexpr int num = A;
    static constexpr int den = B;
};

template <typename Ratio>
constexpr ImageDimensions calculate_dimensions(size_t width) {
    constexpr double aspectRatio = gsl::narrow_cast<double>(Ratio::num) / Ratio::den;

    const size_t height = [&](){
        size_t h = gsl::narrow_cast<double>(width) / aspectRatio;
        return std::max(h, size_t(1));
    }();

    return {height, width};
}

json load_config() {
    json c;
    std::ifstream config_file("../config.json");
    if (!config_file.is_open()) {
        throw std::runtime_error("Failed to open config file!");
    }
    config_file >> c;
    return c;
}

void display_PPM(const json& config) {
    /// Precondition - outputImage file is closed / nothing in the buffer still needing to be written to the file
    const std::string python_PPM_script_path = config["paths"]["printPPM"];
    const std::string output_image_path = config["paths"]["outputImage"];

    const std::string venv_path = config["paths"]["venv"];
    const std::string full_venv_path = venv_path + "/bin/python3";

    const bool isSuccess = system((full_venv_path + ' ' + python_PPM_script_path + ' ' + output_image_path).c_str()) == 0;
    if (!isSuccess) throw std::runtime_error("Oops");
}

std::ofstream open_file(const std::string& fileName) {
    std::ofstream file(fileName);
    if (!file.is_open()) {
        throw std::runtime_error("Can't open output file!");
    }
    return file;
}

int main() {

    // materials

    const Lambertian ground {Colour{0.5, 0.5, 0.5}};
    const Dielectric mat1 {1.5};
    const Lambertian mat2 {Colour{0.4, 0.2, 0.1}};
    const Metal      mat3 {Colour{0.7, 0.6, 0.5}, 0.0};

    // setup

    const json config = load_config();
    const std::string file_name = config["paths"]["outputImage"];

    const ListOfHittables world = [&](){

        ListOfHittables w;
        w.add(Sphere{1000, Point3{0, -1000, 0}, ground});
        w.add(Sphere{1.0, Point3{0, 1, 0}, mat1});
        w.add(Sphere{1.0, Point3{-4, 1, 0}, mat2});
        w.add(Sphere{1.0, Point3{4, 1, 0}, mat3});

        for (gsl::index a = -11; a < 11; ++a) {
            for (gsl::index b = -11; b < 11; ++b) {
                const double choose_mat = utils::random_double();

                Point3 center{a + 0.9 * utils::random_double(), 0.2, b + 0.9 * utils::random_double()};

                if ((center - Point3{4, 0.2, 0}).length() > 0.9) {
                    if (choose_mat < 0.8) {
                        // diffuse
                        const Colour albedo = Colour::random() * Colour::random();
                        w.add(Sphere{0.2, center, Lambertian{albedo}});
                    } else if (choose_mat < 0.95) {
                        // metal
                        const Colour albedo = Colour::random({0.5, 1});
                        const double fuzz_factor = utils::random_double({0, 0.5});
                        w.add(Sphere{0.2, center, Metal{albedo, fuzz_factor}});
                    } else {
                        // glass
                        w.add(Sphere{0.2, center, Dielectric{1.5}});
                    }
                }
            }
        }

        return w;
    }();

    const int width = 240;
    const int samples_per_pixel = 50;

    const ImageDimensions image_dimensions = calculate_dimensions<AspectRatio<16,9>>(width);
    const Camera camera {Point3{13, 2, 3}, Point3{0, 0, 0}, Point3{0, 1, 0}};
    const Viewport viewport {image_dimensions, camera};

    // render

    try {
        std::ofstream output_file = open_file(file_name); // NB: file closed on leaving scope
        render(output_file, image_dimensions, viewport, camera, world, samples_per_pixel);
    }
    catch (const std::exception& e) {
        std::cerr << std::format("Error: {}\n", e.what());
        return EXIT_FAILURE;
    }

    // display

    display_PPM(config);

    return 0;
}
