# ORACEL DEMO => CppDbApiIntro

- In order to build CppDbApiIntro(Connect to an existing oracle database),
- Visual Studio 2013 is required and
- the MicroStation developer batch file must also have been set.

It is recommended to first run
the Visual Studio 2013 command prompt
"VS2013 x64 Cross Tools command prompt"
and then run the MicroStation SDK command
MicroStationDeveloperShell.bat.

Make sure that the environment variables for MS and MSDE are set correctly

The MicroStationDeveloperShell.bat should do this.

## A. The CppDbApiIntro does such things below:

1.	Connect to a (an ORACLE) database:
	cppdbapiintro connectdb CppDbApiIntro

2.	Create MSCATALOG table:
	cppdbapiintro createtablemscatalog

3.	Create table "ELEMENTS" with _MSLINK_ and _NAME_ properties:
	cppdbapiintro createtableelements

4.	Create a line element and attach a linkage to this line;
	a.	Create a line element in the active model;
	b.	Add a linkage to the line element associating it with the entry in the database.
	c.	Check the linkage on the line element and get the data from the database.
5.	Disconnect the database.


B. Corresponding Keyins:
1. CppDbApiIntro CONNECTDB [Login string]
2. CppDbApiIntro CREATETABLEMSCATALOG
2. CppDbApiIntro CREATETABLEELEMENTS
3. CppDbApiIntro ATTACHCHECKLINKAGE
3. CppDbApiIntro DISCONNECT
