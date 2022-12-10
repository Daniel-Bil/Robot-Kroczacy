#include <Servo.h>

#define MIN 0
#define MIN2 45
#define MID 90
#define MAX2 135
#define MAX 180

#define trigPin 11
#define echoPin 12
int krok = 1;
float duration, distance;

Servo T1[6];
Servo T2[6];

void setup() {
  // PODLACZENIE SERW HORYZONTALNYCH
  Serial.begin(9600);
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  
  T1[0].attach(2);
  T1[1].attach(3);
  T1[2].attach(4);
  T1[3].attach(5);
  T1[4].attach(6);
  T1[5].attach(7);
  
  // PODLACZENIE SERW VERTYKALNYCH
  T2[0].attach(14);
  T2[1].attach(15);
  T2[2].attach(16);
  T2[3].attach(17);
  T2[4].attach(18);
  T2[5].attach(19);



  // 1. USTAWIENIE SERW DO GORY ustawiamy na MID-> +45/-45 w zaleznosci od serwa
  // Taki robot lezy na ziemi. Teraz bedziemy mogli wstac
  for (int i = 0; i < 45; i++){

    T2[0].write(MID + i);
    T2[1].write(MID - i);

    T2[2].write(MID + i);
    T2[3].write(MID - i);

    T2[4].write(MID + i);
    T2[5].write(MID - i);
    
    delay(15);
  }

  //2 . Postawione wszystkie nogi "rownolegle" teraz robot stoi na ziemi czas przekrecic nogi horyzontalne
   for (int i = 0; i < 45; i+=krok){

    T2[0].write(MAX2 + i);
    T2[1].write(MIN2 - i);

    T2[2].write(MAX2 + i);
    T2[3].write(MIN2 - i);

    T2[4].write(MAX2 + i);
    T2[5].write(MIN2 - i);
    
    delay(15);
  }
  
  delay(15);
  
  // PIERWSZA PARA 0,0
  podnies(T2,0);
  delay(15);
  przekrec_mid(T1,0);
  delay(15);
  opusc(T2,0);
  delay(15);

  // DRUGA PARA 1,1
  podnies(T2,1);
  delay(15);
 przekrec_mid(T1,1);
  delay(15);
  opusc(T2,1);
  delay(15);

  // TRZECIA PARA 2,2
  podnies(T2,2);
  delay(15);
  przekrec_mid(T1,2);
  delay(15);
  opusc(T2,2);
  delay(15);

  // CZWARTA PARA 3,3
  podnies(T2,3);
  delay(15);
  przekrec_mid(T1,3);
  delay(15);
  opusc(T2,3);
  delay(15);

  // PIATA PARA 4,4
  podnies(T2,4);
  delay(15);
  przekrec_mid(T1,4);
  delay(15);
  opusc(T2,4);
  delay(15);

  // SZÓSTA PARA 5,5
  podnies(T2,5);
  delay(15);
  przekrec_mid(T1,5);
  delay(15);
  opusc(T2,5);
  delay(15);

  //3. TERAZ WSZYSTKIE NOGI SA USTAWIONE W POZYCJI MID
  //4. PRZECHODZIMY DO DZIALANIA PROGRAMU
  delay(3);
}

void loop() {
  float d =check_distance();
  if (d > 20){
    idz_tyl(T1,T2);
  }
  else{
    idz_przod(T1,T2);  
  }
  

}



void przekrec_mid(Servo T[6],int n){
      T[n].write(MID);
      delay(15);
}


void przekrec_tyl_mid(Servo T[6], int n){
  for (int i = 0; i < 45; i+=krok){
    if (n == 0 or n == 1 or n == 2){
      T[n].write(MAX2 - i);
    }
    else{
      T[n].write(MIN2 + i);
    }
    delay(15);
  }
}


void przekrec_mid_przod(Servo T[6],int n){
  for (int i = 0; i < 45; i+=krok){
    if (n == 0 or n == 1 or n == 2){
      T[n].write(MID - i);
    }
    else{
      T[n].write(MID + i);
    }
    delay(15);
  }
}


void przekrec_mid_tyl(Servo T[6],int n){
  for (int i = 0; i < 45; i+=krok){
    if (n == 0 or n == 1 or n == 2){
      T[n].write(MID + i);
    }
    else{
      T[n].write(MID - i);
    }
    delay(15);
  }
}

void przekrec_tyl(Servo T[6],int n){
  for (int i = 0; i < 90; i+=krok){
    if (n == 0 or n == 1 or n == 2){
      T[n].write(MIN2 + i);
    }
    else{
      T[n].write(MAX2 - i);
    }
    delay(15);
  }
}

void podnies(Servo T[6],int n){
 for (int i = 0; i < 45; i+=krok){
    if (n == 1 or n == 3 or n == 5){
      T[n].write(MID - i);
    }
    else{
      T[n].write(MID + i);
    }
    delay(15);
  }
}


void opusc(Servo T[6],int n){
 for (int i = 0; i < 55; i+=krok){
    if (n == 1 or n == 3 or n == 5){
      T[n].write(MIN2 + i);
    }
    else{
      T[n].write(MAX2 - i);
    }
    delay(15);
  }
}


void idz_przod(Servo T1[6],Servo T2[6]){

   delay(15);
   for(int i = 0; i < 6; i++){
        podnies(T2,i);
        delay(15);
        przekrec_mid_przod(T1,i);
        delay(15);
        opusc(T2,i);
        delay(15);
   }
   
  for (int i = 0; i < 90; i+=krok){
    
      T1[0].write(MIN2 + i);
      T1[1].write(MIN2 + i);
      T1[2].write(MIN2 + i);
      T1[3].write(MAX2 - i);
      T1[4].write(MAX2 - i);
      T1[5].write(MAX2 - i);
      delay(15);
  }
    
  for(int i = 0; i < 6; i++){
        podnies(T2,i);
        delay(15);
        przekrec_tyl_mid(T1,i);
        delay(15);
        opusc(T2,i);
        delay(15);
   }
  
  // POJEDYNCZO podnosic nogi i stawiac
  // Pozniej przesuwac wszystkie na raz do tylu
}


void idz_tyl(Servo T1[6],Servo T2[6]){

   delay(15);
   for(int i = 0; i < 6; i++){
        podnies(T2,i);
        delay(15);
        przekrec_mid_tyl(T1,i);
        delay(15);
        opusc(T2,i);
        delay(15);
   }
   
  for (int i = 0; i < 90; i+=krok){
    
      T1[0].write(MAX2 - i);
      T1[1].write(MAX2 - i);
      T1[2].write(MAX2 - i);
      T1[3].write(MIN2 + i);
      T1[4].write(MIN2 + i);
      T1[5].write(MIN2 + i);
      delay(15);
  }
    
  for(int i = 0; i < 6; i++){
        podnies(T2,i);
        delay(15);
        przekrec_tyl_mid(T1,i);
        delay(15);
        opusc(T2,i);
        delay(15);
   }
  
  // POJEDYNCZO podnosic nogi i stawiac
  // Pozniej przesuwac wszystkie na raz do tylu
}

float check_distance(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  distance = (duration/2) * 0.0343;
  Serial.print(distance);
  delay(10);
  return distance;
}
