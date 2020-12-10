# MAMAP

[![Codacy Badge](https://api.codacy.com/project/badge/Grade/bb8a314822344ee2911fe76efc560c1a)](https://app.codacy.com/gh/JoshuaSBrown/MAMAP?utm_source=github.com&utm_medium=referral&utm_content=JoshuaSBrown/MAMAP&utm_campaign=Badge_Grade_Settings)
[![deepcode](https://www.deepcode.ai/api/gh/badge?key=eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJwbGF0Zm9ybTEiOiJnaCIsIm93bmVyMSI6Ikpvc2h1YVNCcm93biIsInJlcG8xIjoiTUFNQVAiLCJpbmNsdWRlTGludCI6ZmFsc2UsImF1dGhvcklkIjoxNjMwMSwiaWF0IjoxNjA3NTc3NTY5fQ.ITk3lCLeNSwKCWT_lLSHL7NkAZK-vjBR8OAf6-N46As)](https://www.deepcode.ai/app/gh/JoshuaSBrown/MAMAP/_/dashboard?utm_content=gh%2FJoshuaSBrown%2FMAMAP)

Made A Magic Argument Parser (MAMAP) Remake the wheel, argument parser. Why? Don't ask... 

Well ok there is actually a reason, the idea was to make an argument parser that was modular and extensible. The idea is that you can add custom argument checks fairly easily because of the flexibility of the design. MAMAP contains a structured hierachy built at its foundation from Options. Properties have a fixed number of options associated with them. Then there are the arguments, arguments can contain one or more properties. Finally, at the top of the hierarchy is the argument parser class which can contain any number of arguments. 
