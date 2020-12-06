### Client/Server model

* Client asks (request) - Server provides (response)
* 클라이언트는 서버의 IP주소와 port number를 알아야함
* socket address = IP + port number

## Socket

* process와 transport를 연결하는 인터페이스
* Multiplexing / Demultiplexing at transport layser
  * Multiplexing (at sender) : handle data from multiple sockets, add transport header
  * Demultiplexing (at receiver): use header info to deliver recieved segment to correct socket

### Socket types

* Stream sockets (for TCP)
  * connection-oriented
  * data with no boundaries
  * bidirectional, reliable, sequenced, unduplicated(중복되지 않는)
* Datagram sockets (for UDP)
  * basically connectionless
  * data with boundaries

* Raw sockets (for ICMP)

### Connectionless demultiplexing

* UDP/IP packets with same destination port number, but different source socket adresses will be directed to same socket at destination
* source socket address를 통해 applicaiton에서 이를 구분

### Connection-oriented demux

* one socket per TCP connection
* TCP socket idenfied by '4-tuple'
  * source socket address
  * destination socket address
* transport 계층에서 구분해줌
* connection 과정
  * Client가 Listening socket에 연결 요청 (3-way handshaking)
  * 서버의 Connection socket과 연결되어 데이터 교환

### Client+server : connectionless (UDP)

![image-20201204115029457](C:\Users\yoonho\AppData\Roaming\Typora\typora-user-images\image-20201204115029457.png)

* sendto(), recvfrom() : 매번 socket address를 명시해야 함

### Client+server : connection-oriented (TCP)

![image-20201204114928198](C:\Users\yoonho\AppData\Roaming\Typora\typora-user-images\image-20201204114928198.png)

* connect() : client의 socket address 할당, 포트는 private port number 중 랜덤 할당