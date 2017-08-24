# cmdLineParam is a C/C++ class to help you process command line arguments. 
#Introduction
cmdLineParam is designed to provide the following common/standard requirements:

	Implicit or explicit help option.
	Usage of both slash ("/") or dash ("-") switch characters
	Support to add more switch characters
	Switch case sensitivity support
	Switch abbreviation support
	Switch default value support
	First Non Switch Parameter support
	Support for Quoted parameters

#Nomenclature
The following legend is used to describe the  CCommandLineParameters class:

Command Line:
The string passed to a program including the name of the current program.
Parameter Line:
The string passed to a program excluding the name of the current program.
Arguments: 
The words in the parameter line each separated by space. Argument 1 is the first word, argument 2 is the same word, etc. Argument 0 is the name of the program. Please note that a double quote (") is used to combine multiple words are one argument. example: President "George Bush"
The above is 2 arguments separate arguments, president and George Bush.
Parameters:  Same as arguments
Switch:
An argument or parameter which begins with a switch character. By default, the switch characters are dash ("-" or forward slash ("/") Abbreviated Switch A switch that offers an abbreviation shortcut. Example: /s*end. Allows for /send or /s to be used. 
Non-Switch:
An argument or parameter which DOES NOT begin with a switch character.
switch value: 
The value assigned to a switch.
argument or parameter index:
The index of the argument on the command line.

The following is standard command line syntax information which will be helpful to you when you wish to document or describe the
possible command line parameters for your application in a help display:

[] When a parameter is surrounded with square brackets, this typically means the parameter is optional. The parameter is not required for normal operations of your program. example: program.exe [-p1]

<> When a parameter is surrounded with angle brackets, this typically means the parameter is required for normal operations of your program. example: program.exe <filename>

| The vertical bar means a choice between one parameter or parameter value is acceptable. example: program.exe </device:com1|com2>

For example, suppose an application describes the following command line syntax:

program.exe <p1> [-p2 <v2>] [[/p3 [v3]] [/p4]] [/p5 <v5|w5>]

By following the standard syntax, you can easily understand what the required and optional parameters for any application.
In this example, p1 is a required parameter. The program will not run if it is not passed. The switches /p2, /p3, /p4 and /p5 are
optional. If p2 is used, then v2 is required. If p3 is used, then V3 and /p4 are optional. However, the parameters v3 and /p4 are only valid if /p3 is used in the first place. If /P5 is used, the valid values are v5 or w5.

This basic syntax is standard across platforms.

#Using the code