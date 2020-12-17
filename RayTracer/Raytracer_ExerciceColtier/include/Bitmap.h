#ifndef BITMAP_H
#define BITMAP_H
#include <string>

template <typename T>
struct TRgb;

class Bitmap
{
public:
	Bitmap(const int& _width, const int& _height, const int& _dpi);

	~Bitmap();

	Bitmap(const Bitmap& _bitmap);

	Bitmap& operator=(const Bitmap& _bitmap);

	int Width() const;
	int Height() const;
	int Dpi() const;
	int DataSize() const;
	int Ppm() const;
	int FileSize() const;

	void Save(const std::string& _filename);
	void SetData(TRgb<double>* _data, const int& _size);

private:
	void FillHeader();
	void FillInfo();
	
	int m_width;
	int m_height;
	int m_dpi;
	unsigned char m_fileHeader[14];
	unsigned char m_fileInfo[40];
	int m_dataSize;

	TRgb<double>* m_pData;

	static const int g_headerSize;
	static const unsigned char g_header[14];
	static const double g_factor;
	static const unsigned char g_info[40];
};


#endif // BITMAP_H
