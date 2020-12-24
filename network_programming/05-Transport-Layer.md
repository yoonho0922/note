### UDP - user datagram protocol

* UDP
  * best effort service
    * lost
    * out-of-order
  * connectionless
    * no handshaking
    * UDP segment handled independently of others
  * UDP used in
    * streaming multimedia apps
    * DNS, SNMP
  * UDP를 사용할 경우 응용 계층에서 보증을 해줘야함
* UDP check sum
  * 전체 segment를 16bit 단위의 시퀀스로 봄
  * 시퀀스를 모두 더함 -> checksum
  * receiver는 checksum 값과 segment를 비교하여 에러를 검출

### TCP - transmission congest protocol

* Basic Mechanisms for Reliable Data Transfer
  * Sequence Number : for sequential numbering of packets
  * Checksum : to detect bit errors in a transmitted packet
  * Acknowledgement : to tell the sender that a packet or set of packets ahs been received correctly
  * Timer : to timeout, retransmit a packet
* TCP
  * point-to-point
  * full duplex data : 통신 이중 연결
  * reliable, in-order byte stream : packet 순서 뒤바뀔 일 없음
  * flow controlled : reciever가 overflow하지 않도록
  * congestion controlled : network에서 overflow 되지 않도록
  * connection-oriendted
* TCP flag
  * (URG)
  * ACK
  * PSH
    * sender가 받을 경우 : 버퍼에 있는 데이터를 즉시 모두 보낼 것
    * receiver가 받을 경우 : 버퍼에 있는 데이터를 app에 모두 보낼 것
  * RST : reset the connection
  * SYN : sequential number 동기화
  * FIN

* Connection management

  * 2-way handshake의 문제

    * 연결이 지연되거나 끊겼을 경우 리소스가 낭비될 수 있음
* 3-way handshake를 사용

