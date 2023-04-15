#include <iostream>
#include <string>
#include <fstream>
#include <yaml-cpp/yaml.h>

void read_yaml(std::string filename) ;

void read_yaml(std::string fn) {

    std::string simulation_name ; //method ; 
    int ndimm ; 
    int Lx, Ly, Lz;  
   // int termaliztion_steps, store_averages_steps ; 
    // std::ifstream input_file("input_model.yaml");
    std::ifstream input_file(fn);

    //Ler o conteúdo do arquivo YAML em um nó YAML
    YAML::Node doc = YAML::Load(input_file);

  // Access the values in the YAML document
  std::string name = doc["general"]["name"].as<std::string>();
  int ndim = doc["geometry"]["ndim"].as<int>();
  if (ndim == 2) {
        Lx = doc["geometry"]["Lx"].as<int>();
        Ly = doc["geometry"]["Ly"].as<int>();
  } else if (ndim == 3) {
        Lx = doc["geometry"]["Lx"].as<int>();
        Ly = doc["geometry"]["Ly"].as<int>();
        Lz = doc["geometry"]["Ly"].as<int>();
  }
  int ncoord = doc["geometry"]["ncoord"].as<int>();
  
  std::string method = doc["simulation"]["method"].as<std::string>();
  int termalization_steps = doc["simulation"]["termaliztion_steps"].as<int>();
  int store_averages_steps = doc["simulation"]["store_averages_steps"].as<int>();
  int window = doc["output"]["window"].as<int>();

  // Access the file names and quantities for each output file
  YAML::Node files = doc["output"]["files"];
  for (auto file : files) {
    std::string filename = file["filename"].as<std::string>();
    std::cout << "Output file: " << filename << std::endl;
    YAML::Node quantities = file["quantities"];
    for (auto quantity : quantities) {
      std::string quantity_name = quantity.as<std::string>();
      std::cout << "  Quantity: " << quantity_name << std::endl;
    }
  }

  // Print the values to the console
  std::cout << "Name: " << name << std::endl;
  std::cout << "ndim: " << ndim << std::endl;
  std::cout << "Lx: " << Lx << std::endl;
  std::cout << "Ly: " << Ly << std::endl;
  std::cout << "ncoord: " << ncoord << std::endl;
  std::cout << "Method: " << method << std::endl;
  std::cout << "Termalization steps: " << termalization_steps << std::endl;
  std::cout << "Store averages steps: " << store_averages_steps << std::endl;
  std::cout << "Window: " << window << std::endl;

  return ;
}


// int main(int argc, char* argv[])
// {

//   std::string fn = argv[1] ;//"filename.conf";

//     read_yaml(fn) ;
// } 