### Layer 4 - Transport Layer Address

* process-to-process
* 전송계층에서 주소 - port number
* port number의 종류
  * Well-known port : 자주 사용되는 특정 Application에 할당된 포트 넘버
  * Registered port : IANA에서 관리하는 포트 넘버, 주로 기관에서 요청하여 할당 받음
  * Dynamic/Private port : Client가 자유롭게 사용할 수 있는 포트 넘버

### Layer 5 - Application Layer Address

* URL
* Host name

### DNS - Domain Name System

* 5계층에서 에서 주소를 바탕으로 4계층과 3계층에서의 전송
  * 4계층의 경우 서비스의 종류에 따라 포트 넘버가 정해져 있어서 큰 어려움은 없음
  * 3계층의 경우는 IP 주소를 알아내야함, 이를 위한 것이 DNS
  
* Domain Name System
  * URL이나 호스트명은 사용자 컴퓨터의 'hosts' 파일에서 IP 주소를 검색하여 사용
  * hosts 파일에 존재하지 않는 URL이나 호스트명은 DNS를 통해 IP주소로 변환
  
* Domain name space
  * 역 트리 형태의 최대 128 level의 계층적 구조
  * Domain name space의 subtree로 Domain을 정의
  
* Root와 TLD
  * 도메인은 트리 형태로 구성됨
  * Root를 제외한 모든 level에는 라벨이 있음
  * Root 바로 아래 level의 노드는 TLD-top level domain 로 com, org, kr, jp 등이 있다.
  
* Name Server (DNS Server)
  * DNS에는 각 domain을 대표하는 Name Sever가 존재
  * Name Server는 세단계의 계층구조로 나눌 수 있음
  * Root DNS Server - (TLD) DNS Server - Authoritative DNS Server
  
* Root DNS Server
  * 대륙, 나라 단위로 존재하며 전세계에 13개가 존재
  * 물리적으론 더 많은 서버가 있지만 이들을 통합하여 관리
  
* TLD Server & Authoritative Server
  * TLD Server - 해당하는 Authoritative Server의 정보를 관리
  * Authoritative Server
  
* Local DNS Server (default name server)
  * 계층에 속하지않는 서버
  * 호스트의 DNS 쿼리 요청을 받는 서버
  * 호스트가 요청한 도메인의 IP 주소를 넘겨줌
  * Host <-> Local DNS Server <-> DNS
  
* DNS caching, updates records

  * 모든 DNS 서버는 매핑한 것을 기록해 둠 (캐싱)
  * 이는 일정 시간이 지나면 지움

* DNS resource records

  * RR format : (name, value, type, ttl)
  * type A : name = hostname, value = IP address
  * type NS : name = domain, value = hostname of authoritative name server
  * type CNAME : name = alias name(별칭), value = canonical name(실제)
  * (type MX : value는 name의 메일서버 이름)

  