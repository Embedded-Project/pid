int a[5];
int last_error = 0;

int motor_right = 15;
int motor_left = 2;

int maxSpeed = 300;
int minSpeed = 100;

int integral = 0;
int expected = 2;

int mode = 0;

int readline();
void PID();
void set_motors(int pid);

void move(int val) {
  analogWrite(motor_right, 300 + val);
  analogWrite(motor_left, 300 - val);
}

void setup() {
  pinMode(motor_right, OUTPUT); // noi chan 1A, moto 1 ben trai
  pinMode(16, OUTPUT); // noi chan 2A
  pinMode(0, OUTPUT); // noi chan 3A, moto2, ben phai
  pinMode(motor_left, OUTPUT); // noi chan 4A.
  pinMode(14, INPUT);
  pinMode(12, INPUT);
  pinMode(13, INPUT);
  pinMode(5, INPUT);
  pinMode(4, INPUT);

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

  if(position == 10) {
    move(0);
    return;
  }

  error = ((int)position - expected); // 0, 1, 2, 3, 4
    
  derivative = error - last_error;
  integral = integral + error;

  last_error = error;

  Kp = 200; 
  Ki = 0;
  Kd = 0;

  power_difference = error*Kp + integral*Ki + derivative*Kd;

  move(power_difference);

  readline();
}

int readline() {
  a[0] = digitalRead(14);
  a[1] = digitalRead(12);
  a[2] = digitalRead(13);
  a[3] = digitalRead(5);
  a[4] = digitalRead(4);

  bool blackspace = a[0] == 0 && a[1] == 0 && a[2] == 0 && a[3] == 0 && a[4] == 0;
  bool whitespace = a[0] == 1 && a[1] == 1 && a[2] == 1 && a[3] == 1 && a[4] == 1;
  if(blackspace || whitespace) {
    return 10;
  }

  if(a[0] == a[4]) {
    mode = a[0];
  }

  for(int i = 0; i < 5; i++) {
    if(a[i] != mode) {
      return i;
    }
  }

  return 10;
}
