#include "format"
#include "gsl/gsl"
#include "json.hpp"

#include "Render.h"
#include "ImageDimensions.h"

#include <algorithm>
#include <fstream>
#include <iostream>

using json = nlohmann::json;

template <int A, int B>
struct AspectRatio {
    static constexpr int num = A;
    static constexpr int den = B;
};

template <typename Ratio>
constexpr ImageDimensions calculate_dimensions(size_t width) {
    constexpr double aspectRatio = gsl::narrow_cast<double>(Ratio::num) / Ratio::den;

    const size_t height = std::invoke([&](){
        size_t h = gsl::narrow_cast<double>(width) / aspectRatio;
        return std::max(h, size_t(1));
    });

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
    const json config = load_config();
    const std::string file_name = config["paths"]["outputImage"];

    constexpr int width = 400;
    const ImageDimensions image_dimensions = calculate_dimensions<AspectRatio<16,9>>(width);

    const Camera camera {
            .center = {0,0,0},
            .focal_length = 1.0
    };

    const Viewport viewport = Viewport(image_dimensions, camera);

    try {
        std::ofstream output_file = open_file(file_name); // NB: file closed on leaving scope
        render(output_file, image_dimensions, viewport, camera);
    }
    catch (const std::exception& e) {
        std::cerr << std::format("Error: {}\n", e.what());
        return EXIT_FAILURE;
    }

    display_PPM(config);

    return 0;
}
