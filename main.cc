#include <iostream>
#include <fstream>
#include <cstring>

using namespace std; 

#include "list.h"

#define nameFile "dati.txt"
#define DEBUG

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

ostream& selectOutput (const char* nameStream) {

    if (strcmp (nameStream, "cout") == 0)
        return cout; 

    ofstream stream (nameStream); 
    return stream; 
}

void viewAll (listNode _exam, bool form, const char* nameStream) {

    ofstream& stream = selectOutput (nameStream); 
    
    #ifdef DEBUG
        stream<<"Stampa di debug...\n"; 
    #endif

    if (!stream) {cerr<<"[!] Errore fatale in salvataggio file...\n"; return;}

    if (form) stream<<"Numero esami sostenuti: "<<countNodes(_exam)<<endl; 

    for (int i=0; _exam != NULL; i++, _exam = tail (_exam)) {
        if (form) viewInfo (head(_exam), stream); 
        
        if (!form) stream<<i<<endl<<head(_exam).examName<<endl<<head(_exam).CFU<<endl<<head(_exam).examScore<<endl; 
    }

    if (form) stream<<"Ciao, al prossimo caricamento...\n"; 
}

void loadExam (listNode& _exam, const char* fileName) { 

    ifstream import (fileName); 
    if (!import) {cerr<<"[!] Errore fatale in salvataggio file...\n"; return;}

    _exam = NULL;

    int numEOF; 
    while (import>>numEOF) {

        infoType newInfo; 

        readLine(import, newInfo.examName); 
        import>>newInfo.CFU; 
        import>>newInfo.examScore; 

        addNodeInList (_exam, newInfo); 

        cout<<"Caricamento esame num. "<<numEOF<<endl; 
    }
    cout<<"-Caricamento terminato-\n";
}

int main () {

    listNode _exam = NULL; 

    char menu [] = "Digita 1-> Inserire un nuovo esame..."
                   "\nDigita 2-> Salvare informazioni memorizzate..."
                   "\nDigita 3-> Caricare le informazioni dal file..."
                   "\nDigita 4-> Avviare la simulazione per un nuovo esame..."
                   "\nDigita 5-> Stampa esami conclusi..."
                   "\nDigita 0-> Uscire -Salva le informazioni all'interno del file-..."
                   "\nDigita un numero per continuare..."; 

    while (true) {

        int intChoice; 
        do {cout<<menu; cin>>intChoice;} while (intChoice < 0 || intChoice > 5); 

        switch (intChoice) {

            case 1: 
                addExam (_exam); 
            break; 

            case 2:
                viewAll (_exam, false, nameFile); 
            break; 

            case 3: 

                char charChoice; 
                do {
                    cout<<"Digita 's' per caricare le informazioni da un file preciso...\n"
                          "Digita 'n' per caricare le informazioni dal file predefinito...\n"
                          "Premi un pulsante per continuare> s/n "; 
                          cin>>charChoice; 
                } while (charChoice != 's' && charChoice != 'n'); 

                if (charChoice == 's') {

                    char fileName [nameSize]; 
                    cout<<"Inserisci il nome del file> "; cin>>fileName; 
                    
                    loadExam (_exam, fileName); 
                }

                else loadExam (_exam, nameFile);

            break;

            case 4: 
                return 0; 
            break;

            case 5: 
                viewAll (_exam, true, "cout");
            break;

            case 0: 
                cout<<"Ci vediamo la prossima volta...\n"; viewAll (_exam, false, nameFile);
                return 0; 
            break;
        }
    }
    
    return 0; 
}