/*
 * AddressBook.cpp + AddressBook.h
 *
 *  Created on: 14 de dez de 2015
 *      Author: Davi
 */
#include <Arduino.h>
class AddressBook{
  public:
  char *address;
  char *rssi;
  short thisSize;
  AddressBook(short _size) {
    address = new char[thisSize];
    rssi = new char [thisSize];
    thisSize = _size;
    for (int i=0;i<thisSize;i++)
    {
      address[i]=0;
      rssi[i]=0;
    }
  }
  
  char getAddressValue(int _pos){
    return  address[_pos];
  }
  
  char getRssiValue(int _pos){
    return rssi[_pos];
  }
  bool insert(char _from,char _rssi){
    for(int i=0;i<thisSize;i++)
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
    sort();
    return true;
  }
  bool sort(){
    for(int x=0; x<thisSize; x++)
    {
      for(int y=0; y<thisSize-1; y++)
      {
        if((rssi[y]>rssi[y+1])&&(rssi[y+1]>0))
        {
          int temp = rssi[y+1];
          rssi[y+1] = rssi[y];
          rssi[y] = temp;
          int temp2 = address[y+1];
          address[y+1] = address[y];
          address[y] = temp2;
        }
      }
    }
    return true;
  }
  
  ~AddressBook() {
    delete address;
    delete rssi;
  }
};
