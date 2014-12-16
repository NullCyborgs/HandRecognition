#pragma once
#include<atomic>
namespace HandRecognition{
	template<typename T>
	class AtomicWrapper{
	public:
		std::atomic<T> _a;

		AtomicWrapper() :_a(){}

		AtomicWrapper(const std::atomic<T> &a)
			:_a(a.load()){}

		AtomicWrapper(const T& a){
			_a.store(a);
		}

		AtomicWrapper(const AtomicWrapper& other)
			:_a(other._a.load()){}

		AtomicWrapper& operator=(const AtomicWrapper &other){
			_a.store(other._a.load());
		}
		AtomicWrapper& operator=(const T& other){
			_a.store(other);
		}
	};
}