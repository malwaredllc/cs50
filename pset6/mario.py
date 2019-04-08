def main():
    # get height as input from user
    while True:
        height = input("Height: ")
        if height.isdigit() and 0 < int(height) < 9:
            height = int(height)

            # print bricks using format string
            for i in range(1, height + 1):
                print(str("#" * i).rjust(height) + " ", "#" * i)
            exit(0)


if __name__ == '__main__':
    main()
