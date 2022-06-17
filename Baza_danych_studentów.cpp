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
int ileStudentow = 0;

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
 cout << "podaj numer indeksu podawanego studenta";
 cin >> numer_indeksu;
 cout << endl;
}

void StudentEduakcja::pokaz_dane() {
 cout << "Imie studenta " << imie << endl;
 cout << "Nazwisko studenta" << nazwisko << endl;
 cout << "Wiek studenta" << wiek << endl;
 cout << "Grupa studenta" << grupa << endl;
 cout << "Numer indeksu studenta" << numer_indeksu << endl;
 cout << endl;
}

void StudentEduakcja::wpisz_dane(){
 cout <<"podaj imie studenta";
 cin >> imie;
 cout <<"podaj nazwiko studenta";
 cin >> nazwisko;
 cout <<"podaj wiek studenta";
 cin >> wiek;
 cout <<"podaj grupe studenta";
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
 cout << "Aktualna Liczba studentow " << ileStudentow << "na mozliwych 20 studentow" << endl;
 for(int i = 0; i < ileStudentow; i++){
 cout << "Student " << i+1 <<" "<<endl;
 tab[i].pokaz_dane();
 }
 menu();
}

void TablicaStudentow::usun(){
 cout << "USUWANIE STUDENTA Podaj numer Studenta: ";
 int i;
 cin >> i;
 for (int j = i; j <= ileStudentow - 1; j++) {
 tab[j].imie = tab[j + 1].imie;
 tab[j].nazwisko = tab[j + 1].nazwisko;
 tab[j].wiek = tab[j + 1].wiek;
 tab[j].grupa = tab[j + 1].grupa;
 tab[j].numer_indeksu = tab[j + 1].numer_indeksu;
 }
 ileStudentow--;
 i--;
 cout << "Student został pomyślnie usuniety"<<endl;
 menu();
}

void TablicaStudentow::dodaj(){
 if
(ileStudentow == 20) {
 cout << "Wykorzystales limit bazy danych, max ilosc to 20" << endl;
 menu();
}
 tab[ileStudentow].wpisz_dane();
 ileStudentow++;
 menu(); 
 }

void TablicaStudentow::sort(){
 //sortowanie babelkowe
int n = ileStudentow - 1;
for(int i=0;i<ileStudentow-1;i++)
for(int j=1;j< n- i ;j++) //pętla wewnętrzna
if(tab[j-1].numer_indeksu>tab[j].numer_indeksu)
//zamiana miejscami
swap(tab[j-1], tab[j]);
}

void TablicaStudentow::zapisz(){
 fstream plik;
 plik.open( "dane.txt", ios::out );
 for( int i =0; i < ileStudentow; i++ ) {
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
 cout << "Nie ma takiego pliku do wyszukania" << endl;
 menu();
}
string linia;
int j = 0;
int nr_li = 1;
ileStudentow = 0;
while (getline(plik, linia)){
switch (nr_li){
 case 1:
 tab[ileStudentow].imie = linia;
 break;
 case 2:
 tab[ileStudentow].nazwisko = linia;
 break;
 case 3:
 tab[ileStudentow].wiek = atoi(linia.c_str()); 
 break;
 case 4:
 tab[ileStudentow].grupa = linia;
 break;
 case 5:
 tab[ileStudentow].numer_indeksu = atof(linia.c_str());
 }
 nr_li++;
 if (nr_li > 5) {
 nr_li = 1;
 j++;
 ileStudentow = j;
 }
 }
 plik.close();
}

TablicaStudentow arr;

void menu() {
 cout << "--------------------------------------------------------------------" << endl;
 cout << "--------------------------------------------------------------------" << endl;
 cout << "--- [ L ] Wylistowanie nazwisk, imion, wieku, grupy i indexu studentow ---" << endl;
 cout << "--------------------------------------------------------------------" << endl;
 cout << "--- [ D ] Dodanie nowego studenta do pliku glownego w katalogu ---" << endl;
 cout << "--------------------------------------------------------------------" << endl;
 cout << "--- [ U ] Usunięcie studenta z pliku glownego w katalogu ---" << endl;
 cout << "--------------------------------------------------------------------" << endl;
 cout << "--- [ K ] Zakonczenie programu i zapisanie bazy studentów do pliku ---" << endl;
 cout << "--------------------------------------------------------------------" << endl;
 cout << "--------------------------------------------------------------------" << endl;
 cout << endl;
 cout << "wybierz opcje: " << endl;

 char x;
 cin >> x;

 x = tolower(x);
 switch (x){
    case 'l':
 arr.sort();
 arr.wyswietl();
 break;
 case 'd':
 arr.dodaj();
 arr.sort();
 break;
 case 'u':
 arr.sort();
 arr.wyswietl();
 arr.usun();
 break;
 case 'k':
 arr.zapisz();
 break;
 default:
 break;
}
}

int main(){
 arr.wczytaj();
 menu();
 return 0;
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ZADANIE ZMODYFIKOWANE Z ZADANIEM Z TAMTEGO ROKU Z LIST ZADAN
// PRZYKLAD ZADANIA GOTOWEGO Z TAMTEGO ROKU
// #include <iostream>
// #include <string>
// #include <stdio.h>
// #include <vector>
// #include <conio.h>
// #include <algorithm>
// #include <cctype>
// #include <fstream>
// #include <iterator> // wskaznik na okreslony element vectora

// using namespace std;

// #define KEY_L 76 //- alfabetyczny porzadek
// #define KEY_K 75 //- zapis studentow i pliku
// #define KEY_U 85 //- usuniecie studenta z 2.5 srocen
// #define KEY_D 68 //- dodanie nowego studenta(im,nazw,wiek,sro,nralb)
// #define KEY_X 88 //- wyjscie

// struct Osoba{

//     string imie;
//     string nazwisko;
//     int nrAlbumu;
//     float srOcen;
//     int wiek;
//     bool operator < (const Osoba &x)const
//     {
//         return nazwisko>x.nazwisko;
//     }
// };

// void ograniczenie(int &liczbaMax){
// cout << "Ilu studentow chcesz dodac(nie wiecej niz 20)?" << endl;
// cin >> liczbaMax;

// if(liczbaMax > 20 ){
//     cout << endl;
//     cout << "nie moze byc wieksza niz 20!" << endl;
//     cout << "popraw sie: " << endl;
//     cin >> liczbaMax;
// }
// }

// void menu(){
//      cout << "---------------------------------------" << endl;
//      cout << "---- U - USUWA STUDENTA ZE SREDNIA <= 2.5" << endl;
//      cout << "---- L - LISTUJE NAZWISKA I SORTUJE" << endl;
//      cout << "---- K - ZAPISUJE AKTUALNY STAN I WYCHODZI Z PROGRAMU" << endl;
//      cout << "---- D - DODAJE NOWEGO STUDENTA" << endl;
//      cout << "---- X - WYCHODZI CALKOWICIE Z PETLI" << endl;
//      cout << "---- NP. Q - PRZECHODZI DO WYJSCIA" << endl;
//      cout << "---------------------------------------" << endl;
//  }

// void dodawanieAll(int liczbaMax, vector<Osoba>&);
// void usuwanie(int liczbaMax, vector<Osoba>&);
// void dodawanieNowego(int liczbaMax,int &liczbaMaxNowych, vector<Osoba>&);
// void sortowanieStudentow(int liczbaMax,int liczbaMaxNowych, vector<Osoba>&);
// void zapisDoPliku(int liczbaMax, int liczbaMaxNowych, vector<Osoba>&);
// void odczytPliku(int liczbaMax, int liczbaMaxNowych, vector<Osoba>&);

// int main(){

//     fstream plikBazy;
// vector<Osoba> studenci(20); 

// int liczbaMax;
// int liczbaMaxNowych;
// int wybor;

// ograniczenie(liczbaMax);
// dodawanieAll(liczbaMax, studenci);
// menu(); // bez paramaetrowy void z prostym menu

// char key = getch();
// int value = key;
// int nowe;

// while(value != KEY_X){ // x - wyjscie z petli calkowicie
//     switch(getch()){
//         case KEY_L : //listowanie + duza litera calych imion i nazwisk
//         sortowanieStudentow(liczbaMax, liczbaMaxNowych, studenci);
//         break;

//         case KEY_D : //dodawanie ucznia > 20 uczniow w grupie/ na liscie
//         dodawanieNowego(liczbaMax,liczbaMaxNowych, studenci);
//         break;

//         case KEY_U : //usuniecie studenta ze srocen 2.5 lub mniej
//         usuwanie(liczbaMax, studenci);
//         break;

//         case KEY_K : //zapis aktualnego stanu - do pliku + zakonczenie programu
//         zapisDoPliku(liczbaMax,liczbaMaxNowych,studenci);
//         break;
        
//         default: //wyjscie
//         cout << "pamietaj o zapisie do pliku klucz kod - K , bo utracisz wszystkie zapisy" << endl;
//         cout << "wychodzisz czy chcesz zobaczyc swoich studentow?  [ 1 - (studenci) / 0 - (wyjscie) ]"  << endl;
//         cin >> wybor;
//          // odczyt z pliku
//         if(wybor == 0){
//             cout << "zakonczyles program, milego dnia..." << endl;
//             return 0;
//         } else {
//             odczytPliku(liczbaMax,liczbaMaxNowych,studenci);
//        }
//     }
// }

// key = getch();
// value = key;

//     return 0;
// }

// void dodawanieAll(int liczbaMax, vector<Osoba>& studenci){

//     int i;

//     for(i = 1; i < liczbaMax + 1; i++){
//     cout << "podaj imie " << i << " studenta:"<< endl;
//     cin >> studenci[i].imie;

//     cout << "podaj nazwisko " << i << " studenta:"<< endl;
//     cin >> studenci[i].nazwisko;

//     cout << "podaj numer albumu " << i << " studenta:"<< endl;
//     cin >> studenci[i].nrAlbumu;

//     cout << "podaj srednia ocen " << i << " studenta:"<< endl;
//     cin >> studenci[i].srOcen;

//     cout << "podaj wiek " << i << " studenta:"<< endl;
//     cin >> studenci[i].wiek;

// }

//     cout << "Twoi studenci: " << endl;
//     cout << endl;

// for(int i = 1; i < liczbaMax + 1; i++){   
// cout <<"Studenci: "<< studenci[i].imie <<" "<< studenci[i].nazwisko <<" ma lat "<< studenci[i].wiek <<" numer albumu: "<< studenci[i].nrAlbumu <<" oraz srednia ocen to: "<< studenci[i].srOcen << endl;
// }
// }

// void usuwanie(int liczbaMax, vector<Osoba>& studenci){
//     int i;

// for(int i = 1; i < liczbaMax + 1; i++){   

//     if(studenci[i].srOcen <= 2.5){
//         cout << "usuniesz studenta ze srednia mniejsza lub rowna 2.5" << endl;

//         cout << endl;

//         cout <<"Student: "<< studenci[i].imie <<" "<< studenci[i].nazwisko <<" ma lat "<< studenci[i].wiek <<" numer albumu: "<< studenci[i].nrAlbumu <<" oraz srednia ocen to: "<< studenci[i].srOcen << endl;

//         cout << endl;
        
//         studenci.erase(studenci.begin() + i);

//         cout << "student zostal usuniety" << endl;

//     } else {
//         cout << "nie znaleziono studenta ze srednia ocen mniejsza lub rowna 2.5" << endl;
//     }
//    }
//    return;
//  }

// void dodawanieNowego(int liczbaMax,int &liczbaMaxNowych, vector<Osoba>& studenci){

// cout << "Ilu nowych studentow chcesz dodac(nie wiecej niz 20)?" << endl;
// cin >> liczbaMaxNowych;

// if(liczbaMaxNowych > 20 ){
//     cout << endl;
//     cout << "nie moze byc wieksza niz 20!" << endl;
//     cout << "popraw sie: " << endl;
//     cin >> liczbaMaxNowych;
// }

// int i;
//     for(i = 1 + liczbaMax; i < liczbaMaxNowych + 1 + liczbaMax; i++){
//     cout << "podaj imie " << i - liczbaMax << " nowego studenta:"<< endl;
//     cin >> studenci[i].imie;
    
//     cout << "podaj nazwisko " << i - liczbaMax << " nowego studenta:"<< endl;
//     cin >> studenci[i].nazwisko;
    
//    cout << "podaj numer albumu " << i - liczbaMax << " nowego studenta:"<< endl;
//     cin >> studenci[i].nrAlbumu;
    
//     cout << "podaj srednia ocen " << i - liczbaMax << " nowego studenta:"<< endl;
//     cin >> studenci[i].srOcen;
    
//     cout << "podaj wiek " << i - liczbaMax << " nowego studenta:"<< endl;
//     cin >> studenci[i].wiek;
// }

//    cout << "nowy student / studenci zostal / zostali dodani do bazy studentow!" << endl;
//    cout << "wrociles do petli - menu, po zakonczeniu tego switcha" << endl;
//    return;
// }

// void sortowanieStudentow(int liczbaMax, int liczbaMaxNowych, vector<Osoba>& studenci){

//     cout << "Sortowanie studentow!" << endl;

//     for(int i = 1; i < liczbaMax + liczbaMaxNowych + 1; i++){   
//     cout <<"Studenci przed sortowaniem: "<< studenci[i].imie <<" "<< studenci[i].nazwisko <<" ma lat "<< studenci[i].wiek <<" numer albumu: "<< studenci[i].nrAlbumu <<" oraz srednia ocen to: "<< studenci[i].srOcen << endl;
//     }

//     sort(studenci.begin(),studenci.end());

//     cout << endl;
//     for(int i = 1; i < liczbaMax + liczbaMaxNowych + 1; i++){   
//     cout <<"Studenci po sortowaniu: "<< studenci[i].imie <<" "<< studenci[i].nazwisko <<" ma lat "<< studenci[i].wiek <<" numer albumu: "<< studenci[i].nrAlbumu <<" oraz srednia ocen to: "<< studenci[i].srOcen << endl;
//     }
//     cout << endl;
//     return;
// }

// void zapisDoPliku(int liczbaMax, int liczbaMaxNowych, vector<Osoba>& studenci){

//     ofstream plikBazy;
//     plikBazy.open( "base.txt", ios::out | ios::app);

//     for(int i = 1; i < liczbaMax + liczbaMaxNowych + 1; i++){   
//     plikBazy << studenci[i].imie <<" "<< studenci[i].nazwisko <<" ma lat "<< studenci[i].wiek <<" numer albumu: "<< studenci[i].nrAlbumu <<" oraz srednia ocen to: "<< studenci[i].srOcen << endl;
//     }

//     plikBazy.close();
//     cout << "zapisano!" << endl;
//     return;
// }
// void odczytPliku(int liczbaMax, int liczbaMaxNowych, vector<Osoba>& studenci){

//     ifstream plikBazy;

//         plikBazy.open( "base.txt", ios::in | ios::app);

//         if(plikBazy.is_open())
// 	    {
//         cout << "Aktualna lista studentow wyglada nastepujaco: " << endl;
//         cout << endl;

// 		char wiersz[1000];

// 		while(plikBazy.getline(wiersz,1000)) 
// 		{
// 			cout<< wiersz << endl;
// 		}
//         cout << endl;
// 	    }

//        plikBazy.close();
//        return;
// }