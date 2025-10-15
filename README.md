# Cuidado de idosos

Este documento tem por objetivo registrar as etapas de desenvolvimento das diversas partes (robô, sensores, alarmes...) que integram o projeto de cuidado de idosos sendo desenvolvido por um grupo de alunos na disciplina **Desenvolvimento de Aplicações para Automação** ministrada pelo professor Alexandre Stürmer Wolf na Univates.

O grupo é integrado por:
* Anderson da Silva Quadros;
* Jonathan Tabaldi Bassani;
* Marcelo Teichenbach;
* Pedro Augusto Rodrigues;
* Samuel Dornelles

Cada membro do grupo envolveu-se em diferentes partes do projeto.

![B1-M1](https://media1.giphy.com/media/v1.Y2lkPTZjMDliOTUyYWtraTV2dTdxNW42OGphMnJvZnplNmpqM2wzbmhwb2UxcnhpdDFkbCZlcD12MV9naWZzX3NlYXJjaCZjdD1n/3o7abB06u9bNzA8lu8/giphy.gif)

## B1-M1 - Robô de monitoramento
Membros envolvidos:
* Anderson da Silva Quadros;
* Pedro Augusto Rodrigues

O B1-M1 é um robô de monitoramento.

Talvez a primeira pergunta que surja seja "e qual a relação dele com o cuidado de idosos?".

Bem, digamos que o sensor do banheiro dispare um alarme de que talvez ocorreu um acidente, pois alguém entrou no cômodo mas não houve registro de saída depois do intervalo de tempo limite do sensor.

O B1-M1 pode ser útil para se deslocar até o banheiro e abrir uma stream de vídeo e chamada por voz para checar o que pode ter ocorrido, permitindo a alguma terceira pessoa checar se está tudo bem com a pessoa idosa.

Enfim, a maior motivação do projeto é um grande interesse em robótica.

O grupo pretende alcançar os seguintes objetivos para o robô B1-M1:
1. mover-se seguindo uma rotina pré-determinada em um ambiente residencial plano e permitir controle remoto;
2. registrar valores obtidos pelo sensoriamento ultrassônico e visual (fotografias) e permitir o stream (vídeo) durante o acesso remoto;
3. comunicar-se com o Gemini através da API fornecida pelo Google a fim de obter instruções para movimento autônomo.

Tanto os alunos Anderson quanto Pedro nunca fizeram antes um projeto de robótica. Portanto, os objetivos listados acima são desafiadores para o grupo.

Para fins didáticos e de criação de um memorial de aprendizado, o grupo decidiu documentar o progresso feito na construção do B1-M1.

A documentação é apresentada abaixo. Cada inserção conta com notas pessoais de aprendizado do grupo. Algumas linhas podem parecer excessivamente detalhadas - muita vezes com informações que podem parecer óbvias a alguém mais experiente - mas é importante lembrar que elas foram escritas mais como um caderno de aula do que como uma documentação profissional.

---

### Relação de componentes utilizados

Nesta seção estão listados os componentes utilizados.

Houve uma infinidade de terminais, parafusos, porcas, brocas, fixadores, cabos, espaçadores... além da estrutura MDF que não foi listada, já que a estutura atual do B1-M1 é apenas um protótipo.

<details>
  <summary>📝 Relação de componentes</summary>

  1x [Placa de desenvolvimento ESP32S-NodeMCU 38 pinos](https://www.usinainfo.com.br/esp32/esp32s-nodemcu-iot-com-wifi-e-bluetooth-38-pinos-com-usb-c-e-cp2102-8796.html)
  
  1x [Placa de desenvolvimento ESP32-CAM-CH340 com câmera OV2640](https://www.usinainfo.com.br/esp32/esp32-cam-ch340-ov2640-iot-com-programador-integrado-8758.html)
  
  3x [Bateria de lítio 18650 3.7V recarregável button-top](https://www.usinainfo.com.br/baterias/bateria-18650-litio-recarregavel-37v-3800mah-button-top-kit-com-2-unidades-8170.html)
  
  1x [Suporte para 3 baterias 18650](https://www.usinainfo.com.br/suporte-para-pilhas/suporte-para-3-baterias-18650-smt-9059.html)
  
  1x [Placa de proteção para bateria (BMS - Battery Management System) 18650-3S-20A](https://www.usinainfo.com.br/controladores-de-carga/placa-de-protecao-para-bateria-18650-3s-20a-12v-hx-3s-fl20-7070.html)
  
  1x [Regulador de tensão XL4015 DC/DC step down 8-36V → 1,25-32V 0,2-3A](https://www.usinainfo.com.br/regulador-de-tensao/regulador-de-tensao-e-corrente-ajustavel-xl4015-dc-step-down-saida-125-a-32vdc-02-a-3a-5880.html)
  
  1x [Regulador de tensão LM2596DC DC/DC step down 3,2-40V → 1,5-35V 1,2A](https://www.usinainfo.com.br/regulador-de-tensao/regulador-de-tensao-ajustavel-lm2596-dc-step-down-saida-15v-a-35vdc-12a-2552.html)
  
  1X [Sensor de distância ultrassônico HC-SR04](https://www.usinainfo.com.br/sensor-ultrassonico/sensor-ultrassonico-de-distancia-hc-sr04-2295.html)
  
  1x [Driver motor DC ponte H TB6612FNG](https://www.usinainfo.com.br/driver-para-motor/driver-tb6612fng-duplo-ponte-h-de-motor-dc-ou-passo-4697.html)
  
  2x [Motor DC 3~6V 200RPM com caixa de redução 48:1](https://www.usinainfo.com.br/motor-dc/motor-dc-3-6v-200rpm-com-caixa-de-reducao-e-eixo-duplo-481--3161.html)
  
  2x [Sensor de velocidade LM393](https://www.usinainfo.com.br/sensor-de-velocidade/sensor-de-velocidade-para-arduino-sensor-de-contagem-chave-optica-para-encoder-5mm-4486.html)
  
</details>

---

### Memorial de cálculo de dimensionamento

Nesta seção estão  registrados a metodologia e os cálculos utilizados para dimensionamento dos componentes do B1-M1.

<details>
  <summary>📝 Memorial</summary>
  
  Como a alimentação elétrica é a espinha dorsal de todo projeto de eletrônica embarcada, o primeiro passo dado pelo grupo foi estimar o consumo de corrente dos componentes utilizados para atingir os objetivos.
  
  #### Consumo de corrente
  
  | Componente                        | Quantidade  | Consumo total | 
  |-----------------------------------|:-----------:|:-------------:|
  | ESP32S-NodeMCU                    | 1           | ~250mA[^1]    |
  | ESP32-CAM                         | 1           | ~250mA[^2]    |
  | Sensor ultrassônico HC-SR04       | 1           | ~15mA         |
  | Driver motor TB6612FNG            | 1           | ~1,5mA        |
  | Motor DC 3-6V 200RPM              | 2           | ~400mA[^3]    |
  | Sensor de velocidade LM393        | 2           | ~20mA         |
  | **Total**                         | **8**       | **~936,5mA**  |
  
  Para fins de cálculo, arredondar-se-á o consumo total para 1A (1000mA).
  
  #### Autonomia
  
  ![18650](https://i.imgur.com/sR7YUmA.jpeg)
  
  As baterias de lítio 18650 têm gravado nos seus invólucros a capacidade de carga elétrica de **3800mAh**. Porém, [é interessante notar que o vendedor fez testes e alegou a capacidade de apenas 1500mAh](https://www.usinainfo.com.br/baterias/bateria-18650-litio-recarregavel-37v-3800mah-flat-top-8760.html). Portanto, para fins de cálculo neste trabalho, adotar-se-á o valor de **1500mAh**.
  
  Fazendo um cálculo simples de autonomia,
  
  $Autonomia = \frac{Capacidade \ de \ carga \ elétrica}{Consumo \ de \ corrente \ elétrica} = \frac{1500mAh}{1000mA} ≈ 1,5h$
  
  Logo, o grupo espera que o B1-M1 tenha uma autonomia de aproximadamente **1 hora e 30 minutos** funcionando com as premissas de consumo feitas na tabela **Consumo de corrente**.
  
  #### Seção dos cabos utilizados
  
  Como cabos de bitola 1mm² suportam correntes contínuas de até 10A, adotou-se o seu uso nas conexões do pack de baterias 18650 com a BMS e da BMS com os reguladores de tensão.
  
  Nas demais conexões utilizou-se cabos de 0,75mm², que suportam correntes contínuas de até 8A.
</details>

---

### Esquemático

![Esquemático](https://i.imgur.com/hKs6kS9.jpeg)

Uma imagem em alta resolução do esquemático pode ser vista [aqui](https://i.imgur.com/tPJJAKS.png)

Algumas notas sobre decisões feitas foram colocadas abaixo.

<details>
  <summary>💽 Capacitores de desacoplamento de 100nF nos terminais dos motores A e B</summary>

  ![Motores escovados](https://i.imgur.com/eeTXd8O.jpeg)
  
  Motores produzem ruído.
  
  No contexto do B1-M1, "ruído" é entendido como as ondas eletromagnéticas emitidas por um dispositivo durante seu funcionamento afetarem o funcionamento de outros dispositivos eletrônicos.
  
  Ruído é um problema difícil de resolver, pois fisicamente eles são uma forma de energia eletromagnética - que também é a descrição para sinais elétricos. Assim, como distinguir sinais de ruídos? A energia eletromagnética que é essencial para o funcionamento de um sistema pode ser a causa de ruído indesejado para outro.
  
  Nos motores DC utilizados neste projeto, uma das fontes de ruído possíveis é devido à comutação entre as escovas de carbono e o anel coletor laminado (o comutador) do induzido.
  
  [GIF mostrando os arcos voltaicos](https://i.imgur.com/fCO2iG0.gif)
  
  Quando as escovas e as lâminas do anel coletor comutam ocorrem arcos voltaicos (*comutar = ligar ou desligar, interromper e religar uma ligação elétrica*). Esses arcos ocorrem pois uma vez energizadas as bobinas do enrolamento do induzido se comportam como indutores.
  
  A equação da tensão para indutores é
  $$
  v = L \frac{di}{dt}
  $$
  Ou seja, a tensão é proporcional à taxa de variação da corrente.
  
  Quando a comutação ocorre, a taxa de variação da corrente é abrupta e intensa (indo de 100% para 0% em um intervalo de tempo muito pequeno). Essa grande taxa de variação provoca um pico de tensão nas bobinas e, por consequência, os arcos voltaicos entre as escovas e as lâminas do anel coletor. Os picos de tensão no funcionamento de um motor DC podem ser vistos na imagem abaixo.
  
  ![Ruído](https://i.imgur.com/xDD7Uay.jpeg)
  
  O objetivo dos capacitores próximos aos terminais do motor é de suprimir um pouco esses picos de tensão gerados pela comutação das escovas e das lâminas do coletor.

  É importante notar que foram utilizados capacitores cerâmicos pois o sentido da corrente pode inverter conforme o sentido de giro dos motores.
  
</details>

---

### Desenvolvimento do código

O código inicial e as versões com melhorias e alterações feitas pelo grupo estão listadas abaixo. A ordem é cronológica e conta sempre com o código integral, um vídeo e uma breve discussão sobre conceitos utilizados.

---

#### 13/10/2025

💾 [Código versão 1](https://gist.github.com/parodrigues-ipynb/be9dc512e9a064356e3e1a73c458425b)

🎥 [Vídeo B1-M1 rodando com a versão 1](https://imgur.com/a/WtTMg6K)

<details>
  <summary>📝 Comentários sobre o código versão 1</summary>
  
  ```ino
  // Linha 2
  #define PWMA 4
  ```
  `#define` é uma diretiva de pré-processador da linguagem C/C++ que cria uma constante simbólica. O compilador substitui todas as ocorrências do nome pelo valor definido antes de compilar. Por exemplo, `#define PWMA 4` substitui `PWMA` por `4` no momento anterior à compilação. O uso de `#define` é útil para mapear pinos e definir valores fixos/limites (distâncias, velocidades...) que permanecerão constantes ao longo do código, tornando as informações mais claras e fáceis de alterar.
  
  ```ino
  // Linha 10
  uint8_t pwmA = 94;
  ```
  A variável `pwmA` irá armazenar os valor de duty cycle para o sinal PWM enviado ao motor A.
  
  PWM significa *Pulse Width Modulation*, ou *Modulação de Largura de Pulso*. *Duty cycle*, ou *ciclo de trabalho*, representa a razão entre a **largura de pulso** ($t_{ON}$), que é o tempo em que o sinal permanece em nível HIGH, e o **período total do sinal** ($T$), conforme a expressão:
  
  ![Duty cycle](https://i.imgur.com/GDkGRCn.png)
  
  Por exemplo, se o período $T$ fosse 100ms, um *duty cycle* de 25% teria uma largura de pulso $t_{ON}$ de 25ms.
  
  ![Sinal PWM](https://i.imgur.com/OkiNbwV.jpeg)
  
  A imagem acima mostra diferentes sinais de tensão PWM. As linhas verticais laranjas são as marcações de tempo. Portanto, todos os sinais compartilham o mesmo período $T$.
  
  Na imagem os sinais de tensão PWM têm *duty cycles* distintos: 0%, 25%, 50%, 75% e 100%.
  
  Quando o *duty cycle* é 0%, a tensão de saída é 0V. Quando o *duty cycle* é de 100%, a tensão de saída é 5V.
  
  É interessante notar que com *duty cycle* de 50% resulta numa tensão de saída média de 2,5V. 25% resulta em uma tensão média de 1,25V. Essas tensões médias são indicadas pelas linhas laranjas grossas horizontais apontadas pelas setas verdes na caixa de texto *Average Output Voltage*, ou *Tensão Média de Saída*.
  
  É uma prática comum utilizar variáveis numéricas para representar o *duty cycle* em código. Por exemplo, seria teoricamente possível criar uma variável `int pwmA = 0` para representar um *duty cycle* de 0%. Caso fosse desejável alterar o duty cycle para 1%, poderia-se simplesmente alterar o valor da variável para `pwma = 1`, ou 2% → `pwma = 2`, e assim por diante.
  
  O tipo de variável `int` é usado para armazenar números inteiros (-2, -1, 0, 1, 2, 3...). Na ESP32, o `int` ocupa **4 bytes** (32 bits) - o que faz sentido, já que o microcontrolador é baseado em arquitetura 32 bits. Os valores possíveis para variáveis do tipo `int` vão de -2,147,483,648 até 2,147,483,647. É possível utlizar `unsigned int` para trabalhar-se com o intervalo de 0 até 4,294,967,295 (aproximadamente 4 bilhões).
  
  Portanto, no caso da linha 10, poderíamos teoricamente utilizar a variável `unsigned int pwmA` para mapear o *duty cycle*. Se desejássemos utilizar todo o potencial de armazenamento do tipo `unsigned int`, como queremos mapear valores de 0% até 100% num intervalo de 0 até 4,294,967,295, faríamos $\frac{100\\% - 0\\%}{4,294,967,295 - 0} ≈ 0,00000002328\\%$.
  
  Assim, teríamos a seguinte resolução:
  * `pwmA = 0             // → 0%`
  * `pwmA = 1             // → ≈ 0,00000002328%`
  * `pwmA = 2             // → ≈ 0,00000004657%`
  * ...
  * `pwmA = 4294967294    // → ≈ 99,9999999767%`
  * `pwmA = 4294967295    // → 100%`
  
  Agora imaginemos programadores tendo de cotidianamente utilizar essa resolução em seus códigos. Seria um pesadelo ter de lembrar o valor 4294967295, e muito difícil lembrar os valores que mapeam para aproximadamente 25%, 50%, 75%...
    
  Portanto, no caso de sinais PWM, é comum utilizar-se tipos de variáveis de apenas **1 byte** (8 bits), que na base binária ($2^n$) correspondem a 256 valores possíveis ($2^8 = 256$). Como $\frac{100\\%-0\\%}{255-0} ≈ 0,39\\%$, teríamos a seguinte resolução:
  * `pwmA = 0             // → 0%`
  * `pwmA = 1             // → ≈ 0,39%`
  * `pwmA = 2             // → ≈ 0,78%`
  * ...
  * `pwmA = 254           // → ≈ 99,61%`
  * `pwmA = 255           // → 100%`
  
  No caso da variável `pwmA = 94`, temos um *duty cycle* de aproximadamente 37%.
  
  Fica evidente que 1 byte já traz uma resolução adequada para se programar e ainda possibilita inferir algumas porcentagens intuitivamente:
  * como 100% → 255,
  * então 50% deve ser algo em torno de 127,
  * 25% deve ser algo em torno de 64...
  e assim por diante.
  
  `uint8_t` significa *unsigned integer of length 8 bits*, ou *número inteiro sem sinal de comprimento de 8 bits*. É muito comum encontrar softwares e hardwares que utilizam sinais PWM mapeados por variáveis de 8 bits. Entretanto, é sempre bom ficar atento às convenções adotadas em cada projeto pois pode haver casos em que uma maior resolução é necessária a fim de alcançar maior precisão.
  
  ```ino
  // Linha 16
  #define TIMEOUT_US 20000 // [µs]
  ```
  O sensor de distância ultrassônico HC_SR04 tem dois componentes principais: um emissor e um receptor de pulsos ultrassônicos.
  
  ![HC_SR04](https://i.imgur.com/9TA6kXy.jpeg)
  
  Chamamos de "som" a propagação de uma onda mecânica através de um meio - comumente nossa atmosfera, ou o nosso "ar".
  
  "Ultrassônico" signica um som fora do espectro de audição humana, que costuma ir de aproximadamente 20Hz até 20kHz. Como os pulsos que o HC_SR04 emite têm frequência de 40kHz, então eles são ultrassônicos.
  
  O funcionamento do sensor é simples: ele emite um pulso ultrassônico, inicia um cronômetro interno e aguarda o receptor identificar o eco do pulso original transmitido, momento no qual o cronômetro é encerrado.
  
  O som se propaga na atmosfera terrestre a 20°C com uma velocidade de aproximadamente 343m/s, ou 0,0343cm/µs.
  
  O [datasheet do HC_SR04](https://cdn.sparkfun.com/datasheets/Sensors/Proximity/HCSR04.pdf) especifica que o sensor é capaz de realizar medições de 2cm até 4m.
  
  A definição de velocidade $v$ é a razão da distância $d$ sobre o tempo $t$, ou
  
  ![Velocidade](https://i.imgur.com/3BgQRWY.png)
  
  Como o pulso ultrassônico deve ir, colidir com um obstáculo e voltar, o tempo medido pelo sensor corresponde à ida e volta do pulso ultrassônico. Portanto, para calcular a distância, devemos dividir o tempo por 2:
  
  ![Distância](https://i.imgur.com/dC75AcF.png)
  
  Substituindo os valores de limite de distância do HC_SR04 e multiplicando as distâncias por 2 para compensar o ajuste feito pelo sensor, temos:
  
  ![Tempos](https://i.imgur.com/0LC2vbj.png)
  
  O [datasheet do HC_SR04](https://cdn.sparkfun.com/datasheets/Sensors/Proximity/HCSR04.pdf) estabelece a seguinte prática para a emissão do pulso ultrassônico:
  * o pino TRIG deve ser mantido em LOW por 2µs a fim de garantir estabilidade, evitando que o pulso no pino TRIG que virá a seguir seja confundido com o sinal residual de alguma medição anterior. Estamos "resetando" o HC_SR04 com esse pulso LOW de 2µs;
  * o pino TRIG deve ser mantido em HIGH por 10µs para identificar o comando de emissão do pulso ultrassônico;
  * o pulso ultrassônico é emitido. São 8 pulsos numa frequência de 40kHz. Isso faz cada pulso ter 25µs de duração e a emissão total demorar 200µs;
  * após a emissão do pulso ultrassônico, o pino ECHO entra em nível HIGH e permanece assim até que o oitavo pulso seja processado pelo receptor na volta. Quando o oitavo pulso for detectado, o pino ECHO retorna ao nível LOW;
  * se o tempo TIMEOUT_US for excedido, o pino ECHO retorna a LOW. Portanto, `TIMEOUT_US` é o limite de tempo em microssegundos que o sensor ultrassônico deve aguardar sem que o receptor identifique o eco do pulso ultrassonoro original.
  
  Toda essa rotina consta nas linhas 36 até 44 do código.
  
  ```ino
  // Linhas 36 até 44
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  
  long duracao = pulseIn(ECHO, HIGH, TIMEOUT_US);
  float distancia = duracao * 0.0343 / 2; // [cm]
  ```
  
  O diagrama de tempo abaixo apresenta o funcionamento das partes do HC_SR04 visualmente. 
  
   ```
      ________________________________________________________________________________________________________
     |                                                                                                        |
     | Pino            ┌┐                                     TIMEOUT_US = 20000µs ┌┐                         |
     | TRIG            ||                                               ↓          ||                         |
     | HC_SR04      ---┘└-----------------------------------------(...)---(...)----┘└-------------------(...) |
     |                 ←→                                                                                     |
     |                 10µs                                                                                   |
     |________________________________________________________________________________________________________|
     |                          8 pulsos                                                                      |
     | Pulsos               ┌┐┌┐┌┐┌┐┌┐┌┐┌┐┌┐                  TIMEOUT_US = 20000µs     ┌┐┌┐┌┐┌┐┌┐┌┐┌┐┌┐       |
     | ultrassônicos        ||||||||||||||||                            ↓              ||||||||||||||||       |
     | emitido      --------┘└┘└┘└┘└┘└┘└┘└┘└----------------------(...)---(...)--------┘└┘└┘└┘└┘└┘└┘└┘└-(...) |
     | pelo HC_SR04         ←→                                                                                |
     |                 40kHz = 25µs                                                                           |
     |                      ←---------------→                                                                 |
     |                             200µs                                                                      |
     |________________________________________________________________________________________________________|
     |                                                                                                        |
     | Pino                                  ┌----------------┐TIMEOUT_US = 20000µs                           |
     | ECHO                                  |                |          ↓                                    |
     | HC_SR04      -------------------------┘                └----(...)---(...)------------------------(...) |
     |                                                                                                        |
     |________________________________________________________________________________________________________|
  
  ```
  
  Como `TIMEOUT_US = 20000`, então o sensor identifica distâncias menores que aproximadamente 3,5m com esse código utilizado:
  
  ![Distância](https://i.imgur.com/wkEWmOA.png)
  
</details>

---

#### 14/10/2025

💾 [Código versão 2](https://gist.github.com/parodrigues-ipynb/5a684ad0ee756691a03b47f6cd5c61a2)

🎥 [Vídeo B1-M1 rodando com a versão 2](https://imgur.com/a/dLxYKjw)

Nesta versão foi feita a substituição da função `analogWrite()` pelas funções `ledcAttach()` e `ledcWrite()`.

A função `analogWrite()` é uma função padrão a API Arduino, mas não é nativa na plataforma ESP32. Na ESP32, a função `analogWrite()` é apenas um *wrapper* (camada de compatibilidade) que chama o sistema PWM por hardware (LEDC).

`analogWrite()` funciona, mas é genérico e limitado. Como o B1-M1 tem uma ESP32-CAM com Wi-Fi ativo, é mais robusto usar LEDC configurado manualmente para controlar frequência e resolução, garantindo um sinal PWM estável mesmo durante o streaming de vídeo via Wi-Fi.

<details>
  <summary>📝 Comentários sobre o código versão 2</summary>

  LEDC (*LED Control*) é um periférico de hardware interno da ESP32 projetado parar gerar sinais PWM com alta precisão e baixo uso da CPU.

  Esse periférico permite até **16 canais PWM independentes** e **8 temporizadores** que definem a frequência (de 1Hz até 40MHz) e resolução (de 1 até 20 bits) compartilhadas entre canais.

  Uma das grandes vantagens é que esse periférico mantém o sinal PWM ativo sem intervenção do processador. Ou seja, mesmo que a CPU fique sobrecarregada com funções de Wi-Fi, o sinal PWM permanecerá estável.

  ```ino
  const unsigned long TIMEOUT_US = 20000 // [µs]
  ```

  `TIMEOUT_US` foi transformada em uma variável pois há a vontade de calcular o seu valor com base em outros parâmetros e `#define` não faz cálculos com `floats` corretamente. O resultado da divisão de macros é `int` - o que pode comprometer o funcionamento do código de forma inesperada.

  ```ino
  // Configuração PWM para uso do LEDC
  #define LEDC_FREQUENCIA_BASE_PWM 5000 // [Hz] Frequência do PWM
  #define LEDC_RESOLUCAO_BIT_PWM 8     // [bits] Resolução (caso o valor seja 8, então a resolução é de 0-255 pois 2^8 = 256)
  ```
  Foi acrescentado o bloco de código acima nas definições para configurar o LEDC.
  
  `LEDC_FREQUENCIA_BASE_PWM` define a frequência que será utilizada nos canais dos sinais PWM. O valor de 5kHz é comumente utilizado para motores DC. Frequências muito baixas, como 50Hz, fazem o motor gerar um zumbido audível. Frequências muito altas, como 50kHz, aumentam a perda de potência no driver motor TB6612FNG.
  
  ```ino
  void setup() {
    pinMode(AIN1, OUTPUT);
    pinMode(AIN2, OUTPUT);
    pinMode(BIN1, OUTPUT);
    pinMode(BIN2, OUTPUT);
    ledcAttach(PWMA, LEDC_FREQUENCIA_BASE_PWM, LEDC_RESOLUCAO_BIT_PWM);
    ledcWrite(PWMA, 0);
    ledcAttach(PWMB, LEDC_FREQUENCIA_BASE_PWM, LEDC_RESOLUCAO_BIT_PWM);
    ledcWrite(PWMB, 0);
    pinMode(STBY, OUTPUT);
  
    digitalWrite(STBY, HIGH); // Ativa o driver motor
  
    pinMode(TRIG, OUTPUT);
    pinMode(ECHO, INPUT);
  }
  ```

  As linhas `pinMode(PWMA, OUTPUT)` e `pinMode(PWMB, OUTPUT)` foram removidas do `void setup()`. Foram inseridas nos seus lugares as funções `ledcAttach()` para configurar os pinos PWM de cada motor e `ledcWrite()` para iniciar esses sinais PWM com *duty cycle* de 0%.

  ```ino
  void moverFrente() {
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW);
    ledcWrite(PWMA, pwmA);
    ledcWrite(PWMB, pwmB);
  }
  
  void parar() {
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, LOW);
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, LOW);
    ledcWrite(PWMA, 0);
    ledcWrite(PWMB, 0); 
  }
  ```

  Tanto nas funções `void moverFrente()` quanto `void parar()`, as linhas utilizando `analogWrite()` foram substituídas por `ledcWrite()`.

</details>

---

#### 15/10/2025

💾 [Código versão 3](https://gist.github.com/parodrigues-ipynb/389f387e5dbd8301c90e3fee4f395897)

🎥 [Vídeo B1-M1 rodando com a versão 3]()

Nesta versão as ocorrências de `delay()` foram substituídas por `millis()`.

O uso de técnicas como a do `millis()` é o padrão para sistemas embarcados que precisam reagir a múltiplos eventos em tempo real, como é o caso do B1-M1.

`delay()` seria um gargalo para o funcionamento do B1-M1 pois essa é uma função **bloqueante**. Isso significa que outras tarefas não serão executadas durante a espera instaurada por `delay()`: o programa irá ficar "travado" naquele ponto por aquela duração de tempo - o que é inviável para uma premissa multitarefas.

Foram consultados os excelentes artigos abaixo para aprender mais sobre as boas práticas de utilização da função `millis()`.

📔 [Artigo "Usando millis() para contagem de tempo - Uma introdução para iniciantes"](https://forum.arduino.cc/t/using-millis-for-timing-a-beginners-guide/483573)

📔 [Artigo "Código de demonstração para diversas coisas que ocorrem simultaneamente"](https://forum.arduino.cc/t/demonstration-code-for-several-things-at-the-same-time/217158/2)

<details>
  <summary>📝 Comentários sobre o código versão 3</summary>

  ```ino
  unsigned long intervaloLeituras = 200; // [ms]
  unsigned long ultimoMillis = 0;        // [ms]
  ```

  Foram criadas duas variáveis do tipo `unsigned long` para trabalhar em conjunto com a lógica de controle temporal através do `millis()`.

  O uso de `unsigned long` é importante pois esse é o tipo de variável usado internamente por `millis()`.

  ```ino
  void loop() {
    unsigned long agora = millis(); // [ms]
  
    if (agora - ultimoMillis >= intervaloLeitura) {
      ultimoMillis = agora;
  
        float distancia = medirDistancia(); // [cm]
  
      if (distancia > DISTANCIA_MINIMA_CM) {
        moverFrente();
      } else {
        parar();
      }
    }
  }
  ```

  Essa modificação remove o `delay(200)` da função `void loop()` e coloca a lógica de `millis()` no seu lugar.

  O já mencionado [artigo "Usando millis() para contagem de tempo - Uma introdução para iniciantes"](https://forum.arduino.cc/t/using-millis-for-timing-a-beginners-guide/483573) tem uma explicação muito boa sobre essa lógica.
  
</details>

[^1]: O [datasheet da Espressif](https://www.espressif.com/sites/default/files/documentation/esp32_datasheet_en.pdf) apresenta diferentes consumos para situações de transmissão ou recepção de Wi-Fi/Bluetooth, light-sleep, deep-sleep... Esses valores podem ser consultados nas tabelas *Table 4-2. Power Consumption by Power Modes* na **página 30** e *Table 5-4. Current Consumption Depending on RF Modes* na **página 53**. Em função dos diversos possíveis valores de corrente para cada modo de funcionamento, adotou-se o pior caso (maior consumo de ~250mA com transmissão Wi-Fi 802.11b ativa).

[^2]: O [datasheet consultado](https://www.handsontec.com/dataspecs/module/ESP32-CAM.pdf) apresenta valores em torno de 200mA para câmera ligada/flash desligado e 300mA para câmera ligada/flash ligado. Os valores podem aumentar em caso de streaming por Wi-Fi. Adotou-se o valor médio.

[^3]: [O valor de corrente de 200mA por cada motor é para situações sem carga](https://www.usinainfo.com.br/motor-dc/motor-dc-3-6v-200rpm-com-caixa-de-reducao-e-eixo-duplo-481--3161.html), nas quais os motores estão girando sem resistências mecânicas. Se houver atrito, inclinação, a própria massa do robô..., o valor de corrente pode subir consideravelmente, chegando a valores de até 1,5A por motor. Como não pode-se encontrar um datasheet para o motor específico utilizado, confiou-se nos valores apresentados pelo vendedor.
