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
  <summary>📝 Relação de componentes [clique para expandir]</summary>

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
  
  2x [Sensor de velocidade encoder LM393](https://www.usinainfo.com.br/sensor-de-velocidade/sensor-de-velocidade-para-arduino-sensor-de-contagem-chave-optica-para-encoder-5mm-4486.html)
  
</details>

---

### Memorial de cálculo de dimensionamento

Nesta seção estão  registrados a metodologia e os cálculos utilizados para dimensionamento dos componentes do B1-M1.

<details>
  <summary>📝 Memorial [clique para expandir]</summary>
  
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
  <summary>💽 Capacitores de desacoplamento de 100nF nos terminais dos motores A e B [clique para expandir]</summary>

  ![Motores escovados](https://i.imgur.com/eeTXd8O.jpeg)
  
  Motores produzem ruído.
  
  No contexto do B1-M1, "ruído" é entendido como as ondas eletromagnéticas emitidas por um dispositivo durante seu funcionamento afetarem o funcionamento de outros dispositivos eletrônicos.
  
  Ruído é um problema difícil de resolver, pois fisicamente eles são uma forma de energia eletromagnética - que também é a descrição para sinais elétricos. Assim, como distinguir sinais de ruídos? A energia eletromagnética que é essencial para o funcionamento de um sistema pode ser a causa de ruído indesejado para outro.
  
  Nos motores DC utilizados neste projeto, uma das fontes de ruído possíveis é devido à comutação entre as escovas de carbono e o anel coletor laminado (o comutador) do induzido.
  
  [GIF mostrando os arcos voltaicos](https://i.imgur.com/fCO2iG0.gif)
  
  Quando as escovas e as lâminas do anel coletor comutam ocorrem arcos voltaicos (*comutar = ligar ou desligar, interromper e religar uma ligação elétrica*). Esses arcos ocorrem pois uma vez energizadas as bobinas do enrolamento do induzido se comportam como indutores.
  
  A equação da tensão para indutores é $v = L \frac{di}{dt}$
  
  Ou seja, a tensão é proporcional à taxa de variação da corrente.
  
  Quando a comutação ocorre, a taxa de variação da corrente é abrupta e intensa (indo de 100% para 0% em um intervalo de tempo muito pequeno). Essa grande taxa de variação provoca um pico de tensão nas bobinas e, por consequência, os arcos voltaicos entre as escovas e as lâminas do anel coletor. Os picos de tensão no funcionamento de um motor DC podem ser vistos na imagem abaixo.
  
  ![Ruído](https://i.imgur.com/xDD7Uay.jpeg)
  
  O objetivo dos capacitores próximos aos terminais do motor é de suprimir um pouco esses picos de tensão gerados pela comutação das escovas e das lâminas do coletor.

  É importante notar que foram utilizados capacitores cerâmicos pois o sentido da corrente pode inverter conforme o sentido de giro dos motores.
  
</details>

<details>
  <summary>💽 Capacitor de 1000µF entre os terminais VM e GND do driver motor TB6612FNG [clique para expandir]</summary>

  Quando os motores A e B estão ligados, eles podem demandar picos de corrente em função de partidas ou frenagens. Esses picos fazem a tensão de alimentação oscilar.

  ![Corrente inrush](https://i.imgur.com/AXEOBzh.jpeg)

  Os picos de corrente são chamados de corrente *inrush*.

  Quando aplicamos uma tensão elétrica $V$ sobre os terminais do motor DC surge uma corrente elétrica $I$ nos enrolamentos do induzido. Essa corrente $I$, na presença do campo magnético $\overrightarrow{B}$ criado pelos ímãs internos do motor DC, gera uma força $F$ sobre as espiras das bobinas do induzido - fenômeno este que está de acordo com o princípio da Lei de Lorentz (inclusive, [fiz um trabalho sobre a Lei de Lorentz](https://docs.google.com/presentation/d/1fynI4v6RXC3prIWHDpS9ZRpDoe6CXCrVUi7HYExRhsw/edit?usp=sharing)! Nesse trabalho explico bem a fundo esse conceito físico).

  Porém, embora a corrente elétrica apareça rapidamente nas bobinas do induzido em função do campo elétrico $\overrightarrow{E}$ que estamos estabelecendo com a tensão $V$ aplicada aos terminais do motor (inclusive, aconselho assistir a [esse ótimo vídeo do canal AlphaPhoenix sobre a velocidade da eletricidade](https://www.youtube.com/watch?v=2Vrhk5OjBP8)), o motor não começa a girar instantaneamente.
  
  Ou seja, haverá um breve momento em que a corrente $I$ atravessará as bobinas do induzido com o induzido praticamente parado, e nesse breve momento é como se o induzido se comportasse como um curto-circuito, pois suas bobinas têm uma resistência $R$ muito baixa e atuam praticamente como se fossem indutores.

  Indutores em circuitos DC atuam como se fossem curto-circuito pois sua impedância $X_L$ é dada por $X_L = 2πfL$, e $f = 0Hz$ em um circuito DC (logo, $X_L = 0$). A única propriedade física das bobinas que se opõe à passagem da corrente $I$ é a sua resistência $R$, que é muito baixa.

  Pela Lei de Ohm, $I = \frac{V}{R}$. Portanto, se o denominador $R$ for muito pequeno, $I$ será muito grande. O quão grande? Bem, até o valor de pico da corrente *inrush*.

  Embora tenhamos explicado o motivo da corrente *inrush* surgir, não explicamos ainda o que faz ela "diminuir". Sabemos que deve ter algo a ver com a velocidade de giro do induzido, pois a curva da corrente *inrush* se comporta da seguinte maneira:
  * cresce conforme o induzido sai da posição parado e começa a adquirir velocidade;
  * atinge um pico quando o induzido atinge uma determinada velocidade;
  * decresce quando o induzido ultrapassa essa determinada velocidade;
  * estabiliza quando o induzido atinge sua velocidade nominal.

  O surgimento da corrente *inrush* estava relacionado à baixa resistência $R$ das bobinas. Entretanto, já que a resistência $R$ não muda conforme o induzido gira mais rápida ou mais lentamente, a resistência $R$ não deve ser a causa da estabilização da corrente $I$. Porém, é claro que o motivo da estabilização da corrente tem relação com o giro do induzido.

  E é justamente o giro do induzido a causa da estabalização. Assim que o motor começa a girar ocorre um fenômeno muito peculiar: o motor estabelece o que conhecemos por força contra-eletro motriz (ou $FCEM$) proporcional à sua velocidade - o que está de acordo com o princípio da Indução Eletromagnética de Faraday, que nos diz que a força eletromotriz $\epsilon$ gerada é proporcional à varição de fluxo magnético $ΔΦ$ e inversamente proporcional à variação do tempo $Δt$, ou $\epsilon = - \frac{ΔΦ}{Δt}$.

  Em outras palavras:
  * as bobinas do induzido são condutores em movimento dentro do campo magnético $\overrightarrow{B}$ dos ímãs do motor;
  * o campo magnético $overrightarrow{B}$ tem linhas de fluxo magnético $Φ$ que atravessam os condutores enquanto o induzido gira;
  * como os condutores estão em movimento, a quantidade de linhas de fluxo magnético $Φ$ está variando - logo, na verdade é um $ΔΦ$ alto com $Δt$ baixo;
  * $\epsilon = - \frac{ΔΦ}{Δt}$. O sinal negativo é uma consequência da Lei da Conservação de Energia (a tensão induzida se opõe à tensão original que a induziu);
  * $\epsilon = FCEM$.

  Certo! E o que tudo isso tem a ver com o capacitor de 1000µF entre os terminais VM e GND do TB6612FNG?

  Bem, embora "microFarad" (µF) possa soar como algo pequeno, esse valor de capacitância certamente não é pequeno. De fato, 1000µF é o suficiente para fornecer uma corrente elétrica "extra" quase que imediatamente quando o motor DC dá partida ou freia. A proximidade do capacitor dos terminais VM e GND torna a resposta ainda mais rápida.

  Se o capacitor não estivesse presente, haveria uma maior tendência de ocorrerem quedas de tensão na alimentação dos motores nos momentos de corrente *inrush*.
  
</details>

---

### Desenvolvimento do código

O código inicial e as versões com melhorias e alterações feitas pelo grupo estão listadas abaixo. A ordem é cronológica e conta sempre com o código integral, um vídeo e uma breve discussão sobre conceitos utilizados.

---

#### 13/10/2025

💾 [Código versão 1](https://gist.github.com/parodrigues-ipynb/be9dc512e9a064356e3e1a73c458425b)

🎥 [Vídeo B1-M1 rodando com a versão 1](https://imgur.com/a/WtTMg6K)

<details>
  <summary>📝 Comentários sobre o código versão 1 [clique para expandir]</summary>
  
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

Decidiu-se utilizar o LEDC já que ela é nativa da ESP32 e já familiariza os alunos com as funções.

É possível controlar frequência e resolução com `analogWrite()` através de `analogWriteFrequency()` e `analogWriteResolution()`. Porém, esse controle afeta todos os canais PWM simultaneamente. A vantagem do LEDC é que ele permite especificar frequências e resoluções distintas para cada canal.

<details>
  <summary>📝 Comentários sobre o código versão 2 [clique para expandir]</summary>

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

🎥 [Vídeo B1-M1 rodando com a versão 3](https://imgur.com/a/VA4kzjJ)

Nesta versão as ocorrências de `delay()` foram substituídas por `millis()`.

O uso de técnicas como a do `millis()` é o padrão para sistemas embarcados que precisam reagir a múltiplos eventos em tempo real, como é o caso do B1-M1.

`delay()` seria um gargalo para o funcionamento do B1-M1 pois essa é uma função **bloqueante**. Isso significa que outras tarefas não serão executadas durante a espera instaurada por `delay()`: o programa irá ficar "travado" naquele ponto por aquela duração de tempo - o que é inviável para uma premissa multitarefas.

Foram consultados os excelentes artigos abaixo para aprender mais sobre as boas práticas de utilização da função `millis()`.

📔 [Artigo "Usando millis() para contagem de tempo - Uma introdução para iniciantes"](https://forum.arduino.cc/t/using-millis-for-timing-a-beginners-guide/483573)

📔 [Artigo "Código de demonstração para diversas coisas que ocorrem simultaneamente"](https://forum.arduino.cc/t/demonstration-code-for-several-things-at-the-same-time/217158/2)

<details>
  <summary>📝 Comentários sobre o código versão 3 [clique para expandir]</summary>

  ```ino
  unsigned long intervaloLeituras = 200; // [ms]
  unsigned long ultimoMillis = 0;        // [ms]
  ```

  Foram criadas duas variáveis do tipo `unsigned long` para trabalhar em conjunto com a lógica de controle temporal através do `millis()`.

  O uso de `unsigned long` é importante pois esse é o tipo de variável usado internamente por `millis()`.

  ```ino
  void loop() {
    unsigned long agora = millis(); // [ms]
  
    if (agora - ultimoMillis >= intervaloLeituras) {
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

---

#### 15/10/2025

💾 [Código versão 4](https://gist.github.com/parodrigues-ipynb/aec2492d27c355218dc54208086fcc25)

🎥 [Vídeo B1-M1 rodando com a versão 4](https://imgur.com/a/nlTqG0y)

Nesta versão houve melhoria na robustez da função `medirDistancia()`, que passou a fazer uma amostragem de 5 leituras e retornar a média dessas leituras. Isso é uma filtragem simples.

Além disso, os macros `VELOCIDADE_SOM_CM_US`, `DISTANCIA_MINIMA_CM`, `DISTANCIA_MAXIMA_CM` e `TIMEOUT_US` foram promovidos a variáveis (parabéns para eles 🎉).

O motivo desta alteração é que esses valores participam ou participarão em cálculos realizados ao longo do projeto. Por conta disso, o grupo desejou ter controle sobre o tipo dessas variáveis para ter mais previsibilidade sobre os resultados das operações matemáticas e tipos (`int`, `long`, `float`...) desses resultados.

<details>
  <summary>📝 Comentários sobre o código versão 4 [clique para expandir]</summary>

  ```ino
  // HC-SR04 - Sensor de distância
  #define TRIG 27
  #define ECHO 14
  constexpr float VELOCIDADE_SOM_CM_US = 0.0343;   // [cm/µs] Velocidade do som a 20°C
  constexpr float DISTANCIA_MINIMA_CM = 30;        // [cm]
  constexpr float DISTANCIA_MAXIMA_CM = 100;       // [cm]
  constexpr unsigned long TIMEOUT_US = 20000;      // [µs]
  constexpr uint8_t NUMERO_AMOSTRAS = 5;           // [amostras] Quantidade de leituras que o HC-SR04 coleta para fazer a média em uma filtragem simples
  constexpr uint8_t INTERVALO_ENTRE_AMOSTRAS = 10; // [ms] Tempo de espera entre cada leitura para que o som possa se dissipar e não gere ruído
  ```
  As variáveis `NUMERO_AMOSTRAS` e `INTERVALO_ENTRE_AMOSTRAS` foram criadas como parâmetros para a função `medirDistancia()`.
  
  O valor de 5 amostras foi escolhido por ser um equilíbrio bom entre estabilidade e tempo de resposta.

  O valor de 10ms para tempo de espera foi escolhido para permitir a dissipação das ondas sonoras no ambiente antes de emitir um novo pulso ultrassônico.

  ```ino
  float medirDistancia() {
    float somaDistancias = 0;
  
    for(int i = 0; i < NUMERO_AMOSTRAS; i++) {
      // Dispara pulso ultrassônico
      digitalWrite(TRIG, LOW);
      delayMicroseconds(2);
      digitalWrite(TRIG, HIGH);
      delayMicroseconds(10);
      digitalWrite(TRIG, LOW);
  
      // Calcula a distância de cada amostra e soma
      long duracao = pulseIn(ECHO, HIGH, TIMEOUT_US);
      float distancia = duracao * VELOCIDADE_SOM_CM_US / 2; // [cm]
      somaDistancias += distancia;
  
      // Espera utilizando millis() para que o som possa se dissipar e não afete leituras futuras
      unsigned long inicioEspera = millis();
      while (millis() - inicioEspera < INTERVALO_ENTRE_AMOSTRAS) {
        yield();
      }
    }
  
    float media = somaDistancias / NUMERO_AMOSTRAS;
    return media;
  }
  ```
  Foi criada a variável `somaDistancias` e toda a lógica anterior da função `medirDistancia()` foi colocada dentro do laço de repetição `for(int i = 0; i < NUMERO_AMOSTRAS; i++)`.

  O uso do laço `for()` ainda não é a solução ideal para um robô multitarefas como o B1-M1 em função de propriedades semi-bloqueantes do `for()`, mas o grupo quis apenas validar a filtragem simples nessa versão.

  O laço `while (millis() - inicioEspera < INTERVALO_ENTRE_AMOSTRAS)` foi inserido para evitar ruído nas leituras.

</details>

---

#### 15/10/2025

💾 [Código versão 5](https://gist.github.com/parodrigues-ipynb/b011a81d9a11b35db54fa2a64b99e691)

🎥 [Vídeo B1-M1 rodando com a versão 5](https://imgur.com/a/nlTqG0y)

Nesta versão foi introduzida uma lógica de tratamento de ruídos na função `medirDistancia()`.

A variável `TIMEOUT_US` passou a ter um valor dinâmico com base nas variáveis `DISTANCIA_MAXIMA_CM` e `VELOCIDADE_SOM_CM_US`.

<details>
  <summary>📝 Comentários sobre o código versão 5 [clique para expandir]</summary>

  ```ino
  float medirDistancia() {
    float somaDistancias = 0;
    uint8_t leiturasValidas = 0;
  
    for (int i = 0; i < NUMERO_AMOSTRAS; i++) {
      // Dispara pulso ultrassônico
      digitalWrite(TRIG, LOW);
      delayMicroseconds(2);
      digitalWrite(TRIG, HIGH);
      delayMicroseconds(10);
      digitalWrite(TRIG, LOW);
  
      // Calcula a distância de cada amostra e soma
      long duracao = pulseIn(ECHO, HIGH, TIMEOUT_US);       // [µs]
      float distancia = duracao * VELOCIDADE_SOM_CM_US / 2; // [cm]
  
      // Verifica a validez da leitura
      if (duracao > 0 && distancia >= 2 && distancia <= DISTANCIA_MAXIMA_CM) {
        somaDistancias += distancia;
        leiturasValidas++;
      }
      
      // Espera utilizando millis() para que o som possa se dissipar e não afete leituras futuras
      unsigned long inicioEspera = millis();
      while (millis() - inicioEspera < INTERVALO_ENTRE_AMOSTRAS) {
        yield();
      }
    }
  
    if (leiturasValidas == 0) {
      return -1;
    }
  
    float media = somaDistancias / leiturasValidas;
    return media;
  }
  ```
  Para realizar o tratamento de erros, foi criada a variável `uint8_t leiturasValidas` para contabilizar a quantidade de amostras válidas durante a execução de `medirDistancia()`.
  
  Uma leitura/amostra é considerada válida se:
  - a variável `duracao` for maior que 0µs. O valor de `duracao` é determinado pela função `pulseIn() e é relativo à duração de tempo em que ECHO permaneceu em nível HIGH;
  - a variável `distancia` for maior ou igual a 2cm. O valor é calculado com base na `duracao` e na `VELOCIDADE_SOM_CM_US`;
  - a variável `distancia` for maior ou igual a `DISTANCIA_MAXIMA_CM`.
  
  A seguinte interpretação das leituras foi considerada
  
  | Situação                                              | Interpretação do B1-M1  | Ação B1-M1 |
  |-------------------------------------------------------|-------------------------|------------|
  | `leiturasValidas = 0`                                 | Os obstáculos estão mais distantes que `DISTANCIA_MAXIMA_CM` (até onde o B1-M1 "enxerga"), o ângulo de reflexão é desfavorável ou há um problema muito grave com as leituras. Enfim, o B1-M1 assume uma postura otimista e considera o caminho como livre  | `distancia == -1` → `moverFrente()` |
  | `0 < leiturasValidas < 5`                             | O B1-M1 já é capaz de detectar quando houve falhas de leitura, mas apenas as descarta por enquanto. O tratamento de erros está mais "refinando" o valor de `media` por enquanto | `distancia > DISTANCIA_MINIMA_CM` → `moverFrente()` |
  | `distancia <= DISTANCIA_MINIMA_CM && distancia != -1` | Algum obstáculo está nas iminências do B1-M1, então ele deve parar | `parar()` |

  ```ino
  constexpr unsigned long TIMEOUT_US = (2 * DISTANCIA_MAXIMA_CM) / VELOCIDADE_SOM_CM_US; // [µs] Limite de tempo de aguardo por eco
  ```
  A variável `TIMEOUT_US` agora é calculada dinamicamente. Isso permite maior flexibilidade no código no momento de alteração de parâmetros.

</details>
  
---

#### 16/10/2025

💾 [Código versão 6](https://gist.github.com/parodrigues-ipynb/9d698c0b5be52341f351f407901ce06d)

🎥 [Vídeo B1-M1 rodando com a versão 6](https://imgur.com/a/DJXzT0k)

Nesta versão foram adicionadas as variáveis, funções e trechos de códigos em `void setup()` e `void loop()` para começar a fazer uso dos sensores de velocidade encoder LM393.

📔 [Artigo "Ligação entre encoder LM393 e Arduino para medir ângulo e velocidade angular"](https://aleksandarhaber.com/interface-lm393-encoder-with-arduino-and-measure-the-angle-and-angular-velocity/)

<details>
  <summary>📝 Comentários sobre o código versão 6 [clique para expandir]</summary>

  ```ino
  // LM393 - Sensor de velocidade
  #define SENSOR_VELOCIDADE_MOTOR_A 34
  #define SENSOR_VELOCIDADE_MOTOR_B 35
  volatile unsigned long pulsosMotorA = 0;
  volatile unsigned long pulsosMotorB = 0;
  ```
  Foram definidos os pinos GPIO 34 e 35 através das diretivas `SENSOR_VELOCIDADE_MOTOR_A` e `SENSOR_VELOCIDADE_MOTOR_B` para receber os sinais dos pinos D0 dos sensores de velocidade dos motores A e B.

  As variáveis `pulsosMotorA` e `pulsosMotorB` são contadores de pulso.

  Quando o disco furado encoder gira os sensores infravermelhos passam a "ligar e desligar" - às vezes a luz infravermelha atravessa um furo do disco, às vezes é interrompida por uma das paredes do disco. Um pulso é justamente a transição de "ligado para desligado" ou "desligado para ligado". Mais para frente no código é definido como é contabilizado o pulso: se é na borda de descida (ligado para desligado) ou subida (desligado para ligado).

  Como os valores dessas variáveis podem ficar muito grandes, o tipo `unsigned long` foi adotado.

  Como são utilizadas funções de interrupção para contabilizar `pulsosMotorA` e `pulsosMotorB`, o tipo `volatile` deve indicar ao compilador que essas variáveis podem ser modificadas fora do fluxo normal do programa. 📼 [Esse vídeo](https://www.youtube.com/watch?v=QtyOiTw0oQc) ajudou os alunos a compreender melhor o conceito de interrupções. O trecho de código a seguir mostra essas funções em si.

  ```ino
  void IRAM_ATTR contarPulsosMotorA() { pulsosMotorA++; }
  void IRAM_ATTR contarPulsosMotorB() { pulsosMotorB++; }
  ```

  O atributo `IRAM_ATTR` é específico da ESP32 e serve para indicar ao compilador que a função deve ser armazenada na IRAM (*internal RAM*, ou *memória RAM interna*, se for permitido o pleonasmo). "ATTR" vem de *attribute*, que traduzido do Inglês significa *atributo*.

  O atributo `IRAM_ATTR` é necessário para que as funções `contarPulsosMotorA()` e `contarPulsosMotorB()` sejam executadas imediatamente quando o evento ocorre. Abaixo é especificado qual é o evento.

  ```ino
  // LM393 - Sensor de velocidade encoder
  pinMode(SENSOR_VELOCIDADE_MOTOR_A, INPUT);
  pinMode(SENSOR_VELOCIDADE_MOTOR_B, INPUT);
  attachInterrupt(digitalPinToInterrupt(SENSOR_VELOCIDADE_MOTOR_A), contarPulsosMotorA, RISING);
  attachInterrupt(digitalPinToInterrupt(SENSOR_VELOCIDADE_MOTOR_B), contarPulsosMotorB, RISING);
  ```

  Essas linhas foram inseridas em `void setup()` e dizem ao compilador quais são os eventos que devem fazer ele executar as funções `contarPulsosMotorA()` e `contarPulsosMotorB()`: uma borda de subida (RISING) nos pinos `SENSOR_VELOCIDADE_MOTOR_A` e `SENSOR_VELOCIDADE_MOTOR_B`.

  ```ino
  // LM393 - Sensor de velocidade encoder
  unsigned long pulsosA = pulsosMotorA;
  unsigned long pulsosB = pulsosMotorB;
  pulsosMotorA = 0;
  pulsosMotorB = 0;
  ```

  Por fim, houve a adição desse bloco em `void loop()`.
  
  Os valores dos pulsos dos sensores são armazenados e zerados a cada ciclo de `loop()` pois estamos medindo apenas a velocidade instantânea dos motores e não a distância percorrida - situação na qual deveríamos verificar o total acumulado.
  
</details>

---

#### 16/10/2025

💾 [Código versão 7](https://gist.github.com/parodrigues-ipynb/17f40759919c51057b26ca906bcfb080)

🎥 [Vídeo B1-M1 rodando com a versão 7](https://imgur.com/a/xP080Ys)

Nesta versão foram adicionadas variáveis e funções de movimento além de apenas andar para frente e parar.

O controle temporal dos testes das funções de movimento foi implementado utilizando `millis()` para refoçar o aprendizado dos conceitos

<details>
  <summary>📝 Comentários sobre o código versão 7 [clique para expandir]</summary>

  ```ino
  void moverTras() {
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, HIGH);
    ledcWrite(PWMA, pwmA);
    ledcWrite(PWMB, pwmB);
  }
  
  void girarEsquerda() {
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW);
    ledcWrite(PWMA, pwmA);
    ledcWrite(PWMB, pwmB);
  }
  
  void girarDireita() {
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, HIGH);
    ledcWrite(PWMA, pwmA);
    ledcWrite(PWMB, pwmB);
  }
  ```
  Estas foram as funções de movimento adicionadas.

  As funções `girarEsquerda()` e `girarDireita()` fazem o B1-M1 girar no ponto em que ele está no sentido especificado.

  ```ino
  // Controle do movimento temporizado para trás
  unsigned long tempoInicioTras = 0;     // [ms] Registro temporal do momento em que o B1-M1 começou o movimento para trás
  unsigned long duracaoTras = 1000;      // [ms] Tempo de duração do movimento para trás
  bool movendoTras = false;              // Flag para lógica do movimento para trás
  
  // Controle do movimento temporizado de giro
  unsigned long tempoInicioGiro = 0;     // [ms] Registro temporal do momento em que o B1-M1 começou o giro
  unsigned long duracaoGiro = 700;       // [ms] Tempo de duração do movimento de giro
  bool movendoGiro = false;              // Flag para lógica do movimento de giro
  ```
  Foram adicionadas as variáveis acima para controle temporal dos movimentos.

  ```ino
  void loop() {
    unsigned long agora = millis(); // [ms]
  
    // [TESTE MOVIMENTO] Verificação do movimento para trás
    if (movendoTras) {
      if (agora - tempoInicioTras >= duracaoTras) {
        girarEsquerda();
        movendoTras = false;
        movendoGiro = true;
        tempoInicioGiro = agora;
      }
      return;
    }
  
    // [TESTE MOVIMENTO] Verificação do movimento de giro
    if (movendoGiro) {
      if (agora - tempoInicioGiro >= duracaoGiro) {
        parar();
        movendoGiro = false;
      }
      return;
    }
  
    if (agora - ultimoMillis >= intervaloLeituras) {
      ultimoMillis = agora;
      
      float distancia = medirDistancia(); // [cm]
  
      // LM393 - Sensor de velocidade encoder
      noInterrupts();
      unsigned long pulsosA = pulsosMotorA;
      unsigned long pulsosB = pulsosMotorB;
      pulsosMotorA = 0;
      pulsosMotorB = 0;
      interrupts();
  
      if (pulsosA > 5 && pulsosB > 5) {
        if (distancia > DISTANCIA_MINIMA_CM || distancia == -1) {
          moverFrente();
        } else {
          girarDireita();
        }
      } else {
        moverTras();
        movendoTras = true;
        tempoInicioTras = agora;
      }
    }
  }
  ```
  Os blocos `if (movendoTras)` e `if(movendoGiro)` foram adicionados ao `void looop()` para checar o estado (`movendoTras` ou `movendoGiro`) em que o B1-M1 está a cada ciclo de `loop()`.

  É assumido na lógica do `loop()` que o B1-M1 está sempre andando para frente chamando a função `moverFrente()`. Portanto, não há checagem para esse estado neste teste.

  `noInterrupts()` e `interrupts()` foram funções utilizadas para realizar comparações lógicas com as variáveis `pulsosA` e `pulsosB`. O uso delas faz com que os valores de pulsos não mudem durante a atribuição, uma vez que eles são determinados por interrupções e poderiam ter valores ligeiramente diferentes.

  `if (pulsosA > 5 && pulsosB > 5)` foi a lógica utilizada para detectar colisões com objetos que estavam em ângulo desfavorável em relação ao sensor ultrassônico HC-SR04 ou fora da altura dele. A ideia por trás foi "se ambos motores estiverem com um giro apropriado, continue em frente. Se pelo menos um dos motores tiver um giro muito baixo ou 0, mova-se para trás, gire e volte a ir para frente".

</details>

---

#### 17/10/2025 e 18/10/2025

Nestes dias foi definida a estratégia de comunicação e acesso remoto do B1-M1.

A ESP32-CAM foi configurada e o seu funcionamento instalada no B1-M1 foi posto à prova.

🎥 [Vídeo B1-M1 rodando com câmera ESP32-CAM fazendo streaming](https://imgur.com/a/8KsLpTI)

<details>
  <summary>📝 Memorial das estratégias adotadas [clique para expandir]</summary>

  Os objetivos do B1-M1 são:
  1. mover-se seguindo uma rotina pré-determinada em um ambiente residencial plano e permitir controle remoto;
  2. registrar valores obtidos pelo sensoriamento ultrassônico e visual (fotografias) e permitir o stream (vídeo) durante o acesso remoto;
  3. comunicar-se com o Gemini através da API fornecida pelo Google a fim de obter instruções para movimento autônomo.
  
  Até essa sexta-feira chuvosa, o objetivo 1 está quase concluído: o B1-M1 já consegue receber rotinas e movimentar-se sozinho, mesmo que de maneira muito simples ainda.
  
  Porém, o B1-M1 ainda não consegue receber controle remoto via web. Ele também ainda não realiza telemetria e nem tem a ESP32-CAM configurada para realizar streaming.
  
  Foi feita uma pesquisa para definir a estratégia de comunicação e acesso remoto que o B1-M1. Procurou-se utilizar opções simples que permitissem ao grupo avançar nos objetivos e compreender cada etapa realizada.
  
  Foi definido que:
  * a ESP32 será configurada em modo Wi-Fi STA (cliente) e será conectada a um roteador Wi-Fi, servindo de ponto de acesso remoto;
  * a ESP32 será responsável por hospedar o servidor WebSocket, servindo uma página HTML que exibe os dados de telemetria, a stream da ESP32-CAM e envia comandos em tempo real;
  * a ESP32-CAM irá transmitir o streaming de vídeo via Wi-Fi na porta 81;
  * tanto a ESP32 quanto a ESP32-CAM **funcionarão localmente** numa mesma rede Wi-Fi;
  * será criado um túnel HTTPS remoto com a ferramenta [ngrok](https://ngrok.com/) para possibilitar o acesso remoto sem precisar configurar roteador;
  * o usuário acessa `http://<ip_esp32>/` e a página HTML exibe o vídeo vindo da ESP32-CAM via `<img src="http://<ip_esp32-cam>:81/stream">`;
  * o WebSocket envia comandos e recebe telemetria em tempo real.
  
  O fluxo adotado foi:
  ```
  Usuário (browser) → Túnel HTTPS → Roteador → ESP32 (WebSocket e controle dos motores e sensores)
                                      ↓
                         ESP-32CAM (vídeo MJPEG)
  ```

  ![Configurações ArduinoIDE](https://i.imgur.com/58JCrel.jpeg)
  
  As seguintes configurações foram utilizadas no ArduinoIDE para programação da ESP32-CAM:
  * `Tools → CPU Frequency: "240MHz (WiFi/BT)"`
  * `Tools → Flash Frequency: "80MHz"`
  * `Tools → Partition Scheme: "Huge APP (3MB No OTA/1MB SPIFFS)"`
  
  A board `AI Thinker ESP32-CAM` foi utilizada. Ela veio junto no pacote `esp32` da Espressif Systems no Boards Manager (`CTRL+SHIFT+B`) do ArduinoIDE.

  ![Bibliotecas ESP32 no ArduinoIDE](https://i.imgur.com/byRoTxa.jpeg)
  
  A biblioteca da ESP32 foi inserida da seguinte forma no ArduinoIDE:
  * `File → Preferences`, e então na linha `Additional boards manager URLs:` foi inserido `https://dl.espressif.com/dl/package_esp32_index.json`. Também foi inserido `https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json`.
  
  Com a board `AI Thinker ESP32-CAM` selecionada no ArduinoIDE, em `File → Examples → ESP32 → Camera → CameraWebServer` é possível localizar o exemplo base utilizado para programar a ESP32-CAM.
  
  Na aba `board_config.h` foi selecionada a board `#define CAMERA_MODEL_AI_THINKER // Has PSRAM` tirando essa linha dos comentários e deixando as demais comentadas.
  
  Na aba `CameraWebServer.ino` foram inseridos os credenciais da rede Wi-Fi local nas variáveis `const char *ssid` e `const char *password`.
  
  A variável `config.frame_size` teve seu valor ajustado para `FRAMESIZE_QVGA`. Esse *framesize* é apropriado para uma transmissão rápida e sem muita qualidade - ideal para o projeto.

  Logo abaixo da linha `sensor_t *s = esp_camera_sensor_get();` foram inseridas essas duas linhas:
  ```ino
  s->set_vflip(s, 1);
  s->set_hmirror(s, 1);
  ```

  Essas linhas são responsáveis por fazer a imagem captada pela câmera espelhar vertical e horizontalmente.

  ![Jumper entre GPIO0 e GND](https://i.imgur.com/QdL94Oa.jpeg)
  
  A ESP32-CAM foi conectada ao computador por cabo e um jumper foi colocado entre os pinos GPIO0 e GND, conforme a imagem acima. Após pressionar o botão `Upload` na ArduinoIDE, o botão `Flash` da ESP32-CAM foi pressionado brevemente após a compilação do ArduinoIDE completar para iniciar o modo flash da ESP32-CAM.

  🎥 [O processo descrito acima pode ser verificado nesse vídeo](https://imgur.com/a/ZGpJELn)

  Depois de completo o flash, a ESP32-CAM imprimiu pelo monitor serial o IP `192.168.0.11`. Foi acessado o link `http://192.168.0.11:81/stream` para verificar se o streaming estava funcionando e, para nossa alegria, estava!

  ![Streaming funcionando](https://i.imgur.com/X4qUtl7.jpeg)

  A ESP32-CAM foi prontamente montada no B1-M1 e foi verificado se era possível acessar o streaming enquanto o B1-M1 se movia.
  
  🎥 [O vídeo do funcionamento da ESP32-CAM no B1-M1 pode ser visto aqui](https://imgur.com/a/8KsLpTI).
</details>

---

#### 19/10/2025

Nesta versão foi implementado um WebServer na ESP32, que passou a hospedar uma página HTML que contém o `<img src="http://<ip_esp32-cam>:81/stream">` para exibir o streaming da ESP32-CAM.

💾 [Código versão 8](https://gist.github.com/parodrigues-ipynb/481f91f52f6bb0200ce5ec6a1855c48b)

🎥 [Vídeo B1-M1 rodando com a versão 8](https://imgur.com/a/bDEAqPS)

<details>
  <summary>📝 Comentários sobre o código versão 8 [clique para expandir]</summary>

  ```ino
  #include <WiFi.h>
  #include <WebServer.h>
  
  // Configurações rede Wi-Fi
  const char* SSID_REDE_WIFI = "Internet do Pedrinho 2.4 GHz";
  const char* SENHA_REDE_WIFI = "[conteúdo removido]";
  const char* URL_STREAM_CAMERA = "http://192.168.0.11:81/stream";
  WebServer server(80);
  ```

  Foram inseridas as linhas acima no código da ESP32 do B1-M1, junto com as bibliotecas `<WiFi.h>` e `<WebServer.h>`.

  As variáveis `SSID_REDE_WIFI`, `SENHA_REDE_WIFI` e `URL_STREAM_CAMERA` são apenas parâmetros constantes de configuração. O ideal seria que essas informações estivessem em um arquivo `.cpp` separado, mas o grupo ainda não aprendeu como implementar isso e não é algo crucial para a etapa atual.

  O tipo `const char*` é um ponteiro para caracteres constante. Ele foi utilizado porque as funções da biblioteca `<WiFi.h>` (como `WiFi.begin()`) esperam esse tipo de variável, e não objetos `String`. O uso de ponteiros evita conversões desnecessárias e economiza processamento.

  Para fins didáticos, cabe mencionar que ponteiros são endereços físicos de memória. Eles indicam, portanto, uma área fixa da memória (geralmente a memória flash já que essas variáveis foram declaradas com `const`). Já `Strings` alocam memória dinamicamente conforme são alteradas ou atribuídas. Como microcontroladores geralmente têm pouca memória RAM, ponteiros costumam ser mais eficientes e devem ser preferidos em casos como os das variáveis que armazenam o SSID, a senha e a URL da câmera.

  Há ainda outro tipo de variável para sequências de caracteres: o `char[]`, que cria vetores. Por exemplo, `char [] SSID = "Internet do Pedrinho 2.4GHz";` criaria um vetor cujos elemntos seriam os caracteres do SSID: `I`, `n`, `t`, `e`, `r`, `n`, `e`, `t`, ` `, `d`, `o`,... e assim por diante. O último elemento desse vetor seria preenchido por `\0`  para indicar o final do vetor. Portanto, o endereço físico apontado por `SSID` teria um valor ideal para armazenar o texto `Internet do Pedrinho 2.4GHz\0`.

  Talvez a SSID mude. Digamos que eu adquirisse a Internet do Pedrinho Um Bilhão GHz. Eu não conseguiria utilizar o mesmo espaço de memória para armazenar esse novo valor de forma segura, sem o risco de sobrescrever outras informações importantes na memória.

  Portanto, faz muito sentido que a biblioteca tenha essa predileção por ponteiros: eles tornam o processo todo mais seguro, eficiente e prático.
  
  A linha `WebServer server(80)`  cria um objeto do tipo `WebServer` configurado para utilizar o protocolo HTTP da porta `80`.

  | Parte do código  | Tipo                  | Função                                                                                          |
  |------------------|-----------------------|-------------------------------------------------------------------------------------------------|
  | `WebServer`      | Classe de um objeto   | Molde ou tipo de dado que define as características ou comportamento de algo. Neste caso, a classe WebServer foi criada para lidar com as funcionalidades de um servidor web.    *Nota:* Esta classe está na biblioteca `<WebServer.h>` |
  | `server()`       | Nome do objeto        | `WebServer` é o "molde para servidores". `server()` é o servidor que estamos criando.             |
  | `80`             | Argumento ou parâmetro| O número `80` é a porta padrão para tráfego de internet não criptografado (*HTTP - HyperText Transfer Protocol*). Ao passar o argumento `80`, estamos instruíndo o objeto `server()` a "ouvir" as requisições que chegam nessa porta. Quando um navegador web tenta se conectar à ESP32 usando o endereço IP dela, o navegador fará isso na porta `80` por padrão, permitindo que a comunicação entre o servidor e o cliente (navegador) seja estabelecida.    *Nota:* No contexto de redes de computadores, 'porta' é um número que identifica um serviço ou aplicação específica em um computador ou dispositivo. Dá para pensar em 'porta' como sendo o 'número da sala onde ocorrem determinadas atividades'. As portas são essenciais pois permitem a um dispositivo responda diversas requisições em diferentes portas simultaneamente. Inclusive, a porta para HTTPS (tráfego criptografado, seguro) é `443`. |
  
  **Exemplo prático**
  * Digamos que o IP da ESP32 seja `192.168.1.100`;
  * Se a gente digitar `http://192.168.1.100` em um navegador, esse navegador irá tentar, por padrão, se conectar à porta `80` da ESP32;
  * O objeto `server()` na ESP32 irá "receber" ou "escutar" essa requisição e, dependendo do resto do código, responderá com uma página HTML ou
  outra informação qualquer.

  ```ino
  void handleRoot() {
    String html = R"rawliteral(
      <!DOCTYPE html>
        <html>
          <head>
            <meta charset = "utf-8">
            <title>B1-M1</title>
            <style>
              body { text-align: center; background-color: #222; color: white; }
              img { width: 90%; max-width: 480px; border: 2px solid #444; margin-top: 20px; }
            </style>
          </head>
          <body>
            <h2>Stream da ESP32-CAM</h2>
            <img src=")rawliteral";
            html += URL_STREAM_CAMERA;
            html += R"rawliteral(">
          </body>
        </html>
    )rawliteral";
  
    server.send(200, "text/html", html);
  }
  ```
  A função `handleRoot()` foi criada para criar a página HTML exibida durante acessos ao WebServer da ESP32.

  Um *handler* é uma função criada para que um conjunto de ações seja realizado quando diferentes rotas do WebServer forem acessadas.

  Por exemplo, a rota padrão (ou rota raíz, *root* ou simplesmente `/`) da ESP32 é `http://<IP-da-ESP32>/` (a `/` final é o motivo de poder chamar a rota padrão de apenas `/`). O conjunto de ações dentro da função `handleRoot()` deve ser executado quando algum usuário acessar a rota padrão.

  A função começa com uma `String` chamada `html` que contém o código HTML da página que desejamos exibir ao usuário. O prefixo `R"rawliteral(...)rawliteral"` foi utilizado para facilitar a inclusão do bloco de código HTML utilizando múltiplas linhas numa mesma `String`.

  A linha `server.send(200, "text/html", html);` é típica em projetos de WebServer. 

  A função `send()` é chamada quando algum cliente (navegador) acessa a raíz (*root*) do servidor web (WebServer) da ESP32 (exemplo: `http://192.168.0.10/`).
  
  | Parte do código             | Tipo                  | Função                                                                                          |
  |-----------------------------|-----------------------|-------------------------------------------------------------------------------------------------|
  |`.send(200,<>,<>)`           | Código de status HTTP | '200' significa 'OK'. Ou seja, a requisição de acesso à *root* foi bem-sucedida.                  |
  |`.send(<>,"text/html",<>)`   | Definição do tipo de conteúdo enviado ao navegador  | `text/html` é o *MIME type* (ou *Content-Type*) que o servidor informa ao navegador sobre o tipo de dado que está sendo enviado na resposta. `text/html` diz ao navegador que o conteúdo retornado é um código HTML e deve ser interpretado/renderizado como uma página web. |
  |`.send(<>, <>, html)`| Conteúdo                      | Quando algum cliente acessar a página principal da ESP32 (raíz, ou *root*, ou `/`), envia como resposta o código de página HTML na variável `html` |

  ```ino
  void setup() {
    // Rede Wi-Fi
    Serial.begin(115200);
    WiFi.begin(SSID_REDE_WIFI, SENHA_REDE_WIFI);
    Serial.print("Conectando o B1-M1 à rede Wi-Fi ");
    Serial.print(SSID_REDE_WIFI);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    Serial.println("\nConexão estabelecida!");
    Serial.print("IP da ESP32: ");
    Serial.println(WiFi.localIP());
  
    server.on("/", handleRoot);
    server.begin();
    Serial.println("Servidor Wi-Fi do B1-M1 iniciado.");
  }
  ```
  As linhas acima foram adicionadas para iniciar a conexão Wi-Fi com a rede informada na variável `SSID_REDE_WIFI`.

  O IP da ESP32 é impresso no monitor da comunicação serial e então a linha `server.on("/", handleRoot)` configura que acessos de usuários à rota padrão devem chamar a função `handleRoot()`.

  ```ino
  void loop() {
    unsigned long agora = millis(); // [ms]
  
    // ┌------------------------------------------┐
    // |  Controle de movimento e sensoriamento   |
    // └------------------------------------------┘
  
    // Verificação do movimento para trás
    if (movendoTras) {
      ...
    }
  
    // Verificação do movimento de giro
    if (movendoGiro) {
      ...
    }
  
    if (agora - ultimoMillis >= intervaloLeituras) {
      ...
    }
  
    // ┌------------------------------------------┐
    // |  Processamento de requisições HTTP       |
    // └------------------------------------------┘
    server.handleClient();
  }
  ```
  A linha com o método `server.handleClient();` da biblioteca `<WebServer.h>` foi adicionada no final da função `void loop()`. Ela faz o servidor receber as solicitações dos usuários (ou *clients*).
  
</details>

---

#### 19/10/2025

💾 [Código versão 9](https://gist.github.com/parodrigues-ipynb/5c16661706b89709aed75a170137865f)

🎥 [Vídeo B1-M1 rodando com a versão 9](https://imgur.com/a/lSfCcor)

<details>
  <summary>📝 Comentários sobre o código versão 9 [clique para expandir]</summary>

  ```ino
  #include <WiFi.h>
  #include <AsyncTCP.h>
  #include <ESPAsyncWebServer.h>
  
  // Configurações rede Wi-Fi
  const char* SSID_REDE_WIFI = "Internet do Pedrinho 2.4 GHz";
  const char* SENHA_REDE_WIFI = "cachorronuclear";
  const char* URL_STREAM_CAMERA = "http://192.168.0.11:81/stream";
  AsyncWebServer server(80);
  AsyncWebSocket ws("/ws");
  bool modoManual = false; // Flag para verificar se algum usuário do WebServer está no modo manual do B1-M1
  ```
  As bibliotecas `<AsyncTCP.h>` e `<ESPAsyncWebServer.h>` foram adicionadas no cabeçalho do código do B1-M1.

  `<AsyncTCP.h>` implementa uma camada TCP assíncrona para a ESP32.

  TCP significa *Transmission Control Protocol*, ou *Protocolo de Controle de Transmissão*. TCP é o protocolo de transporte de dados usado pela internet para garantir que os dados enviados cheguem ao destino.
  
  Por exemplo, digamos que o navegador esteja enviando dados para a ESP32. Esses dados são divididos em pacotes IP - pequenos blocos numerados que viajam por roteadores e redes diferentes até chegar ao destino, que é a ESP32. Abaixo está uma imagem exemplo de um pacote.
  
  ![Pacote IP](https://i.imgur.com/5jAjZOZ.jpeg)
  
  A internet é composta por milhares de roteadores e enlaces físicos (cabos, fibra, Wi-Fi, rádio...). Durante o transporte dos pacotes, falhas comuns e inevitáveis em redes grandes como a internet são:
  * os pacotes atrasarem (latência);
  * os pacotes chegarem fora de ordem;
  * algum roteador descartar pacotes se estiver sobrecarregado (congestionamento);
  * alguma interferência eletromagnética corromper bits (erro de transmissão);
  * conexões Wi-Fi falharem temporariamente em função de sinal fraco ou ruído.
  
  O TCP foi projetado para lidar com essas imperfeições. Ele:
  * numera cada pacote para que o receptor saiba a ordem correta dos pacotes;
  * faz o destino confirmar o recebimento (ACK - *acknowledge*, ou *reconhecimento*) dos pacotes enviando mensagens como "recebi o pacote X";
  * se um tempo limite for excedido sem ACK desde o envio, faz o remetente reenviar pacotes não reconhecidos;
  * verifica a integridade de cada pacote através de uma [soma de verificação (*checksum*)](https://pt.wikipedia.org/wiki/Soma_de_verifica%C3%A7%C3%A3o);
  * remonta os dados no destino seguindo a ordem e garantindo a completude dos pacotes.
  
  Existem protocolos que não aplicam controle de erros, como o UDP (*User Datagram Protocol*, ou *Protocolo de Datagrama do Usuário*). O fato do envio não depender de esperar confirmações torna a comunicação mais rápida.
  
  ![TCP vs. UDP](https://i.imgur.com/3Lm5mss.jpeg)
  
  Normalmente TCP é utilizado para dados que não podem se perder, enquanto que UDP é usado para dados que podem ser descartados sem problemas.
  
  Em resumo,
  |Protocolo | Tipo          | Reenvia pacotes? | Ordem dos pacotes garantida? | Exemplo de uso                |
  |----------|---------------|:----------------:|:----------------------------:|-------------------------------|
  |TCP       | Confiável     | Sim              | Sim                          | Web, WebSocket, HTTP          |
  |UDP       | Não confiável | Não              | Não                          | Streaming, jogos online, VoIP |
  
  O meme abaixo ajudou os alunos a fixar o conteúdo sobre UDP e TCP.
  
  ![Meme didático](https://i.imgur.com/xA05ZFi.jpeg)

  Já o termo "comunicação assíncrona" significa que o programa não espera que uma operação termine para continuar sua execução.

  Na comunicação síncrona (bloqueante), o B1-M1 iria "congelar" durante a comunicação, pois iria **esperar cada operação terminar para dar sequência**. Quando ele atendesse a uma requisição da interface web, a ESP32 travaria momentaneamente a leitura dos sensores ultrassônicos ou o controle dos motores A e B. Isso é muito ruim para um robô multitarefas.

  Na comunicação assíncrona (não bloqueante), o B1-M1 continuaria ativo durante a comunicação, pois iria **utilizar eventos** para chamar funções de callback somente no momento de chegada dos dados, sem travar o restante do código durante o aguardo dos dados.

  Com a biblioteca `<AsyncTCP.h>` é possível manter o servidor HTTP aceitando conexões, manter os WebSockets recebendo comandos e manter o B1-M1 realizando o sensoriamento e controle dos motores.

  A biblioteca `<ESPAsyncWebServer.h>` é a versão assíncrona da `<WebServer.h>`.

  As linhas `AsyncWebServer server(80);` e `AsyncWebSocket ws("/ws");` inicializam objetos para criação do WebServer assíncrono e os WebSockets.

  WebSockets são um protocolo de comunicação bidirecional e contínua entre cliente e servidor. Eles operam sobre TCP.

  | Aspecto               | HTTP                                                       | WebSocket                                                                       |
  |-----------------------|------------------------------------------------------------|---------------------------------------------------------------------------------|
  | Modelo de comunicação | Unidirecional / Requisição (Cliente) → Resposta (Servidor) | Bidirecional                                                                    |
  | Conexão               | Abre e fecha a cada requisição                             | Conexão única e persistente                                                     |
  | Latência              | Alta (*handshake* e cabeçalhos a cada requisição)          | Baixa (canal aberto após o *handshake* inicial)                                 |
  | Uso típico            | Páginas web, APIs REST, requisições ocasionais             | Aplicações em tempo real (chats, telemetria, jogos online, controle remoto)     |
  | Transporte            | HTTP/HTTPS                                                 | TCP (com *handshake* inicial via HTTP, depois muda de protocolo para WebSocket) |

  Ou seja, HTTP é ideal para trocas ocasionais de dados (*pull*), enquanto que WebSocket é projetado para comunicação contínua e instantânea (*push/pull* em tempo real).

  ```ino
  void onWsEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len) {
    if (type == WS_EVT_DATA) {
      String cmd = String((char*)data).substring(0, len);
      cmd.trim();
      Serial.println("Comando recebido: " + cmd);
  
      if (cmd == "frente") {
        modoManual = true;
        moverFrente();
      } else if (cmd == "tras") {
        modoManual = true;
        moverTras();
      } else if (cmd == "esquerda") {
        modoManual = true;
        girarEsquerda();
      } else if (cmd == "direita") {
        modoManual = true;
        girarDireita();
      } else if (cmd == "parar") {
        modoManual = true;
        parar();
      } else if (cmd == "automatico") {
        modoManual = false;
      }
    }
    Serial.println(modoManual ? "Modo manual do B1-M1 ativado." : "Modo automático do B1-M1 ativado.");
  }
  ```
  A função `void onWsEvent()` foi adicionada ao código.

  Essa função é um manipulador de eventos do protocolo WebSocket. É ela quem define o que a ESP32 deve fazer quando um evento ocorre na conexão WebSocket. No caso do B1-M1, ela está tratando os comandos enviados ao robô B1-M1 por controle remoto via WebSocket.

  A função tem a seguinte assinatura:
  * `server`: ponteiro para o servidor WebSocket;
  * `client`: ponteiro para o cliente que enviou a mensagem;
  * `type`: tipo do evento (conexão, desconexão, erro ou dados recebidos);
  * `arg`: argumento adicional (usado em eventos específicos);
  * `data`: ponteiro para os dados recebidos (mensagem);
  * `len`: tamanho da mensagem.

  A linha `if (type == WS_EVT_DATA)` descreve bem o funcionamento do protocolo WebSocket com TCP assíncrono: ações somente são tomadas em caso de eventos (WS_EVT_DATA) específicos.

  As linhas `String cmd  String((char*)data).substring(0, len);` e `cmd.trim();` convertem os bytes recebidos em `data` para o tipo `String`. `.trim()` remove os espaços em branco no começo e no final da mensagem.

  ```ino
  const char paginaHTML[] PROGMEM = R"rawliteral(
    <!DOCTYPE html>
        <html>
          <head>
            <meta charset = "utf-8">
            <title>B1-M1</title>
            <style>
              body { text-align: center; background-color: #222; color: white; font-family: sans-serif; }
              button { width: 100px; height: 50px; margin: 5px; font-size: 16px; }
              img { width: 90%; max-width: 480px; border: 2px solid #444; margin-top: 20px; }
            </style>
          </head>
          <body>
            <h2>Stream da ESP32-CAM</h2>
            <img id="cam" src="{{URL_ESP32_CAM}}">
            <h2>Comandos para o B1-M1</h2>
            <div>
              <button onclick="enviar('frente')">Frente</button><br>
              <button onclick="enviar('esquerda')">Esquerda</button>
              <button onclick="enviar('parar')">Parar</button>
              <button onclick="enviar('direita')">Direita</button><br>
              <button onclick="enviar('tras')">Trás</button><br>
              <button onclick="enviar('automatico')">Modo automático</button>
            </div>
            <script>
              const ws = new WebSocket("ws://" + location.host + "/ws");
              function enviar(cmd){ ws.send(cmd); }
            </script>
          </body>
        </html>
  )rawliteral";
  ```
  A página HTML teve sua estrutura armazenada desta vez numa variável própria na linha `const char paginaHTML[] PROGMEM`.

  `const char paginaHTML[]` define uma array constante de caracteres: uma String. Como `[]` está vazio, o compilador calcula o tamanho automaticamente.

  Por exemplo, `const char texto[] = "ABC";` é uma array de 4 elementos: `A`, `B`, `C` e `\0`, que é o terminador nulo da array.

  `PROGMEM` é uma diretiva que instrui ao compilador que ele deve armazenar a variável na memória flash ao invés da memória RAM. Essa diretiva é muito útil para poupar espaço da memória RAM ao lidar com variáveis muito grandes como é o caso da `paginaHTML`.

  ```ino
  void setup() {
    // Rede Wi-Fi
    Serial.begin(115200);
    WiFi.begin(SSID_REDE_WIFI, SENHA_REDE_WIFI);
    Serial.print("Conectando o B1-M1 à rede Wi-Fi ");
    Serial.print(SSID_REDE_WIFI);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    Serial.println("\nConexão estabelecida!");
    Serial.print("IP da ESP32: ");
    Serial.println(WiFi.localIP());
    // WebSocket
    ws.onEvent(onWsEvent);
    server.addHandler(&ws);
    // Página principal
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
      String html = FPSTR(paginaHTML);
      html.replace("{{URL_ESP32_CAM}}", URL_STREAM_CAMERA);
      request->send(200, "text/html", html);
    });
    server.begin();
    Serial.println("Servidor WebSocket do B1-M1 iniciado!");
  ```
  Dentro da função `void setup()` houve o acréscimo da lógica de eventos do WebSocket.

  No bloco do `server.on()` há uma lógica para substituir a ocorrência de `{{URL_ESP32_CAM}}` na array `paginaHTML` por `URL_STREAM_CAMERA`.

  Na linha `request->send(200, "text/html", html);` há o uso do operador `->`, que é utilizado quando temos um ponteiro. Por exemplo,

  ```cpp
  class Cachorro {
    public:
      void latir() { Serial.println("Au au!"); }
  };

  Cachorro bernadete;       // Esse objeto é minha cadela, que é um cachorro
  Cachorro* b = &bernadete; // Ponteiro para o objeto

  bernadete.latir();    // Acesso direto que faz a Bernadete latir
  b->latir();           // Acesso via ponteiro que faz a Bernadete latir. É equivalente a (*b).latir()
  ```

  No caso dessa linha, `request` é um ponteiro para um objeto `AsyncWebServerRequest`. `->send()` chama o método `send()` desse objeto. Esse método chama a resposta HTTP padrão conforme já vimos no código anterior.

</details>

---

### 20/10/2025

Nesta versão foram adicionadas funções e trechos de código em funções já existentes para implementar o funcionamento da telemetria do B1-M1 através da página HTML do WebServer assíncrono WebSocket.

💾 [Código versão 10](https://gist.github.com/parodrigues-ipynb/958ebaa8788f99ceea95b4e497a6b2e0)

🎥 [Vídeo B1-M1 rodando com a versão 10]()

<details>
  <summary>📝 Comentários sobre o código versão 10 [clique para expandir]</summary>

  ```ino
  // LM393 - Sensor de velocidade encoder
  #define SENSOR_VELOCIDADE_MOTOR_A 34
  #define SENSOR_VELOCIDADE_MOTOR_B 35
  volatile unsigned long pulsosMotorA = 0;
  unsigned long pulsosA = 0;                // Clone de armazenamento
  volatile unsigned long pulsosMotorB = 0;
  unsigned long pulsosB = 0;                // Clone de armazenamento
  float distancia = 0;
  ```
  As variáveis `pulsosA`, `pulsosB` e `distancia` passaram a ter escopo global para que seu uso possa ser compartilhado com a telemetria. Antes essas variáveis estavam dentro do `void loop()`, no seguinte trecho:

  ```ino
  distancia = medirDistancia(); // [cm]

  // LM393 - Sensor de velocidade encoder
  noInterrupts();
  pulsosA = pulsosMotorA;
  pulsosB = pulsosMotorB;
  pulsosMotorA = 0;
  pulsosMotorB = 0;
  interrupts();
  ```

  ```ino
  const char paginaHTML[] PROGMEM = R"rawliteral(
    <!DOCTYPE html>
    <html>
  
    <head>
        <meta charset="utf-8">
        <title>B1-M1</title>
        <style>
            body {
                text-align: center;
                background-color: #222;
                color: white;
                font-family: sans-serif;
            }
  
            button {
                width: 100px;
                height: 50px;
                margin: 5px;
                font-size: 16px;
            }
  
            .painel {
                display: flex;
                justify-content: center;
                align-items: flex-start;
                gap: 20px;
                margin-top: 20px;
            }
  
            .painel img {
                width: 480px;
                max-width: 90%;
                border: 2px solid #444;
            }
  
            .coluna-lateral {
                display: flex;
                flex-direction: column;
                align-items: center;
                gap: 20px;
            }
  
            .telemetria {
                text-align: left;
                background-color: #333;
                border: 1px solid #444;
                padding: 15px;
                width: 250px;
                border-radius: 8px;
            }
  
            @media (max-width: 700px) {
                .painel {
                    flex-direction: column;
                    align-items: center;
                }
  
                .telemetria {
                    width: 90%;
                }
            }
        </style>
    </head>
  
    <body>
        <h2>Streaming do B1-M1</h2>
  
        <div class="painel">
            <!-- Imagem à esquerda -->
            <img id="cam" src="{{URL_ESP32_CAM}}">
  
            <!-- Lateral direita com telemetria e botões -->
            <div class="coluna-lateral">
                <div class="telemetria" id="info">Aguardando dados de telemetria...</div>
                <div>
                    <h3>Comandos</h3>
                    <button onclick="enviar('frente')">Frente</button><br>
                    <button onclick="enviar('esquerda')">Esquerda</button>
                    <button onclick="enviar('parar')">Parar</button>
                    <button onclick="enviar('direita')">Direita</button><br>
                    <button onclick="enviar('tras')">Trás</button><br>
                    <button onclick="enviar('automatico')">Modo automático</button>
                </div>
            </div>
        </div>
  
        <script>
            const ws = new WebSocket("ws://" + location.host + "/ws");
            function enviar(cmd) { ws.send(cmd); }
            ws.onmessage = (event) => {
                const d = JSON.parse(event.data);
                document.getElementById("info").innerHTML =
                    `Distância: ${d.distancia} cm<br>` +
                    `Pulsos motor A: ${d.pulsosA} | Pulsos motor B: ${d.pulsosB}<br>` +
                    `Modo atual: ${d.modo}`;
            };
        </script>
    </body>
  
    </html>
  )rawliteral";
  ```
  O layout da página HTML do B1-M1 teve modificações para que a exibição do streaming, da telemetria e dos comandos de movimento fique contida numa tela de exibição de navegador *desktop*.

  ```ino
  // Telemetria
  void enviarTelemetria() {
    if (ws.count() == 0) return;
  
    String dados = "{";
    dados += "\"distancia\":" + String(distancia, 1) + ",";
    dados += "\"pulsosA\":" + String(pulsosA) + ",";
    dados += "\"pulsosB\":" + String(pulsosB) + ",";
    dados += "\"modo\":\"" + String(modoManual ? "manual" : "automatico") + "\"";
    dados += "}";
  
    ws.textAll(dados);
  }
  ```
  A função `void enviarTelemetria()` foi criada para comunicar através do protocolo WebSocket os dados da telemetria para exibição na página HTML.

  A variável `String dados` contém uma concatenação dos dados. Embora tenha um resultado mais legível para os autores, não utilizou-se *raw string literals* (`R"rawliteral(...)rawliteral`) e *placeholders* (`{{...}}`) e `String.replace()`. O motivo foi por eficiência.

  O método `String.replace()` cria várias cópias intermediárias, o que pode consumir mais RAM e fragmentar a *heap memory* (*memória dinâmica*) no ESP32 se for chamado com frequência. *Heap memory* é uma região da RAM usada para alocações em tempo de execução - ou seja, um espaço para dados cujo tamanho só é conhecido enquanto o programa está rodando.

  Como a função `enviarTelemetria()` pode executar mais de uma ou duas vezes por segundo, optou-se pelo método da concatenação de `string` ao invés de correr o risco de ter muitas alocações extras.

  O método `.textAll()` está na biblioteca `<ESPAsyncWebServer.h>`. Ele envia uma mensagem de texto (`string`) para todos os clientes WebSocket conectados ao servidor naquele momento. O envio é através de uma mensagem JSON.

  ```ino
  void loop() {
    unsigned long agora = millis(); // [ms]
  
    // Verificação do movimento para trás
    if (movendoTras) {
      if (agora - tempoInicioTras >= duracaoTras) {
        girarEsquerda();
        movendoTras = false;
        movendoGiro = true;
        tempoInicioGiro = agora;
      }
      yield();
      return;
    }
  
    // Verificação do movimento de giro
    if (movendoGiro) {
      if (agora - tempoInicioGiro >= duracaoGiro) { parar(); movendoGiro = false; }
      yield();
      return;
    }
  
    if (modoManual) {
      yield();
      return;
    }
  
    if (agora - ultimoMillis >= intervaloLeituras) {
      ultimoMillis = agora;
      
      distancia = medirDistancia(); // [cm]
  
      // LM393 - Sensor de velocidade encoder
      noInterrupts();
      pulsosA = pulsosMotorA;
      pulsosB = pulsosMotorB;
      pulsosMotorA = 0;
      pulsosMotorB = 0;
      interrupts();
  
      enviarTelemetria();
      ws.cleanupClients();
  
      if (pulsosA > 5 && pulsosB > 5) {
        if (distancia > DISTANCIA_MINIMA_CM || distancia == -1) {
          moverFrente();
        } else {
          girarDireita();
        }
      } else {
        moverTras();
        movendoTras = true;
        tempoInicioTras = agora;
      }
    }
    yield();
  }
  ```
  A função `enviarTelemetria()` foi adicionada ao `void loop()`. O método `cleanupClients()` teve sua posição transferida para logo após a `enviarTelemetria()`.

</details>

---

### 26/10/2025

Nesta versão foi instalado, calibrado e integrado um sensor LSM303DHLC GY511 para a adição de uma bússola digital ao B1-M1.

Também foi adotada a arquitetura de transmissão de dados através do protocolo MQTT.

💾 [Código versão 11](https://gist.github.com/parodrigues-ipynb/699cc992c6e68aecfd2559a6be93e43e)

🎥 Não houve necessidade de vídeo nessa versão

<details>
  <summary>📝 Comentários sobre o código versão 11 [clique para expandir]</summary>

  Foi instalada a biblioteca `LSM303` da Pololu no ArduinoIDE.

  Foi utilizado [este script](https://gist.github.com/parodrigues-ipynb/99d4b30a8cf4a63b18cbad1b848596ad) para coleta dos dados crus do LSM303. A seguir seguem comentários sobre este script e seu funcionamento.

  ```ino
  #include <Wire.h>
  #include <LSM303.h>
  LSM303 bussola;
  ```
  `#include <Wire.h>` habilita a comunicação I²C, que é o protocolo de comunicação serial utilizado pelo LSM303.

  `LSM303 bussola;` cria um objeto que representa o módulo físico do LSM303.

  ```ino
  Serial.begin(115200);
  Wire.begin(21, 22); // (SDA, SCL)
  bussola.init();
  bussola.enableDefault();
  delay(200);
  Serial.println("mx,my,mz,ax,ay,az"); // cabeçalho CSV
  ```
  `Wire.begin(21,22);` informa os pinos da ESP32 para SDA (*Serial Data*) e SCL (*Serial Clock*).

  O método `.init()` inicializa a comunicação com os sensores (acelero e magnetômetro). `.enableDefault()` aplica as configurações padrão de ganho e sensibilidade.

  `delay(200)` dá tempo para os sensores estabilizarem após ligados.

  O `.println()` é utilizado para coletar os dados para posterior envio a um documento `.csv`.

  ```ino
  bussola.read();
  Serial.print(bussola.m.x); Serial.print(",");
  Serial.print(bussola.m.y); Serial.print(",");
  Serial.print(bussola.m.z); Serial.print(",");
  Serial.print(bussola.a.x); Serial.print(",");
  Serial.print(bussola.a.y); Serial.print(",");
  Serial.println(bussola.a.z);
  delay(40); // ~25 Hz
  ```
  O método `.read()` faz a leitura dos dois sensores (acelero e magnetômetro). O valor em cada eixo (`x`, `y` e `z`) é enviado pela comunicação serial I²C, separados por vírgula, conforme padrão do `.csv`.

  O `delay(40)` é utilizado para gerar 25 amostras por segundo ($\frac{1000 ms}{40 ms} = 25 Hz$).

  🎥 [Vídeo da coleta de dados crus dos sensores acelero e magnetômetro](https://imgur.com/a/g4aFAeq)

  Para armazenar os dados, foi instalado o [software PuTTY](https://www.chiark.greenend.org.uk/~sgtatham/putty/latest.html), que foi configurado conforme a imagem abaixo. Foi necessário executar o PuTTY como administrador para ter acesso à comunicação serial da porta `COM10`. O path do arquivo escolhido foi `C:\Users\Usuario\Desktop\mag_data.csv`.

  ![Configuração PuTTY](https://i.imgur.com/iNb3KOO.jpeg)

  É importante notar que às vezes o PuTTY gera um cabeçalho com informações além dos dados coletados. Para corrigir isso, basta abrir o arquivo e remover as primeiras linhas até que ele fique semelhante à imagem abaixo.

  ![.csv do PuTTY corrigido](https://i.imgur.com/px6s7yR.jpeg)

  [Este script Python](https://gist.github.com/parodrigues-ipynb/0648d8b6c1c98801b7eef37fe56ecd2d) foi desenvolvido para calibração dos dados coletados pelos sensores magneto e acelerômetro. O script também imprime gráficos para comparação da leitura de dados dos sensores antes e depois da calibração.

 🎥 [Excelente vídeo que fala sobre a calibração dos dados dos sensores acelero e magnetômetro](https://www.youtube.com/watch?v=MinV5V1ioWg)

 🎥 [Ótimo vídeo para visualizar a causa das distorções hard-iron e soft-iron](https://www.youtube.com/watch?v=cGI8mrIanpk&t=196s)

  Os dois arquivos foram colocados no desktop, conforme a imagem abaixo.

  ![Arquivos](https://i.imgur.com/GnDEfEX.jpeg)

  O Windows PowerShell foi aberto no Desktop e o script Python foi executado com a linha de comando `python calib_lsm303.py mag_data.csv`, conforme a caixa amarela na imagem abaixo. O script retornou os valores de offset e scale para calibração dos sensores, assim como criou uma pasta contendo as imagens dos gráficos dos dados antes e depois da calibração, conforme a caixa laranja na mesma imagem.

  ![Execução do script Python](https://i.imgur.com/pGMKVM1.jpeg)

  A imagem abaixo apresenta os gráficos obtidos com a análise dos dados do .csv.

  ![Gráficos](https://i.imgur.com/TcS6qUt.jpeg)

  🎥 [Vídeo comparando os gráficos tridimensionalmente](https://imgur.com/a/l8q1bQo)

  Após a calibração, observou-se que a versão calibrada estava elipsoidal nos planos x, y e x, z na visualização 3D. Isso se deve à escala distorcida na visualização.

</details>

---

### 26/10/2025

Nesta versão foi implementado o módulo LSM303DHLC GY511 para servir de bússola digital no B1-M1.

💾 [Código versão 12](https://gist.github.com/parodrigues-ipynb/321e96d45b61859578bc1fb003bc0cd2)

🎥 Não houve necessidade de vídeo nessa versão

<details>
  <summary>📝 Comentários sobre o código versão 10 [clique para expandir]</summary>

  W.I.P.

</details>


[^1]: O [datasheet da Espressif](https://www.espressif.com/sites/default/files/documentation/esp32_datasheet_en.pdf) apresenta diferentes consumos para situações de transmissão ou recepção de Wi-Fi/Bluetooth, light-sleep, deep-sleep... Esses valores podem ser consultados nas tabelas *Table 4-2. Power Consumption by Power Modes* na **página 30** e *Table 5-4. Current Consumption Depending on RF Modes* na **página 53**. Em função dos diversos possíveis valores de corrente para cada modo de funcionamento, adotou-se o pior caso (maior consumo de ~250mA com transmissão Wi-Fi 802.11b ativa).

[^2]: O [datasheet consultado](https://www.handsontec.com/dataspecs/module/ESP32-CAM.pdf) apresenta valores em torno de 200mA para câmera ligada/flash desligado e 300mA para câmera ligada/flash ligado. Os valores podem aumentar em caso de streaming por Wi-Fi. Adotou-se o valor médio.

[^3]: [O valor de corrente de 200mA por cada motor é para situações sem carga](https://www.usinainfo.com.br/motor-dc/motor-dc-3-6v-200rpm-com-caixa-de-reducao-e-eixo-duplo-481--3161.html), nas quais os motores estão girando sem resistências mecânicas. Se houver atrito, inclinação, a própria massa do robô..., o valor de corrente pode subir consideravelmente, chegando a valores de até 1,5A por motor. Como não pode-se encontrar um datasheet para o motor específico utilizado, confiou-se nos valores apresentados pelo vendedor.
