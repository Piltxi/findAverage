#include <iostream>
using namespace std; 

#include "exam.h"

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