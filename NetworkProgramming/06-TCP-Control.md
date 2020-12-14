## TCP Error Control

* transmission delay : 패킷을 싣는 시간
* propagation delay :  하나의 패킷이 목적지에 도달하는 시간

### Stop-and-Wait ARQ

* 기본적으로 리시버가 ACK를 통해 다음에 기대되는 패킷을 샌더에게 알려줌
* 샌더가 보내는 프레임이 loss될 경우
  * 리시버가 ACK를 보내지 않음
  * time out이 되면 sender가 ACK가 오징지 않은 패킷을 보냄
* ACK 패킷이 loss될 경우
  * 샌더가 time out 되고 같은 패킷을 다시 보냄
  * 리시버는 identifier로 같은 패킷임을 확인하고 받지 않음
    * 여기서 identifier는 0과1로 최소한의 구분만 함
*  에러가 있다고 말하지 않는 이유
  * 에러가난 패킷을 정확히 알기 힘들기 때문
* 한계
  * ACK가 올때까지 기다리기 때문에 전송시간이 너무 오래걸림

### Go-Back-N ARQ

* Stop-and-Wait ARQ에서 pinpelining 방식이 더해진 방법
  * ACK를 받기전에도 다음 패킷을 보냄
* identifier를 늘림으로써 가능 (0, 1,  2, 3, 4, ...)
* cumulative ACK 방식
  * 앞의 ACK가 loss되고 다음 ACK를 보냈을 때 다음 ACK가 앞의 ACK를 포함한다.
* 윈도우 사이즈가  2^m (리시버 버퍼 사이즈) 보다 작은 이유
  * 최악의 경우 (모든 ACK가 loss될 때) identifier가 동일해서 잘못된 정보를 받을 수 있음
* 한계 : 리시버는 앞의 세그먼트가 로스되면 뒤에오는 세그먼트를 받지 않음
  * 샌더는 time 아웃 된 것 부터 이미 보낸 것까지 다시 다 보냄 :  Go-back

### TCP Error control

* Go-back-N ARQ과 공통점

  * time-out 방식으로 loss를 검출
  * 샌더가 time out이 날 경우 해당 패킷 부터 다시 보냄
  * does not use NACK
  * ACKS are cumulative

* Go-back-N ARQ과 차이점

  * 리시버가 로스된 패킷의 자리를 비워두고 다음에 오는 패킷들을 버리지 않고 받음
    * byte 단위의 sequence number의 사용을 통해
  * send/receiver 윈도우가 가변적임

* TCP time out 시간의 결정 : 추정된 RTT + 여유분

  * RTT : 패킷을 보내고 ACK가 돌아오기 까지의 시간
  * RTT 추정 : 각각의 RTT를 추정하고 weigthed average를 구함

* duplicate ACK (NACK과 같은 역할)

  * 리시버가 기대하지 않는 패킷이 올 때마다 duplicate ACK을 보냄
  * sender가 duplicate ACK을 3번 받을 경우 - 3 duplicate ACK
    * time out이 되기 전에 해당 패킷이 loss 됐다고 생각하고 해당 패킷부터 다시 보냄

   

## TCP Window Control

* trassmission rate : TCP window size에 비례

### summary

* Flow control
  * 리시버가 오버로드 되는 것을 방지
  * 리시버에 의해 조절됨
  * rwnd : receive window (샌더에게 rwnd 값을 알려줌)
* Congestion control
  * 네트워크 congestion을 방지
  * sender에 의해 조절 됨
  * Infer available network capacity
  * cwnd : contgestion window
* TCP window = min(cwnd, rwnd) : 실제로 TCP가 사용하는 window는 하나

### Flow Control

* 리시버가 오버로드 되지 않도록 rwnd의 결정
* rwnd : 리시버가 가용한 버퍼의 크기
* rwnd는 리시버의 버퍼보다 작게 결정됨
* sender는 세그먼트를 한번에 rwnd보다 적게 보냄
* TCP 헤더의 windowsize 필드 = rwnd

## TCP congestion control

* 샌더는 네트워크 혼잡을 감지하고 cwnd를 조절한다
* 혼잡 감지 방법
  * 패킷 로스 : 로스가 발생하면 네트워크 혼잡이라 간주
    *  로스는 중계기의 큐잉 딜레이 등 다른 이유 때문에 나타나기도 하지만 네트워크 혼잡때문이라고 간주
    * 실제로 사용하는 방법은 로스 밖에 없음
  * 딜레이 : 딜레이가 길어질 경우 혼잡으로
    * 딜레이가 길다는 기준을 잡기 힘들기 때문에 사용하기 힘든 방법
  * Explicit Marks : 중계기가 알려주는 방법
    * TCP는 end-to-end  프로토콜이기 때문에 사용하기 힘든 방법
* cwnd 조절 알고리즘
  * Tahoe, Reno, ...

### Congestion control의 필요성

*  인터넷의 특징 statistical multiplexing
  * 여러개의 input을 하나의 input으로 내보낼 때 input에 들어오는 순서대로 내보내는 것
  *   평균 input의 속도가 output의 속도를 넘지 않아야함
* short-term congestion : 중계기의 버퍼를 늘리는 것으로 해결 가능
* long-term congestion : 네트워크 속도의 조절로만 해결 가능
* loss가 발생할경우 그에 대한 재전송을 해야함
  * 재전송하면 더 많은 패킷을 보내고, 거치는 모든 중계기에 영향을 줌
  * 연쇄 반응으로 congestion이 걷잡을 수 없이 커짐

### Congestion Control Algorithm

* Original concept
  * cwnd를 RTT마다 1씩 증가시킴
  * loss가 발생하면 cwnd를 반으로 줄임
    * time out or 3 dup ACK
  * 문제점 : 혼잡을 없애기에 cwnd를 반으로 줄이는 거 가지곤 부족함
* TCP Tahoe
  * loss가 발생하면 cwnd를 1로 줄임
  * threshold : 현재 cwnd의 반
  * cwnd < threshold
    * Slow Start : cwnd를 지수적으로 증가시킴 (하나의 ACK당 하나의 패킷을 추가)
  * cwnd > threshold 
    * cwnd를 1씩 증가시킴
  * 문제점 : loss 발생 원인의 구분이 없음

* TCP Reno
  * 3 dup ACK : sender가 보낸 많은 ACK 중 하나가 Loss 됨
    * 3 dup ACK 이면 cwnd를 반으로 줄임
  * time out : 모든 패킷이 Loss된 심각한 상황
    * time out ehlaus cwnd를 반으로 줄임

