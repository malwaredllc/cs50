import sys


def main():

    # get number as input from user
    while True:
        number = input("Number: ")
        try:
            int(number)
            break
        except:
            continue

    # Luhn's algorithm
    total = 0

    # starting from the 2nd to last digit, multiply every other digit by 2
    for product in map(lambda x: int(x) * 2, number[-2::-2]):

        # sum the digits of the products
        for digit in str(product):
            total += int(digit)

    # sum the digits not multiplied by 2
    for integer in map(lambda x: int(x), number[::-2]):
        total += integer

    # if total mod 10 is congruent to 0, the number is valid
    if total % 10 == 0:

        # check card type
        if len(number) in (13, 16) and number.startswith('4'):
            print("VISA")
        elif len(number) == 16 and filter(lambda x: number.startswith(str(x)), range(51, 55)):
            print("MASTERCARD")
        elif len(number) == 15 and filter(lambda x: number.startswith(x), ['34', '37']):
            print("AMEX")
        else:
            print("INVALID")

    else:
        print("INVALID")


if __name__ == '__main__':
    main()
