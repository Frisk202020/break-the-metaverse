from PIL import Image
import random as r

""" This file is used for all picture related code"""


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
    img.save("../data/palette.jpg")
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
    
    img.save("../data/sample.jpg")
    return

"""
@Brief : create a circle on an Image object
@Param :  
    - x: abs coordinate
    - r: radius of the cicle
@Return : y(x)
"""
def circle(x: int, r: int):
    return int((r**2 - x**2)**0.5)

"""
@Brief : determine the radius of a point from arbitrary origin
@Param : coordinates
"""
def Radius(x: int, y: int):
    return (x**2 + y**2)**0.5

"""
@Brief : randomly generate the "inner cells" (don't ask me about biology) in a white globule
@Param : 
    - im : the Image object
    - radius : radius of the globule
    - M0 : center of the globule
"""
def innerCells(im: Image, radius: int, M0: list):
    N = r.randint(2, 4)

    center = []
    for i in range(N):
        generate = True
        while generate:
            generate = False
            inner = r.randint(radius//4, radius//2)
            cX = r.randint(0, radius//2)
            cY = r.randint(0, radius//2)
            if (Radius(inner + cX, cY) > radius) or (Radius(cX, inner + cY) > radius):
                generate = True
        
        cell(im, inner, inner, [M0[0] + cX, M0[1] + cY], "white")

    return



"""
@Brief : create a cell on the blood sample picture
@Param :
    - im : the Image object
    - radius : the radius of the cell (randomly generated)
    - center : coordinates of the center of the circle
    - type : the type of the cell (white or red globule)
"""
def cell(im: Image, radius: int, inner: int, center: list, type: str):
    if type == "red":
        color = (190,156,145) # outside color
        Icolor = (216,199,182) # inner color
        overlap = (160,126,115) # color in case of overlapping
    elif type == "white":
        color = (162,112,137)
        overlap = (151,83,122)
        Icolor = (151,83,122)

    for x in range(-radius, radius):
        Y = circle(x, radius)
        for y in range(-Y, Y):
            M = (x+center[0], y+center[1])
            current_color = im.getpixel(M)

            if color == current_color or overlap == current_color:
                im.putpixel(M, overlap)

            else:
                if Radius(x, y) > inner:
                    im.putpixel(M, color)
                else:
                    im.putpixel(M, Icolor)

    return im

"""
@Brief : checks if a future cell radius collides with a pre-existing cell
@Param : 
    - interval : a pre-exisisting cell is defined as a square collision area
    - M0 : the future cell center
"""
def belongs(interval: list, M0: list):
    Ix = interval[0]
    Iy = interval[1]
    X = M0[0]
    Y = M0[1]

    if (Ix[0] <= X and Ix[1] >= X) and (Iy[0] <= Y and Iy[1] >= Y):
        return True
    return False

"""
@Brief : this time, we check if one point among the whole future cell collides with a pre-existing cell (we don't allow white globules to collide at all)
@Param : 
    - interval, M0 : same as before
    - r : the radius of the future cell
"""
def whiteInRed(interval: list, M0: list, r: int):
    X = M0[0]
    Y = M0[1]
    for x in range(X - r, X + r):
        for y in range(Y - r, Y + r):
            if belongs(interval, [x, y]):
                return True
    return False

"""
@Brief : generate all the globules in the blood sample
@Param : 
    - im : the Image object
    - length : the size of the image
"""
def globules(im: Image, length: int):
    safe = []

    # red globules
    N = r.randint(100, 200)

    for i in range(N):
        generate = True
        while generate :
            generate = False
            radius = r.randint(30, 50)
            inner = r.randint(0, radius//2)
            X0 = r.randint(radius+10, length-radius-10)
            Y0 = r.randint(radius+10, length-radius-10)
            for s in safe:
                if(belongs(s, [X0, Y0])):
                    generate = True       

        cell(im, radius, inner, [X0, Y0], "red")
        safe.append([(X0 - radius, X0 + radius), (Y0 - radius, Y0 + radius)])
    
    # white globules
    Nr = r.randint(40, 70)

    for i in range(Nr):
        generate = True   
        while generate :
            generate = False
            radius = r.randint(40, 70)
            inner = 0
            X0 = r.randint(radius+10, length-radius-10)
            Y0 = r.randint(radius+10, length-radius-10)
            for s in safe:
                if(whiteInRed(s, [X0, Y0], radius)):
                    generate = True       

        cell(im, radius, inner, [X0, Y0], "white")
        innerCells(im, radius, [X0, Y0])
        safe.append([(X0 - radius, X0 + radius), (Y0 - radius, Y0 + radius)])
    
    return Nr

"""
@Brief : create and save the blood sample image
"""
def cell_sample():
    img = Image.new('RGB', [3000,3000])
    length = 3000
    for x in range(length):
        for y in range(length):
            img.putpixel((x, y), (213,204,189)) #background color

    #generating white globules
    N = globules(img, length)

    img.save("../data/cell_"+str(N)+".jpg")
    return

def randomColor():
    return (r.randint(0, 255), r.randint(0, 255), r.randint(0, 255))

def corruption(path: str, lx: int, ly: int, noise: float):
    im = Image.open(path)
    noiseX = random_list(int(lx*noise), 0, lx - 1)
    noiseY = random_list(int(ly*noise), 0, ly - 1)

    for x in noiseX:
        for y in noiseY:
            im.putpixel((x, y), randomColor())

    im.save("../data/corrupt.jpg")
    return       


def main():
    # palette()

    # noise = 0.1
    # sample('O', noise)

    #cell_sample()

    corruption("../Table_cipher.jpg", 555, 291, 0.8)

    return

main()




