#include <SoftwareSerial.h>   //Inlcui a biblioteca SoftwareSerial.h
#include <DualMotor.h> //Inclui a biblioteca DualMotor.h

#define RxD  3 //Define RxD como 3
#define TxD  2 //Define TxD como 2

DualMotor dualmotor; //Instância a DualMotor.h
SoftwareSerial blueToothSerial(RxD,TxD); //Instância a biblioteca SoftwareSerial.h

void setup()
{

  pinMode(13, OUTPUT);
  blueToothSerial.begin(9600);
  
}

void loop()
{
  
  char letra; //Variável char para armazenar o caractere recebido

  if(blueToothSerial.available()) //Se algo for recebido pela serial do módulo bluetooth
  {
 
    letra = blueToothSerial.read(); //Armazena o caractere recebido na variável letra
    //digitalWrite(13, 1);
    if(letra == 'F') //Se o caractere recebido for a letra 'F'
    {
      digitalWrite(13, 1);
      //Move o carrinho para frente
      dualmotor.M1move(255,1);
      dualmotor.M2move(255,1);
      //==================
    }
    
    else if (letra == 'B') //Se o caractere recebido for a letra 'B'
    {
      //Move o carrinho para trás
      dualmotor.M1move(255,0);
      dualmotor.M2move(255,0);
      //==================
    }
    
    else if(letra == 'R') //Se o caractere recebido for a letra 'R'
    {
      //Move o carrinho para direita
      dualmotor.M1move(255,1);
      dualmotor.M2parar();
      //==================
    }
    
    else if (letra == 'L') //Se o caractere recebido for a letra 'L'
    { 
      //Move o carrinho para esquerda
      dualmotor.M1parar();
      dualmotor.M2move(255,1);
      //==================
    }
    
    else if(letra == 'S') //Se o caractere recebido for a letra 'S'
    {
      //Para o carrinho
      dualmotor.M1parar();
      dualmotor.M2parar();
      //==================
    }  
    
  }  
  
}


