int sensorDireito = 11;
int sensorEsquerdo = 8;
int sensorCentro = 12;

int velocidadeA = 80;
int velocidadeB = 80;

boolean curva = false;
int cont = 0;


int estado_sensor_centro = 0;
int estado_sensor_esquerdo = 0;
int estado_sensor_direito = 0;

#define motorA 3
#define motora 5

#define motorB 6
#define motorb 9

void leSensores(){
  estado_sensor_centro = digitalRead(sensorCentro);
  estado_sensor_direito = digitalRead(sensorDireito);
  estado_sensor_esquerdo = digitalRead(sensorEsquerdo);
  
}
void setup() {
  Serial.begin(9600);


    pinMode(6, OUTPUT);
    pinMode(9, OUTPUT);
  
    pinMode(13, INPUT);
    pinMode(11, INPUT);
    pinMode(12, INPUT);
}

void loop() {

    leSensores();
    if((estado_sensor_centro == 1) && (estado_sensor_direito == 0) && (estado_sensor_esquerdo == 0)){

      
      digitalWrite(motorA, 0);
      analogWrite(motora, velocidadeA);


      analogWrite(motorB, velocidadeB);
      digitalWrite(motorb, 0);

      Serial.println("frente");

    
    }
    leSensores();
    if((estado_sensor_centro == 1) && (estado_sensor_direito == 1) && (estado_sensor_esquerdo == 0)){
      curva = true;
        analogWrite(motorA, velocidadeA);
        digitalWrite(motora, 0);


        analogWrite(motora, velocidadeB);
        digitalWrite(motorb, 0);

        while((estado_sensor_centro == 0) && (estado_sensor_direito == 0) && (estado_sensor_esquerdo == 0) && (curva == true)){
          leSensores();
        }
        if((estado_sensor_centro == 0) && (estado_sensor_direito == 1) && (estado_sensor_esquerdo == 0)){
          curva = false;
          
        }
        
        delay(5);
        
        
    }
    leSensores();
    if((estado_sensor_centro == 1) && (estado_sensor_direito == 0) && (estado_sensor_esquerdo == 1)){
      curva = true;
        //analogWrite(pwm2, 180);
        digitalWrite(motorA, 0);
        analogWrite(motora, velocidadeA);


        digitalWrite(motorB, 0);
        analogWrite(motora, velocidadeB);
        while((estado_sensor_centro == 0) && (estado_sensor_direito == 0) && (estado_sensor_esquerdo == 0) && (curva == true)){
          leSensores();
        }
        if((estado_sensor_centro == 0) && (estado_sensor_direito == 0) && (estado_sensor_esquerdo == 1)){
          curva = false;
          
        }

        
        delay(5);
        
      
    }
    leSensores();
    if((estado_sensor_centro == 0) && (estado_sensor_direito == 0) && (estado_sensor_esquerdo == 0) && (curva == false)){
      digitalWrite(motorA, 1);
      digitalWrite(motora, 1);


      digitalWrite(motorB, 1);
      digitalWrite(motorb, 1);
      
      
      
    }
    
    delay(30);
  
}
