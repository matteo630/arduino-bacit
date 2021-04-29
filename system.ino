// mise en place des librairies nécéssaires

#include <Keypad.h>
#include <LiquidCrystal.h>
#include <Servo.h>

Servo myservo;
int pos=0; // LCD Connexion
LiquidCrystal lcd(A0,A1,A2,A3,A4,A5);
const byte rows=4;
const byte cols=3;

char key[rows][cols]={
{'1','2','3'},
{'4','5','6'},
{'7','8','9'},
{'*','0','#'}
};
byte rowPins[rows]={1,2,3,4};
byte colPins[cols]={5,6,7};
Keypad keypad= Keypad(makeKeymap(key),rowPins,colPins,rows,cols);
char* password="4567";
int currentposition=0;
int redled=10;
int greenled=11;
int buzz=8;
int invalidcount=12;



void setup()
{

displayscreen();
Serial.begin(9600);
pinMode(redled, OUTPUT);
pinMode(greenled, OUTPUT);
pinMode(buzz, OUTPUT);
myservo.attach(9); //SERVOMOTEUR ATTACHÉ//

lcd.begin(16,2);

}

void loop()
{
if( currentposition==0)
{
displayscreen();

}
int l ;
char code=keypad.getKey();
if(code!=NO_KEY)
{
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Mot de passe :");
lcd.setCursor(7,1);
lcd.print(" ");
lcd.setCursor(7,1);
for(l=0;l<=currentposition;++l)
{

lcd.print("*");
keypress();
}

if (code==password[currentposition])
{
++currentposition;
if(currentposition==4)
{

unlockdoor();
currentposition=0;

}

}

else
{
++invalidcount;
incorrect();
currentposition=0;

}
if(invalidcount==5)
{

++invalidcount;
torture1();

}
if(invalidcount==8)
{
torture2();
}

}
// fin de la boucle
}

//ouverture de la fonction d'entrée

void unlockdoor()
{
delay(900);

lcd.setCursor(0,0);
lcd.println(" ");
lcd.setCursor(1,0);
lcd.print("Acces autorise");
lcd.setCursor(4,1);
lcd.println("BIENVENUE!!");
lcd.setCursor(15,1);
lcd.println(" ");
lcd.setCursor(16,1);
lcd.println(" ");
lcd.setCursor(14,1);
lcd.println(" ");
lcd.setCursor(13,1);
lcd.println(" ");
unlockbuzz();

for(pos = 180; pos>=0; pos-=5) // passe de 180 degrés à 0 degré
{
myservo.write(pos); // dit au servo d'aller à la position de la variable 'pos'.
delay(5); // attend 15ms pour que le servo atteigne la position.
}
delay(2000);



delay(1000);
counterbeep();

delay(1000);

for(pos = 0; pos <= 180; pos +=5) // va de 0 à 180 degrés
{ // par étapes de 1 degré en 1 degré
myservo.write(pos); // dit au servo d'aller à la position de la variable 'pos'.
delay(15);


currentposition=0;

lcd.clear();
displayscreen();

}
}

//***FONCTION CODE FAUX

void incorrect()
{
delay(500);
lcd.clear();
lcd.setCursor(1,0);
lcd.print("CODE");
lcd.setCursor(6,0);
lcd.print("INCORRECT");
lcd.setCursor(15,1);
lcd.println(" ");
lcd.setCursor(4,1);
lcd.println("PARTEZ!!!");

lcd.setCursor(13,1);
lcd.println(" ");
Serial.println("CODE INCORRECT VOUS N'ÊTES PAS AUTORISÉ");
digitalWrite(redled, HIGH);
digitalWrite(buzz, HIGH);
delay(3000);
lcd.clear();
digitalWrite(redled, LOW);
digitalWrite(buzz,LOW);
displayscreen();
}
//fonction nettoyage de l'écran
void clearscreen()
{
lcd.setCursor(0,0);
lcd.println(" ");
lcd.setCursor(0,1);
lcd.println(" ");
lcd.setCursor(0,2);
lcd.println(" ");
lcd.setCursor(0,3);
lcd.println(" ");
}
//******************************KEYPRESS***********************************//
void keypress()
{



digitalWrite(buzz, HIGH);
delay(50);
digitalWrite(buzz, LOW);
}
//********************************FONCTION D'AFFICHAGE!!!***********************************************************//
void displayscreen()
{

lcd.setCursor(0,0);
lcd.println("*ENTRER LE CODE*");
lcd.setCursor(1 ,1);

lcd.println("POUR _/_ (OUVRIR))!!");
}
//*************************** ARM SERVO****************************************************************************//
void armservo()
{

for (pos=180;pos<=180;pos+=50)
{
myservo.write(pos);
delay(5);
}
delay(5000);

for(pos=180;pos>=0;pos-=50)
{
myservo.write(pos);
}

}
//********************************DÉBLOQUEZ LE BUZZ***********************************//
void unlockbuzz()
{

digitalWrite(buzz, HIGH);
delay(80);
digitalWrite(buzz, LOW);
delay(80);
digitalWrite(buzz, HIGH);
delay(80);
digitalWrite(buzz, LOW);
delay(200);
digitalWrite(buzz, HIGH);
delay(80);
digitalWrite(buzz, LOW);
delay(80);
digitalWrite(buzz, HIGH);
delay(80);
digitalWrite(buzz, LOW);
delay(80);
}

//*******************************COUNTER BEEP*************************************//
void counterbeep()
{
delay(1200);


lcd.clear();
digitalWrite(buzz, HIGH);

lcd.setCursor(2,15);
lcd.println(" ");
lcd.setCursor(2,14);
lcd.println(" ");
lcd.setCursor(2,0);
delay(200);
lcd.println("ENTREZ DANS:::");

lcd.setCursor(4,1);
lcd.print("5");
delay(200);
lcd.clear();
lcd.setCursor(2,0);
lcd.println("ENTREZ DANS:");
digitalWrite(buzz,LOW);
delay(1000);
//2
digitalWrite(buzz, HIGH);
lcd.setCursor(2,0);
lcd.println("ENTREZ DANS:");
lcd.setCursor(4,1); //2
lcd.print("4");
delay(100);
lcd.clear();
lcd.setCursor(2,0);
lcd.println("GET IN WITHIN:");
digitalWrite(buzz,LOW);
delay(1000);
//3
digitalWrite(buzz, HIGH);
lcd.setCursor(2,0);
lcd.println("ENTREZ DANS:");
lcd.setCursor(4,1); //3
lcd.print("3");
delay(100);
lcd.clear();
lcd.setCursor(2,0);
lcd.println("ENTREZ DANS:");
digitalWrite(buzz,LOW);
delay(1000);
//4
digitalWrite(buzz, HIGH);
lcd.setCursor(2,0);
lcd.println("ENTREZ DANS:");
lcd.setCursor(4,1); //4
lcd.print("2");
delay(100);
lcd.clear();
lcd.setCursor(2,0);
lcd.println("ENTREZ DANS:");
digitalWrite(buzz,LOW);
delay(1000);
//
digitalWrite(buzz, HIGH);
lcd.setCursor(4,1);
lcd.print("1");
delay(100);
lcd.clear();
lcd.setCursor(2,0);
lcd.println("ENTREZ DANS::");
digitalWrite(buzz,LOW);
delay(1000);
//5
digitalWrite(buzz, HIGH);
delay(40);
digitalWrite(buzz,LOW);
delay(40);
digitalWrite(buzz, HIGH);
delay(40);
digitalWrite(buzz,LOW);
delay(40);
digitalWrite(buzz, HIGH);
delay(40);
digitalWrite(buzz,LOW);
delay(40);
digitalWrite(buzz, HIGH);
delay(40);
digitalWrite(buzz,LOW);
lcd.clear();
lcd.setCursor(2,0);
lcd.print("VEROUILLAGE");
delay(500);
lcd.setCursor(12,0);
lcd.print(".");
delay(500);
lcd.setCursor(13,0);
lcd.print(".");
delay(500);
lcd.setCursor(14,0);
lcd.print(".");
delay(400);
lcd.clear();
lcd.setCursor(4,0);
lcd.print("LOCKED!");
delay(440);
}
//*****************************TORTURE1****************************************//
void torture1()
{
delay(1000);
lcd.clear();
lcd.setCursor(2,0);
lcd.print("ATTENDEZ POUR ");
lcd.setCursor(5,1);
lcd.print("15 SECONDES");
digitalWrite(buzz, HIGH);
delay(15000);
digitalWrite(buzz, LOW);
lcd.clear();
lcd.setCursor(2,0);
lcd.print("LOL..");
lcd.setCursor(1,1);
lcd.print(" COMMENT C'ÉTAIT ?");
delay(3500);
lcd.clear();

}
//******************************TORTURE2*****************************************//
void torture2()
{
delay(1000);
lcd.setCursor(1,0);
lcd.print(" ");
lcd.setCursor(2,0);
lcd.print("LES TAMBOURS D'OREILLE SONT");
lcd.setCursor(0,1);
lcd.print(" PRECIEUX!! ");
delay(1500);
lcd.clear();
lcd.setCursor(1,0);
lcd.print(" ATTENDEZ POUR");
lcd.setCursor(4,1);
lcd.print(" 1 MINUTE");
digitalWrite(buzz, HIGH);
delay(55000);
counterbeep();
lcd.clear();
digitalWrite(buzz, LOW);
lcd.setCursor(2,0);
lcd.print("TU VEUX QUE JE TE CONTREDISE");
lcd.setCursor(1,1);
lcd.print("ENCORE PLUS ?");
delay(2500);
lcd.clear();
lcd.setCursor(2,0);
lcd.print("Ha Ha Ha Ha");
delay(1700);
lcd.clear();
}