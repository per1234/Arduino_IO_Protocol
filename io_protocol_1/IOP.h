/**
 * IOP: IO Protocol - An Arduino library to read and write values to
 * the digital and analog ports
 * 
 * Copyright (C) 2014 Mauricio Jabur
 * 
 * 
 * Version 20140528
 *  * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this library.  If not, see <http://www.gnu.org/licenses/>.
 */


#ifndef IOP_h
#define IOP_h

#if defined(WIRING) && WIRING >= 100
#include <Wiring.h>
#elif defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif
#include <string.h>
#include <Stream.h>

// Uncomment the next line to run the library in debug mode (verbose messages)
//#define IOP_DEBUG 

class IOP : 
public Print{
public:
  IOP(Stream *stream = &Serial);// Constructor

  size_t write(uint8_t val);// provide method for printing

  void setStream(Stream *stream);  // Change the Stream object

  inline void comment();
  void sendAnalog(int first = 0, int count = 1); // send the values of n=count analog ports


  // private: // commented out during development
  Stream *_stream;
  char _delim[7]; // null-terminated list of character to be used as delimiters for tokenizing (default " ")

  void header(char type, int first, int count);
  void footer();
};

//////////////////////////////////////////////////////////
// IOP.cpp
//////////////////////////////////////////////////////////

//#include "IOP.h"

/**
 * Constructor makes sure some things are set.
 */
IOP::IOP(Stream *stream)
: 
_stream(stream)
{
  strcpy(_delim, "[],;"); 
}

/**
 * forward all writes to the encapsulated "port" Stream object
 */
size_t IOP::write(uint8_t val) {
  return _stream->write(val);
}

/**
 * start the comment line
 */
inline void IOP::comment(){
  _stream->print("// ");
}

/**
 * send the values of n=count analog ports
 */
void IOP::sendAnalog(int first, int count){  
  header('A', first, count);

#ifdef IOP_DEBUG
  long t = micros();
#endif

  _stream->print(analogRead(A0 + first));
  int index = 1;
  while (index++ < count) {
    _stream->print(_delim[2]);
    _stream->print(analogRead(A0 + first + index));
  }
  footer();

#ifdef IOP_DEBUG
  t = micros()-t;
  comment();
  _stream->print("micros to read inputs: ");
  _stream->println (t);
#endif
}

void IOP::header(char type, int first, int count){
  _stream->print((char)type);
  _stream->print(first);
  _stream->print(_delim[0]);
  _stream->print(count);
  _stream->print(_delim[1]);

}

void IOP::footer(){
  _stream->print(_delim[3]);
  _stream->println();
}
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
#endif //IOP_h

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////



