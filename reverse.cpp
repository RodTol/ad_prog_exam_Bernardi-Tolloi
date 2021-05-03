#include <iostream>

template <typename K> 
K* arr(K const n);

template <typename T>
void rev (T const n, int* vett);

int main () {

 std::cout << "Inserisci dimensione dell'array:" << std::endl;
 int n;
 std::cin >> n;

 /*creo il pointer e lo ottengo dal chiamare la funzione*/
 int* vettore;
 
 vettore = arr(n);

 /* Check*/
 std::cout << "Pointer al primo elemento del vettore\n";
 std::cout << vettore << "\n";
 std::cout << "Elemento indicato dal pointer\n" << *vettore << std::endl;
 
 
 /*stampo il vettore all'incontrario*/
 rev(n, vettore);

 //std::cout << "Prima del delete\n" << *vettore << " --> primo elemento\n"; 
 //std::cout << "Prima del delete\n" << *(vettore+=n-1) << " --> ultimo elemento\n";
 
 delete[] vettore; 
 
 //std::cout << "Dopo il delete\n" << *vettore << " --> primo elemento\n";
 //std::cout << "Dopo il delete\n" << *(vettore+=n-1) << " --> ultimo elemento\n";

}

/*funzione che crea l'array con i valori data una dimensione n*/
template <typename K> 
K* arr(K const n) {

    int* vett{new int[n]};

    std::cout << "Inserisci " << n << " elementi:\n";
    for (int i = 0; i < n; i++)
     {
     std:: cin >> vett[i];
     }

    /* Check*/ 
    std::cout << "Pointer al primo elemento\n" << vett << std::endl; 
    

    return vett;
} 

/*funzione che inverte l'array*/
template <typename T>
void rev(T const n, int* vett) {

    /*mi sposto nell'ultimo indirizzo di memoria*/
    /*ocho che l'ultimo e lo 0 finale, quindi n-1*/
    vett += n-1;

    /*e poi stampo andando indietro*/

    std::cout << "Vettore inverso\n";

    for (int i = 0; i < n; i++)
    {
        std::cout << *(vett--) << "\n";
    }
}
