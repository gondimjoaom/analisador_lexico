import sys



linha = 1
coluna = 1
operandos = ['+','-','/','*','%', '=']

c = sys.stdin.read(1)
while c:
    #coluna += 1
    if c.isalpha() or c == '_': #IDENTIFICADOR
        c = sys.stdin.read(1)
        coluna += 1
        while c.isalnum() or c == '_':
            c = sys.stdin.read(1)
            coluna += 1
    if c == '\n':
        linha += 1
        coluna = 1
    if c.isdigit():
        c = sys.stdin.read(1)
        coluna += 1
        while c.isdigit() or c == '.':
            c = sys.stdin.read(1)
            coluna += 1
        if c.isalpha():
            print(str(linha) + " " + str(coluna - 1))
    if c == '\'':
        c = sys.stdin.read(1)
        c = sys.stdin.read(1) #COLOCAR EOF
        coluna += 1
        if c != '\'':
            print(str(linha) + " " + str(coluna))
    if c == "\"":
        c = sys.stdin.read(1)
        coluna += 1
        while c != "\"":
            c = sys.stdin.read(1)
            coluna += 1
        
            
    c = sys.stdin.read(1)