import sys
import crypt
import string
from itertools import chain, product


def main():

    # display usage information and exit if incorrect number of arguments
    if len(sys.argv) != 2 or len(sys.argv[1]) != 13:
        exit("Usage: python crack.py hashcode")

    # get hash from user as command-line argument
    hashcode = sys.argv[1]
    salt = hashcode[:2]

    # initialize variables for character set and max length of password
    charset = string.ascii_letters + string.digits
    maxlength = 5

    # brute force algorithm
    for candidate in bruteforce(charset, maxlength):
        if crypt.crypt(candidate, salt) == hashcode:
            print(candidate)
            break


def bruteforce(charset, maxlength):

    # return memory-efficient generator object for iterating over all possible combinations of characters up to maxlength
    return (''.join(candidate) for candidate in chain.from_iterable(product(charset, repeat=i) for i in range(1, maxlength + 1)))


if __name__ == '__main__':
    main()
