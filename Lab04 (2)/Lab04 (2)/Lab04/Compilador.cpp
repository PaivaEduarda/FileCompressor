#include <iostream>
#include "FrequencyCounter.h"
#include "Huffman.h"
#include "HuffmanUtility.h"
#include <fstream>
using namespace std;

bool fileExists(const std::string& filename)
{
    std::ifstream file(filename.c_str());
    return file.good();
}

int main()
{
    cout << " Bem-vindo ao programa de compactacao e descompactacao da Elo e da Estrelinha :) \n";

    while (true) {
        cout << "\nEscolha uma opcao:\n";
        cout << "1. Compactar arquivo\n";
        cout << "2. Descompactar arquivo\n";
        cout << "3. Sair\n";

        int choice;
        cin >> choice;

        if (choice == 1 || choice == 2) {
            string inputFileName, outputFileName;

            cout << "Digite o nome do arquivo de entrada: ";
            cin >> inputFileName;

            cout << "Digite o nome do arquivo de saida(.huff): ";
            cin >> outputFileName;

            if (choice == 1) {
                // Compactar
                FrequencyCounter frequencyCounter;
                if (fileExists(inputFileName)) {
                    frequencyCounter.readFile(inputFileName);
                    Huffman huffman;
                    huffman.huffer(frequencyCounter.getFrequencyMap());
                    huffman.compressTofile(inputFileName, outputFileName);

                    std::cout << "Arquivo compactado com sucesso!\n";
                }
                else {
                    std::cout << "Arquivo não localizado!" <<std::endl;
                }
            }
            else {
                // Descompactar
                if (fileExists(inputFileName) && !fileExists(outputFileName)) {

                    Huffman huffman;
                    huffman.deHuffer(inputFileName, outputFileName);

                    cout << "Arquivo descompactado com sucesso!\n";
                }
                else {
                    std::cout << "Arquivo não localizado!" << std::endl;
                }
            }
        }
        else if (choice == 3) {
            cout << "Saindo do programa. Ate mais!\n";
            break;
        }
        else {
            cout << "Opcao invalida. Tente novamente.\n";
        }
    }

    return 0;
}