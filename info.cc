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
    stream<<"Nome dell'esame: "<<infoToPrint.examName<<"\tEsito: "<<infoToPrint.examScore<<"\tCFU: "<<infoToPrint.CFU<<endl;
} 