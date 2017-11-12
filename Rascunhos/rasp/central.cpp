
#include <RF24Mesh/RF24Mesh.h>
#include <RF24/RF24.h>
#include <RF24Network/RF24Network.h>
#include "pacote.c"

//RF24 radio(<ce_pin>, <a>*10+<b>);	  /dev/spidev<a>.<b>
RF24 radio(24,0);
RF24Network network(radio);
RF24Mesh mesh(radio,network);



int main(int argc, char** argv) {

  // Set the nodeID to 0 for the master node
  mesh.setNodeID(0);
  // Connect to the mesh
  printf("start\n");
  mesh.begin();
  radio.printDetails();

while(1)
{

  // Call network.update as usual to keep the network updated
  mesh.update();

  // In addition, keep the 'DHCP service' running on the master node so addresses will
  // be assigned to the sensor nodes
  mesh.DHCP();


  // Check for incoming data from the sensors
  while(network.available()){
//    printf("rcv\n");
    RF24NetworkHeader header;
    network.peek(header);
    pacote_t pacote;

    switch(header.type){
      // Display the incoming millis() values from the sensor nodes
      case 'M': network.read(header,&pacote,sizeof(pacote));
                printf("Pacote recebido do alimentador %u from 0%o\n",pacote.alimentadorID,header.from_node);
                 break;
      default:  network.read(header,0,0);
                printf("Rcv bad type %d from 0%o\n",header.type,header.from_node);
                break;
    }
  }
delay(2);
  }
return 0;
}




