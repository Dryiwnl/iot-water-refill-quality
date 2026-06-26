# Tutorial de Instalação

Este tutorial explica como configurar o ambiente de desenvolvimento, fazer o upload do código para o ESP32 e configurar o dashboard no Adafruit IO.

## Pré-requisitos

- Computador com Windows, macOS ou Linux
- Acesso à internet
- Cabo USB para conectar o ESP32

## Passo 1: Instalar o VS Code e o PlatformIO

1. Baixe e instale o [Visual Studio Code](https://code.visualstudio.com/).
2. Abra o VS Code e clique no ícone de Extensions (quadradinho no menu lateral esquerdo).
3. Procure por "PlatformIO" na barra de pesquisa e clique em Install na extensão "PlatformIO IDE".
4. Aguarde a instalação e clique em "Reload" quando concluído.

## Passo 2: Clonar o projeto

1. Abra um terminal (no VS Code, use o menu Terminal → New Terminal).
2. Navegue até a pasta onde deseja salvar o projeto.
3. Clone o repositório com o comando:
   ```
   git clone https://github.com/Dryiwnl/iot-water-refill-quality.git
   ```
4. Entre na pasta do projeto:
   ```
   cd iot-water-refill-quality
   ```

## Passo 3: Configurar as credenciais

1. Na pasta `src/`, crie um arquivo chamado `secrets.h`.
2. Abra o `secrets.h` e cole o seguinte conteúdo:
   ```cpp
   #ifndef SECRETS_H
   #define SECRETS_H
   
   #define IO_USERNAME "seu_usuario"
   #define IO_KEY "sua_chave"
   
   #define WIFI_SSID "sua_rede_wifi"
   #define WIFI_PASS "sua_senha_wifi"
   
   #endif
   ```
3. Substitua `seu_usuario` e `sua_chave` pelas suas credenciais do Adafruit IO, e `sua_rede_wifi` e `sua_senha_wifi` pelos dados da sua rede Wi-Fi.

## Passo 4: Compilar e fazer upload

1. Conecte o ESP32 ao computador com o cabo USB.
2. No VS Code, clique no ícone do PlatformIO na barra lateral.
3. Em "PROJECT TASKS", expanda a seta ao lado de "esp32doit-devkit-v1".
4. Clique em "Build" para compilar o código. Aguarde o processo ser concluído.
5. Clique em "Upload" para enviar o código para o ESP32. 
6. Se for pedido para selecionar a porta serial, escolha a porta onde o ESP32 está conectado.

## Passo 5: Configurar o Adafruit IO

1. Acesse [io.adafruit.com](https://io.adafruit.com/) e faça login (ou crie uma conta se não tiver).
2. Clique em "Feeds" e crie os seguintes feeds: `nivel`, `ph`, `turbidez`.
3. Clique em "Dashboards" e crie um novo dashboard chamado "Bebedouro IoT".
4. Adicione blocos para cada feed, ajustando os limites e cores como desejar.

## Passo 6: Monitorar os dados

1. No VS Code, clique no ícone do PlatformIO na barra lateral.
2. Em "PROJECT TASKS", expanda a seta ao lado de "esp32doit-devkit-v1".
3. Clique em "Monitor" para abrir o monitor serial.
4. Verifique se os dados estão sendo enviados corretamente.
5. Acesse o dashboard no Adafruit IO e acompanhe as leituras em tempo real.

Pronto! Agora você tem o projeto Bebedouro IoT rodando e enviando dados para a nuvem. Caso tenha alguma dúvida ou problema durante o processo, confira a documentação completa na pasta `docs/` ou abra uma issue no repositório.
