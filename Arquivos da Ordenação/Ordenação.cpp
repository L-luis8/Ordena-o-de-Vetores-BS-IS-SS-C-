#include <iostream>
#include <chrono>
#include <unistd.h>
#include <fstream>

using namespace std;
using namespace chrono;

int geraAleatorio(int min, int max){
    return (rand() % (max - min)) + min;
}

void preencherVetor(int *vetor, int tam){
    for(int i = 0; i < tam; i++){
        vetor[i] = geraAleatorio(1, tam*2);
    }
}

void bubbleSort(int *vetor, int tam){
	int aux = 0;
	for(int i = 0; i < tam-1; i++){
		for(int j = 0; j < (tam-i-1); j++){
			if(vetor[j] > vetor[j+1]){
				aux = vetor[j];
				vetor[j] = vetor[j+1];
				vetor[j+1] = aux;
			}
		}
	}
}

void insertionSort(int *vetor, int tam){
	int i, j, aux = 0;
	for(i = 1; i < tam; i++){
		aux = vetor[i];
		for(j = i-1; j >= 0 && vetor[j] > aux; j--){
			vetor[j+1] = vetor[j];
		}
		vetor[j+1] = aux;
	}
}

int *copyArray(int *vetor, int tam){
    int *vCopia = new int[tam];

    // Copiar V em vCopia;
    for(int i = 0; i < tam; i++){
        vCopia[i] = vetor[i];
    }
    return vCopia;
}

void selectionSort(int *vetor, int tam){
    int i, j, min, aux;
    for(i = 0; i < (tam-1); i++){
        min = i;
        for(j = (i+1); j < tam; j++){
            if(vetor[j] < vetor[min]) min = j;
        }
        if(vetor[i] != vetor[min]){
            aux = vetor[i];
            vetor[i] = vetor[min];
            vetor[min] = aux;
        }
    }
}

int main(){

    srand(time(NULL));
    int opcao = 0;
    int tam = 0;
    int cont = 0;

    do{
    cout << "Digite o tamanho do vetor: \n";
    cin >> tam;

    int *vetor = new int[tam];

        cout << "\nQual algoritmo de ordenação deseja?\n" <<
            "1 - Bubble_Sort.\n" <<
            "2 - Insertion_Sort.\n" <<
            "3 - Selection_Sort.\n" <<
            "0 - Sair.\n";
        cin >> opcao;

        if(opcao == 0)
            return 0;

        ofstream arquivo("Arquivo_Teste_Com_50.000.txt", ios::app);// Serve para não sobrecrever

        preencherVetor(vetor, tam);

        for(int i = 0; i < 100; i++){
            auto inicio = steady_clock::now();
            switch(opcao){
                case 1:
                    bubbleSort(copyArray(vetor, tam), tam);
                break;

                case 2:
                    insertionSort(copyArray(vetor, tam), tam);
                break;

                case 3:
                    selectionSort(copyArray(vetor, tam), tam);
                break;
            }

            steady_clock::time_point fim = steady_clock::now();
            cont += duration_cast<milliseconds>(fim-inicio).count();
        }
        arquivo << "\n\nMédia Selection_Sort: " << cont/100 << "\n";
        system("cls");
        cout << "----------\n" << tam <<" Ordenou!\n";
        delete vetor;
    }while(opcao != 0);
}
