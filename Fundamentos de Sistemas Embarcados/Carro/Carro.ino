#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <Math.h>

// Constantes do display
#define DISPLAYADDR 0x27
#define DISPLAYCOL 20
#define DISPLAYROW 4
/* 

  LAYOUT DO DISPLAY:

  Velocidade: xxxx kmh
  Proximidade: [xxxxx]
  Farol:       xxxxxxx
  A/C:         xxxxxxx

*/

// Pinos usados
#define KEYPIN A0 // Potenciômetro que simula chave
#define PEDALPIN A1 // Potenciômetro que controla acelereação do carro
#define ERRORLEDPIN 0 // Led vermelho de erro
#define SMALLLEDPIN 2 // Dois leds brancos pequenos que representam farol baixo
#define HEADLIGHTBUTTONPIN 4 // Botão para troca de estados dos farois
#define BUZZERPIN 6  // Buzzer que simula uma buzina
#define BIGLEDPIN 7 // Dois leds brancos que servem para simular farol alto
#define ACBUTTONPIN 8 // Botão que liga/desliga o Arcondicionado
#define ECHOPIN 12 // Pino que recebe o sinal de echo do sensor de distância
#define TRIGPIN 13 // Pino que ativa o sinal de echo do sensor de distância

// Tempo entre cada ciclo do programa
#define CYCLETIME 10

// Demarcadores da posição da chave
#define SYSTEM 300
#define ENGINE 900

// Demarcadores de aceleração do pedal
#define POSACC 400
#define NEGACC 300

// Limites de velocidade
#define MAXSPD 100
#define MINSPD -30

// Instanciando display
LiquidCrystal_I2C lcd(DISPLAYADDR, DISPLAYCOL, DISPLAYROW);

// Variáveis globais
bool ACon; // true = ligado, false = desligado
uint8_t headlightState; // 0 = desligado, 1 = farol baixo, 2 = farol alto
uint8_t carState; // 0 = desligado, 1 = painel ligado, 2 = painel e motor ligado
int8_t speed; // Velocidade do carro
uint16_t showErrorUntil; // Armazena até que o ciclo o led de erro estará aceso 
int16_t keyValue; // Valor da chave de ignição
uint32_t cycle; // Contador de ciclos
float distance; // Distancia de algum objeto do sensor

// Chamada quando o motor e painel estão desligados
void startSystem() {
  // Tenta ligar o painel
  if(keyValue >= SYSTEM) {
    // Ligando painel
    lcd.backlight();
    lcd.print("Velocidade: ");
    lcd.setCursor(0, 1);
    lcd.print("Proximidade: ");
    lcd.setCursor(0, 2);
    lcd.print("Farol:     Desligado");
    lcd.setCursor(0, 3);
    lcd.print("A/C: ");

    // Permite acionar a buzina
    analogWrite(BUZZERPIN, 200);

    carState = 1;
  }
}

// Função responsável por atualizar a parte da velocidade do display
// Chamada apenas quando há alteração nos valores
void updateDisplaySpeed() {
  lcd.setCursor(12, 0);
  
  // Estes ifs aqui estão aí para formatar as informações no lugar certo
  // dependendo da quantidade de dígitos no número
  if(speed >= 100) {
    lcd.print(" ");
    lcd.print(speed);
  }
  else if(speed >= 10) {
    lcd.print("  ");
    lcd.print(speed);
  }
  else if(speed >= 0) {
    lcd.print("   ");
    lcd.print(speed);
  }
  else if(speed >= -9) {
    lcd.print("  ");
    lcd.print(speed);
  }
  else if(speed >= -99) {
    lcd.print(" ");
    lcd.print(speed);
  }
  else {
    lcd.print(speed);
  }
}

// Responsável por pegar o valor do potenciômetro 2 e transformar em aceleração
// Além de alterar o valor da velocidade dentro do sistema
// Função chamada a cada 10 ciclos
void updateSpeed() {
  // Armazena o ciclo onde essa função vai poder ser chamada novamente
  static uint32_t disabledUntil = 0;

  if(cycle > disabledUntil) {
    int16_t pedalValue = analogRead(PEDALPIN);
    disabledUntil = cycle + 10; // Desabilitado por 100ms

    // Decidindo velocidade
    if(pedalValue > POSACC && speed < MAXSPD) {
      speed += (pedalValue - 400) / 160;
      updateDisplaySpeed();
    }
    else if(pedalValue <= NEGACC && speed > MINSPD) {
      speed += (pedalValue - 200) / 80;
      updateDisplaySpeed();
    }
  }
}

// Chamada quando o apenas o paínel está ligado
void startEngine() {
  // Esta é a unica funcionalidade ativa enquanto o carro está com apenas o painel ligado
  updateHeadlight();

  // Tenta desligar o sistema
  turnSystemOff();

  // Tenta ligar o motor do carro
  if(keyValue >= ENGINE) {
    // Deixa ligar o motor apenas com potenciômetro de aceleração no neutro
    int16_t pedalValue = analogRead(PEDALPIN);
    if(pedalValue > POSACC || pedalValue < NEGACC) {
      startError(5);

      return;
    }

    // Mostrando os valores
    lcd.setCursor(15, 0);
    lcd.print("0 kmh");
    lcd.setCursor(13, 1);
    lcd.print("[     ]");
    lcd.setCursor(11, 3);
    lcd.print("Desligado");

    carState = 2;
  }
}

// Função responsável por atualizar o campo que mostra o estado atual do farol
// Chamada apenas quando há alteração nos valores
void updateDisplayHeadlight() {
  lcd.setCursor(11, 2);

  // Máquina de estados
  // Os espaços em branco servem para formatação e para apagar os caracteres não sobrepostos
  // pelas palavras menores
  switch(headlightState) {
    case 0: {
      lcd.print("Desligado");
      break;
    }
    case 1: {
      lcd.print("    Baixo");
      break;
    }
    case 2: {
      lcd.print("     Alto");
      break;
    }
  }
}

// Função responsável por mudar os estados dos farois
// Chamada a cada ciclo
void updateHeadlight() {
  // Armazena o ciclo onde essa função vai poder ser chamada novamente
  static uint32_t disabledUntil = 0;

  if(disabledUntil < cycle) {
    bool headlightButton = !digitalRead(HEADLIGHTBUTTONPIN);

    if(headlightButton) {
      disabledUntil = cycle + 20; // Desabilitado por 200ms

      // Máquina de estados 
      switch(headlightState) {
        case 0: {
          digitalWrite(SMALLLEDPIN, HIGH);
          digitalWrite(BIGLEDPIN, LOW);
          headlightState = 1;
          break;
        }
        case 1: {
          digitalWrite(SMALLLEDPIN, HIGH);
          digitalWrite(BIGLEDPIN, HIGH);
          headlightState = 2;
          break;
        }
        case 2: { 
          digitalWrite(SMALLLEDPIN, LOW);
          digitalWrite(BIGLEDPIN, LOW);
          headlightState = 0;
          break;
        }
      }

      updateDisplayHeadlight();
    }
  }
}

// Função responsável pelo controle do ar condicionado
// Chamada a cada ciclo
void updateAC() {
  // Armazena o ciclo onde essa função vai poder ser chamada novamente
  static uint32_t disabledUntil = 0;
  bool ACButton = !digitalRead(ACBUTTONPIN);

  if(ACButton) {
    if(disabledUntil < cycle) {
      disabledUntil = cycle + 500; // Desabilitado por 5 segundos

      // Inverte e mostra no display a informação correspondente
      ACon = !ACon;
      lcd.setCursor(11, 3);
      ACon ? lcd.print("   Ligado") : lcd.print("Desligado");
    }
    else if(disabledUntil - cycle < 400) {
      // Caso botão tenha sido pressionado e a função ainda estiver desabilitada mostra erro
      // Tem um periodo onde isso não funciona pois, senão, o led de erro liga mesmo que não era pra ter erro
      startError(5);
    }
  }
}

// Função responsável por atualizar o display com a informação da proximidade
// Chamada apenas quando há mudança no valor
void updateDisplayProximity() {
  // Calcula quantos espacos vazios terão
  // fmin serve para garantir que nada saia do controle quando a distancia for muito grande
  // d >= 50:      [     ]
  // 50 > d >= 40: [#    ]
  // 40 > d >= 30: [##   ]
  // 30 > d >= 20: [###  ]
  // 20 > d >= 10: [#### ]
  // 10 > d >= 0:  [#####]
  uint8_t espacos = floorf(fmin(distance, 50) / 10);
  uint8_t cursorX = 14; // Cursor no primerio espaço para percorrer os outros 5 e ir preenchedo-os conforme o valor de distancia

  // Percorre os espaços preenchendo com #
  for(;cursorX < 19 - espacos; cursorX++) {
    lcd.setCursor(cursorX, 1);
    lcd.print("#");
  }

  // Percorre os espaços restantes preenchendo com espaços vazios
  for(;cursorX < 19; cursorX++) {
    lcd.setCursor(cursorX, 1);
    lcd.print(" ");
  }
}

// Função responsável por calcular a distância
// Chamada a cada 50 ciclos
void updateProximity() {
  // Armazena o ciclo onde essa função vai poder ser chamada novamente
  static uint32_t disabledUntil = 0;

  if(disabledUntil < cycle) {
    digitalWrite(TRIGPIN, HIGH); // Enviando ondas sonoros
    delayMicroseconds(10); // Espera um pouco
    digitalWrite(TRIGPIN, LOW); // Para

    // Calcula a distancia baseado no tempo em que o echo foi acionado, velocidade do som e divide por dois para compensar ida e volta do som
    distance = (pulseIn(ECHOPIN, HIGH) * 0.0343) / 2;

    updateDisplayProximity();

    disabledUntil = cycle + 50; // Desabilitado por 500ms
  }
}

// Esta função tenta desligar o carro
// É chamada a cada 100 ciclos
void turnEngineOff() {
  // Armazena o ciclo onde essa função vai poder ser chamada novamente
  static uint32_t disabledUntil = 0;

  if(disabledUntil < cycle) {
    disabledUntil = cycle + 100; // Desabilitado por 1 segundo

    // Só desliga o motor quando estiver parado e a chave na posição certa
    if(keyValue < ENGINE) {
      // Mostrar erro se o carro estiver andando
      if(speed != 0) {
        startError(100);

        return;
      }

      // Limpa parcialmente o display
      lcd.setCursor(12, 0);
      lcd.print("        ");
      lcd.setCursor(13, 1);
      lcd.print("       ");
      lcd.setCursor(11, 3);
      lcd.print("         ");

      carState = 1;
    }
  }
}

// Esta função tenta desligar o sistema
// É chamada a cada 100 ciclos
void turnSystemOff() {
  // Armazena o ciclo onde essa função vai poder ser chamada novamente
  static uint32_t disabledUntil = 0;

  if(disabledUntil < cycle) {
    disabledUntil = cycle + 100; // Desabilitado por 1 segundo

    // Só desliga se a chave estiver na posição certa
    if(keyValue < SYSTEM) {
      // Desliga farois e display
      digitalWrite(SMALLLEDPIN, LOW);
      digitalWrite(BIGLEDPIN, LOW);
      lcd.clear();
      lcd.noBacklight();

      // Desliga a buzina
      analogWrite(BUZZERPIN, 0);

      headlightState = 0;
      carState = 0;
    }
  }
}

// Função responsável por atualizar o carro a cada ciclo
void run() {
  updateSpeed();
  updateHeadlight();
  updateAC();
  updateProximity();

  // Tenta desligar o carro
  turnEngineOff();
}

// Função responsável por enviar o sinal de erro para o led dedicado
// Recebe a duração para versatilidade de aplicação
void startError(uint8_t duration) {
  digitalWrite(ERRORLEDPIN, HIGH);
  showErrorUntil = cycle + duration;
}

// Função responsável por checar se o led de erro está ativo e tentar desligá-lo 
void endError() {
  if(showErrorUntil > 0 && showErrorUntil < cycle) {
    digitalWrite(ERRORLEDPIN, LOW);
    showErrorUntil = 0;
  }
}

void setup() {
  // Inicializando variáveis
  cycle = 0;
  carState = 0;
  speed = 0;
  headlightState = 0;
  showErrorUntil = 0;
  ACon = false;

  // Configurando display
  lcd.init();

  // Configurando pinos digitais
  pinMode(SMALLLEDPIN, OUTPUT);
  pinMode(BIGLEDPIN, OUTPUT);
  pinMode(TRIGPIN, OUTPUT);
  pinMode(ERRORLEDPIN, OUTPUT);
  pinMode(ECHOPIN, INPUT);
  pinMode(HEADLIGHTBUTTONPIN, INPUT_PULLUP);
  pinMode(ACBUTTONPIN, INPUT_PULLUP);

  // Inicializando pinos digitais
  digitalWrite(SMALLLEDPIN, LOW);
  digitalWrite(BIGLEDPIN, LOW);
  digitalWrite(TRIGPIN, LOW);
  analogWrite(BUZZERPIN, 0);
}

void loop() {
  // Lê o valor da chave
  keyValue = analogRead(KEYPIN);

  // Máquina de estados geral do carro
  switch(carState) {
    case 0: startSystem(); break;
    case 1: startEngine(); break;
    case 2: run();
  }

  // Tenta desligar o led de erro
  endError();

  // Contagem do ciclo
  delay(CYCLETIME);
  cycle++;
}
