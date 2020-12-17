#include "Bitmap.h"
#include <fstream>
#include <cassert>
#include "ImageTypes.h"

inline const double	Bitmap::g_factor = 39.375;
inline const int Bitmap::g_headerSize = 54;
inline const unsigned char Bitmap::g_header[14] = {
	'B', 'M',
	0, 0, 0, 0,
	0, 0, 0, 0,
	54, 0, 0, 0
};
inline const unsigned char Bitmap::g_info[40] = {
	40, 0, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, 0,
	1, 0, 24, 0
};

Bitmap::Bitmap(const int& _width, const	int& _height, const	int& _dpi)
	: m_width(_width)
	, m_height(_height)
	, m_dpi(_dpi)
	, m_dataSize(0)
	, m_pData(nullptr)
{
	std::copy(g_header, g_header + 14, m_fileHeader);
	std::copy(g_info, g_info + 40, m_fileInfo);
}

Bitmap::~Bitmap()
{
	delete [] m_pData;
	m_pData	= nullptr;
}

Bitmap::Bitmap(const Bitmap& _bitmap)
{
	m_width	= _bitmap.m_width;
	m_height = _bitmap.m_height;
	m_dpi = _bitmap.m_dpi;
	m_dataSize = _bitmap.m_dataSize;
	std::copy(_bitmap.m_fileHeader, _bitmap.m_fileHeader + 14, m_fileHeader);
	std::copy(_bitmap.m_fileInfo, _bitmap.m_fileInfo + 40, m_fileInfo);
	m_pData = new TRgb<double>[_bitmap.m_dataSize];
	std::copy(_bitmap.m_pData, _bitmap.m_pData + _bitmap.m_dataSize, m_pData);
}

Bitmap&	Bitmap::operator=(const	Bitmap&	_bitmap)
{
	m_width	= _bitmap.m_width;
	m_height = _bitmap.m_height;
	m_dpi = _bitmap.m_dpi;
	m_dataSize = _bitmap.m_dataSize;
	std::copy(_bitmap.m_fileHeader, _bitmap.m_fileHeader + 14, m_fileHeader);
	std::copy(_bitmap.m_fileInfo, _bitmap.m_fileInfo + 40, m_fileInfo);
	m_pData	= new TRgb<double>[_bitmap.m_dataSize];
	std::copy(_bitmap.m_pData, _bitmap.m_pData + _bitmap.m_dataSize, m_pData);

	return *this;
}

int	Bitmap::Width()	const
{
	return m_width;
}

int	Bitmap::Height() const
{
	return m_height;
}

int	Bitmap::Dpi() const
{
	return m_dpi;
}

int	Bitmap::DataSize() const
{
	const auto imageSize = m_width * m_height;
	return static_cast<int>(sizeof(int) * imageSize);
}

int	Bitmap::Ppm() const
{
	const auto m = static_cast<int>(g_factor);
	return m_dpi * m;
}

int	Bitmap::FileSize() const
{
	return g_headerSize + DataSize();
}

void Bitmap::Save(const	std::string& _filename)
{
	std::ofstream	file(_filename);

	assert(file.is_open() && "Can’t open the file!");
	const auto imageSize = m_width * m_height;

	file.write(reinterpret_cast<char*>(&m_fileHeader[0]),14);
	file.write(reinterpret_cast<char*>(&m_fileInfo[0]), 40);
	for (auto i = 0; i < imageSize; ++i)
	{
		const auto rgb = m_pData[i];
		const auto b = rgb.b * 255;
		const auto g = rgb.g * 255;
		const auto r = rgb.r * 255;
		unsigned char color[] = { b, g,	r };

		file.write(reinterpret_cast<char*>(&color[0]), 3);
	}

	file.close();
}

void Bitmap::SetData(TRgb<double>* _data, const int& _size)
{
	assert(_size == m_width * m_height && "Data size incompatible");
	delete m_pData;
	m_pData = _data;
	FillHeader();
	FillInfo();
}

void Bitmap::FillHeader()
{
	static const auto start = 2;
	static const auto fileSize = FileSize();
	for (auto i = start; i < 6; ++i)
		m_fileHeader[i] = static_cast<unsigned char>(fileSize >> (i - start) * 8);
}

void Bitmap::FillInfo()
{
	static const auto startWidth = 4;
	for (auto i = startWidth; i < 8; ++i)
		m_fileInfo[i] =	static_cast<unsigned char>(m_width >> (i - startWidth) * 8);

	static const auto startHeight =	8;
	for (auto i = startHeight; i < 12; ++i)
		m_fileInfo[i] =	static_cast<unsigned char>(m_height >> (i - startHeight) * 8);

	static const auto startDataSize	= 21;
	const auto dataSize = DataSize();
	for (auto i = startDataSize; i < 25; ++i)
		m_fileInfo[i] = static_cast<unsigned char>(dataSize	>> (i - startDataSize) * 8);

	static const auto startPpm = 25;
	const auto ppm = Ppm();
	for (auto j = 0; j < 2; ++j)
	{
		const auto start = startPpm + 4 * j;
		for (auto i = start; i < startPpm +	4 * (j + 1); ++i)
			m_fileInfo[i] = static_cast<unsigned char>(ppm >> (i - start) * 8);
	}
}
