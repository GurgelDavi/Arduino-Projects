#include <Arduino.h>
class AddressBook
{
  public:   //public otherwise error: test::test private
    uint8_t *address;
    uint8_t *rssi;
    short thisSize;
    AddressBook(short _size) {
    uint8_t* _address=(uint8_t *)malloc(sizeof(uint8_t)*_size);
    uint8_t* _rssi=(uint8_t *)malloc(sizeof(uint8_t)*_size);
    address = _address;
    rssi = _rssi;
    thisSize = _size;
    clearList();
  }
  void clearList(){
  
    for (int i=0;i<thisSize;i++)
      {
        address[i]=0;
        rssi[i]=0;
      }
  }
  
  char getAddressValue(short _pos){
    return  address[_pos];
  }
  
  char getRssiValue(short _pos){
    return rssi[_pos];
  }
  bool insert(short _from,short _rssi){
    for(short i=0;i<thisSize;i++)
    {
      if ((_from==address[i])||(address[i]==0))
      {
        address[i] = _from;
        rssi[i]=_rssi;
        sort();
        return true;
      }
    }
    address[thisSize-1]=_from;
    rssi[thisSize-1]=_rssi;
    //sort();
    return true;
  }
  bool sort(){
    for(short x=0; x<thisSize; x++)
    {
      for(short y=0; y<thisSize-1; y++)
      {
        if((rssi[y]>rssi[y+1])&&(rssi[y+1]>0))
        {
          short temp = rssi[y+1];
          rssi[y+1] = rssi[y];
          rssi[y] = temp;
          short temp2 = address[y+1];
          address[y+1] = address[y];
          address[y] = temp2;
        }
      }
    }
    return true;
  }
  ~AddressBook() {
    free(address);
    free(rssi);
  }
}; // undocumented semicolon otherwise error:
