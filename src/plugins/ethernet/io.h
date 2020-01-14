#ifndef SIMPLE_RPC_ETHERNET_IO_H_
#define SIMPLE_RPC_ETHERNET_IO_H_

#include <Arduino.h>
#include <Ethernet.h>

class EthernetIO {
  public:
    EthernetIO(void) {}
    void begin(EthernetServer&);
    size_t available(void),
           read(byte*, size_t),
           write(byte*, size_t);
  private:
    EthernetServer* _es;
    EthernetClient* _ec;
};

#endif
