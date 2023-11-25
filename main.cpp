#include <iostream>
#include "gsl/gsl"
#include <fstream>
#include "format"
#include "json.hpp"
#include "Render.h"

using json = nlohmann::json;

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

    try {
        std::ofstream output_file = open_file(file_name); // NB: file closed on leaving scope
        render(ImageDimensions{256,256}, output_file);
    }
    catch (const std::exception& e) {
        std::cerr << std::format("Error: {}\n", e.what());
        return EXIT_FAILURE;
    }

    display_PPM(config);
    return 0;
}
