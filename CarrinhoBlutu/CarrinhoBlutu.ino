#define mA 2
#define ma 3

#define mB 4
#define mb 5

#define mC 8
#define mc 9

#define mD 10
#define md 11

void setup()
{

  Serial.begin(9600);

  pinMode(mA, OUTPUT);
  pinMode(ma, OUTPUT);
  pinMode(mB, OUTPUT);
  pinMode(mb, OUTPUT);

  pinMode(mC, OUTPUT);
  pinMode(mc, OUTPUT);
  pinMode(mD, OUTPUT);
  pinMode(mD, OUTPUT);
}

void loop()
{

  char letra; //Variável char para armazenar o caractere recebido

  if (Serial.available()) //Se algo for recebido pela serial do módulo bluetooth
  {

    letra = Serial.read(); //Armazena o caractere recebido na variável letra

    if (letra == 'F' ) //Se o caractere recebido for a letra 'F'
    {
      //Move o carrinho para frente

      digitalWrite(mA, 1);
      digitalWrite(ma, 0);

      digitalWrite(mB, 0);
      digitalWrite(mb, 1);

      digitalWrite(mC, 0);
      digitalWrite(mc, 1);

      digitalWrite(mD, 1);
      digitalWrite(md, 0);
      //==================
    }

    if (letra == 'B') //Se o caractere recebido for a letra 'B'
    {
      //Move o carrinho para trás
      digitalWrite(mA, 0);
      digitalWrite(ma, 1);

      digitalWrite(mB, 1);
      digitalWrite(mb, 0);

      digitalWrite(mC, 1);
      digitalWrite(mc, 0);

      digitalWrite(mD, 0);
      digitalWrite(md, 1);
      //==================
    }

     if (letra == 'L') //Se o caractere recebido for a letra 'R'
    {
      //Move o carrinho para direita
      digitalWrite(mA, 1);
      digitalWrite(ma, 0);

      digitalWrite(mB, 1);
      digitalWrite(mb, 0);

      digitalWrite(mC, 1);
      digitalWrite(mc, 0);

      digitalWrite(mD, 1);
      digitalWrite(md, 0);
      //==================
    }

    if (letra == 'R') //Se o caractere recebido for a letra 'L'
    {
      //Move o carrinho para esquerda
      digitalWrite(mA, 0);
      digitalWrite(ma, 1);

      digitalWrite(mB, 0);
      digitalWrite(mb, 1);

      digitalWrite(mC, 0);
      digitalWrite(mc, 1);

      digitalWrite(mD, 0);
      digitalWrite(md, 1);
      //==================
    }
    if(letra == 'S') {//Se o caractere recebido for a letra 'S'
      digitalWrite(mA, 1);
      digitalWrite(ma, 1);

      digitalWrite(mB, 1);
      digitalWrite(mb, 1);

      digitalWrite(mC, 1);
      digitalWrite(mc, 1);

      digitalWrite(mD, 1);
      digitalWrite(md, 1);
  }
    

  }

}
