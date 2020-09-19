#include <M5Stack.h> 
#include <EEPROM.h>
#include <Electrum.h>

#include "gameimg.c"
#include "walletimg.c"
#include "decoy.h"
#include "Bitcoin.h"
#include "Hash.h"
#include "SPIFFS.h"
#include "PSBT.h"

bool buttona = false;
bool buttonb = false;
bool buttonc = false;
bool confirm = false;
bool loopmenu = true;

unsigned long timy;
String passkey;
String morseletter;
String passhide;
String seedgeneratestr;
String savedseed;
String seedgeneratesarr[24];
String sdcommand;
String hashed;
String savedpinhash;
String privatekey;
String pubkey;

char ref[2][36][7]={
{"10","0111","0101","011","1","1101","001","1111","11","1000","010","1011","00","01","000","1001", "0010","101","111","0","110","1110","100","0110","0100","0011","10000","11000","11100","11110","11111","01111","00111","00011","00001","00000"},
{"A", "B",   "C",   "D",  "E","F",   "G",  "H",   "I", "J",   "K",  "L",   "M",  "N","O",  "P",    "Q",   "R",  "S",  "T","U",  "V",   "W",  "X",   "Y",   "Z",   "1",    "2",    "3",    "4",    "5",    "6",    "7",    "8",    "9",    "0"}
};

//========================================================================
void setup(void) {
  M5.begin();                   
  M5.Lcd.setBrightness(100);    
  M5.Lcd.fillScreen(BLACK);    
  decoysetup();
  M5.Lcd.setBrightness(100);
  if(!SPIFFS.begin(true)){
    return;
  }
  //Checks if the user has an account or is forcing a reset
  File otherfile = SPIFFS.open("/key.txt");
  savedseed = otherfile.readStringUntil('\n');
  otherfile.close();
  sdchecker();

  if(sdcommand == "HARD RESET"){

    seedmaker();  
    pinmaker();
  }
  else if(sdcommand.substring(0,7) == "RESTORE"){
    restorefromseed(sdcommand.substring(8,sdcommand.length()));
    enterpin(true);
  }
  else{
    enterpin(false);
  }
  M5.Lcd.drawBitmap(0, 0, 320, 240, (uint8_t *)WalletImg_map);
  delay(3000);
}

//========================================================================
void loop() {
  int menuitem = 1;
  loopmenu = true;
  //Run menu loop
  while(loopmenu == true){
   M5.Lcd.fillScreen(BLACK);
   M5.Lcd.setCursor(38, 30);
   M5.Lcd.setTextSize(3);
   M5.Lcd.setTextColor(GREEN);
   M5.Lcd.println("MOON WALLET");
   M5.Lcd.println("");
   M5.Lcd.setTextSize(2);
    if (menuitem == 1){
      M5.Lcd.setTextColor(BLUE);
      M5.Lcd.println("Exibir endereco");
      M5.Lcd.setTextColor(GREEN);
      M5.Lcd.println("Assinar transacao");
      M5.Lcd.println("Exportar ZPUB");
      M5.Lcd.println("Exibir seed");
      M5.Lcd.println("Limpar dispositivo");
      M5.Lcd.println("Restaurar de seed");
    }
    else if (menuitem == 2){
      M5.Lcd.println("Exibir endereco");
      M5.Lcd.setTextColor(BLUE);
      M5.Lcd.println("Assinar transacao");
      M5.Lcd.setTextColor(GREEN);
      M5.Lcd.println("Exportar ZPUB");
      M5.Lcd.println("Exibir seed");
      M5.Lcd.println("Limpar dispositivo");
      M5.Lcd.println("Restaurar de seed");
    }
    else if (menuitem == 3){
      M5.Lcd.println("Exibir endereco");
      M5.Lcd.println("Assinar transacao");
      M5.Lcd.setTextColor(BLUE);
      M5.Lcd.println("Exportar ZPUB");
      M5.Lcd.setTextColor(GREEN);
      M5.Lcd.println("Exibir seed");
      M5.Lcd.println("Limpar dispositivo");
      M5.Lcd.println("Restaurar de seed");
    }
    else if (menuitem == 4) {
      M5.Lcd.println("Exibir endereco");
      M5.Lcd.println("Assinar transacao");
      M5.Lcd.println("Exportar ZPUB");
      M5.Lcd.setTextColor(BLUE);
      M5.Lcd.println("Exibir seed");
      M5.Lcd.setTextColor(GREEN);
      M5.Lcd.println("Limpar dispositivo");
      M5.Lcd.println("Restaurar de seed");
    }
    else if (menuitem == 5) {
      M5.Lcd.println("Exibir endereco");
      M5.Lcd.println("Assinar transacao");
      M5.Lcd.println("Exportar ZPUB");
      M5.Lcd.println("Exibir seed");
      M5.Lcd.setTextColor(BLUE);
      M5.Lcd.println("Limpar dispositivo");
      M5.Lcd.setTextColor(GREEN);
      M5.Lcd.println("Restaurar de seed");
    }
    else if (menuitem == 6) {
      M5.Lcd.println("Exibir endereco");
      M5.Lcd.println("Assinar transacao");
      M5.Lcd.println("Exportar ZPUB");
      M5.Lcd.println("Exibir seed");
      M5.Lcd.println("Limpar dispositivo");
      M5.Lcd.setTextColor(BLUE);
      M5.Lcd.println("Restaurar de seed");
      M5.Lcd.setTextColor(GREEN);
    }
    while (buttona == false){
       if (M5.BtnA.wasReleased()){
         menuitem--;
         buttona = true;
       }
       else if (M5.BtnB.wasReleased()){
         menuitem++;
         buttona = true;
       }else if (M5.BtnC.wasReleased()){
         loopmenu = false;
         buttona = true;
       }
        M5.update(); 
    }
    buttona = false;
       
     if(menuitem < 1){
      menuitem=6;
     }
     else if(menuitem > 6){
      menuitem=1;
     }
  }
  
  //Exibir endereco: Menu item 1 selected
  if(menuitem == 1){ 
    HDPublicKey hd(pubkey);
    
    File otherfile = SPIFFS.open("/num.txt");
    String pubnumm = otherfile.readStringUntil('\n');
    otherfile.close();
    int pubnum = pubnumm.toInt() + 1;
    File file = SPIFFS.open("/num.txt", FILE_WRITE);
    file.print(pubnum);
    file.close();
    
    String path = String("m/0/")+pubnum;
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setCursor(0, 20);
    M5.Lcd.setTextSize(3);
    M5.Lcd.setTextColor(GREEN);
    M5.Lcd.println(" ENDERECO");
    String freshpub = hd.derive(path).address();
    M5.Lcd.qrcode(freshpub, 5, 46, 160);
    M5.Lcd.setTextSize(2);
    int i = 0;
    while (i < freshpub.length() + 1){
      M5.Lcd.println("              " + freshpub.substring(i, i + 12));
      i = i + 12;
    }
    M5.Lcd.setCursor(0, 220);
    M5.Lcd.println(" C para voltar ao menu");

    
    while (buttonc == false){
      if (M5.BtnC.wasReleased()){buttonc = true;}
       M5.update(); 
      }
     buttonc = false;  
  }
  
  //Assinar transacao: Menu item 2 selected
  else if(menuitem == 2){
    sdchecker();
    if (sdcommand.substring(0, 4) == "SIGN"){
        String eltx = sdcommand.substring(5, sdcommand.length() + 1);
  
        ElectrumTx tx;
        
        M5.Lcd.fillScreen(BLACK);
        M5.Lcd.setCursor(0, 20);
        M5.Lcd.setTextSize(3);
        M5.Lcd.setTextColor(GREEN);
        M5.Lcd.println("");
        M5.Lcd.setCursor(0, 90);
        M5.Lcd.println("  Oh, yeah!");
        M5.Lcd.println("");
        M5.Lcd.println("  Transacao");
        M5.Lcd.println("  no SD");
      
        delay(3000);
        
        M5.Lcd.fillScreen(BLACK);
        M5.Lcd.setCursor(0, 20);
        M5.Lcd.setTextSize(2);
  
        int len_parsed = tx.parse(eltx);
        if(len_parsed == 0){
          M5.Lcd.println("Erro ao parse tx");
          return;
        }
        for(int i=0; i<tx.tx.outputsNumber; i++){
          M5.Lcd.print(tx.tx.txOuts[i].address());
          M5.Lcd.print("\n-> ");
          // Serial can't print uint64_t, so convert to int
          M5.Lcd.print(int(tx.tx.txOuts[i].amount));
          M5.Lcd.println(" sat\n");
        }
        M5.Lcd.print("Taxa: ");
        M5.Lcd.print(int(tx.fee()));
        M5.Lcd.println(" sat");

       M5.Lcd.setCursor(0, 220);
       M5.Lcd.println("A assinar, C cancelar");
       while (buttona == false && buttonc == false){
        if (M5.BtnA.wasReleased()){buttona = true;}
        if (M5.BtnC.wasReleased()){buttonc = true;}
        M5.update(); 
       }
       if(buttonc == true){
        buttonc = false;
        return;
       }
       buttona = false;

        HDPrivateKey hd(savedseed, passkey);
        HDPrivateKey account = hd.derive("m/84'/0'/0'/");
        Serial.println(account);
        
        tx.sign(account); 
        M5.Lcd.fillScreen(BLACK);
        M5.Lcd.setCursor(0, 20);
        M5.Lcd.setTextSize(2);
        
        String signedtx = tx;
        Serial.print(signedtx);
        int str_len = signedtx.length() + 1; 
        char char_array[str_len];
        signedtx.toCharArray(char_array, str_len);
        writeFile(SD, "/assinada.txt", char_array);
    
        M5.Lcd.fillScreen(BLACK);
        M5.Lcd.setCursor(0, 100);
        M5.Lcd.setTextSize(2);
        M5.Lcd.println("  All right! Salva no SD");
        M5.Lcd.println("");
        M5.Lcd.setTextSize(2);
        M5.Lcd.setCursor(0, 220);
        M5.Lcd.println("   Pressione C para menu");
        while (buttonc == false){
        if (M5.BtnC.wasReleased()){buttonc = true;}
         M5.update(); 
         }
        buttonc = false;  
        sdcommand = "";
        }
        
        else{
        M5.Lcd.fillScreen(BLACK);
        M5.Lcd.setCursor(0, 100);
        M5.Lcd.setTextSize(2);
        M5.Lcd.setTextColor(RED);
        M5.Lcd.println("   Nao encontrada no SD");
        M5.Lcd.setTextColor(GREEN);
        M5.Lcd.setTextSize(2);
        M5.Lcd.setCursor(0, 220);
        M5.Lcd.println("   Pressione C para menu");
        while (buttonc == false){
        if (M5.BtnC.wasReleased()){buttonc = true;}
         M5.update(); 
         }
        buttonc = false;   
     }
  }

  //Exportar ZPUB: Menu item 3 selected
  else if (menuitem == 3){
        int str_len = pubkey.length() + 1; 
        char char_array[str_len];
        pubkey.toCharArray(char_array, str_len);
        writeFile(SD, "/zpub.txt", char_array);
    
        M5.Lcd.fillScreen(BLACK);
        M5.Lcd.setCursor(0, 20);
        M5.Lcd.setTextSize(3);
        M5.Lcd.println("  EXPORTAR ZPUB");
        M5.Lcd.qrcode(pubkey, 5, 46, 160);
        M5.Lcd.setTextSize(2);
        int i = 0;
        while (i < pubkey.length() + 1){
          M5.Lcd.println("              " + pubkey.substring(i, i + 12));

          i = i + 12;
        }   
        M5.Lcd.setTextSize(2);
        M5.Lcd.setCursor(0, 220);
        M5.Lcd.println(" Salva no SD, C para menu");
        while (buttonc == false){
        if (M5.BtnC.wasReleased()){buttonc = true;}
         M5.update(); 
         }
        buttonc = false;  
        sdcommand = "";
  }
  
  //SHOW SEED: Menu item 4 selected
  else if(menuitem == 4){
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setCursor(0, 20);
    M5.Lcd.setTextSize(3);
    M5.Lcd.setTextColor(GREEN);
    M5.Lcd.println("   EXIBIR SEED");
    M5.Lcd.println("");
    M5.Lcd.setTextColor(BLUE);
    M5.Lcd.setTextSize(2);
    M5.Lcd.println(savedseed);
    M5.Lcd.setTextColor(GREEN);
    M5.Lcd.setTextSize(2);
    M5.Lcd.setCursor(0, 220);
    M5.Lcd.println("   Pressione C para menu");
    while (buttonc == false){
      if (M5.BtnC.wasReleased()){buttonc = true;}
       M5.update(); 
    }
    buttonc = false;  
  }
  
  //WIPE DEVICE: Menu item 5 selected
  else if(menuitem == 5){
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setCursor(0, 20);
    M5.Lcd.setTextSize(3);
    M5.Lcd.setTextColor(GREEN);
    M5.Lcd.println(" LIMPAR SEED");
    M5.Lcd.setCursor(0, 90);
    M5.Lcd.setTextColor(RED);
    M5.Lcd.setTextSize(2);
    M5.Lcd.println(" Seed sera excluida,");
    M5.Lcd.println(" tem certeza?");
    M5.Lcd.setTextSize(2);
    M5.Lcd.setCursor(0, 220);
    M5.Lcd.println(" A continuar, C cancelar");

    while (buttona == false && buttonc == false){
      if (M5.BtnA.wasReleased()){buttona = true;}
      if (M5.BtnC.wasReleased()){buttonc = true;}
      M5.update(); 
    }
     if (buttona == true){
        seedmaker();  
        pinmaker();
     }
     
     buttona = false;
     buttonc = false;
  }
  
    //RESTOR FROM SEED: Menu item 4 selected
   
  else if(menuitem == 6){
    if(sdcommand.substring(0,7) == "RESTORE"){
    // sdchecker();
     restorefromseed(sdcommand.substring(8,sdcommand.length()));
    }
    else{
     M5.Lcd.fillScreen(BLACK);
     M5.Lcd.setTextSize(2);
     M5.Lcd.setCursor(0, 90);
     M5.Lcd.setTextColor(RED);
     M5.Lcd.println("    'RESTORE *seed*'");
     M5.Lcd.println("   nao encontrada no SD");
     M5.Lcd.setCursor(0, 220);
     M5.Lcd.setTextColor(GREEN);
     M5.Lcd.println("   Pressione C para menu");
     while (buttonc == false){
      if (M5.BtnC.wasReleased()){buttonc = true;}
       M5.update(); 
     }
     buttonc = false;  
     } 
    }  
}

//========================================================================
void seedchecker(){
  File otherfile = SPIFFS.open("/key.txt");
  savedseed = otherfile.readStringUntil('\n');
  otherfile.close();
  int seedcount = 0;
  
  for (int x = 0; x < 24; x++){
    for (int z = 0; z < 2048; z++){
      if (getValue(savedseed,' ',x) == seedwords[z]){
        seedcount = seedcount + 1;
      }
    } 
  }
  
  if(int(seedcount) != 24){
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setCursor(0, 90);
    M5.Lcd.setTextColor(RED);
    M5.Lcd.setTextSize(2);
    M5.Lcd.println("   Erro: reinicie M5Stack");
    M5.Lcd.println("   ou restaure da seed");
    M5.Lcd.println("   (Veja documentacao)");
    delay(99999999999999999999999);
  }
  else{
    return;
  }
}

//========================================================================
void seedmaker(){
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0, 100);
  M5.Lcd.setTextColor(GREEN);
  M5.Lcd.setTextSize(2);
  M5.Lcd.println("   Escreva as palavras");
  M5.Lcd.println("   em um lugar seguro!");
  delay(6000);
  buttona = false;
  
  for (int z = 0; z < 24; z++){
    seedgeneratestr += seedwords[random(0,2047)] + " ";

  }
  
  for (int z = 0; z < 24; z++){
      M5.Lcd.fillScreen(BLACK);
      M5.Lcd.setCursor(0, 70);
      M5.Lcd.setTextSize(2);
      M5.Lcd.println("   Palavra " + String(z+1));
      M5.Lcd.println("");
      M5.Lcd.setTextSize(5);
      M5.Lcd.setTextColor(BLUE);
      M5.Lcd.println("  " + getValue(seedgeneratestr,' ',z));
      M5.Lcd.setTextSize(2);
      M5.Lcd.println("");
      M5.Lcd.setTextColor(GREEN);
      M5.Lcd.println("   Pressione A para seguir");
      
     while (buttona == false){
        if (M5.BtnA.wasReleased()){buttona = true;}
        M5.update(); 
     }
     buttona = false;
     
  }
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0, 100);
  M5.Lcd.setTextSize(2);
  M5.Lcd.println("   Hora de verificar");
  M5.Lcd.println("   as palavras!");
  delay(6000);
  for (int z = 0; z < 24; z++){
      M5.Lcd.fillScreen(BLACK);
      M5.Lcd.setCursor(0, 70);
      M5.Lcd.setTextSize(2);
      M5.Lcd.println("   Palavra " + String(z+1));
      M5.Lcd.println("");
      M5.Lcd.setTextSize(5);
      M5.Lcd.setTextColor(BLUE);
      M5.Lcd.println("  " + getValue(seedgeneratestr,' ',z));
      M5.Lcd.setTextSize(2);
      M5.Lcd.println("");
      M5.Lcd.setTextColor(GREEN);
      M5.Lcd.println("   Pressione A para seguir");

     while (buttona == false){
        if (M5.BtnA.wasReleased()){buttona = true;}
        M5.update(); 
     }
     buttona = false;
  }
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0, 100);
  M5.Lcd.println("   As palavras tambem");
  M5.Lcd.println("   serao salvas no SD");

  File file = SPIFFS.open("/key.txt", FILE_WRITE);
  file.print(seedgeneratestr.substring(0, seedgeneratestr.length() - 1) + "\n");
  file.close();
  
  String seedgen = "Guarde as 24 palavras abaixo em um lugar seguro: \n" + seedgeneratestr + "\n\nÉ recomendável excluir este arquivo ou manter sempre offline. Para saber mais sobre as palavras de seed, acesse https://bitcoinheiros.com/duvidas-sobre-carteiras-bitcoin \n\nCOMANDOS ADICIONAIS: \n\n1. Para restaurar esta seed em sua carteira, crie um arquivo chamado 'moon.txt' no cartão SD e inclua a frase 'RESTORE' (sem aspas) e as 24 palavras acima separadas por 1 espaço cada. \n\n2. Para assinar uma transação, copie a transação criada na Electrum e cole ao lado da palavra 'SIGN' (sem aspas) no arquivo 'moon.txt' em seu cartão SD. \n\n3. Para reiniciar a carteira, escreva 'HARD RESET' (sem aspas) no arquivo 'moon.txt' na pasta base do cartão micro SD e reinicie o dispositivo";
  int str_len = seedgen.length() + 1; 
  char char_array[str_len];
  seedgen.toCharArray(char_array, str_len);

  File otherfile = SPIFFS.open("/key.txt");
  savedseed = otherfile.readStringUntil('\n');
  otherfile.close();

  writeFile(SD, "/seed.txt", char_array);
  
  delay(6000);
}

//========================================================================
void pinmaker(){
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0, 90);
  M5.Lcd.setTextColor(GREEN);
  M5.Lcd.println("   Insira o pin usando");
  M5.Lcd.println("   codigo morse,");
  M5.Lcd.println("   pelo menos 3 letras");
  delay(6000);
  enterpin(true);
}

//========================================================================
void enterpin(bool set){
  morseletter = "";
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextColor(GREEN);
  M5.Lcd.setCursor(0, 100);
  M5.Lcd.setTextSize(3);
  M5.Lcd.print("  Insira o pin");
  confirm = false;
  while(confirm == false){
   if (M5.BtnA.wasReleased()){
    buttona = true; 
    morseletter = morseletter + "1";
    timy = millis();
   }
   if (M5.BtnB.wasReleased()){
    buttonb = true; 
    morseletter = morseletter + "0";
    timy = millis();
   }
   if (M5.BtnC.wasReleased()){
     
     if (set == true){
       uint8_t newpasskeyresult[32];
       sha256(passkey, newpasskeyresult);
       hashed = toHex(newpasskeyresult,32);
          
       File file = SPIFFS.open("/pass.txt", FILE_WRITE);
       file.print(hashed + "\n");
       file.close();
     }
     
     File otherfile = SPIFFS.open("/pass.txt");
     savedpinhash = otherfile.readStringUntil('\n');
     otherfile.close();
         
     uint8_t passkeyresult[32];
     sha256(passkey, passkeyresult);
     hashed = toHex(passkeyresult,32);
     Serial.println(savedpinhash);
     Serial.println(hashed);
     
     if(savedpinhash == hashed || set == true ){
        getKeys(savedseed, passkey);
        //passkey = "";
        passhide = "";
        confirm = true;
        return;
     }
     else if (savedpinhash != hashed && set == false){
        M5.Lcd.fillScreen(BLACK);
        M5.Lcd.setCursor(0, 110);
        M5.Lcd.setTextSize(2);
        M5.Lcd.setTextColor(RED);
        M5.Lcd.print("  Reinicie e tente de novo");
        passkey = "";
        passhide = "";
        delay(3000);
     }
   }
   M5.update(); 
   if ((millis() - timy) > 2000) {
      if (buttona == true || buttonb == true){
         for (int z = 0; z < 36; z++){
             if (morseletter == ref[0][z]){
                passkey += ref[1][z];
                passhide += "* ";
                M5.Lcd.fillScreen(BLACK);
                M5.Lcd.setTextSize(3);
                M5.Lcd.setCursor(0, 90);
                M5.Lcd.setTextColor(GREEN);
                if(set == true){
                   M5.Lcd.print("   " + passkey);
                }
                else{
                   M5.Lcd.print("   " + passhide);
       }}}
      buttona = false;
      buttonb = false;
      morseletter = "";
   }}}
  confirm = false;
}

//========================================================================

void restorefromseed(String theseed){
  
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setCursor(0, 20);
    M5.Lcd.setTextSize(3);
    M5.Lcd.setTextColor(GREEN);
    M5.Lcd.println("Restaurar de seed");
    M5.Lcd.setCursor(0, 85);
    M5.Lcd.setTextColor(RED);
    M5.Lcd.setTextSize(2);
    M5.Lcd.println("O dispositivo sera zerado");
    M5.Lcd.println("e entao restaurado.");
    M5.Lcd.println("Tem certeza?");
    M5.Lcd.setTextSize(2);
    M5.Lcd.setCursor(0, 220);
    M5.Lcd.println("A continuar, C cancelar");

    while (buttona == false && buttonc == false){
      if (M5.BtnA.wasReleased()){buttona = true;}
      if (M5.BtnC.wasReleased()){buttonc = true;}
      M5.update(); 
    }
    if (buttona == true){
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setCursor(0, 100);
    M5.Lcd.setTextColor(GREEN);
    M5.Lcd.setTextSize(2);
    M5.Lcd.println("   Salvando seed...");
    delay(2000);
    File file = SPIFFS.open("/key.txt", FILE_WRITE);
    file.print(theseed + "\n");
    file.close();
    writeFile(SD, "/moon.txt", ""); 
    }
     
  buttona = false;
  buttonc = false;
}

//========================================================================
void sdchecker(){
  readFile(SD, "/moon.txt");

}

//========================================================================
String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length()-1;

  for(int i=0; i<=maxIndex && found<=index; i++){
    if(data.charAt(i)==separator || i==maxIndex){
        found++;
        strIndex[0] = strIndex[1]+1;
        strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }

  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}

//========================================================================
void getKeys(String mnemonic, String password)
{

  HDPrivateKey hd(mnemonic, password);

  if(!hd){ // check if it is valid
    Serial.println("   Xpub invalida");
    return;
  }
  
  HDPrivateKey account = hd.derive("m/84'/0'/0'/");
  
  privatekey = account;
  
   pubkey = account.xpub();
 
 
}

//========================================================================
void readFile(fs::FS &fs, const char * path) {
    File file = fs.open(path);
    if(!file){
        Serial.println("   Falha ao abrir o arquivo para ler");
        return;
    }
      while(file.available()){
          sdcommand = file.readStringUntil('\n');
      }

}



//========================================================================
void writeFile(fs::FS &fs, const char * path, const char * message){


    File file = fs.open(path, FILE_WRITE);
    if(!file){

        M5.Lcd.println("   Falha ao abrir arquivo para escrever");
        return;
    }
    if(file.print(message)){

    } else {
        M5.Lcd.println("   Falha ao escrever");
    }
}

//========================================================================
void writeIntIntoEEPROM(int addresss, int number)
{ 
  EEPROM.write(addresss, number);
}
int readIntFromEEPROM(int addresss)
{
  return EEPROM.read(addresss);
}
