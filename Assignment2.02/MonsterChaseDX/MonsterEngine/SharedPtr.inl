namespace Engine
{
	inline SharedPtr::SharedPtr(SharedPtr & i_other) :
		m_ptr(i_other.m_ptr)
		m_pRefCount(i_other.m_pRefCount)


	{
			assert(m_pRefCount != NULL);
			(*m_pRefCount)++;
		}

	inline SharedPtr & SharedPtr::operator=(SharedPtr & i_other)
	{
		assert(m_pRefCount != NULL);

		if (--(*m_pRefCount) == 0)
		{
			if (m_ptr)
				delete m_ptr;
			delete m_pRefCount;
		}

		m_ptr = i_other.m_ptr;
		m_pRefCount = i_other.m_pRefCount;

		(*m_pRefCount)++;
		return *this;
	}

	inline SharedPtr::~SharedPtr()
	{
		assert(m_pRefCount != NULL);
		if (--(*m_pRefCount) == 0)
		{
			if (m_ptr)
				delete m_ptr;
			delete m_pRefCount;
		}
	}

	inline T * SharedPtr::operator->()
	{
		return m_ptr;
	}

	inline T & SharedPtr::operator*()
	{
		assert(m_ptr);

		return *m_ptr;
	}

} // namespace Engine
