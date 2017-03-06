#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>

#define R_POCZ 256
#define SPACJA ' '
#define KONIEC_WIERSZA '\n'

/**
 * Wczytuje do tablic dynamicznych ciag wierszy z wejscia. Reprezentowany jest
 * jako zbiór par: znak (różny od spacji) oraz kolumna, w której się on
 * znajduje. 
 */
void wczytaj(int **wier, int **kol, char **zn, int *maxDlugosc, int *ilWier) {
    int *wiersze, *kolumny;
    char *znaki;
    int rozmiar, rozmiarWiersze;
    int i = 0, w = 0, k = 0, akt, pop = 0, maxDl = 0;

    wiersze = malloc(R_POCZ * sizeof *wiersze);
    kolumny = malloc(R_POCZ * sizeof *kolumny);
    znaki = malloc(R_POCZ * sizeof *znaki);
    rozmiar = R_POCZ;
    rozmiarWiersze = R_POCZ;

    wiersze[0] = 0;

    while ((akt = getchar()) != EOF) {
        if (rozmiar <= i) {
            kolumny = realloc(kolumny, 2 * rozmiar * sizeof *kolumny);
            znaki = realloc(znaki, 2 * rozmiar * sizeof *znaki);
            rozmiar *= 2;
        }
        if (akt != KONIEC_WIERSZA) {
            if (akt != SPACJA) {
                znaki[i] = akt;
                kolumny[i] = k;
                ++i;
            }
            ++k;
        } else {
            ++w;
            if (w >= rozmiarWiersze) {
                wiersze =
                        realloc(wiersze, 2 * rozmiarWiersze * sizeof *wiersze);
                rozmiarWiersze *= 2;
            }
            wiersze[w] = i;
            if (k > maxDl) {
                maxDl = k;
            }
            k = 0;
        }
        pop = akt;
    }
    if (pop != KONIEC_WIERSZA && pop != EOF) {
        ++w;
        if (w >= rozmiarWiersze) {
            wiersze = realloc(wiersze, 2 * rozmiarWiersze * sizeof *wiersze);
            rozmiarWiersze *= 2;
        }
        wiersze[w] = i;
        if (k > maxDl) {
            maxDl = k;
        }
        k = 0;
    }
    *wier = wiersze;
    *kol = kolumny;
    *zn = znaki;
    *maxDlugosc = maxDl;
    *ilWier = w;
}
/**
 * Sprawdza, czy w tablicy @t między indeksami @poczatek i @koniec 
 * znajduje się wartość @x.
 */
bool czyJest(int t[], int poczatek, int koniec, int x) {
    int l = poczatek;
    int p = koniec - 1;
    while (l < p) {
        int s = (l + p) / 2;
        if (t[s] < x) {
            l = s + 1;
        } else {
            p = s;
        }
    }
    return (t[l] == x);
}

/**
 * Tworzy tablicę w której po indeksem @k znajduje się tablica, w której to
 * wpisane są numery wierszy, w których to w kolumnie k znajduje się znak
 * różny od spacji.
 */
void stworzTabKol(int ***t, int kolumny[], int wiersze[], int dl, int ilWier) {
    int i, j, akt;
    int **wierszeWKol;
    wierszeWKol = malloc(dl * sizeof *wierszeWKol);
    for (i = 0; i < dl; ++i) {
        wierszeWKol[i] = malloc((ilWier + 1) * sizeof *wierszeWKol[i]);
    }
    for (i = 0; i < dl; ++i) {
        akt = 0;
        for (j = 0; j < ilWier; ++j) {
            if (czyJest(kolumny, wiersze[j], wiersze[j + 1], i)) {
                wierszeWKol[i][akt++] = j;
            }
        }
        wierszeWKol[i][akt] = -1;
    }
    *t = wierszeWKol;
}

/**
 * Tworzy tablicę typu bool rozmiaru @n wypełnioną wartością @true
 */
void stworzTabPrawda(bool **t, int n) {
    int i;
    bool *a;
    a = malloc(n * sizeof *a);
    for (i = 0; i < n; ++i) {
        a[i] = true;
    }
    *t = a;
}

/**
 * Tworzy tablicę typu char rozmiaru @n wypełnioną spacjami.
 */
void stworzWiersz(char **t, int n) {
    int i;
    char *a;
    a = malloc(n * sizeof *a);
    for (i = 0; i < n; ++i) {
        a[i] = SPACJA;
    }
    *t = a;
}

/**
 * Wypisuje na wyjscie znaki z tablicy @t.
 */
void wypisz(char t[], int n) {
    int i;
    for (i = 0; i < n; ++i) {
        putchar(t[i]);
    }
    putchar(KONIEC_WIERSZA);
}
/**
 * Sprawdza, czy wiersz o numerze @w moze zotac wybrany.
 */
bool czyMoznaWybrac(int wiersze[], int kolumny[], char wynikowy[], int w) {
    int i = wiersze[w];
    bool war = true;
    while (i < wiersze[w + 1] && war) {
        if (wynikowy[kolumny[i]] != SPACJA) {
            war = false;
        }
        ++i;
    }
    return war;
}

/**
 * Wpisuje wiersz o numerze @w do wiersza wynikowego.
 */

void wpiszWiersz(int wiersze[], int kolumny[], char znaki[], char wynikowy[],
                 int w, int *dost) {
    int i = wiersze[w];
    while (i < wiersze[w + 1]) {
        wynikowy[kolumny[i]] = znaki[i];
        --(*dost);
        ++i;
    }
}

/**
 * Usuwa wiersz o numerze @w z wiersza wynikowego.
 */

void usunWiersz(int wiersze[], int kolumny[], char wynikowy[], int w) {
    int i = wiersze[w];
    while (i < wiersze[w + 1]) {
        wynikowy[kolumny[i]] = SPACJA;
        ++i;
    }
}

/**
 * Usuwa dynamiczną tablicę tablic rozmiaru @n
 */
void usunTabKol(int **wierszeWKol, int n) {
    int i;
    for (i = 0; i < n; ++i) {
        free(wierszeWKol[i]);
    }
    free(wierszeWKol);
}

/**
 * Na wszystkie możliwe sposoby dobiera wiersze do określonej kolumny 
 * i wypisuje na wyjscie wszystkie mozliwe wiersze wynikowe.
 */

void wybierz(int wiersze[], int kolumny[], char znaki[], int **wierszeWKol,
             bool niewybrane[], int dost, char wynikowy[], int dl, int k) {
    if (dost == 0) {
        wypisz(wynikowy, dl);
    } else if (k < dl) {
        if (wynikowy[k] != ' ') {
            wybierz(wiersze, kolumny, znaki, wierszeWKol, niewybrane, dost,
                    wynikowy,
                    dl, k + 1);
        } else {
            int i = 0;
            int pom = dost;
            while (wierszeWKol[k][i] != -1) {
                if (niewybrane[wierszeWKol[k][i]] && czyMoznaWybrac(wiersze,
                                                                    kolumny,
                                                                    wynikowy,
                                                                    wierszeWKol[k][i])) {
                    niewybrane[wierszeWKol[k][i]] = false;
                    wpiszWiersz(wiersze, kolumny, znaki, wynikowy,
                                wierszeWKol[k][i], &pom);
                    wybierz(wiersze, kolumny, znaki, wierszeWKol, niewybrane,
                            pom,
                            wynikowy, dl, k + 1);

                    usunWiersz(wiersze, kolumny, wynikowy, wierszeWKol[k][i]);
                    niewybrane[wierszeWKol[k][i]] = true;
                    pom = dost;
                }
                ++i;
            }
        }
    }
}

/**
 * Odpowiada za wykonanie programu.
 */
void wykonaj(void) {
    bool *niewybrane;
    char *znaki, *wynikowy;
    int *wiersze, *kolumny;
    int **wierszeWKol;
    int maxDl, ilWier;
    wczytaj(&wiersze, &kolumny, &znaki, &maxDl, &ilWier);
    if (maxDl > 0) {
        stworzTabKol(&wierszeWKol, kolumny, wiersze, maxDl, ilWier);
        stworzWiersz(&wynikowy, maxDl);
        stworzTabPrawda(&niewybrane, ilWier);

        wybierz(wiersze, kolumny, znaki, wierszeWKol, niewybrane, maxDl,
                wynikowy,
                maxDl, 0);

        usunTabKol(wierszeWKol, maxDl);
        free(wynikowy);
        free(niewybrane);
    }

    free(znaki);
    free(wiersze);
    free(kolumny);
}

int main(void) {
    wykonaj();
    return 0;
}


