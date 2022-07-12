# MAMAP

Made A Magic Argument Parser (MAMAP) Remake the wheel, argument parser. Why? Don't ask... 

Well ok there is actually a reason, the idea was to make an argument parser that was modular and extensible. The idea is that you can add custom argument checks fairly easily because of the flexibility of the design. MAMAP contains a structured hierachy built at its foundation from Options. Properties have a fixed number of options associated with them. Then there are the arguments, arguments can contain one or more properties. Finally, at the top of the hierarchy is the argument parser class which can contain any number of arguments. 
