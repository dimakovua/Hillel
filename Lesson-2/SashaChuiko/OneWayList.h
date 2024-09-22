#pragma once
template<typename T1,typename T2>
class OneWayList
{
private:
	struct Node
	{
		T1 Value = 0;
		Node* pNext = nullptr;

	};
	T2  size = 0;
	Node* pHead = nullptr;

public:
	void Add(T1 iValue);
	T1 GetValue(T2 uiIndex) const;
	T2 Size() const;
	~OneWayList();
};
template<typename T1, typename T2>
void OneWayList<T1,T2>::Add(T1 iValue)
{
	Node* newNode = new Node;
	newNode->Value = iValue;
	if (pHead == nullptr)
	{
		pHead = newNode;
	}
	else
	{
		Node* lastElem = pHead;
		while (lastElem->pNext)
		{
			lastElem = lastElem->pNext;
		}
		lastElem->pNext = newNode;
	}
	++size;
}
template<typename T1, typename T2>
T1  OneWayList<T1, T2>::GetValue(T2 uiIndex)const
{
	Node* searchElem = pHead;
	for (unsigned int i = 0; i < uiIndex; ++i)
	{
		searchElem = searchElem->pNext;
	}
	return searchElem->Value;
}
template<typename T1, typename T2>
T2  OneWayList<T1, T2>::Size() const
{
	return size;
}
template<typename T1, typename T2>
OneWayList<T1, T2>::~OneWayList()
{
	while (pHead != nullptr)
	{
		Node* pTmp = pHead->pNext;
		delete pHead;
		pHead = pTmp;
	}
}
