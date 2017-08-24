#include <stdio.h>
#include <iostream>
#include <string>

#include "cmdlineparam.h"

using namespace std;

void usage()
{
  cout << "usage: <p1> [-p2 <v2>] [[/p3 [v3]] [/p4]]" << endl;
}

int main(int argc, char **argv)
{
	cout <<"Hola Argumentos" << endl;
    for (int i=0;i<argc;i++)
        cout << "Arg. " << i << " : "<< argv[i] << endl;
    //transformamos el primer argumento en una cadena.
    string tmp_str = argv[0]; //tambien con  string tmp_str(argv[0];
    string tmp_str2(argv[1]);
    //<FONT color = #0000ff> // check for ? or if no parameters are passed
    //</FONT>
    cout << tmp_str << " : esto es una cadena extraida del primer argumento.\n" 
    << "su longitud es de: " << tmp_str.length()  <<" : caracteres"<< endl;
    //
    cout << tmp_str2 << " : esto es una cadena extraida del primer argumento.\n" 
    << "su longitud es de: " << tmp_str2.length()  <<" : caracteres"<< endl;
    // trabajar con los argumentos.
    cout << "Working with cmdlineparam.lib" << endl;
    cmdlineparam clp;
    //vamos a ver los parametros
    cout << "----------------------" << endl;
    cout << "checked the params" << endl;
    cout << "----------------------" << endl;
        if (clp.CheckHelp(true)) {
          usage();
          return 0;
        }
   //---------------------------------------------------------
  // Syntax checking for p1.
  // First parameter must be a non-switch
  //---------------------------------------------------------
  cout << "-----------------------" << endl;
  cout << "sintax checking for p1 " << endl;
  cout << "First parameter must be a non-switch "<<endl;
  cout << "--------------------------------------------" << endl;
      string p1;
     if (clp.FirstNonSwitchIndex() != 1) {
          cout << "! syntax error: p1 required" << endl;
          usage();
          return 0;
    }else{
        p1 = clp.FirstNonSwitchStr();
        cout << "first parametro -p1: " << p1 << endl;
        usage();
    }
  //---------------------------------------------------------
  // Syntax checking for p2. If p2 is used, then
  // the next argument must be a non-switch.
  //---------------------------------------------------------
  cout << "--------------------------------------------" << endl;
  cout << "sintax checking for p2 if p2 is usde " << endl;
  cout << "the next argument must be a non-switch "<<endl;
  cout << "--------------------------------------------" << endl;
  bool p2    = clp.Switch("p2")>0;
  string v2 = clp.GetSwitchStr("p2");
  //cout << "p2 = "<<p2 << endl;
  //cout << "!v2.empty(): "<< !v2.empty() << endl;
  //if(!v2.empty()) cout << "parametro v2 = " << v2 << endl;
  if (p2  && v2.empty()) {
      cout << "! syntax error: v2 required when /p2 is used" << endl;
      usage();
      return 0;
  }else{
      cout << "v2 required when -p2 is used :" << v2 << endl;
      usage();
  }
    //---------------------------------------------------------
  // Syntax checking for p2.
  // For p3, since v3 is optional, we use a default "" value.
  // p4 is only valid if p3 is enabled
  //---------------------------------------------------------
  cout << "--------------------------------------------" << endl;
  cout << "For p3, since v3 is optional, we use a default "" value " << endl;
  cout << "p4 is only valid if p3 is enabled"<<endl;
  cout << "--------------------------------------------" << endl;
  bool p3    = clp.Switch("p3")>0;
  string v3 = clp.GetSwitchStr("p3","");
  bool p4    = p3 && (clp.Switch("p4")>0);
  usage();
  printf("p1 : %s\n",p1);
  printf("p2 : %d  v2: %s\n",p2,v2);
  printf("p3 : %d  v3: %s\n",p3,v3);
  printf("p4 : %d\n",p4);
    
	return 0;
}
