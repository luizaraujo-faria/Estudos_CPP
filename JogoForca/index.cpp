#include <iostream> // LIB PARA ENTRADA E SAÍDA DE DADOS NO CMD
#include <string>   // LIB PARA UTILIZAR O TIPO STRING
#include <map>  // LIB PARA ADICIONAR DICIONARIO "MAP"
#include <vector>   // LIB PARA ADICIONAR O VECTOR "VETOR DINAMICO"
#include <fstream> // LIB PARA ADICIONAR O IFSTREAM "MANIPULAR ARQUIVOS"
#include <ctime>
#include <cstdlib>
using namespace std;    // LIB PADRÃO DO C++

// char secretWord[20]; --> MANEIRA DE DECLARAR UMA STRING
// cout << "A palavra secreta é: " << secretWord << endl;

char attempt;
// VARIAVEL EM ESCOPO GLOBAL
string secretWord;
// TOTAL DE TENTATIVAS
int totalAttempts = 5;
// DICIONÁRIO PARA MAPEAR AS LETRAS DA PALAVRA SECRETA
map<char, bool> wordLetters;
//  VETOR DINAMICO PARA SALVAR OS CHUTES ERRADOS
vector<char> badAttempts;


//  LE O TXT COM AS PALAVRAS E AS LISTA
vector<string> readWordFile() {
    vector<string> wordsInFile;

    ifstream file;
    file.open("words.txt"); // ABRE O ARQUIVO

    //  VERIFICA SE O ARQUIVO FOI ABERTO E LIDO CORRETAMENTE
    if(file.is_open()){
        int totalWords;
        file >> totalWords; // PEGA O PRIMEIRO ELEMENTO DO ARQUIVO

        // cout << "O jogo possui " << totalWords << " palavras.\n" << endl;

        for(int i = 0; i < totalWords; i++){
            string readedWord;
            file >> readedWord;
            // cout << i + 1 << "-" << readedWord << endl;
            wordsInFile.push_back(readedWord);
        }

        file.close();   // FECHA O ARQUIVO
        return wordsInFile;
    }
    else{
        cout << "Não foi possível acessar o banco de palavras." << endl;
        exit(0);
    }
}

void randomWord() {
    vector<string> words = readWordFile();

    srand(time(NULL));
    int randomIndex = rand() % words.size();

    secretWord = words[randomIndex];
    // cout << "Palavra sorteada " << secretWord;
}

void setStart(){
    randomWord();
    cout << "\n****************************************" << endl;
    cout << "****** Bem-Vindo ao Jogo da Forca ******" << endl;
    cout << "****************************************" << endl;
    cout << "\n--- Você terá um total de " << totalAttempts << " tentativas ---" << endl;
}

void makeAttempt() {
    // char attempt;
    cout << "\nChute uma letra: ";
    cin >> attempt;
    wordLetters[attempt] = true;
}

bool letterExists(char attempt){
    // C++ 11 - MANEIRA MAIS MODERNA
    for(char letter : secretWord){
        if(attempt == letter){
            cout << "\nVocê acertou, a letra '" << attempt << "' está na palavra!" << endl;
            cout << "Ainda lhe restam " << totalAttempts << " tentativas!" << endl;
            return true;
        }
    }

    cout << "\nVocê errou, a letra '" << attempt << "' não está na palavra!" << endl;
    cout << "Lhe restam " << --totalAttempts << " tentativas!" << endl;
    return false;
}

void showWordState() {
    cout << endl;
    cout << "*** PALAVRA: ";
    //  ITERA POR CADA LETRA DA PALAVRA
    for(char letter : secretWord){
        // VERIFICA SE A LETRA EXISTE
        if(wordLetters[letter]){
            // SE SIM, MARCA VERDADEIRO NO DICIONÁRIO E IMPRIME A LETRA NA TELA
            cout << letter << " ";
        }
        else{
            // CASO CONTRÁRIO EXIBE LINHA VAZIA ṔARA CADA LETRA
            cout << "_ ";
        }
    }
    cout << endl;
}

void showBadAttempts() {
    cout << "*** CHUTES ERRADOS: ";
    for(char letter : badAttempts){
        cout << letter << " ";
    }
    cout << endl;
}

bool incompletedWord(){
    for(char letter : secretWord){
        if(!wordLetters[letter]){
            return true;
        }
    }

    cout << "\n***** PARABÉNS, VOCÊ ACERTOU A PALAVRA SECRETA *****" << endl;
    cout << "A PALAVRA SECRETA ERA --- " << secretWord << " ---" << endl;
    return false;
}

bool gameOver() {
    if(badAttempts.size() == 5){
        cout << "\n***** GAME OVER *****" << endl;
        cout << "SUAS CHANCES ACABARAM, VOCÊ ENFORCOU!" << endl;
        return true;
    }
    
    return false;
}


int main() {

    setStart();
    while(incompletedWord()){

        showWordState();
        showBadAttempts();
        makeAttempt();

        if(!letterExists(attempt))
            badAttempts.push_back(attempt);
        
        if(gameOver())
            break;
    }
}