#include <iostream>
#include "FrequencyCounter.h"
#include "Huffman.h"
#include "HuffmanUtility.h"
using namespace std;
int main()
{
    cout << "Bem-vindo ao programa de compactacao e descompactacao!\n";

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

            cout << "Digite o nome do arquivo de saida: ";
            cin >> outputFileName;

            if (choice == 1) {
                // Compactar
                FrequencyCounter frequencyCounter;
                frequencyCounter.readFile(inputFileName);

                Huffman huffman;
                huffman.huffer(frequencyCounter.getFrequencyMap());
                huffman.compressTofile(inputFileName, outputFileName);

                std::cout << "Arquivo compactado com sucesso!\n";
            }
            else {
                // Descompactar
                Huffman huffman;
                huffman.deHuffer(inputFileName, outputFileName);

                cout << "Arquivo descompactado com sucesso!\n";
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