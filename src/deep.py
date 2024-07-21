from PIL import Image
import random as r
from palette import random_list, randomColor, corruption

def generate():
    im = Image.open("../data/rick.jpg")
    dim = im.size
    im = corruption(im, dim[0], dim[1], 1)

    f = open("../data/deep.txt", "w")
    for i in range(im.size[0]):
        for j in range(im.size[1]):
            s = str(i) +  " " + str(j) + "\n"
            f.write(s)

    f.close()

    return im

def load():
    f = open("../data/deep.txt", "r")
    corrupted = []

    for s in f.readlines():
        l = s.split(' ')
        tup = (int(l[0]), int(l[1]))
        corrupted.append(tup)

    f.close()
    return corrupted

def write(l: list):
    f = open("../data/deep.txt", "w")
    for i in range(len(l)):
        s = str(l[i][0]) +  " " + str(l[i][1]) + "\n"
        f.write(s)

    f.close()
    return


def reveal(im: Image.Image, x: float, corrupted: list):
    rick = Image.open("../data/rick.jpg")
    N = int(im.size[0]*im.size[1]*x)

    for i in range(min(N, len(corrupted))):
        y = r.randint(0, len(corrupted) - 1)
        e = corrupted[y]
        color = rick.getpixel(e)
        im.putpixel(e, color)
        corrupted.pop(y)

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
            x = float(input("How much should the key be decrypted (look at the MJ Book) ? "))
            if (x > 1):
                print("please input a value between 0 and 1")
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