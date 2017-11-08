template <class T>
RingBuffer<T> * RingBuffer <T>::create(size_t i_Size)
{
	DEBUG_PRINT(1, "%s(%d): Creating Bit Field\n", __FILE__, __LINE__);
	void * pMemory = MemoryManager::allocate(sizeof(T)* i_Size);
	if (pMemory == NULL)
		return NULL;
	return new RingBuffer<T>(reinterpret_cast<T *>(pMemory), i_Size);
}
template <class T>
RingBuffer<T>::RingBuffer(T * i_pMemory, size_t i_Size)
{
	m_pBuffer = i_pMemory;
	m_Max = i_Size;
	m_Total = 0;
	m_pCurrentPosition = NULL;
}
template <class T>
RingBuffer<T>::~RingBuffer()
{
	DEBUG_PRINT(1, "%s(%d): Destroyed Bit Field\n", __FILE__, __LINE__);
	MemoryManager::deallocate(m_pBuffer);
}
template <class T>
T RingBuffer<T>::operator[](size_t i_Index)
{
	size_t currentIndex = m_pCurrentPosition - m_pBuffer;
	size_t newIndex = currentIndex - i_Index;
	if (newIndex < 0)
	{
		if (m_Total == m_Max)
			newIndex = m_Max - newIndex;
		else
			newIndex = 0;
	}
	return *(m_pBuffer + newIndex);
}
template <class T>
void RingBuffer<T>::push(T i_Element)
{
	if (m_pCurrentPosition == NULL)
		m_pCurrentPosition = m_pBuffer;
	else
		m_pCurrentPosition++;
	if (m_pCurrentPosition - m_pBuffer == m_Max)
		m_pCurrentPosition = m_pBuffer;
	*m_pCurrentPosition = i_Element;
	if (m_Total < m_Max)
		m_Total++;
}