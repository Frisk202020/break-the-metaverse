from PIL import Image
import random as r
from palette import random_list, randomColor, corruption

def random_color():
    return (r.randint(0, 255), r.randint(0, 255), r.randint(0, 255))

def generate_chess():
    im = Image.new('RGB', [800, 800])
    white = random_color()
    black = random_color()

    for i in range(8):
        for j in range(8):
            x, y = i%2, j%2
            if (x == y):
                for I in range(100*i, 100*(i+1)):
                    for J in range(100*j, 100*(j+1)):
                        im.putpixel((I, J), white)
            else:
                for I in range(100*i, 100*(i+1)):
                    for J in range(100*j, 100*(j+1)):
                        im.putpixel((I, J), black)

    return (im, white, black)

def circle(x: int, r: int):
    return int((r**2 - x**2)**0.5)

def pawn(im: Image.Image, color: tuple, pos: list):
    center = (100*pos[0] + 50, 100*pos[1] + 50)
    R = int((25**2 + 25**2)**0.5)
    for x in range(-R, R):
        Y = circle(x, R)
        for y in range(-Y, Y):
            im.putpixel((x + center[0], y + center[1]), color)
    
    return im

def number(im: Image.Image, color: tuple, pos: list):
    if (pos[2] == 1):
        for y in range (25, 75):
            im.putpixel((100*pos[0] + 49, 100*pos[1] + y), color)
            im.putpixel((100*pos[0] + 50, 100*pos[1] + y), color)
    elif (pos[2] == 3):
        for y in range (25, 75):
            im.putpixel((100*pos[0] + 15, 100*pos[1] + y), color)
            im.putpixel((100*pos[0] + 16, 100*pos[1] + y), color)
            im.putpixel((100*pos[0] + 47, 100*pos[1] + y), color)
            im.putpixel((100*pos[0] + 48, 100*pos[1] + y), color)
            im.putpixel((100*pos[0] + 79, 100*pos[1] + y), color)
            im.putpixel((100*pos[0] + 80, 100*pos[1] + y), color)
    elif (pos[2] == 5):
        for i in range (25):
            im.putpixel((100*pos[0] + 24 + i, 100*pos[1] + 25 + 2*i), color)
            im.putpixel((100*pos[0] + 25 + i, 100*pos[1] + 25 + 2*i), color)
            im.putpixel((100*pos[0] + 26 + i, 100*pos[1] + 25 + 2*i), color)
            im.putpixel((100*pos[0] + 50 + i, 100*pos[1] + 75 - 2*i), color)
            im.putpixel((100*pos[0] + 51 + i, 100*pos[1] + 75 - 2*i), color)
            im.putpixel((100*pos[0] + 52 + i, 100*pos[1] + 75 - 2*i), color)
    elif(pos[2] == 9):
        for i in range (50):
            im.putpixel((100*pos[0] + 30 + i, 100*pos[1] + 25 + i), color)
            im.putpixel((100*pos[0] + 30 + i, 100*pos[1] + 75 - i), color)
            im.putpixel((100*pos[0] + 29 + i, 100*pos[1] + 25 + i), color)
            im.putpixel((100*pos[0] + 29 + i, 100*pos[1] + 75 - i), color)
            im.putpixel((100*pos[0] + 31 + i, 100*pos[1] + 25 + i), color)
            im.putpixel((100*pos[0] + 31 + i, 100*pos[1] + 75 - i), color)
        
        for y in range (24, 76):
            im.putpixel((100*pos[0] + 24, 100*pos[1] + y), color)
            im.putpixel((100*pos[0] + 25, 100*pos[1] + y), color)
            im.putpixel((100*pos[0] + 26, 100*pos[1] + y), color)                
    else:
        print("Unknown")

    return im

def start_config():
    M = []

    for i in range(2):
        for j in range(8):
            M.append((j, i, 0))
            M.append((j, -i-1, 0))

    return M

def heart_config():
    M = [(0, 1, 0), (0, 6, 0), (1, 0, 0), (1, 2, 0), (1, 5, 0), (1, 7, 0), (2, 0, 0), (2, 3, 0), (2, 4, 0), (2, 7, 0), (3, 1, 0), (3, 6, 0), (4, 2, 0), (4, 5, 0), (5, 3, 0), (5, 4, 0)]
    for i in range(len(M)):
        M[i] = (M[i][0] + 1, M[i][1], 0)
    return M

def arrow_config():
    M = [(2, 4, 0), (1, 4, 0), (3, 1, 0), (3, 2, 0), (3, 3, 0), (3, 4, 0), (3, 6, 0), (2, 5, 0), (4, 1, 0), (4, 2, 0), (4, 3, 0), (4, 4, 0), (4, 6, 0), (5, 4, 0), (5, 5, 0), (6, 4, 0)]
    return M

def generate_positions(N: int):
    res = []
    while (len(res) < N):
        pos = (r.randint(0, 7), r.randint(0, 7), 0)
        if pos not in res:
            res.append(pos)

    #print(res)
    return res

def numbers_config():
    M = generate_positions(9)
    for i in range(2):
        M[i] = (M[i][0], M[i][1], 1)
    for i in range(2, 6):
        M[i] = (M[i][0], M[i][1], 3)
    for i in range(6, 8):
        M[i] = (M[i][0], M[i][1], 5)
    M[8] = (M[8][0], M[8][1], 9)
    #print(M)
    
    return M

def glitch(im: Image.Image, size: int, min: int, max: int):
    s = r.randint(min, max)
    x = r.randint(s, size - s - 1)
    y = r.randint(s, size - s - 1)

    for i in range(-s, s):
        for j in range(-s, s):
            im.putpixel((x + i, y + j), randomColor())

    return im

def glitches(im: Image.Image):
    min = 10
    max = 150
    for i in range(r.randint(10, 20)):
        glitch(im, 800, min, max)

    return im

def main():
    # generate chessboard
    names = ["start", "heart", "arrow", "numbers", "inverted", "glitch"]
    configs = [start_config(), heart_config(), arrow_config(), numbers_config(), numbers_config(), start_config()]

    for i in range(len(configs)):
        im, W, B = generate_chess()
        M = configs[i]

        whites = 0
        blacks = 0
        for x in M:
            if (x[0]%2 == x[1]%2):
                if (x[2] == 0):
                    im = pawn(im, B, x)
                else:
                    im = number(im, B, x)
                blacks += 1
            else:
                if (x[2] == 0):
                    im = pawn(im, W, x)
                else:
                    im = number(im, W, x)
                whites += 1

        if (i == 4):
            im = corruption(im, 800, 800, 0.5)        
        if (i == 5):
            im = glitches(im)

        print("Number of pawns ( room", i,") :", whites, "whites,", blacks, "blacks")
        im.save("../result/"+names[i]+".jpg")
        im.close()

    return

main()