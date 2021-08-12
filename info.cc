#include <iostream>
#include <cstring>
#include <fstream>
using namespace std; 

#include "info.h"

void copyInfo (infoType& newInfo, infoType infoToCopy) {

    strcpy (newInfo.examName, infoToCopy.examName); 
    newInfo.examScore = infoToCopy.examScore; 
    newInfo.CFU = infoToCopy.CFU; 
}

void viewInfo (infoType infoToPrint, ostream& stream) {
    
    stream<<"Nome Esame: "<<infoToPrint.examName<<"\t"; 
    
    if (infoToPrint.examScore == 1) cout<<"|Esito: IDO"; 
    else cout<<"|Esito: "<<infoToPrint.examScore; 
    
    cout<<"|\tCFU: "<<infoToPrint.CFU<<endl;
} 