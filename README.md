# Disruptive-Architectures-IOT-IOB-Generative-IA

# DeuRuim

## Entregas

Temos o código fonte **codigo.c++**, temos também o **diagrama.json** que é a estrutura do ESP32 em formato JSON e também **modelo.png** que é uma imagem do sistema IOT

## Integrantes

- Vicenzo Massao - 554833
- Luiz Heimberg - 556864
- Erick Alves - 556862

## Vídeos:

**Pitch** : https://youtu.be/55PfbdSWxNo?si=QYtacM-vdKux6S3t
**Protótipo Funcional** : https://youtu.be/7EgNjwZWAzQ

## Descrição do Projeto

#### DeuRuim tem como objetivo ajudar pessoas a se ajudarem. A nossa solução propõe um espaço interativo onde usuários podem reportar desastres e condições climáticas de um jeito divertido e engajante.

## Intruções

### ESP32 + DHT22 + ThingSpeak

Sistema IoT com ESP32 que coleta temperatura, umidade e índice de calor usando um sensor DHT22, e envia os dados para o ThingSpeak. O sensor pode ser ativado ou desativado por um botão, com LEDs indicando o status do sistema.

### Componentes

- ESP32
- Sensor DHT22
- Botão (GPIO 18)
- LEDs:

  - Verde (Sensor ON - GPIO 25)
  - Vermelho (Sensor OFF - GPIO 26)

  - Azul (Enviando dados - GPIO 27)

###  Como usar

1. Instalação
Arduino IDE com suporte ao ESP32

Instale as bibliotecas:

   - DHT sensor library (Adafruit)

   - ThingSpeak

2. Configuração

Defina sua rede Wi-Fi:

```
const char* ssid = "SEU_WIFI";
const char* pass = "SENHA";
```

Configure o canal no ThingSpeak:

```
unsigned long myChannelNumber = XXXXXXX;
const char* myWriteAPIKey = "SUA_API_KEY";
```

3. Upload
Conecte o ESP32 e envie o código.

### Funcionamento

Pressione o botão para ativar/desativar o sensor.

**Quando ativo:**

Coleta temperatura, umidade e índice de calor.

Envia os dados a cada 20 segundos para o ThingSpeak.

LED amarela acende durante envio.

**Quando inativo:**

Dados não são coletados.

ThingSpeak recebe sensor desligado.

### ThingSpeak - Campos utilizados
Campo	Dados
1	Temperatura (°C)
2	Umidade (%)
3	Status do sensor
4	Índice de calor

### Monitoramento
Visualize os dados no painel do ThingSpeak.

Consulte o monitor serial para depuração.