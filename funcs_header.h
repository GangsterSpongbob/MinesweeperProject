#ifndef Mines
#define Mines

const int maxArrayLength{ 100 }; // maximum array length is 100 elements

extern int arrSize, mines;
extern int** playingField, ** maskedField;

int strToInt(const char*);
bool Compare(const char*, const char*), checkInteger(const char*), gameOver(), gameWon();
void delArr(int**&, const int&), clearStr(char*), openTile(const int&, const int&);
void getTableSize(char*), getMineCount(char*);
void setMessage(char*, const char[]), getLine(char*), getWord(char*);
void maskTable(), populateTable(int), printTable();
char* openFunc(const int&, const int&), * markFunc(const int&, const int&), * unmarkFunc(const int&, const int&);

#endif // !Mines
