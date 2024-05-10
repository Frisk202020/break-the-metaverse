from PIL import Image
import random as r

""" To generate the blood palette, uncomment line 90
To generate a sample, uncomment and choose a noise (line 92), then uncomment line 93 and choose a group (O, A or B) """

"""
@Brief : Generate the palette of all blood types
"""
def palette():
    img = Image.new('RGB', [900,300])
    for i in range(3):
        for j in range(300):
            for k in range(300):
                I = i*300 + k
                if i == 0:
                    img.putpixel((I, j), (247,30,15))
                elif i == 1:
                    img.putpixel((I,j), (250, 65, 52))
                else:
                    img.putpixel((I, j), (255, 88, 77))
    img.save("../palette.jpg")
    return

"""
@Brief : generate a list of random values 
@Param :
    - length
    - min, max : defining the interval in which the random values must be
"""
def random_list(length: int, min: int, max: int):
    l = []
    for i in range(length):
        n = r.randint(min, max)
        while n in l:
            n = r.randint(min, max)
        l.append(n)
    return l

"""
@Brief : pick a random value from a random list
@Param : list
"""
def random_in_list(l: list):
    ind = r.randint(0, len(l)-1)
    return l[ind]

"""
@Brief : generate a blood sample
@Param
    - group : the blood group of the subject, most of the colors will be related to this group
    - noise : a pourcentage of the pixels will have a random color different from the intended one
"""
def sample(group: str, noise: float):
    length = int(noise*300)
    noiseX = random_list(length, 0, 299)
    noiseY = random_list(length, 0, 299)

    img = Image.new('RGB', [300,300])
    if group == 'O':
        for j in range(300):
            for k in range(300):
                if (j in noiseX and k in noiseY):
                    i = r.randint(1, 2)
                else:
                    i = 0
                
                if i == 0:
                    img.putpixel((j, k), (247,30,15))
                elif i == 1:
                    img.putpixel((j,k), (250, 65, 52))
                else:
                    img.putpixel((j, k), (255, 88, 77))

    elif group == 'A':
        for j in range(300):
            for k in range(300):
                if (j in noiseX and k in noiseY):
                    i = random_in_list([0,2])
                else:
                    i = 1
                
                if i == 0:
                    img.putpixel((j, k), (247,30,15))
                elif i == 1:
                    img.putpixel((j,k), (250, 65, 52))
                else:
                    img.putpixel((j, k), (255, 88, 77))

    else:
        for j in range(300):
            for k in range(300):
                if (j in noiseX and k in noiseY):
                    i = r.randint(0, 1)
                else:
                    i = 2
                
                if i == 0:
                    img.putpixel((j, k), (247,30,15))
                elif i == 1:
                    img.putpixel((j,k), (250, 65, 52))
                else:
                    img.putpixel((j, k), (255, 88, 77))
    
    img.save("../sample.jpg")
    return

def circle(x: int, r: int):
    return int((r**2 - x**2)**0.5)

def cell(im: Image, radius: int, center: list, type: str):
    if type == "red":
        color = (190,156,145)
        overlap = (160, 126, 115)
    elif type == "white":
        color = (151,83,122)
        overlap = (0,0,0)

    for x in range(-radius, radius):
        Y = circle(x, radius)
        for y in range(-Y, Y):
            M = (x+center[0], y+center[1])
            current_color = im.getpixel(M)

            if color == current_color or overlap == current_color:
                im.putpixel(M, overlap)

            else:
                im.putpixel(M, color)

    return im

def belongs(interval: list, M0: list):
    Ix = interval[0]
    Iy = interval[1]
    X = M0[0]
    Y = M0[1]

    if (Ix[0] <= X and Ix[1] >= X) and (Iy[0] <= Y and Iy[1] >= Y):
        return True
    return False

def whiteInRed(interval: list, M0: list, r: int):
    X = M0[0]
    Y = M0[1]
    for x in range(X - r, X + r):
        for y in range(Y - r, Y + r):
            if belongs(interval, [x, y]):
                return True
    return False

def globules(im: Image, length: int, N: int):
    safe = []
    # red globules
    for i in range(N):
        generate = True
        while generate :
            generate = False
            radius = r.randint(30, 60)
            X0 = r.randint(radius+10, length-radius-10)
            Y0 = r.randint(radius+10, length-radius-10)
            for s in safe:
                if(belongs(s, [X0, Y0])):
                    generate = True       

        cell(im, radius, [X0, Y0], "red")
        safe.append([(X0 - radius, X0 + radius), (Y0 - radius, Y0 + radius)])
    
    # white globules
    Nr = r.randint(20, 30)
    for i in range(Nr):
        generate = True   
        while generate :
            generate = False
            radius = r.randint(60, 90)
            X0 = r.randint(radius+10, length-radius-10)
            Y0 = r.randint(radius+10, length-radius-10)
            for s in safe:
                if(whiteInRed(s, [X0, Y0], radius)):
                    generate = True       

        cell(im, radius, [X0, Y0], "white")
        safe.append([(X0 - radius, X0 + radius), (Y0 - radius, Y0 + radius)])
    
    return im

def cell_sample():
    img = Image.new('RGB', [3000,3000])
    length = 3000
    for x in range(length):
        for y in range(length):
            img.putpixel((x, y), (213,204,189)) #background color

    #generating white globules
    N = r.randint(50, 100)
    globules(img, length, N)

    img.save("../cell.jpg")
    return

def main():
    # palette()

    # noise = 0.1
    # sample('O', noise)

    cell_sample()

    return

main()




