def lines(a, b):
    """Return lines in both a and b"""

    return list(set(a.splitlines()).intersection(set(b.splitlines())))


def sentences(a, b):
    """Return sentences in both a and b"""

    from nltk.tokenize import sent_tokenize
    return list(set(sent_tokenize(a)).intersection(set(sent_tokenize(b))))


def substrings(a, b, n):
    """Return substrings of length n in both a and b"""
    substrings_a, substrings_b = set(), set()
    length_a, length_b = len(a), len(b)

    # get all unique substrings of string b
    for i in range(length_a):
        for j in range(i, length_a):
            substrings_a.add(a[i:j + 1])

    # get all unique of string b
    for i in range(length_b):
        for j in range(i, length_b):
            substrings_b.add(b[i:j + 1])

    # remove duplicates and substrings greater than length n
    return [s for s in substrings_a.intersection(substrings_b) if len(s) == n]
