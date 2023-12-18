all:compile run clean


compile: main.cpp
	@echo "-------------------------------------------"
	@echo "Compiling..."
	@g++ -g -std=c++11 -o test main.cpp ChessBoard.cpp ChessPiece.cpp

run:
	@echo "-------------------------------------------"
	@echo "Running the tests...."
	@echo "======================================================================="
	@./test
	@echo "======================================================================="
	@echo "Completed tests...."

clean:
	@echo "-------------------------------------------"
	@echo "Cleaning..."
	@rm -f *.o
	@rm -f test
	@rm -rf *.dSYM