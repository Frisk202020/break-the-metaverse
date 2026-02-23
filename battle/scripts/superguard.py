import random as r
import time as t

def main():
    FPS = 30

    start = t.time()
    input("The enemy will attack...")
    endMJ = t.time()
    input("Press enter now !!")
    endPJ = t.time()

    print("frames took :", int((endPJ - endMJ)*FPS))

    return

main()