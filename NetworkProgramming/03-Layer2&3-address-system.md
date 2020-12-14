### 주소체계가 다른 이유

* 각 계층별 주소의 역할이 다르기 때문
  * 2계층은 좁은 지역 내에서 상대적으로 한정적인 수의 장비간 데이터 전달
  * 3계층은 지리적으로 광범위한 인터넷에서 특정 지역으로 전달

### ARP

* 데이터가 전달되어야 할 목적지 장비의 3계층 주소를 가지고 있는 중계 장비가 2계층의 서비스를 이용하려면 해당 목적지의 2계층 주소를 알아야함
* 3계층 주소를 가지고 2계층 주소를 알아내는 것이 ARP의 주요기능

### 2계층 주소 (MAC)

* 특징
  * 좁은 지역(LAN)에서 한정적인 수의 장비간 데이터 전달이 목적
  * 위치적 특성 없음
  * 인터페이스 제조업체에서 할당, 고정값으로 계속 사용
  * 제조사의 고유번호 + 제조사가 할당하는 식별 번호
* frame 전달
  * LAN (bus topology) - 하나의 host가 보내는 frame은 모든 다른 host에 전달됨 (broadcast)
  * 전달 받은 host는 DA를 바탕으로 수신 여부 결정
* unicast / multicast address - 첫번째 byte를 확인
  * 첫번째 byte의 LSB가 짝수 : unicast
  * 첫번째 byte의 LSB가 홀수 : multicast
  * 모든 bit가 1 (FF:FF:FF:FF:FF:FF) : broadcast
  * 첫번째 byte의 LSB가 가장 먼저 전송된다 -> 신속하게 unicast, broadcast를 파악하고 대비하기 위해

### 3계층 주소 (IP)

* 특징
  * 광범위한 인터넷의 임의의 지점까지 경로를 찾아서 특정 위치까지 전달이 목적
  * 앞에가 같은 주소 -> 비슷한 지역 (주소가 위치적 특성을 갖는다)
  * 인터페이스의 물리적 위치에 따라 가변적으로 할당
    * IANA(국제 IP주소 관리) -> 대륙별 IP 주소 관리 기관 -> 각국 IP 주소 관리 기관 -> ISP->개인 또는 기업
  * 하나의 IP 주소는 같은 시간에 다른 인터페이스에 할당 될 수 없음 - Global uniqueness
  * 시간에 따라 인터페이스의 IP 주소가 달라질 수 있음 - Dynamic assignment
* IP address Class (현재는 class 기반 아님)
  * 첫 네 bit를 이용하여 전체 주소 공간을 나눔
  * 0, 10, 110, 1110, 1111 : A, B, C, D
  * 클래스에서 블록 단위로 주소를 나눌 수 있음
    * 이 블록을 기관이나 회사에 할당
* neitid와 hostid
  * net id의 mask : A - /8, B - /16, C - /24
  * 주소와 mask를 AND 연산 하여 netid 도출
* Classless subnetting 
  * netid 가변적 사용
  * 클래스 구분 X
  * prefix의 길이로 block 크기 유추
  * 첫 주소는 network block 전체를 가리키는 주소
  * 마지막 주소는 network 내 broadcast를 위한 주소

### NAT

* private address (사설)
  * IP 주소의 전역 유일성(global uniqueness)이 항상 필요하지는 않다는 생각
  * 네트워크 내부에서 TCP/IP로 통신하는 경우 굳이 공인된 IP 주소가 필요 없음
  * 10.0.0.0, 172.16.00, 192.168.0.0이 있음
* Network Address translation
  * 사설 IP를 할당받은 호스트가 외부와 통신할 때 사설 IP를 공인 IP로 변환 해줌
  * NAT기능을 가진 라우터가 이를 수행
  * port number를 달리 사용하여 사설IP를 더 늘리기도 함 (약간의 편법)