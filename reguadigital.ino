#include <NewPing.h>

//Variáveis de Sensores e Componentes//
#define TRIGGER_PINO      2
#define ECHO_PINO         3
#define DISTANCIA_MAXIMA  400

//Criando objetos dos sensores//
NewPing sonar(TRIGGER_PINO,ECHO_PINO,DISTANCIA_MAXIMA);

#include <LCD5110_Basic.h>
//Variáveis de apoio//
int intervalo = 100; //Millisegundos
unsigned long pulso;
int distancia;


/*Cria objeto da classe LCD5110
CLK – Pino 8
DIN – Pino 9
DC – Pino 10
RST – Pino 12
CE – Pino 11
*/
LCD5110 tela(8,9,10,12,11);

//Obtendo as fontes
extern uint8_t SmallFont[];
extern uint8_t MediumNumbers[];
extern uint8_t BigNumbers[];

void setup() {
  
  // put your setup code here, to run once:
  Serial.begin(115200);
  pulso = millis();
  tela.InitLCD();
}

void loop() {
  
  if (millis() >= pulso){
    pulso = pulso + intervalo;
    sonar.ping_timer(echoCheck);
  }

  //distanciacao(retornaDistancia());
}

void echoCheck() { // Timer2 interrupt calls this function every 24uS where you can check the ping status.
  // Don't do anything here!
  if (sonar.check_timer()) { // This is how you check to see if the ping was received.
    // Here's where you can add code.
    Serial.print("Ping: ");
    distancia = retornaDistancia();
    Serial.print(distancia); // Ping returned, uS result in ping_result, convert to cm with US_ROUNDTRIP_CM.
    Serial.println("cm");

     tela.setFont(SmallFont);
      
    tela.print("Temp: ", LEFT, 35);
    tela.printNumI(distancia, RIGHT, 35);
    
  }
  // Don't do anything here! wsdttsfsytgtfs
}
int retornaDistancia(){
  distancia = sonar.ping_result / US_ROUNDTRIP_CM;
  return distancia;
}
