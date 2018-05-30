
#include "Point.h"
#include <iostream>
#include <fstream>
#include <math.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
using namespace std;

class Board {
    public:
    int size;
    char **pBoard;

    Board(){}
    
    Board(int size){
        this->size = size;
        pBoard = new char*[size];
        for(int i = 0; i < size; i++){
            pBoard[i] = new char[size];
        }
    }
    
    Board(const Board& b){
        size = b.size;
        pBoard = new char*[size];
        for(int i = 0; i < size; i++){
            pBoard[i] = new char[size];
        }
        *this = b;
    }
    
    Board& operator=(const Board& b){
        for (int i = 0; i < size; i++) {
            for(int j = 0; j < size; j++){
                pBoard[i][j]=b.pBoard[i][j];
            }
        }
        return *this;
    }
    
    friend ostream& operator<<(ostream& os, Board const& b) {  
        for (int i = 0; i < b.size; i++) {
            for(int j=0; j<b.size; j++){
                os << b.pBoard[i][j];
            }
            os << endl;
        }
        return os;  
    }
    
    friend istream& operator>>(istream & is, Board& b) {  
        string s;
        is >> s;
        int nsize = s.length();
        
        Board temp(nsize);
        b.size = nsize;
        b.pBoard = temp.pBoard;
        
        for (int i = 0; i < nsize; i++) {
            b.pBoard[0][i] = s[i];
        }
        for (int j = 1; j < nsize; j++) {
            is >> s;
            for (int i = 0; i < nsize; i++) {
                b.pBoard[j][i] = s[i];
            }
        }
        return is;  
    }
    
    char* draw(int imgSize){
    
        ofstream img ("img.ppm");
        
        int **finalMat = new int*[imgSize];
        for(int i = 0; i < imgSize; ++i) {
            finalMat[i] = new int[imgSize];
        }
        
        createBoard(finalMat, imgSize);
        
        img << "P3" << endl;
        img << imgSize << " " << imgSize << endl;
        img << 255 << endl;
        
        for (int y = 0; y < imgSize; y++) {
            for (int x = 0; x < imgSize; x++) {
                if (finalMat[y][x] == 1) 
                    img << "160 160 160" << endl;
                else if (finalMat[y][x] == 2) 
                    img << "77 122 245" << endl;
                else if (finalMat[y][x] == 3) 
                    img << "245 77 77" << endl;
                else
                    img << "255 255 255" << endl; 
            }
        }
        
        return "img.ppm";
    }

    void createBoard(int** finalMat, int imgSize){
    int gSize = imgSize/size;
    int** matX = makeX(imgSize);
    int** matO = makeO(imgSize);
    int** matWhite = makeWhite(imgSize);

    
    for (int i = 0; i < size; i++) { /// Go over grids
        
        for (int j = 0; j < size; j++) {
            
            for (int y = 0; y < gSize; y++) { /// Go over rows
            
                for (int x = 0; x < gSize; x++) { /// Go over columns
                    if (pBoard[i][j] == 'X') {
                        if (matX[y][x] == 1){
                            finalMat[(y + i*gSize)%imgSize][(x + j*gSize)%imgSize] = 1;
                        }
                        else if (matX[y][x] == 2){
                            finalMat[(y + i*gSize)%imgSize][(x + j*gSize)%imgSize] = 2;
                        }
                        else {
                            finalMat[(y + i*gSize)%imgSize][(x + j*gSize)%imgSize] = 0;
                        }
                    }
                    else if (pBoard[i][j] == 'O') {
                        if (matO[y][x] == 1){
                            finalMat[(y + i*gSize)%imgSize][(x + j*gSize)%imgSize] = 1;
                        }
                        else if (matO[y][x] == 3){
                            finalMat[(y + i*gSize)%imgSize][(x + j*gSize)%imgSize] = 3;
                        }
                        else {
                            finalMat[(y + i*gSize)%imgSize][(x + j*gSize)%imgSize] = 0;
                        }
                    }
                    else if (pBoard[i][j] == '.') {
                        finalMat[(y + i*gSize)%imgSize][(x + j*gSize)%imgSize] = 0;
                    }
                    if (y == gSize - 1 || x == gSize - 1 || y == 0 || x == 0){
                        finalMat[(y + i*gSize)%imgSize][(x + j*gSize)%imgSize] = 1;
                    }
                }
            }
            
            
        }
    
    }
    
}

    int** makeX(int imgSize){
    
    // Create matrix to contain pixels of X img
    int matSize = imgSize / size;
    int **mat = new int*[matSize];
    for(int i = 0; i < matSize; ++i) {
        mat[i] = new int[matSize];
    }
    
    int diff = matSize/30;
    int margin = (int)(matSize/7); 
    
    // Fill matrix
    for (int y = margin; y < matSize - margin; y++) {
        for (int x = margin ; x < matSize - margin; x++){
            if(y <= x + diff && y >= x - diff){
                mat[y][x] = 2;
            }
            else if(y <= matSize - x + diff && y >= matSize - x - diff){
                mat[y][x] = 2;
            }
            else {
                mat[y][x] = 0;
            }
        }
    }
    
    return mat;
    
    
    
}
    
    int** makeO(int imgSize){
    
    // Create matrix to contain pixels of O img
    int matSize = imgSize / size;
    int **mat = new int*[matSize];
    for(int i = 0; i < matSize; ++i) {
        mat[i] = new int[matSize];
    }
    
    int diff = matSize/40;
    int margin = (int)(matSize/8); 
    int radius = matSize/2 - margin;
    
    // Fill matrix
    for (int y = 0; y < matSize; y++) {
        for (int x = 0; x < matSize; x++){
            if (floor(sqrt((x-matSize/2)*(x-matSize/2) + (y-matSize/2)*(y-matSize/2))) >= radius - diff 
                && floor(sqrt((x-matSize/2)*(x-matSize/2) + (y-matSize/2)*(y-matSize/2))) <= radius + diff) {
                 mat[y][x] = 3;
            }
            else {
                 mat[y][x] = 0;
            }
        }
        
    }
    
    return mat;
    
}

    int** makeWhite(int imgSize){
    
    // Create matrix to contain white square
    int matSize = imgSize / size;
    int **mat = new int*[matSize];
    for(int i = 0; i < matSize; ++i) {
        mat[i] = new int[matSize];
    }
    
    // Fill matrix
    for (int y = 0; y < matSize; y++) {
        for (int x = 0; x < matSize; x++){
            mat[y][x] = 0;
        }
        
    }
    
    return mat;
    
}
    
};

int main() {
// 	Board b;
// 	cin >> b;
// 	cout << b << endl;
	
	Board board;
	cin >> board;
	string filename = board.draw(400);
	cout << filename << endl;
	
	
	
	
	
	
	
	
}
