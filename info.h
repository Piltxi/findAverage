const int nameSize = 30; 

struct infoType {

    int examScore; 
    int CFU; 
    char examName [nameSize]; 
}; 

void copyInfo (infoType&, infoType);
void viewInfo (infoType, ostream&); 