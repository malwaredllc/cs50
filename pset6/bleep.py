import os
import sys


def main():
    # return usage information and exit if incorrect number of command-line arguments
    if len(sys.argv) != 2:
        exit("Usage: python bleep.py dictionary")

    filename = sys.argv[1]

    # return error message if dictionary file does not exit
    if not os.path.isfile(filename):
        exit("Error: file '{}' does not exist".format(filename))

    # read banned words from dictionary and strip newline characters from end of strings
    wordlist = [line.rstrip() for line in open(filename, 'r').readlines()]

    # get text to censor as input from user
    text = input("What would you like to censor? ")

    # replace banned words in text with asterisks
    for word in text.split():
        if word.lower() in wordlist:
            text = text.replace(word, '*' * len(word))

    # display censored output
    print(text)


if __name__ == "__main__":
    main()

