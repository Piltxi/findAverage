#include <iostream>
#include <fstream>
#include <cstring>

using namespace std; 

#include "list.h"

#define nameFile "dati.txt"
#define DEBUG

//float findAverage (listNode); 

/*!
*\brief countCFU conta i CFU dei singoli esami registrati 
*\param _exam lista con gli esami registrati
*\return numero di cfu corrispondenti agli esami sostenuti
*/
int countCFU (listNode _exam) {

    if (_exam == NULL)
        return 0; 

    return _exam->exam.CFU + countCFU(tail(_exam)); 
} 

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
*\brief addExam permette l'inserimento manuale, un informazione per volta, di un nodo nella lista 
*\param _exam lista con gli esami. Sarà modificata in questa procedura
*/
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

/*!
*\brief findAverage calcola la media degli esami sostenuti
*\param _exam lista con gli esami da considerare
*\return valore numerico della media accademica
*/
float findAverage (listNode _exam) {

    if (_exam == NULL)
        {cout<<"Lista vuota in ingresso...\n"; return 0;}

    int CFU = countCFU (_exam);

    #ifdef DEBUG
        cout<<"Numero di CFU trovati: "<<CFU<<endl; 
    #endif
    
    float average = 0; 
    while (_exam != NULL) {

        average += (_exam->exam.examScore * _exam->exam.CFU); 

        #ifdef DEBUG
            cout<<"Somma in lavorazione: "<<average<<endl; 
        #endif

        _exam = tail (_exam); 
    }
    
    return (float)average/CFU; 
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

/*!
*\brief viewExam stampa tutte le informazioni sugli esami
*\param _exam lista con gli esami da stampare
*\param stream flusso di output da considerare per la stampa
*\param form booleano usato per distinguere stampa formattata da stampa non formattata
*/
void viewExam (listNode _exam, ostream& stream, bool form) {

    int i=0; 

    if (form) stream<<"Numero esami sostenuti: "<<countNodes(_exam)<<"\tMedia esami: "<<findAverage(_exam)<<endl; 

    while (_exam != NULL) {

        i++; 

        if (form) viewInfo (head(_exam), stream); 
        if (!form) stream<<i<<endl<<_exam->exam.examName<<endl<<head(_exam).CFU<<endl<<head(_exam).examScore<<endl; 

        _exam = tail (_exam); 
    }
}

/*!
* LaunchOutput stampa tutte le informazioni sugli esami, richiamando delle funzioni
* La procedura prepara il flusso di output e lo manda alla procedura di stampa, viewExam
*\param _exam lista con gli esami da stampare
*\param nameStream nome tipo e flusso output da utilizzare
*\param form booleano usato per distinguere stampa formattata da stampa non formattata
*/
void launchOutput (listNode _exam, bool form, const char* nameStream) {

    if (strcmp (nameStream, "cout") == 0) {
        
        viewExam (_exam, cout, true); 
        return;
    }  

    else {
    
        ofstream stream (nameStream); 
        if (!stream) {cerr<<"[!] Errore fatale in salvataggio file...\n"; return;}

        viewExam (_exam, stream, form); 
    }
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
                    cout<<"Inserisci il nome del file> "; cin>>fileName; 
                    
                    loadExam (_exam, fileName); 
                }

                else loadExam (_exam, nameFile);

            break;

            case 4: {
                listNode examTemp = copy (_exam); 
                
                cout<<"\n...Simulazione Esame...\n"; 
                addExam (examTemp); 

                float examsAverage = findAverage (examTemp);

                cout<<"Media esami: "<<examsAverage<<endl; 
            break;}

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