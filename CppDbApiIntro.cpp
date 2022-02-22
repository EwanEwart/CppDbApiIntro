/*--------------------------------------------------------------------------------------+
|
|     $Source: MstnExamples/Databases/CppDbApiIntro/CppDbApiIntro.cpp $
|
|  $Copyright: (c) 2020 Bentley Systems, Incorporated. All rights reserved. $
|
+--------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------+
|                                                                       |
|   $Workfile:   CppDbApiIntro.cpp  $                                      |
|   $Revision: 1.1 $                                                    |
|       $Date: 2020/02/10 14:20:05 $                                    |
|                                                                       |
+----------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------+
|                                                                                                   |
|   Function -                                                                                      |
|                                                                                                   |
|   Example MDL program to show database interface                                                  |
|                                                                                                   |
|   - - - - - - - - - - - - - - - - - - - - - - - - - - - - -                                       |
|                                                                                                   |
|   Public Routine Summary -                                                                        |
|                                                                                                   |
|   main - main entry point                                                                         |
|                                                                                                   |
|   Commands:                                                                                       |
|   CppDbApiIntro_connectToDb - Connect to an oracle database                                          |
|   CppDbApiIntro_createTableMSCATALOG - Create table MSCATALOG                                        |
|   CppDbApiIntro_createTableELEMENTS - Create table ELEMENTS                                          |
|   CppDbApiIntro_attachAndCheckLinkage - Attach and check the created linkage                         |
|   CppDbApiIntro_disconnect - Disconnect the database                                                 |
|                                                                                                   |
|   Local Functions:                                                                                |
|   CppDbApiIntro_setupGlobalData - Set up global data                                                 |
|   CppDbApiIntro_MessageCenter - Show messages                                                        |
|   CppDbApiIntro_appendLinkage - Append a linkage to an element                                       |
|   CppDbApiIntro_checkLinkage - Check the linkage on an element                                       |
|                                                                                                   |
+--------------------------------------------------------------------------------------------------*/
#include <cassert>

#undef __EDG__ // EE++ Bentley

#include <Mstn/MdlApi/MdlApi.h>
#include <Mstn/MdlApi/rdbmslib.fdf>
#include <Mstn/MdlApi/dbdefs.h>
#include <Mstn/ISessionMgr.h>
#include <DgnPlatform/DgnModel.h>
#include <DgnPlatform/ElementHandle.h>
#include <DgnPlatform/LinearHandlers.h>
#include "CppDbApiIntroId.h"  /* resource IDs */
#include "CppDbApiIntroCmd.h" /* generated by resource compiler */

USING_NAMESPACE_BENTLEY
USING_NAMESPACE_BENTLEY_DGNPLATFORM
USING_NAMESPACE_BENTLEY_MSTNPLATFORM
USING_NAMESPACE_BENTLEY_MSTNPLATFORM_ELEMENT

/*----------------------------------------------------------------------+
|                                                                       |
|   Public Global variables                                             |
|                                                                       |
+----------------------------------------------------------------------*/
WChar g_mscatalogName[MAXFILELENGTH];
UShort g_entityNum(1);

/*----------------------------------------------------------------------+
|                                                                       |
|   Local Functions Section                                             |
|                                                                       |
+----------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------**/ /**
 * @bsimethod                                                              Bentley Systems
 +---------------+---------------+---------------+---------------+---------------+------*/
static void CppDbApiIntro_setupGlobalData(void)
{
    /*
    Copy the mscatalog table name.
    Use the value in env var if it exists,
    otherwise use the default to "mscatalog".
    */
    mdlDB_getMscatalogName(g_mscatalogName);
}

/*---------------------------------------------------------------------------------**/ /**
 * @bsimethod                                                              Bentley Systems
 +---------------+---------------+---------------+---------------+---------------+------*/
static void CppDbApiIntro_MessageCentre(
    DgnPlatform::OutputMessagePriority messagePriority,
    MsgId msgId,
    DgnPlatform::OutputMessageAlert openAlertBox)
{
    WString BriefMessage;
    mdlResource_loadWString(BriefMessage, NULL, MESSAGELISTID_CPP_DB_API_INTRO_MESSAGES, msgId);
    mdlOutput_messageCenter(messagePriority, BriefMessage.GetWCharCP(), NULL, openAlertBox);
}

/*---------------------------------------------------------------------------------**/ /**
 * @bsimethod                                                              Bentley Systems
 +---------------+---------------+---------------+---------------+---------------+------*/
static int CppDbApiIntro_appendLinkage(
    EditElementHandle &eeh,
    UInt32 mslink,
    WCharCP tableNameP)
{
    short attributes[MAX_ATTRIBSIZE];
    int status{BentleyStatus::SUCCESS};
    int length{0};
    LinkProps props;

    memset(&props, 0, sizeof(props));

    // status = mdlDB_buildLink(attributes, &length, ORACLE_LINKAGE, &props, tableNameP, mslink, 0);
    if (BentleyStatus::SUCCESS == (status = mdlDB_buildLink(/*out*/ attributes, /*out*/ &length, ODBC_LINKAGE, &props, tableNameP, mslink, 0)))
    {
        MSElementP el = eeh.GetElementP();
        ElementRefP elemRef = eeh.GetElementRef();

        MSElementP elBuffer{nullptr};
        elBuffer = static_cast<MSElementP>(_alloca(sizeof(MSElement)));
        el->CopyTo(*elBuffer); // MSElement > elBuffer

        if (SUCCESS != (status = mdlElement_appendAttributes(elBuffer, length, attributes))) // elBuffer << attributes
        {
            return status;
        }

        eeh.ReplaceElement(elBuffer);
        status = eeh.ReplaceInModel(elemRef);

        // if (elBuffer != nullptr)
        // {
        //     delete elBuffer; elBuffer = nullptr;
        // }
    }

    return (status);
}

/*---------------------------------------------------------------------------------**/ /**
 * @bsimethod                                                              Bentley Systems
 +---------------+---------------+---------------+---------------+---------------+------*/
static void CppDbApiIntro_checkLinkage(EditElementHandle &eeh)
{
    MSElementP elmP = eeh.GetElementP();

    /* check if this attribute linkage belongs to us */
    if (mdlDB_elementFilter(elmP))
    {
        DatabaseLink *link{nullptr};
        int linkCount{0};
        int status{0};

        if (Bentley::SUCCESS == (status = mdlDB_extractLinkages(&link, &linkCount, elmP)))
        {
            BeAssert(linkCount == 1);
            WChar sqlStatement[256];
            swprintf(sqlStatement, L"SELECT name FROM elements WHERE mslink = %d", link[0].mslink);

            CursorID cursorID{0};
            if (BentleyStatus::SUCCESS == mdlDB_openCursorWithID(&cursorID, sqlStatement))
            {
                bool found{false};
                MS_sqlda tableSQLDA;
                int statusFetch{QUERY_NOT_FINISHED};
                while (statusFetch == QUERY_NOT_FINISHED)
                {
                    statusFetch = mdlDB_fetchRowByID(&tableSQLDA, cursorID);
                    if (statusFetch == QUERY_NOT_FINISHED)
                    {
                        /* step through every column returned from the query */
                        for (int i = 0; i < tableSQLDA.numColumns; i++)
                        {
                            std::wstring column{tableSQLDA.name[i]};
                            std::wstring value{tableSQLDA.value[i]};

                            if (wcsicmp(column.c_str(), L"name") == 0)
                            {
                                if (wcscmp(value.c_str(), L"line") == 0)
                                {
                                    found = true;
                                    break;
                                }
                            }
                        }
                        if (found)
                        {
                            break;
                        }
                    }
                }

                BeAssert(Bentley::SUCCESS == mdlDB_closeCursorByID(cursorID));
                mdlDB_freeSQLDADescriptor(&tableSQLDA);

                if (!found)
                {
                    CppDbApiIntro_MessageCentre(OutputMessagePriority::Warning, MSG_FailedCheckingLinkage, OutputMessageAlert::Dialog);
                    return;
                }

                CppDbApiIntro_MessageCentre(OutputMessagePriority::Warning, MSG_succeededCheckingLinkage, OutputMessageAlert::Dialog);
            }
        }
    }
}

/*----------------------------------------------------------------------+
|                                                                       |
|   Command Functions Section                                           |
|                                                                       |
+----------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------**/ /**
 * @bsimethod                                                              Bentley Systems
 +---------------+---------------+---------------+---------------+---------------+------*/
static void CppDbApiIntro_cmd_disconnect(WCharCP)
{
    mdlDB_activeDatabase(L" ");

    /* Unload the Visual SQL Query Builder and Builder apps */
    mdlSystem_unloadMdlProgram(L"VSQL");
    mdlSystem_unloadMdlProgram(L"VSQLGEO");
}

/*---------------------------------------------------------------------------------**/ /**
 * @bsimethod                                                              Bentley Systems
 +---------------+---------------+---------------+---------------+---------------+------*/
static void CppDbApiIntro_cmd_connectToDb(WCharCP loginString)
{
    CppDbApiIntro_cmd_disconnect(nullptr);
    mdlDB_changeDatabase(DATABASESERVERID_ODBC, loginString); // This line also create table "MSFORMS"
    // mdlDB_changeDatabase(DATABASESERVERID_Oracle, loginString); // This line also create table "MSFORMS"
}

/*---------------------------------------------------------------------------------**/ /**
 * @bsimethod                                                              Bentley Systems
 +---------------+---------------+---------------+---------------+---------------+------*/
static void CppDbApiIntro_cmd_createTableMSCATALOG(WCharCP)
{
    if (!mdlDB_isActive())
    {
        CppDbApiIntro_MessageCentre(OutputMessagePriority::Warning, MSG_databaseIsNotActive, OutputMessageAlert::Dialog);
        return;
    }

    WChar sqlStatement[256];
    CursorID cursorID;

    // Judge if table "mscatalog" is exist
    swprintf(sqlStatement, L"select * from %ls", g_mscatalogName);
    if (SUCCESS == mdlDB_openCursorWithID(&cursorID, sqlStatement))
    {
        mdlDB_closeCursorByID(cursorID);
        CppDbApiIntro_MessageCentre(OutputMessagePriority::Info, MSG_tableMSCATALOGIsExist, OutputMessageAlert::Dialog);
        return;
    }

    swprintf(sqlStatement, L"create table %ls (tablename char(32), entitynum integer, screenform char(64), reporttable char(64), sqlreview char(240), fencefilter char(240), dastable char(32), formtable char(64))", g_mscatalogName);
    if (SUCCESS != mdlDB_processSQL(sqlStatement))
    {
        CppDbApiIntro_MessageCentre(OutputMessagePriority::Warning, MSG_failedCreatingTableMSCATALOG, OutputMessageAlert::Dialog);
        return;
    }
    else
    {
        CppDbApiIntro_MessageCentre(OutputMessagePriority::Info, MSG_succeededCreatingTableMSCATALOG, OutputMessageAlert::None);
    }
}

/*---------------------------------------------------------------------------------**/ /**
 * @bsimethod                                                              Bentley Systems
 +---------------+---------------+---------------+---------------+---------------+------*/
static void CppDbApiIntro_cmd_createTableELEMENTS()
{
    WChar sqlStatement[256];
    CursorID cursorID{0};

    /*
    Check if table "elements" exists.
    If it exists, clear its rows.
    */
    swprintf(sqlStatement, L"SELECT * FROM %ls", L"elements");
    if (BentleyStatus::SUCCESS == mdlDB_openCursorWithID(&cursorID, sqlStatement))
    {
        assert(Bentley::SUCCESS == mdlDB_closeCursorByID(cursorID) && L"mdlDB_closeCursorByID failed");
        // swprintf(sqlStatement, L"TRANCATE TABLE elements"); // Oracle
        swprintf(sqlStatement, L"DELETE * FROM elements"); // ACCESS
        (void)mdlDB_processSQL(sqlStatement);
    }
    else
    {
        swprintf(sqlStatement, L"CREATE table elements (mslink integer, name char(64))");
        // swprintf(sqlStatement, L"create table elements (mslink NUMBER(10,4), name char(64))");
        if (BentleyStatus::SUCCESS != mdlDB_processSQL(sqlStatement))
        {
            CppDbApiIntro_MessageCentre(OutputMessagePriority::Warning, MSG_failedCreatingTableELEMENTS, OutputMessageAlert::Dialog);
            mdlDB_closeCursorByID(cursorID);
            CppDbApiIntro_MessageCentre(OutputMessagePriority::Info, MSG_succeededCreatingTableELEMENTS, OutputMessageAlert::Dialog);
            return;
        }
        // EE++
        else
        {
            // Insert a row into MSCATALOG to record the table ELEMENTS
            swprintf(sqlStatement, L"INSERT INTO %ls (tablename, entitynum) VALUES('elements', %hu)", g_mscatalogName, g_entityNum++);
            if (BentleyStatus::SUCCESS != mdlDB_processSQL(sqlStatement))
            {
                CppDbApiIntro_MessageCentre(OutputMessagePriority::Warning, MSG_failedInsertingRowIntoMSCATALOG, OutputMessageAlert::Dialog);
                mdlDB_closeCursorByID(cursorID);
                return;
            }
        }
    }

    // EE--
    // // Check if "elements" is in table "MSCATALOG"
    // swprintf(sqlStatement, L"SELECT * FROM %ls WHERE tablename = '%hs'", L"mscatalog", "elements");
    // if (BentleyStatus::SUCCESS != mdlDB_openCursorWithID(&cursorID, sqlStatement))
    // {
    //     // Insert a row into MSCATALOG to record the table ELEMENTS
    //     swprintf(sqlStatement, L"INSERT INTO %ls (tablename, entitynum) VALUES('elements', %hu)", g_mscatalogName, g_entityNum++);
    //     if (BentleyStatus::SUCCESS != mdlDB_processSQL(sqlStatement))
    //     {
    //         CppDbApiIntro_MessageCentre(OutputMessagePriority::Warning, MSG_failedInsertingRowIntoMSCATALOG, OutputMessageAlert::Dialog);
    //         mdlDB_closeCursorByID(cursorID);
    //         return;
    //     }
    // }

    // EE--
    // CppDbApiIntro_MessageCentre(OutputMessagePriority::Info, MSG_succeededCreatingTableELEMENTS, OutputMessageAlert::Dialog);
    // if (BentleyStatus::SUCCESS != mdlDB_closeCursorByID(cursorID))
    // {
    //     CppDbApiIntro_MessageCentre(OutputMessagePriority::Warning, MSG_failedReloadingDB, OutputMessageAlert::Dialog);
    // }

    // // Need to reload the db, if the table is newly created.
    // if (BentleyStatus::SUCCESS != mdlDB_processSQL(L"reload"))
    // {
    //     CppDbApiIntro_MessageCentre(OutputMessagePriority::Warning, MSG_failedReloadingDB, OutputMessageAlert::Dialog);
    // }
}

/*---------------------------------------------------------------------------------**/ /**
 * @bsimethod                                                              Bentley Systems
 +---------------+---------------+---------------+---------------+---------------+------*/
static void CppDbApiIntro_cmd_attachAndCheckLinkage()
{
    WChar sqlStatement[256];

    // Create a line
    bool is3d = ACTIVEMODEL->Is3d();

    DSegment3d segment;
    segment.Init(0.0, 0.0, 0.0, 100.0, 100.0, 100.0);
    EditElementHandle eeh;
    BentleyStatus status{BentleyStatus::SUCCESS};

    if (BentleyStatus::SUCCESS != (status = LineHandler::CreateLineElement(eeh, nullptr, segment, is3d, *ACTIVEMODEL)))
    {
        CppDbApiIntro_MessageCentre(OutputMessagePriority::Warning, MSG_failedCreatingLineElement, OutputMessageAlert::Dialog);
    }
    StatusInt addStatus = eeh.AddToModel();
    if (BentleyStatus::SUCCESS != addStatus)
    {
        CppDbApiIntro_MessageCentre(OutputMessagePriority::Warning, MSG_failedCreatingLineElement, OutputMessageAlert::Dialog);
    }
    // Insert a row into table elements
    UInt32 mslink{0};
    mdlDB_largestMslink(&mslink, L"elements");
    mslink++;
    swprintf(sqlStatement, L"INSERT INTO %ls (mslink, name) VALUES(%hu, '%ls')", L"elements", mslink, L"line");
    if (Bentley::SUCCESS != mdlDB_processSQL(sqlStatement))
    {
        CppDbApiIntro_MessageCentre(OutputMessagePriority::Warning, MSG_failedInsertingRowIntoTableELEMENTS, OutputMessageAlert::Dialog);
        return;
    }

    // Attach a linkage to ??? DB row ???
    if (BentleyStatus::SUCCESS != CppDbApiIntro_appendLinkage(eeh, mslink, L"elements"))
    {
        CppDbApiIntro_MessageCentre(OutputMessagePriority::Warning, MSG_failedAppendingLinkage, OutputMessageAlert::Dialog);
        return;
    }

    // Check the linkage again
    CppDbApiIntro_checkLinkage(eeh);
}

Public MdlCommandNumber commandNumbers[] =
    {
        {(CmdHandler)CppDbApiIntro_cmd_connectToDb, CMD_CppDbApiIntro_CONNECTDB},
        {(CmdHandler)CppDbApiIntro_cmd_createTableMSCATALOG, CMD_CppDbApiIntro_CREATETABLEMSCATALOG},
        {(CmdHandler)CppDbApiIntro_cmd_createTableELEMENTS, CMD_CppDbApiIntro_CREATETABLEELEMENTS},
        {(CmdHandler)CppDbApiIntro_cmd_attachAndCheckLinkage, CMD_CppDbApiIntro_ATTACHCHECKLINKAGE},
        {(CmdHandler)CppDbApiIntro_cmd_disconnect, CMD_CppDbApiIntro_DISCONNECT},
        0 /* The table must be NULL-terminated */
};

/*---------------------------------------------------------------------------------**/ /**
 * @bsimethod                                                              Bentley Systems
 +---------------+---------------+---------------+---------------+---------------+------*/
extern "C" DLLEXPORT void MdlMain(int argc, WCharCP argv[])
{
    mdlSystem_registerCommandNumbers(commandNumbers);

    /* setup global variables */
    CppDbApiIntro_setupGlobalData();

    /* open our application file for access to our dialogs */
    RscFileHandle rfHandle;
    mdlResource_openFile(&rfHandle, NULL, RSC_READ);

    if (mdlParse_loadCommandTable(NULL) != NULL)
    {
        mdlOutput_rscPrintf(MSG_MESSAGE, NULL, MESSAGELISTID_CPP_DB_API_INTRO_MESSAGES, MSG_commandsLoaded);
    }
}