/*--------------------------------------------------------------------------------------+
|
|     $Source: MstnExamples/Databases/CppDbApiIntro/transkit/CppDbApiIntromsgs.r $
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
|   $Source: MstnExamples/Databases/CppDbApiIntro/transkit/CppDbApiIntromsgs.r $
|   $Workfile:   CppDbApiIntromsgs.r  $
|   $Revision: 1.1 $
|       $Date: 2020/02/10 13:40:54 $
|                                                                       |
+----------------------------------------------------------------------*/
/*----------------------------------------------------------------------+
|                                                                       |
|   Function -                                                          |
|                                                                       |
|   CppDbApiIntro Example application message resources                      |
|                                                                       |
+----------------------------------------------------------------------*/
#include <Mstn/MdlApi/rscdefs.r.h>
#include <Mstn/MdlApi/cmdclass.r.h>

#include    "../CppDbApiIntroId.h"

MessageList MESSAGELISTID_CPP_DB_API_INTRO_MESSAGES =
    {
      {
      { MSG_commandsLoaded,                     "CppDbApiIntro commands loaded" },
      { MSG_databaseIsNotActive,                "Database is not active." },
      { MSG_failedCreatingTableMSCATALOG,       "Failed creating table MSCATALOG. Please verify." },
      { MSG_succeededCreatingTableMSCATALOG,    "Succeeded creating table MSCATALOG." },
      { MSG_tableMSCATALOGIsExist,              "Table MSCATALOG exists." },
      { MSG_failedCreatingTableELEMENTS,		    "Failed creating table ELEMENTS. Please verify." },
      { MSG_succeededCreatingTableELEMENTS,		  "Succeeded creating table ELEMENTS." },
      { MSG_failedCreatingLineElement,          "Failed creating a line element." },
      { MSG_failedAppendingLinkage,				      "Failed appending linkage." },
      { MSG_succeededCheckingLinkage,			      "Succeeded checking linkage." },
      { MSG_FailedCheckingLinkage,				      "Failed checking linkage." },
      { MSG_failedInsertingRowIntoTableELEMENTS,"Failed inserting row into table ELEMENTS." },
      { MSG_failedInsertingRowIntoMSCATALOG,	  "Failed inserting a row into MSCATALOG to record the table ELEMENTS." },
      { MSG_failedReloadingDB,                  "Failed reloading DB"},
      { MSG_failedCloseCursorByID,              "Failed to close cursor by ID"},
      }
    };
