import random as r
import time as t

def main():
    window = r.randint(1, 10)

    string = "For this hack, you'll need to press a key after " + str(window) + " seconds. Press any key to start the hack. You'll have a 0.1 seconds window of error"
    input(string)

    start = t.time()
    input("Press any key when you think the time is right")
    end = t.time()

    print("time took :", round(end - start, 2), "seconds")
    if (window - 0.1 < end - start and end - start < window + 0.1):
        print("Success !")
    else:
        print("Fail...")
    return

main()