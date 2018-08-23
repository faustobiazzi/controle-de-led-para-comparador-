int ligado = 0;
int lightson =0;
int direction = 0;
int botao1 =0;
int botao2 =0;
int botao3 =0;
int botao4 =0;
int carrossel = 0;

int modo = 0;


void setup()
{
  Serial.begin(9600);
  //inputs
  pinMode(13, INPUT);//ligar
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  
  //outputs
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  
}


void controleDIR(){
  direction = analogRead(A1);
  if (direction <= 168 ){
    carrossel = 0;
  }
  if (direction > 168 && direction  < 336){
    carrossel = 1;
  } 
  if (direction >= 336 && direction  < 504){
    carrossel = 2;
  }
  if (direction >= 504 && direction  < 672){
    carrossel = 3;
  }
 
}

void fullLED(){
	while(modo==0){
		digitalWrite(8, HIGH);
		digitalWrite(9, HIGH);
		digitalWrite(10, HIGH);
		digitalWrite(11, HIGH);
		Serial.println("full");
		verificaModo();
	}
}

void halfLED(){
	while (modo ==1){
      	 verificaModo();
		 direction = analogRead(A1);
		 controleDIR();
         Serial.println(direction);
		 if (carrossel == 0){
			turnOFF();
			digitalWrite(8, HIGH);
			digitalWrite(10, HIGH); 
            Serial.println("pin 8 e 10");
			
		  }else{
			if (carrossel == 1){
				turnOFF();
				digitalWrite(8, HIGH);
				digitalWrite(9, HIGH);
              	Serial.println("pin 8 e 9");
				
			}
			else{
			  if (carrossel == 2){
					turnOFF();
					digitalWrite(9, HIGH);
					digitalWrite(11, HIGH);
                    Serial.println("pin 9 e 11");
			  }else{
				if (carrossel == 3){
					turnOFF();
					digitalWrite(10, HIGH);
					digitalWrite(11, HIGH);
                    Serial.println("pin 10 e 11");
				}else{
				  if (carrossel >3)
				  {
					  carrossel = 0;
				  }
				}
				}
			}
		 }
		 verificaModo();
	}
}

void onesection(){
	while (modo ==2){
		 
		 verificaModo();
		 
		 controleDIR();
         Serial.println(direction);
		 if (carrossel == 0){
			turnOFF();
			digitalWrite(8, HIGH);		
            Serial.println("pin 8");
		  }else{
			if (carrossel == 1){
				turnOFF();	
				digitalWrite(9, HIGH);
                Serial.println("pin 9");
			}
			else{
			  if (carrossel == 2){
					turnOFF();
					digitalWrite(11, HIGH);
                	Serial.println("pin 11");
			  }else{
				if (carrossel == 3){
					turnOFF();
					digitalWrite(10, HIGH);
                  	Serial.println("pin 10");
				}else{
				  if (carrossel >3)
				  {
					  carrossel = 0;
				  }
				}
				}
			}
		 }
	}
}

void alternate(){
	while (modo ==3){
		verificaModo();
		controleDIR();
        Serial.println(direction);
		if (carrossel == 0 || carrossel == 1){
			turnOFF();
			digitalWrite(8, HIGH);
			digitalWrite(11, HIGH); 
          	Serial.println("pin 8 e 11");
			
		 }else{
			if (carrossel == 3 || carrossel == 2 ){
				turnOFF();
				digitalWrite(9, HIGH);
				digitalWrite(10, HIGH);
				Serial.println("pin 9 e 10");
			}
		
		}
	} 
	
}


void turnOFF(){
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
}

void verificaModo(){
	botao1 = digitalRead(2);
    botao2 = digitalRead(3);
    botao3 = digitalRead(4);
    botao4 = digitalRead(5);
	
	if (botao1 == HIGH) {
		modo = 0;
		fullLED();
	}
    if (botao2 == HIGH) {
		modo = 1;
		halfLED();
    } 
	if (botao3 == HIGH) {
		modo = 2;
		onesection();
    }
	if (botao4 == HIGH){
		modo = 3;
		alternate();
	}
}

void loop()
{
  ligado = digitalRead(13);
  if (ligado != 0){
    controleDIR();
    verificaModo();
  }else{
	  turnOFF();
  } 
 }
