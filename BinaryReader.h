/*
	BinaryReader.h — fast lightweight binary reader library for C++

	Copyright (c) 2026 Max Müller
	https://github.com/max8447/BinaryReader

	MIT License
*/

#pragma once

class BinaryReader
{
public:

private:

	unsigned char* Data;
	unsigned long long	Length;
	unsigned long long	Position;

public:

	BinaryReader(void* InData, unsigned long long InLength, unsigned long long InPosition = 0llu)
		: Data((unsigned char*)InData)
		, Length(InLength)
		, Position(InPosition)
	{
	}

	unsigned char* GetBegin() { return Data; }
	const unsigned char* GetBegin() const { return Data; }

	unsigned char* GetEnd() { return Data + Length; }
	const unsigned char* GetEnd() const { return Data + Length; }

	unsigned char* GetData() { return Data + Position; }
	const unsigned char* GetData() const { return Data + Position; }

	unsigned long long GetLen() { return Length; }
	const unsigned long long GetLen() const { return Length; }

	unsigned long long GetPos() { return Position; }
	const unsigned long long GetPos() const { return Position; }

	void SetPos(unsigned long long InPos) { if (InPos < Length) Position = InPos; }
	void Skip(unsigned long long InLen) { if (Position + InLen < Length) Position += InLen; }

public:

	template<typename T>
	inline T Read();

	template<typename T>
	inline void Read(T& Value);

	template<unsigned long long Len>
	inline void ReadChars(char (&Chars)[Len]);

	inline void ReadChars(char* Chars, unsigned long long Len);

	template<unsigned long long Len>
	inline void ReadUChars(unsigned char (&Chars)[Len]);

	inline void ReadUChars(unsigned char* Chars, unsigned long long Len);

	inline signed char ReadChar();
	inline signed short ReadShort();
	inline signed int ReadInt();
	inline signed long long ReadLongLong();

	inline unsigned char ReadUChar();
	inline unsigned short ReadUShort();
	inline unsigned int ReadUInt();
	inline unsigned long long ReadULongLong();
};

template<typename T>
T BinaryReader::Read()
{
	if (Length == -1 || Position + sizeof(T) <= Length)
	{
		T Value = *(T*)(Data + Position);
		Position += sizeof(T);
		return Value;
	}

	return T{};
}

template<typename T>
void BinaryReader::Read(T& Value)
{
	if (Length == -1 || Position + sizeof(T) <= Length)
	{
		Value = *(T*)(Data + Position);
		Position += sizeof(T);
	}
}

template<unsigned long long Len>
void BinaryReader::ReadChars(char (&Chars)[Len])
{
	for (int i = 0; i < Len; i++)
	{
		Chars[i] = ReadChar();
	}
}

void BinaryReader::ReadChars(char* Chars, unsigned long long Len)
{
	for (int i = 0; i < Len; i++)
	{
		Chars[i] = ReadChar();
	}
}

template<unsigned long long Len>
void BinaryReader::ReadUChars(unsigned char (&Chars)[Len])
{
	for (int i = 0; i < Len; i++)
	{
		Chars[i] = ReadUChar();
	}
}

void BinaryReader::ReadUChars(unsigned char* Chars, unsigned long long Len)
{
	for (int i = 0; i < Len; i++)
	{
		Chars[i] = ReadUChar();
	}
}

signed char BinaryReader::ReadChar()
{
	return Read<signed char>();
}

signed short BinaryReader::ReadShort()
{
	return Read<short>();
}

signed int BinaryReader::ReadInt()
{
	return Read<int>();
}

signed long long BinaryReader::ReadLongLong()
{
	return Read<long long>();
}

unsigned char BinaryReader::ReadUChar()
{
	return Read<unsigned char>();
}

unsigned short BinaryReader::ReadUShort()
{
	return Read<unsigned short>();
}

unsigned int BinaryReader::ReadUInt()
{
	return Read<unsigned int>();
}

unsigned long long BinaryReader::ReadULongLong()
{
	return Read<unsigned long long>();
}
