# **Lattice Simulation Tools**

Este repositório consiste de um conjunto de classes, métodos e modelos que 
desenvolvi ao longo dos anos que podem ajudar no desenvolvimento de códigos 
de simulação de Monte Carlo em modelos definidos em redes regulares. As 
topologias já implementadas são, quadrada, triangular, cúbica e FCC. 


repositório contém as seguintes classes : 

- adjacency_matrix_class : esta classe gera a lista de vizinhos de um 
para todos os sítios da rede. Ela necessaita dos seguintes parâmetros de
entrada : 
    - L : Dimensões Laterais da rede
    - ndim : Número de dimensões da rede
    - N : Número total de sítios da rede ->  N = L**(ndim)
    - ncoord : número vizinhos (numero de coordenação)
    - nn : lista de vizinhos

- sublattice_class : classe geradora da subrede do sistema. Nesta
classe identificamos quais sítios 

- read_input : este arquivo contém funções que são usadas para ler
o arquivo de input. É aconselhável que se use um arquivo .yaml como
input para código.             

## **Compile** 

To compile this code use : 

- `g++ read_input_file.cpp -lyaml-cpp`