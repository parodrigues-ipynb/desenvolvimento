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

---

### Relação de componentes utilizados

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

E uma infinidade de terminais, parafusos, porcas, brocas, fixadores, cabos, espaçadores... utilizados para montar o robô em uma estrutura de MDF.

---

### Memorial de cálculo de dimensionamento
O grupo pretende alcançar os seguintes objetivos para o robô B1-M1:
1. mover-se seguindo uma rotina pré-determinada em um ambiente residencial plano e permitir controle remoto;
2. registrar valores obtidos pelo sensoriamento ultrassônico e visual (fotografias) e permitir o stream (vídeo) durante o acesso remoto;
3. comunicar-se com o Gemini através da API fornecida pelo Google a fim de obter instruções para movimento autônomo.

Para alcançar os objetivos acima listados foi determinada a necessidade dos componentes listados na seção [Relação de componentes utilizados](#relacao-de-componentes-utilizados).

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

![18650](https://i.imgur.com/KVCxV1z.jpeg)

As baterias de lítio 18650 têm gravado nos seus invólucros a capacidade de carga elétrica de **3800mAh**. Porém, [é interessante notar que o vendedor fez testes e alegou a capacidade de apenas 1500mAh](https://www.usinainfo.com.br/baterias/bateria-18650-litio-recarregavel-37v-3800mah-flat-top-8760.html). Portanto, para fins de cálculo neste trabalho, adotar-se-á o valor de **1500mAh**.

Fazendo um cálculo simples de autonomia,

$Autonomia = \frac{Capacidade \ de \ carga \ elétrica}{Consumo \ de \ corrente \ elétrica} = \frac{1500mAh}{1000mA} ≈ 1,5h$

Logo, o grupo espera que o B1-M1 tenha uma autonomia de aproximadamente **1 hora e 30 minutos** funcionando com as premissas de consumo feitas na tabela **Consumo de corrente**.

#### Seção dos cabos utilizados

Como cabos de bitola 1mm² suportam correntes contínuas de até 10A, adotou-se o seu uso nas conexões do pack de baterias 18650 com a BMS e da BMS com os reguladores de tensão.

Nas demais conexões utilizou-se cabos de 0,75mm², que suportam correntes contínuas de até 8A.

---

### Esquemático

Uma imagem do esquemático pode ser vista [aqui](https://i.imgur.com/tPJJAKS.png)

Algumas notas sobre decisões feitas são colocadas a seguir.

#### Capacitores de desacoplamento de 100nF nos terminais dos motores A e B

![Motores escovados](https://i.imgur.com/TV1qZob.jpeg)

Motores produzem ruído.

Nos motores DC utilizados neste projeto, uma das fontes de ruído possíveis é devido à comutação entre as escovas de carbono e o anel coletor laminado (o comutador) do induzido.

[GIF mostrando os arcos voltaicos](https://i.imgur.com/fCO2iG0.gif)

Quando as escovas e as lâminas do anel coletor comutam ocorrem arcos voltaicos (*comutar = ligar ou desligar, interromper e religar uma ligação elétrica*). Esses arcos ocorrem pois uma vez energizadas as bobinas do enrolamento do induzido se comportam como indutores.

A equação da tensão para indutores é $v = L \frac{di}{dt}$. Ou seja, a tensão é proporcional à taxa de variação da corrente. Quando a comutação ocorre, a taxa de variação da corrente é abrupta e intensa (indo de 100% para 0% em um intervalo de tempo muito pequeno). Essa grande taxa de variação provoca um pico de tensão nas bobinas e, por consequência, os arcos voltaicos entre as escovas e as lâminas do anel coletor. Os picos de tensão no funcionamento de um motor DC podem ser vistos na imagem abaixo.

![Ruído](https://i.imgur.com/wnImMP7.jpeg)

Esse ruído pode afetar o funcionamento de outras partes do circuito.

---

### Desenvolvimento do código

Tanto os alunos Anderson quanto Pedro nunca fizeram antes um projeto de robótica.

Para fins didáticos e de criação de um memorial de aprendizado, o grupo decidiu documentar o progresso do desenvolvimento do código utilizado no B1-M1.

A documentação é apresentada abaixo em ordem cronológica. Cada inserção conta com notas pessoais de aprendizado do grupo.

---

#### 13/10/2025

💾 [Código versão 1](https://gist.github.com/parodrigues-ipynb/be9dc512e9a064356e3e1a73c458425b)

🎥 [Vídeo B1-M1 rodando com a versão 1](https://imgur.com/a/WtTMg6K)

**Comentários sobre o código**

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

$$
Duty \ cycle = \frac{t_{ON}}{T} × 100 \\%
$$

Por exemplo, se o período $T$ fosse 100ms, um *duty cycle* de 25% teria uma largura de pulso $t_{ON}$ de 25ms.

![Sinal PWM](https://i.imgur.com/OkiNbwV.jpeg)

A imagem acima mostra diferentes sinais de tensão PWM. As linhas verticais laranjas são as marcações de tempo. Portanto, todos os sinais compartilham o mesmo período $T$.

Na imagem os sinais de tensão PWM têm *duty cycles* distintos: 0%, 25%, 50%, 75% e 100%.

É uma prática comum utilizar variáveis numéricas para representar o *duty cycle* em código. Por exemplo, seria teoricamente possível criar uma variável `int pwmA = 0` para representar um *duty cycle* de 0%. Caso fosse desejável alterar o duty cycle para 1%, poderia-se simplesmente alterar o valor da variável para `pwma = 1`, ou 2% → `pwma = 2`, e assim por diante.

O tipo de variável `int` é usado para armazenar números inteiros (-2, -1, 0, 1, 2, 3...). Na ESP32, o `int` ocupa **4 bytes** (32 bits) - o que faz sentido, já que o microcontrolador é baseado em arquitetura 32 bits. Os valores possíveis para variáveis do tipo `int` vão de -2,147,483,648 até 2,147,483,647. É possível utlizar `unsigned int` para trabalhar-se com o intervalo de 0 até 4,294,967,295 (aproximadamente 4 bilhões).

Portanto, no caso da linha 10, poderíamos teoricamente utilizar a variável `unsigned int pwmA` para mapear o *duty cycle*. Se desejássemos utilizar todo o potencial de armazenamento do tipo `unsigned int`, como queremos mapear valores de 0% até 100% num intervalo de 0 até 4,294,967,295, faríamos $\frac{100 - 0}{4,294,967,295 - 0} ≈ 0,00000002328$.

Assim, teríamos a seguinte resolução:
* `pwmA = 0             // → 0%`
* `pwmA = 1             // → ≈ 0,00000002328%`
* `pwmA = 2             // → ≈ 0,00000004657%`
* ...
* `pwmA = 4294967294 // → ≈ 99,9999999767%`
* `pwmA = 4294967295 // → 100%`

Agora imaginemos programadores tendo de cotidianamente utilizar essa resolução em seus códigos. Seria um pesadelo ter de lembrar o valor 4294967295, e muito difícil lembrar os valores que mapeam para aproximadamente 25%, 50%, 75%...
  
Portanto, no caso de sinais PWM, é comum utilizar-se tipos de variáveis de apenas **1 byte** (8 bits), que na base binária ($2^n$) correspondem a 256 valores possíveis ($2^8 = 256$). Como $\frac{100-0}{255-0} ≈ 0,39$, teríamos a seguinte resolução:
* `pwmA = 0             // → 0%`
* `pwmA = 1             // → ≈ 0,39%`
* `pwmA = 2             // → ≈ 0,78%`
* ...
* `pwmA = 254 // → ≈ 99,61%`
* `pwmA = 255 // → 100%`

Fica evidente que 1 byte já traz uma resolução adequada para se programar e ainda possibilita inferir algumas porcentagens intuitivamente: como 100% → 255, então 50% deve ser algo em torno de 127, 25% deve ser algo em torno de 64... e assim por diante.

`uint8_t` significa *unsigned integer of length 8 bits*, ou *número inteiro sem sinal de comprimento de 8 bits*. É muito comum encontrar softwares e hardwares que utilizam sinais PWM mapeados por variáveis de 8 bits. Entretanto, é sempre bom ficar atento às convenções adotadas em cada projeto pois pode haver casos em que uma maior resolução é necessária a fim de alcançar maior precisão.

 


[^1]: O [datasheet da Espressif](https://www.espressif.com/sites/default/files/documentation/esp32_datasheet_en.pdf) apresenta diferentes consumos para situações de transmissão ou recepção de Wi-Fi/Bluetooth, light-sleep, deep-sleep... Esses valores podem ser consultados nas tabelas *Table 4-2. Power Consumption by Power Modes* na **página 30** e *Table 5-4. Current Consumption Depending on RF Modes* na **página 53**. Em função dos diversos possíveis valores de corrente para cada modo de funcionamento, adotou-se o pior caso (maior consumo de ~250mA com transmissão Wi-Fi 802.11b ativa).

[^2]: O [datasheet consultado](https://www.handsontec.com/dataspecs/module/ESP32-CAM.pdf) apresenta valores em torno de 200mA para câmera ligada/flash desligado e 300mA para câmera ligada/flash ligado. Os valores podem aumentar em caso de streaming por Wi-Fi. Adotou-se o valor médio.

[^3]: [O valor de corrente de 200mA por cada motor é para situações sem carga](https://www.usinainfo.com.br/motor-dc/motor-dc-3-6v-200rpm-com-caixa-de-reducao-e-eixo-duplo-481--3161.html), nas quais os motores estão girando sem resistências mecânicas. Se houver atrito, inclinação, a própria massa do robô..., o valor de corrente pode subir consideravelmente, chegando a valores de até 1,5A por motor. Como não pode-se encontrar um datasheet para o motor específico utilizado, confiou-se nos valores apresentados pelo vendedor.
