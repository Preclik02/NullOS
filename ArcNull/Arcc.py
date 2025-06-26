import os
sifra_dict = {
    "4_tm/": "auto",
    "()€[4@": "break",
    "%49[": "case",
    "%84€": "char",
    "%/$9tm": "const",
    "%/$tm!$_[": "continue",
    "][*4_?tm": "default",
    "]/": "do ",
    "]/_()?[": "double",
    "[?9[": "else",
    "[$_=": "enum",
    "[<>tm[€$": "extern",
    "*?/4tm": "float",
    "*/€": "for",
    "O/tm/": "goto",
    "!*": "if",
    "!$?!$[": "inline",
    "!$tm": "int",
    "?/$O": "long",
    "€[O!9tm[€": "register",
    "€[9tm€!%tm": "restrict",
    "€[tm_€$": "return",
    "98/€tm": "short",
    "9!O$[]": "signed",
    "9!3[/*": "sizeof",
    "9tm4tm!%": "static",
    "9tm€_%tm": "struct",
    "9..!tm%8": "switch",
    "tmY+[][*": "typedef",
    "_$!/$": "union",
    "_$9!O$[]": "unsigned",
    "./!]": "void",
    "./?4tm!?[": "volatile",
    "..8!?[": "while",
    "+€!$tm*": "printf",
    "!$%?_][": "include",
    "=4!$": "main",
    "=4!$()": "main",
    "#!$%?_][": "#include",
    "+€!$tm*(": "printf(",
    "+€int*(": "printf(",
    "+€int*": "printf"
}

x = input("Filename (without .arc): ")

with open(x + ".arc", "r") as f:
    code = f.read()

for sifra, word in sifra_dict.items():
    code = code.replace(sifra, word)

with open("program.c", "w") as f:
    f.write(code)
    
filepath = os.path.expanduser("~/Documents/filenames.txt")

with open(filepath, "w") as f:
    f.write(x)

