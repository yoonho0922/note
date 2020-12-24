### Netowrk layer functions

* packetizing
  * source에서 payload를 네트워크 계층 패킷으로 encapsulating
  * destination에서 네트워크 계층 패킷을 decapsulating하여 payload를 얻음
  * soure에서 destination까지 payload를 변경하거나 사용하지 않고 전송
* routing and forwarding
  * forwarding : 패킷을 라우터의 인풋에서 적절한 아우풋으로 옮김
  * routing : source부터 destination 까지의 패킷의 경로를 결정하는 것
  * 라우팅 알고리즘에 의해 forwarding table 결정, 이를 통해 forwarding

## Routing algorithms overview

* key question : source와 destination 간의 leaset-cost 경로가 무엇인가
* routing algorithm : to find that least-cost path

### Routing algorithm classfication

global or decentralized

* global(centralized)
  * 라우터가 모든 노드들의 정보를 알고있음
  * "link state" algorithms
* decentralized
  * 라우터가 물리적으로 연결된 neighbor 노드의 정보만 알고있음
  * "distance vetor" algorithms

static or dynamic

* static
  * 네트워크의 변화가 거의 없을 겨우
* dynamic 
  * 네트워크의 변화가 많을 경우 (대부분의 네트워크)

### Algorithms

##### Link-State Routing Algorithm

* Dijkstra's algorithm

* 모든 노드까지의 최단 경로를 저장
* net topology & link costs are known to all nodes
* computes least cost path from one node to all nodes

##### distance-vector Algorithm

* Bellman-ford equation : calculate the shortest path from neighbor information

* distance-vector : node X 까지 가는 최단 경로와 cost
* node X의 neighbor가 자신의 distance-vector를 알려줌
* node X는 이를 바탕으로 자신의 최단 경로 선택, distance-vector 갱신
* neighbor간 정보 교환으로 distance-vector를 계속 갱신

##### Path-vector Algorithm

* cost를 무시하고 갈 수 있는 지만 고려
* initial state
  * 자신과 1차적으로 연결된 노드들만 vector에 저장
* updating path vectors
  * 자신과 연결된 노드의 path-vector도 고려하여 자신의 path-vector를 갱신

### Internet structure

* Inter-AS
  * 광범위의 네트워크 (나라간, 대륙간)
  * Intra-AS들을 연결
  * uses Path-vector Algorithm
* Intra-AS
  * 상대적으로 범위가 작은 네트워크(나라 안의)
  * uses Link-State Routing Algorithm,  distance-vector Algorithm

## Internet Protocol Overview

### IP service

* IP provides an unreliable, connectionless, "best effort" service
* best effort (UDP와 같이 보장은 못하고 효율을 중시함)
* 상위 계층에서 패킷 손실이나 중복을 다뤄야함
* IP supports the following services
  * unicast (one-to-one)
  * broadcast (one-to-all)
    * The local(limited) broadcast : 내가 속한 network의 모든 노드
    * the directed brodadcast address : 특정 서브넷에 속한 모드 노드
  * multicast (one-to-several)
* TTL : 라우터를 거칠 때 마다 1씩 감소하며, 네트워크에서 routing loop를 방지

### Maximum Transmission Unit

* MTU : IP 패킷의 최대 크기

* IP 패킷이 Ethernet frame에서 encapsulate할 수있는 MTU를 벗어난 경우 패킷을 분할함
  * 라우터 등에서 발생
* IP fragmentation, reassembly
  * end-host에서만 reassemble할 수 있음
* reassembly에서 사용되는 IP 헤더 필드
  * total length (in bytes) : 분할 전 패킷의 총 길이
  * identification : 분할된 패킷은 모두 같은 identification을 갖음
  * Flags
    * DF (Don't fragment : 이 패킷은 fragment하면 안됨, MTU가 너무 작다면 해당 패킷을 삭제할 것
    * MF (More fragment) : 이 패킷은 fragment이고, 뒤에 추가적인 fragment들이 있음
  * Fragment offset : 최초 시작점에서 얼마나 떨어진 곳에서 fragment 됐는지
    * fragment의 order 파악 가능

## DHCP

Dynamic Host Configuration Protocol

호스트에 IP 주소를 할당하는 방법

장점

* iP주소를 필요할 때마다 할당 받음
* 수동적인 IP 설정을 하지 않아도 됨
* 무선 환경을 지원함

BOOTP의 확장

* 부팅할 때 ip 주소를 포함하여 다양한 정보를 가져오는 프로토콜

과정

* hosts broadcasts "DHCP discover" msg
  * DHCP 서버를 브로드캐스트로 찾음
* DHCP server responds with "DHCP offer" msg
  * 서버가 요청에 응답하고 자신의 주소와 할당가능한 IP주소를 알려줌
* host requests IP address : "DHCP request" msg
  * 서버에게 받은 할당 가능한 IP 주소로 할당을 요청함
* DHCP server sends address "DHCP ack" msg
  * IP 주소를 할당해주고 요청에 대한 응답



주소 블록을 서브넷에 할당하는 방법

* Networks gets allocated portion of its provider ISP's addr space
* ISP가 할당한 블록을 서브넷마스크를 늘려서 나눈다. -> 서브넷팅



ISP가 IP 블록을 할당 받는 방법

* 국제 기관에서 수동으로 할당

## ICMP

Internet Control Message Protocol

what happens if

* 라우터가 패킷을 버렸을 때
* TTL이 끝났을 때
* Host가 모든 fragment를 받지 못 했을 때

ICMP는 상위 계층의 메시지를 포함하지 않는다.

* Network Layer 부터 encapsulation

ICMP Type field

* Error reporting
  * 3 : Destination Unreachable (ureachable한 이유는 code 필드로 명시)
  * ...
* Query
  * 8/0 : Echo request or reply
  * ...

Content of data field for error messages

* 에러를 알리는 패킷의 경우 추가로 필드를 가짐
  * 에러난 패킷의 IP 헤더와 에러난 패킷의 payload(TCP/UDP)의 앞 8byte
    * 앞 8byte는 port number와 sequence number를 가짐

ICMP는 4바이트를 고정 필드로 갖고 용도에 따라 추가필드를 다르게 함

* Echo-request and echo-reply
  * ping에서 사용되는 패킷
  * 추가로 Identifier와 Sequence number를 가짐
* source-quench (참고)
  * destinatino host 또는 라우터에서 congestion이 발생할 경우 보내는 패킷
  * Layer 3에서의 flow&congestion control 이지만 자주 사용하지는 않음
* Redirection with ICMP (참고)
  * IP 패킷을 받은 라우터가 source에게 목적지를 다시 알려줄 때 보내는 패킷

 Traceroute  and ICMP

* UDP 세그먼트의 TTL을 1부터 하나씩 늘려가서 목적지에 도달할 때 까지 거치는 라우터들을 알아냄
* 각 라우터는 Time exceeded error 패킷을 source에게 보냄
* end-host에서는 unreachable port number를 설정하여  에러 패킷을 유도함
  * 최근 윈도우에서는 end-host에 ICMP 패킷을 보내 echo(ping) 통신을 함

