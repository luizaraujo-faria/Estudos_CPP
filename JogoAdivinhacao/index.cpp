#include <iostream>
using namespace std;

int main() {

    // COUT COMANDO DE SAIDA
    cout << "--* Bem-Vindo ao jogo da adivinhação *--" << endl;
    cout << "     -- Você tem 10 tentativas! --" << endl;


    // CONSTANTE
    const int secretNumber = 42;
    
    int totalAttempts = 10;    

    while(true){

        totalAttempts--;

        int attempt;
        cout << "\nQual seu chute?: ";
        cin >> attempt;  // CIN COMANDO DE ENTRADA
        cout << "O valor do seu chute é: " << attempt << endl;

        bool above = attempt > secretNumber;
        bool below = attempt < secretNumber;
        bool equal = attempt == secretNumber;

        if(totalAttempts == 0){
            cout << "\nSuas tentativas acabaram!" << endl;
            cout << "   - Você perdeu!" << endl;
            break;
        }

        if(equal){
            cout << "\nParabéns! Você acertou o número secreto!" << endl;
            cout << "   - Você acertou em " << 10 - totalAttempts << " tentativas" << endl;
            break;
        }
        else if(above){
            cout << "\nSeu chute foi maior que o número secreto!" << endl;
            cout << "   - Lhe restam " << totalAttempts << " tentativas!" << endl;
            cout << "\nTente novamente: ";
        }
        else{
            cout << "\nSeu chute foi menor que o número secreto!" << endl;
            cout << "   - Lhe restam " << totalAttempts << " tentativas!" << endl;
            cout << "\nTente novamente: ";
        }
    }
}