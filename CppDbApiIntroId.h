/*--------------------------------------------------------------------------------------+
|
|     $Source: MstnExamples/Databases/CppDbApiIntro/CppDbApiIntroid.h $
|
|  $Copyright: (c) 2020 Bentley Systems, Incorporated. All rights reserved. $
|
+--------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------+
|                                                                       |
| Copyright 1993-2020, Bentley Systems, Incorporated,                   |
| All rights reserved.                                                  |
|                                                                       |
|                                                                       |
| Limited permission is hereby granted to reproduce and modify this     |
| copyrighted material provided that the resulting code is used only in |
| conjunction with Bentley Systems products under the terms of the      |
| license agreement provided therein, and that this notice is retained  |
| in its entirety in any such reproduction or modification.             |
|                                                                       |
+----------------------------------------------------------------------*/
/*----------------------------------------------------------------------+
|                                                                       |
|    $Logfile:   MstnExamples/CppDbApiIntro/CppDbApiIntroid.h_v  $
|   $Workfile:   CppDbApiIntroid.h  $
|   $Revision: 1.1 $
|       $Date: 2020/02/10 14:32:12 $
|                                                                       |
+----------------------------------------------------------------------*/
/*----------------------------------------------------------------------+
|                                                                       |
|   Function -                                                          |
|                                                                       |
|   Dialog Box IDs                                                      |
|                                                                       |
+----------------------------------------------------------------------*/
#if !defined (__CppDbApiIntroidH__)
#define	__CppDbApiIntroidH__

#define DIALOGID_Locate             (1)

/*----------------------------------------------------------------------+
|                                                                       |
|   Base IDs for Related Groups                                         |
|                                                                       |
+----------------------------------------------------------------------*/
#define BASEID_Locate               (DIALOGID_Locate * 100)

/*----------------------------------------------------------------------+
|                                                                       |
|   Message List Id                                                     |
|                                                                       |
+----------------------------------------------------------------------*/
#define	MESSAGELISTID_CPP_DB_API_INTRO_MESSAGES   (BASEID_Locate - 1)

/*----------------------------------------------------------------------+
|                                                                       |
|   Message List ID's                                                   |
|                                                                       |
+----------------------------------------------------------------------*/
enum MsgId
    {
    MSG_commandsLoaded,
    MSG_databaseIsNotActive,
    MSG_failedCreatingTableMSCATALOG,
    MSG_succeededCreatingTableMSCATALOG,
    MSG_tableMSCATALOGIsExist,
    MSG_failedCreatingTableELEMENTS,
    MSG_succeededCreatingTableELEMENTS,
    MSG_failedCreatingLineElement,
    MSG_failedAppendingLinkage,
    MSG_succeededCheckingLinkage,
    MSG_FailedCheckingLinkage,
    MSG_failedInsertingRowIntoTableELEMENTS,
    MSG_failedInsertingRowIntoMSCATALOG,
    MSG_failedReloadingDB,
    MSG_failedCloseCursorByID,
    };

#endif /* if !defined (__gisidH__) */
