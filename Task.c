#include "mcp9808.h"
#include "stm32f0xx_hal.h"
#include <i2c.h>
#include <init.h>


int main(void)
{
  HAL_init()
    
  I2C_HandleTypeDef hi2c1
  HAL_I2C_Master_Transmit(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout); 

  HAL_I2C_Master_Receive(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout); 

  /* Private variables ---------------------------------------------------------*/ 
  unsigned char buffer[5];  
  unsigned int rawT; 
  float Temperature;

  HAL_Delay(15);  
  buffer[0]=0x01; //Pointer buffer  
  buffer[1]=0; //MSB byte  
  buffer[2]=0; //LSB byte  
  HAL_I2C_Master_Transmit(&hi2c1,0x18<<1,buffer,3,100);  

   //Trigger Temperature measurement 
  buffer[0]=0x00;  
  HAL_I2C_Master_Transmit(&hi2c1,0x18<<1,buffer,1,100);  
  HAL_Delay(20);  
  HAL_I2C_Master_Receive(&hi2c1,0x18<<1,buffer,2,100);  
  //receive 2 bytes, store into buffer[0] and buffer[1]
  //buffer[0] : MSB data 
  //buffer[1] : LSB data 
  rawT = buffer[0]<<8 | buffer[1]; //combine 2 8-bit into 1 16bit  
  Temperature = ((float)rawT/65536)*165.0 -40.0; 
}

  
 



