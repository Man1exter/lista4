// 1) Tytuł programu:
// Baza danych studentów.
// Program będzie bazą danych studentów WSZEdukacja.
// Dane studentów zostaną zapisane w tablicyobiektów klasyStudentEdukacja(należy rozbudować klasę o składowe danych przechowujące informacje o wybranych cechach studenta).
// 2) Po uruchomieniu, program przeczyta dane studentów z pliku (jeżeli wcześniej taki plik zostałutworzony).
// 3) Następnie program umożliwi wybór następujących funkcji poprzez naciśnięcieodpowiedniego przycisku na klawiaturze:
// <L> wylistowanie nazwisk, imion i wieku wszystkich studentów posortowanych wedługnumeru_indeksu;
// <D> dodanie nowego studenta oraz wprowadzenie wszystkich cech go opisujących;
// <U> usunięcie studenta;
// <K> zakończenie programu i zapisanie bazy studentów do pliku.

#include <iostream>
#include <string>
#include <stdio.h>
#include <vector>
#include <conio.h>
#include <algorithm>
#include <cctype>
#include <fstream>
#include <iterator> // wskaznik na okreslony element vectora


using namespace std;

const int N = 20;
int iloscStu = 0;

void menu();

class Osoba{
public:
 string imie;
 string nazwisko;
 int wiek;
 void pokaz_dane();
};

void Osoba::pokaz_dane(){
 cout << "Imie " + imie << endl;
 cout << "Nazwisko " + nazwisko << endl;
 cout << "Wiek " << wiek << endl;
 cout << endl;
}

class Student: public Osoba{
public:
 string grupa;
 void pokaz_dane();
};

void Student::pokaz_dane() {
 cout << "student" <<endl;
 cout << "Imie " + imie << endl;
 cout << "Nazwisko " + nazwisko << endl;
 cout << "Wiek " << wiek << endl;
 cout << "Grupa " + grupa << endl;
 cout << endl;
}

class StudentEduakcja: public Student{
 friend class StudentsArray;
public:
 int numer_indeksu;
 void podaj_numer_indeksu();
 void pokaz_dane();
 void wpisz_dane();
};

void StudentEduakcja::podaj_numer_indeksu(){
 cout << "podaj numer indeksu ";
 cin >> numer_indeksu;
 cout << endl;
}

void StudentEduakcja::pokaz_dane() {
 cout << "Imie " << imie << endl;
 cout << "Nazwisko " << nazwisko << endl;
 cout << "Wiek " << wiek << endl;
 cout << "Grupa " << grupa << endl;
 cout << "Numer indeksu " << numer_indeksu << endl;
 cout << endl;
}

void StudentEduakcja::wpisz_dane(){
 cout <<"podaj imie ";
 cin >> imie;
 cout <<"podaj nazwiko ";
 cin >> nazwisko;
 cout <<"podaj wiek ";
 cin >> wiek;
 cout <<"podaj grupe ";
 cin >> grupa;
 podaj_numer_indeksu();
}

class TablicaStudentow: public StudentEduakcja{
 friend class ObslugaPliku;
public:
 StudentEduakcja tab[N];
 void wyswietl();
 void usun();
 void dodaj();
 void sort();
 void wczytaj();
 void zapisz();
};

void TablicaStudentow::wyswietl(){
 cout << "Liczba studentow " << iloscStu << "/20" << endl;
 for(int i = 0; i < iloscStu; i++){
 cout << "Student " << i+1 <<" "<<endl;
 tab[i].pokaz_dane();
 }
 menu();
}

void TablicaStudentow::usun(){
 cout << "Ktorego studenta chcesz usunąć? Podaj numer Studenta: ";
 int i;
 cin >> i;
 for (int j = i; j <= iloscStu - 1; j++) {
 tab[j].imie = tab[j + 1].imie;
 tab[j].nazwisko = tab[j + 1].nazwisko;
 tab[j].wiek = tab[j + 1].wiek;
 tab[j].grupa = tab[j + 1].grupa;
 tab[j].numer_indeksu = tab[j + 1].numer_indeksu;
 }
 iloscStu--;
 i--;
 cout << "Student usuniety"<<endl;
 menu();
}

void TablicaStudentow::dodaj(){
 if
(iloscStu == 20) {
 cout << "Wykorzystales limit bazy danych, max ilosc to 20" << endl;
 menu();
}
 tab[iloscStu].wpisz_dane();
 iloscStu++;
 menu(); 
 }

void TablicaStudentow::sort(){
 //sortowanie babelkowe
int n = iloscStu - 1;
for(int i=0;i<iloscStu-1;i++)
for(int j=1;j< n- i ;j++) //pętla wewnętrzna
if(tab[j-1].numer_indeksu>tab[j].numer_indeksu)
//zamiana miejscami
swap(tab[j-1], tab[j]);
}

void TablicaStudentow::zapisz(){
 fstream plik;
 plik.open( "dane.txt", ios::out );
 for( int i =0; i < iloscStu; i++ ) {
 plik << tab[i].imie << endl;
 plik << tab[i].nazwisko << endl;
 plik << tab[i].wiek << endl;
 plik << tab[i].grupa << endl;
 plik << tab[i].numer_indeksu << endl;
}
 plik.close(); 
}

void TablicaStudentow::wczytaj(){
fstream plik;

plik.open
("dane.txt", ios::in);
 if (plik.good() == false){
 cout << "Nie ma takiego pliku" << endl;
 menu();
}
string linia;
int j = 0;
int nr_li = 1;
iloscStu = 0;
while (getline(plik, linia)){
switch (nr_li){
 case 1:
 tab[iloscStu].imie = linia;
 break;
 case 2:
 tab[iloscStu].nazwisko = linia;
 break;
 case 3:
 tab[iloscStu].wiek = atoi(linia.c_str()); 
 break;
 case 4:
 tab[iloscStu].grupa = linia;
 break;
 case 5:
 tab[iloscStu].numer_indeksu = atof(linia.c_str());
 }
 nr_li++;
 if (nr_li > 5) {
 nr_li = 1;
 j++;
 iloscStu = j;
 }
 }
 plik.close();
}

TablicaStudentow arr;

void menu() {
 cout << "L: wylistowanie nazwisk, imion, wieku, grupy i numerze indeksu wszystkich studentów wedlug numerow indeksow" << endl;
 cout << "D: dodanie nowego studenta " << endl;
 cout << "U: usunięcie studenta" << endl;
 cout << "K: zakonczenie programu i zapisanie bazy studentów do pliku" << endl;
 cout << endl;
 cout << "wybierz opcje: " << endl;
 char x;
 cin >> x;
 x = tolower(x);
 switch (x){
    case 'l':
 arr.sort();
 arr.wyswietl();
 break
;
 case 'd':
 arr.dodaj();
 arr.sort();
 break
;
 case 'u':
 arr.sort();
 arr.wyswietl();
 arr.usun();
 break
;
 case 'k':
 arr.zapisz();
 break
;
 default:
 break
;

}
}

int main(){
 arr.wczytaj();
 menu();
 return 0;
}
