#include <iostream>
#include <string>
#include <fstream>
#include <yaml-cpp/yaml.h>

void read_yaml(std::string filename) ;

void read_yaml(std::string fn) {

    // std::ifstream input_file("input_model.yaml");
    std::ifstream input_file(fn);

    //Ler o conteúdo do arquivo YAML em um nó YAML
    YAML::Node no = YAML::Load(input_file);

    // Processar o conteúdo do nó YAML
    std::string name = no["name"].as<std::string>();
    int ndim = no["ndim"].as<int>();
    int ncoord = no["ncoord"].as<int>();

    // Imprimir os valores lidos do arquivo YAML
    std::cout << "Name: " << name << std::endl;
    std::cout << "No of dimensions: " << ndim << std::endl;
    std::cout << "ncoord: " << ncoord << std::endl;

    return ; 
}

int main(int argc, char* argv[])
{

  std::string fn = argv[1] ;//"filename.conf";

  if (fn.substr(fn.find_last_of(".") + 1) == "conf") {
    std::cout << "Yes..." << std::endl;
    // here the function to parse conf file
  } else if (fn.substr(fn.find_last_of(".") + 1) == "yaml") {
    std::cout << "It is a yaml file" << std::endl;

    read_yaml(fn) ;
 
    // std::ifstream input_file("input_model.yaml");

    // //Ler o conteúdo do arquivo YAML em um nó YAML
    // YAML::Node no = YAML::Load(input_file);

    // // Processar o conteúdo do nó YAML
    // std::string name = no["name"].as<std::string>();
    // int ndim = no["ndim"].as<int>();
    // int ncoord = no["ncoord"].as<int>();

    // // Imprimir os valores lidos do arquivo YAML
    // std::cout << "Name: " << name << std::endl;
    // std::cout << "No of dimensions: " << ndim << std::endl;
    // std::cout << "ncoord: " << ncoord << std::endl;
    //here the function to parse yaml file
  }
}


// void read_yaml(std::string fn) {

//     // std::ifstream input_file("input_model.yaml");
//     std::ifstream input_file(fn);

//     //Ler o conteúdo do arquivo YAML em um nó YAML
//     YAML::Node no = YAML::Load(input_file);

//     // Processar o conteúdo do nó YAML
//     std::string name = no["name"].as<std::string>();
//     int ndim = no["ndim"].as<int>();
//     int ncoord = no["ncoord"].as<int>();

//     // Imprimir os valores lidos do arquivo YAML
//     std::cout << "Name: " << name << std::endl;
//     std::cout << "No of dimensions: " << ndim << std::endl;
//     std::cout << "ncoord: " << ncoord << std::endl;

//     return ; 
// }



    // Verificar se o nó é uma sequência (ou seja, um vetor)
//     if (no.IsSequence())
//     {
//         // Percorrer todos os elementos da sequência
//         for (YAML::iterator it = no.begin(); it != no.end(); ++it)
//         {
//             // Verificar se o elemento é um mapa (ou seja, um dicionário)
//             if (it->IsMap())
//             {
//                 // Percorrer todos os campos do mapa
//                 for (YAML::const_iterator map_it = it->begin(); map_it != it->end(); ++map_it)
//                 {
//                     // Obter o nome do campo e o valor correspondente
//                     std::string nome_campo = map_it->first.as<std::string>();
//                     YAML::Node valor_campo = map_it->second;

//                     // Imprimir o nome do campo e o valor correspondente
//                     std::cout << nome_campo << ": " << valor_campo << std::endl;
//                 }
//             }
//         }
//     }

//     return 0;
// }
