
///////////////////////////////////////////////////////////////////////////////
//
// This file contains definition of DATA class NODE class
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////

#include "Header.h" //User defined header file inclusion

///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/*
Class Name     :  NODE
Function Name  :  NODE()
Input          :  -
Output         :  -
Description    :  Constructor: used to initialise non static characteristics
                  of class
Author         :  Aishwarya Sunil Karande
Date           :  22/08/2022
*/
///////////////////////////////////////////////////////////////////////////////

NODE::NODE()
    {
        sNormalVertex.clear();
        sVertexX.clear();
        sVertexY.clear();
        sVertexZ.clear();
        prev = NULL;
        next = NULL;
    }

///////////////////////////////////////////////////////////////////////////////
/*
Class Name     :  NODE
Function Name  :  ~NODE()
Input          :  -
Output         :  -
Description    :  Destructor: used to deallocate memory
Author         :  Aishwarya Sunil Karande
Date           :  22/08/2022
*/
///////////////////////////////////////////////////////////////////////////////

    NODE::~NODE()
    {
        sNormalVertex.clear();
        sVertexX.clear();
        sVertexY.clear();
        sVertexZ.clear();
        prev = NULL;
        next = NULL;
    }

///////////////////////////////////////////////////////////////////////////////
/*
Class Name     :  DATA
Function Name  :  DATA()
Input          :  -
Output         :  -
Description    :  Constructor: used to initialise non static characteristics
                  of class
Author         :  Aishwarya Sunil Karande
Date           :  22/08/2022
*/
///////////////////////////////////////////////////////////////////////////////

DATA ::DATA()
{
    first = NULL;
    last = NULL;
    iNodeCnt = 0;
}

///////////////////////////////////////////////////////////////////////////////
/*
Class Name     :  DATA
Function Name  :  ~DATA()
Input          :  -
Output         :  -
Description    :  Destructor: used to deallocate memory
Author         :  Aishwarya Sunil Karande
Date           :  22/08/2022
*/
///////////////////////////////////////////////////////////////////////////////

DATA ::~DATA()
{
    first = NULL;
    last = NULL;
    iNodeCnt = 0;
}

///////////////////////////////////////////////////////////////////////////////
/*
Class Name     :  DATA
Function Name  :  insertLast()
Input          :  Vector of strings,Vector of strings,Vector of strings,Vector of strings
Output         :  -
Description    :  Used to insert data in doubly circular linked list
Author         :  Aishwarya Sunil Karande
Date           :  22/08/2022
*/
///////////////////////////////////////////////////////////////////////////////

void DATA ::insertLast(vector<string> v1, vector<string> v2, vector<string> v3, vector<string> v4)
{
    int iCnt = 0;

    NODE *newn = NULL;
    newn = new NODE();
    newn->sNormalVertex = v1;
    newn->sVertexX = v2;
    newn->sVertexY = v3;
    newn->sVertexZ = v4;
    newn->next = NULL;
    newn->prev = NULL;

    if ((first == NULL) && (last == NULL))
    {
        first = newn;
        last = newn;
    }
    else
    {
        newn->prev = last;
        last->next = newn;
        last = newn;
    }

    last->next = first;
    first->prev = last;
    iNodeCnt++;
}

///////////////////////////////////////////////////////////////////////////////
/*
Class Name     :  DATA
Function Name  :  displayNodes()
Input          :  -
Output         :  -
Description    :  Used to display all nodes in doubly circular linked list
Author         :  Aishwarya Sunil Karande
Date           :  22/08/2022
*/
///////////////////////////////////////////////////////////////////////////////

void DATA::displayNodes()
{
    if ((first == NULL) && (last == NULL))
    {
        cout << "Linked list is empty\n";
        return;
    }

    NODE *temp = NULL;
    temp = first;

    cout << "first<=>\n|";
    for (int iCnt = 1; iCnt <= iNodeCnt; iCnt++)
    {
        for (int iCnt1 = 0; iCnt1 < (temp->sNormalVertex.size()); iCnt1++)
        {
            cout << temp->sNormalVertex[iCnt1] << " ";
        }
        cout << "| |";
        for (int iCnt1 = 0; iCnt1 < (temp->sVertexX.size()); iCnt1++)
        {
            cout << temp->sVertexX[iCnt1] << " ";
        }
        cout << "| |";
        for (int iCnt1 = 0; iCnt1 < (temp->sVertexY.size()); iCnt1++)
        {
            cout << temp->sVertexY[iCnt1] << " ";
        }
        cout << "| |";
        for (int iCnt1 = 0; iCnt1 < (temp->sVertexZ.size()); iCnt1++)
        {
            cout << temp->sVertexZ[iCnt1] << " ";
        }

        cout << "|<=>\n|";

        temp = temp->next;
    }
    cout << "<=>last\n";
}

///////////////////////////////////////////////////////////////////////////////
/*
Class Name     :  DATA
Function Name  :  accessListStart()
Input          :  -
Output         :  Address of first node
Description    :  Used to send address of first node of doubly circular
                  linked list
Author         :  Aishwarya Sunil Karande
Date           :  22/08/2022
*/
///////////////////////////////////////////////////////////////////////////////

NODE *DATA::accessListStart()
{
    return first;
}

///////////////////////////////////////////////////////////////////////////////
/*
Class Name     :  DATA
Function Name  :  accessListEnd()
Input          :  -
Output         :  Address of last node
Description    :  Used to send address of last node of doubly circular
                  linked list
Author         :  Aishwarya Sunil Karande
Date           :  22/08/2022
*/
///////////////////////////////////////////////////////////////////////////////

NODE *DATA ::accessListEnd()
{
    return last;
}

///////////////////////////////////////////////////////////////////////////////
/*
Class Name     :  DATA
Function Name  :  accessNodeCnt()
Input          :  -
Output         :  Integer
Description    :  Used to return count of nodes present in doubly circular
                  linked list
Author         :  Aishwarya Sunil Karande
Date           :  22/08/2022
*/
///////////////////////////////////////////////////////////////////////////////

int DATA::accessNodeCnt()
{
    return iNodeCnt;
}
