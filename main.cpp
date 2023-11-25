#include <iostream>
#include "gsl/gsl"
#include <fstream>
#include "format"
#include "json.hpp"

using json = nlohmann::json;

json loadConfig() {
    json c;
    std::ifstream config_file("../config.json");
    if (!config_file.is_open()) {
        throw std::runtime_error("Failed to open config file!");
    }
    config_file >> c;
    return c;
}

void displayPPM(const json& config) {

    const std::string printPPM_path = config["paths"]["printPPM"];

    const std::string venv_location = config["paths"]["venv"];
    const std::string full_venv_path = venv_location + "/bin/python3";

    const std::string output_image_path = config["paths"]["outputImage"];

    const bool isSuccess = system((full_venv_path + ' ' + printPPM_path + ' ' + output_image_path).c_str()) == 0;
    if (!isSuccess) throw std::runtime_error("Oops");
}

int main() {
    const json config = loadConfig();
    displayPPM(config);
    return 0;
}
