from enum import Enum

class colors:
	reset='\033[0m'
	bold='\033[01m'
	disable='\033[02m'
	underline='\033[04m'
	reverse='\033[07m'
	strikethrough='\033[09m'
	invisible='\033[08m'
	class fg: 
		black='\033[30m'
		red='\033[31m'
		green='\033[32m'
		orange='\033[33m'
		blue='\033[34m'
		purple='\033[35m'
		cyan='\033[36m'
		lightgrey='\033[37m'
		darkgrey='\033[90m'
		lightred='\033[91m'
		lightgreen='\033[92m'
		yellow='\033[93m'
		lightblue='\033[94m'
		pink='\033[95m'
		lightcyan='\033[96m'
		white='\033[37m'
	class bg: 
		black='\033[40m'
		red='\033[41m'
		green='\033[42m'
		orange='\033[43m'
		blue='\033[44m'
		purple='\033[45m'
		cyan='\033[46m'
		lightgrey='\033[47m'
		white='\033[47m'
	none=''
	error=fg.red
	warning=fg.yellow
	debug=fg.green
	info=fg.white

class Level(Enum):
	NONE = 1
	ERROR = 2
	WARNING = 3
	DEBUG = 3
	INFO = 3
class Message:
	NONE=""
	ERROR="ERROR: "
	WARNING="WARNING: "
	DEBUG="DEBUG: "
	INFO="INFO"
class Logger:
	class __Logger:

		levelToColor =	{
			Level.NONE: colors.none,
			Level.ERROR: colors.error,
			Level.WARNING: colors.warning,
			Level.DEBUG: colors.debug,
			Level.INFO: colors.info,
		}
		levelToLog =	{
			Level.NONE: Message.NONE,
			Level.ERROR: Message.ERROR,
			Level.WARNING: Message.WARNING,
			Level.DEBUG: Message.DEBUG,
			Level.INFO: Message.INFO,
		}
		
		_level = Level.NONE
		
		def log(self, level):
			self._level = level
			return self
		
		def lprint(self, *args, **kwargs):
			print(Logger.instance.levelToColor[Logger.instance._level], Logger.instance.levelToLog[Logger.instance._level], colors.reset, "".join(map(str,args)), end='', sep='')
			print(colors.reset, end='', sep='')

	instance = None
	def __init__(self):
		if not Logger.instance:
			Logger.instance = Logger.__Logger()
	
	def log(self, level):
		if not Logger.instance is None:
			return self.instance.log(level)
		return None
		
	def lprint(self, *args, **kwargs):
		if not Logger.instance is None:
			Logger.instance.lprint(*args, **kwargs)

class List:
	class ElemList:
		fg = colors.fg.white
		bg = colors.bg.black
		level = Level.NONE
		data = ""
		
		def __init__(self, data="", level=Level.NONE, fg=colors.fg.white, bg=colors.bg.black):
			self.fg=fg
			self.bg=bg
			self.level = level
			self.data=data
		
	def __init__(self):
		pass

	def remove(self, id):
		if (id >= len(self._list)):
			l=Logger()
			l.log(Level.ERROR).lprint("BAD ID")
			return
		self._list.erase(id)

	def insert(self, value):
		self._list.append(value);
	
	def insertById(self, id, value):
		if (id >= len(self._list)):
			l=Logger()
			l.log(Level.ERROR).lprint("BAD ID")
			return
		
		self._list.insert(id, value)

	def get(self, id):
		if (id >= len(self._list)):
			l=Logger()
			l.log(Level.ERROR).lprint("BAD ID")
			return ""
		return self._list[id]

	def clear(self):
		_list = []

	def lprint(self):
		cnt = 1;
		l=Logger()
		for e in self._list:
			l.log(e.level).lprint(self._format(cnt), self._separator)
			l.log(e.level).lprint(e.fg, e.bg, e.data, "\n")
			cnt+=1

	def setSeparator(self, sep):
		self._separator = sep
	
	def getList(self):
		return self._list
	def setList(self, l):
		_list = l
	
	_list = []
	_separator = ". "
	
	def _format(self, e):
		elemLen = len(str(len(self._list) + 1))
		es = str(e)
		while (len(es) < elemLen):
			es += " ";
		return es


class Table:
	class TableElem:
		level = Level.NONE
		fgColor = colors.fg.white
		bgColor = colors.bg.black
		data = ""
	
		def __init__(self, data="", level=Level.NONE, fg=colors.fg.white, bg=colors.bg.black):
			self.fg=fg
			self.bg=bg
			self.level = level
			self.data=data
	
		def size(self):
			return len(self.data)
	
		def toDefault(self):
			self.level=Level.NONE
			self.fgColor=colors.fg.white
			self.bgColor=colors.bg.black
			self.data = ""
		
		
	def __init__(self, w=0, h=0):
		self._table = []
		for i in range(0, h):
			self._table.append([])
			for j in range(0, w):
				self._table[i].append(Table.TableElem())

	fgBorder = colors.fg.red;
	bgBorder = colors.bg.blue;

	def setElementWidth(self, w):
		self.elemW = w;

	def insert(self, col, row, value,
				level=Level.NONE,
				fgColor=colors.fg.white,
				bgColor=colors.bg.black):
		if row < len(self._table) and col < len(self._table[row]):
			self._table[row][col] = Table.TableElem(value, level, fgColor, bgColor)


	def remove(self, col, row, value):
		if row >= len(self._table) or col >= len(self._table[row]):
			l=Logger()
			l.log(Level.ERROR).lprint("BAD ID")
			return
		self._table[row][col].toDefault()

	#def removeRow(int row);
	#def removeCol(int col);
	#def addRow();
	#def addCol();
	#def addRowById();
	#def addColById();

	def get(self, col, row):
		if row >= len(self._table) or col >= len(self._table[row]):
			l=Logger()
			l.log(Level.ERROR).lprint("BAD ID")
			return ""
		return self._table[row][col].data

	def tprint(self):
		if len(self._table) == 0:
			return
			
		l=Logger()
		colSize = len(self._table[0])

		if (self.elemW < 0):
			self._getColSizes()

		borderLen = 1;
		if len(self.colSizes) > 0:
			for e in self.colSizes:
				borderLen += e + 1
		else:
			borderLen += (self.elemW + 1) * colSize

		for i in range(0, borderLen):
			if i == 0:
				l.log(Level.NONE).lprint(self.fgBorder, self.bgBorder, self.border[0])
				continue
			if i == borderLen-1:
				l.log(Level.NONE).lprint(self.fgBorder, self.bgBorder, self.border[2])
				continue
			l.log(Level.NONE).lprint(self.fgBorder, self.bgBorder, self.border[1])
		l.log(Level.NONE).lprint('\n')
		for i in range(0, len(self._table)):
			l.log(Level.NONE).lprint(self.fgBorder, self.bgBorder, self.border[3])
			for j in range(0, len(self._table[i])):
				elem = self._table[i][j]
				elemLen = self.elemW
				if len(self.colSizes) > 0:
					elemLen = self.colSizes[j]
				l.log(elem.level).lprint(elem.fgColor, elem.bgColor, self._format(elem.data, elemLen))
				l.log(Level.NONE).lprint(self.fgBorder, self.bgBorder, self.border[3])
			l.log(Level.NONE).lprint('\n')
			if i == len(self._table)-1:
				continue
			for k in range(0, borderLen):
				if k == 0:
					l.log(Level.NONE).lprint(self.fgBorder, self.bgBorder, self.border[3])
					continue
				if k == borderLen-1:
					l.log(Level.NONE).lprint(self.fgBorder, self.bgBorder, self.border[3])
					continue
				l.log(Level.NONE).lprint(self.fgBorder, self.bgBorder, self.border[1])
			l.log(Level.NONE).lprint('\n')
		for i in range(0, borderLen):
			if i == 0:
				l.log(Level.NONE).lprint(self.fgBorder, self.bgBorder, self.border[4])
				continue
			if i == borderLen-1:
				l.log(Level.NONE).lprint(self.fgBorder, self.bgBorder, self.border[6])
				continue
			l.log(Level.NONE).lprint(self.fgBorder, self.bgBorder, self.border[5])
		l.log(Level.NONE).lprint('\n')

	border = ["/", "-", "\\", "|", "\\", "_", "/"]
	colSizes = []

	elemW = -1

	def _format(self, elem, size):
		if len(elem) >= size:
			return elem[:size]

		res = elem
		isFront = False;
		while len(res) < size:
			if isFront:
				res = " " + res
			else:
				res += " "

			isFront = not isFront
		return res

	def _getColSizes(self):
		if len(self._table) == 0:
			return
		w = len(self._table[0])
		self.colSizes = []
		for i in range(0, w):
			_max = 1;
			for j in range(0, len(self._table)):
				elemLen = self._table[j][i].size()
				if elemLen > _max:
					_max = elemLen
			self.colSizes.append(_max)
	
		print(self.colSizes)
	

