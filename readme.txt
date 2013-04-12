- This project is under GNU 2 license

implementation of Lexical Analyzer Generator like FLEX spring 2013 
Main Modules : 
	1.Parsing input 
	2.Generate non-deterministic finite state automata (NFA)
	3.Generate deterministic finite state automata (DFA)
	4.Minimize DFA
	5.Simulating the generated DFA 



User manual
•	Regular expressions and definitions are written in the file “in” besides the .exe file
•	The java file must be besides the .exe file. The java input file contains the source code. 
	The matched tokens are written in a file “input.txt”
•	Output file also contains the unmatched lexemes (error in which line)

1-	Regular definitions can contain only | and – symbols
Ex:  digit = a-z|A-z
2-	It can't handle + * ? ( ) definitions must also come before expression using them
3-	Regular expressions can't have - symbol in it
Ex:  reg : (a-z)+ can't be handled instead define regular definition for it
4-	When use | + * ? we have to use () with them
Ex:  
•	reg : (a)+
•	reg2 : ((a)+ | (b)*)
5-	\ has to be used with all the preserved words used in the rules which are { } ( ) = : or any other preserved characters
6-	If any keyword need to be define in regular expression then add it between brackets
Ex: 
•	reg0 :(null)
•	reg1 :(true|false)
7-regular definiton has to be written in ()
Ex:
digit = 0-9 
num : (digit)
