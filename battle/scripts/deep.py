from PIL import Image
import random as r
from palette import random_list, randomColor, corruption

def generate():
    og = Image.open("../data/Fay.jpg")
    dim = og.size
    Nx = dim[0]//10
    Ny = dim[1]//10

    im = Image.new("RGB", [Nx*10, Ny*10])
    for x in range(Nx*10):
        for y in range(Ny*10):
            im.putpixel((x, y), og.getpixel((x, y)))

    dim = im.size
    im = corruption(im, dim[0], dim[1], 1, True)
    og.close()
    f = open("../data/deep.txt", "w")
    
    for i in range(10):
        for j in range(10):
            s = '*' + str(j + 10*i) + '*\n'
            f.write(s)
            for x in range(i*Nx, (i+1)*Nx):
                for y in range(j*Ny, (j+1)*Ny):
                    s = str(x) +  " " + str(y) + "\n"
                    f.write(s)

    f.close()
    return im

def load():
    f = open("../data/deep.txt", "r")
    corrupted = []
    l = []

    for s in f.readlines():
        if (s[0] != '*'):
            st = s.split(' ')
            tup = (int(st[0]), int(st[1]))
            l.append(tup)
        else:
            if (l != []):
                corrupted.append(l)
            l = []

    corrupted.append(l)
    f.close()
    return corrupted

def write(l: list):
    f = open("../data/deep.txt", "w")
    
    for i in range(len(l)):
        s = '*' + str(i) + '*\n'
        f.write(s)
        for j in range(len(l[i])):
            s = str(l[i][j][0]) +  " " + str(l[i][j][1]) + "\n"
            f.write(s)

    f.close()
    return


def reveal(im: Image.Image, n: int, corrupted: list):
    rick = Image.open("../data/Fay.jpg")

    for i in range(min(n, len(corrupted))):
        pieceInd = r.randint(0, len(corrupted) - 1)
        piece = corrupted[pieceInd]

        for x in piece:
            color = rick.getpixel(x)
            #print(color, im.getpixel(x))
            im.putpixel(x, color)
            #print(color, im.getpixel(x))

        corrupted.pop(pieceInd)

    write(corrupted)
    return im


def main():
    print("~~ DEEP HOME Decryption software ~~")
    ans = input("If you're launching this software for the first time, please prompt 'y'. ")
    if (ans == 'y'):
        im = generate()
        print("Encrypted access key generated at 'result/deep.jpg'! You should now find parts of the key all around BOTTOM Home. Good luck.")
    else:
        done = False
        while(not(done)):
            x = int(input("How much should pieces should be revealed (look at the MJ Book) ? "))
            if (x > 101):
                print("please input a value between 0 and 101")
            else:
                done = True

        print("Revealing image, this may take some time...")
        im = Image.open("../result/deep.jpg")
        corrupted = load()
        im = reveal(im, x, corrupted)
        print("All done ! Image 'deep.jpg' has been updated.")

    im.save("../result/deep.jpg")
    im.close()
    

main()