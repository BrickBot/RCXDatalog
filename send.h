/*
 *  send.c
 *
 *  A program to communicate with an RCX.
 *
 *  Under IRIX, Linux, and Solaris, you should be able to compile this
 *  program with cc send.c -o send.  I don't know about other versions of
 *  Unix, although I'd be interested in hearing about compatibility issues
 *  that you are able to fix.
 *
 *  Set DEFAULTTTY to the serial device you want to use.
 *  Set the RCXTTY environment variable to override DEFAULTTTY.
 *
 *  Some additional documentation is available at:
 *
 *     http://graphics.stanford.edu/~kekoa/rcx/tools.html
 *
 *  Acknowledgements:
 *
 *     Ray Kelm sent word that send.c compiles successfully under Linux,
 *        and he passed on info about the names of the serial devices.
 *
 *     Laurent Demailly ran this through lint, and suggested some changes,
 *        including a printf bug fix.  He also pointed out some behavior
 *        that prompted me to increase the number of retries in the send
 *        code.  He also pointed out that this program compiles fine under
 *        Solaris.
 *
 *     Other people have used the ideas in this program (and Paul Haas's
 *        Perl script) to write similar programs in other languages.  More
 *        information is available at http://www.crynwr.com/lego-robotics/.
 */

/*  Copyright (C) 1998, Kekoa Proudfoot.  All Rights Reserved.
 *
 *  License to copy, use, and modify this software is granted provided that
 *  this notice is retained in any copies of any part of this software.
 *
 *  The author makes no guarantee that this software will compile or
 *  function correctly.  Also, if you use this software, you do so at your
 *  own risk.
 * 
 *  Kekoa Proudfoot
 *  kekoa@graphics.stanford.edu
 *  10/3/98
 */

/* C++-interface written by Roeland Merks, (c) 2000 */
/* Roeland Merks, roel@science.uva.nl */
#ifndef _SEND_H_
#define _SEND_H_

#define LINUX
#ifdef LINUX
#define DEFAULTTTY   "/dev/ttyS1" /* Linux - COM1 */
#else
#define DEFAULTTTY   "/dev/ttyd2" /* IRIX - second serial port */
#endif

#define RCX_BUFFERSIZE 8192
#define RETRIES      5

#include <iostream>

namespace RCXError {
 
  class RCXError {

  public:
    virtual const char* error_str(void) const {
      return "RCXSend:: Unknown communication error";
    }
  
    virtual void debug_print() const {
      cerr << "RCXSend:: Unknown communication error" << "\n";
    }
    
  };  
  
  class BadLink : public RCXError {

  public:
    virtual const char* error_str(void) const {
      return "RCXSend:: Bad link";
    }
    
    virtual void debug_print() const {
      cerr << "RCXSend:: Bad link" << "\n";
    }
  };
  
  class BadResponse : public RCXError {
    
  public:
    virtual const char* error_str(void) const {
      return "RCXSend:: Bad response";
    }


    virtual void debug_print() const {
      cerr << "RCXSend:: Bad response" << "\n";
    }
    
  };
  
  class NoResponse : public RCXError {

  public:
    virtual const char* error_str(void) const {
      return "RCXSend:: No response";
    }

    virtual void debug_print() const {
      cerr << "RCXSend:: No response" << "\n";
    }
    
  };
  
  class ResponseTooLarge : public RCXError {
    
  public:
    virtual const char* error_str(void) const {
      return "RCXSend:: Response too large.";
    }

    virtual void debug_print() const {
      cerr << "RCXSend:: Response too large." << "\n";
    }

  };
  
  class SerialPortError {
    
    // Error with setting up the connection with the serial port
  public:
      virtual const char* error_str(void) const {
	return "Unknown error with serial port setup";
      }
      
      virtual void debug_print() const {
	cerr << "Unknown error with serial port setup\n";
      }
  };
  
  class TTYOpenError : public SerialPortError {
   
      
  };
  
  class NotATTYError : public SerialPortError {


  };

  
}

class RCXSend {

 public:
  RCXSend();
  ~RCXSend();
  void hexdump(int len);
  
 protected:
  virtual void Send(const char *commandstring);
  int len;
  unsigned char recvbuf[RCX_BUFFERSIZE];
  void CheckError(void);
  int error_status;
  
 private:
  static bool toggle8;
  static unsigned int initialisedP;
  void Open(void);
  void Init(char *tty);
  void Close(void);
  int Send(unsigned char *sbuf, int slen, unsigned char *rbuf, int rlen);
  
  unsigned char ToggleBit3(unsigned char mess_byte);
 
  // datamembers
  static int fd;
  static unsigned char sendbuf[RCX_BUFFERSIZE];
  
};


#endif
