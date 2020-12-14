## Layered Model

### OSI Model

* Application
* Presentation
* Session
* Transport
* Network
* Data link
* Physical

각 계층에서 헤더를 붙여서 (possibly trailer) encapsulation / decapsulation

### Application Layer

* message를 생성

### Presentation Layer

* bitstream으로 변형

### Session Layer

* session을 관리

보통 하나의 application이 3개의 계층을 모두 관리

### Transport Layer

* Process (or port) addressing
* Segmentation and reassemble of a message
  * a process : 실행 중인 프로그램, 실존하는 객체(하나의 인스턴스)
  * process-to-process delivery
  * segmentation : session에서 받은 큰 데이터를 분할
  * reassemble : segment들을 합침

* optional duties
  * Connection control : communication 링크 연결 유지
  * Flow control : receiver가 overflow하지 않도록
    * receiver가 감당하지 못할 정도의 데이터를 보내지 않도록 조절
  * Congestion control : network가 overflow하지 않도록
  * Error control : 전달된 bitstream에 오류가 없는지 확인

### Network Layer

* host-to-host delivery
* Duties : Logical addressing and routing

### Data Link Layer

* reliable(error-free) link 제공이 목적
* Framing : 패킷을 프레임으로, bitstream을 프레임 단위로 나눠 symbolize
* Physical addressing : 데이터 링크에서 사용하는 address
* Flow control : 리시버가 overflow되는 걸 막음
* Error control
* Access control : 동시에 들어오는 데이터에 대해 충돌나지 않도록 제어
* hop-to-hop delivery

### Physical Layer

* 물리적 매체를 통해 bitstream을 보내는 것이 목적

### TCP/IP

OSI 7계층을 묶어 더 간단하게 규정

* Application Layer
  * SMTP, FTP, HTTP, DNS, SNMP, TELNET, ...
* Transport Layer
  * SCTP, TCP, UDP
* Network Layer
  * IP
* Host-to-network (Physical and Data Link Layer)

## Addressing

### Phyiscal Address

* MAC 주소
* 공장에서 기계에 일련번호를 할당. (공장마다 할당된 일련번호가 있음)

* LAN에 모든 physical address 는 달라야함

 ### Logical Address

* IP 주소

* 멀리 있는 상대방을 구별하는 방법
* 중간에 바뀌지 않음
* 위치 기반으로 IP 할당

### Port Address

### Specific Address

* application 내의 고유 주소
* ex) 이메일, 웹주소