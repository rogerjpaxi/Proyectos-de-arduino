/*Para control de Motor PaP modelo 28BYJ-48
 * Se introducen: 
 * Nro pasos(pasos), 
 * Sentido de giro (Der-Izq)
 * Velocidad (rpm)
 * POR Ing Roger Paxi Churata
 */
#include <Stepper.h>    //libreria del Motor PasoaPaso
#include <Keypad.h>     //libreria para leer datos en teclado
#include <LiquidCrystal.h> //Libreria de la pantalla LCD16x2
const byte FILAS =4;     //Se definen el tamaño de teclado Nro Filas
const byte COLS =3;      //Se definen el tamaño de teclado Nro Columnas
char teclas[FILAS][COLS]={ //Se definen los caracteres del teclado
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
  };
  byte pinsFilas[FILAS]={16,17,18,19};//a,b,c,d parametros de conexion de filas del teclado
  byte pinsCols[COLS]={14,15,13};//1,2,3 parametros de conexion de columnas del teclado
  Keypad teclado = Keypad(makeKeymap(teclas),pinsFilas,pinsCols,FILAS,COLS);//mapeo del teclado
  LiquidCrystal lcd(2,3,4,5,6,7); //RS,E,D4,D5,D6,D7 parametros de conexion del objeto lcd
  Stepper mpp(2048,8,10,9,11);//#pasos/rev,A,C,B,D 64x32=2048
void setup() {
  lcd.begin(16,2); //definimos la geometria del objeto lcd
  lcd.blink();     //Para que el cursor parpadee
}
void loop() {
  int numpasos,sentido,vel; //definimos tipos y nombres de datos
  lcd.clear();              //limpiar pantalla
  lcd.print("Num pasos: "); //mostrar Num pasos:
  numpasos=leeNumero();     //lee el numero de datos 
  lcd.setCursor(0,1);       //posiciona el cursor en la 2da linea
  lcd.print("Der[1]/izq[2]"); //muestra el texto Der Izq para sentido de giro
  sentido=leeNumero();       //lee el dato de sentido de giro
  lcd.clear();              //limpia pantalla
  lcd.print("RPM:");        //muestra para ingreso de RPM
  vel=leeNumero();          //lee el dato de velocidad ingresada
  mpp.setSpeed(vel);        //definimos la velocidad del objeto mpp
  if(sentido==1){           //condicion si sentido de giro es Derecho=1
    mpp.step(numpasos);     //ejecuta el numero de pasos 
    }
    else{                   //ejecuta en caso de ser Izquierdo
      mpp.step(-numpasos);  //invierte el sentido 
      }
}
int leeNumero() {         //para la lectura de datos del teclado
  char aux;               //definimos el tipo de caracter del teclado
  int num=0, i=0, p, k, teclas[4];  //definimos objetos 
  //lee los dígitos
  do{
   aux=NO_KEY;
   while(aux==NO_KEY){//Espera que se pulse una tecla
   aux=teclado.getKey();//Lee el teclado
 }
  if(aux != '#'){     //definir como enter al caracter "#"
   lcd.print(aux); 
   teclas[i]=aux & 0x0f;
   i++;
 }
 }while(aux != '#' && i < 4); //Obtiene el valor numérico
   p = i-1;
   int pesos[4] = {1,10,100,1000};
   for(k=0; k < i; ++k){
   num = num + teclas[k]*pesos[p];
   --p;
 }
  return num;
}
 /*Datos adicionales
  * 2048 pasos para una vuelta https://programarfacil.com/blog/arduino-blog/motor-paso-a-paso-uln2003-l298n/
  */
