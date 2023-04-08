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

    if (no.IsSequence())
    {
        std::cout << no << std::endl ; 
        // Percorrer todos os elementos da sequência
        for (YAML::iterator it = no.begin(); it != no.end(); ++it)
        {
            // Verificar se o elemento é um mapa (ou seja, um dicionário)
            if (it->IsMap())
            {
                // Percorrer todos os campos do mapa
                for (YAML::const_iterator map_it = it->begin(); map_it != it->end(); ++map_it)
                {
                    // Obter o nome do campo e o valor correspondente
                    std::string nome_campo = map_it->first.as<std::string>();
                    YAML::Node valor_campo = map_it->second;

                    // Imprimir o nome do campo e o valor correspondente
                    std::cout << nome_campo << ": " << valor_campo << std::endl;
                }
            }
        }
        
     } else {
        std::cout << "It is not a sequence" << std::endl;
     
        for (std::size_t i = 0; i < no.size(); i++) {
           YAML::Node node = no[i];

        // Imprimindo o valor de cada nó
            std::cout << "Valor do nó " << i << ": " << node << std::endl;
    }

    //     for (auto node : no ) {
    //         std::cout << "aawww" << std::endl;
    //         std::cout << "Nome do nó: " << node.Tag() << std::endl;
    // }
        //std::string nome_campo = map_it->first.as<std::string>();
    //     YAML::Node valor_campo = map_it->second;

    //     // Imprimir o nome do campo e o valor correspondente
    //     std::cout << nome_campo << ": " << valor_campo << std::endl;
    }


    // Processar o conteúdo do nó YAML
    // std::string name = no["general"]["name"].as<std::string>();
    // int L = no["geometry"]["L"].as<int>();
    // int ndim = no["geometry"]["ndim"].as<int>();
    // int ncoord = no["geometry"]["ncoord"].as<int>();
    // std::string method = no["simulation"]["method"].as<std::string>();
    // int thermalization_steps = no["simulation"]["termaliztion_steps"].as<int>();
    // int store_averages_steps = no["simulation"]["store_averages_steps"].as<int>();
    // int window = no["output"]["window"].as<int>();
    // std::string output_file_1 = no["output"]["files"][0]["filename_1"].as<std::string>();
    // int quantidade_1 = no["output"]["files"]["quantities"][0].as<std::string>();

    // // Imprimir os valores lidos do arquivo YAML
    // std::cout << "Name: " << name << std::endl;
    // std::cout << "linear size : " << L << std::endl;
    // std::cout << "No of dimensions: " << ndim << std::endl;
    // std::cout << "ncoord: " << ncoord << std::endl;
    // std::cout << "method: " << method << std::endl;
    // std::cout << "thermalization_steps: " << thermalization_steps << std::endl;
    // std::cout << "store_averages_steps: " << store_averages_steps << std::endl;
    // std::cout << "output_file_1: " << output_file_1 << std::endl;
    //std::cout << "quantidades: " << quantidade_1 << std::endl;
    
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
