#pragma once
#include <array>
#include <mutex>
namespace experis
{
template<typename ValT, size_t MAX_QUEUED>
class CyclinBlockingQueue_mt
{
public:
	explicit CyclinBlockingQueue_mt();
	~CyclinBlockingQueue_mt() = default;

	void Push(const ValT& a_val);
	void Pop(ValT& valToRet);

private:
	size_t NextIdx_unsafe(size_t a_idx);

	std::array<ValT, MAX_QUEUED> m_array;
	std::mutex m_arrayMutex;
	std::condition_variable m_possiblyNotEmpty;
	std::condition_variable m_possiblyNotFull;
	size_t m_idxPush;
	size_t m_idxPop;
};

template<typename ValT, size_t MAX_QUEUED>
CyclinBlockingQueue_mt<ValT, MAX_QUEUED>::CyclinBlockingQueue_mt()
	:m_array{}
	,m_arrayMutex{}
	,m_possiblyNotEmpty{}
	,m_possiblyNotFull{}
	,m_idxPush{0}
	,m_idxPop{0}
{
}

template<typename ValT, size_t MAX_QUEUED>
void CyclinBlockingQueue_mt<ValT,MAX_QUEUED>::Push(const ValT& a_val)
{
	{ //arrayLocker
		std::unique_lock<std::mutex> arrayLocker(m_arrayMutex);
		while (m_idxPop == NextIdx_unsafe(m_idxPush))
		{
			m_possiblyNotFull.wait(arrayLocker);
		}
		m_array[m_idxPush] = a_val;
		m_idxPush = NextIdx_unsafe(m_idxPush);
	}
	m_possiblyNotEmpty.notify_one();
}

template<typename ValT, size_t MAX_QUEUED>
void CyclinBlockingQueue_mt<ValT,MAX_QUEUED>::Pop(ValT& valToRet)
{
	{ //arrayLocker
		std::unique_lock<std::mutex> arrayLocker(m_arrayMutex);
		while (m_idxPop == m_idxPush)
		{
			m_possiblyNotEmpty.wait(arrayLocker);
		}
		valToRet = m_array[m_idxPop];
		m_idxPop = NextIdx_unsafe(m_idxPop);
	}
	m_possiblyNotFull.notify_one();
}

template<typename ValT, size_t MAX_QUEUED>
size_t CyclinBlockingQueue_mt<ValT,MAX_QUEUED>::NextIdx_unsafe(size_t a_idx)
{
	return (a_idx + 1) % MAX_QUEUED;
}
} //experis