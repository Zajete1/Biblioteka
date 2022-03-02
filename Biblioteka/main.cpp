#include <iostream>
#include <stdio.h>
#include <cstdio>
#include <cstring>
#include <string.h>
#include <conio.h>
#include <cstdlib>
#include <limits>


using namespace std;

int i=0;

int czyInt (int x);

class Ksiazka{
public:
    Ksiazka();
    void dodaj(char *tyt,int rokWyd, char *aut, char *gatunek);
    void wyswietl();
    void wyczyscKsiazke();
    char* getTyt();
    int getRokWyd();
    char* getAut();
    char* getGat();
protected:
    char tytul[60];
    int rokWydania;
    char autor[30];
    char gatunek[30];
};

class Biblioteka:public Ksiazka
{
protected:
    Ksiazka *ksiaz;
    Ksiazka *znalezione;
    int licznosc;
    int licznoscZnalezione;
    int rozmiar;
    int current;
    int currentZnalezione;
public:
    Biblioteka();
    void dodajKsiazke(char *tyt,int rokWyd, char *aut, char *gat);
    void wyswietlWszystko();
    void save();
    void read();
    void setCurrent(int index);
    void showCurrent();
    void next();
    void previous();
    void deleteCurrent();
    bool szukajRokWydania(int minimum, int maximum);
    bool szukajTytul(char *tytul);
    void previousZnalezione();
    void nextZnalezione();
    void showCurrentZnalezione();
    void sortowanie();
};

Ksiazka::Ksiazka(): tytul(""),autor(""),rokWydania(0),gatunek("")
    {
    }

    char* Ksiazka::getTyt()
    {
        return tytul;
    }
    int Ksiazka::getRokWyd()
    {
        return rokWydania;
    }
    char* Ksiazka::getAut()
    {
        return autor;
    }
    char* Ksiazka::getGat()
    {
        return gatunek;
    }

void Ksiazka::wyswietl()
{
    cout <<"Tytul: " << tytul << ", rok wydania: " << rokWydania << ", autor: "<< autor
    <<", gatunek: " << gatunek << endl;

}

void Ksiazka::dodaj(char *tyt,int rokWyd, char *aut, char *gat)
{
strcpy(tytul,tyt);
rokWydania=rokWyd;
strcpy(autor,aut);
strcpy(gatunek,gat);

}

void Ksiazka::wyczyscKsiazke()
{
    strcpy(tytul, "");
    rokWydania=0;
    strcpy(autor, "");
    strcpy(gatunek, "");

}

Biblioteka::Biblioteka(){
    this->rozmiar=100;
    ksiaz= new Ksiazka[rozmiar];
    znalezione = new Ksiazka [rozmiar];
    for(i=0;i<rozmiar;i++)
        ksiaz[i].wyczyscKsiazke();
    licznosc=0;
    licznoscZnalezione=0;
    current=-1;
    currentZnalezione=-1;
}

void Biblioteka::wyswietlWszystko()
{
  for (i=0;i<licznosc;i++)
    ksiaz[i].wyswietl();
}
void Biblioteka::deleteCurrent()
{
    if(licznosc>=1)
    {
        for(i=current; i<licznosc-1;i++)
            ksiaz[i]=ksiaz[i+1];
        if(current==licznosc-1)
            current--;
        licznosc--;
    }
}
void Biblioteka::dodajKsiazke(char *tyt,int rokWyd, char *aut, char *gat)
{
 if(licznosc<rozmiar)
 {
     ksiaz[licznosc].dodaj(tyt,rokWyd,aut,gat);
     licznosc++;
 }
}

void Biblioteka::save()
{
    FILE *fp;
    fp=fopen("dane.dat","wb");
    fwrite(&rozmiar,sizeof(rozmiar),1,fp);
    fwrite(&licznosc,sizeof(licznosc),1,fp);
    for(i=0;i<licznosc;i++)
        fwrite(&ksiaz[i],sizeof(ksiaz[i]),1,fp);
    fclose(fp);
}
void Biblioteka::read()
{
    FILE *fp;
    fp=fopen("dane.dat","rb");
    fread(&rozmiar,sizeof(rozmiar),1,fp);
    fread(&licznosc,sizeof(licznosc),1,fp);
    for(i=0;i<rozmiar;i++)
        fread(&ksiaz[i],sizeof(ksiaz[i]),1,fp);
    fclose(fp);
}
void Biblioteka::setCurrent(int index)
{
    if(index>=0 && index<licznosc)
        current=index;
}
void Biblioteka::showCurrent()
{
    if (current>=0 && current<rozmiar)
        ksiaz[current].wyswietl();
}
void Biblioteka::next()
{
    if (current<licznosc-1)
        current++;
}
void Biblioteka::previous()
{
    if (current>0)
        current--;
}

void Biblioteka::showCurrentZnalezione()
{
        if (currentZnalezione>=0 && currentZnalezione<rozmiar)
        znalezione[currentZnalezione].wyswietl();
}
void Biblioteka::nextZnalezione()
{
    if (currentZnalezione<licznoscZnalezione-1)
        currentZnalezione++;
}
void Biblioteka::previousZnalezione()
{
    if (currentZnalezione>0)
        currentZnalezione--;
}

bool Biblioteka::szukajRokWydania(int minimum, int maximum)
{
    licznoscZnalezione=0;
    currentZnalezione=-1;
    for (i=0; i<licznosc; i++)
        if(ksiaz[i].getRokWyd()>=minimum && ksiaz[i].getRokWyd()<=maximum)
    {
        znalezione[licznoscZnalezione]=ksiaz[i];
        licznoscZnalezione++;
    }
    if(licznoscZnalezione)
    {
        currentZnalezione=0;
        return 1;
    }else
    return 0;
}

bool Biblioteka::szukajTytul(char *tytulSz)
{
    licznoscZnalezione=0;
    currentZnalezione=-1;
    for (i=0; i<licznosc; i++)
        if(strstr(ksiaz[i].getTyt(),tytulSz))
        {
            znalezione[licznoscZnalezione]=ksiaz[i];
            licznoscZnalezione++;
        }
    if(licznoscZnalezione)
    {
        currentZnalezione=0;
        return 1;
    }else
    return 0;
}

void Biblioteka::sortowanie()
{
    for(i=0;i<licznosc;i++)
        for(int j=1;j<licznosc-i;j++)
            if(ksiaz[j-1].getRokWyd()>ksiaz[j].getRokWyd())
            swap(ksiaz[j-1], ksiaz[j]);
}


int main()
{
    int b, minimum, maximum;
    char *a = new char;
    char *d = new char;
    char *e = new char;
    char *tytulSz = new char;
    int przelacznikMenu, przelacznikMenu2;
    Biblioteka biblio;
    do{do{
    cout << "\t1.Menu wyswietlanie" << endl;
    cout << "\t2.Menu pliki" << endl;
    cout << "\t3.Wyszukiwanie" << endl;
    cout << "\t4.Sortowanie wg roku" << endl;
    cout << "\t5.Wyjdz z programu" << endl;

    cin >> przelacznikMenu;
system("cls");
    switch (przelacznikMenu){

        case 1:
            do{
                        cout << "\t1.Indeks wyswietlanego elementu" << endl;
                        cout << "\t2.Poprzedni" << endl;
                        cout << "\t3.Nastepny" << endl;
                        cout << "\t4.Usun" << endl;
                        cout << "\t5.Wyswietl wszystkie ksiazki" << endl;
                        cout << "\t6.Dodaj nowa ksiazke"<< endl;
                        cout << "\t7.Cofnij do poprzedniego menu" << endl;
                        cin >> przelacznikMenu;
                        system("cls");
                        switch(przelacznikMenu){
                    case 1:
                        cout << "Podaj indeks elementu: ";
                        cin >> i;
                        system("cls");
                        biblio.setCurrent(i);
                        biblio.showCurrent();
                        break;
                    case 2:
                        biblio.previous();
                        biblio.showCurrent();

                        break;
                    case 3:
                        biblio.next();
                        biblio.showCurrent();

                        break;
                    case 4:
                        biblio.deleteCurrent();
                        biblio.showCurrent();

                        break;
                    case 5:
                        biblio.wyswietlWszystko();

                        break;
                    case 6:
                                    //char *tyt,int rokWyd, char *autor, char *gat
                        cout << "tytul: " << endl;
                        cin.ignore();
                        cin.getline(a,60);
                        cout << "rok wydania: " << endl;
                        do{cin >> b;
                        b = czyInt(b);
                        }while (b==0);

                        cout << "autor: " << endl;
                        cin.ignore();
                        cin.getline(d,30);
                        cout << "gatunek ksiazki: " << endl;
                        cin.getline(e,30);
                        biblio.dodajKsiazke(a,b,d,e);
                        system("cls");
                        break;

                        }
                }while (przelacznikMenu != 7);
            break;
        case 2:
                do{
                        cout << "\t1.Zapisz stan do pliku" << endl;
                        cout << "\t2.Wczytaj stan z pliku" << endl;
                        cout << "\t3.Cofnij" << endl;
                        cin >> przelacznikMenu;
                        system("cls");
                        switch(przelacznikMenu){
                    case 1:
                        biblio.save();
                        cout << "Zapisano plik"<< endl;
                        break;
                    case 2:
                        biblio.read();
                        cout << "Wczytano plik" << endl;
                        break;
                        }
                }while (przelacznikMenu != 3);
            break;
        case 3:
            do{
                        cout << "\t1.Wyszukiwanie rokiem wydania" << endl;
                        cout << "\t2.Wyszukiwanie nazwa" << endl;
                        cout << "\t3.W przod" << endl;
                        cout << "\t4.W tyl" << endl;
                        cout << "\t5.Cofnij" << endl;
                        cin >> przelacznikMenu2;
                        system("cls");
                        switch(przelacznikMenu2){
                    case 1:
                        cout << "Podaj zakres roku wydania od: ";
                        do
                        {
                                cin >> minimum;
                                b = czyInt(minimum);
                        }
                        while (minimum==0);
                        cout << " do: ";
                        do
                        {
                            cin >> maximum;
                            b = czyInt(maximum);
                        }
                        while (maximum==0);
                        if(biblio.szukajRokWydania(minimum, maximum))
                            biblio.showCurrentZnalezione();
                        else
                            cout << "Brak ksiazek o podanych kryteriach." << endl;
                        break;
                    case 2:
                        cout << "Podaj szukany tytul: ";
                        cin.ignore();
                        cin.getline(tytulSz,60);
                        if(biblio.szukajTytul(tytulSz))
                            biblio.showCurrentZnalezione();
                        else
                            cout << "Brak ksiazek o podanych kryteriach." << endl;
                        break;
                    case 3:
                        biblio.nextZnalezione();
                        biblio.showCurrentZnalezione();
                        break;
                    case 4:
                        biblio.previousZnalezione();
                        biblio.showCurrentZnalezione();
                        break;
                        }
                }while (przelacznikMenu2 != 5);
            break;
        case 4:
            biblio.sortowanie();

            break;
    }}while (przelacznikMenu!=5);
    cout << "Czy na pewno chcesz wyjsc?" << endl << "\t1. Wyjdz"<< endl << "\t2. Cofnij" << endl;
    cin >> przelacznikMenu;
    system("cls");
    }while(przelacznikMenu!=1);

    return 0;
}



int czyInt(int x)
{
    if(cin.good() && x <2023)
        return x;
    else
    {
        cin.clear();
        cin.ignore(1000,'\n');
        return 0;
    }
}
