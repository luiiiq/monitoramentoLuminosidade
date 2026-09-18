// Projeto: Monitoramento de Luminosidade com Sensor LDR e LEDs Indicadores
// Descrição: Altera o LED aceso com base na intensidade de luz captada.

// Inclusão de Biblioteca
#include <LiquidCrystal.h>

// Configuração do Display LCD
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Definição dos pinos
int buzzer = 8;
int ledVerde = 13;
int ledAmarelo = 10;
int ledVermelho = 9;
int LDR = A0;

// Valor inicial LDR e porcentagem inicial
int valorLDR = 0;
int porcentagemLuz = 0;

int NUM_LEITURAS = 10;


// Variáveis do Buzzer
unsigned long tempoInicioBuzzer = 0;
bool buzzerTocando = false;
bool jaTocouNoAmarelo = false;

// FRAME 01 - Animação: Introdução da folha (Cena inicial de tamanho intermédio)
byte frame01_0[8] = {
  B11110,
  B11110,
  B11111,
  B11111,
  B11110,
  B11100,
  B11100,
  B11100
};

byte frame01_1[8] = {
  B11010,
  B11110,
  B11000,
  B10000,
  B00000,
  B00000,
  B00000,
  B00000
};

byte frame01_2[8] = {
  B00000,
  B00000,
  B00000,
  B00001,
  B00011,
  B00010,
  B00110,
  B11111
};

byte frame01_3[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00001,
  B00011,
  B11111,
  B10000
};

byte frame01_4[8] = {
  B00000,
  B00000,
  B00000,
  B11000,
  B10110,
  B00001,
  B11001,
  B00111
};

byte frame01_5[8] = {
  B11100,
  B11100,
  B11111,
  B11111,
  B11111,
  B11111,
  B11110,
  B11111
};

byte frame01_6[8] = {
  B00011,
  B01111,
  B11111,
  B11100,
  B10000,
  B00000,
  B00000,
  B00000
};

byte frame01_7[8] = {
  B11000,
  B00000,
  B10000,
  B11000,
  B00000,
  B00000,
  B00000,
  B00000
};


// ZOOM A: Primeira fase da aproximação da folha à câmara

byte zoomA0[8] = {
  B11100,
  B11110,
  B11111,
  B11111,
  B11110,
  B11100,
  B11000,
  B10000
};

byte zoomA1[8] = {
  B11000,
  B11100,
  B11110,
  B11000,
  B10000,
  B00000,
  B00000,
  B00000
};

byte zoomA2[8] = {
  B00000,
  B00000,
  B00000,
  B00011,
  B00111,
  B00110,
  B01100,
  B11100
};

byte zoomA3[8] = {
  B00000,
  B00000,
  B00000,
  B00001,
  B00011,
  B00111,
  B11100,
  B10000
};

byte zoomA4[8] = {
  B00000,
  B00000,
  B00000,
  B10000,
  B11000,
  B01100,
  B00110,
  B00011
};

byte zoomA5[8] = {
  B11000,
  B11100,
  B11110,
  B11111,
  B11111,
  B11110,
  B11100,
  B11000
};

byte zoomA6[8] = {
  B00001,
  B00111,
  B01111,
  B11110,
  B11000,
  B10000,
  B00000,
  B00000
};


// ZOOM B: Transição intermédia de escala

byte zoomB0[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00001,
  B00011,
  B00111,
  B00100
};

byte zoomB1[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B10000,
  B11000,
  B01000
};

byte zoomB2[8] = {
  B00000,
  B00000,
  B00001,
  B01111,
  B11111,
  B11110,
  B11000,
  B00000
};

byte zoomB3[8] = {
  B00000,
  B00000,
  B00011,
  B11110,
  B11000,
  B10000,
  B00000,
  B00000
};

byte zoomB4[8] = {
  B00000,
  B10000,
  B11000,
  B11100,
  B01110,
  B00110,
  B00000,
  B00000
};

byte zoomB5[8] = {
  B00000,
  B00100,
  B01100,
  B11010,
  B01110,
  B00100,
  B00000,
  B00000
};


// FRAME 02: Estabilização da trajetória da folha

byte frame02_0[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00011,
  B00100
};

byte frame02_1[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B10000,
  B01000
};

byte frame02_2[8] = {
  B00000,
  B00000,
  B00000,
  B00111,
  B11111,
  B11111,
  B11100,
  B00000
};

byte frame02_3[8] = {
  B00000,
  B00000,
  B00111,
  B11100,
  B10000,
  B00000,
  B00000,
  B00000
};

byte frame02_4[8] = {
  B01000,
  B10001,
  B11110,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};

byte frame02_5[8] = {
  B00100,
  B10010,
  B11001,
  B01110,
  B00000,
  B00000,
  B00000,
  B00000
};


// FRAME 03 / 04: Estrutura estática da folha no ponto médio

byte folhaBase0[8] = {
  B00000,
  B00000,
  B00000,
  B00111,
  B11111,
  B11111,
  B11100,
  B00000
};

byte folhaBase1[8] = {
  B00000,
  B00000,
  B00111,
  B11100,
  B10000,
  B00000,
  B00000,
  B00000
};

byte frame03_2[8] = {
  B00000,
  B00001,
  B11010,
  B00101,
  B00010,
  B00001,
  B00000,
  B00000
};

byte frame03_3[8] = {
  B01100,
  B10011,
  B00001,
  B10100,
  B00001,
  B00010,
  B11100,
  B00000
};

byte frame03_4[8] = {
  B00000,
  B11010,
  B00100,
  B01000,
  B10000,
  B00000,
  B00000,
  B00000
};


// Folha Voando - FRAME A: Oscilação (Fase superior)

byte vooA0[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00001,
  B00010,
  B01100,
  B10000
};

byte vooA1[8] = {
  B00000,
  B00000,
  B01000,
  B11000,
  B01000,
  B01000,
  B10000,
  B10000
};

byte vooA2[8] = {
  B00000,
  B00001,
  B00010,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};

byte vooA3[8] = {
  B11001,
  B01110,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};


// Folha Voando - FRAME B: Oscilação aerodinâmica (Fase inferior)

byte vooB0[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00100,
  B01000
};

byte vooB1[8] = {
  B00000,
  B00111,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};

byte vooB2[8] = {
  B11111,
  B00011,
  B11110,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};

byte vooB3[8] = {
  B11000,
  B10000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};

// Arrays para inversão
// Guardam temporariamente versões invertidas dos desenhos da folha.

byte invertido0[8];
byte invertido1[8];
byte invertido2[8];
byte invertido3[8];

// Transição Final - ENTRADA 1: Início do fecho da cena 
byte entrada1_0[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00001,
  B00110
};

byte entrada1_1[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00001,
  B00110,
  B11000
};

// Transição Final - ENTRADA 2: Avanço do preenchimento geométrico
byte entrada2_0[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00001,
  B00010,
  B00100,
  B11000
};

byte entrada2_1[8] = {
  B00000,
  B00000,
  B00000,
  B00001,
  B00110,
  B01000,
  B10000,
  B00000
};

byte entrada2_2[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B10000,
  B01000,
  B00100,
  B00010
};


// Transição Final - ENTRADA 3: Quase oclusão do espaço

byte entrada3_0[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00001,
  B00010,
  B00100,
  B01000
};

byte entrada3_1[8] = {
  B00000,
  B00000,
  B00001,
  B00010,
  B00100,
  B01000,
  B10000,
  B00000
};

byte entrada3_2[8] = {
  B00000,
  B00001,
  B00010,
  B00100,
  B01000,
  B10000,
  B00000,
  B00000
};

byte entrada3_3[8] = {
  B00001,
  B00010,
  B00100,
  B01000,
  B10000,
  B00000,
  B00000,
  B00000
};

// Frame Central - Folha mais Próxima: O pico do efeito "Macro/Zoom"
byte close0[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00001,
  B00010,
  B01100,
  B10000
};

byte close1[8] = {
  B00100,
  B01000,
  B10000,
  B10000,
  B00000,
  B00000,
  B00000,
  B00000
};

byte close2[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00001,
  B00110,
  B01000,
  B10000
};

byte close3[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B11111,
  B11110,
  B00001,
  B00000
};

byte close4[8] = {
  B00001,
  B00010,
  B00100,
  B11000,
  B00000,
  B00000,
  B11000,
  B00110
};

byte close5[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B01111,
  B00000,
  B00000,
  B00000
};

byte close6[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00011,
  B00010,
  B00100,
  B01000
};

byte close7[8] = {
  B00000,
  B00100,
  B01000,
  B10000,
  B00000,
  B00000,
  B00000,
  B00000
};

// Transição Final - SAÍDA 1: Limpeza da tela por varrimento diagonal
byte saida1_0[8] = {
  B00000,
  B00001,
  B00010,
  B00100,
  B01000,
  B10000,
  B00000,
  B00000
};

byte saida1_1[8] = {
  B00001,
  B00010,
  B00100,
  B01000,
  B10000,
  B00000,
  B00000,
  B00000
};

byte saida1_2[8] = {
  B00010,
  B00100,
  B01000,
  B10000,
  B00000,
  B00000,
  B00000,
  B00000
};

byte saida1_3[8] = {
  B00100,
  B01000,
  B10000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};

// Transição Final - SAÍDA 2: Conclusão do corte
byte saida2_0[8] = {
  B00000,
  B00000,
  B00001,
  B00010,
  B00100,
  B01000,
  B10000,
  B00000
};

byte saida2_1[8] = {
  B00000,
  B00001,
  B00010,
  B00100,
  B01000,
  B10000,
  B00000,
  B00000
};

byte saida2_2[8] = {
  B00001,
  B00010,
  B00100,
  B01000,
  B10000,
  B00000,
  B00000,
  B00000
};

// Transição Final - SAÍDA 3
// Descrição: Frame final de corte geométrico antes da revelação do logótipo.
byte saida3_0[8] = {
  B00000,
  B00000,
  B00000,
  B00001,
  B00010,
  B00100,
  B01000,
  B10000
};

byte saida3_1[8] = {
  B00001,
  B00010,
  B00100,
  B01000,
  B10000,
  B00000,
  B00000,
  B00000
};

// Logo
char logoLinha1[] = "   CALM TECH    ";
char logoLinha2[] = "      TEAM      ";

// Utilidades da Animação
// Reúnem operações repetidas de limpeza da tela e manipulação dos desenhos,
// deixando as funções de cada cena mais simples de acompanhar


// Limpa as Duas llinhas LCD, evitando que partes de uma imagem antiga permaneçam visíveis.
void limpaTela() {
  lcd.setCursor(0, 0);
  lcd.print("                "); // Limpa tela superior

  lcd.setCursor(0, 1);
  lcd.print("                "); // Limpa tela inferior
}

// Inverte verticalmente um caractere
// Cada bitmap tem 8 linhas. Copiamos as linhas de baixo para cima
// para produzir uma versão verticalmente invertida do desenho.
// Recebe um bitmap de 8 linhas e grava no destino a ordem inversa das linhas.
void inverterVertical(byte original[8], byte destino[8]) {
  for (int i = 0; i < 8; i++) {
    destino[i] = original[7 - i];
  }
}

// FRAME 01
void mostrarFrame01() {
  lcd.createChar(0, frame01_0);
  lcd.createChar(1, frame01_1);
  lcd.createChar(2, frame01_2);
  lcd.createChar(3, frame01_3);
  lcd.createChar(4, frame01_4);
  lcd.createChar(5, frame01_5);
  lcd.createChar(6, frame01_6);
  lcd.createChar(7, frame01_7);

  limpaTela();

  lcd.setCursor(0, 0); lcd.write(byte(0));
  lcd.setCursor(1, 0); lcd.write(byte(1));
  lcd.setCursor(2, 0); lcd.write(byte(2));
  lcd.setCursor(3, 0); lcd.write(byte(3));
  lcd.setCursor(4, 0); lcd.write(byte(4));

  lcd.setCursor(0, 1); lcd.write(byte(5));
  lcd.setCursor(1, 1); lcd.write(byte(6));
  lcd.setCursor(2, 1); lcd.write(byte(7));
}

// ZOOM A
void mostrarZoomA() {
  lcd.createChar(0, zoomA0);
  lcd.createChar(1, zoomA1);
  lcd.createChar(2, zoomA2);
  lcd.createChar(3, zoomA3);
  lcd.createChar(4, zoomA4);
  lcd.createChar(5, zoomA5);
  lcd.createChar(6, zoomA6);

  limpaTela();

  lcd.setCursor(0, 0); lcd.write(byte(0));
  lcd.setCursor(1, 0); lcd.write(byte(1));
  lcd.setCursor(2, 0); lcd.write(byte(2));
  lcd.setCursor(3, 0); lcd.write(byte(3));
  lcd.setCursor(4, 0); lcd.write(byte(4));

  lcd.setCursor(0, 1); lcd.write(byte(5));
  lcd.setCursor(1, 1); lcd.write(byte(6));
}

// ZOOM B
void mostrarZoomB() {
  lcd.createChar(0, zoomB0);
  lcd.createChar(1, zoomB1);
  lcd.createChar(2, zoomB2);
  lcd.createChar(3, zoomB3);
  lcd.createChar(4, zoomB4);
  lcd.createChar(5, zoomB5);

  limpaTela();

  lcd.setCursor(2, 0); lcd.write(byte(0));
  lcd.setCursor(3, 0); lcd.write(byte(1));

  lcd.setCursor(0, 1); lcd.write(byte(2));
  lcd.setCursor(1, 1); lcd.write(byte(3));
  lcd.setCursor(2, 1); lcd.write(byte(4));
  lcd.setCursor(3, 1); lcd.write(byte(5));
}

// FRAME 02
void mostrarFrame02() {
  lcd.createChar(0, frame02_0);
  lcd.createChar(1, frame02_1);
  lcd.createChar(2, frame02_2);
  lcd.createChar(3, frame02_3);
  lcd.createChar(4, frame02_4);
  lcd.createChar(5, frame02_5);

  limpaTela();

  lcd.setCursor(2, 0); lcd.write(byte(0));
  lcd.setCursor(3, 0); lcd.write(byte(1));

  lcd.setCursor(0, 1); lcd.write(byte(2));
  lcd.setCursor(1, 1); lcd.write(byte(3));
  lcd.setCursor(2, 1); lcd.write(byte(4));
  lcd.setCursor(3, 1); lcd.write(byte(5));
}

// FRAME 03
void mostrarFrame03() {
  lcd.createChar(0, folhaBase0);
  lcd.createChar(1, folhaBase1);
  lcd.createChar(2, frame03_2);
  lcd.createChar(3, frame03_3);
  lcd.createChar(4, frame03_4);

  limpaTela();

  lcd.setCursor(0, 1); lcd.write(byte(0));
  lcd.setCursor(1, 1); lcd.write(byte(1));
  lcd.setCursor(2, 1); lcd.write(byte(2));
  lcd.setCursor(3, 1); lcd.write(byte(3));
  lcd.setCursor(4, 1); lcd.write(byte(4));
}

// FRAME 04
void mostrarFrame04() {
  lcd.createChar(0, folhaBase0);
  lcd.createChar(1, folhaBase1);
  lcd.createChar(2, frame03_2);
  lcd.createChar(3, frame03_3);
  lcd.createChar(4, frame03_4);

  limpaTela();

  lcd.setCursor(0, 1); lcd.write(byte(0));
  lcd.setCursor(1, 1); lcd.write(byte(1));
  lcd.setCursor(2, 1); lcd.write(byte(2));
  lcd.setCursor(3, 1); lcd.write(byte(3));
  lcd.setCursor(4, 1); lcd.write(byte(4));
}

// FOLHA VOANDO A
void desenhaVooA(int deslocamento) {
  lcd.createChar(0, vooA0);
  lcd.createChar(1, vooA1);
  lcd.createChar(2, vooA2);
  lcd.createChar(3, vooA3);

  limpaTela();

  int c;

  c = 4 + deslocamento;
  if (c >= 0 && c < 16) {
    lcd.setCursor(c, 0);
    lcd.write(byte(0));
  }

  c = 5 + deslocamento;
  if (c >= 0 && c < 16) {
    lcd.setCursor(c, 0);
    lcd.write(byte(1));
  }

  c = 3 + deslocamento;
  if (c >= 0 && c < 16) {
    lcd.setCursor(c, 1);
    lcd.write(byte(2));
  }

  c = 4 + deslocamento;
  if (c >= 0 && c < 16) {
    lcd.setCursor(c, 1);
    lcd.write(byte(3));
  }
}

// FOLHA VOANDO B
void desenhaVooB(int deslocamento) {
  lcd.createChar(0, vooB0);
  lcd.createChar(1, vooB1);
  lcd.createChar(2, vooB2);
  lcd.createChar(3, vooB3);

  limpaTela();

  int c;

  c = 6 + deslocamento;
  if (c >= 0 && c < 16) {
    lcd.setCursor(c, 0);
    lcd.write(byte(0));
  }

  c = 4 + deslocamento;
  if (c >= 0 && c < 16) {
    lcd.setCursor(c, 1);
    lcd.write(byte(1));
  }

  c = 5 + deslocamento;
  if (c >= 0 && c < 16) {
    lcd.setCursor(c, 1);
    lcd.write(byte(2));
  }

  c = 6 + deslocamento;
  if (c >= 0 && c < 16) {
    lcd.setCursor(c, 1);
    lcd.write(byte(3));
  }
}

// FOLHA VOANDO A INVERTIDA
void desenhaVooAInvertido(int deslocamento) {
  inverterVertical(vooA0, invertido0);
  inverterVertical(vooA1, invertido1);
  inverterVertical(vooA2, invertido2);
  inverterVertical(vooA3, invertido3);

  lcd.createChar(0, invertido0);
  lcd.createChar(1, invertido1);
  lcd.createChar(2, invertido2);
  lcd.createChar(3, invertido3);

  limpaTela();

  int c;

  c = 4 + deslocamento;
  if (c >= 0 && c < 16) {
    lcd.setCursor(c, 1);
    lcd.write(byte(0));
  }

  c = 5 + deslocamento;
  if (c >= 0 && c < 16) {
    lcd.setCursor(c, 1);
    lcd.write(byte(1));
  }

  c = 3 + deslocamento;
  if (c >= 0 && c < 16) {
    lcd.setCursor(c, 0);
    lcd.write(byte(2));
  }

  c = 4 + deslocamento;
  if (c >= 0 && c < 16) {
    lcd.setCursor(c, 0);
    lcd.write(byte(3));
  }
}

// FOLHA VOANDO B INVERTIDA
void desenhaVooBInvertido(int deslocamento) {
  inverterVertical(vooB0, invertido0);
  inverterVertical(vooB1, invertido1);
  inverterVertical(vooB2, invertido2);
  inverterVertical(vooB3, invertido3);

  lcd.createChar(0, invertido0);
  lcd.createChar(1, invertido1);
  lcd.createChar(2, invertido2);
  lcd.createChar(3, invertido3);

  limpaTela();

  int c;

  c = 6 + deslocamento;
  if (c >= 0 && c < 16) {
    lcd.setCursor(c, 1);
    lcd.write(byte(0));
  }

  c = 4 + deslocamento;
  if (c >= 0 && c < 16) {
    lcd.setCursor(c, 0);
    lcd.write(byte(1));
  }

  c = 5 + deslocamento;
  if (c >= 0 && c < 16) {
    lcd.setCursor(c, 0);
    lcd.write(byte(2));
  }

  c = 6 + deslocamento;
  if (c >= 0 && c < 16) {
    lcd.setCursor(c, 0);
    lcd.write(byte(3));
  }
}


// Animação do voo da folha
void folhaVoando() {
  desenhaVooA(0);
  delay(170);

  desenhaVooB(0);
  delay(140);

  desenhaVooAInvertido(2);
  delay(150);

  desenhaVooBInvertido(3);
  delay(130);

  desenhaVooA(5);
  delay(150);

  desenhaVooB(6);
  delay(130);

  desenhaVooAInvertido(8);
  delay(140);

  desenhaVooBInvertido(9);
  delay(120);

  desenhaVooA(11);
  delay(130);

  desenhaVooB(13);
  delay(100);

  limpaTela();
}

// Desenha uma parte do Logo
// Mostra somente a quantidade de colunas solicitada, permitindo revelar
// o texto gradualmente durante a animação de saída da folha.
void desenhaLogoAte(int quantidadeColunas) {
  if (quantidadeColunas < 0) {
    quantidadeColunas = 0;
  }

  if (quantidadeColunas > 16) {
    quantidadeColunas = 16;
  }

  for (int coluna = 0; coluna < quantidadeColunas; coluna++) {

    lcd.setCursor(coluna, 0);
    lcd.print(logoLinha1[coluna]);

    lcd.setCursor(coluna, 1);
    lcd.print(logoLinha2[coluna]);
  }
}

// ENTRADA 1
void mostrarEntrada1() {
  lcd.createChar(0, entrada1_0);
  lcd.createChar(1, entrada1_1);

  limpaTela();

  lcd.setCursor(0, 1);
  lcd.write(byte(0));

  lcd.setCursor(1, 1);
  lcd.write(byte(1));
}

// ENTRADA 2
void mostrarEntrada2() {
  lcd.createChar(0, entrada2_0);
  lcd.createChar(1, entrada2_1);
  lcd.createChar(2, entrada2_2);

  limpaTela();

  lcd.setCursor(0, 1);
  lcd.write(byte(0));

  lcd.setCursor(1, 1);
  lcd.write(byte(1));

  lcd.setCursor(2, 1);
  lcd.write(byte(2));
}

// ENTRADA 3
void mostrarEntrada3() {
  lcd.createChar(0, entrada3_0);
  lcd.createChar(1, entrada3_1);
  lcd.createChar(2, entrada3_2);
  lcd.createChar(3, entrada3_3);

  limpaTela();

  lcd.setCursor(1, 1);
  lcd.write(byte(0));

  lcd.setCursor(2, 1);
  lcd.write(byte(1));

  lcd.setCursor(2, 0);
  lcd.write(byte(2));

  lcd.setCursor(3, 0);
  lcd.write(byte(3));
}

// FRAME Central da folha
void mostrarFolhaCentral() {
  lcd.createChar(0, close0);
  lcd.createChar(1, close1);
  lcd.createChar(2, close2);
  lcd.createChar(3, close3);
  lcd.createChar(4, close4);
  lcd.createChar(5, close5);
  lcd.createChar(6, close6);
  lcd.createChar(7, close7);

  limpaTela();

  lcd.setCursor(2, 0);
  lcd.write(byte(0));

  lcd.setCursor(3, 0);
  lcd.write(byte(1));

  lcd.setCursor(7, 0);
  lcd.write(byte(2));

  lcd.setCursor(0, 1);
  lcd.write(byte(3));

  lcd.setCursor(1, 1);
  lcd.write(byte(4));

  lcd.setCursor(3, 1);
  lcd.write(byte(5));

  lcd.setCursor(10, 1);
  lcd.write(byte(6));

  lcd.setCursor(11, 1);
  lcd.write(byte(7));
}

// SAÍDA 1
void mostrarSaida1() {
  lcd.createChar(0, saida1_0);
  lcd.createChar(1, saida1_1);
  lcd.createChar(2, saida1_2);
  lcd.createChar(3, saida1_3);

  limpaTela();

  desenhaLogoAte(5);

  lcd.setCursor(8, 1);
  lcd.write(byte(0));

  lcd.setCursor(9, 1);
  lcd.write(byte(1));

  lcd.setCursor(10, 0);
  lcd.write(byte(2));

  lcd.setCursor(11, 0);
  lcd.write(byte(3));
}

// SAÍDA 2
void mostrarSaida2() {
  lcd.createChar(0, saida2_0);
  lcd.createChar(1, saida2_1);
  lcd.createChar(2, saida2_2);

  limpaTela();

  desenhaLogoAte(10);

  lcd.setCursor(11, 0);
  lcd.write(byte(0));

  lcd.setCursor(12, 0);
  lcd.write(byte(1));

  lcd.setCursor(13, 0);
  lcd.write(byte(2));
}

// SAÍDA 3
void mostrarSaida3() {
  lcd.createChar(0, saida3_0);
  lcd.createChar(1, saida3_1);

  limpaTela();

  desenhaLogoAte(14);

  lcd.setCursor(14, 0);
  lcd.write(byte(0));

  lcd.setCursor(15, 0);
  lcd.write(byte(1));
}

// Transição final da folha
// Apresenta quadros de entrada, aproximação e saída da folha.
// Ao final, revela o nome da equipe no LCD.
void transicaoFolhaGigante() {
  mostrarEntrada1();
  delay(80);

  mostrarEntrada2();
  delay(80);

  mostrarEntrada3();
  delay(100);

  mostrarFolhaCentral();
  delay(150);

  mostrarSaida1();
  delay(100);

  mostrarSaida2();
  delay(80);

  mostrarSaida3();
  delay(80);

  // Logo final
  limpaTela();

  lcd.setCursor(3, 0);
  lcd.print("CALM TECH");

  lcd.setCursor(6, 1);
  lcd.print("TEAM");

  delay(2000);
}

// Animação de Abertura
// Executa os quadros de introdução, aproximação e voo da folha,
// antes de iniciar a tela de boas-vindas e o monitoramento.
void animacaoIntroducao() {
  mostrarFrame01();
  delay(700);

  mostrarZoomA();
  delay(180);

  mostrarZoomB();
  delay(180);

  mostrarFrame02();
  delay(350);

  mostrarFrame03();
  delay(250);

  mostrarFrame04();
  delay(350);

  folhaVoando();

  delay(80);

  transicaoFolhaGigante();
}

// SETUP: Executado uma única vez ao ligar ou reiniciar
void setup() {
    // Configuração das portas
    pinMode(ledVerde, OUTPUT);
    pinMode(ledAmarelo, OUTPUT);
    pinMode(ledVermelho, OUTPUT);
    pinMode(buzzer, OUTPUT);
    pinMode(LDR, INPUT);

    lcd.begin(16, 2);

    animacaoIntroducao();

    // Iniciando Monitoramento animação
    lcd.clear();

    lcd.setCursor(2, 0);
    lcd.print("Iniciando");

    lcd.setCursor(2, 1);
    lcd.print("monitoramento");

    delay(2000);

    // Sejam Bem-vindos(a)
    lcd.clear();
    lcd.setCursor(5, 1);
    lcd.print("Sejam");
    delay(600);

    lcd.clear();
    lcd.setCursor(5, 0);
    lcd.print("Sejam");
    delay(600);

    // Faz "Bem-vindos(a)" aparecer embaixo
    lcd.clear();

    lcd.setCursor(5, 0);
    lcd.print("Sejam");

    lcd.setCursor(1, 1);
    lcd.print("Bem-vindos(a)");

    delay(1000);

    // Depois "Bem-vindos(a)" sobe
    lcd.clear();

    lcd.setCursor(1, 0);
    lcd.print("Bem-vindos(a)");

    delay(1200);

    lcd.clear();
    delay(500);

    // Textos fixos do monitoramento

    lcd.setCursor(0, 0);
    lcd.print("Luz:"); // Luminosidade

    lcd.setCursor(0, 1);
    lcd.print("Status:"); // Status do ambiente
}

// LOOP: Monitoramento com valores médios
void loop() {
  	// Acumula as amostras do sensor antes de calcular a média.
    long somaLeituras = 0;

  	// Repete a leitura NUM_LEITURAS vezes para reduzir oscilações pontuais.
    for (int i = 0; i < NUM_LEITURAS; i++) {
        somaLeituras += analogRead(LDR);
        delay(10); 
    }
	
  	// Calcula a média das amostras
    valorLDR = (somaLeituras + (NUM_LEITURAS / 2))/ NUM_LEITURAS;

  	// map() transforma a faixa calibrada da leitura do LDR em uma escala
    // aproximada de porcentagem para apresentação no LCD.
    porcentagemLuz =  map(valorLDR + 4,6,167,0,97);

	// Exibe a luminosidade convertida
    lcd.setCursor(5, 0);
    lcd.print(porcentagemLuz);
    lcd.print("%   ");

    // LED Verde: OK
    if (valorLDR < 90) {
        apagaLeds(); 
        digitalWrite(ledVerde, HIGH);

        jaTocouNoAmarelo = false; 
        lcd.setCursor(8, 1);
        lcd.print("OK      "); 
    }

    // LED Amarelo - Alerta
    else if (valorLDR >= 90 && valorLDR < 120) {
        digitalWrite(ledVerde, LOW);
        digitalWrite(ledVermelho, LOW);
        digitalWrite(ledAmarelo,HIGH);

        lcd.setCursor(8, 1);
        lcd.print("Alerta  ");

        // Ativa o alarme por apenas 3 segundos
        // sem travar a leitura
      	// millis() permite medir o tempo decorrido sem usar uma pausa longa,
		// mantendo o ciclo de monitoramento em execução.
        if (!buzzerTocando &&!jaTocouNoAmarelo) {
            tone(buzzer,1000);
            tempoInicioBuzzer = millis();
            buzzerTocando = true;
            jaTocouNoAmarelo = true;
        }
    }

    // LED Vermelho - ERROR
    else {
        apagaLeds();
        digitalWrite(ledVermelho,HIGH);

        jaTocouNoAmarelo = false;
        lcd.setCursor(8, 1);

        lcd.print("ERROR!  ");
      	delay(500);
      
      	// Efeito de piscar ERROR!
        lcd.setCursor(8, 1);
        lcd.print("      ");
        delay(300);
      
        // Buzzer tocando em intervalos para avisar ERRO
      	if (!buzzerTocando) {
            tone(buzzer, 1000);
          	delay(50);
        }
    }

    // Desliga Buzzer depois de 3 segundos  e atualiza
	// o estado buzzerTocando para permitir novos acionamentos.
    if (buzzerTocando) {
        if (
          millis() - tempoInicioBuzzer
          >= 3000
        ) {
            noTone(buzzer);

            buzzerTocando =
              false;
        }
    }

    delay(100);
}


// Desliga Leds e Buzzer
void apagaLeds() {
    digitalWrite(ledVerde,LOW); // Desliga LED Verde

    digitalWrite(ledAmarelo,LOW); // Desliga LED Amarelo

    digitalWrite(ledVermelho,LOW); // Desliga LED Vermelho

    noTone(buzzer); // Desliga buzzer

    buzzerTocando = false; // buzzer volta pra false
}