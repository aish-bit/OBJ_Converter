//---------------------------------User Defined Header File---------------------------------//

// #pragma once

///////////////////////////////////////////////////////////////////////////////////////////////////

//Pre Defined Header file inclusion

///////////////////////////////////////////////////////////////////////////////////////////////////

// to perform  std i/o in c++
#include <iostream>
// to use vector in program
#include <vector>
// to use map in program
#include <map>
// to perform string related operations
#include <string>
// to perform file i/o opreration
#include <fstream>
#include <sstream>

// to include cin and cout objects of istream and ostream classes which are present in iostream header file
using namespace std;



///////////////////////////////////////////////////////////////////////////////////////////////////

//User Defined Classes declaration : 

//////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/*
Class Name     :  NODE
Description    :  class is a blueprint structure of each node of doubly 
                  circular linked list.                  
Author         :  Aishwarya Sunil Karande
Date           :  22/08/2022
*/
///////////////////////////////////////////////////////////////////////////////

class NODE
{
public:
    NODE *prev;
    vector<string> sNormalVertex;
    vector<string> sVertexX;
    vector<string> sVertexY;
    vector<string> sVertexZ;
    NODE *next;

    NODE();

    ~NODE();
};


///////////////////////////////////////////////////////////////////////////////
/*
Class Name     :  DATA
Description    :  To create a doubly circular linked list of triangle deatils 
                  where each node contain data from one loop                   
Author         :  Aishwarya Sunil Karande
Date           :  22/08/2022
*/
///////////////////////////////////////////////////////////////////////////////

class DATA
{

private:
    NODE *first;
    NODE *last;
    int iNodeCnt;

public:
    DATA();
    ~DATA();
    void insertLast(vector<string>, vector<string>, vector<string>, vector<string>);
    void displayNodes();
    NODE *accessListStart();
    NODE *accessListEnd();
    int accessNodeCnt();
};


///////////////////////////////////////////////////////////////////////////////
/*
Class Name     :  FILE_OP
Description    :  Class perform file operations like reading & extracting data 
                  from stl file,creating new obj file and writing obj file        
Author         :  Aishwarya Sunil Karande
Date           :  22/08/2022
*/
///////////////////////////////////////////////////////////////////////////////

class FILE_OP

{
public:
    string sFileName;                          // this is file name without extension
    string sSourceFileName;                    // this is the name of stl file
    string sDestFileName;                      // this is the name of obj file
    DATA *dobj;                                // composition of DCLL class DATA
    ofstream destFile;                         // to write obj file
    map<vector<string>, char> normalVertexMap; // to store unique normal vertices and their index value
    map<vector<string>, char> xyzVertexMap;    // to store unique xyz vertices and their index value

public:
    FILE_OP(string);
    ~FILE_OP();
    void extractData();
    void createObjFile();
    void writeStartTemplate();
    void writeVertices();
    void writeNormalVertices();
    void writeFaces();
};

