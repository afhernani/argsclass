
#include <stdio.h>
#include <iostream>
#include <string>
#include <windows.h>
#include "cmdlineparam.h"

using namespace std;

int CreateParameterFromString(char *pszParams, char *argv[], int max);

cmdlineparam::cmdlineparam(const char *switchchars /*= "-/"*/)
 : szSwitchChars(switchchars)  
{
    maxparms = 100;
    pszCmdLineDup = _strdup(GetCommandLine());
    paramcount = CreateParameterFromString(pszCmdLineDup,parms,maxparms);
}

cmdlineparam::~cmdlineparam()
{
    if (pszCmdLineDup) {
      free(pszCmdLineDup);
      pszCmdLineDup = NULL;
    }
}
//

bool cmdlineparam::IsSwitch(const char *sz)
{
    return (strchr(szSwitchChars,sz[0]) != NULL);
}

bool cmdlineparam::CheckHelp( bool bNoSwitches /*= false*/)
{
    if (bNoSwitches && (paramcount < 2)) return true;
     if (paramcount < 2) return false;
     if (strcmp(ParamStr(1),"-?") == 0) return true;
     if (strcmp(ParamStr(1),"/?") == 0) return true;
     if (strcmp(ParamStr(1),"?") == 0) return  true;
     return false;
}

string cmdlineparam::ParamLine()
{
    string s;
    char *p = strchr(GetCommandLine(),' ');
    if (p) {
        s =p+1;
    }
    return s;
}

string cmdlineparam::CommandLine(){
   string s;
    s =GetCommandLine();
    return s;
}
const char* cmdlineparam::ParamStr(int index, bool bGetAll /*= false*/){
    if ((index < 0) || (index >= paramcount)) {
        return "";
    }
    string s = parms[index];
    if (bGetAll) {
        for (int i = index+1;i < paramcount; i++) {
              s += " ";
              s += parms[i];
        }
    }
    return s.c_str();
}
int cmdlineparam::ParamInt(int index){
    return atoi(ParamStr(index));
}
int cmdlineparam::FirstNonSwitchIndex(){
    for (int i = 1;i < paramcount; i++) {
        if (!IsSwitch(parms[i])) {
            return i;
        }
    }
    return 0;
}
string cmdlineparam::FirstNonSwitchStr(){
    // returns the first non-switch, handles lines such as:
    // [options] file [specs]
    return GetNonSwitchStr(false,true);
}
 int cmdlineparam::SwitchCount(){
     int count = 0;
    for (int i = 1;i < paramcount; i++) {
        if (IsSwitch(parms[i])) count++;
    }
    return count;
 }
 int cmdlineparam::Switch( const char *sz,  bool bCase /*= false*/){
     if (!sz || !sz[0]) {
        return 0;
    }

    char sz2[255];
    strncpy(sz2,sz,sizeof(sz2)-1);
    sz2[sizeof(sz2)-1] = 0;

    char *p = sz2;
    if (strchr(szSwitchChars,*p) != NULL) p++;

    // check for abbrevation

    int amt = 0;
    char *abbr = strchr(p,'*');
    if (abbr) {
        *abbr = 0;
        amt = strlen(p);
        strcpy(abbr,abbr+1);
    }

    for (int i = 1;i < paramcount; i++) {
      if (!IsSwitch(parms[i])) continue;
      char *pColon = strchr(&parms[i][1],':');
      if (pColon && (amt == 0)) { amt = strlen(p); }

      if (bCase) {
        if (amt > 0) {
          if (strncmp(p,&parms[i][1],strlen(p)) != 0) continue; // 450.6b20
          if (strncmp(p,&parms[i][1],amt) == 0) return i;
        } else {
          if (strcmp(p,&parms[i][1]) == 0) return i;
        }
      } else {
        if (amt > 0) {
          if (_strnicmp(p,&parms[i][1],strlen(p)) != 0) continue; // 450.6b20
          if (_strnicmp(p,&parms[i][1],amt) == 0) return i;
        } else {
          if (_stricmp(p,&parms[i][1]) == 0) return i;
        }
      }
    }
    return 0;
 }
 const char* cmdlineparam::GetSwitchStr(const char *sz, const char *szDefault /*= ""*/,  bool bCase /*= false*/){
    int idx = Switch( sz, bCase);
    if (idx > 0) {
        string s = ParamStr(idx);
        int n = s.find( ':');
        if (n > -1) {
            return  &s[n+1];
        } else {
          if ((idx+1) < paramcount) {
              if (!IsSwitch(parms[idx+1])) {
                  return parms[idx+1];
              }
          }
        }
        //return szDefault;
    }
    return szDefault;
 }
  int cmdlineparam::GetSwitchInt( const char *sz,  int iDefault /*= -1*/,  bool bCase /*= false*/){
        char szDefault[25];
        sprintf(szDefault,"%d",iDefault);
        return atoi(GetSwitchStr(sz, szDefault, bCase));
  }
  const char* cmdlineparam::GetNonSwitchStr( bool bBreakAtSwitch /*= true*/,  bool bFirstOnly /*= false*/){
      string sLine = "";
    int i = 1;
    while (i < paramcount) {
        if (IsSwitch(parms[i])) {
            if (bBreakAtSwitch) break;
        } else {
            sLine += parms[i];
            if (bFirstOnly) break;
            sLine += " ";
        }
        i++;
    }
    //sLine.TrimRight();
    return sLine.c_str();
  }

int CreateParameterFromString(char *pszParams, char *argv[], int max)
{
    int argc = 0;
    if (pszParams) {
        char *p = pszParams;
        while (*p && (argc < max)) {
            while (*p == ' ') {
                p++;
            }
            if (!*p) {
                break;
            }
            if (*p == '"') {
                p++;
                argv[argc++] = p;
                while (*p && *p != '"') {
                    p++;
                }
            } else {
                argv[argc++] = p;
                while (*p && *p != ' ') {
                    p++;
                }
            }
            if (*p) {
                *p++ = 0;
            }
        }
    }
    return argc;
}