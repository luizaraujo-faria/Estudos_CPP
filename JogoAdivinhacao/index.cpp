#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {

    srand(time(NULL));

    // CONSTANTE
    const int secretNumber = rand() % 100;
    cout << "O numero secreto é " << secretNumber << endl;

    // COUT COMANDO DE SAIDA
    cout << "--* Bem-Vindo ao jogo da adivinhação *--" << endl;
    cout << "     -- Você tem 10 tentativas! --" << endl;
    
    cout << "\nEscolha o seu nível de dificuldade: " << endl;
    cout << "Fácil (F), Médio (M) ou Difícil (D)" << endl;

    char diff;
    cin >> diff;

    int totalAttempts;

    if (diff == 'F'){
        totalAttempts = 15;
    }
    else if (diff == 'M'){
        totalAttempts = 10;
    }
    else if(diff == 'D'){
        totalAttempts = 5;
    } 

    int currentAttempt = totalAttempts;

    cout << "   \nVocê terá " << totalAttempts << " tentativas." << endl;

    while(true){

        currentAttempt--;    

        int attempt;
        cout << "\nQual seu chute?: ";
        cin >> attempt;  // CIN COMANDO DE ENTRADA
        cout << "O valor do seu chute é: " << attempt << endl;

        bool above = attempt > secretNumber;
        bool below = attempt < secretNumber;
        bool equal = attempt == secretNumber;

        if(currentAttempt == 0){
            cout << "\nSuas tentativas acabaram!" << endl;
            cout << "   - Você perdeu!" << endl;
            break;
        }

        if(equal){
            cout << "\nParabéns! Você acertou o número secreto!" << endl;
            cout << "   - Você acertou em " << totalAttempts - currentAttempt << " tentativas" << endl;
            break;
        }
        else if(above){
            cout << "\nSeu chute foi maior que o número secreto!" << endl;
            cout << "   - Lhe restam " << currentAttempt << " tentativas!" << endl;
            cout << "\nTente novamente: ";
        }
        else{
            cout << "\nSeu chute foi menor que o número secreto!" << endl;
            cout << "   - Lhe restam " << currentAttempt << " tentativas!" << endl;
            cout << "\nTente novamente: ";
        }
    }
}