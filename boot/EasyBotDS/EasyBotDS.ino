/*
 * Q1234
 * AUTOR:   BrincandoComIdeias
 * LINK:    https://www.youtube.com/brincandocomideias ; https://cursodearduino.net/
 * SKETCH:  EasyBotDS - Controle PS2
 * VERSÃO:  1.0.0
 * DATA:    27/08/2018
 */

// INCLUSÃO DE BIBLIOTECAS
#include <PS2X_lib.h>
#include <Servo.h>
#include <HCSR04.h>

// DEFINIÇÃO DOS PINOS DOS SERVOS
#define pinServo1 10
#define pinServo2 5
#define pinServo3 6

// DEFINIÇÃO DOS PINOS DO CONTROLE
#define pinClock 2
#define pinComando 4
#define pinAtencao 3
#define pinData 7

// DEFINIÇÃO DOS PINOS DO HC-SR E DISTANCIA MINIMA EM CM PARA SEGURANÇA
#define pinTrig 8
#define pinEcho 9
#define minDist 15

// DEFINIÇÃO DOS PINOS DO SENSOR DE REFLETANCIA
#define pinSensor 11

// DEFINIÇÃO DOS ANGULOS DOS SERVOS
#define positivoMax 0
#define parado 90
#define negativoMax 180


// INSTANCIANDO OBJETOS
Servo servoEsquerda; // SERVO ROTAÇÃO CONTÍNUA MOTOR DA ESTEIRA ESQUERDA 
Servo servoDireita;  // SERVO ROTAÇÃO CONTÍNUA MOTOR DA ESTEIRA DIREITA
Servo servoCabeca;   // SERVO 180º MOTOR DA CABEÇA
PS2X controlePS;             // CONTROLE DE PLAYSTATION 2
HCSR04 sensorDistancia( pinTrig, pinEcho); // SENSOR ULTRASONICO

// INICIANDO VARIÁVEIS GLOBAIS
unsigned long tempoLeitura = 0; // VARIAVEL PARA CONTROLAR TEMPO DE LEITURA DO HCSR04
float distObstaculo = 30;    // VARIÁVEL PARA ARMAZENAR DISTANCIA DOS OBSTÁCULOS
bool terraFirme;             // VÁRIÁVEL PARA CHECAR SE HÁ CHÃO A FRENTE DO ROBO
bool perigo = false;         // VARIÁVEL PARA CONTROLE DE SEGURANÇA

int error = 0;              // CHECAR ERRO NA CONFIGURAÇÃO DO CONTROLE
byte type = 0;              // CHECAR TIPO DE CONTROLE
byte vibrate = 0;           // CONFIGURAR VIBRAÇÃO DO CONTROLE

byte lidoEx;  //GUARDA A LEITURA DO EIXO DO JOYSTICK
byte lidoEy;  //GUARDA A LEITURA DO EIXO DO JOYSTICK
byte lidoDx;  //GUARDA A LEITURA DO EIXO DO JOYSTICK
byte lidoDy;  //GUARDA A LEITURA DO EIXO DO JOYSTICK

byte exAnt;   //GUARDA A ULTIMA POSICAO DO EIXO ANALOGICO PARA COMPARAR COM A ATUAL E FILTRAR PICOS DE INTERFERENCIA
byte eyAnt;   //GUARDA A ULTIMA POSICAO DO EIXO ANALOGICO PARA COMPARAR COM A ATUAL E FILTRAR PICOS DE INTERFERENCIA
byte dxAnt;   //GUARDA A ULTIMA POSICAO DO EIXO ANALOGICO PARA COMPARAR COM A ATUAL E FILTRAR PICOS DE INTERFERENCIA
byte dyAnt;   //GUARDA A ULTIMA POSICAO DO EIXO ANALOGICO PARA COMPARAR COM A ATUAL E FILTRAR PICOS DE INTERFERENCIA

void setup(){  
  //Serial.begin(9600); // INICIA MONITOR SERIAL
  
  // CONFIGURANDO PINOS DOS SERVOS
  servoEsquerda.attach(pinServo1);
  servoDireita.attach(pinServo2);
  servoCabeca.attach(pinServo3);

  // FUNÇÃO PARA INICIAR E CHECAR CONTROLE VERIFICAR NO MONITOR SERIAL SE HÁ ERROS
  checarControle();

  // CONFIGURAÇÃO DO SENSOR DE REFLETÂNCIA
  pinMode(pinSensor, INPUT);
  Serial.begin(115200);  
}

void loop(){
    
  controlePS.read_gamepad(); // LER ESTADO DO CONTROLE DE PS2
  lidoEy = controlePS.Analog(PSS_LY); // ARMAZENA O VALOR LIDO PELO ANALÓGICO DA ESQUERDA NO EIXO Y
  lidoEx = controlePS.Analog(PSS_LX); // ARMAZENA O VALOR LIDO PELO ANALÓGICO DA ESQUERDA NO EIXO X
  lidoDx = controlePS.Analog(PSS_RX); // ARMAZENA O VALOR LIDO NO EIXO X DO ANALÓGICO DA DIREITA   

  if ( (lidoEy == 255) && (eyAnt < 130) ) { lidoEy = eyAnt; eyAnt = 255;} else eyAnt = lidoEy;  //FILTRO DE INTERFERENCIAS
  if ( (lidoEx == 255) && (exAnt < 130) ) { lidoEx = exAnt; exAnt = 255;} else exAnt = lidoEx;  //FILTRO DE INTERFERENCIAS
  if ( (lidoDx == 255) && (dxAnt < 130) ) { lidoDx = dxAnt; dxAnt = 255;} else dxAnt = lidoDx;  //FILTRO DE INTERFERENCIAS
  
  checarPerigo(); // VERIFICA SE TEM PERIGO A FRENTE
  moverEasyds(); // CONTROLA OS SERVOS DE 360° DAS ESTEIRAS
  moverCabeca(); // CONTROLA O SERVO DE 180° DA CABEÇA 
       
  delay(50);
}

//FUNÇÃO MOVIMENTO MANUAL DO EASYDS
void moverEasyds(){
    
  int anguloEy = map(lidoEy, 0 , 255, 0, 180);       // CONVERTE VALORES LIDO PARA A FAIXA DO SERVO
  int anguloEx = map(lidoEx, 0 , 255, -90, 90);      // CONVERTE VALORES LIDO PARA A FAIXA DE AJUSTE DE DIRECAO COM ZERO NO CENTRO
  
  int anguloServoE = anguloEy - anguloEx;  //DESCONTA O EIXO X PARA AJUSTAR A DIREÇAO
  int anguloServoD = anguloEy + anguloEx;  //SOMA O EIXO X PARA AJUSTAR A DIREÇAO 

  if (perigo) {  //SE HOUVER PERIGO, NAO DEIXA SEGUIR PARA FRENTE (SEGURANÇA DUPLA PORQUE AO ENCONTRAR PERIGO ELE VOLTA PARA TRÁS)
     anguloServoE = max(anguloServoE, 90);
     anguloServoD = max(anguloServoD, 90);
  }
  
  servoEsquerda.write(180 - anguloServoE); //INVERTE O VALOR PARA EXECUTAR O MOVIMENTO CORRETO  
  servoDireita.write(anguloServoD);
}

// FUNÇÃO DE CONTROLE DA CABEÇA
void moverCabeca(){
  
  byte anguloCabeca = map(lidoDx, 0, 255, 180, 0); // CONVERTE O VALOR PARA FAIXA DE TRABALHO DO SERVO
  servoCabeca.write(anguloCabeca);          // MOVE A CABEÇA PARA O VALOR DE ANGULO CORRESPONDENTE COM VELOCIDADE 80
}

//FUNÇÃO PARA BALANCAR CABEÇA
void naoCabeca(){
  
  //servoEsquerda.write(180-negativoMax);  // MOVIMENTA PARA TRÁS
  //servoDireita.write(negativoMax);       // MOVIMENTA PARA TRÁS

  //delay(500);

  //servoEsquerda.write(parado); // PARA O SERVO
  //servoDireita.write(parado);  // PARA O SERVO
  
  servoCabeca.write(40);
  delay(250);  
  servoCabeca.write(140);
  delay(250); 
  servoCabeca.write(40);
  delay(250);
  //servoCabeca.write(140);
  //delay(250);
  servoCabeca.write(90);
  delay(250);
}

//FUNÇÃO PARA CHECAR PERIGO
void checarPerigo(){
  if ( (millis() - tempoLeitura) > 500){ // LER DISTANCIA A CADA 500 MILISEGUNDOS
      distObstaculo = sensorDistancia.dist(); // LEITURA DA DISTÂNCIA EM CM DO OBSTÁCULO À FRENTE
      tempoLeitura = millis(); // ATRIBUI O VALOR ATUAL DE MILLIS À VARIÁVEL DE CONTROLE
  }
  
  terraFirme = !digitalRead(pinSensor);   // VERIFICA SE TEM CHÃO À FRENTE 
  
  if ( (distObstaculo < minDist) || !terraFirme) { // PARA O ROBO CASO NÃO TENHA CHÃO OU ENCONTRE UM OBSTÁCULO PERTO
    if (!perigo) {
      perigo = true; // GUARDA VALOR PARADO PARA LEMBRAR QUE TEM OBSTÁCULO À FRENTE DURANTE A PRÓXIMA EXECUÇÃO DO LOOP
      servoDireita.write(parado);
      servoEsquerda.write(parado);
      naoCabeca();
    }
  } else {
    perigo = false;
  }  
}

//FUNÇÃO DE CONFIGURAÇÃO E RETORNO DO CONTROLE
void checarControle(){
  //CONFIGURANDO PINO DO CONTROLE PARA CHECAR ERROS
  error = controlePS.config_gamepad(pinClock,pinComando,pinAtencao,pinData, true, true);
  
  //MENSAGENS DE STATUS DO CONTROLE
  switch(error){
    case 0: 
      Serial.println("Controle encontrado e configurado com sucesso!");
      break;
    case 1: 
      Serial.println("Nenhum controle encontrado, verifique os cabos, acesse www.billporter.info para mais informacoes");   
      break;
    case 2: 
      Serial.println("Controle encontrado mas comandos nao funcionam. acesse www.billporter.info para mais informacoes");   
      break;
    case 3: 
      Serial.println("Controle recusou comando de pressao. ");
      break;
  }
  //CHECAR O TIPO DE CONTROLE
  type = controlePS.readType();
  switch(type){
    case 0:
      Serial.println("Tipo desconhecido");
      break;
    case 1:
      Serial.println("Controle DualShock encontrado");
      break;
    case 2:
      Serial.println("Controle GuitarHero encontrado");
      break;
     } 
  
}

