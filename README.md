# Cuidado de idosos

Este documento tem por objetivo registrar as etapas de desenvolvimento das diversas partes (robô, sensores, alarmes...) que integram o projeto de cuidado de idosos sendo desenvolvido por um grupo de alunos na disciplina **Desenvolvimento de Aplicações para Automação** ministrada pelo professor Alexandre Stürmer Wolf na Univates.

O grupo é integrado por:
* Anderson da Silva Quadros;
* Jonathan Tabaldi Bassani;
* Marcelo Teichenbach;
* Pedro Augusto Rodrigues;
* Samuel Dornelles

Cada membro do grupo envolveu-se em diferentes partes do projeto.

## B1-M1 - Robô de monitoramento
Membros envolvidos:
* Anderson da Silva Quadros;
* Pedro Augusto Rodrigues

O B1-M1 é um robô de monitoramento.

### Relação de componentes utilizados

1x [Placa de desenvolvimento ESP32S-NodeMCU 38 pinos](https://www.usinainfo.com.br/esp32/esp32s-nodemcu-iot-com-wifi-e-bluetooth-38-pinos-com-usb-c-e-cp2102-8796.html)

1x [Placa de desenvolvimento ESP32-CAM-CH340 com câmera OV2640](https://www.usinainfo.com.br/esp32/esp32-cam-ch340-ov2640-iot-com-programador-integrado-8758.html)

3x [Bateria de lítio 18650 3.7V recarregável button-top](https://www.usinainfo.com.br/baterias/bateria-18650-litio-recarregavel-37v-3800mah-button-top-kit-com-2-unidades-8170.html)

1x [Suporte para 3 baterias 18650](https://www.usinainfo.com.br/suporte-para-pilhas/suporte-para-3-baterias-18650-smt-9059.html)

1x [Placa de proteção para bateria (BMS - Battery Management System) 18650-3S-20A](https://www.usinainfo.com.br/controladores-de-carga/placa-de-protecao-para-bateria-18650-3s-20a-12v-hx-3s-fl20-7070.html)

1x [Regulador de tensão XL4015 DC/DC step down 8~36V → 1,25~32V 0,2~3A](https://www.usinainfo.com.br/regulador-de-tensao/regulador-de-tensao-e-corrente-ajustavel-xl4015-dc-step-down-saida-125-a-32vdc-02-a-3a-5880.html)

1x [Regulador de tensão LM2596DC DC/DC step down 3,2~40V → 1,5~35V 1,2A](https://www.usinainfo.com.br/regulador-de-tensao/regulador-de-tensao-ajustavel-lm2596-dc-step-down-saida-15v-a-35vdc-12a-2552.html)

1X [Sensor de distância ultrassônico HC-SR04](https://www.usinainfo.com.br/sensor-ultrassonico/sensor-ultrassonico-de-distancia-hc-sr04-2295.html)

1x [Driver motor DC ponte H TB6612FNG](https://www.usinainfo.com.br/driver-para-motor/driver-tb6612fng-duplo-ponte-h-de-motor-dc-ou-passo-4697.html)

2x [Motor DC 3~6V 200RPM com caixa de redução 48:1](https://www.usinainfo.com.br/motor-dc/motor-dc-3-6v-200rpm-com-caixa-de-reducao-e-eixo-duplo-481--3161.html)

2x [Sensor de velocidade LM393](https://www.usinainfo.com.br/sensor-de-velocidade/sensor-de-velocidade-para-arduino-sensor-de-contagem-chave-optica-para-encoder-5mm-4486.html)

E uma infinidade de terminais, parafusos, porcas, brocas, fixadores, cabos, espaçadores... utilizados para montar o robô em uma estrutura de MDF.

### Memorial de cálculo de dimensionamento
O grupo pretende alcançar os seguintes objetivos para o robô B1-M1:
1. mover-se seguindo uma rotina pré-determinada em um ambiente residencial plano e permitir controle remoto;
2. registrar valores obtidos pelo sensoriamento ultrassônico e visual (fotografias) e permitir o stream (vídeo) durante o acesso remoto;
3. comunicar-se com o Gemini através da API fornecida pelo Google a fim de obter instruções para movimento autônomo

Para alcançar os objetivos acima listados foi determinada a necessidade dos componentes listados na seção Relação de componentes utilizados

### Desenvolvimento do código

Tanto os alunos Anderson quanto Pedro nunca fizeram antes um projeto

```ino
// TB6612FNG - Driver motor
#define PWMA 4
#define AIN1 16
#define AIN2 17
#define PWMB 5
#define BIN1 18
#define BIN2 19
#define STBY 2

int pwmA = 94;
int pwmB = 94;

// HC-SR04 - Sensor de distância
#define TRIG 27
#define ECHO 14
#define VELOCIDADE_SOM_CM_US 0.0343 // [cm/µs] Velocidade de propagação de uma onda sonora em um ambiente a 20°C
#define DISTANCIA_MINIMA_CM 30 // [cm]
#define DISTANCIA_MAXIMA_CM 100 // [cm]
#define TIMEOUT_US DISTANCIA_MAXIMA_CM / VELOCIDADE_SOM_CM_US // [µs]

void setup() {
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(STBY, OUTPUT);

  digitalWrite(STBY, HIGH); // Ativa o driver motor

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
}

float medirDistancia() {
  // Dispara pulso ultrassônico no sensor de distância
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  // Calcula e retorna a distância até obstáculo
  long duracao = pulseIn(ECHO, HIGH, TIMEOUT_US);
  float distancia = duracao * VELOCIDADE_SOM_CM_US / 2; // [cm]
  return distancia;
}

void moverFrente() {
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
  analogWrite(PWMA, pwmA);
  analogWrite(PWMB, pwmB);
}

void moverTras() {
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH);
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, HIGH);
  analogWrite(PWMA, pwmA);
  analogWrite(PWMB, pwmB);
}

void parar() {
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, LOW);
  analogWrite(PWMA, 0);
  analogWrite(PWMB, 0);  
}

void loop () {
  float distancia = medirDistancia(); // [cm]

  if(distancia > DISTANCIA_MINIMA_CM) {
    moverFrente();
  } else {
    parar();
  }

  delay(200);
}
```
