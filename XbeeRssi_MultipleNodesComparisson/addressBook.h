#ifndef addressBook
#define addressBook
class addressBook {
  char address[16];
  char rssi[16];
  void sort()
  {
    for(int x=0; x<n; x++)
    {
      for(int y=0; y<n-1; y++)
      {
        if(rssi[y]>rssi[y+1])
        {
          int temp = rssi[y+1];
          int temp2 = address[y+1];
          rssi[y+1] = rssi[y];
          address[y+1] = address[y];
          rssi[y] = temp;
          address[y] = address;
        }
      }
    }
  }
  int nearestNode()
  {
    return (uint8_t)address[0]; 
  }
}

