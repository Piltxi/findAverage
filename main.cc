#include <iostream>
#include <fstream>
#include <cstring>

using namespace std; 

#include "list.h"

#define nameFile "dati.txt"

/*!
*\brief readLine permette di acquisire un intera riga in input, fino al carattere '\n'
*\param stream flusso di input da considerare
*\param buffer array su cui depositare i caratteri acquisiti
*/
void readLine (istream &stream, char *buffer) {
	while (stream.peek() == '\n')
		stream.get();
	
    stream.get (buffer, nameSize);
	stream.get();
}

void addExam (listNode& _exam) {

    infoType newExam; 
    
    cout<<"Nome dell'esame? "; readLine(cin, newExam.examName); 
    cout<<"CFU esame? "; cin>>newExam.CFU; 
    cout<<"Esito esame? "; cin>>newExam.examScore; 

    #ifdef DEBUG
        cout<<"Esame in elaborazione: "<<endl; 
        viewInfo (newExam, cout);
    #endif

    addNodeInList (_exam, newExam); 

    cout<<"-Caricamento terminato-\n"; 
}

void viewAll (listNode _exam, bool form, const char* fileName) {

    ofstream stream (fileName); 
    if (!stream) {cerr<<"[!] Errore fatale in salvataggio file...\n"; return;}

    for (; _exam != NULL; _exam = tail (_exam))
        if (form) viewInfo (head(_exam), stream); 
        else stream<<head(_exam).examName<<endl<<head(_exam).CFU<<endl<<head(_exam).examScore<<endl; 

    stream.close(); 
}

int main () {

    listNode _exam = NULL; 

    char menu [] = "Digita 1-> Inserire un nuovo esame..."
                   "Digita 2-> Salvare informazioni memorizzate..."
                   "Digita 3-> Caricare le informazioni dal file..."
                   "Digita 4-> Avviare la simulazione per un nuovo esame..."
                   "Digita 5-> Stampa esami conclusi..."
                   "Digita 0-> Uscire -Salva le informazioni all'interno del file-"; 

    
    while (true) {

        int intChoice; 
        do {cout<<menu; cin>>intChoice;} while (intChoice < 1 || intChoice > 5); 

        switch (intChoice) {

            case 1: 
                addExam (_exam); 
            break; 

            case 2:
                viewAll ();
            break; 

            case 3: 

            break;

            case 4: 

            break;

            case 5: 

            break;

            case 0:
                saveAll (nameFile); 
            break;

        }

    }
    
    return 0; 
}