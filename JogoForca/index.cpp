#include <iostream>
#include <string>
using namespace std;

// VARIAVEL EM ESCOPO GLOBAL
const string SECRET_WORD = "Melancia";

bool letterExists(char attempt){

    for(int i = 0; i < SECRET_WORD.size(); i++){
        if(attempt == SECRET_WORD[i]){
            return true;
        }
    }

    return false;
}

int main() {
    
    // char SECRET_WORD[20]; --> MANEIRA DE DECLARAR UMA STRING
    // cout << "A palavra secreta é: " << SECRET_WORD << endl;

    cout << "--* Bem-Vindo ao Jogo da Forca *--" << endl;

    int totalAttempts = 10;

    while(true){

        totalAttempts--;

        char attempt;
        cout << "\nChute uma letra: " << endl;
        cin >> attempt;
        cout << "Seu chute foi: " << attempt << endl;

        if(letterExists(attempt)){
            cout << "\nVocê acertou, a letra " << attempt << " está na palavra!" << endl;
            cout << "Lhe restam " << 10 - totalAttempts << " tentativas!" << endl;
        }

        if(!letterExists(attempt)){
            cout << "\nVocê errou, a letra " << attempt << " não está na palavra!" << endl;
            cout << "Lhe restam " << 10 - totalAttempts << " tentativas!" << endl;
        }
        
        if(totalAttempts == 0){
            cout << "\nSuas chances acabaram, voce enforcou!" << endl;
            break;
        }
    }
}