import random as r

def generate_alphabet():

    s = "abcdefghijklmnopqrstuvwxyz"
    S = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"

    l, L = [], []

    for i in range(26):
        l.append(s[i])
        L.append(S[i])

    d = {}
    D = {}

    for i in range(26):
        ind = r.randint(0, (25 - i))
        IND = r.randint(0, (25 - i))
        d[s[i]] = l[ind]
        D[S[i]] = L[IND]
        
        l.pop(ind)
        L.pop(IND)

    return d, D

text = "Hi everyone !\n\nLet me introduce myself, I'm ClyDE Cipeher and I'm the one in charge of your decipher task. You may think it is complicated, and it is, so congrats if you made it this far ! Oh, you may wonder what's the purpose of this long, long, long text. Well, in order to unlock your piece of IP adress, you need to write this password on the chalkboard : QWERTY\n\nYeah, that's it, QWERTY. Why would I choose some complicated shit when most people reading this will not understand a pourcentage of what's written ? Anyway, thanks for your time, and good luck on your quest. I hope you try to reach BOTTOM TOWN for a good reason..."

def cipher(text: str):
    d, D = generate_alphabet()
    result = ""

    for i in range(len(text)):
        if (text[i] in list("abcdefghijklmnopqrstuvwxyz")):
            for k in d.keys():
                if (text[i] == k):
                    result += d[k]
        elif (text[i] in list("ABCDEFGHIJKLMNOPQRSTUVWXYZ")):
            for k in D.keys():
                if (text[i] == k):
                    result += D[k]
        else:
            result += text[i]
    
    return result

result = cipher(text)

def simplify(text: str):
    simple = ""
    s = "abcdefghijklmnopqrstuvwxyz "
    S = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    for x in text:
        if (x in s or x in S):
            simple += x
        elif (x == "'" or x == "\n"):
            simple += " "
    
    return simple

def clean(words: list):
    s = "abcdefghijklmnopqrstuvwxyz'"
    S = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"

    for i in range(len(words)):
        string = ""
        for x in words[i]:
            if x in s or x in S:
                string += x
    
        words[i] = string

    return words

def rebuild(text: str, l: list):
    result = ""
    ind = 0

    for i in range(len(text)):
        if (i >= l[1] and i < l[1] + len(l[0])):
            result += l[0][ind]
            ind += 1
        else:
            result += text[i]
        
    return result
            

def software():
    print("Decipher trial software - by Dipper")
    text = "Hi everyone !\n\nLet me introduce myself, I'm ClyDE Cipeher and I'm the one in charge of your decipher task. You may think it is complicated, and it is, so congrats if you made it this far ! Oh, you may wonder what's the purpose of this long, long, long text. Well, in order to unlock your piece of IP adress, you need to write this password on the chalkboard : QWERTY\n\nYeah, that's it, QWERTY. Why would I choose some complicated shit when most people reading this will not understand a pourcentage of what's written ? Anyway, thanks for your time, and good luck on your quest. I hope you try to reach BOTTOM TOWN for a good reason..."
    simp = simplify(text)
    words = []
    indexes = []
    w = ""
    j = 0
    
    for i in range(len(text)):
        x = text[i]
        if(x == " " or x == "\n"):
            if (w != ""):
                words.append(w)
                indexes.append(j)
            w = ""
            j = i + 1
        else:
            w += x

    words = clean(words)

    encrypt = cipher(text)
    end = False
    
    while(not(end)):
        prompt = input("> ")

        if (prompt == "end"):
            end = True
        else:
            for i in range(len(words)):
                if (prompt == words[i]):
                    encrypt = rebuild(encrypt, [words[i], indexes[i]])
            
            print(encrypt)

    return
            

print(software())
