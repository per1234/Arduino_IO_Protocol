import processing.serial.*;

final int BAUD = 115200;
final int PORT = 0;

Serial myPort;  // Create object from Serial class
int iop_state;
int iop_val;


void IOP_setup() 
{
  println(Serial.list());
  String portName = Serial.list()[PORT];
  myPort = new Serial(this, portName, BAUD);
  iop_state = 0;
}

// for now it will only read the first analog value received
boolean IOP_check() {
  while (myPort.available () > 0) {
    char inByte = myPort.readChar();
    print(inByte);
    switch (inByte) {
    case ']':
      iop_state = 1;
      iop_val = 0;
      break;
    case ',':
      if (iop_state == 1) {
        iop_state = 2;
        return true;
      }
      break;
      default:
      if (iop_state == 1) {
        iop_val = iop_val*10+(inByte-'0');
      }      
    }
  }
  return false;
}

int iop_read() {
  iop_state = 0;
  return iop_val;
}

