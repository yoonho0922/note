### 로컬의 상태를 가장 최근으로 되돌리기 (git stash)
* 현재 로컬의 상태를 백업해두고 가장 최근에 pull 또는 push 했던 상태로 돌아감

### 원격 저장소의 특정 커밋으로 되돌리기 (git reset)
* git reset <commit hash>
* git push origin +master
* 주의 : 지정한 커밋 이후에 했던 커밋들은 모두 사라지고 지정한 커밋으로 돌아감
* 특히 git push origin +master는 강제 푸시로, 잘못 사용하면 돌이킬 수 없는 일이 발생할 수도...
* [관련 문서](https://git-scm.com/book/ko/v2/Git-%EB%8F%84%EA%B5%AC-Reset-%EB%AA%85%ED%99%95%ED%9E%88-%EC%95%8C%EA%B3%A0-%EA%B0%80%EA%B8%B0)
