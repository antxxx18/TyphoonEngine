#pragma once

template<typename T>
void _Delete(T* p)
{
	if (p)
	{
		delete p;
		p = nullptr;
	}
}

template<typename T>
void _DeleteArray(T* p)
{
	if (p)
	{
		delete[] p;
		p = nullptr;
	}
}

template<typename T>
void _Release(T* p)
{
	if (p)
	{
		p->Release();
		p = nullptr;
	}
}

template<typename T>
void _Close(T*& p)
{
	if (p)
	{
		p->Close();
		delete p;
		p = nullptr;
	}
}