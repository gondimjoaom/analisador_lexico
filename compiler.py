import sys
import string

def ehascii(char):
    if((ord(char) > 31 and ord(char) < 127) or (ord(c) == 9 or ord(c) == 10) ):
        return True
    return False

if __name__ == "__main__":

    tokens = []
    digitos = ['0','1','2','3','4','5','6','7','8','9']
    operadores = ['+', '-', '=', '<', '>', '*', '/', '%']
    erro_ascii = False
    c = sys.stdin.read(1)
    while c:
        if(ehascii(c)):
            if (c in digitos): #CONFERIR NUMERO
                c = sys.stdin.read(1)
                while(c in digitos):
                    c = sys.stdin.read(1)
                if (c == '.'):
                    c = sys.stdin.read(1)
                    while(c in digitos):
                        c = sys.stdin.read(1)
        else:
            erro_ascii = True
            break
        c = sys.stdin.read(1)
    if erro_ascii:
        print ("ARQUIVO INVALIDO")