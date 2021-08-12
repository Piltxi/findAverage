#include <iostream>
#include <cstring>

using namespace std; 

#include "exam.h"

#define nameFile "dati.txt"
//#define DEBUG -> Decommentare per alcune stampe di debug

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

/*!
*\brief loadExam carica tutte le informazioni sugli esami dal file 
*\param fileName nome del file di import
*\param _exam lista con gli esami. Sarà ripristinata in questa procedura
*/
void loadExam (listNode& _exam, const char* fileName) { 

    ifstream import (fileName); 
    if (!import) {cerr<<"[!] Errore fatale in salvataggio file...\n"; return;}

    _exam = NULL;

    cout<<endl<<"Caricamento Informazioni"; 

    int numEOF; 
    while (import>>numEOF) {

        infoType newInfo; 

        readLine(import, newInfo.examName); 
        import>>newInfo.CFU; 
        import>>newInfo.examScore; 

        addNodeInList (_exam, newInfo); 

        cout<<"."; 
    }
    cout<<endl<<"-Caricamento terminato-\n";
}

/*!
* launchOutput stampa tutte le informazioni sugli esami, richiamando delle funzioni
* La procedura prepara il flusso di output e lo manda alla procedura di stampa, viewExam
*\param _exam lista con gli esami da stampare
*\param nameStream nome tipo e flusso output da utilizzare
*\param form booleano usato per distinguere stampa formattata da stampa non formattata
*/
void launchOutput (listNode _exam, bool form, const char* nameStream) {

    if (strcmp (nameStream, "cout") == 0)
        viewExam (_exam, cout, form);
    

    else {
    
        ofstream stream (nameStream); 
        if (!stream) {cerr<<"[!] Errore fatale in salvataggio file...\n"; return;}

        viewExam (_exam, stream, form); 
        stream.close(); 
    } 
}

int main () {

    listNode _exam = NULL; 
    loadExam (_exam, nameFile);

    char menu [] = "Digita 1-> Inserire un nuovo esame..."
                   "\nDigita 2-> Salvare informazioni memorizzate..."
                   "\nDigita 3-> Caricare le informazioni da file..."
                   "\nDigita 4-> Avviare la simulazione per un nuovo esame..."
                   "\nDigita 5-> Stampa esami conclusi..."
                   "\nDigita 0-> Uscire -Salva le informazioni all'interno del file-..."
                   "\nDigita un numero per continuare..."; 

    while (true) {

        int intChoice; 
        do {cout<<endl<<menu; cin>>intChoice; cout<<endl;} while (intChoice < 0 || intChoice > 5); 

        switch (intChoice) {

            case 1: 
                addExam (_exam); 
            break; 

            case 2:

                launchOutput (_exam, false, nameFile); 
                launchOutput (_exam, true, "esami_form.txt"); 
            
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
                    cout<<"Inserisci il nome del file di caricamento> "; cin>>fileName; 
                    
                    loadExam (_exam, fileName); 
                }

                else loadExam (_exam, nameFile);

            break;

            case 4: {

                listNode examTemp = copy (_exam); 
                
                cout<<"\n...Simulazione Esame...\n"; 
                
                char charChoice; 
                do {addExam (examTemp); cout<<"Digita 'n' per terminare la Simulazione...\n"; cin>>charChoice;}
                while (charChoice != 'n'); 

                float examsAverage = findAverage (examTemp);
                cout<<"Media esami: "<<examsAverage<<endl; 

            break; }

            case 5: 
                launchOutput (_exam, true, "cout");
            break;

            case 0: 
                cout<<"Ci vediamo la prossima volta...\n"; launchOutput (_exam, false, nameFile);
                return 0; 
            break;
        }
    }

    return 0; 
}