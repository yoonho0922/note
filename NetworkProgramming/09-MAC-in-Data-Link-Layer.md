## Data Link Layer

* reliable (error-free) link 제공이 목적
  * link : 네트워크에서 노드간의 연결
* hop-to-hop 통신을 보장
* 2계층 헤더는 한 서브넷(LAN) 안에서 유효
  * 서브넷 안에 목적지 노드에 전달하면 목적을 완수
  * 라우터가 전달 받은 패킷의 2계층 헤더를 제거
  *  IP 패킷을 보고 목적지를 확인하여 2계층 헤더를 붙힘 - 라우팅

Duties

* Logical Link Control sublayer
  * framing, physical addressing, flow control error control
* Medium Access control

## Medium Access Control

Collision을 막거나 감지하기위한 제어

Collision은 곧 data loss

**Wireless Medium**

무선 환경 특징

1. decreased signal strength - 거리에 따른 시그널 감쇠
2. interference from other source - 다른 시그널의 간섭 (노이즈)
3. multipath propagation - 직진파와 반사파 사이의 시간차로 인한 훼손

distnace에 따른 시그널 감쇠의 영향

* 직접 통신 가능
  * Trasmission range
    * 성공적으로 통신이 되는 영역
* 통신 불가
  * Detection range
    * 시그널의 존재는 파악 but 성공적인 복구 불가한 영역
  * Interference range
    * 복구 불가 + 다른 통신을 방해하는 영역

### Random Access Control

* 각 스테이션은 중앙제어자가 따로 없이 접근 권한을 갖음

* 충돌 발생 많음

* 전송하는 호스트가 매우 적은 경우에 사용가능

* MA -> CSMA -> CSMA/CD, CSMA/CA

#### ALOHA (Multiple Access)

* 각 스테이션이 아무때나 시그널을 보냄
* 모든 에러는 collision에 의한 것이라 가정 
* collision을 detect
  * back-off algorithm - ACK를 기다림
* 한계
  * 충돌 감지가 상위 계층에서 감지됨
  * 전송 성공 비율이 매우 낮음

#### CSMA

* Carrier Sense Multiple Access
* 시그널을 보내기 전에 다른 station이 시그널을 보내고 있는지 확인
  * propagation delay 때문에 완전히 보장하지는 못함
* 한계
  * 충돌 가능성을 줄일 순 있지만 전파 지연 때문에 없앨 순 없음
  * sender가 충돌이 일어난지 알 수 없음 - time out이 될 때까지 기다려야함

#### CSMA/CD

* CSMA + Collision Detect
* 충돌을 일으킨 sender가 충돌을 감지함
  * 충돌을 전자공학적(시그널 강도의 변화)으로 감지하여 다른 스테이션들에게 충돌을 알림
  * sender가 ack를 기다리지 않고 바로 back-off 하게 함
* 무선 환경에선 충돌을 감지할 수 없음

#### CSMA/CA

* CSMA + Collision Avoidance
* Found idle이 되면 IFS + CW 만큼 기다렸다가 시그널을 보냄
  * Found idle : carrier가 감지되지 않을 때 (다른 스테이션이 시그널을 보내지 않을 때)
  * IFS(inter frame space) : 우선 순위에 영향을 받음 (짧으면 우선순위가 높은 것)
  * Contention Window : 랜덤값으로 지정
* IFS 중 carrier가 감지되면 reset (IFS 전으로가서 carrier sense)
* CW 중 carrier가 감지되면 남은 CW가 지난 다음 시그널을 보냄

### Controlled Access

접근 권한을 가진 station만 시그널을 보낼 수 있음

접근 권한을 결정하는 방식 3가지

#### Reservation

* 예약 프레임에 예약정보를 넣음
* 예약한 station만 시그널을 보냄
* 한계
  * 예약 프레임에 station을 추가/제거가 어려움
  * 동기화가 중요함 -> 치명적 한계

#### polling

* 중앙제어자 역할인 Primary station이 다른 station에 발언권(polling)을 줌
* primary to other station
  * SEL -> ACK -> DATA -> ACK
* other station to all station
  * Poll -> NAK (보낼 데이터가 없음)
  * Poll -> DATA -> ACK
  * DATA의 destination에 따라 other station 혹은 primary station
* 한계
  * other station에서 먼저 요청을 할 수 없다 (기다리는 것 밖엔...)
  * primary station의 overhead

#### token

* 중앙 제어자 없이 station 끼리 token(발언권)을 돌려가며 발언
* 한계 :  토큰이 loss되면 치명적임



**Bridge & Switch**

* CSMA/CD을 사용하는 2계층 장비
* 스위치/브릿지를 사이에둔 station 끼리는 collision이 나지 않음

### Channelized Access

물리적으로 채널을 나눔

* FDMA
  * 한채널의 대역폭을 나눠서 station에 할당
* TDMA 
  * 시간을 슬롯 단위로 시간대 별로 나눠 통신
* CDMA
  * 내가받은 데이터에 내 코드를 곱해서 전달 -> D*C
  * 모든 스테이션의 D*C를 더한 시그널을 주고 받음
  * 코드를 통해 특정 스테이션이 보낸  데이터를 복구할 수 있음

