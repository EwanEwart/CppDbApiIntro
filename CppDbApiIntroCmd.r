/*------------------------------------------------------------------------------+
|                                                                               |
| $Copyright: (c) 2020 Bentley Systems, Incorporated. All rights reserved. $    |
|                                                                               |
| Limited permission is hereby granted to reproduce and modify this             |
| copyrighted material provided that the resulting code is used only in         |
| conjunction with Bentley Systems products under the terms of the              |
| license agreement provided therein, and that this notice is retained          |
| in its entirety in any such reproduction or modification.                     |
|                                                                               |
+------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------+
|                                                                       |
|   $Logfile:   MstnExamples/CppDbApiIntro/CppDbApiIntrocmd.r_v  $
|   $Workfile:   CppDbApiIntrocmd.r  $
|   $Revision: 1.1 $
|   $Date: 2020/02/10 14:20:05 $
|                                                                       |
+----------------------------------------------------------------------*/

#include        <Mstn/MdlApi/rscdefs.r.h>
#include        <Mstn/MdlApi/cmdclass.r.h>
#include        <Mstn/MdlApi/dlogids.r.h>

/*-----------------------------------------------------------------------
 Setup for native code only MDL app
-----------------------------------------------------------------------*/
#define  DLLAPP_PRIMARY     1

DllMdlApp   DLLAPP_PRIMARY =
    {
    L"CppDbApiIntro", L"CppDbApiIntro"
    }

#define CT_NONE                         0
#define CT_CppDbApiIntroCOMMAND              1
#define CT_SUBCOMMANDS                  2

CommandTable CT_CppDbApiIntroCOMMAND =
{
    {  1, CT_SUBCOMMANDS,           DATABASE,       TRY | DEF,  "CppDbApiIntro" },
}
CommandTable CT_SUBCOMMANDS =
{
    {  1, CT_NONE,        DATABASE,       TRY | DEF,  "CONNECTDB" },
    {  2, CT_NONE,        DATABASE,       NONE,       "CREATETABLEMSCATALOG" },
    {  3, CT_NONE,        DATABASE,       NONE,       "CREATETABLEELEMENTS" },
    {  4, CT_NONE,        DATABASE,       NONE,       "ATTACHCHECKLINKAGE" },
    {  5, CT_NONE,        DATABASE,       NONE,       "DISCONNECT" }
};
