## Internet의 구조

### What's the Internet

* Internet : 네트워크의 네트워크 (network of network)
  * ISP(Internet Service Providers, 통신사업자)를 연결
* protocol : 통신 규칙
* Infrastructure : application을 서비스

### Internet infrastructure

* end devices (hosts)
  * 인터넷에 가장 마지막 단에 붙어있는 장치
  * PC, 스마트폰, 서버, ...
* communication links (연결)
  * 광섬유, 구리선, 무선, 인공위성, ...
* packet switches (중계기, forward packets)
  * Router, Switch

### network structure

* access network
  * 호스트가 있는 네트워크
  * 홈 네트워크, 모바일 네트워크, 기업 네트워크, ...
* network core
  * 중계기로 구성된 네트워크

## Internet의 원리

### Packet switching

sharing에 유리한 방식

* transmission delay : 벽돌을 올리는 시간

* propagation delay : 벽돌이 전달되는 시간

* store-and-forward : 패킷이 완전히 저장된 후에 송신을 시작함

##### 전송할 수 있는 양보다 더 많은 양의 데이터가 들어올 때

* queuing delay : 전송대기줄이 발생하는 것

* queuing loss : 큐잉 딜레이 될 때 수신 되는 패킷을 드랍하는 것

### Delay componets in a node

1. 트랜스미션 딜레이
2. 전파 지연
3. 큐잉 딜레이
4. 프로세싱 딜레이 : 패킷을 어디로 보낼지 결정하는 시간

d(nodal) = d(proc) + d(queue) + d(trans) + d(prop)

### Throughput : reciever sender 전송 속도

trasmission rate : 패킷을 올리는 속도

### Two key network-core function

* routing : 목적지에 따라 경로를 결정하는 것
* forwarding : 패킷을 실제로 보내는 행위

## Circuit switching 

패킷 스위칭의 alternative

* 데이터를 패킷 단위로 나누지 않음
* 경로를 독점함

* call : 독점한 경로(회선)
* 장점 : 딜레이가 적고 퀄리티가 높음
* 단점 : 동시 사용성이 떨어짐

### FDM vs TDM (Circuit switching)

하나의 링크를 n분의 1로 나눠서 할당

##### FDM

* Frequency를 bandwidth로 나눔
* 전자기파에 관한 내용..

##### TDM

* 전체 시간을 슬롯으로 나누고 이를 프레임으로 묶음
* 슬롯마다 할당된 사람이 다름
* 주기적으로 슬롯에 해당하는 사람에게 데이터 전송





