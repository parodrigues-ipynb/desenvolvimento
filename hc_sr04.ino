
// esquemático do projeto
/*
    __________________              _____________
   |       ESP32      |            |   HC-SR04   |
   |      NodemCU     |            |             |
   |               5V |------------| Vcc         |
   |              GND |------------| GND         |
   |          GPIO  5 |-----------→| TRIG        |
   |                  | 5V→ ┌------| ECHO        |
   |                  |     |      |_____________|
   |                  |   [1kΩ]
   |                  |     |
   |          GPIO 25 |←----┤ ←3.3V    Vout = Vin · R2 / (R1 + R2)
   |__________________|     |          Vout =  5  · 2k / (1k + 2k)
   .                      [2kΩ]        Vout =  5  · 2k / 3k
   .                        |          Vout ≈ 3.333... V
   .                        ⏚ GND
*/

// explicações do HC-SR04
/*
   Parâmetros elétricos
   ┌-----------------------------------------┐
   | TENSÃO DE OPERAÇÃO              5Vdc    |
   ├-----------------------------------------┤
   | CORRENTE DE OPERAÇÃO            15mA    |
   ├-----------------------------------------┤
   | FREQUÊNCIA DE OPERAÇÃO          40Hz    |
   ├-----------------------------------------┤
   | DISTÂNCIA MÍNIMA PARA MEDIÇÃO   2cm     |
   ├-----------------------------------------┤
   | DISTÂNCIA MÁXIMA PARA MEDIÇÃO   400cm   |
   ├-----------------------------------------┤
   | PRECISÃO PARA MEDIÇÃO           +/- 3mm |      ⟋   
   ├-----------------------------------------┤    ⟋
   | ÂNGULO DE MEDIÇÃO               15°     |  <  ) 15°
   └-----------------------------------------┘    ⟍
   .                                                ⟍
   Diagrama de tempo de operação
    ________________________________________________________________________________________________________
   |                                                                                                        |
   | Pino            ┌┐                                     TIMEOUT_US = 17493µs ┌┐                         |
   | TRIG            ||                                               ↓          ||                         |
   | HC_SR04      ---┘└-----------------------------------------(...)---(...)----┘└-------------------(...) |
   |                 ←→                                                                                     |
   |                 10µs                                                                                   |
   |________________________________________________________________________________________________________|
   |                                                                                                        |
   | Pulso                ┌┐┌┐┌┐┌┐┌┐┌┐┌┐┌┐                  TIMEOUT_US = 17493µs     ┌┐┌┐┌┐┌┐┌┐┌┐┌┐┌┐       |
   | ultrassônico         ||||||||||||||||                            ↓              ||||||||||||||||       |
   | emitido      --------┘└┘└┘└┘└┘└┘└┘└┘└----------------------(...)---(...)--------┘└┘└┘└┘└┘└┘└┘└┘└-(...) |
   | pelo HC_SR04         ←→                                                                                |
   |                 40kHz = 25µs                                                                           |
   |                      ←---------------→                                                                 |
   |                             200µs                                                                      |
   |________________________________________________________________________________________________________|
   |                                                                                                        |
   | Pino                                  ┌----------------┐TIMEOUT_US = 17493µs                           |
   | ECHO                                  |                |          ↓                                    |
   | HC_SR04      -------------------------┘                └----(...)---(...)------------------------(...) |
   |                                                                                                        |
   |________________________________________________________________________________________________________|
   */

#define TRIG_PIN 5    // pino TRIGGER conectado na GPIO 5, responsável por iniciar a emissão do pulso ultrassônico
#define ECHO_PIN 25   // pino ECHO conectado na GPIO 25, responsável por medir o tempo percorrido para reflexão do pulso ultrassônico

const float SOUND_SPEED_CM_US = 0.0343;   // cm/μs
/*
   a velocidade do som é de aproximadamente 343m/s

   1m = 100cm
   1s = 1,000,000μs
   portanto,
   1m/s = 100cm / 1,000,000μs = 0.0001cm/μs

   343m/s · 0.0001 = 0.0343cm/μs

   é importante lembrar que a velocidade do som varia com a temperatura (cerca de 0.6m/s a cada 1°C). a velocidade de 0.0343cm/µs assume
   uma temperatura de aproximadamente 20°C
*/
const float MAX_DISTANCE = 3;   // distância máxima que se deseja medir, usada para cálculo do tempo máximo de espera

const unsigned long TIMEOUT_US = 17493;   // tempo máximo de espera para retorno do eco, em microssegundos (µs, ou "US" do nome da constante)
/*
   se a velocidade do som é 343m/s, então
   v   = (d · 2) / t
   343 = (d · 2) / t
   .               t = (d · 2) / 343
   .               no nosso caso, d = MAX_DISTANCE
   .               assumindo MAX_DISTANCE = 3
   .               t = (3 · 2) / 343
   .               t ≈ 0.0174927s, ou 17.493ms, ou 17493µs
*/

// Cálculo da distância em centímetros aferida pelo HC-SR04
float distanceMeasure_cm() {
   // pulso LOW de 2µs para "reset" do sensor HC-SR04 no pino TRIG para garantir estabilidade, exigido no datasheet
   /*
      antes de enviar o pulso HIGH para disparar o sensor, o pino TRIG precisa estar em nível LOW para
      garantir que o pulso será claramente identificado como um pulso novo e não um sinal residual de
      alguma medição anterior

      isso evita "ruídos" ou transições lentas que possam ser interpretadas incorretamente pelo sensor,
      pois estamos "resetando" o sensor para um novo pulso
   */
   digitalWrite(TRIG_PIN, LOW);
   delayMicroseconds(2);

   // pulso HIGH de 10µs para disparo do pulso ultrassônico
   /*
     agora sim podemos enviar o pulso HIGH padrão para que o sensor HC-SR04 emita um pulso ultrassônico,
     sem risco de "ruídos", com duração de 10µs conforme especificado pelo datasheet
   */
   digitalWrite(TRIG_PIN, HIGH);
   delayMicroseconds(10);
   digitalWrite(TRIG_PIN, LOW);

   // duração do eco
   /*
      pulseIn() mede o tempo em microssegundos (µs) em que ECHO_PIN permanece no nível HIGH
      logo após receber o pulso HIGH no pino TRIG, o HC-SR04 coloca o pino ECHO no nível HIGH também.
      o pino ECHO permanece em HIGH até o momento em que o eco do som seja refletido
   */
   long duration = pulseIn(ECHO_PIN, HIGH, TIMEOUT_US);

   // conversão do tempo para distância
   if (duration == 0) {
     return -1;   // isso indica que não houve eco
   }
   return (duration * SOUND_SPEED_CM_US) / 2;   // a divisão por dois ocorre pois o pulso ultrassônico precisa ir e voltar
}

void setup()
{
    Serial.begin(115200);   // 115200 bits por segundo é uma baud rate padrão com a ESP32
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
}

void loop()
{
   float distance_cm = distanceMeasure_cm();

   // impressão dos dados no Serial Monitor
   if(distance_cm < 0) {
      Serial.println("O HC-SR04 não escutou eco ):");
   } else {
      Serial.print("Distância: ");
      Serial.print(distance_cm, 2);   // duas casas decimais
      Serial.println(" cm");
   }

   // delay de 100ms para evitar ecos falsos. o datasheet solicita 60ms
   delay(100);
}