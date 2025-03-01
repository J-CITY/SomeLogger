#pragma once

#include <map>
#include <string>
#include <vector>
#include <map>

#ifdef _WIN32
#include <windows.h>
#else

#endif
#include <mutex>
#include <sstream>
#include<stdarg.h>

#define PRINT_LINE __LINE__
#define PRINT_LINE_STR std::to_string(__LINE__)

namespace SomeLogger {

enum class LoggerLevel {
	NONE = 0,
	ERR,
	WARNING,
	DEBUG,
	INFO
};
enum class Color {
	Black = 0,
	Blue,
	Green,
	Red,
	Grey,
	LightGrey,
	Cyan,
	Purple,
	LightBlue,
	LightGreen,
	LightCyan,
	LightRed,
	LightPurple,
	Orange,
	Yellow,
	White
};

#ifdef _WIN32
#else
std::map<Color, std::string> colorToFgColor {
	{ Color::Black, "30" },
	{ Color::Grey, "1;30" },
	{ Color::LightGrey, "1;37" },
	{ Color::White, "37" },
	{ Color::Blue, "34"} ,
	{ Color::Green, "32" },
	{ Color::Cyan, "36" },
	{ Color::Red, "31" },
	{ Color::Purple, "35" },
	{ Color::LightBlue, "1;34" },
	{ Color::LightGreen, "1;32" },
	{ Color::LightCyan, "1;36" },
	{ Color::LightRed, "1;31" },
	{ Color::LightPurple, "1;35" },
	{ Color::Orange, "1;33" },
	{ Color::Yellow, "33" }
};

std::map<Color, std::string> colorToBgColor {
	{ Color::Black, "40" },
	{ Color::Grey, "1;40" },
	{ Color::LightGrey, "1;47" },
	{ Color::White, "47" },
	{ Color::Blue, "44"} ,
	{ Color::Green, "42" },
	{ Color::Cyan, "46" },
	{ Color::Red, "41" },
	{ Color::Purple, "45" },
	{ Color::LightBlue, "1;44" },
	{ Color::LightGreen, "1;42" },
	{ Color::LightCyan, "1;46" },
	{ Color::LightRed, "1;41" },
	{ Color::LightPurple, "1;45" },
	{ Color::Orange, "1;43" },
	{ Color::Yellow, "43" }
};
#endif

class String {
	std::string data;
public:
	String() = default;

	String(const std::string& in) {
		data = in;
	}
	String(int in) {
		data = std::to_string(in);
	}
	String(long in) {
		data = std::to_string(in);
	}
	String(long long in) {
		data = std::to_string(in);
	}
	String(unsigned in) {
		data = std::to_string(in);
	}
	String(unsigned long in) {
		data = std::to_string(in);
	}
	String(unsigned long long in) {
		data = std::to_string(in);
	}
	String(float in) {
		data = std::to_string(in);
	}
	String(double in) {
		data = std::to_string(in);
	}
	String(long double in) {
		data = std::to_string(in);
	}
	String(bool in) {
		data = in ? "true" : "false";
	}
	String(char in) {
		data = std::string(1, in);
	}
	String(unsigned char in) {
		data = std::string(1, in);
	}

	std::string asStr() const {
		return data;
	}
};

struct Endl {
	Endl() = default;
};
struct Endlf {
	Endlf() = default;
};
struct Flush {
	Flush() = default;
};

template<class T>
concept IsCont = 
	requires(T t) { t.size(); } && 
	requires(T t) { t.begin(); } &&
	requires(T t) { t.end(); } &&
	requires(T t) { std::is_same<decltype(t.size()), std::size_t>::value; };


#define HAS_MEM_FUNC(func, name)                                        \
    template<typename T, typename Sign>                                 \
    struct name {                                                       \
        typedef char yes[1];                                            \
        typedef char no [2];                                            \
        template <typename U, U> struct type_check;                     \
        template <typename _1> static yes &chk(type_check<Sign, &_1::func > *); \
        template <typename   > static no  &chk(...);                    \
        static bool const value = sizeof(chk<T>(0)) == sizeof(yes);     \
    }

HAS_MEM_FUNC(toString, has_to_string);

class Logger {
public:
	static Logger& Instance() {
		static Logger logger;
		return logger;
	}

	void setLabelForLevel(const LoggerLevel level, const std::string& label) {
		levelLabel[level] = label;
	}

	Logger& operator<<(const std::string& msg) {
		out(String(msg));
		return *this;
	}
	Logger& operator<<(const char* msg) {
		out(String(std::string(msg)));
		return *this;
	}
	Logger& operator<<(const int& msg) {
		out(String(msg));
		return *this;
	}
	Logger& operator<<(const long& msg) {
		out(String(msg));
		return *this;
	}
	Logger& operator<<(const long long& msg) {
		out(String(msg));
		return *this;
	}
	Logger& operator<<(const unsigned& msg) {
		out(String(msg));
		return *this;
	}
	Logger& operator<<(const unsigned long& msg) {
		out(String(msg));
		return *this;
	}
	Logger& operator<<(const unsigned long long& msg) {
		out(String(msg));
		return *this;
	}
	Logger& operator<<(const float& msg) {
		out(String(msg));
		return *this;
	}
	Logger& operator<<(const double& msg) {
		out(String(msg));
		return *this;
	}
	Logger& operator<<(const long double& msg) {
		out(String(msg));
		return *this;
	}

	Logger& operator<<(Endl msg) {
		endl();
		return *this;
	}

	Logger& operator<<(Endlf msg) {
		endlf();
		return *this;
	}

	Logger& operator<<(Flush msg) {
		flush();
		return *this;
	}

	template<class T>
	Logger& operator<<(const T& arg) {
		constexpr bool has_toString = requires(const T& t) {
			t.toString();
		};
	
		if constexpr (has_toString) {
			out(String(arg.toString()));
		}
		return *this;
	}

	template<class T1, class T2>
	Logger& operator<<(std::pair<T1, T2> const& val) {
		*this << "{" << val.first << " " << val.second << "}";
		return *this;
	}

	template<IsCont Cont>
	Logger& operator<<(Cont cont) {
		auto sz = cont.size();
		for (const auto& e : cont) {
			--sz;
			*this << e << (sz ? seprStr : "");
		}
		return *this;
	}

	Logger& endl() {
		out(endlStr);
		errLevelPrint = false;
		return *this;
	}

	Logger& flush() {
		std::cout.flush();
		errLevelPrint = false;
		return *this;
	}

	Logger& endlf() {
		endl();
		flush();
		return *this;
	}

	Logger& log(LoggerLevel level=LoggerLevel::NONE,
				Color fgColor=Color::White,
				Color bgColor=Color::Black) {
		this->fgColor = fgColor;
		this->bgColor = bgColor;
		this->level = level;
		return *this;
	}

	Logger& setEndl(const std::string& endl) {
		endlStr = endl;
		return *this;
	}

	Logger& setSepr(const std::string& sepr) {
		seprStr = sepr;
		return *this;
	}

	Logger& logFormat(const std::string format, ...) {
		std::lock_guard lg(mutex);

		std::string allFormat = format;
		#ifdef _WIN32
		SetConsoleTextAttribute(hConsole, (static_cast<int>(fgColor) + (static_cast<int>(bgColor)<<1)));
		#else
		puts((std::string("\033[") + colorToFgColor[fgColor] + std::string(";") + colorToBgColor[bgColor] + std::string("m")).c_str());
		#endif
		allFormat += endlStr;

		va_list arg;
		va_start(arg, format);
		bool needCheck = true;
		for (auto& traverse : allFormat) {
			if (traverse == '\0') {
				break;
			}
			if (traverse != '%' && needCheck) {
				out(traverse);
				continue;
			} else if (needCheck) {
				needCheck = false;
				continue;
			}
			needCheck = true;
			switch (traverse) {
				case 'c': {
					int i = va_arg(arg, int);	//Fetch char argument
					out(i);
				}
				break;
				case 'd': {
					int i = va_arg(arg, int); //Fetch Decimal/Integer argument
					if (i < 0) {
						i = -i;
						out('-');
					}
					out(convert(i, 10));
				}
				break;
				case 'o': {
					unsigned i = va_arg(arg, unsigned int); //Fetch Octal representation
					out(convert(i, 8));
				}
				break;
				case 's': {
					auto s = va_arg(arg, char*); //Fetch string
					out(s);
				}
				break;
				case 'x': {
					unsigned i = va_arg(arg, unsigned int); //Fetch Hexadecimal representation
					out(convert(i, 16));
				}
				break;
				case 'b': {
					unsigned i = va_arg(arg, unsigned int); //Fetch binary representation
					out(convert(i, 2));
				}
				break;
			}
		}
		va_end(arg);
		#ifdef _WIN32
		SetConsoleTextAttribute(hConsole, 0x0f);
		#else
		puts("\033[0m\n");
		#endif

		flush();

		return *this;
	}

	~Logger() = default;

	//You could create local logger
	Logger() {
#ifdef _WIN32
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
#else

#endif
	}
private:
	inline static std::mutex mutex;

	bool errLevelPrint = false;

	std::map<LoggerLevel, std::string> levelLabel{
		{ LoggerLevel::NONE, "" },
		{ LoggerLevel::ERR, "ERROR " },
		{ LoggerLevel::WARNING, "WARNING " },
		{ LoggerLevel::DEBUG, "DEBUG " },
		{ LoggerLevel::INFO, "INFO " }
	};

	std::string endlStr = "\n";
	std::string seprStr = ", ";
	Color fgColor = Color::White;
	Color bgColor = Color::Black;
	LoggerLevel level = LoggerLevel::NONE;

	#ifdef _WIN32
	HANDLE  hConsole;
	#endif

	std::string convert(unsigned int num, int base) {
		static char Representation[]= "0123456789ABCDEF";
		std::string res;
		do {
			res = Representation[num % base] + res;
			num /= base;
		} while(num != 0);
		return res;
	}

	void out(const String& msg) {
		#ifdef _WIN32
		SetConsoleTextAttribute(hConsole, (static_cast<int>(fgColor) + (static_cast<int>(bgColor)<<1)));
		std::cout << (errLevelPrint ? "" : levelLabel[level]) << msg.asStr();
		SetConsoleTextAttribute(hConsole, 0x0f);
		#else
		std::cout << std::string("\033[") + colorToFgColor[fgColor] + std::string(";") + colorToBgColor[bgColor] +
			std::string("m") + (errLevelPrint ? "" : levelLabel[level]) + msg.asString() + std::string("\033[0m\n");
		#endif


		errLevelPrint = true;
	}
};


class ListElem {
public:
	LoggerLevel level = LoggerLevel::NONE;
	Color fgColor = Color::White;
	Color bgColor = Color::Black;
	std::string data = "";

	ListElem(std::string data="",
			LoggerLevel level=LoggerLevel::NONE,
			Color fgColor=Color::White,
			Color bgColor=Color::Black) {
		this->data = data;
		this->level = level;
		this->fgColor = fgColor;
		this->bgColor = bgColor;
	}

	size_t size() {
		return data.size();
	}

	void toDefault() {
		level=LoggerLevel::NONE,
		fgColor=Color::White,
		bgColor=Color::Black,
		data = "";
	}
};

class List {
public:
	List() {}

	//TODO add ani simple args
	List& operator<<(const std::string& msg) {
		_list.push_back(ListElem(msg));
		return *this;
	}

	//counr from 0
	void remove(unsigned int id) {
		if (id >= _list.size()) {
			Logger l = Logger::Instance();
			l.log(LoggerLevel::ERR, Color::Red) << "BAD ID";
			return;
		}
		_list.erase(_list.begin() + id);
	}

	void insert(unsigned int id, const std::string& value) {
		if (id >= _list.size()) {
			Logger l = Logger::Instance();
			l.log(LoggerLevel::ERR, Color::Red) << "BAD ID";
			return;
		}
		_list.insert(_list.begin() + id, ListElem(value));
	}

	ListElem get(unsigned int id) {
		if (id >= _list.size()) {
			Logger l = Logger::Instance();
			l.log(LoggerLevel::ERR, Color::Red) << "BAD ID";
			return ListElem();
		}
		return _list[id];
	}

	void clear() {
		_list.clear();
	}

	void print() const {
		Logger& l = Logger::Instance();

		auto cnt = 1;
		for (auto& e : _list) {
			l.log(e.level, e.fgColor, e.bgColor) << format(cnt) << separator << e.data << "\n";
			cnt++;
		}
	}

	std::string toString() const {
		std::string res = "\n";
		auto cnt = 1;
		for (auto& e : _list) {
			res += format(cnt) + separator + e.data + "\n";
			cnt++;
		}
		return res;
	}

	void setSeparator(const std::string& sep) {
		separator = sep;
	}

private:
	std::vector<ListElem> _list;
	std::string separator = ". ";

	std::string format(int e) const {
		auto elemLen = std::to_string(_list.size() + 1).size();
		auto es = std::to_string(e);
		while (es.size() < elemLen) {
			es += " ";
		}
		return es;
	}
};

class TableElem {
public:
	LoggerLevel level = LoggerLevel::NONE;
	Color fgColor = Color::White;
	Color bgColor = Color::Black;
	std::string data = "";

	TableElem(const std::string& data="",
			LoggerLevel level=LoggerLevel::NONE,
			Color fgColor=Color::White,
			Color bgColor=Color::Black) {
		this->data = data;
		this->level = level;
		this->fgColor = fgColor;
		this->bgColor = bgColor;
	}

	size_t size() {
		return data.size();
	}

	void toDefault() {
		level=LoggerLevel::NONE,
		fgColor=Color::White,
		bgColor=Color::Black,
		data = "";
	}
};

class Table {
public:
	Table(int w=0, int h=0) {
		for (auto i = 0; i < h; i++) {
			_table.push_back(std::vector<TableElem>());
			for (auto j = 0; j < w; ++j) {
				_table[i].push_back(TableElem());
			}
		}
	}

	Color fgBorder = Color::Red;
	Color bgBorder = Color::Blue;

	void setElementWidth(int w) {
		elemW = w;
	}

	void insert(unsigned int col, unsigned int row, const std::string& value,
				LoggerLevel level=LoggerLevel::NONE,
				Color fgColor=Color::White,
				Color bgColor=Color::Black) {
		if (row < _table.size() && col < _table[row].size()) {
			_table[row][col] = TableElem(value, level, fgColor, bgColor);
		}
	}

	void remove(unsigned int col, unsigned int row) {
		if (row >= _table.size() || col >= _table[row].size()) {
			Logger l = Logger::Instance();
			l.log(LoggerLevel::ERR, Color::Red) << "BAD IDS";
			return;
		}
		_table[row][col].toDefault();
	}

	std::vector<TableElem> &operator[] (int i) { return _table[i]; }

	void removeRow(int row);
	void removeCol(int col);
	void addRow();
	void addCol();
	void addRowById();
	void addColById();

	std::string get(unsigned int col, unsigned int row) {
		if (row >= _table.size() || col >= _table[row].size()) {
			Logger l = Logger::Instance();
			l.log(LoggerLevel::ERR, Color::Red) << "BAD IDS";
			return "";
		}
		return _table[row][col].data;

	}

	void print() {
		if (_table.size() == 0) {
			return;
		}
		const auto colSize = _table[0].size();

		if (elemW < 0) {
			getColSizes();
		}

		auto borderLen = 1u;
		if (colSizes.size() > 0) {
			for (auto& e : colSizes) {
				borderLen += e + 1;
			}
		} else {
			borderLen += (elemW + 1) * static_cast<unsigned>(colSize);
		}
		Logger l = Logger::Instance();
		for (auto i = 0u; i < borderLen; ++i) {
			if (i == 0) {
				l.log(LoggerLevel::NONE, fgBorder, bgBorder) << border[0];
				continue;
			}
			if (i == borderLen-1) {
				l.log(LoggerLevel::NONE, fgBorder, bgBorder) << border[2];
				continue;
			}
			l.log(LoggerLevel::NONE, fgBorder, bgBorder) << border[1];
		}
		l.log(LoggerLevel::NONE, fgBorder, bgBorder) << "\n";
		for (auto i = 0; i < _table.size(); i++) {
			l.log(LoggerLevel::NONE, fgBorder, bgBorder) << border[3];
			for (auto j = 0; j < _table[i].size(); ++j) {
				TableElem elem = _table[i][j];
				auto elemLen = elemW;
				if (colSizes.size() > 0) {
					elemLen = colSizes[j];
				}
				l.log(elem.level, elem.fgColor, elem.bgColor) << format(elem.data, elemLen);
				l.log(LoggerLevel::NONE, fgBorder, bgBorder) << border[3];
			}
			l.log(LoggerLevel::NONE, fgBorder, bgBorder) << "\n";
			if (i == _table.size()-1) {
				continue;
			}
			for (auto k = 0u; k < borderLen; ++k) {
				if (k == 0) {
					l.log(LoggerLevel::NONE, fgBorder, bgBorder) << border[3];
					continue;
				}
				if (k == borderLen-1) {
					l.log(LoggerLevel::NONE, fgBorder, bgBorder) << border[3];
					continue;
				}
				l.log(LoggerLevel::NONE, fgBorder, bgBorder) << border[1];
			}
			l.log(LoggerLevel::NONE, fgBorder, bgBorder) << "\n";
		}

		for (auto i = 0u; i < borderLen; ++i) {
			if (i == 0u) {
				l.log(LoggerLevel::NONE, fgBorder, bgBorder) << border[4];
				continue;
			}
			if (i == borderLen-1) {
				l.log(LoggerLevel::NONE, fgBorder, bgBorder) << border[6];
				continue;
			}
			l.log(LoggerLevel::NONE, fgBorder, bgBorder) << border[5];
		}
		l.log(LoggerLevel::NONE, fgBorder, bgBorder) << "\n";
	}

	std::string toString() const {
		if (_table.size() == 0) {
			return "";
		}
		const auto colSize = _table[0].size();

		if (elemW < 0) {
			getColSizes();
		}

		auto borderLen = 1u;
		if (colSizes.size() > 0) {
			for (auto& e : colSizes) {
				borderLen += e + 1;
			}
		} else {
			borderLen += (elemW + 1) * static_cast<unsigned>(colSize);
		}
		std::string res = "\n";
		for (auto i = 0u; i < borderLen; ++i) {
			if (i == 0) {
				res += border[0];
				continue;
			}
			if (i == borderLen - 1) {
				res += border[2];
				continue;
			}
			res += border[1];
		}
		res += "\n";
		for (auto i = 0; i < _table.size(); i++) {
			res += border[3];
			for (auto j = 0; j < _table[i].size(); ++j) {
				TableElem elem = _table[i][j];
				auto elemLen = elemW;
				if (colSizes.size() > 0) {
					elemLen = colSizes[j];
				}
				res += format(elem.data, elemLen);
				res += border[3];
			}
			res += "\n";
			if (i == _table.size() - 1) {
				continue;
			}
			for (auto k = 0u; k < borderLen; ++k) {
				if (k == 0) {
					res += border[3];
					continue;
				}
				if (k == borderLen - 1) {
					res += border[3];
					continue;
				}
				res += border[1];
			}
			res += "\n";
		}

		for (auto i = 0u; i < borderLen; ++i) {
			if (i == 0u) {
				res += border[4];
				continue;
			}
			if (i == borderLen - 1) {
				res += border[6];
				continue;
			}
			res += border[5];
		}
		res += "\n";

		return res;
	}

private:
	std::vector<std::string> border = {"/", "-", "\\", "|", "\\", "_", "/"};
	mutable std::vector<unsigned> colSizes;

	int elemW = -1;
	std::vector<std::vector<TableElem>> _table;

	std::string format(std::string elem, int size) const {
		if (elem.size() >= size) {
			return elem.substr(0, size);
		}

		std::string res = elem;
		auto isFront = false;
		while (res.size() < size) {
			if (isFront) {
				res = " " + res;
			} else {
				res += " ";
			}

			isFront = !isFront;
		}
		return res;
	}

	void getColSizes() const {
		colSizes.clear();

		if (!_table.size()) {
			return;
		}
		auto w = _table[0].size();
		for (auto i = 0; i < w; i++) {
			auto _max = 1u;
			for (auto j = 0; j < _table.size(); ++j) {
				auto elemLen = _table[j][i].data.size();
				if (elemLen > _max) {
					_max = static_cast<unsigned>(elemLen);
				}
			}
			colSizes.push_back(_max);
		}
	}
};

};

