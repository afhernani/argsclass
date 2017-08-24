#ifndef CMDLINEPARAM_H
#define CMDLINEPARAM_H

#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;

class cmdlineparam
{
private:
    bool IsSwitch(const char *sz);
    const char *szSwitchChars;
    char *parms[100];
    char *pszCmdLineDup;
    int maxparms;
    int paramcount;
    
public:
    cmdlineparam( const char *switchchars = "-");
    ~cmdlineparam();
    //
    bool CheckHelp(bool bNoSwitches = false);

    int ParamCount() { return paramcount; }
    string ParamLine();
    string CommandLine();
    const char* ParamStr(int index, bool bGetAll = false);
    int ParamInt(int index);

    int FirstNonSwitchIndex();
    string FirstNonSwitchStr();
    int SwitchCount();
    int Switch(const char *sz, bool bCase = false);
    const char*  GetSwitchStr( const char *sz, const char *szDefault = "", bool bCase = false);
    int GetSwitchInt(const char *sz,  int iDefault = -1,  bool bCase = false);
    const char* GetNonSwitchStr( bool bBreakAtSwitch = true,  bool bFirstOnly = false);

};

#endif // CMDLINEPARAM_H
