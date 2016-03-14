#ifndef JY901_h
#define JY901_h
#include <stdint.h>

class CJY901 
{
  public: 
	
	CJY901(); 										//构造函数
	void     startIIC(uint8_t address = 0x50);		    //设定0x50地址的IIC初始化
	bool     copeSerialData(uint8_t data);			//处理接收的数据
	void     readData(uint8_t address,					//address地址
					  uint8_t length,					//长度length
					   int8_t data[]);				//手动读取ucLength长度的数据
	uint16_t getTime(char*);				//获取时间，'Y'年，'M'月，'D'天，'h'时，'m'分，'s'秒，'l'毫秒
	double 	 getAcc(char*);				//获取加速度
	double 	 getGyro(char*);				//获取角速度
	double 	 getAngle(char*);				//获取角度
	double 	 getMag(char*);				//获取磁场
	uint32_t getPressure(void);				//获取压力
	uint32_t getAltitude(void);				//获取高度	
	uint16_t getDStatus(char*);			//获取端口输出	
	uint32_t getLon(void);				//获取经度
	uint32_t getLat(void);				//获取纬度
	double 	 getGPSV(char*);				//获取地速
	
  private: 
	uint8_t _address;
	bool    _transferMode;
	void readRegisters(uint8_t deviceAddr,uint8_t addressToRead, uint8_t bytesToRead, int8_t * dest);
	void writeRegister(uint8_t deviceAddr,uint8_t addressToWrite,uint8_t bytesToRead, int8_t *dataToWrite);
	struct
	{		
		struct 
		{
			uint8_t  year       :8;
			uint8_t  month      :8;
			uint8_t  day        :8;
			uint8_t  hour       :8;
			uint8_t  minute 	:8;
			uint8_t  second     :8;
			uint16_t milisecond :16;
		}time;
		struct
		{
			uint16_t x 			 :16;
			uint16_t y 			 :16;
			uint16_t z 			 :16;
			uint16_t temperature :16;
		}acc;
		struct
		{
			uint16_t x	         :16;
			uint16_t y           :16;
			uint16_t z 			 :16;
			uint16_t temperature :16;
		}gyro;
		struct
		{
			uint16_t x 			 :16;
			uint16_t y 			 :16;
			uint16_t z 			 :16;
			uint16_t temperature :16;
		}angle;
		struct
		{
			uint16_t x 			 :16;
			uint16_t y 			 :16;
			uint16_t z 			 :16;
			uint16_t temperature :16;
		}mag;
		struct
		{
			uint16_t d_0 :16;
			uint16_t d_1 :16;
			uint16_t d_2 :16;
			uint16_t d_3 :16;
		}dStatus;
		int32_t pressure;
		int32_t altitude;
		int32_t lon;
		int32_t lat;
		struct
		{
			uint16_t GPSHeight   :16;
			uint16_t GPSYaw 	 :16;
			int32_t  GPSVelocity :32;
		}GPSV;
	}JY901_data;
};
extern CJY901 JY901;
#endif
