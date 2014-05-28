/*
 */

int max_r = 1024;

int STEP = 3;

int low_alarm = 100;
boolean alarm = false;


import processing.serial.*;

color[] line = {
  color(255, 40, 40), 
  color(0, 255, 0), 
  color(80, 80, 255),
};

float[] old= {
  0,
};


void setup() {
  size(1024, 768);
  IOP_setup();
  for (int i = 0; i<old.length; i++) {
    old[i] = iop_read();
  }
  text("", 0, 0);
  background(0);
  draw_alarm();
}
int x = 0;
void draw() {
  if (IOP_check()) {
    for (int i = 0; i<old.length; i++) {
      float reading = (iop_read()+old[i])/2; //running average
      alarm =  (reading <= low_alarm);

      stroke(line[i]);
      line(x, to_screen(old[i]), x+STEP, to_screen(reading));
      old[i] = reading;
    }
    x += STEP;
    if (x>width) {
      x=0;
      fill(0, 180);
      noStroke();
      rect(0, 00, width, height);
      draw_alarm();
    }
  }

  if (alarm) {
    stroke(255, 0, 0);
    fill(255, 0, 0);
    rect (0, 0, width, 40);
    textSize(30);
    fill(0);
    text ("DETECTADO", 35, 32);
  } else {
    stroke(0, 255, 0);
    fill(0, 0, 0);
    rect (0, 0, width, 40);
  }
}

void draw_alarm() {
  float tmp = to_screen(low_alarm);
  stroke(111,111,222);
  line(0,tmp,width,tmp);
}

float to_screen(float value) {
  return  (int)map(value, 0, max_r, height-1, 40);
}

