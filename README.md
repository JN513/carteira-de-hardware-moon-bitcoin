<p align="center">
<img src="https://i.imgur.com/sJRPQB7.png" />
</p>

<h1>MOON, HARDWARE WALLET DE BITCOIN DIY (BETA)</h1>

Criar sua própria hardwallet é um processo divertido e repleto de aprendizado. Como o criador original do projeto <a href="https://github.com/arcbtc/bowser-bitcoin-hardware-wallet" target="_blank">Bowser Bitcoin Wallet</a>, Ben Arc, bem colocou: "Construir sua hardwallet é como construir um sabre de luz, só é realmente necessário se você quer ser um Jedi".

E construir uma hardware wallet ficou mais fácil com a ajuda da <a href="https://github.com/micro-bitcoin/uBitcoin" target="_blank">uBitcoin</a> uma biblioteca Arduino criada por Stepan Snigirev - criador da <a href="https://www.youtube.com/playlist?list=PLgcVYwONyxmhvPW88vQ21XjpQ6ZmyXNI3" target="_blank">Specter DIY e Specter Desktop</a>.

Construir hardware wallets não é apenas um processo liberador, também é uma ótima desculpa para entender como funcionam as chaves, seeds e assinatura de transações Bitcoin.


## Tutorial
Original em inglês da Bowser Wallet: https://www.youtube.com/watch?v=DG1zrlAVdys

Tutorial em Português:  https://www.youtube.com/watch?v=5dQ8nCrkdpw


## COMANDOS SD

Comandos para inserir em um arquivo de texto moon.txt na pasta raiz do cartão SD:

1. Limpar o dispositivo e configurar uma nova carteira:<br/>
```HARD RESET```
<br>Depois do processo, lembre-se de apagar o arquivo moon.txt do microSD antes de reiniciar com ele inserido.

2. Restaurar de uma seed de backup:<br/>
```RESTORE husband behind shallow promote....```
    
3. Assinar uma transação Electrum/Specter Desktop:<br/>
```SIGN 45505446ff00020000000001016cb....```


## Hardware necessário (Lista de compras)
- M5Stack (ESP32 GREY Development Kit with 9-Axis Sensor)
- Cartão microSD (idealmente de baixa capacidade, até 16GB funciona bem com certeza)


## Instalando o Arduino
Instale o Arduino IDE
https://www.arduino.cc/en/Guide/HomePage

Instale as placas ESP32 no Arduino
https://github.com/espressif/arduino-esp32/blob/master/docs/arduino-ide/boards_manager.md

## Bibliotecas utilizadas
- <a href="https://github.com/micro-bitcoin/uBitcoin" target="_blank">uBitcoin</a> (Baixe a biblioteca do github e "Add Zip Library" no Library Manager do Arduino) 
- <a href="https://github.com/m5stack/M5Stack" target="_blank">M5Stack</a> (Instale direto da "Library Manager" dentro do Arduino buscando por M5Stack)
- [lvgl](https://lvgl.io/) (Instale direto na "Library Manager" do Arduino, busque por "lvgl", e instale apenas o "lv_arduino" - não o lvgl!) 


## Projeto original
Visite o projeto original <a href="https://github.com/arcbtc/bowser-bitcoin-hardware-wallet" target="_blank">Bowser Bitcoin Wallet</a> se preferir a versão em inglês ou para verificar se está mais atualizada que esta versão traduzida e levemente adaptada.

## Botões do M5Stack
<p align="left"><img src="https://i.imgur.com/DqPu6Xl.png"></p>
