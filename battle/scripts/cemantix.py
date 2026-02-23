import random as r

def key_from_value(d: dict, v: str):
    for key, value in d.items():
        if (v == value):
            return key

    return "none"

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
    
    return result, d, D

def clean(words: list, indexes: list):
    s = "abcdefghijklmnopqrstuvwxyz'"
    S = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"

    for i in range(len(words)):
        string = ""
        for x in words[i]:
            if x in s or x in S:
                string += x
    
        words[i] = string

    j = 0
    for i in range(len(words)-1):
        j += 1
        if (words[j] == ''):
            words.pop(j)
            indexes.pop(j)
            j -= 1

    return words, indexes

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

def printf(text: str, words: list, indexes: list, revealed: list, colors: list):
    colors.append("\033[97m")
    ind = 0
    i = 0
    word = False
    end = -1
    result = ""
    while (ind < len(words)):
        if (word == False):
            result += colors[ind]
            word = True
            end = indexes[ind] + len(words[ind])
            ind += 1

        if (i == end):
            result += "\033[97m"
            word = False
        
        if (text[i] in revealed.keys() and colors[ind-1] != "\033[92m"):
            result += "\033[93m"
            result += revealed[text[i]]
            result += "\033[97m"
        else:
            result += text[i]
        
        i += 1

    while(i < len(text)):
        if (text[i] in revealed.keys() and colors[ind-1] != "\033[92m"):
            result += "\033[93m"
            result += revealed[text[i]]
            result += "\033[97m"
        else:
            result += text[i]
        i += 1

    result += "\033[97m"
    print(result)

    return

def lifebar(N: int):
    bar = ""
    for i in range(N):
        bar += "♥ "
    
    return bar


def software():
    print("*** Decipher trial software - by Dipper P ***")
    print("\nEncrypted letters are white")
    print("\033[93mRevealed characters are yellow")
    print("\033[92mFound words are green")
    input("\n\033[97mPress any key to start ")
    text = "Hi everyone !\nLet me introduce myself, I'm ClyDE Cipeher and I'm the one in charge of your decipher task. You may think it is complicated, and it is, so congrats if you made it this far ! Oh, you may wonder what's the purpose of this long, long, long text. Well, in order to unlock your piece of IP adress, you need to write this password on the chalkboard : QWERTY\n\nYeah, that's it, QWERTY. Why would I choose some complicated shit when most people reading this will not understand a pourcentage of what's written ? Anyway, thanks for your time, and good luck on your quest. I hope you try to reach BOTTOM TOWN for a good reason..."
    words = []
    indexes = []
    lives = 10
    w = ""
    j = 0
    
    for i in range(len(text)):
        x = text[i]
        if(x == " " or x == "\n" or i == len(text) - 1):
            if (w != ""):
                words.append(w)
                indexes.append(j)
            w = ""
            j = i + 1
        else:
            w += x

    words, indexes = clean(words, indexes)
    colors = ["\033[97m" for i in range(len(words))]
    revealed = {}
    left = 10

    encrypt, d, D = cipher(text)
    print("")
    print(encrypt)
    
    while(1 == 1):
        prompt = input("\n\n> ")

        if (prompt == "-end"):
            print("*break*")
            return
        elif (prompt[0:6] == "reveal"):
            if (left > 0):
                left -= 1
                if (len(prompt) > 7):
                    if (prompt[7] in d.values()):
                        revealed[prompt[7]] = key_from_value(d, prompt[7])
                    else:
                        revealed[prompt[7]] = key_from_value(D, prompt[7])
                else:
                    print("\033[91mYou forgot to indicate the character to reveal !\033[97m\n")
            else:
                print("\033[91mNo reveals left !\033[97m")
        else:
            correct = False
            for i in range(len(words)):
                if (prompt == words[i]):
                    correct = True
                    colors[i] = "\033[92m"
                    encrypt = rebuild(encrypt, [words[i], indexes[i]])
            
            if (not(correct)):
                lives -= 1

        if (lives == 0):
            print("You lost !")
            return
            
        printf(encrypt, words, indexes, revealed, colors)
        print("\n\033[94mRevealed characters :", revealed)

        if (lives > 3):
            print("\033[95mLives :", lifebar(lives), "(", lives, ")\033[97m")
        else:
            print("\033[91mLives :", lifebar(lives), "DANGER !!\033[97m")

        print("\033[94mReveals left :", left, "\033[97m")
            
software()