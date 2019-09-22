import spell2

WORDS = open('bin/cmp_names.txt').read().split("\n")

def correction(w):
    w = w.lower()
    y = []
    nw = []

    for wd in w.split(" "):
        nw.append(spell2.correction(wd))

    w = " ".join(nw).strip()

    for word in WORDS:
        word = word.lower()
        if w in word:
            return word


#print WORDS
