#pragma once

template<typename T>
class Singleton
{
public:
	static T& Get()
	{
		static T instance;
		return instance;
	}

protected:
	// Singleton : 클래스의 인스턴스가 1개만 있는 클래스. 
	// private/protected에 생성자를 넣어서 밖에서 인스턴스화 하는 것을 원천적으로 봉쇄
	Singleton() = default;
	virtual ~Singleton() = default;

	Singleton(const Singleton&) = delete;				// 복사 생성자 삭제
	Singleton& operator=(const Singleton&) = delete;	// 대입 연산자 삭제
	Singleton(const Singleton&&) = delete;				// 이동 생성자 삭제
	Singleton& operator=(const Singleton&&) = delete;	// 이동 대입 연산자 삭제

	// Rule of Five
	// 다섯가지 항목 중 하나라도 직접 선언했으면 나머지 네가지도 직접 정의하거나 명시적으로 = default, =delete 해야한다.
	// 1. 소멸자, 2. 복사 생성자, 3. 대입 연산자, 4. 이동 생성자, 5. 이동 대입 연산자
};