
///////////////////////////////////////////////////////////////////////////////
//
// This file contains definition of FILE_OP class
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////

#include "Header.h" //User defined header file inclusion

///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/*
Class Name     :  FILE_OP
Function Name  :  FILE_OP()
Input          :  STRING
Output         :  -
Description    :  Constructor: used to initialise non static characteristics
                  of class as well as allocate external resources
Author         :  Aishwarya Sunil Karande
Date           :  22/08/2022
*/
///////////////////////////////////////////////////////////////////////////////

FILE_OP::FILE_OP(string sFileName)
{

    // allocating resources as well as initiaising non static characteristics of class
    (this->sFileName) = sFileName;        // file name without extension
    sSourceFileName = sFileName + ".stl"; // file name with .stl extension
    sDestFileName = sFileName + ".obj";   // file name with .obj extension
    dobj = new DATA();                    // memory allocation to DATA class to create linked list of required data
    destFile.open(sDestFileName);         // opening .obj file for writing purpose
}

///////////////////////////////////////////////////////////////////////////////
/*
Class Name     :  FILE_OP
Function Name  :  ~FILE_OP()
Input          :  -
Output         :  -
Description    :  Destructor: used to deallocate resources
Author         :  Aishwarya Sunil Karande
Date           :  22/08/2022
*/
///////////////////////////////////////////////////////////////////////////////

FILE_OP::~FILE_OP()
{
    // deallocating resources to free memory of class

    sFileName.clear();
    sSourceFileName.clear();
    sDestFileName.clear();

    // deallocating memory of DATA class
    delete dobj;

    // closing dest file after writing
    destFile.close();
}

///////////////////////////////////////////////////////////////////////////////
/*
Class Name     :  FILE_OP
Function Name  :  extractData()
Input          :  -
Output         :  -
Description    :  Used to extract required data by reading .stl file into Doubly
                  Circular Linked List
Author         :  Aishwarya Sunil Karande
Date           :  22/08/2022
*/
///////////////////////////////////////////////////////////////////////////////

void FILE_OP::extractData()
{
    /////////////////////////////////////////////////////////////////
    // local variables used in function
    string sBuffer;
    string sWord;
    string sTemp;

    int iCnt = 0; // loop counter
    int iCnt1 = 0;
    int iVertexIndex = 0;
    int iPos = 0;

    string sChkWord1 = "facet";
    string sChkWord2 = "vertex";

    vector<string> wordArray;
    vector<string> sNormalVertex;
    vector<string> sVertexX;
    vector<string> sVertexY;
    vector<string> sVertexZ;

    sBuffer.clear();
    sWord.clear();
    wordArray.clear();
    sNormalVertex.clear();
    sVertexX.clear();
    sVertexY.clear();
    sVertexZ.clear();
    sTemp.clear();

    /////////////////////////////////////////////////////////////////
    // Note : source file open
    ifstream ifSourceFile;
    ifSourceFile.open(sSourceFileName); // opening source file
    /////////////////////////////////////////////////////////////////

    // reading file line by line and extracting required data into doubly circular linked list
    if (ifSourceFile.is_open())
    {

        while (getline(ifSourceFile, sBuffer)) // to read .stl source file line by line
        {

            stringstream strObj(sBuffer); // X is an object of stringstream that references the S string

            while (getline(strObj, sWord, ' '))
            {
                /* strObj represents to read the string from stringstream, sWord use for store the token string and,
                 ' ' whitespace represents to split the string where whitespace is found. */

                wordArray.push_back(sWord);
            }

            for (iCnt = 0; iCnt < wordArray.size(); iCnt++) // checking facet and vertex word is present in line or not
            {
                if ((wordArray[iCnt] == sChkWord1) || (wordArray[iCnt] == sChkWord2))
                {
                    break;
                }
            }

            if (iCnt != wordArray.size()) // if facet and vertex word present in line then only reading that line ahead to extract data otherwise taking next line
            {

                // for (iCnt = 0; iCnt < wordArray.size(); iCnt++)
                // {
                //     cout << wordArray[iCnt] << "\n";
                // }
                iCnt = 0;
                iCnt1 = 0;
                iVertexIndex++;

                // cout <<iVertexIndex << "\n";

                //     for (iCnt = 0; iCnt < sVertexX.size(); iCnt++)
                //     {
                //         cout << sVertexX[iCnt] << "\t";

                //     }

                //     cout << "\n";

                if (iVertexIndex == 5)

                {
                    iVertexIndex = 1;
                }

                for (iCnt = 0, iCnt1 = 0; iCnt < wordArray.size(); iCnt++)
                {
                    while (wordArray[iCnt][iCnt1] != '\0')
                    {
                        if (((wordArray[iCnt][iCnt1] >= '0') && (wordArray[iCnt][iCnt1] <= '9')) || (wordArray[iCnt][iCnt1] == '-'))
                        {
                            // Find position of '.' using find()
                            // iPos = wordArray[iCnt].find(".");

                            // Copy substring before pos
                            // sTemp = wordArray[iCnt].substr(0, iPos);

                            sTemp = wordArray[iCnt];

                            if (iVertexIndex == 1)
                            {
                                sNormalVertex.push_back(sTemp);
                            }
                            else if (iVertexIndex == 2)
                            {
                                sVertexX.push_back(sTemp);
                            }
                            else if (iVertexIndex == 3)
                            {
                                sVertexY.push_back(sTemp);
                            }
                            else if (iVertexIndex == 4)
                            {
                                sVertexZ.push_back(sTemp);
                            }

                            break;
                        }
                        iCnt1++;
                        sTemp.clear();
                        iPos = 0;
                    }

                    // iCnt1 = 0;
                }

                if (iVertexIndex == 4)
                {
                    dobj->insertLast(sNormalVertex, sVertexX, sVertexY, sVertexZ);

                    sNormalVertex.clear();
                    sVertexX.clear();
                    sVertexY.clear();
                    sVertexZ.clear();
                }
            }

            // clearing buffer to read next line
            sBuffer.clear();
            wordArray.clear();
            sWord.clear();
            // iCnt = 0;
        }
    }

    // closing source file after reading
    ifSourceFile.close();
}

///////////////////////////////////////////////////////////////////////////////
/*
Class Name     :  FILE_OP
Function Name  :  createObjFile()
Input          :  -
Output         :  -
Description    :  Used to create new empty .obj file
Author         :  Aishwarya Sunil Karande
Date           :  22/08/2022
*/
///////////////////////////////////////////////////////////////////////////////

void FILE_OP::createObjFile()
{
    ifstream ifSourceFile;
    fstream destFile;

    ifSourceFile.open(sSourceFileName); // opening source file

    // to create empty obj file with same file name as stl file
    if (ifSourceFile)
    {
        destFile.open(sDestFileName, ios::out);

        if (!destFile)
        {
            cout << "Error in creating file!!!";
            return;
        }
    }
    else
    {
        cout << "There is no such stl file available. Kindly check.\n";
    }

    // closing files after creating obj file
    ifSourceFile.close();
    destFile.close();
    return;
}

///////////////////////////////////////////////////////////////////////////////
/*
Class Name     :  FILE_OP
Function Name  :  writeStartTemplate()
Input          :  -
Output         :  -
Description    :  used to write some starting statements in .obj file
Author         :  Aishwarya Sunil Karande
Date           :  22/08/2022
*/
///////////////////////////////////////////////////////////////////////////////

void FILE_OP::writeStartTemplate()
{
    if (destFile.is_open())
    {
        destFile << "# .stl file to .obj file export"
                 << "\n\n";
        destFile << "g " << sFileName << "\n\n";
    }
    else
    {
        cout << "Unable to open destination file for writing purpose.Check whether it exists or not or Contact developer. \n";
        return;
    }
}

///////////////////////////////////////////////////////////////////////////////
/*
Class Name     :  FILE_OP
Function Name  :  writeVertices()
Input          :  -
Output         :  -
Description    :  used to write vertices in .obj file
Author         :  Aishwarya Sunil Karande
Date           :  22/08/2022
*/
///////////////////////////////////////////////////////////////////////////////

void FILE_OP::writeVertices()
{
    /////////////////////////////////////////////////////////////////
    // local variables used in function

    // loop counter
    int iCnt = 0;
    int iCnt1 = 0;
    int iCnt2 = 0;
    int iCnt3 = 0;
    int iCnt4 = 0;

    // to count unique vertices
    char iUnique = '\0';

    // accessing DCLL to write nodes in obj file
    NODE *head = NULL;
    NODE *tail = NULL;
    int iNodeCnt = 0;
    // getting addresses into variables to acces linked list
    head = dobj->accessListStart();
    tail = dobj->accessListEnd();
    iNodeCnt = dobj->accessNodeCnt();

    // tmporary variable
    NODE *start = NULL;
    NODE *end = NULL;
    NODE *temp1 = NULL;
    // NODE *temp2 = NULL;
    vector<string> sTemp;
    sTemp.clear();

    /////////////////////////////////////////////////////////////////
    // checking whether the Doubly Circular linked list is empty or not
    if ((head == NULL) && (tail == NULL))
    {
        cout << "Somthing went wrong....!!! Please check.Linked list is empty.Or contact developer\n";
        return;
    }
    /////////////////////////////////////////////////////////////////
    // writing data in dest obj file

    //--------------------writing  unique vertices (v) in file logic start--------------------//

    iUnique = '\0', iCnt = 0, iCnt1 = 0, iCnt2 = 0, iCnt3 = 0, iCnt4 = 0, sTemp.clear();
    temp1 = NULL;
    start = head;

    for (int iCnt = 1; iCnt <= iNodeCnt; iCnt++)
    {
        for (iCnt3 = 1; iCnt3 <= 3; iCnt3++)
        {
            for (int iCnt1 = 0; iCnt1 < (head->sNormalVertex.size()); iCnt1++)
            {
                if (iCnt == 1 && iCnt3 == 1)
                {

                    if (iCnt1 == 0)
                    {
                        iUnique = '1';
                        xyzVertexMap[start->sVertexX] = iUnique;
                        destFile << "v " << start->sVertexX[iCnt1] << " ";
                    }
                    else
                    {
                        destFile << start->sVertexX[iCnt1] << " ";
                    }
                }
                else if (iCnt == 1 && iCnt3 == 2)
                {

                    if (iCnt1 == 0)
                    {
                        iUnique++;
                        xyzVertexMap[start->sVertexY] = iUnique;
                        destFile << "v " << start->sVertexY[iCnt1] << " ";
                    }
                    else
                    {
                        destFile << start->sVertexY[iCnt1] << " ";
                    }
                }
                else if (iCnt == 1 && iCnt3 == 3)
                {

                    if (iCnt1 == 0)
                    {
                        iUnique++;
                        xyzVertexMap[start->sVertexZ] = iUnique;
                        destFile << "v " << start->sVertexZ[iCnt1] << " ";
                    }
                    else
                    {
                        destFile << start->sVertexZ[iCnt1] << " ";
                    }
                }
                else
                {
                    if (iCnt3 == 1)
                    {
                        sTemp.clear();
                        temp1 = NULL;
                        sTemp = start->sVertexX;
                        temp1 = start->prev;

                        for (iCnt2 = iCnt; iCnt2 > 1; iCnt2--)
                        {
                            for (iCnt4 = 0; iCnt4 < 3; iCnt4++)
                            {
                                if ((iCnt4 == 0) && (sTemp == temp1->sVertexX))
                                {
                                    break;
                                }
                                else if ((iCnt4 == 1) && (sTemp == temp1->sVertexY))
                                {
                                    break;
                                }
                                else if ((iCnt4 == 2) && (sTemp == temp1->sVertexZ))
                                {
                                    break;
                                }
                            }

                            if (iCnt4 == 3)
                            {
                                temp1 = temp1->prev;
                            }
                            else
                            {
                                break;
                            }
                        }

                        if (iCnt2 == 1)
                        {
                            if (iCnt1 == 0)
                            {
                                iUnique++;
                                xyzVertexMap[start->sVertexX] = iUnique;
                                destFile << "v " << start->sVertexX[iCnt1] << " ";
                            }
                            else
                            {
                                destFile << start->sVertexX[iCnt1] << " ";
                            }
                        }
                    }
                    else if (iCnt3 == 2)
                    {
                        sTemp.clear();
                        temp1 = NULL;
                        sTemp = start->sVertexY;
                        temp1 = start->prev;

                        for (iCnt2 = iCnt; iCnt2 > 1; iCnt2--)
                        {
                            for (iCnt4 = 0; iCnt4 < 3; iCnt4++)
                            {
                                if ((iCnt4 == 0) && (sTemp == temp1->sVertexX))
                                {
                                    break;
                                }
                                else if ((iCnt4 == 1) && (sTemp == temp1->sVertexY))
                                {
                                    break;
                                }
                                else if ((iCnt4 == 2) && (sTemp == temp1->sVertexZ))
                                {
                                    break;
                                }
                            }

                            if (iCnt4 == 3)
                            {
                                temp1 = temp1->prev;
                            }
                            else
                            {
                                break;
                            }
                        }

                        if (iCnt2 == 1)
                        {
                            if (iCnt1 == 0)
                            {
                                iUnique++;
                                xyzVertexMap[start->sVertexY] = iUnique;
                                destFile << "v " << start->sVertexY[iCnt1] << " ";
                            }
                            else
                            {
                                destFile << start->sVertexY[iCnt1] << " ";
                            }
                        }
                    }
                    else if (iCnt3 == 3)
                    {
                        sTemp.clear();
                        temp1 = NULL;
                        sTemp = start->sVertexZ;
                        temp1 = start->prev;

                        for (iCnt2 = iCnt; iCnt2 > 1; iCnt2--)
                        {
                            for (iCnt4 = 0; iCnt4 < 3; iCnt4++)
                            {
                                if ((iCnt4 == 0) && (sTemp == temp1->sVertexX))
                                {
                                    break;
                                }
                                else if ((iCnt4 == 1) && (sTemp == temp1->sVertexY))
                                {
                                    break;
                                }
                                else if ((iCnt4 == 2) && (sTemp == temp1->sVertexZ))
                                {
                                    break;
                                }
                            }

                            if (iCnt4 == 3)
                            {
                                temp1 = temp1->prev;
                            }
                            else
                            {
                                break;
                            }
                        }

                        if (iCnt2 == 1)
                        {
                            if (iCnt1 == 0)
                            {
                                iUnique++;
                                xyzVertexMap[start->sVertexZ] = iUnique;
                                destFile << "v " << start->sVertexZ[iCnt1] << " ";
                            }
                            else
                            {
                                destFile << start->sVertexZ[iCnt1] << " ";
                            }
                        }
                    }
                }

                if ((iCnt1 == 2 && iCnt2 == 1) || (iCnt1 == 2 && iCnt == 1))
                {

                    destFile << "\n";
                }
            }
        }

        start = start->next;
        sTemp.clear();
        temp1 = NULL;
    }

    destFile << "# " << iUnique << " vertices\n\n";

    //--------------------writing  unique vertices (v) in file logic end--------------------//
}

///////////////////////////////////////////////////////////////////////////////
/*
Class Name     :  FILE_OP
Function Name  :  writeNormalVertices()
Input          :  -
Output         :  -
Description    :  used to write normal vertices in .obj file
Author         :  Aishwarya Sunil Karande
Date           :  22/08/2022
*/
///////////////////////////////////////////////////////////////////////////////

void FILE_OP::writeNormalVertices()

{
    /////////////////////////////////////////////////////////////////
    // local variables used in function

    // loop counter
    int iCnt = 0;
    int iCnt1 = 0;
    int iCnt2 = 0;

    // to count unique vertices
    char iUnique = '\0';

    // accessing DCLL to write nodes in obj file
    NODE *head = NULL;
    NODE *tail = NULL;
    int iNodeCnt = 0;
    // getting addresses into variables to acces linked list
    head = dobj->accessListStart();
    tail = dobj->accessListEnd();
    iNodeCnt = dobj->accessNodeCnt();

    // tmporary variable
    NODE *start = NULL;
    // NODE *end = NULL;
    NODE *temp1 = NULL;
    // NODE *temp2 = NULL;
    vector<string> sTemp;
    sTemp.clear();
    /////////////////////////////////////////////////////////////////

    // checking whether the Doubly Circular linked list is empty or not
    if ((head == NULL) && (tail == NULL))
    {
        cout << "Somthing went wrong....!!! Please check.Linked list is empty.Or contact developer\n";
        return;
    }

    /////////////////////////////////////////////////////////////////

    //---------------writing unique normal vertices (vn) in file logic start---------------//
    iUnique = '\0', iCnt = 0, iCnt1 = 0, iCnt2 = 0, sTemp.clear();
    temp1 = NULL;
    start = head;
    for (int iCnt = 1; iCnt <= iNodeCnt; iCnt++)
    {

        for (iCnt1 = 0; iCnt1 < (head->sNormalVertex.size()); iCnt1++)
        {

            if (iCnt == 1)
            {

                if (iCnt1 == 0)
                {
                    iUnique = '1';
                    normalVertexMap[start->sNormalVertex] = iUnique;
                    destFile << "vn " << start->sNormalVertex[iCnt1] << " ";
                }
                else
                {
                    destFile << start->sNormalVertex[iCnt1] << " ";
                }
            }
            else
            {
                sTemp = start->sNormalVertex;
                temp1 = start->prev;

                for (iCnt2 = iCnt; iCnt2 > 1; iCnt2--)
                {
                    if (sTemp == temp1->sNormalVertex)
                    {
                        break;
                    }
                    else
                    {

                        temp1 = temp1->prev;
                    }
                }

                if (iCnt2 == 1)
                {
                    if (iCnt1 == 0)
                    {
                        iUnique++;
                        normalVertexMap[start->sNormalVertex] = iUnique;
                        destFile << "vn " << start->sNormalVertex[iCnt1] << " ";
                    }
                    else
                    {
                        destFile << start->sNormalVertex[iCnt1] << " ";
                    }
                }
            }

            if ((iCnt1 == 2 && iCnt2 == 1) || (iCnt1 == 2 && iCnt == 1))
            {

                destFile << "\n";
            }
        }

        start = start->next;
        sTemp.clear();
        temp1 = NULL;
    }

    destFile << "# " << iUnique << " normal vertex\n\n";

    //---------------writing unique normal vertices (vn) in file logic end---------------//
}

///////////////////////////////////////////////////////////////////////////////
/*
Class Name     :  FILE_OP
Function Name  :  writeFaces()
Input          :  -
Output         :  -
Description    :  used to write faces combination in .obj file
Author         :  Aishwarya Sunil Karande
Date           :  22/08/2022
*/
///////////////////////////////////////////////////////////////////////////////

void FILE_OP::writeFaces()
{
    /////////////////////////////////////////////////////////////////
    // local variables used in function

    // loop counter
    int iCnt = 0;

    // to count unique vertices
    char cNormalVertexIndex = '\0';

    // accessing DCLL to write nodes in obj file
    NODE *head = NULL;
    NODE *tail = NULL;
    int iNodeCnt = 0;
    // getting addresses into variables to acces linked list
    head = dobj->accessListStart();
    tail = dobj->accessListEnd();
    iNodeCnt = dobj->accessNodeCnt();

    // tmporary variable
    NODE *start = NULL;

    /////////////////////////////////////////////////////////////////

    // checking whether the Doubly Circular linked list is empty or not
    if ((head == NULL) && (tail == NULL))
    {
        cout << "Somthing went wrong....!!! Please check.Linked list is empty.Or contact developer\n";
        return;
    }

    /////////////////////////////////////////////////////////////////

    //---------------writing unique normal vertices (vn) in file logic start---------------//
    iCnt = 0;
    start = head;

    for (int iCnt = 1; iCnt <= iNodeCnt; iCnt++)
    {

        auto findValue = normalVertexMap.find(start->sNormalVertex);
        cNormalVertexIndex = findValue->second;

        findValue = xyzVertexMap.find(start->sVertexX);
        destFile << "f " << findValue->second << "//" << cNormalVertexIndex << " ";

        findValue = xyzVertexMap.find(start->sVertexY);
        destFile << findValue->second << "//" << cNormalVertexIndex << " ";

        findValue = xyzVertexMap.find(start->sVertexZ);
        destFile << findValue->second << "//" << cNormalVertexIndex << " \n";

        cNormalVertexIndex = '\0';
        start = start->next;
    }

    destFile << "# " << iNodeCnt << " faces\n\n";

    start = NULL;
    head = NULL;
    tail = NULL;
}
