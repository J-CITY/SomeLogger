#include <iostream>

#include "SomeLogger.h"

using namespace std;
using namespace SomeLogger;

int main() {
	Logger logger = Logger::Instance();

	logger.printEndl(true).log(LoggerLevel::ERR, Color::Red, Color::Blue) << PRINT_LINE_STR << "TEST";


	logger.log(LoggerLevel::ERR, Color::Red, Color::Blue).logFormat(" WWW.FIRMCODES.COM  %d wwa %d", 1321, PRINT_LINE);
	//cout << "\033[1;31mbold red text\033[0m\n";
    logger.printEndl(false);
	List l;

	l << "TEST";
	l << "TEST";
	l << "TEST";
	l << "TEST";
	l << "TEST";

	l.print();

	Table t(5, 5);

	t.insert(1, 1, "!!!!");
	t.insert(1, 2, "!!!!");
	t.insert(1, 3, "!!!!");
	t.insert(4, 4, "!!!!");
	t[2][4] = TableElem("QWQFS");
	t.print();

	cout << t.get(2, 4);
	return 0;
}
