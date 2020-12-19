## Scheduling

보다 효율적인 자원의 활용을 위해 어떤 작업을 메모리에 올리고 어떤 작업에게 자원을 할당 해야하는 지 결정

* CPU-burst : CPU 자원을 많이 요구하는 작업
* I/O-burst : I/O 사용이 많은 작업
* Non-preemptive : 프로세스가 스스로 자원을 반납하는 방식
* Preemptive : 프로세스가 스스로 자원을 반납하기 전에 강제로 회수할 수 있는 방식

* 스케줄링 알고리즘 성능 판단 기준
  * CPU Utilization - cpu를 최대한 바쁘게
  * Throughput - 시가 단위안에 실행이 완료되는 프로세스의 수
  * Turnaround Time - 하나의 프로세스가 시작에서 종료까지 걸리는 시간
  * Waiting Time - 하나의 프로세스가 레디큐에서 기다린 총 시간
  * Response Time - 프로세스가 첫 아웃풋을 내는데 걸리는 시간

### 스케줄링 알고리즘

* 하나의 ready Queue 이용하는 방식
  * FCFS (First-Come, First-Served)
    * convoy effect : 실행시간이 긴 작업이 먼저 오게 됨에 따라 전체적인 waiting time이 증가하는 것
  * SJF (Shortest-Job-First) : cpu-busrt time이 적은 프로세스부터 수행
    * cpu burst time 을 예측할 수 있어야함 (불가능)
  * Prriority Scheduling
    * starvation : 우선순위가 계속 밀려 cpu를 할당 받지 못하는 상태
    * aging : 오래기다린 작업의 우선순위를 올려주는 것
  * RR (Round Robin) : 시간을 나눠 할당
* 다수의 ready queue를 사용하는 방식
  * Multilevel Queue
    * 각 큐에 용 도에 맞는 작업이 들어감, 한번 큐가 배정되면 바뀌지 않음
    * 각 큐에는 서로다른 스케줄링 알고리즘
    * 각 큐의 우선순위에 따라 수행 -> starvation 문제 -> aging
  * Multilevel feedback Queue
    * 큐를 옮겨다닐 수 있음

### 다중 처리기 스케줄링

* Asymmetric multiprocessing : 하나의 프로세서만 시스템 자료 구조에 접근할 수 있음
* Symmetric multiprocessing(SMP)
  * 각각의 프로세서가 공통의 데이터 구조에 접근하고 그를 업데이트함
  * 대부분의 멀티프로세서 스케줄링에 쓰임
* load balancing : 모든 프로세서에 workload가 고루 분배되도록 함
  * push migration : 외부에서 주기적으로 프로세스의 로드를 확인하고 고루 분배
  * pull migration : 한가한 프로세서가 바쁜 프로세서에서 대기 중일 일을 당겨옴
* Multicore Processors
  * memory stall : 메모리에 접근하여 기다리는 동안 프로세서가 계산을 멈춰 낭비됨
  * simultaneous multithreading (SMT) : memory stall의 해결

### 실시간  CPU  스케줄링

* soft real-time system  : 우선순위가 높은 프로세스가 먼저 실행되도록 보장
* hard real-time system : 각 task가 반드시 정해진 deadline 안으로 작업이 끝나는 것을 보장
* 스케줄링은 각 프로세스의 latency를 줄이기 위함
  * latency : 어떤 이벤트가 발생하고 그에 맞는 서비스가 수행되기 까지의 시간
    * Interupt latency : 인터럽트가 발생하고 ISR이 시작되기 까지의 지연시간
    * Dispatch Latency : dispatcher가 하나의 프로세스를 block하고 다른 프로세스를 시작하기 까지의 지연 시간
* Priority-Based Scheduling
* Rate Montonic Scheduling
* Earlist Deadline First Scheduling

### 알고리즘 평가

* deterministic evaluation :  미리 정해놓은 workload를 통해 성능 측정
* queueing models : 프로세스의 도착시간, cpu와 I/O 버스트 들을 확률적인 분포로 기술
* little's formula : 큐 사이즈길이 = (평균 도착시간) X (평균 대기시간)

## Synchronization

* Shared data : 여러 프로세스들이 공유하는 데이터 (Critical data)
* Critical section (임계구역): 공유 데이터를 접근하는 고드 영역
* Mutual exclusion : 둘 이상의 프로세스가 동시에 임계구역에 진입하는 것을 막는것
* 임계 구역 문제
  * 누가 먼저 공유데이터에 접근?
  * 공유 데이터에 누가 접근하고 있는지?
  * 공유 데이터를 어떤 순서로 접근할지?
* 솔루션
  1. Mutual Exclusion - 쓰고있으면 다른 프로세스는 못 들어옴
  2. Progress - 누군가 기다린다면, 대기 시간이 무한이되면 안됨
  3. Bounded Waiting - 임계 구역 진입 횟수를 제한하여 독점하지 못하도록

### Peterson's Solution

* sw 수준
  * two process solution (다중 프로세스에서 보장 X)
  * turn : 차례가 된 프로세스, flag : 준비가 되었는지
  * turn과 flag는 서로 다른 프로세스를 가리킴
  * 다중 프로세서 보장 X, 할당 받기 전에 무한루프를 돎 (busy-waiting 비효율적)

### 동기화를 위한 하드웨어 지원

* locking : 내가 진입하는 임계구역에 lock을 걸어 다른 프로세스가 못 들어오게
* test_and_set(TAS)
* acquire lock (잠금), release lock(해제)
* lock이 true면 접근 못함.
* 다중 프로세서 보장 X, 할당 받기 전에 무한루프를 돎 (busy-waiting 비효율적)
* 누가 대기하고 있는지 알 수 없음 (bounded-waiting 미충족)
  * 해결 : cmpare_and_swap

### 뮤텍스락과 세마포어

* Mutex Locks
  * OS에서 하는 lock
  * acquire(), release()
  * 멀티프로세서에서 유용함
    * Context switching을 하지않아도 됨 ( 정보를 갖고있는 채로 spinlcok 하며 기다리기 때문)
* Semaphores
  * binary semaphore : mutex lock과 같음
  * counting semaphore :  유한한 개수를 가진 자원 에 대한 접근 제어
    * 자원을 반납(signal)하면 +1, 사용하면(wait) -1
  * wait와 signal 을 같은 S에 대해 동시에 수행하지 않는 것을 보장해야함

### 모니터

* 프로그래밍 언어 수준
  * 이전의 내용들은 다른 프로세스 간 동기화, 모니터는 한프로세스에서 스레드 간 동기화임

## Deadlocks

### 교착 상태

* 프로세스나 스레드가 결코 일어날 수 없는 특정 이벤트를 기타리는 것
* 대부분의 교착 상태는 전용 자원을 차지하려는 경쟁에서 발생
* 순환 대기는 교착 상태에 있는 시스템의 특징
* 교착 상태 성립 조건
  * 상호 배제 조건 : 자원은 한 번에 한 프로세스에서만 배타적으로 점유
  * 대기 조건  : 자원을 최소 1개 갖고있으면서 다른 자원을 기다리는 상태
  * 비선점 조건 : 시스템이 프로세스의 제어를 빼앗을 수 없음
  * 순환 대기 조건
    * 두 프로세스 이상이 순환 고리 상태
    * 각 프로세스는 고리 안에 있는 다음 프로세스가 점유하고 있는 자원을 대기

### 교착 상태 해결책

* 교착 상태 방지
  * 대기 조건 거부
    * 자원을 요청할 땐 어느 자원도 소유하고 있지 않아야함
    * 단점 : 자원의 낭비
  * 비선점 조건 거부
    * 하나 이상의 자원을 소유하고 있고 다른 프로세스가 소유한 다른 자원을 요청한다면
    * 소유하고 있는 모든 자원을 반납하게 함
    * 단점 : 프로세스가 재 시작 되어야하는 추가적인 부하
  * 순환 대기 조건 거부
    * 자원에 대한 선형 순서 사용 (프로세스가 자원을 돌아가면서 사용)
    * 단점 : 자원의 요구에 대해 동적이거나 유연하지 못함

* 교착 상태 회피
* 교착 상태 탐지
  * 순환 대기 존재 여부에 초점
  * 실행 시 심각한 부담을 줌
  * 자원 할당 그래프 소거
    * 실행을 완료할 수 있는 그래프가 있는지 확인
    * 자원 요청을 허용할 수 있다면 그래프 소거
    * 그래프가 모든 ㅡ로세스에 대해 소거될 수 있으면 교착 상태 없음

* 교착 상태 복구
  * 일시정지/재시작 메커니즘
  * 체크 포인트/롤백

## Main memory

* 프로세스의 메모리 공간 보호
  *  base register & limit register
  * BR <= 프로세스가 접근할 수 있는 공간 <= BR + LR
* Address binding : 프로그램의 논리 주소를 실제 메모리의 물리 주소로 매핑
  * Compile time
  * Load time
  * Execution time
* 프로세스가 메모리에 올라간 이후
  * Dynamic Loading : 프로그램의 모든 모듈을 올리지 않고 필요하면 올려주는 방식
  * Dynamic Linking : 프로세스 실행 시 같은 라이브러리가 메모리에 올라가는 것을 방지
    * 라이브러리 최초 필요시 해당 라이브러리의 메모리 공간 확보
    * 다른 프로세스가 해당 라이브러리를 필요할 경우 stub 포인트로 참조
  * Swapping : 메모리의 올라간 프로세스를 잠시 디스크에 저장했다가 다시 올리는 방식
    * 메모리 공간이 부족시 사용
    * swap-in : 메모리에 다시 할당되는 것, swap-out : 디스크로 빠지게되는 것

### 연속 메모리 할당

* multiple-partition allocation : hole이 생길때까지 잠시 대기
* hole 탐색하는 방법
  * First-fit : 찾으면 일단 넣음
  * Best-fit : 있는 것 중 제일 작은 것에 넣음 (효율성 중시)
  * Worst-fit : 제일  넉넉한 것에 넣음
* Fragmentation
  * External fragmentation : 프로세스를 넣을 남은 메모리가 충분하지만, 연속되지 않음
    * compaction을 통한 해결 but overhead가 크고 압축 과정에서 또 frag를 생성함
  * Internal fragmentation : partition(할당된 메모리)의 크기가 프로세스보다 큼

### 불연속 메모리 할당 - Paging 

물리적 메모리를 고정된 크기의 블록으로 나눔 -> frames

논리적 메모리를 고정된 크기의 블록으로 나눔 -> pages

page table을 이용해 page와 frame을 매핑

Internal fragmentation 문제

TLB를 통해 page table 접근을 빠르게

* CPU가 TLB에 먼저 접근하여 page address를 확인
  * 있으면 바로 물리 주소에 접근
  * 없으면 page table에 접근

Memory protection

* 연속 할당에서는  base/limit register를 통해 프로세스 메모리 보호
* 불연속 할당에서는 page table에 protection bit을 이용 (valid-invalid)

Shared pages

* Shared code (I/O 프로세스 등)
* Private code and data

### Page Table 구조

page table도 큰 연속적인 메모리가 되어서 page table을 나누고 접근하는 방법

* Hierarchical page table
  * Two-levle page Table
  * 64bit에는 부적합
* Hashed page table
  * 해시 함수를 통해 테이블에 바로 접근하여 물리주소를 찾음
  * 해시 테이블에 접근 후엔 chaining 방식으로
* Inverted page table
  * 페이지 주소(논리) -> 프레임 주소(물리) 가 아닌 프레임 주소를 기준으로 테이블을 할당
  * 메모리 활용 효율성이 좋지만, 테이블 탐색 시간이 오래걸릴 수 있음

## Virtual memory

* 프로그램을 당장 실행에 필요한 부분만 실제 메모리에 올려서 실행
  * 프로그래머는 메모리 크기 제약에서 자유로워질 수 있음
  * 논리 메모리 개념을 통해 엄청나게 큰 메모리 구성 가능
  * 구현이 어려움
  * 잘못 사용하면 성능 저하가 심함
  * 시스템이 멈춰 버릴 수도...

* MMU(Memory Management Unit)
  * 가상 주소를 물리 주소로 빠르게 맵핑

### Demand Paging

* Valid-Invalid Bit
* page fault : i인 프레임에 접근하는 경우
  * 아예 참조할 수 없는 경우
    * abort
  * 메모리에 없을 뿐인 경우
    * 메모리에서 비어있는 프레임을 찾음
    * 찾은 페이지를 프레임으로 swap in
    * 페이지 테이블에서 i를 v로 바꿈
    * 이전 프레임으로 돌아가 재실행
* pure demand paging : 프로그램을 처음 시작할 때 부터 page fault일 경우
  * 모든 프레임을 가져오는 과정이 demand paging임
* 하드웨어 지원
  * valid-invalid  bit를 갖는 페이지테이블을 제공해야함
  * 보조메모리의 swapping 기능 제공
  * Instruction restart  기능 제공
* Copy-On-Write
  * 자식 프로세스가 부모프로세스를 복제할 경우 -> 메모리 페이지 내의 중복
  * 자식 프로세스가 부모 프로세스의 어떤 페이지라도 수정시
    * 복사하여 수정후 수정된 페이지 따로 저장