//-----------------------Entry Point Function of Application-----------------------//

///////////////////////////////////////////////////////////////////////////////
/*
Project Name : Obj Converter
Description  : Used to convert .stl file into .obj file
Author       : Aishwarya Sunil Karande
Date         : 22/08/2022
*/
///////////////////////////////////////////////////////////////////////////////

#include "Header.h" //User defined header file inclusion

///////////////////////////////////////////////////////////////////////////////
//
// Function name: main()
// Input:         -
// Output:        int (to OS)
// Description:   Entry point function of program
// Author:        Aishwarya Sunil Karande
// Date:          22/08/2022
//
///////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() // Entry Point Function of Application
{
    // int iRet = 0;

    fflush(stdin);

    // local variable to accept stl file name from user
    string sFileName;

    sFileName.clear();

    // accepting fime name and storing it in variable
    cout << "Note : stl file should be present in same(current) directory.\n";
    cout << "Enter stl File Name : (without extension)\n";
    cin >> sFileName;

    // creating object of FILE_OP class to perform file operation
    FILE_OP *fobj = new FILE_OP(sFileName);

    // to extract required data from stl file and store it in doubly circular linked list format
    fobj->extractData();

    // this call display created doubly circular linked list on console
    fobj->dobj->displayNodes();

    // create new empty .obj file similar to the name of stl file
    fobj->createObjFile();

    // used to write some starting statements in .obj file
    fobj->writeStartTemplate();

    // used to write vertices in .obj file
    fobj->writeVertices();

    // used to write normal vertices in .obj file
    fobj->writeNormalVertices();

    // used to write faces combination in .obj file
    fobj->writeFaces();

    // deallocating memory after usage
    delete fobj;

    // return success to OS
    return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
