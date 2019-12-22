int a[5];
int last_error = 0;

int maxSpeed = 1000;
int minSpeed = 200;

int integral = 0;

int readline();
void PID();
void set_motors(int pid);

void setup() {
  pinMode(15, OUTPUT);
  pinMode(16, OUTPUT);
  pinMode(0, OUTPUT);
  pinMode(2, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  PID();
}

void PID() {
  int i;      // Control function
  int power_difference = 0;
  float Kp, Ki, Kd;
  unsigned int position;
  int derivative, error;

  position = readline();

  error = ((int)position - 2); // 0, 1, 2, 3, 4
    
  derivative = error - last_error;
  integral = integral + error;

  last_error = error;

  Kp = 50; 
  Ki = 0;
  Kd = 0;

  power_difference = error*Kp + integral*Ki + derivative*Kd;

  if(power_difference > maxSpeed)
    power_difference = maxSpeed;
    
  if(power_difference < - maxSpeed)
    power_difference = (-1 * maxSpeed);

  set_motors(power_difference);

  readline();
}

void set_motors(int pid) {
  analogWrite(15, 400 + pid);
  digitalWrite(16, 0);
  analogWrite(2, 400 - pid);
  digitalWrite(0, 0);
}

int readline() {
  a[0] = digitalRead(5);
  a[1] = digitalRead(6);
  a[2] = digitalRead(7);
  a[3] = digitalRead(20);
  a[4] = digitalRead(19);

  int index = 0;
  for(int i = 0; i < 5; i++) {
    index = i;
    if(a[i] == 0) {
      break;
    }
  }

  return index;
}
