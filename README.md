

  <p align="center">
<img src="https://i.imgur.com/RtfMYOS.png" />
</p>

<h1>MOON, HARDWARE WALLET DE BITCOIN DIY (BETA)</h1>

Criar sua própria hardwallet é um process divertido e repleto de aprendizado. Como o criador original deste projeto, <a href="https://github.com/arcbtc" target="_blank">Ben Arc</a>, bem colocou: "Construir sua hardwallet é como construir um sabre de luz, só é realmente necessário se você quer ser um Jedi".

E construir uma hardware wallet ficou mais fácil com a ajuda da <a href="https://github.com/micro-bitcoin/uBitcoin" target="_blank">uBitcoin</a> uma biblioteca Arduino criada por Stepan Snigirev - criador da <a href="https://www.youtube.com/playlist?list=PLgcVYwONyxmhvPW88vQ21XjpQ6ZmyXNI3" target="_blank">Specter DIY e Specter Desktop</a>.

Construir hardware wallets não é apenas um processo liberador, também é uma ótima desculpa para entender como funcionam as chaves, seeds e assinatura de transações Bitcoin.

## Tutorial
Original em inglês da Bowser Wallet: https://www.youtube.com/watch?v=DG1zrlAVdys
Em breve tutorial em Português. Sendo gravado neste instante! :)

## COMANDOS SD

Comandos para inserir em um arquivo de texto moon.txt na pasta raiz do cartão SD:

1. Limpar o dispositivo e configurar uma nova carteira:<br/>
```HARD RESET```

Restaurar de uma seed de backup:<br/>
```RESTORE husband behind shallow promote....```
    
Assinar uma transação Electrum/Specter Desktop:<br/>
```SIGN 45505446ff00020000000001016cb....```

## Instalando o Arduino
Instale o Arduino IDE
https://www.arduino.cc/en/Guide/HomePage

Instale as placas ESP32 no Arduino
https://github.com/espressif/arduino-esp32/blob/master/docs/arduino-ide/boards_manager.md

## Bibliotecas utilizadas
- <a href="https://github.com/micro-bitcoin/uBitcoin" target="_blank">uBitcoin</a> (Baixe a biblioteca do github e "Add Zip Library" no Library Manager do Arduino) 
- <a href="https://github.com/m5stack/M5Stack" target="_blank">M5Stack</a> (Instale direto da "Library Manager" dentro do Arduino buscando por M5Stack)
- [lvgl](https://lvgl.io/) (Instale direto na "Library Manager" do Arduino, busque por "lvgl", e instale apenas o "lv_arduino" - não o lvgl!)
## Materiais
- M5Stack (a versão grey - cinza - é melhor)
- Cartão SD (idealmente de baixa capacidade, até 16GB funciona bem - pode ser que maiores também funcionem, você pode testar) 


