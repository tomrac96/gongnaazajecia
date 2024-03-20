def policz(plik):
    literki = dict()
    with open(plik, "r") as f:
        linijka = f.readline()
        while linijka:
            for litera in linijka:
                    literki[litera.lower()] = literki.get(litera.lower(), 0) + 1
            linijka = f.readline()
    return literki

if __name__ == "__main__":
    print(policz("lorem.txt"))
