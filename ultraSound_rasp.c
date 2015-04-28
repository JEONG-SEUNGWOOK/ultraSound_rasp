# ultraSound_rasp
In raspberry-PI, running ultraSound(SR04)

#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int trig = 23;	//송신부 pin num
	int echo = 24;	//수신부 pin num
	int start_time, end_time; //송신 시간, 수신 시간
	float distance; //장애물과 떨어진 거리

	if (wiringPiSetup() == -1) exit(1); //WiringPi 셋업이 정상적으로 이루어지는지 확인하는 부분

	pinMode(trig, OUTPUT);  //trig(송신) 핀 - 23번
	pinMode(echo, INPUT);	//echo(수신) 핀 - 24번

	while (1) {
		digitalWrite(trig, LOW);	//LOW : 0V , HIGH : 5V
		delayMicroseconds(10);
		digitalWrite(trig, HIGH);	//trig에서 10μs동안 초음파 발생
		delayMicroseconds(10);
		digitalWrite(trig, LOW);	//초음파 발생하기 전후로, 잡음을 제거하기 위하여 전류를 보내지 않도록 설정
		while (digitalRead(echo) == 0); //조건부 대기상태, 부하를 덜어주는 코드
		start_time = micros();		//시간단위 μs
		while (digitalRead(echo) == 1); //
		end_time = micros();
		distance = (end_time - start_time) / 29. / 2.;  // 초음파의 속도는 29마이크로초 당 1센치(340m/s)를 이동
		printf("distance %.2f cm \n", distance);		//거리값 출력
	}
	return 0;
}
