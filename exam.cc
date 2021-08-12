#include <iostream>
using namespace std; 

#include "exam.h"

void readLine (istream &, char *); 

/*!
*\brief addExam permette l'inserimento manuale, un informazione per volta, di un nodo nella lista 
*\param _exam lista con gli esami. Sarà modificata in questa procedura
*/
void addExam (listNode& _exam) {

    infoType newExam; 
    
    cout<<"Nome dell'esame? "; readLine(cin, newExam.examName); 
    
    do {cout<<"CFU esame? "; cin>>newExam.CFU;}
    while (newExam.CFU < 3 || newExam.CFU > 12); 

    do {cout<<"Esito esame? "; cin>>newExam.examScore;}
    while ((newExam.examScore > 1 && newExam.examScore < 18) || newExam.examScore > 30);  

    #ifdef DEBUG
        cout<<"Esame in elaborazione: "<<endl; 
        viewInfo (newExam, cout);
    #endif

    addNodeInList (_exam, newExam); 

    cout<<"-Caricamento terminato-\n"; 
}

/*!
* countCFU conta i CFU dei singoli esami registrati 
* la funzione distingue esami di profitto e idoneità tramite il parametro all 
*\param _exam lista con gli esami registrati
*\param all booleano utile a considerare tutti gli esami o solo le idoneità
*\return numero di cfu corrispondenti agli esami sostenuti
*/
int countCFU (listNode _exam, const bool all) {

    if (_exam == NULL)
        return 0; 

    if (all) return _exam->exam.CFU + countCFU(tail(_exam), all);

    if (_exam->exam.examScore != 1) return _exam->exam.CFU + countCFU(tail(_exam), all); 
    else return countCFU(tail(_exam), all);
} 

/*!
*\brief findAverage calcola la media degli esami sostenuti
*\param _exam lista con gli esami da considerare
*\return valore numerico della media accademica
*/
float findAverage (listNode _exam) {

    if (_exam == NULL)
        {cout<<"Lista vuota in ingresso...\n"; return 0;}

    int CFU = countCFU (_exam, false);

    #ifdef DEBUG
        cout<<"Numero di CFU trovati: "<<CFU<<endl; 
    #endif
    
    float average = 0; 
    
    while (_exam != NULL) {

        if (_exam->exam.examScore != 1) average += (_exam->exam.examScore * _exam->exam.CFU); 

        #ifdef DEBUG
            cout<<"Somma in lavorazione: "<<average<<endl; 
        #endif

        _exam = tail (_exam); 
    }
    
    return (float)average/CFU; 
}

/*!
*\brief viewExam stampa tutte le informazioni sugli esami
*\param _exam lista con gli esami da stampare
*\param stream flusso di output da considerare per la stampa
*\param form booleano usato per distinguere stampa formattata da stampa non formattata
*/
void viewExam (listNode _exam, ostream& stream, bool form) {

    int i=0; 

    if (form) stream<<"Numero esami sostenuti: "<<countNodes(_exam)<<" ["<<countCFU(_exam, true)<<" CFU] "<<"\tMedia esami: "<<findAverage(_exam)<<endl; 

    while (_exam != NULL) {

        i++; 

        if (form) viewInfo (head(_exam), stream); 
        if (!form) stream<<i<<endl<<_exam->exam.examName<<endl<<head(_exam).CFU<<endl<<head(_exam).examScore<<endl; 

        _exam = tail (_exam); 
    }
}